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
  // load default and stored configs // TODO: default config nyi
  File dataDir = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  if (!dataDir.isDirectory()) return ;

  this->configFile               = dataDir.getChildFile(CONFIG::STORAGE_FILENAME) ;
  FileInputStream* config_stream = new FileInputStream(this->configFile) ;

  XmlElement* default_xml   = XmlDocument::parse(CONFIG::DEFAULT_CONFIG_XML) ;
  ValueTree   stored_config = (config_stream->openedOk()) ? ValueTree::readFromStream(*config_stream) :
                                                            ValueTree::invalid                        ;

DEBUG_TRACE_LOAD_CONFIG

  // create shared config ValueTree from persistent storage or default xml
  this->configStore = ((validateConfig(stored_config)) ? stored_config                      :
                      ((default_xml != nullptr       ) ? ValueTree::fromXml(*default_xml) :
                                                         ValueTree::invalid               ) ) ;
  storeConfig() ;

  // status display
  this->currentFrame = 0 ;   this->currentFps     = 0 ;
  this->currentQ     = 0.0 ; this->currentSize    = String::empty ;
  this->currentTime  = 0.0 ; this->currentBitrate = String::empty ;

  detectDisplayDimensions() ;
  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;

  detectCaptureDevices() ;
  Trace::TraceState("detected " + String(this->cameraDevices.size()) + " capture devices") ;

//   sanitizeParams() ;

  // cleanup init
  delete config_stream ; if (default_xml != nullptr) delete default_xml ;
}

AvCasterConfig::~AvCasterConfig() { storeConfig() ; }


/* AvCasterConfig private instance methods */

bool AvCasterConfig::validateConfig(ValueTree configStore)
{
  var    config_version    = configStore[CONFIG::CONFIG_VERSION_ID] ;
  double stored_version    = double(config_version) ;
  bool   do_versions_match = stored_version == CONFIG::CONFIG_VERSION ;
  bool   has_stored_config = configStore.isValid() && do_versions_match ;
  if (!do_versions_match) {;} // TODO: convert (if ever necessary)

DEBUG_TRACE_VALIDATE_CONFIG

  return has_stored_config ; // TODO: better validations
}

void AvCasterConfig::storeConfig()
{
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

void AvCasterConfig::detectDisplayDimensions()
{
/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                  but would eliminate platform-specific xwininfo binary dependency
                  (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea) */
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;
  this->desktopW      = area.getWidth() ;
  this->desktopH      = area.getHeight() ;
}

void AvCasterConfig::detectCaptureDevices()
{
#ifndef _WIN32
#  ifndef _MAC
  File*       capture_devices_dir = new File(APP::CAPTURE_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->cameraDevices.clear() ;
  if (capture_devices_dir->containsSubDirectories()                                       &&
    !!capture_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
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

  return ;
#  endif // _MAC
#endif // _WIN32

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
}

void AvCasterConfig::sanitizeParams()
{
/* TODO: ? without external proc
  // test selected capture device readiness
  if (this->proc->start(APP::AVPLAY_TEST_CAM_COMMAND + this->cameraDevice))
    while (!!readProcOutputLines())
    {
      if (hasSubstring(this->proc_out_lines , APP::AVPLAY_CAM_BUSY_ERROR))
        AvCaster::Warning(GUI::CAM_BUSY_ERROR_MSG) ;
    }
*/
  // sanity check capture params
  int capture_w = int(configStore[CONFIG::CAPTURE_W_ID]) ;
  int capture_h = int(configStore[CONFIG::CAPTURE_H_ID]) ;
  int offset_x  = int(configStore[CONFIG::OFFSET_X_ID ]) ;
  int offset_y  = int(configStore[CONFIG::OFFSET_Y_ID ]) ;
  if (capture_w == 0 || offset_x + capture_w > this->desktopW)
    this->configStore.setProperty(CONFIG::CAPTURE_W_ID , var(this->desktopW) , nullptr) ;
  if (capture_h == 0 || offset_y + capture_h > this->desktopH)
    this->configStore.setProperty(CONFIG::CAPTURE_H_ID , var(this->desktopH) , nullptr) ;
  // TODO: test for device/screen existence
//     if (deviceNotExist) this->displayDevice = 0 ;
//     if (screenNotExist) this->displayScreen = 0 ;
}

void AvCasterConfig::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  AvCaster::HandleConfigChanged(a_key) ;
}
