/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "AvCasterStore.h"
#include "AvCaster.h"
#include "PresetSeed.h"
#include "Trace/TraceAvCasterStore.h"


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
  // load persistent storage
  this->configDir                = APP::APPDATA_DIR.getChildFile(CONFIG::STORAGE_DIRNAME ) ;
  this->configFile               = this->configDir .getChildFile(CONFIG::STORAGE_FILENAME) ;
  FileInputStream* config_stream = new FileInputStream(this->configFile) ;
  ValueTree        stored_config = ValueTree::invalid ;
  if (config_stream->openedOk()) stored_config = ValueTree::readFromStream(*config_stream) ;
  delete config_stream ;

  // create shared config ValueTree from persistent storage or defaults
  this->root     = verifyStoredConfig(stored_config) ;
  this->presets  = getOrCreatePresets() ;
  this->networks = getOrCreateNetworks() ;
  this->config   = ValueTree(CONFIG::VOLATILE_CONFIG_ID) ;
  this->cameras  = ValueTree(CONFIG::CAMERA_DEVICES_ID ) ;
  this->audios   = ValueTree(CONFIG::AUDIO_DEVICES_ID  ) ;

  // remove presets and networks from runtime store (to ignore events)
  this->root.removeChild(presets  , nullptr) ;
  this->root.removeChild(networks , nullptr) ;

DEBUG_TRACE_DUMP_CONFIG("AvCasterStore::AvCasterStore()")

  // sanitize config
  verifyRoot() ;    sanitizeRoot() ;    verifyRoot() ;
  verifyPresets() ; sanitizePresets() ; verifyPresets() ;
  verifyNetworks() ;
  loadPreset() ; storeConfig() ;

  // detect hardware
  detectCaptureDevices() ; // detectDisplayDimensions() ; // TODO: (issue #2 issue #4)
}


// persistence and validations

ValueTree AvCasterStore::verifyStoredConfig(ValueTree stored_config)
{
  bool      is_valid     = stored_config.isValid() && stored_config.hasType(CONFIG::STORAGE_ID) ;
  ValueTree config_store = (is_valid) ? stored_config : CONFIG::DefaultStore() ;

  // verify config version
  double stored_version    = double(config_store[CONFIG::CONFIG_VERSION_ID]) ;
  bool   do_versions_match = stored_version ==   CONFIG::CONFIG_VERSION ;
  if (!do_versions_match)
  {
    // TODO: convert (if ever necessary)
    File parent_dir  = this->configFile.getParentDirectory() ;
    File backup_file = parent_dir.getNonexistentChildFile(CONFIG::STORAGE_FILENAME , ".bak" , false) ;
    this->configFile.copyFileTo(backup_file) ;

    config_store.removeProperty(CONFIG::CONFIG_VERSION_ID , nullptr) ;
  }

DEBUG_TRACE_VERIFY_CONFIG

  return config_store ;
}

ValueTree AvCasterStore::getOrCreatePresets()
{
DEBUG_TRACE_VERIFY_PRESETS_NODE

  ValueTree   presets   = this->root.getOrCreateChildWithName(CONFIG::PRESETS_ID , nullptr) ;
  PresetSeed* file_seed = new FilePresetSeed() ; ValueTree file_preset = file_seed->preset ;
  PresetSeed* rtmp_seed = new RtmpPresetSeed() ; ValueTree rtmp_preset = rtmp_seed->preset ;
  PresetSeed* lctv_seed = new LctvPresetSeed() ; ValueTree lctv_preset = lctv_seed->preset ;

  if (!presets.getChild(CONFIG::FILE_PRESET_IDX).hasType(file_preset.getType()))
    presets.addChild(file_preset , CONFIG::FILE_PRESET_IDX , nullptr) ;
  if (!presets.getChild(CONFIG::RTMP_PRESET_IDX).hasType(rtmp_preset.getType()))
    presets.addChild(rtmp_preset , CONFIG::RTMP_PRESET_IDX , nullptr) ;
  if (!presets.getChild(CONFIG::LCTV_PRESET_IDX).hasType(lctv_preset.getType()))
    presets.addChild(lctv_preset , CONFIG::LCTV_PRESET_IDX , nullptr) ;
  delete file_seed ; delete rtmp_seed ; delete lctv_seed ;

  return presets ;
}

ValueTree AvCasterStore::getOrCreateNetworks()
{
DEBUG_TRACE_VERIFY_NETWORKS_NODE

  ValueTree networks = this->root.getOrCreateChildWithName(CONFIG::NETWORKS_ID , nullptr) ;

  for (int network_n = 0 ; network_n < networks.getNumChildren() ; ++network_n)
    networks.getChild(network_n).addChild(ValueTree(CONFIG::CHATTERS_ID) , -1 , nullptr) ;

  return networks ;
}

void AvCasterStore::verifyRoot()
{
DEBUG_TRACE_VERIFY_CONFIG_ROOT

  if (!this->root.isValid() || this->root.getType() != CONFIG::STORAGE_ID) return ;

  // transfer missing properties
  verifyRootProperty(CONFIG::CONFIG_VERSION_ID , var(CONFIG::CONFIG_VERSION    )) ;
  verifyRootProperty(CONFIG::IS_PENDING_ID     , var(CONFIG::DEFAULT_IS_PENDING)) ;
  verifyRootProperty(CONFIG::PRESET_ID         , var(CONFIG::DEFAULT_PRESET_IDX)) ;
}

void AvCasterStore::verifyPresets()
{
DEBUG_TRACE_VERIFY_CONFIG_PRESETS

  if (!this->presets.isValid() || this->presets.getType() != CONFIG::PRESETS_ID) return ;

  // verify user preset nodes
  int n_presets = this->presets.getNumChildren() ;
  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    ValueTree a_preset = this->presets.getChild(preset_n) ;

    this->config.copyPropertiesFrom(a_preset , nullptr) ; verifyPreset() ;
    a_preset.copyPropertiesFrom(this->config , nullptr) ;

    // restore non-persistent properties
    setValue(a_preset , CONFIG::OUTPUT_ID , false) ;
  }
}

void AvCasterStore::verifyPreset()
{
DEBUG_TRACE_VERIFY_CONFIG_PRESET

  // transfer missing properties
  verifyPresetProperty(CONFIG::PRESET_NAME_ID   , var(CONFIG::DEFAULT_PRESET_NAME        )) ;
  verifyPresetProperty(CONFIG::SCREENCAP_ID     , var(CONFIG::DEFAULT_IS_SCREENCAP_ACTIVE)) ;
  verifyPresetProperty(CONFIG::CAMERA_ID        , var(CONFIG::DEFAULT_IS_CAMERA_ACTIVE   )) ;
  verifyPresetProperty(CONFIG::TEXT_ID          , var(CONFIG::DEFAULT_IS_TEXT_ACTIVE     )) ;
  verifyPresetProperty(CONFIG::IMAGE_ID         , var(CONFIG::DEFAULT_IS_IMAGE_ACTIVE    )) ;
  verifyPresetProperty(CONFIG::PREVIEW_ID       , var(CONFIG::DEFAULT_IS_PREVIEW_ACTIVE  )) ;
  verifyPresetProperty(CONFIG::AUDIO_ID         , var(CONFIG::DEFAULT_IS_AUDIO_ACTIVE    )) ;
  verifyPresetProperty(CONFIG::DISPLAY_N_ID     , var(CONFIG::DEFAULT_DISPLAY_N          )) ;
  verifyPresetProperty(CONFIG::SCREEN_N_ID      , var(CONFIG::DEFAULT_SCREEN_N           )) ;
  verifyPresetProperty(CONFIG::SCREENCAP_W_ID   , var(CONFIG::DEFAULT_SCREENCAP_W        )) ;
  verifyPresetProperty(CONFIG::SCREENCAP_H_ID   , var(CONFIG::DEFAULT_SCREENCAP_H        )) ;
  verifyPresetProperty(CONFIG::OFFSET_X_ID      , var(CONFIG::DEFAULT_OFFSET_X           )) ;
  verifyPresetProperty(CONFIG::OFFSET_Y_ID      , var(CONFIG::DEFAULT_OFFSET_Y           )) ;
  verifyPresetProperty(CONFIG::CAMERA_DEVICE_ID , var(CONFIG::DEFAULT_CAMERA_DEVICE_IDX  )) ;
  verifyPresetProperty(CONFIG::CAMERA_RES_ID    , var(CONFIG::DEFAULT_CAMERA_RES_IDX     )) ;
  verifyPresetProperty(CONFIG::AUDIO_API_ID     , var(CONFIG::DEFAULT_AUDIO_API_IDX      )) ;
  verifyPresetProperty(CONFIG::AUDIO_DEVICE_ID  , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX   )) ;
  verifyPresetProperty(CONFIG::AUDIO_CODEC_ID   , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX    )) ;
  verifyPresetProperty(CONFIG::N_CHANNELS_ID    , var(CONFIG::DEFAULT_N_CHANNELS         )) ;
  verifyPresetProperty(CONFIG::SAMPLERATE_ID    , var(CONFIG::DEFAULT_SAMPLERATE_IDX     )) ;
  verifyPresetProperty(CONFIG::AUDIO_BITRATE_ID , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX  )) ;
  verifyPresetProperty(CONFIG::MOTD_TEXT_ID     , var(CONFIG::DEFAULT_MOTD_TEXT          )) ;
  verifyPresetProperty(CONFIG::TEXT_STYLE_ID    , var(CONFIG::DEFAULT_TEXT_STYLE_IDX     )) ;
  verifyPresetProperty(CONFIG::TEXT_POSITION_ID , var(CONFIG::DEFAULT_TEXT_POSITION_IDX  )) ;
  verifyPresetProperty(CONFIG::IMAGE_LOC_ID     , var(CONFIG::DEFAULT_IMAGE_LOCATION     )) ;
  verifyPresetProperty(CONFIG::OUTPUT_SINK_ID   , var(CONFIG::DEFAULT_OUTPUT_SINK_IDX    )) ;
  verifyPresetProperty(CONFIG::OUTPUT_MUXER_ID  , var(CONFIG::DEFAULT_OUTPUT_MUXER_IDX   )) ;
  verifyPresetProperty(CONFIG::OUTPUT_W_ID      , var(CONFIG::DEFAULT_OUTPUT_W           )) ;
  verifyPresetProperty(CONFIG::OUTPUT_H_ID      , var(CONFIG::DEFAULT_OUTPUT_H           )) ;
  verifyPresetProperty(CONFIG::FRAMERATE_ID     , var(CONFIG::DEFAULT_FRAMERATE_IDX      )) ;
  verifyPresetProperty(CONFIG::VIDEO_BITRATE_ID , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX  )) ;
  verifyPresetProperty(CONFIG::OUTPUT_DEST_ID   , var(CONFIG::DEFAULT_OUTPUT_DEST        )) ;
  verifyPresetProperty(CONFIG::NETWORK_IDX_ID   , var(CONFIG::DEFAULT_NETWORK_IDX        )) ;
  verifyPresetProperty(CONFIG::TIMESTAMPS_ID    , var(CONFIG::DEFAULT_SHOW_TIMESTAMPS    )) ;
  verifyPresetProperty(CONFIG::JOINPARTS_ID     , var(CONFIG::DEFAULT_SHOW_JOINPARTS     )) ;
}

void AvCasterStore::verifyNetworks()
{
DEBUG_TRACE_VERIFY_NETWORKS

  if (!this->networks.isValid() || this->networks.getType() != CONFIG::NETWORKS_ID) return ;

  // verify user preset nodes
  int n_networks = this->networks.getNumChildren() ;
  for (int network_n = 0 ; network_n < n_networks ; ++network_n)
    verifyNetwork(this->networks.getChild(network_n)) ;
}

void AvCasterStore::verifyNetwork(ValueTree a_network_node)
{
DEBUG_TRACE_VERIFY_NETWORK_IN

  if (!a_network_node.isValid()) return ;

  // transfer missing properties
  if (!a_network_node.hasProperty     (CONFIG::HOST_ID     )         ||
      !a_network_node.hasProperty     (CONFIG::PORT_ID     )         ||
      !a_network_node.hasProperty     (CONFIG::NICK_ID     )         ||
      !a_network_node.hasProperty     (CONFIG::PASS_ID     )         ||
      !a_network_node.hasProperty     (CONFIG::CHANNEL_ID  )         ||
      !a_network_node.hasProperty     (CONFIG::GREETING_ID )         ||
      !a_network_node.getChildWithName(CONFIG::CHATTERS_ID).isValid() )
    a_network_node.getParent().removeChild(a_network_node , nullptr) ;

DEBUG_TRACE_VERIFY_NETWORK_OUT
}

void AvCasterStore::sanitizeRoot()
{
  sanitizeRootComboProperty(CONFIG::PRESET_ID , presetsNames()) ;
}

void AvCasterStore::sanitizePresets()
{
  // sanitize user preset nodes
  int n_presets = this->presets.getNumChildren() ;
  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    ValueTree a_preset = this->presets.getChild(preset_n) ;

    this->config.copyPropertiesFrom(a_preset , nullptr) ; sanitizePreset() ;
    a_preset.copyPropertiesFrom(this->config , nullptr) ;
  }
}

void AvCasterStore::sanitizePreset()
{
  sanitizePresetComboProperty(CONFIG::CAMERA_RES_ID    , getCameraResolutions()   ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEVICE_ID , cameraNames()            ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_API_ID     , CONFIG::AUDIO_APIS       ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_DEVICE_ID  , audioNames()             ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_CODEC_ID   , CONFIG::AUDIO_CODECS     ) ;
  sanitizePresetComboProperty(CONFIG::SAMPLERATE_ID    , CONFIG::AUDIO_SAMPLERATES) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_BITRATE_ID , CONFIG::AUDIO_BITRATES   ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_STYLE_ID    , CONFIG::TEXT_STYLES      ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_POSITION_ID , CONFIG::TEXT_POSITIONS   ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_SINK_ID   , CONFIG::OUTPUT_SINKS     ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_MUXER_ID  , CONFIG::OUTPUT_MUXERS    ) ;
  sanitizePresetComboProperty(CONFIG::FRAMERATE_ID     , CONFIG::FRAMERATES       ) ;
  sanitizePresetComboProperty(CONFIG::VIDEO_BITRATE_ID , CONFIG::VIDEO_BITRATES   ) ;
  sanitizePresetComboProperty(CONFIG::NETWORK_IDX_ID   , networkNames()           ) ;
}

void AvCasterStore::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  if (!this->root.isValid()) return ;

  // prepare storage directory
  this->configDir .createDirectory() ;
  this->configFile.deleteFile() ;

  ValueTree root_clone     = this->root   .createCopy() ;
  ValueTree presets_clone  = this->presets.createCopy() ;
  ValueTree networks_clone = this->networks.createCopy() ;

  // filter transient data and append presets and networks to persistent storage
  root_clone.removeProperty(CONFIG::IS_PENDING_ID , nullptr) ;
  root_clone.addChild(presets_clone  , -1 , nullptr) ;
  root_clone.addChild(networks_clone , -1 , nullptr) ;
  for (int preset_n = 0 ; preset_n < presets_clone.getNumChildren() ; ++preset_n)
  {
    ValueTree preset_store = presets_clone.getChild(preset_n) ;
    preset_store.removeProperty(CONFIG::OUTPUT_ID , nullptr) ;
  }
  for (int network_n = 0 ; network_n < networks_clone.getNumChildren() ; ++network_n)
  {
    ValueTree network_store  = networks_clone.getChild(network_n) ;
    ValueTree chatters_store = network_store.getChildWithName(CONFIG::CHATTERS_ID) ;
    network_store.removeProperty(CONFIG::HOST_ID    , nullptr) ;
    network_store.removeProperty(CONFIG::RETRIES_ID , nullptr) ;
    network_store.removeChild   (chatters_store     , nullptr) ;
  }

DEBUG_TRACE_DUMP_CONFIG("AvCasterStore->StoreConfig()")

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) root_clone.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;
}


/* runtime params */

void AvCasterStore::verifyProperty(ValueTree config_store    , Identifier a_key ,
                                   var       a_default_value                    )
{
DEBUG_TRACE_VERIFY_CONFIG_PROPERTY

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

void AvCasterStore::sanitizeIntProperty(ValueTree config_store , Identifier a_key ,
                                        int       min_value    , int max_value    )
{
  int a_value = int(config_store[a_key]) ;

  if (a_value < min_value || a_value > max_value)
    config_store.removeProperty(a_key , nullptr) ;

DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY
}

void AvCasterStore::sanitizeRootComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->root , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::sanitizePresetComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->config , a_key , -1 , options.size() - 1) ;
}

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
  String      resolutions = CONFIG::CAMERA_RESOLUTIONS.joinIntoString(newLine) ;
  Array<File> device_info_dirs ;

  this->cameras.removeAllChildren(nullptr) ;
  if (APP::CAMERAS_DEV_DIR.containsSubDirectories())
    APP::CAMERAS_DEV_DIR.findChildFiles(device_info_dirs , File::findDirectories , false) ;

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
  // NOTE: currently this method is needed only for AvCasterStore->deactivateControl()
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

bool AvCasterStore::isMediaKey(const Identifier& a_key)
{
//   return CONFIG::MEDIA_KEYS.contains(a_key) ;
  return a_key == CONFIG::SCREENCAP_ID || a_key == CONFIG::CAMERA_ID ||
         a_key == CONFIG::TEXT_ID      || a_key == CONFIG::IMAGE_ID  ||
         a_key == CONFIG::PREVIEW_ID   || a_key == CONFIG::AUDIO_ID  ||
         a_key == CONFIG::OUTPUT_ID                                   ;
}

bool AvCasterStore::isReconfigureKey(const Identifier& a_key)
{
//   return CONFIG::RECONFIGURE_KEYS.contains(a_key) ;
  return a_key == CONFIG::IS_PENDING_ID || a_key == CONFIG::PRESET_ID ;
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

StringArray AvCasterStore::networkNames()
{
  return PropertyValues(this->networks , CONFIG::NETWORK_ID) ;
}

ValueTree AvCasterStore::getCameraStore()
{
  int camera_idx = int(this->config[CONFIG::CAMERA_DEVICE_ID]) ;

  return this->cameras.getChild(camera_idx) ;
}

ValueTree AvCasterStore::getNetworkStore(Identifier network_id)
{
  return this->networks.getChildWithName(network_id) ;
}

StringArray AvCasterStore::getCameraResolutions()
{
  ValueTree camera_store = getCameraStore() ;
  String    resolutions  = STRING(camera_store[CONFIG::CAMERA_RESOLUTIONS_ID]) ;

  return (camera_store.isValid()) ? StringArray::fromLines(resolutions) :
                                    CONFIG::CAMERA_RESOLUTIONS          ;
}

void AvCasterStore::deactivateControl(const Identifier& a_key)
{
DEBUG_TRACE_DEACTIVATE_CONTROL

  listen(false) ; setVolatileValue(a_key , var(false)) ; listen(true) ;
}

void AvCasterStore::setRootValue(const Identifier& a_key , var a_value)
{
  setValue(this->root , a_key , a_value) ;
}

void AvCasterStore::setVolatileValue(const Identifier& a_key , var a_value)
{
  setValue(this->config , a_key , a_value) ;
}

void AvCasterStore::setValue(ValueTree storage_node , const Identifier& a_key , var a_value)
{
DEBUG_TRACE_SET_CONFIG

  if (storage_node.isValid()) storage_node.setProperty(a_key , a_value , nullptr) ;
}

void AvCasterStore::storePreset(String preset_name)
{
  if (preset_name.isEmpty()) return ;

  Identifier preset_id    = CONFIG::FilterId(preset_name , APP::VALID_ID_CHARS) ;
  ValueTree  preset_store = this->presets.getOrCreateChildWithName(preset_id , nullptr) ;
  int        preset_idx   = this->presets.indexOf(preset_store) ;

DEBUG_TRACE_STORE_PRESET

#ifdef FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
  int         fullscreen_w    = int(this->config[CONFIG::SCREENCAP_W_ID]) ;
  int         fullscreen_h    = int(this->config[CONFIG::SCREENCAP_H_ID]) ;
  int         output_w        = int(this->config[CONFIG::OUTPUT_W_ID   ]) ;
  int         output_h        = int(this->config[CONFIG::OUTPUT_H_ID   ]) ;
  String      resolution      = AvCaster::GetCameraResolution() ;
  StringArray res_tokens      = StringArray::fromTokens(resolution , "x" , "") ;
  int         camera_w        = res_tokens[0].getIntValue() ;
  int         camera_h        = res_tokens[1].getIntValue() ;
  var         fit_output_w    = var(jmax(fullscreen_w , camera_w , output_w)) ;
  var         fit_output_h    = var(jmax(fullscreen_h , camera_h , output_h)) ;
  bool        has_idx_changed = preset_idx != AvCaster::GetPresetIdx() ;

  setValue(this->config , CONFIG::OUTPUT_W_ID , fit_output_w) ;
  setValue(this->config , CONFIG::OUTPUT_H_ID , fit_output_h) ;
#endif // FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT

  setValue(this->config , CONFIG::PRESET_NAME_ID , preset_name) ;
  preset_store.copyPropertiesFrom(this->config , nullptr) ;
  setValue(this->root   , CONFIG::PRESET_ID      , preset_idx ) ;

//   storeNetwork() ;
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

  int         preset_idx = int(this->root[CONFIG::PRESET_ID]) ;
  PresetSeed* seed ;

  switch (preset_idx)
  {
    case CONFIG::FILE_PRESET_IDX: seed = new FilePresetSeed() ; break ;
    case CONFIG::RTMP_PRESET_IDX: seed = new RtmpPresetSeed() ; break ;
    case CONFIG::LCTV_PRESET_IDX: seed = new LctvPresetSeed() ; break ;
    default:                      return ;                      break ;
  }

  this->presets.removeChild(preset_idx , nullptr) ;
  this->presets.addChild(seed->preset , preset_idx , nullptr) ;
  delete seed ;

  AvCaster::RefreshGui() ;
}

void AvCasterStore::loadPreset()
{
  int preset_idx = int(this->root[CONFIG::PRESET_ID]) ;
  if (preset_idx == CONFIG::INVALID_IDX) return ; // renaming

  this->config.copyPropertiesFrom(this->presets.getChild(preset_idx) , nullptr) ;
}

void AvCasterStore::storeNetwork(String network         , String port    , String nick     ,
                                 String pass            , String channel , String greeting ,
                                 bool   show_join_parts                                    )
{
DEBUG_TRACE_STORE_NETWORK

  Identifier network_id    = CONFIG::FilterId(network , APP::VALID_URI_CHARS) ;
  ValueTree  network_store = this->networks.getOrCreateChildWithName(network_id , nullptr) ;
  int        network_idx   = this->networks.indexOf(network_store) ;

  network_store.setProperty(CONFIG::NETWORK_ID  , network  , nullptr) ;
  network_store.setProperty(CONFIG::PORT_ID     , port     , nullptr) ;
  network_store.setProperty(CONFIG::NICK_ID     , nick     , nullptr) ;
  network_store.setProperty(CONFIG::PASS_ID     , pass     , nullptr) ;
  network_store.setProperty(CONFIG::CHANNEL_ID  , channel  , nullptr) ;
  network_store.setProperty(CONFIG::GREETING_ID , greeting , nullptr) ;
  network_store.setProperty(CONFIG::RETRIES_ID  , 0        , nullptr) ;
  network_store.addChild(ValueTree(CONFIG::CHATTERS_ID) , -1 , nullptr) ;

/*
  setValue(this->config , CONFIG::PRESET_NAME_ID , preset_name) ;
  preset_store.copyPropertiesFrom(this->config , nullptr) ;
  setValue(this->root   , CONFIG::PRESET_ID      , preset_idx) ;
*/
}

void AvCasterStore::updateIrcHost(StringArray aliases , String actual_host)
{
  // update current host for IRC network e.g. irc.debian.org => charm.oftc.net
  for (int alias_n = 0 ; alias_n < aliases.size() ; ++alias_n)
  {
    Identifier network_id    = CONFIG::FilterId(aliases[alias_n] , APP::VALID_URI_CHARS) ;
    ValueTree  network_store = this->networks.getChildWithName(network_id) ;

DEBUG_TRACE_UPDATE_IRC_HOST

    if (network_store.isValid())
      network_store.setProperty(CONFIG::HOST_ID , actual_host , nullptr) ;
  }
}

void AvCasterStore::updateChatNicks(Identifier network_id , StringArray active_nicks)
{
  ValueTree   network_store  = this->networks.getChildWithName(network_id) ;
  ValueTree   chatters_store = network_store.getChildWithName(CONFIG::CHATTERS_ID) ;
  StringArray stored_nicks   = getChatNicks(chatters_store) ;
#ifdef PREFIX_CHAT_NICKS
  String      channel        = String(network_store[CHANNEL_ID]) ;
  bool        is_lctv        = (network == IRC::BITLBEE_HOST || network == IRC::LOCAL_HOST) &&
                               channel == IRC::BITLBEE_XMPP_CHANNEL                          ;
  String      prefix         = (is_lctv) ? GUI::LCTV_USER_PREFIX : GUI::IRC_USER_PREFIX ;
  String      joined_nicks   = active_nicks.joinIntoString("] " + prefix + "[") ;
  String      prefixed_nicks = prefix + "["  + joined_nicks + "]" ;
  active_nicks               = StringArray::fromTokens(prefixed_nicks , false) ;
#endif // PREFIX_CHAT_NICKS

DEBUG_TRACE_UPDATE_CHAT_NICKS

  // add joining chatters
  for (String* nick = active_nicks.begin() ; nick != active_nicks.end() ; ++nick)
  {
    Identifier user_id       = CONFIG::FilterId(*nick , APP::VALID_NICK_CHARS) ;
    ValueTree  chatter_store = chatters_store.getChildWithName(user_id) ;

    if (!chatter_store.isValid())
    {
      stored_nicks.add(*nick) ; stored_nicks.sort(true) ;

DEBUG_TRACE_ADD_CHAT_NICK

      chatter_store = ValueTree(user_id) ;
      chatter_store.setProperty(CONFIG::NICK_ID , var(*nick) , nullptr) ;
      chatters_store.addChild(chatter_store , stored_nicks.indexOf(*nick) , nullptr) ;
    }
  }

  // remove parting chatters
  for (int chatter_n = 0 ; chatter_n < chatters_store.getNumChildren() ; ++chatter_n)
  {
    ValueTree chatter_store = chatters_store.getChild(chatter_n) ;
    String    stored_nick   = STRING(chatter_store[CONFIG::NICK_ID]) ;

DEBUG_TRACE_REMOVE_CHAT_NICK

    if (!active_nicks.contains(stored_nick))
      chatters_store.removeChild(chatter_store , nullptr) ;
  }

DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , active_nicks                 , "active_nicks")
DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , getChatNicks(chatters_store) , "stored_nicks")
}

StringArray AvCasterStore::getChatNicks(ValueTree chatters_store)
{
  return AvCasterStore::PropertyValues(chatters_store , CONFIG::NICK_ID) ;
}
