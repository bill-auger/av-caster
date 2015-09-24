/*
  ==============================================================================

    AvCasterConfig.h
    Created: 26 Sep 2015 3:53:12am
    Author:  me

  ==============================================================================
*/

#ifndef AVCASTERCONFIG_H_INCLUDED
#define AVCASTERCONFIG_H_INCLUDED

#include "Constants.h"


class AvCasterConfig
{
  friend class AvCaster ;


public:

  ~AvCasterConfig() ;

  enum AudioApi      { ALSA_AUDIO , PULSE_AUDIO , JACK_AUDIO } ;
/* TODO: GUI nyi
  enum MainInput     { SCREENCAP_INPUT , INTERSTITIAL_INPUT } ;
  enum OverlayInput  { CAMERA_INPUT , LOGO_INPUT } ;
  enum AudioCodec    { AAC_AUDIO , MP3_AUDIO } ;
  enum VideoCodec    { X264_VIDEO } ;
  enum OutputStream  { FILE_OUTPUT , NET_OUTPUT } ;
*/


private:

  AvCasterConfig() ;

  void detectDisplayDimensions() ;
  void detectCaptureDevices() ;
  void sanitizeParams() ;


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


#endif // AVCASTERCONFIG_H_INCLUDED
