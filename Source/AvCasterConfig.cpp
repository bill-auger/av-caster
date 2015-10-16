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

  // detect hardware and sanitize config
  detectDisplayDimensions() ; detectCaptureDevices() ;
  validateConfig() ; sanitizeConfig() ; storeConfig() ;

  // subscribe to model changes
  this->configStore.addListener(this) ;

  // status display
  this->currentFrame = 0 ;   this->currentFps     = 0 ;
  this->currentQ     = 0.0 ; this->currentSize    = String::empty ;
  this->currentTime  = 0.0 ; this->currentBitrate = String::empty ;

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
  if (!this->configStore.isValid()) return ;

  // transfer missing properties
  validateProperty(CONFIG::CONFIG_VERSION_ID   , var(CONFIG::CONFIG_VERSION              )) ;
  validateProperty(CONFIG::DISPLAY_N_ID        , var(CONFIG::DEFAULT_DISPLAY_N           )) ;
  validateProperty(CONFIG::SCREEN_N_ID         , var(CONFIG::DEFAULT_SCREEN_N            )) ;
  validateProperty(CONFIG::SCREENCAP_W_ID      , var(CONFIG::DEFAULT_SCREENCAP_W         )) ;
  validateProperty(CONFIG::SCREENCAP_H_ID      , var(CONFIG::DEFAULT_SCREENCAP_H         )) ;
  validateProperty(CONFIG::OFFSET_X_ID         , var(CONFIG::DEFAULT_OFFSET_X            )) ;
  validateProperty(CONFIG::OFFSET_Y_ID         , var(CONFIG::DEFAULT_OFFSET_Y            )) ;
  validateProperty(CONFIG::CAMERA_DEV_ID       , var(CONFIG::DEFAULT_CAMERA_DEV_IDX      )) ;
  validateProperty(CONFIG::CAMERA_RES_ID       , var(CONFIG::DEFAULT_CAMERA_RES_IDX      )) ;
  validateProperty(CONFIG::AUDIO_API_ID        , var(CONFIG::DEFAULT_AUDIO_API_IDX       )) ;
  validateProperty(CONFIG::AUDIO_DEVICE_ID     , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX    )) ;
  validateProperty(CONFIG::AUDIO_CODEC_ID      , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX     )) ;
  validateProperty(CONFIG::N_CHANNELS_ID       , var(CONFIG::DEFAULT_N_CHANNELS          )) ;
  validateProperty(CONFIG::SAMPLERATE_ID       , var(CONFIG::DEFAULT_SAMPLERATE_IDX      )) ;
  validateProperty(CONFIG::AUDIO_BITRATE_ID    , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX   )) ;
  validateProperty(CONFIG::OVERLAY_TEXT_ID     , var(CONFIG::DEFAULT_OVERLAY_TEXT        )) ;
  validateProperty(CONFIG::TEXT_STYLE_ID       , var(CONFIG::DEFAULT_TEXT_STYLE_IDX      )) ;
  validateProperty(CONFIG::TEXT_POSITION_ID    , var(CONFIG::DEFAULT_TEXT_POSITION_IDX   )) ;
  validateProperty(CONFIG::OUTPUT_STREAM_ID    , var(CONFIG::DEFAULT_OUTPUT_STREAM_IDX   )) ;
  validateProperty(CONFIG::OUTPUT_CONTAINER_ID , var(CONFIG::DEFAULT_OUTPUT_CONTAINER_IDX)) ;
  validateProperty(CONFIG::OUTPUT_W_ID         , var(CONFIG::DEFAULT_OUTPUT_W            )) ;
  validateProperty(CONFIG::OUTPUT_H_ID         , var(CONFIG::DEFAULT_OUTPUT_H            )) ;
  validateProperty(CONFIG::OUTPUT_FRAMERATE_ID , var(CONFIG::DEFAULT_OUTPUT_FRAMERATE_IDX)) ;
  validateProperty(CONFIG::VIDEO_BITRATE_ID    , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX   )) ;
  validateProperty(CONFIG::OUTPUT_DEST_ID      , var(CONFIG::DEFAULT_OUTPUT_DEST         )) ;
  validateProperty(CONFIG::IS_PREVIEW_ON_ID    , var(CONFIG::DEFAULT_IS_PREVIEW_ON       )) ;
}

void AvCasterConfig::sanitizeConfig() // TODO: ?
{
  if (!this->configStore .isValid() || !this->cameraDevices.isValid() ||
      !this->audioDevices.isValid()                                    ) return ;

  sanitizeComboProperty(CONFIG::CAMERA_DEV_ID       , CONFIG::CAMERA_RESOLUTIONS     ) ;
  sanitizeComboProperty(CONFIG::CAMERA_DEV_ID       , nodeValues(this->cameraDevices)) ;
  sanitizeComboProperty(CONFIG::AUDIO_API_ID        , CONFIG::AUDIO_APIS             ) ;
  sanitizeComboProperty(CONFIG::AUDIO_DEVICE_ID     , nodeValues(this->audioDevices) ) ;
  sanitizeComboProperty(CONFIG::AUDIO_CODEC_ID      , CONFIG::AUDIO_CODECS           ) ;
  sanitizeComboProperty(CONFIG::SAMPLERATE_ID       , CONFIG::AUDIO_SAMPLERATES      ) ;
  sanitizeComboProperty(CONFIG::AUDIO_BITRATE_ID    , CONFIG::AUDIO_BITRATES         ) ;
  sanitizeComboProperty(CONFIG::TEXT_STYLE_ID       , CONFIG::TEXT_STYLES            ) ;
  sanitizeComboProperty(CONFIG::TEXT_POSITION_ID    , CONFIG::TEXT_POSITIONS         ) ;
  sanitizeComboProperty(CONFIG::OUTPUT_STREAM_ID    , CONFIG::OUTPUT_STREAMS         ) ;
  sanitizeComboProperty(CONFIG::OUTPUT_CONTAINER_ID , CONFIG::OUTPUT_CONTAINERS      ) ;
  sanitizeComboProperty(CONFIG::OUTPUT_FRAMERATE_ID , CONFIG::OUTPUT_FRAMERATES      ) ;
  sanitizeComboProperty(CONFIG::VIDEO_BITRATE_ID    , CONFIG::VIDEO_BITRATES         ) ;

  validateConfig() ;
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
#if JUCE_WINDOWS || JUCE_MAC
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
#endif // JUCE_WINDOWS || JUCE_MAC
#if JUCE_LINUX

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

#endif // JUCE_LINUX

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


/* event handlers */

void AvCasterConfig::validateProperty(Identifier a_key , var a_default_value)
{
  if (!this->configStore.hasProperty(a_key))
    this->configStore.setProperty(a_key , a_default_value , nullptr) ;
}


/* helpers */

void AvCasterConfig::sanitizeIntProperty(Identifier a_key , int min_value , int max_value)
{
  int a_value = int(this->configStore[a_key]) ;

  if (a_value < min_value || a_value > max_value)
    this->configStore.removeProperty(a_key , nullptr) ;
}

void AvCasterConfig::sanitizeComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(a_key , 0 , options.size() - 1) ;
}

void AvCasterConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  AvCaster::HandleConfigChanged(a_key) ;
}

StringArray AvCasterConfig::nodeValues(ValueTree a_node)
{
  int n_values = a_node.getNumProperties() ; StringArray values ;
  for (int value_n = 0 ; value_n < n_values ; ++value_n)
  {
    Identifier a_key   = a_node.getPropertyName(value_n) ;
    var        a_value = a_node.getProperty(a_key , "n/a") ;

    values.add(a_value) ;
  }

  return values ;
}
