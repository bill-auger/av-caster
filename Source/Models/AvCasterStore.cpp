/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "AvCasterStore.h"
#include "Seeds.h"
#include "../Controllers/AvCaster.h"
#include "../Trace/TraceAvCasterStore.h"


/* AvCasterStore private class methods */

StringArray AvCasterStore::PropertyValues(ValueTree root_node , Identifier property_id)
{
  int         n_children = root_node.getNumChildren() ;
  StringArray values ;

  for (int child_n = 0 ; child_n < n_children ; ++child_n)
  {
    ValueTree child_node = root_node.getChild(child_n) ;
    String    value      = STRING(child_node[property_id]) ;

    values.add(value) ;
  }

  return values ;
}


/* AvCasterStore public instance methods */

AvCasterStore::~AvCasterStore() { }


/* AvCasterStore private instance methods */

AvCasterStore::AvCasterStore()
{
  // create shared config ValueTrees from persistent storage or defaults
  this->root    = loadConfig() ; verifyConfig() ;
  this->presets = this->root.getOrCreateChildWithName(CONFIG::PRESETS_ID , nullptr) ;
  this->config  = ValueTree(CONFIG::VOLATILE_CONFIG_ID) ;
  this->network = ValueTree(CONFIG::NETWORK_ID        ) ;
  this->config.addChild   (this->network , -1 , nullptr) ;
  this->root  .removeChild(this->presets ,      nullptr) ; // ignore store events

  // validate and sanitize config
  verifyRoot() ;   verifyPresets() ;
  sanitizeRoot() ; sanitizePresets() ;
  verifyRoot() ;   verifyPresets() ;
  restoreTransients() ; loadPreset() ; storeConfig() ;

  // create or assign aliases to transient shared config ValueTrees
  this->chatters = ValueTree(CONFIG::CHATTERS_ID      ) ;
  this->cameras  = ValueTree(CONFIG::CAMERA_DEVICES_ID) ;
  this->audios   = ValueTree(CONFIG::AUDIO_DEVICES_ID ) ;

  // detect hardware
  detectCaptureDevices() ; // detectDisplayDimensions() ; // TODO: (issue #2 issue #4)

DEBUG_TRACE_DUMP_CONFIG_ALL
}

void AvCasterStore::shutdown() { listen(false) ; storeConfig() ; }


/* validations */

void AvCasterStore::verifyConfig()
{
  // verify or reset stored configuration
  bool was_storage_found   = this->root.isValid() ;
  bool is_root_valid       = this->root.hasType(CONFIG::STORAGE_ID) ;
  bool has_canonical_nodes = !hasDuplicatedNodes(this->root) ;
  if (!was_storage_found || !is_root_valid) this->root = Seeds::DefaultStore() ;
  else if (!has_canonical_nodes) removeConflictedNodes(this->root , CONFIG::PRESETS_ID) ;

  // verify schema version
  int  stored_version    = int(this->root[CONFIG::CONFIG_VERSION_ID]) ;
  bool do_versions_match = stored_version == CONFIG::CONFIG_VERSION ;
  if (!do_versions_match)
  {
    // TODO: convert (if ever necessary)
    File parent_dir  = this->storageFile.getParentDirectory() ;
    File backup_file = parent_dir.getNonexistentChildFile(CONFIG::STORAGE_FILENAME , ".bak" , false) ;
    this->storageFile.copyFileTo(backup_file) ;

    this->root.removeProperty(CONFIG::CONFIG_VERSION_ID , nullptr) ;
  }

DEBUG_TRACE_VERIFY_STORED_CONFIG
}

void AvCasterStore::verifyRoot()
{
  // ensure missing properties exist
  verifyRootProperty(CONFIG::CONFIG_VERSION_ID , var(CONFIG::CONFIG_VERSION    )) ;
  verifyRootProperty(CONFIG::PRESET_ID         , var(CONFIG::DEFAULT_PRESET_IDX)) ;
}

void AvCasterStore::verifyPresets()
{
  // ensure default preset configurations exist
  ValueTree file_preset_store = this->presets.getChild(CONFIG::FILE_PRESET_IDX) ;
  ValueTree rtmp_preset_store = this->presets.getChild(CONFIG::RTMP_PRESET_IDX) ;
  ValueTree lctv_preset_store = this->presets.getChild(CONFIG::LCTV_PRESET_IDX) ;
  if (!file_preset_store.isValid() || file_preset_store.getType() != CONFIG::FILE_PRESET_ID ||
      !rtmp_preset_store.isValid() || rtmp_preset_store.getType() != CONFIG::RTMP_PRESET_ID ||
      !lctv_preset_store.isValid() || lctv_preset_store.getType() != CONFIG::LCTV_PRESET_ID  )
    restoreStaticPresets() ;

  // verify preset nodes
  for (int preset_n = 0 ; preset_n < this->presets.getNumChildren() ; ++preset_n)
  {
    ValueTree preset_store  = this->presets.getChild(preset_n) ;
    ValueTree network_store = preset_store.getChildWithName(CONFIG::NETWORK_ID) ;

    this->config .copyPropertiesFrom(preset_store  , nullptr) ;
    this->network.copyPropertiesFrom(network_store , nullptr) ;
    verifyPreset() ;
    preset_store .copyPropertiesFrom(this->config  , nullptr) ;
    network_store.copyPropertiesFrom(this->network , nullptr) ;
  }
}

void AvCasterStore::verifyPreset()
{
DEBUG_TRACE_VERIFY_PRESET

  // ensure missing properties exist
  verifyPresetProperty (CONFIG::SCREEN_ID        , var(CONFIG::DEFAULT_IS_SCREEN_ACTIVE )) ;
  verifyPresetProperty (CONFIG::CAMERA_ID        , var(CONFIG::DEFAULT_IS_CAMERA_ACTIVE )) ;
  verifyPresetProperty (CONFIG::TEXT_ID          , var(CONFIG::DEFAULT_IS_TEXT_ACTIVE   )) ;
  verifyPresetProperty (CONFIG::IMAGE_ID         , var(CONFIG::DEFAULT_IS_IMAGE_ACTIVE  )) ;
  verifyPresetProperty (CONFIG::PREVIEW_ID       , var(CONFIG::DEFAULT_IS_PREVIEW_ACTIVE)) ;
  verifyPresetProperty (CONFIG::AUDIO_ID         , var(CONFIG::DEFAULT_IS_AUDIO_ACTIVE  )) ;
  verifyPresetProperty (CONFIG::PRESET_NAME_ID   , var(CONFIG::DEFAULT_PRESET_NAME      )) ;
  verifyPresetProperty (CONFIG::CONFIG_PANE_ID   , var(CONFIG::DEFAULT_CONFIG_PANE      )) ;
  verifyPresetProperty (CONFIG::DISPLAY_N_ID     , var(CONFIG::DEFAULT_DISPLAY_N        )) ;
  verifyPresetProperty (CONFIG::SCREEN_N_ID      , var(CONFIG::DEFAULT_SCREEN_N         )) ;
  verifyPresetProperty (CONFIG::SCREENCAP_W_ID   , var(CONFIG::DEFAULT_SCREENCAP_W      )) ;
  verifyPresetProperty (CONFIG::SCREENCAP_H_ID   , var(CONFIG::DEFAULT_SCREENCAP_H      )) ;
  verifyPresetProperty (CONFIG::OFFSET_X_ID      , var(CONFIG::DEFAULT_OFFSET_X         )) ;
  verifyPresetProperty (CONFIG::OFFSET_Y_ID      , var(CONFIG::DEFAULT_OFFSET_Y         )) ;
  verifyPresetProperty (CONFIG::CAMERA_DEVICE_ID , var(CONFIG::DEFAULT_CAMERA_DEVICE_IDX)) ;
  verifyPresetProperty (CONFIG::CAMERA_RES_ID    , var(CONFIG::DEFAULT_CAMERA_RES_IDX   )) ;
  verifyPresetProperty (CONFIG::AUDIO_API_ID     , var(CONFIG::DEFAULT_AUDIO_API_IDX    )) ;
  verifyPresetProperty (CONFIG::AUDIO_DEVICE_ID  , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX )) ;
  verifyPresetProperty (CONFIG::AUDIO_CODEC_ID   , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX  )) ;
  verifyPresetProperty (CONFIG::N_CHANNELS_ID    , var(CONFIG::DEFAULT_N_CHANNELS       )) ;
  verifyPresetProperty (CONFIG::SAMPLERATE_ID    , var(CONFIG::DEFAULT_SAMPLERATE_IDX   )) ;
  verifyPresetProperty (CONFIG::AUDIO_BITRATE_ID , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX)) ;
  verifyPresetProperty (CONFIG::MOTD_TEXT_ID     , var(CONFIG::DEFAULT_MOTD_TEXT        )) ;
  verifyPresetProperty (CONFIG::TEXT_STYLE_ID    , var(CONFIG::DEFAULT_TEXT_STYLE_IDX   )) ;
  verifyPresetProperty (CONFIG::TEXT_POSITION_ID , var(CONFIG::DEFAULT_TEXT_POSITION_IDX)) ;
  verifyPresetProperty (CONFIG::IMAGE_LOC_ID     , var(CONFIG::DEFAULT_IMAGE_LOCATION   )) ;
  verifyPresetProperty (CONFIG::OUTPUT_SINK_ID   , var(CONFIG::DEFAULT_OUTPUT_SINK_IDX  )) ;
  verifyPresetProperty (CONFIG::OUTPUT_MUXER_ID  , var(CONFIG::DEFAULT_OUTPUT_MUXER_IDX )) ;
  verifyPresetProperty (CONFIG::OUTPUT_W_ID      , var(CONFIG::DEFAULT_OUTPUT_W         )) ;
  verifyPresetProperty (CONFIG::OUTPUT_H_ID      , var(CONFIG::DEFAULT_OUTPUT_H         )) ;
  verifyPresetProperty (CONFIG::FRAMERATE_ID     , var(CONFIG::DEFAULT_FRAMERATE_IDX    )) ;
  verifyPresetProperty (CONFIG::VIDEO_BITRATE_ID , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX)) ;
  verifyPresetProperty (CONFIG::OUTPUT_DEST_ID   , var(CONFIG::DEFAULT_OUTPUT_DEST      )) ;
  verifyPresetChildNode(CONFIG::NETWORK_ID) ;
  verifyNetworkProperty(CONFIG::NETWORK_ID       , var(CONFIG::DEFAULT_NETWORK          )) ;
  verifyNetworkProperty(CONFIG::PORT_ID          , var(CONFIG::DEFAULT_PORT             )) ;
  verifyNetworkProperty(CONFIG::NICK_ID          , var(CONFIG::DEFAULT_NICK             )) ;
  verifyNetworkProperty(CONFIG::PASS_ID          , var(CONFIG::DEFAULT_PASS             )) ;
  verifyNetworkProperty(CONFIG::CHANNEL_ID       , var(CONFIG::DEFAULT_CHANNEL          )) ;
  verifyNetworkProperty(CONFIG::TIMESTAMPS_ID    , var(CONFIG::DEFAULT_SHOW_TIMESTAMPS  )) ;
  verifyNetworkProperty(CONFIG::JOINPARTS_ID     , var(CONFIG::DEFAULT_SHOW_JOINPARTS   )) ;
  verifyNetworkProperty(CONFIG::GREETING_ID      , var(CONFIG::DEFAULT_GREETING         )) ;

  // filter any rogue data
  filterRogueKeys (this->root    , CONFIG::RootPersistentKeys()    ) ;
  filterRogueKeys (this->config  , CONFIG::PresetPersistentKeys()  ) ;
  filterRogueKeys (this->network , CONFIG::NetworkPersistentKeys() ) ;
  filterRogueNodes(this->root    , CONFIG::RootPersistentNodes()   ) ;
  filterRogueNodes(this->config  , CONFIG::PresetPersistentNodes() ) ;
  filterRogueNodes(this->network , CONFIG::NetworkPersistentNodes()) ;
}

void AvCasterStore::sanitizeRoot()
{
  sanitizeRootComboProperty(CONFIG::PRESET_ID , presetsNames()) ;
}

void AvCasterStore::sanitizePresets()
{
DEBUG_TRACE_SANITIZE_PRESETS

  // sanitize user-defined preset configurations
  int n_presets = this->presets.getNumChildren() ;
  for (int preset_n = CONFIG::N_STATIC_PRESETS ; preset_n < n_presets ; ++preset_n)
  {
    ValueTree preset_store = this->presets.getChild(preset_n) ;

    this->config.copyPropertiesFrom(preset_store , nullptr) ; sanitizePreset() ;
    preset_store.copyPropertiesFrom(this->config , nullptr) ;
  }
}

void AvCasterStore::sanitizePreset()
{
  sanitizePresetComboProperty(CONFIG::CAMERA_RES_ID    , getCameraResolutions()    ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEVICE_ID , cameraNames()             ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_API_ID     , CONFIG::AudioApis()       ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_DEVICE_ID  , audioNames()              ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_CODEC_ID   , CONFIG::AudioCodecs()     ) ;
  sanitizePresetComboProperty(CONFIG::SAMPLERATE_ID    , CONFIG::AudioSampleRates()) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_BITRATE_ID , CONFIG::AudioBitRates()   ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_STYLE_ID    , CONFIG::TextStyles()      ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_POSITION_ID , CONFIG::TextPositions()   ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_SINK_ID   , CONFIG::OutputSinks()     ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_MUXER_ID  , CONFIG::OutputMuxers()    ) ;
  sanitizePresetComboProperty(CONFIG::FRAMERATE_ID     , CONFIG::FrameRates()      ) ;
  sanitizePresetComboProperty(CONFIG::VIDEO_BITRATE_ID , CONFIG::VideoBitRates()   ) ;
}

void AvCasterStore::verifyChildNode(ValueTree config_store , Identifier a_node_id)
{
DEBUG_TRACE_VERIFY_MISSING_NODE

  if (!config_store.getChildWithName(a_node_id).isValid())
    config_store.addChild(ValueTree(a_node_id) , -1 , nullptr) ;
}

void AvCasterStore::verifyPresetChildNode(Identifier a_node_id)
{
  verifyChildNode(this->config , a_node_id) ;
}

void AvCasterStore::verifyProperty(ValueTree config_store    , Identifier a_key ,
                                   var       a_default_value                    )
{
DEBUG_TRACE_VERIFY_MISSING_PROPERTY

  if (!config_store.hasProperty(a_key))
    config_store.setProperty(a_key , a_default_value , nullptr) ;
}

void AvCasterStore::verifyRootProperty(Identifier a_key , var a_default_value)
{
  verifyProperty(this->root , a_key , a_default_value) ;
}

void AvCasterStore::verifyPresetProperty(Identifier a_key , var a_default_value)
{
  verifyProperty(this->config , a_key , a_default_value) ;
}

void AvCasterStore::restoreStaticPresets()
{
  ValueTree preset_seeds = Seeds::PresetSeeds() ;

  for (int preset_idx = 0 ; preset_idx < CONFIG::N_STATIC_PRESETS ; ++preset_idx)
  {
    ValueTree  preset_seed     = preset_seeds.getChild(0) ;
    Identifier preset_id       = preset_seed.getType() ;
    ValueTree  existing_preset = this->presets.getChild(preset_idx) ;

    if (existing_preset.hasType(preset_id) && existing_preset.isValid()) continue ;

    removeConflictedNodes(this->presets , preset_id) ;
    preset_seeds .removeChild(preset_seed , nullptr) ;
    this->presets.addChild   (preset_seed , preset_idx , nullptr) ;
  }
}

bool AvCasterStore::hasDuplicatedNodes(ValueTree stored_config)
{
  StringArray root_node_ids      = CONFIG::RootPersistentNodes() ;
  StringArray preset_node_ids    = CONFIG::PresetPersistentNodes() ;
  StringArray network_node_ids   = CONFIG::NetworkPersistentNodes() ;
  int         n_duplicated_nodes = 0 ;
  bool        has_duplicates     = false ;

  n_duplicated_nodes = nDuplicatedNodes(stored_config , root_node_ids) ;
  has_duplicates     = has_duplicates || n_duplicated_nodes > root_node_ids.size() ;

  ValueTree presets_node = stored_config.getChildWithName(CONFIG::PRESETS_ID) ;
  for (int preset_n = 0 ; preset_n < presets_node.getNumChildren() ; ++preset_n)
  {
    ValueTree preset_node  = presets_node.getChild(preset_n) ;
    n_duplicated_nodes     = nDuplicatedNodes(preset_node , preset_node_ids) ;
    has_duplicates         = has_duplicates || n_duplicated_nodes > preset_node_ids .size() ;

    ValueTree network_node = preset_node.getChildWithName(CONFIG::NETWORK_ID) ;
    n_duplicated_nodes     = nDuplicatedNodes(network_node , network_node_ids) ;
    has_duplicates         = has_duplicates || n_duplicated_nodes > network_node_ids.size() ;
  }

  return has_duplicates ;
}

int AvCasterStore::nDuplicatedNodes(ValueTree parent_node , StringArray node_ids)
{
  int n_duplicated_nodes = 0 ;

  for (int node_n = 0 ; node_n < node_ids.size() ; ++node_n)
  {
    Identifier node_id = CONFIG::FilterId(node_ids[node_n] , APP::VALID_ID_CHARS) ;

    for (int child_n = 0 ; child_n < parent_node.getNumChildren() ; ++child_n)
      if (parent_node.getChild(child_n).hasType(node_id)) ++n_duplicated_nodes ;
  }

  return n_duplicated_nodes ;
}

void AvCasterStore::removeConflictedNodes(ValueTree parent_node , Identifier node_id)
{
  ValueTree a_node ;
  while ((a_node = parent_node.getChildWithName(node_id)).isValid())
    parent_node.removeChild(a_node , nullptr) ;
}

void AvCasterStore::verifyNetworkProperty(Identifier a_key , var a_default_value)
{
  ValueTree network_store = this->config.getChildWithName(CONFIG::NETWORK_ID) ;

  verifyProperty(network_store , a_key , a_default_value) ;
}

void AvCasterStore::filterRogueKeys(ValueTree parent_node , StringArray persistent_keys)
{
  for (int key_n = 0 ; key_n < parent_node.getNumProperties() ; ++key_n)
  {
    String property_id = STRING(parent_node.getPropertyName(key_n)) ;

DEBUG_TRACE_FILTER_ROGUE_KEY

    if (!persistent_keys.contains(property_id))
      parent_node.removeProperty( property_id , nullptr) ;
  }
}

void AvCasterStore::filterRogueNodes(ValueTree parent_node , StringArray persistent_node_ids)
{
  for (int child_n = 0 ; child_n <    parent_node.getNumChildren() ; ++child_n)
  {
    String node_id = STRING(parent_node.getChild(child_n).getType()) ;

DEBUG_TRACE_FILTER_ROGUE_NODE

    if (!persistent_node_ids.contains(node_id))
      parent_node.removeChild(child_n , nullptr) ;
  }
}

void AvCasterStore::sanitizeIntProperty(ValueTree config_store , Identifier a_key ,
                                        int       min_value    , int max_value    )
{
  int a_value = int(config_store[a_key]) ;

  if (a_value < min_value || a_value > max_value)
    config_store.removeProperty(a_key , nullptr) ;

DEBUG_TRACE_SANITIZE_INT_PROPERTY
}

void AvCasterStore::sanitizeRootComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->root , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::sanitizePresetComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->config , a_key , -1 , options.size() - 1) ;
}

void AvCasterStore::restoreTransients()
{
  if (AvCaster::IsInitialized) return ; // NOTE: should be called only once on startup

  setValue(this->root , CONFIG::IS_PENDING_ID , CONFIG::DEFAULT_IS_PENDING) ;
  for (int preset_n = 0 ; preset_n < this->presets.getNumChildren() ; ++preset_n)
    restorePresetTransients(this->presets.getChild(preset_n)) ;
  restorePresetTransients(this->config) ;
}

void AvCasterStore::restorePresetTransients(ValueTree a_preset_store)
{
  ValueTree network_store = a_preset_store.getChildWithName(CONFIG::NETWORK_ID ) ;

  // restore or reset properties
  setValue(a_preset_store , CONFIG::OUTPUT_ID  , CONFIG::DEFAULT_IS_OUTPUT_ACTIVE) ;
  setValue(network_store  , CONFIG::HOST_ID    , CONFIG::DEFAULT_HOST            ) ;
  setValue(network_store  , CONFIG::RETRIES_ID , CONFIG::DEFAULT_N_RETRIES       ) ;

  // restore or reset child nodes
  this->chatters.removeAllChildren(nullptr) ;
}


/* persistence */

ValueTree AvCasterStore::loadConfig()
{
  // load persistent storage
  this->storageDir           = APP::AppdataDir().getChildFile(CONFIG::STORAGE_DIRNAME ) ;
  this->storageFile          = this->storageDir .getChildFile(CONFIG::STORAGE_FILENAME) ;
  FileInputStream* storage   = new FileInputStream(this->storageFile) ;
  ValueTree        root_node = (storage->openedOk()) ? ValueTree::readFromStream(*storage) :
                                                       ValueTree()                         ;
  delete storage ;

  return root_node ;
}

void AvCasterStore::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  if (!this->root.isValid()) return ;

  // prepare storage directory
  this->storageDir .createDirectory() ;
  this->storageFile.deleteFile() ;

  ValueTree root_clone    = this->root   .createCopy() ;
  ValueTree presets_clone = this->presets.createCopy() ;

  // filter transient data and append presets and networks to persistent storage
  root_clone.removeProperty(CONFIG::IS_PENDING_ID , nullptr) ;
  root_clone.addChild      (presets_clone , -1    , nullptr) ;
  for (int preset_n = 0 ; preset_n < presets_clone.getNumChildren() ; ++preset_n)
  {
    ValueTree preset_clone  = presets_clone.getChild(preset_n) ;
    ValueTree network_clone = preset_clone .getChildWithName(CONFIG::NETWORK_ID ) ;

    preset_clone .removeProperty(CONFIG::OUTPUT_ID  , nullptr) ;
    network_clone.removeProperty(CONFIG::HOST_ID    , nullptr) ;
    network_clone.removeProperty(CONFIG::RETRIES_ID , nullptr) ;
  }

DEBUG_TRACE_DUMP_CONFIG    (root_clone , "root_clone")
DEBUG_TRACE_DUMP_CONFIG_XML(root_clone , "root_clone")

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->storageFile) ;
  if (!config_stream->failedToOpen()) root_clone.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;
}

void AvCasterStore::loadPreset()
{
  int       preset_idx    = int(this->root[CONFIG::PRESET_ID]) ;
  ValueTree preset_store  = this->presets.getChild(preset_idx) ;
  ValueTree network_store = preset_store.getChildWithName(CONFIG::NETWORK_ID) ;
  if (preset_idx == CONFIG::INVALID_IDX) return ; // renaming

DEBUG_TRACE_LOAD_PRESET

  listen(false) ;
  this->config  .copyPropertiesFrom(preset_store  , nullptr) ;
  this->network .copyPropertiesFrom(network_store , nullptr) ;
  this->chatters.removeAllChildren(nullptr) ;
  listen(true) ;
}

void AvCasterStore::storePreset(String preset_name)
{
  if (preset_name.isEmpty()) return ;

  Identifier preset_id     = CONFIG::FilterId(preset_name , APP::VALID_ID_CHARS) ;
  ValueTree  preset_store  = this->presets.getOrCreateChildWithName(preset_id          , nullptr) ;
  ValueTree  network_store = preset_store .getOrCreateChildWithName(CONFIG::NETWORK_ID , nullptr) ;
  int        preset_idx    = this->presets.indexOf(preset_store) ;

DEBUG_TRACE_STORE_PRESET
DEBUG_TRACE_DUMP_CONFIG_XML(this->config , STRING(preset_id))

#ifdef FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
  int        fullscreen_w = int(this->config[CONFIG::SCREENCAP_W_ID]) ;
  int        fullscreen_h = int(this->config[CONFIG::SCREENCAP_H_ID]) ;
  int        output_w     = int(this->config[CONFIG::OUTPUT_W_ID   ]) ;
  int        output_h     = int(this->config[CONFIG::OUTPUT_H_ID   ]) ;
  Point<int> resolution   = AvCaster::GetCameraResolution() ;
  int        camera_w     = resolution.getX() ;
  int        camera_h     = resolution.getY() ;
  var        fit_output_w = var(jmax(fullscreen_w , camera_w , output_w)) ;
  var        fit_output_h = var(jmax(fullscreen_h , camera_h , output_h)) ;

  setValue(this->config , CONFIG::OUTPUT_W_ID , fit_output_w) ;
  setValue(this->config , CONFIG::OUTPUT_H_ID , fit_output_h) ;
#endif // FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT

  setValue(this->config , CONFIG::PRESET_NAME_ID , preset_name) ;
  preset_store .copyPropertiesFrom(this->config  , nullptr) ;
  network_store.copyPropertiesFrom(this->network , nullptr) ;
  setValue(this->root   , CONFIG::PRESET_ID      , preset_idx ) ;
}

void AvCasterStore::renamePreset(String preset_name)
{
  Identifier preset_id      = CONFIG::FilterId(preset_name , APP::VALID_ID_CHARS) ;
  int        preset_idx     = int(this->root[CONFIG::PRESET_ID]) ;
  ValueTree  conflict_store = this->presets.getChildWithName(preset_id) ;

  if (conflict_store.isValid()) return ;

DEBUG_TRACE_RENAME_PRESET

  // destroy and re-create
  this->presets.removeChild(preset_idx , nullptr) ;
  setValue(this->root , CONFIG::PRESET_ID , CONFIG::INVALID_IDX) ; // force reload
  storePreset(preset_name) ;
}

void AvCasterStore::deletePreset()
{
  int preset_idx = int(this->root[CONFIG::PRESET_ID]) ;

  if (this->presets.getNumChildren() <= 1) return ;

DEBUG_TRACE_DELETE_PRESET

  this->presets.removeChild(preset_idx , nullptr) ;
  setValue(this->root , CONFIG::PRESET_ID , CONFIG::DEFAULT_PRESET_IDX) ;
  AvCaster::RefreshGui() ;
}

void AvCasterStore::resetPreset()
{
  if (!AvCaster::IsStaticPreset()) return ;

  int       preset_idx    = int(this->root[CONFIG::PRESET_ID]) ;
  ValueTree preset_store  = this->presets.getChild(preset_idx) ;
  ValueTree network_store = preset_store .getChildWithName(CONFIG::NETWORK_ID) ;
  ValueTree preset_seed   = Seeds::PresetSeeds().getChild(preset_idx) ;
  ValueTree network_seed  = preset_seed         .getChildWithName(CONFIG::NETWORK_ID) ;

  // transfer default preset values
  preset_store .copyPropertiesFrom(preset_seed  , nullptr) ;
  network_store.copyPropertiesFrom(network_seed , nullptr) ;
  restorePresetTransients(preset_store) ;

  loadPreset() ; AvCaster::RefreshGui() ;
}


/* runtime params */

/*
void AvCasterStore::detectDisplayDimensions()
{
// TODO: the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                       (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea)
                       gStreamer handles resolution changes gracefully so this  may not be strictly necessary
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;

  this->desktopW      = area.getWidth() ;
  this->desktopH      = area.getHeight() ;

  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;
}
*/

void AvCasterStore::detectCaptureDevices()
{
#if JUCE_LINUX
  // TODO: query device for framerates and resolutions
  int         camera_rate = CONFIG::DEFAULT_CAMERA_RATE ;
  String      resolutions = CONFIG::CameraResolutions().joinIntoString(newLine) ;
  Array<File> device_info_dirs ;

  this->cameras.removeAllChildren(nullptr) ;
  if (APP::CamerasDevDir().containsSubDirectories())
    APP::CamerasDevDir().findChildFiles(device_info_dirs , File::findDirectories , false) ;

  File* device_info_dir = device_info_dirs.begin() ;
  while (device_info_dir != device_info_dirs.end())
  {
    String    device_id     = device_info_dir->getFileName() ;
    String    friendly_name = device_info_dir->getChildFile("name").loadFileAsString().trim() ;
    String    device_path   = "/dev/" + device_id ;
    ValueTree device_info   = ValueTree(Identifier(device_id)) ;

    device_info.setProperty(CONFIG::CAMERA_PATH_ID        , var(device_path  ) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_NAME_ID        , var(friendly_name) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_RATE_ID        , var(camera_rate  ) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_RESOLUTIONS_ID , var(resolutions  ) , nullptr) ;
    this->cameras.addChild(device_info , -1 , nullptr) ;
    ++device_info_dir ;
  }
/* mac and windows only (issue #6 issue #8)
#else // JUCE_LINUX
#  if JUCE_WINDOWS || JUCE_MAC
// Returns a list of the available cameras on this machine.
  StringArray video_devs = juce::CameraDevice::getAvailableDevices() ;
LOG(video_devs.joinIntoString("\n")) ;
  while (video_devs.size())
  {
LOG("video_devs=" + video_devs[0]) ;

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
#  endif // JUCE_WINDOWS || JUCE_MAC
*/
#endif // JUCE_LINUX

DEBUG_TRACE_DETECT_CAPTURE_DEVICES
}


/* event handlers */

void AvCasterStore::listen(bool should_listen)
{
  if (!AvCaster::IsInitialized) return ;

DEBUG_TRACE_LISTEN

  if (should_listen) { this->root.addListener   (this) ; this->config.addListener   (this) ; }
  else               { this->root.removeListener(this) ; this->config.removeListener(this) ; }
}

void AvCasterStore::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  if (a_key == CONFIG::PRESET_ID) loadPreset() ;

  AvCaster::HandleConfigChanged(a_key) ;
}


/* getters/setters */

bool AvCasterStore::isMediaToggleKey(const Identifier& a_key)
{
  return CONFIG::MediaToggleKeys().contains(STRING(a_key)) ;
}

bool AvCasterStore::isPresetConfigKey(const Identifier& a_key)
{
  return CONFIG::PresetConfigKeys().contains(STRING(a_key)) ;
}

void AvCasterStore::deactivateControl(const Identifier& a_key)
{
  if (!isMediaToggleKey(a_key)) return ;

  listen(false) ;

DEBUG_TRACE_DEACTIVATE_CONTROL

  setValue(this->config , a_key , var(false)) ;

  listen(true) ;
}

bool AvCasterStore::isKnownProperty(ValueTree a_node  , const Identifier& a_key)
{
  ValueTree a_parent_node = a_node.getParent() ;

  // TODO: cameras and audio nyi
  return (a_node        == this->root    ) ? CONFIG::RootKeys()   .contains(a_key) :
         (a_node        == this->config  ) ? CONFIG::PresetKeys() .contains(a_key) :
         (a_node        == this->network ) ? CONFIG::NetworkKeys().contains(a_key) :
         (a_parent_node == this->presets ) ? CONFIG::PresetKeys() .contains(a_key) :
         (a_parent_node == this->chatters) ? CONFIG::ChatterKeys().contains(a_key) :
         (a_parent_node == this->cameras ) ? CONFIG::CameraKeys() .contains(a_key) :
         (a_parent_node == this->audios  ) ? CONFIG::AudioKeys()  .contains(a_key) :
                                             false                                ;
}

void AvCasterStore::setProperty(ValueTree a_node  , const Identifier& a_key ,
                                const var a_value                           )
{
  if (!a_node.isValid() || !isKnownProperty(a_node , a_key)) return ;

DEBUG_TRACE_SET_PROPERTY // call this only from AvCasterStore->setValue() and AvCasterStore->setValueViaGui() for tracing correctness

  if (!AvCaster::IsInitialized || !AvCaster::DisabledFeatures.contains(a_key))
    a_node.setProperty(a_key , a_value , nullptr) ;
}

void AvCasterStore::setValue(ValueTree a_node  , const Identifier& a_key ,
                             const var a_value                           )
{
DEBUG_TRACE_STORE_SET_VALUE // call this only from AvCasterStore methods for tracing correctness

  setProperty(a_node , a_key , a_value) ;
}

void AvCasterStore::setValueViaGui(ValueTree a_node  , const Identifier& a_key ,
                                   const var a_value                           )
{
DEBUG_TRACE_GUI_SET_VALUE // call this only from AvCaster methods for tracing correctness

  setProperty(a_node , a_key , a_value) ;
}

void AvCasterStore::updateChatters(StringArray active_nicks)
{
  StringArray stored_nicks   = getChatNicks() ;
#ifdef PREFIX_CHAT_NICKS
  String      network        = String(this->network[NETWORK_ID]) ;
  String      channel        = String(this->network[CHANNEL_ID]) ;
  bool        is_lctv        = IRC::BITLBEE_HOSTS.contains(network) &&
                               channel == IRC::BITLBEE_XMPP_CHANNEL  ;
  String      prefix         = (is_lctv) ? GUI::LCTV_USER_PREFIX : GUI::IRC_USER_PREFIX ;
  String      joined_nicks   = active_nicks.joinIntoString("] " + prefix + "[") ;
  String      prefixed_nicks = prefix + "["  + joined_nicks + "]" ;
  active_nicks               = StringArray::fromTokens(prefixed_nicks , false) ;
#endif // PREFIX_CHAT_NICKS

DEBUG_TRACE_UPDATE_CHAT_NICKS_IN

  // add joining chatters
  for (int chatter_idx = 0 ; chatter_idx < active_nicks.size() ; ++chatter_idx)
  {
    String     active_nick   = active_nicks[chatter_idx] ;
    Identifier chatter_id    = CONFIG::FilterId(active_nick , APP::VALID_NICK_CHARS) ;
    ValueTree  chatter_store = this->chatters.getChildWithName(chatter_id) ;

    if (!chatter_store.isValid())
    {
      stored_nicks.add(active_nick) ; stored_nicks.sort(true) ;

DEBUG_TRACE_ADD_CHAT_NICK

      chatter_store = ValueTree(chatter_id) ;
      chatter_store.setProperty(CONFIG::NICK_ID , var(active_nick) , nullptr) ;
      this->chatters.addChild(chatter_store , stored_nicks.indexOf(active_nick) , nullptr) ;
    }
  }

  // remove parting chatters
  for (int chatter_idx = 0 ; chatter_idx < stored_nicks.size() ; ++chatter_idx)
  {
    String     stored_nick   = stored_nicks[chatter_idx] ;
    Identifier chatter_id    = CONFIG::FilterId(stored_nick , APP::VALID_NICK_CHARS) ;
    ValueTree  chatter_store = this->chatters.getChildWithName(chatter_id) ;

DEBUG_TRACE_REMOVE_CHAT_NICK

    if (!active_nicks.contains(stored_nick))
      this->chatters.removeChild(chatter_store , nullptr) ;
  }

DEBUG_TRACE_UPDATE_CHAT_NICKS_OUT
}

StringArray AvCasterStore::presetsNames()
{
  return PropertyValues(this->presets , CONFIG::PRESET_NAME_ID) ;
}

StringArray AvCasterStore::cameraNames()
{
  return PropertyValues(this->cameras , CONFIG::CAMERA_NAME_ID) ;
}

StringArray AvCasterStore::audioNames()
{
  return PropertyValues(this->audios  , Identifier("TODO")) ;
}

ValueTree AvCasterStore::getCameraStore()
{
  int camera_idx = int(this->config[CONFIG::CAMERA_DEVICE_ID]) ;

  return this->cameras.getChild(camera_idx) ;
}

StringArray AvCasterStore::getCameraResolutions()
{
  ValueTree camera_store = getCameraStore() ;
  String    resolutions  = STRING(camera_store[CONFIG::CAMERA_RESOLUTIONS_ID]) ;

  return (camera_store.isValid()) ? StringArray::fromLines(resolutions) :
                                    CONFIG::CameraResolutions()         ;
}

StringArray AvCasterStore::getChatNicks()
{
  return AvCasterStore::PropertyValues(this->chatters , CONFIG::NICK_ID) ;
}
