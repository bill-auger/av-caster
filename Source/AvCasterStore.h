/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef AVCASTERSTORE_H_INCLUDED
#define AVCASTERSTORE_H_INCLUDED

#include "Constants.h"


/**
  AvCasterStore is the model class for the AvCaster application.
  It holds the runtime configuration via shared value holders
      and handles persistence via JUCE binary storage.
*/
class AvCasterStore : ValueTree::Listener
{
  friend class AvCaster ;


public:

  ~AvCasterStore() ;


  enum AudioApi     { ALSA_AUDIO , PULSE_AUDIO , JACK_AUDIO } ;
//   enum MainInput    { SCREENCAP_INPUT , INTERSTITIAL_INPUT } ; // TODO: GUI nyi
//   enum OverlayInput { CAMERA_INPUT , LOGO_INPUT } ;            // TODO: GUI nyi
  enum AudioCodec   { AAC_AUDIO , MP3_AUDIO } ;
//   enum VideoCodec   { X264_VIDEO } ;                           // TODO: GUI nyi
  enum OutputStream { FILE_OUTPUT , RTMP_OUTPUT } ;

  // configuration/persistence
  ValueTree configRoot ;    // config root           (STORAGE_ID node)
  ValueTree configPresets ; // persistent GUI config (PRESETS_ID node)
  ValueTree configStore ;   // volatile GUI config   (VOLATILE_CONFIG_ID node)
  ValueTree cameraDevices ; // video devices info    (CAMERA_DEVICES_ID node)
  ValueTree audioDevices ;  // audio devices info    (AUDIO_DEVICES_ID node)


private:

  AvCasterStore() ;

  // persistence
  ValueTree verifyConfig  (ValueTree config_store , Identifier root_node_id) ;
  void      validateConfig() ;
  void      validatePreset() ;
  void      sanitizeConfig() ;
  void      storeConfig   () ;

  // runtime params
  void validateProperty           (ValueTree config_store    , Identifier a_key ,
                                   var       a_default_value                    ) ;
  void validateRootProperty       (Identifier a_key , var a_default_value) ;
  void validatePresetProperty     (Identifier a_key , var a_default_value) ;
  void sanitizeIntProperty        (ValueTree config_store , Identifier a_key ,
                                   int       min_value    , int max_value    ) ;
  void sanitizeRootComboProperty  (Identifier a_key , StringArray options) ;
  void sanitizePresetComboProperty(Identifier a_key , StringArray options) ;
  void detectDisplayDimensions    () ;
  void detectCaptureDevices       () ;
  void loadPreset                 () ;
  void storePreset                (String preset_name) ;
  void deletePreset               () ;

  // event handlers
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // helpers
  StringArray presetsNames() ;
  StringArray devicesNames(ValueTree a_devices_node) ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildAdded       (ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; }
  void valueTreeChildRemoved     (ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; }
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override { UNUSED(a_parent_node) ;                  }
  void valueTreeParentChanged    (ValueTree& a_node)                            override { UNUSED(a_node) ;                         }
  void valueTreeRedirected       (ValueTree& a_node)                            override { UNUSED(a_node) ;                         }
//   after upgrade to v >= 3.2.0
//   void valueTreeChildAdded       (ValueTree& a_parent_node , ValueTree& a_node)           override { UNUSED(a_parent_node) , UNUSED(a_node) ;                      }
//   void valueTreeChildRemoved     (ValueTree& a_parent_node , ValueTree& a_node , int idx) override { UNUSED(a_parent_node) , UNUSED(a_node) ; UNUSED(idx) ;        }
//   void valueTreeChildOrderChanged(ValueTree& a_parent_node , int prev_idx , int curr_idx) override { UNUSED(a_parent_node) ; UNUSED(prev_idx) ; UNUSED(curr_idx) ; }
//   void valueTreeParentChanged    (ValueTree& a_node)                                      override { UNUSED(a_node) ;                                              }
//   void valueTreeRedirected       (ValueTree& a_node)                                      override { UNUSED(a_node) ;                                              }


  File configFile ;
} ;


#endif // AVCASTERSTORE_H_INCLUDED
