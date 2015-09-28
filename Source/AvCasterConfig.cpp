/*
  ==============================================================================

    AvCasterConfig.cpp
    Created: 26 Sep 2015 3:53:12am
    Author:  me

  ==============================================================================
*/

#include "AvCasterConfig.h"
#include "AvCaster.h"
#include "Trace/TraceAvCasterConfig.h"


AvCasterConfig::AvCasterConfig()
{
  // load stored configs
  ValueTree stored_config = ValueTree::invalid ;
  File      user_dir      = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  if (user_dir.isDirectory())
  {
    this->configFile               = user_dir.getChildFile(CONFIG::STORAGE_FILENAME) ;
    FileInputStream* config_stream = new FileInputStream(this->configFile) ;

    if (config_stream->openedOk()) stored_config = ValueTree::readFromStream(*config_stream) ;
    delete config_stream ;
  }

  // create shared config ValueTree from persistent storage or defaults
  this->configStore = validateConfig(stored_config , CONFIG::STORAGE_ID) ;
  sanitizeConfig() ; storeConfig() ;

  // subscribe to model changes
  this->configStore.addListener(this) ;

  // status display
  this->currentFrame = 0 ;   this->currentFps     = 0 ;
  this->currentQ     = 0.0 ; this->currentSize    = String::empty ;
  this->currentTime  = 0.0 ; this->currentBitrate = String::empty ;

  detectDisplayDimensions() ; detectCaptureDevices() ;
}

AvCasterConfig::~AvCasterConfig() { storeConfig() ; }


/* AvCasterConfig private instance methods */

ValueTree AvCasterConfig::validateConfig(ValueTree config_store , Identifier root_node_id)
{
DEBUG_TRACE_VALIDATE_CONFIG

  bool is_config_valid = config_store.isValid() && config_store.hasType(root_node_id) ;

  return (is_config_valid) ? config_store : ValueTree(CONFIG::STORAGE_ID) ;
}

void AvCasterConfig::sanitizeConfig()
{
  double stored_version    = double(this->configStore[CONFIG::CONFIG_VERSION_ID]) ;
  bool   do_versions_match = stored_version == CONFIG::CONFIG_VERSION ;
  if (!do_versions_match) { ; } // TODO: convert (if ever necessary)

DEBUG_TRACE_SANITIZE_CONFIG

  if (!this->configStore.hasProperty(CONFIG::CONFIG_VERSION_ID))
    setConfig(CONFIG::CONFIG_VERSION_ID , var(CONFIG::CONFIG_VERSION           )) ;
  if (!this->configStore.hasProperty(CONFIG::DISPLAY_N_ID     ))
    setConfig(CONFIG::DISPLAY_N_ID      , var(CONFIG::DEFAULT_DISPLAY_N        )) ;
  if (!this->configStore.hasProperty(CONFIG::SCREEN_N_ID      ))
    setConfig(CONFIG::SCREEN_N_ID       , var(CONFIG::DEFAULT_SCREEN_N         )) ;
  if (!this->configStore.hasProperty(CONFIG::SCREENCAP_W_ID   ))
    setConfig(CONFIG::SCREENCAP_W_ID    , var(CONFIG::DEFAULT_SCREENCAP_W      )) ;
  if (!this->configStore.hasProperty(CONFIG::SCREENCAP_H_ID   ))
    setConfig(CONFIG::SCREENCAP_H_ID    , var(CONFIG::DEFAULT_SCREENCAP_H      )) ;
  if (!this->configStore.hasProperty(CONFIG::OFFSET_X_ID      ))
    setConfig(CONFIG::OFFSET_X_ID       , var(CONFIG::DEFAULT_OFFSET_X         )) ;
  if (!this->configStore.hasProperty(CONFIG::OFFSET_Y_ID      ))
    setConfig(CONFIG::OFFSET_Y_ID       , var(CONFIG::DEFAULT_OFFSET_Y         )) ;
  if (!this->configStore.hasProperty(CONFIG::CAMERA_DEV_ID    ))
    setConfig(CONFIG::CAMERA_DEV_ID     , var(CONFIG::DEFAULT_CAMERA_DEV_IDX   )) ;
  if (!this->configStore.hasProperty(CONFIG::CAMERA_RES_ID    ))
    setConfig(CONFIG::CAMERA_RES_ID     , var(CONFIG::DEFAULT_CAMERA_RES_IDX   )) ;
  if (!this->configStore.hasProperty(CONFIG::AUDIO_API_ID     ))
    setConfig(CONFIG::AUDIO_API_ID      , var(CONFIG::DEFAULT_AUDIO_API_IDX    )) ;
  if (!this->configStore.hasProperty(CONFIG::AUDIO_DEVICE_ID  ))
    setConfig(CONFIG::AUDIO_DEVICE_ID   , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX )) ;
  if (!this->configStore.hasProperty(CONFIG::AUDIO_CODEC_ID   ))
    setConfig(CONFIG::AUDIO_CODEC_ID    , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX  )) ;
  if (!this->configStore.hasProperty(CONFIG::N_CHANNELS_ID    ))
    setConfig(CONFIG::N_CHANNELS_ID     , var(CONFIG::DEFAULT_N_CHANNELS       )) ;
  if (!this->configStore.hasProperty(CONFIG::SAMPLERATE_ID    ))
    setConfig(CONFIG::SAMPLERATE_ID     , var(CONFIG::DEFAULT_SAMPLERATE_IDX   )) ;
  if (!this->configStore.hasProperty(CONFIG::AUDIO_BITRATE_ID ))
    setConfig(CONFIG::AUDIO_BITRATE_ID  , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX)) ;
  if (!this->configStore.hasProperty(CONFIG::OVERLAY_TEXT_ID  ))
    setConfig(CONFIG::OVERLAY_TEXT_ID   , var(CONFIG::DEFAULT_OVERLAY_TEXT     )) ;
  if (!this->configStore.hasProperty(CONFIG::TEXT_STYLE_ID    ))
    setConfig(CONFIG::TEXT_STYLE_ID     , var(CONFIG::DEFAULT_TEXT_STYLE_IDX   )) ;
  if (!this->configStore.hasProperty(CONFIG::TEXT_POS_ID      ))
    setConfig(CONFIG::TEXT_POS_ID       , var(CONFIG::DEFAULT_TEXT_POS_IDX     )) ;
  if (!this->configStore.hasProperty(CONFIG::OUTPUT_STREAM_ID ))
    setConfig(CONFIG::OUTPUT_STREAM_ID  , var(CONFIG::DEFAULT_OUTPUT_STREAM_IDX)) ;
  if (!this->configStore.hasProperty(CONFIG::OUTPUT_W_ID      ))
    setConfig(CONFIG::OUTPUT_W_ID       , var(CONFIG::DEFAULT_OUTPUT_W         )) ;
  if (!this->configStore.hasProperty(CONFIG::OUTPUT_H_ID      ))
    setConfig(CONFIG::OUTPUT_H_ID       , var(CONFIG::DEFAULT_OUTPUT_H         )) ;
  if (!this->configStore.hasProperty(CONFIG::FRAMERATE_ID     ))
    setConfig(CONFIG::FRAMERATE_ID      , var(CONFIG::DEFAULT_FRAMERATE_IDX    )) ;
  if (!this->configStore.hasProperty(CONFIG::BITRATE_ID       ))
    setConfig(CONFIG::BITRATE_ID        , var(CONFIG::DEFAULT_BITRATE_IDX      )) ;
  if (!this->configStore.hasProperty(CONFIG::OUTPUT_DEST_ID   ))
    setConfig(CONFIG::OUTPUT_DEST_ID    , var(CONFIG::DEFAULT_OUTPUT_DEST      )) ;
}

void AvCasterConfig::storeConfig()
{
DEBUG_TRACE_DUMP_CONFIG

  if (!this->configStore.isValid()) return ;

  this->configFile.deleteFile() ;

  // create storage directory
  File user_dir   = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  File config_dir = user_dir.getChildFile(CONFIG::STORAGE_DIRNAME) ;
  config_dir.createDirectory() ;

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) this->configStore.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;
}


/* runtime params */

void AvCasterConfig::detectDisplayDimensions()
{
/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                  but would eliminate platform-specific xwininfo binary dependency
                  (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea) */
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;
  this->desktopW      = area.getWidth() ;
  this->desktopH      = area.getHeight() ;

  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;
}

void AvCasterConfig::detectCaptureDevices()
{
#if defined(_WIN32) || defined(_MAC)
/* mac and windows only (issue #6 issue #8)
// Returns a list of the available cameras on this machine.
  StringArray video_devs = juce::CameraDevice::getAvailableDevices() ;
DBG(video_devs.joinIntoString("\n")) ;
  while (video_devs.size())
  {
DBG("video_devs=" + video_devs[0]) ;

    video_devs.remove(0) ;
  }
*/
/* mac and windows only (issue #6 issue #8)
You can open one of these devices by calling openDevice().
static CameraDevice* CameraDevice::openDevice   (
    int   deviceIndex,
    int   minWidth = 128,
    int   minHeight = 64,
    int   maxWidth = 1024,
    int   maxHeight = 768
  )
*/
#else // defined(_WIN32) || defined(_MAC)

  File*       camera_devices_dir = new File(APP::CAMERA_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->cameraDevices.clear() ;
  if (camera_devices_dir->containsSubDirectories()                                       &&
    !!camera_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
  {
    File* device_info_dir = device_info_dirs.begin() ;
    while (device_info_dir != device_info_dirs.end())
    {
      String device_name = device_info_dir->getChildFile("name").loadFileAsString() ;
      this->cameraDevices.add(device_name) ;
      ++device_info_dir ;
    }
  }
  else AvCaster::Warning(GUI::NO_CAMERAS_ERROR_MSG) ;

#endif // defined(_WIN32) || defined(_MAC)

  Trace::TraceState("detected " + String(this->cameraDevices.size()) + " capture devices") ;
}

void AvCasterConfig::sanitizeParams()
{
/* TODO: ? test is camera busy without external proc
  // test selected capture device readiness
  if (this->proc->start(APP::AVPLAY_TEST_CAM_COMMAND + this->cameraDevice))
    while (!!readProcOutputLines())
    {
      if (hasSubstring(this->proc_out_lines , APP::AVPLAY_CAM_BUSY_ERROR))
        AvCaster::Warning(GUI::CAM_BUSY_ERROR_MSG) ;
    }
*/
/* TODO: gStreamer does not have a problem with screen coordinates OOB
  // sanity check capture params
  int screencap_w = int(this->configStore[CONFIG::SCREENCAP_W_ID]) ;
  int screencap_h = int(this->configStore[CONFIG::SCREENCAP_H_ID]) ;
  int offset_x    = int(this->configStore[CONFIG::OFFSET_X_ID ]) ;
  int offset_y    = int(this->configStore[CONFIG::OFFSET_Y_ID ]) ;
  if (screencap_w == 0 || offset_x + screencap_w > this->desktopW)
    setConfig(CONFIG::SCREENCAP_W_ID , var(this->desktopW)) ;
  if (screencap_h == 0 || offset_y + screencap_h > this->desktopH)
    setConfig(CONFIG::SCREENCAP_H_ID , var(this->desktopH)) ;
*/

// TODO: test for device/screen existence
//  if (deviceNotExist) this->displayDevice = 0 ;
//  if (screenNotExist) this->displayScreen = 0 ;
}


/* getters/setter and listeners */

void AvCasterConfig::setConfig(Identifier a_key , var a_value)
{
  this->configStore.setProperty(a_key , a_value , nullptr) ;
}

void AvCasterConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  AvCaster::HandleConfigChanged(a_key) ;
}
