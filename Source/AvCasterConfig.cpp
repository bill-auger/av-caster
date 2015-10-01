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
  this->configStore   = verifyConfig(stored_config , CONFIG::STORAGE_ID) ;
  this->cameraDevices = ValueTree(CONFIG::CAMERA_DEVICES_ID) ;
  this->audioDevices  = ValueTree(CONFIG::AUDIO_DEVICES_ID ) ;
  validateConfig() ; sanitizeConfig() ; storeConfig() ;

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

ValueTree AvCasterConfig::verifyConfig(ValueTree stored_config , Identifier root_node_id)
{
  bool      is_config_valid = stored_config.isValid() && stored_config.hasType(root_node_id) ;
  ValueTree config_store    = (is_config_valid) ? stored_config : ValueTree(CONFIG::STORAGE_ID) ;

  double stored_version    = double(config_store[CONFIG::CONFIG_VERSION_ID]) ;
  bool   do_versions_match = stored_version ==   CONFIG::CONFIG_VERSION ;
  if (!do_versions_match) { ; } // TODO: convert (if ever necessary)

DEBUG_TRACE_VALIDATE_CONFIG

  return config_store ;
}

void AvCasterConfig::validateConfig()
{
  // transfer missing properties
  validateConfigProperty(CONFIG::CONFIG_VERSION_ID , var(CONFIG::CONFIG_VERSION           )) ;
  validateConfigProperty(CONFIG::DISPLAY_N_ID      , var(CONFIG::DEFAULT_DISPLAY_N        )) ;
  validateConfigProperty(CONFIG::SCREEN_N_ID       , var(CONFIG::DEFAULT_SCREEN_N         )) ;
  validateConfigProperty(CONFIG::SCREENCAP_W_ID    , var(CONFIG::DEFAULT_SCREENCAP_W      )) ;
  validateConfigProperty(CONFIG::SCREENCAP_H_ID    , var(CONFIG::DEFAULT_SCREENCAP_H      )) ;
  validateConfigProperty(CONFIG::OFFSET_X_ID       , var(CONFIG::DEFAULT_OFFSET_X         )) ;
  validateConfigProperty(CONFIG::OFFSET_Y_ID       , var(CONFIG::DEFAULT_OFFSET_Y         )) ;
  validateConfigProperty(CONFIG::CAMERA_DEV_ID     , var(CONFIG::DEFAULT_CAMERA_DEV_IDX   )) ;
  validateConfigProperty(CONFIG::CAMERA_RES_ID     , var(CONFIG::DEFAULT_CAMERA_RES_IDX   )) ;
  validateConfigProperty(CONFIG::AUDIO_API_ID      , var(CONFIG::DEFAULT_AUDIO_API_IDX    )) ;
  validateConfigProperty(CONFIG::AUDIO_DEVICE_ID   , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX )) ;
  validateConfigProperty(CONFIG::AUDIO_CODEC_ID    , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX  )) ;
  validateConfigProperty(CONFIG::N_CHANNELS_ID     , var(CONFIG::DEFAULT_N_CHANNELS       )) ;
  validateConfigProperty(CONFIG::SAMPLERATE_ID     , var(CONFIG::DEFAULT_SAMPLERATE_IDX   )) ;
  validateConfigProperty(CONFIG::AUDIO_BITRATE_ID  , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX)) ;
  validateConfigProperty(CONFIG::OVERLAY_TEXT_ID   , var(CONFIG::DEFAULT_OVERLAY_TEXT     )) ;
  validateConfigProperty(CONFIG::TEXT_STYLE_ID     , var(CONFIG::DEFAULT_TEXT_STYLE_IDX   )) ;
  validateConfigProperty(CONFIG::TEXT_POS_ID       , var(CONFIG::DEFAULT_TEXT_POS_IDX     )) ;
  validateConfigProperty(CONFIG::OUTPUT_STREAM_ID  , var(CONFIG::DEFAULT_OUTPUT_STREAM_IDX)) ;
  validateConfigProperty(CONFIG::OUTPUT_W_ID       , var(CONFIG::DEFAULT_OUTPUT_W         )) ;
  validateConfigProperty(CONFIG::OUTPUT_H_ID       , var(CONFIG::DEFAULT_OUTPUT_H         )) ;
  validateConfigProperty(CONFIG::FRAMERATE_ID      , var(CONFIG::DEFAULT_FRAMERATE_IDX    )) ;
  validateConfigProperty(CONFIG::BITRATE_ID        , var(CONFIG::DEFAULT_BITRATE_IDX      )) ;
  validateConfigProperty(CONFIG::OUTPUT_DEST_ID    , var(CONFIG::DEFAULT_OUTPUT_DEST      )) ;
  validateConfigProperty(CONFIG::IS_PREVIEW_ON_ID  , var(CONFIG::DEFAULT_IS_PREVIEW_ON    )) ;
}

void AvCasterConfig::sanitizeConfig() { } // TODO: ?

void AvCasterConfig::storeConfig()
{
DEBUG_TRACE_DUMP_CONFIG

  if (!this->configStore.isValid()) return ;

  this->configFile.deleteFile() ;

  // create storage directory
  File user_dir   = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  File config_dir = user_dir.getChildFile(CONFIG::STORAGE_DIRNAME) ;
  config_dir.createDirectory() ;

  // filter dynamic params
  this->configStore.removeChild(this->cameraDevices , nullptr) ;
  this->configStore.removeChild(this->audioDevices  , nullptr) ;

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) this->configStore.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;

  // restore dynamic params
  this->configStore.addChild(this->cameraDevices , -1 , nullptr) ;
  this->configStore.addChild(this->audioDevices  , -1 , nullptr) ;
}


/* runtime params */

void AvCasterConfig::detectDisplayDimensions()
{
/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                  (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea)
                  gStreamer handles resolution changes gracefully so this  may not be strictly necessary */
/*
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;

  this->desktopW      = area.getWidth() ;
  this->desktopH      = area.getHeight() ;

  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;
*/
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
  this->cameraDevices.removeAllProperties(nullptr) ;
  if (camera_devices_dir->containsSubDirectories()                                       &&
    !!camera_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
  {
    File* device_info_dir = device_info_dirs.begin() ;
    while (device_info_dir != device_info_dirs.end())
    {
      String device_name   = device_info_dir->getFileName() ;
      String friendly_name = device_info_dir->getChildFile("name").loadFileAsString().trim() ;
      this->cameraDevices.setProperty(Identifier(device_name) , var(friendly_name) , nullptr) ;
      ++device_info_dir ;
    }
  }
  else AvCaster::Warning(GUI::NO_CAMERAS_ERROR_MSG) ;

#endif // defined(_WIN32) || defined(_MAC)

  Trace::TraceState("detected " + String(this->cameraDevices.getNumProperties()) + " capture devices") ;
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

void AvCasterConfig::validateConfigProperty(Identifier a_key , var a_default_value)
{
  if (!this->configStore.hasProperty(a_key))
    this->configStore.setProperty(a_key , a_default_value , nullptr) ;
}

void AvCasterConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  AvCaster::HandleConfigChanged(a_key) ;
}
