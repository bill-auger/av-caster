/*
  ==============================================================================

    AvCaster.h
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/

#ifndef AVCASTER_H_INCLUDED
#define AVCASTER_H_INCLUDED

#include <gst/gst.h>

#include "Constants.h"
#include "MainContent.h"


class Alert
{
public:

  Alert(GUI::AlertType message_type , String message_text)
  {
    this->messageType = message_type ;
    this->messageText = message_text ;
  }

  GUI::AlertType messageType ;
  String         messageText ;
} ;

class AvStream : public Thread
{
  friend class AvCaster ;


public:

  ~AvStream() { this->proc->kill() ; delete this->proc ; }

  enum AudioApi      { ALSA_AUDIO , PULSE_AUDIO , JACK_AUDIO } ;
/* TODO: GUI nyi
  enum MainInput     { SCREENCAP_INPUT , INTERSTITIAL_INPUT } ;
  enum OverlayInput  { CAMERA_INPUT , LOGO_INPUT } ;
  enum AudioCodec    { AAC_AUDIO , MP3_AUDIO } ;
  enum VideoCodec    { X264_VIDEO } ;
  enum OutputStream  { FILE_OUTPUT , NET_OUTPUT } ;
*/

private:

  AvStream(const String& thread_name) : Thread(thread_name)
  {
    this->proc           = new ChildProcess() ;
    this->proc_out[0]    = '\0' ;
    this->proc_out_lines = StringArray() ;
    this->proc_out_tail  = String::empty ;

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
  }

  void   run() override ;
  void   detectDisplayDimensions() ;
  void   detectCaptureDevices() ;
  void   sanitizeParams() ;
  String buildAvconvMuxCommand() ;
  bool   readProcOutput() ;
  int    readProcOutputLines() ;
  bool   isSystemSane() ;
  String findSubstring(  StringArray haystack , String needle) ;
  bool   hasSubstring(   StringArray haystack , String needle) ;
  bool   hasAnySubstring(StringArray haystack , StringArray needles) ;
  bool   areRuntimeErrors() ;


  ChildProcess* proc ;
  char          proc_out[APP::PROC_BUFFER_SIZE] ;
  StringArray   proc_out_lines ;
  String        proc_out_tail ;
  // screen configuration
//   uint8 mainInput ; // GUI nyi
  uint16 desktopW ;
  uint16 desktopH ;
  uint8  displayDevice ;
  uint8  displayScreen ;
  uint16 captureW ;
  uint16 captureH ;
  uint16 offsetX ;
  uint16 offsetY ;
  // camera configuration
//   uint8 overlayInput ; // GUI nyi
  StringArray cameraDevices ;
  String      cameraDevice ;
  StringArray cameraResolutions ;
  String      cameraResolution ;
  // audio configuration
  StringArray audioInputs ;
  uint8       audioInput ;
//   uint8       audioCodec ; // GUI nyi
  uint8       nChannels ;
  StringArray samplerates ;
  String      samplerate ;
  StringArray audioBitrates ;
  String      audioBitrate ;
  // output configuration
//   StringArray outputStreams; // GUI nyi
//   uint8       outputStream ; // GUI nyi
  String      outputDest ;
  uint8       videoCodec ;
  StringArray outputResolutions ;
  String      outputResolution ;
  StringArray outputQualities ;
  String      outputQuality ;
  StringArray framerates ;
  String      framerate ;
  StringArray videoBitrates ;
  String      videoBitrate ;
  // text configuration
  String      overlayText ;
  StringArray textStyles ;
  String      textStyle ;
  StringArray textPositions ;
  String      textPosition ;
  // status display
  uint32 currentFrame ;
  uint8  currentFps ;
  float  currentQ ;
  String currentSize ;
  float  currentTime ;
  String currentBitrate ;
} ;


class AvCaster
{
  friend class AvCasterApplication ;

public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error(  String message_text) ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* getModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;


private:

  // setup
  static bool Initialize(MainContent* main_content , const String& args) ;
//   static bool Initialize(JUCEApplication* main_app , MainContent* main_content ,
//                          const String&    args                                 ) ;
  static bool SetVideoWindowHandles() ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer(int timer_id) ;
  static void UpdateStatusGUI() ;

//   static JUCEApplication* App ;
  static MainContent*            Gui ;
  static GstElement*             OutputMonitorGst ;
  static ScopedPointer<AvStream> MuxStream ;
  static Array<Alert*>           Alerts ;
  static bool                    IsAlertModal ;
} ;

#endif  // AVCASTER_H_INCLUDED
