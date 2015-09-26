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


/**
  LinJamConfig is the model class
  it holds the runtime configuration via shared value holders
      and handles persistence via JUCE binary storage TODO: persistence nyi
*/
class AvCasterConfig : ValueTree::Listener
{
  friend class AvCaster ;


public:

  ~AvCasterConfig() ;

  void componentMovedOrResized(Component& a_component , bool wasMoved  , bool wasResized) ;


  enum AudioApi      { ALSA_AUDIO , PULSE_AUDIO , JACK_AUDIO } ;
/* TODO: GUI nyi
  enum MainInput     { SCREENCAP_INPUT , INTERSTITIAL_INPUT } ;
  enum OverlayInput  { CAMERA_INPUT , LOGO_INPUT } ;
  enum AudioCodec    { AAC_AUDIO , MP3_AUDIO } ;
  enum VideoCodec    { X264_VIDEO } ;
  enum OutputStream  { FILE_OUTPUT , NET_OUTPUT } ;
*/

  // config root
  ValueTree configStore ; // STORAGE_ID node


private:

  AvCasterConfig() ;

  // persistence
  bool validateConfig(ValueTree configStore) ;
  void storeConfig() ;

  // runtime params
  void detectDisplayDimensions() ;
  void detectCaptureDevices() ;
  void sanitizeParams() ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildAdded(       ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; } ;
  void valueTreeChildRemoved(     ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; } ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override { UNUSED(a_parent_node) ; } ;
  void valueTreeParentChanged(    ValueTree& a_node)                            override { UNUSED(a_node) ;        } ;
  void valueTreeRedirected(       ValueTree& a_node)                            override { UNUSED(a_node) ;        } ;


  File configFile ;

  // configuration
  uint16      desktopW ;
  uint16      desktopH ;
  StringArray cameraDevices ;
//   StringArray audioDevices ;

  // status display
  uint32 currentFrame ;
  uint8  currentFps ;
  float  currentQ ;
  String currentSize ;
  float  currentTime ;
  String currentBitrate ;
} ;


#endif // AVCASTERCONFIG_H_INCLUDED
