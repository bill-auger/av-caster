/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef _AVCASTERSTORE_H_
#define _AVCASTERSTORE_H_

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
  enum AudioCodec   { MP3_AUDIO , AAC_AUDIO } ;
  enum OutputStream { FILE_OUTPUT , RTMP_OUTPUT } ;


private:

  AvCasterStore() ;

  // class helpers
  static StringArray PropertyValues(ValueTree root_node , Identifier property_id) ;


  // persistence
  ValueTree verifyConfig      (ValueTree config_store , Identifier root_node_id) ;
  ValueTree getOrCreatePresets() ;
  ValueTree getOrCreateServers() ;
  void      verifyRoot        () ;
  void      verifyPresets     () ;
  void      verifyPreset      () ;
  void      verifyServers     () ;
  void      verifyServer      (ValueTree a_server_node) ;
  void      sanitizeRoot      () ;
  void      sanitizePresets   () ;
  void      sanitizePreset    () ;
  void      storeConfig       () ;

  // runtime params
  void verifyProperty              (ValueTree config_store    , Identifier a_key ,
                                   var       a_default_value                    ) ;
  void verifyRootProperty          (Identifier a_key , var a_default_value) ;
  void verifyPresetProperty        (Identifier a_key , var a_default_value) ;
  void sanitizeIntProperty        (ValueTree config_store , Identifier a_key ,
                                   int       min_value    , int max_value    ) ;
  void sanitizeRootComboProperty  (Identifier a_key , StringArray options) ;
  void sanitizePresetComboProperty(Identifier a_key , StringArray options) ;
//   void detectDisplayDimensions    () ;
  void detectCaptureDevices       () ;
  void loadPreset                 () ;
  void storePreset                (String preset_name) ;
  void renamePreset               (String preset_name) ;
  void deletePreset               () ;
  void resetPreset                () ;
  void storeServer                (String host , String port) ;

  // event handlers
  void listen                  (bool should_listen) ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildAdded       (ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; }
  void valueTreeChildRemoved     (ValueTree& a_parent_node , ValueTree& a_node) override { UNUSED(a_parent_node) , UNUSED(a_node) ; }
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                     override { UNUSED(a_parent_node) ;                  }
  void valueTreeParentChanged    (ValueTree& a_node)                            override { UNUSED(a_node) ;                         }
  void valueTreeRedirected       (ValueTree& a_node)                            override { UNUSED(a_node) ;                         }
//   TODO: API change after upgrade to v >= 3.2.0
//   void valueTreeChildAdded       (ValueTree& a_parent_node , ValueTree& a_node)           override { UNUSED(a_parent_node) , UNUSED(a_node) ;                      }
//   void valueTreeChildRemoved     (ValueTree& a_parent_node , ValueTree& a_node , int idx) override { UNUSED(a_parent_node) , UNUSED(a_node) ; UNUSED(idx) ;        }
//   void valueTreeChildOrderChanged(ValueTree& a_parent_node , int prev_idx , int curr_idx) override { UNUSED(a_parent_node) ; UNUSED(prev_idx) ; UNUSED(curr_idx) ; }
//   void valueTreeParentChanged    (ValueTree& a_node)                                      override { UNUSED(a_node) ;                                              }
//   void valueTreeRedirected       (ValueTree& a_node)                                      override { UNUSED(a_node) ;                                              }

  // getters/setters
  ValueTree   getKeyNode          (const Identifier& a_key) ;
  bool        isControlKey        (const Identifier& a_key) ;
  StringArray presetsNames        () ;
  StringArray cameraNames         () ;
  StringArray audioNames          () ;
  ValueTree   getCameraConfig     () ;
  StringArray getCameraResolutions() ;
  void        toogleControl       (const Identifier& a_key) ;
  void        setConfig           (const Identifier& a_key , var a_value) ;
  void        updateIrcHost       (StringArray alias_uris , String actual_host) ;
#ifdef PREFIX_CHAT_NICKS
  void        updateChatNicks     (String host , String channel , StringArray nicks) ;
#else // PREFIX_CHAT_NICKS
  void        updateChatNicks     (String host , StringArray nicks) ;
#endif // PREFIX_CHAT_NICKS

  // configuration/persistence
  ValueTree root ;      // config root            (STORAGE_ID node)
  ValueTree presets ;   // persistent GUI config  (PRESETS_ID node)
  ValueTree config ;    // volatile GUI config    (VOLATILE_CONFIG_ID node)
  ValueTree cameras ;   // video devices info     (CAMERA_DEVICES_ID node)
  ValueTree audios ;    // audio devices info     (AUDIO_DEVICES_ID node)
  ValueTree servers ;   // chat servers and nicks (SERVERS_ID node)
  File      configDir ;
  File      configFile ;
} ;


#endif // _AVCASTERSTORE_H_
