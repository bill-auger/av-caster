/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef AVCASTERCONFIG_H_INCLUDED
#define AVCASTERCONFIG_H_INCLUDED

#include "Constants.h"


/**
  AvCasterConfig is the model class for the AvCaster application
  It holds the runtime configuration via shared value holders
      and handles persistence via JUCE binary storage
*/
class AvCasterConfig : ValueTree::Listener
{
  friend class AvCaster ;


public:

  ~AvCasterConfig() ;

  void componentMovedOrResized(Component& a_component , bool wasMoved  , bool wasResized) ;


  enum AudioApi     { ALSA_AUDIO , PULSE_AUDIO , JACK_AUDIO } ;
//   enum MainInput    { SCREENCAP_INPUT , INTERSTITIAL_INPUT } ; // TODO: GUI nyi
//   enum OverlayInput { CAMERA_INPUT , LOGO_INPUT } ;            // TODO: GUI nyi
  enum AudioCodec   { AAC_AUDIO , MP3_AUDIO } ;
//   enum VideoCodec   { X264_VIDEO } ;                           // TODO: GUI nyi
  enum OutputStream { FILE_OUTPUT , RTMP_OUTPUT } ;

  // configuration/persistence
  ValueTree configStore ;   // config root (STORAGE_ID node)
  ValueTree cameraDevices ; // (CAMERA_DEVICES_ID node)
  ValueTree audioDevices ;  // (AUDIO_DEVICES_ID node)


private:

  AvCasterConfig() ;

  // persistence
  ValueTree verifyConfig(  ValueTree config_store , Identifier root_node_id) ;
  void      validateConfig() ;
  void      sanitizeConfig() ;
  void      storeConfig() ;

  // runtime params
  void detectDisplayDimensions() ;
  void detectCaptureDevices() ;
  void sanitizeParams() ; // unused
  void validateProperty(     Identifier a_key , var a_default_value) ;
  void sanitizeIntProperty(  Identifier a_key , int min_value , int max_value) ;
  void sanitizeComboProperty(Identifier a_key , StringArray options) ;

  // event handlers
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // helpers
  StringArray nodeValues(ValueTree a_devices_node) ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildAdded(       ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; } ;
  void valueTreeChildRemoved(     ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; } ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override { UNUSED(a_parent_node) ; } ;
  void valueTreeParentChanged(    ValueTree& a_node)                            override { UNUSED(a_node) ;        } ;
  void valueTreeRedirected(       ValueTree& a_node)                            override { UNUSED(a_node) ;        } ;


  File configFile ;

  // status display
  uint32 currentFrame ;
  uint8  currentFps ;
  float  currentQ ;
  String currentSize ;
  float  currentTime ;
  String currentBitrate ;
} ;


#endif // AVCASTERCONFIG_H_INCLUDED
