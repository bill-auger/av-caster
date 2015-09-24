/*
  ==============================================================================

    AvCasterConfig.cpp
    Created: 26 Sep 2015 3:53:12am
    Author:  me

  ==============================================================================
*/

#include "AvCasterConfig.h"
#include "AvCaster.h"
#include "Trace/Trace.h"


AvCasterConfig::AvCasterConfig()
{
  // screen configuration
//     this->mainInput = 0 ; // GUI nyi
  this->desktopW      = 0 ; this->desktopH      = 0 ;
  this->displayDevice = 0 ; this->displayScreen = 0 ;
  this->captureW      = 0 ; this->captureH      = 0 ;
  this->offsetX       = 0 ; this->offsetY       = 0 ;
  // camera configuration
//     this->overlayInput = 0 ; // GUI nyi
  this->cameraDevices     = StringArray() ; this->cameraDevice     = "" ;
  this->cameraResolutions = StringArray() ; this->cameraResolution = "" ;
  // audio configuration
  this->audioInputs   = StringArray() ;
  this->audioInput    = 0 ; // this->audioCodec = 0 ;// GUI nyi
  this->nChannels     = 0 ;
  this->samplerates   = StringArray() ; this->samplerate   = "" ;
  this->audioBitrates = StringArray() ; this->audioBitrate = "" ;
  // text configuration
  this->overlayText   = "" ;
  this->textStyles    = StringArray() ; this->textStyle    = "" ;
  this->textPositions = StringArray() ; this->textPosition = "" ;
  // output configuration
//    this->outputStreams     = StringArray() ; this->outputStream     = 0 ;  // GUI nyi
  this->outputDest        = "" ;         // this->videoCodec       = 0 ; // GUI nyi
  this->outputResolutions = StringArray() ; this->outputResolution = "" ;
  this->outputQualities   = StringArray() ; this->outputQuality    = "" ;
  this->framerates        = StringArray() ; this->framerate        = "" ;
  this->videoBitrates     = StringArray() ; this->videoBitrate     = "" ;
  // status display
  this->currentFrame = 0 ;   this->currentFps     = 0 ;
  this->currentQ     = 0.0 ; this->currentSize    = String::empty ;
  this->currentTime  = 0.0 ; this->currentBitrate = String::empty ;


  detectDisplayDimensions() ;
  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;

  detectCaptureDevices() ;
  Trace::TraceState("detected " + String(this->cameraDevices.size()) + " capture devices") ;

  sanitizeParams() ;
}

AvCasterConfig::~AvCasterConfig() {}


/* AvCasterConfig private instance methods */

void AvCasterConfig::detectDisplayDimensions()
{
#define CROSS_PLATFORM_RESOLUTION_DETECTION
#ifndef CROSS_PLATFORM_RESOLUTION_DETECTION
  if (this->proc->start(APP::DISPLAY_DIMS_COMMAND) && readProcOutput())
  {
    StringArray tokens     = StringArray::fromTokens(this->proc_out , false) ;
    tokens.removeEmptyStrings(true) ;
    int         width_idx  = tokens.indexOf(APP::DISPLAY_DIMS_WIDTH_TOKEN ) + 1 ;
    int         height_idx = tokens.indexOf(APP::DISPLAY_DIMS_HEIGHT_TOKEN) + 1 ;
    if (!!width_idx && !!height_idx)
    {
      this->desktopW = tokens[width_idx ].getIntValue() ;
      this->desktopH = tokens[height_idx].getIntValue() ;
    }
  }

#else // CROSS_PLATFORM_RESOLUTION_DETECTION

/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                  but would eliminate platform-specific xwininfo binary dependency
                  (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea) */
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;
  this->desktopW = area.getWidth() ;
  this->desktopH = area.getHeight() ;

#endif // CROSS_PLATFORM_RESOLUTION_DETECTION
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
      if (hasSubstring(this->proc_out_lines , APP::AVCONV_CAM_BUSY_ERROR))
        AvCaster::Warning(GUI::CAM_BUSY_ERROR_MSG) ;
    }
*/
  // sanity check capture params
  if (this->captureW == 0 || this->offsetX + this->captureW > this->desktopW)
    this->captureW = this->desktopW ;
  if (this->captureH == 0 || this->offsetY + this->captureH > this->desktopH)
    this->captureH = this->desktopH ;
  // TODO: test for device/screen existence
//     if (deviceNotExist) this->displayDevice = 0 ;
//     if (screenNotExist) this->displayScreen = 0 ;
}
