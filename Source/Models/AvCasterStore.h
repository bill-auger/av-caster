/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef _AVCASTERSTORE_H_
#define _AVCASTERSTORE_H_

#include "../Constants/Constants.h"


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

  // class helpers
  static StringArray PropertyValues(ValueTree root_node , Identifier property_id) ;


private:

  // initialize
  AvCasterStore() ;

  // validations
  void verifyConfig               () ;
  void verifyRoot                 () ;
  void verifyPresets              () ;
  void verifyPreset               () ;
  void verifyNetworks             () ;
  void verifyNetwork              (ValueTree a_network_node) ;
  void sanitizeRoot               () ;
  void sanitizePresets            () ;
  void sanitizePreset             () ;
  void verifyChildNode            (ValueTree config_store , Identifier a_node_id) ;
  void verifyPresetChildNode      (Identifier a_node_id) ;
  void verifyProperty             (ValueTree config_store    , Identifier a_key ,
                                   var       a_default_value                    ) ;
  void verifyRootProperty         (Identifier a_key , var a_default_value) ;
  void verifyNetworkProperty      (Identifier a_key , var a_default_value) ;
  void verifyPresetProperty       (Identifier a_key , var a_default_value) ;
  void restoreStaticPresets       () ;
  bool hasDuplicatedNodes         (ValueTree stored_config) ;
  int  nDuplicatedNodes           (ValueTree parent_node , StringArray node_ids) ;
  void removeConflictedNodes      (ValueTree parent_node , Identifier node_id) ;
  void filterRogueKeys            (ValueTree parent_node , StringArray persistent_keys) ;
  void filterRogueNodes           (ValueTree parent_node , StringArray persistent_node_ids) ;
  void sanitizeIntProperty        (ValueTree config_store , Identifier a_key ,
                                   int       min_value    , int max_value    ) ;
  void sanitizeRootComboProperty  (Identifier a_key , StringArray options) ;
  void sanitizePresetComboProperty(Identifier a_key , StringArray options) ;
  void restoreTransients          () ;
  void restorePresetTransients    (ValueTree a_preset_store) ;

  // persistence
  ValueTree loadConfig() ;
  void      storeConfig () ;
  void      loadPreset  () ;
  void      storePreset (String preset_name) ;
  void      renamePreset(String preset_name) ;
  void      deletePreset() ;
  void      resetPreset () ;

  // runtime params
//   void detectDisplayDimensions    () ;
  void detectCaptureDevices       () ;

  // event handlers
  void listen                  (bool should_listen) ;
  void valueTreePropertyChanged(ValueTree& a_node , const Identifier& key) override ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildAdded       (ValueTree& /*a_parent_node*/ , ValueTree& /*a_node*/                   ) override {}
  void valueTreeChildRemoved     (ValueTree& /*a_parent_node*/ , ValueTree& /*a_node*/ , int /*idx*/     ) override {}
  void valueTreeChildOrderChanged(ValueTree& /*a_parent_node*/ , int /*prev_idx*/      , int /*curr_idx*/) override {}
  void valueTreeParentChanged    (ValueTree& /*a_node*/                                                  ) override {}
  void valueTreeRedirected       (ValueTree& /*a_node*/                                                  ) override {}

  // getters/setters
  bool        isMediaToggleKey    (const Identifier& a_key) ;
  bool        isPresetConfigKey   (const Identifier& a_key) ;
  void        deactivateControl   (const Identifier& a_key) ;
  bool        isKnownProperty     (ValueTree a_node  , const Identifier& a_key) ;
  void        setProperty         (ValueTree a_node  , const Identifier& a_key ,
                                   const var a_value                           ) ;
  void        setValue            (ValueTree storage_node , const Identifier& a_key ,
                                   const var a_value                                ) ;
  void        setValueViaGui      (ValueTree storage_node , const Identifier& a_key ,
                                   const var a_value                                ) ;
  void        updateChatters      (StringArray nicks) ;
  StringArray presetsNames        () ;
  StringArray cameraNames         () ;
  StringArray audioNames          () ;
  ValueTree   getCameraStore      () ;
  StringArray getCameraResolutions() ;
  StringArray getChatNicks        () ;


  // configuration/persistence
  ValueTree root ;        // persistent static config  (STORAGE_ID node        )
  ValueTree presets ;     // persistent dynamic config (PRESETS_ID node        )
  ValueTree config ;      // volatile media config     (VOLATILE_CONFIG_ID node)
  ValueTree network ;     // volatile network config   (NETWORK_ID node        )
  ValueTree chatters ;    // volatile nicks list       (CHATTERS_ID node       )
  ValueTree cameras ;     // video devices info        (CAMERA_DEVICES_ID node )
  ValueTree audios ;      // audio devices info        (AUDIO_DEVICES_ID node  )
  File      storageDir ;
  File      storageFile ;
} ;

#endif // _AVCASTERSTORE_H_
