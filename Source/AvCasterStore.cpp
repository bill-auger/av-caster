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


#include "AvCasterStore.h"
#include "AvCaster.h"
#include "PresetSeed.h"
#include "Trace/TraceAvCasterStore.h"


String bitlbee_host = "localhost" ;      String bitlbee_port = "6667" ; // TODO: GUI support
String debian_host  = "irc.debian.org" ; String debian_port  = "6667" ; // TODO: GUI support
String xmpp_chat    = "#mychat" ;                                       // TODO: GUI support


/* AvCasterStore private class methods */

StringArray AvCasterStore::PropertyValues(ValueTree root_node , Identifier property_id)
{
  int         n_children      = root_node.getNumChildren() ;
  StringArray property_values ;

  for (int child_n = 0 ; child_n < n_children ; ++child_n)
  {
    ValueTree child_node     = root_node.getChild(child_n) ;
    String    property_value = STRING(child_node[property_id]) ;

    property_values.add(property_value) ;
  }

  return property_values ;
}


/* AvCasterStore public instance methods */

AvCasterStore::~AvCasterStore() { }


/* AvCasterStore private instance methods */

AvCasterStore::AvCasterStore()
{
  // load stored configs
  this->configDir                = APP::APPDATA_DIR.getChildFile(CONFIG::STORAGE_DIRNAME ) ;
  this->configFile               = this->configDir .getChildFile(CONFIG::STORAGE_FILENAME) ;
  FileInputStream* config_stream = new FileInputStream(this->configFile) ;
  ValueTree        stored_config = ValueTree::invalid ;

  if (config_stream->openedOk()) stored_config = ValueTree::readFromStream(*config_stream) ;
  delete config_stream ;

  // create shared config ValueTree from persistent storage or defaults
  this->root    = verifyConfig(stored_config , CONFIG::STORAGE_ID) ;
  this->presets = getOrCreatePresets() ;
  this->servers = getOrCreateServers() ;
  this->config  = ValueTree(CONFIG::VOLATILE_CONFIG_ID) ;
  this->cameras = ValueTree(CONFIG::CAMERA_DEVICES_ID ) ;
  this->audios  = ValueTree(CONFIG::AUDIO_DEVICES_ID  ) ;

DEBUG_TRACE_DUMP_CONFIG("AvCasterStore::AvCasterStore()")

  // detect hardware and sanitize config
  detectCaptureDevices() ; // detectDisplayDimensions() ; // TODO: (issue #2 issue #4)
  verifyRoot() ;    sanitizeRoot() ;    verifyRoot() ;
  verifyPresets() ; sanitizePresets() ; verifyPresets() ; loadPreset() ;
  storeConfig() ;

#ifndef DISABLE_CHAT
storeServer(bitlbee_host , bitlbee_port) ; // TODO: GUI support
// storeServer(debian_host  , debian_port) ;  // TODO: GUI support
#endif // DISABLE_CHAT
}

ValueTree AvCasterStore::verifyConfig(ValueTree stored_config , Identifier root_node_id)
{
  bool      is_config_valid = stored_config.isValid() && stored_config.hasType(root_node_id) ;
  ValueTree config_store    = (is_config_valid) ? stored_config : CONFIG::DefaultStore() ;

  // verify config version
  double stored_version    = double(config_store[CONFIG::CONFIG_VERSION_ID]) ;
  bool   do_versions_match = stored_version ==   CONFIG::CONFIG_VERSION ;
  if (!do_versions_match)
  {
    // TODO: convert (if ever necessary)
    File parent_dir  = this->configFile.getParentDirectory() ;
    File backup_file = parent_dir.getNonexistentChildFile(CONFIG::STORAGE_FILENAME , ".bak" , false) ;
    this->configFile.copyFileTo(backup_file) ;
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

  // remove presets from runtime store (to ignore events)
  this->root.removeChild(presets , nullptr) ;

  return presets ;
}

ValueTree AvCasterStore::getOrCreateServers()
{
DEBUG_TRACE_VERIFY_SERVERS_NODE

  ValueTree servers = this->root.getOrCreateChildWithName(CONFIG::SERVERS_ID , nullptr) ;

  for (int server_n = 0 ; server_n < servers.getNumChildren() ; ++server_n)
    servers.getChild(server_n).addChild(ValueTree(CONFIG::CHATTERS_ID) , -1 , nullptr) ;

  // remove servers from runtime store (to ignore events)
  this->root.removeChild(servers , nullptr) ;

  return servers ;
}

void AvCasterStore::verifyRoot()
{
DEBUG_TRACE_VERIFY_CONFIG_ROOT

  if (!this->root.isValid()) return ;

  // transfer missing properties
  verifyRootProperty(CONFIG::CONFIG_VERSION_ID , var(CONFIG::CONFIG_VERSION    )) ;
  verifyRootProperty(CONFIG::IS_PENDING_ID     , var(CONFIG::DEFAULT_IS_PENDING)) ;
  verifyRootProperty(CONFIG::PRESET_ID         , var(CONFIG::DEFAULT_PRESET_IDX)) ;
}

void AvCasterStore::verifyPresets()
{
DEBUG_TRACE_VERIFY_CONFIG_PRESETS

  if (!this->presets.isValid()) return ;

  // verify user preset nodes
  int n_presets = this->presets.getNumChildren() ;
  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    this->config = this->presets.getChild(preset_n) ; verifyPreset() ;
  }
}

void AvCasterStore::verifyPreset()
{
DEBUG_TRACE_VERIFY_CONFIG_PRESET

  if (!this->config.isValid()) return ;

  // transfer missing properties
  verifyPresetProperty(CONFIG::PRESET_NAME_ID         , var(CONFIG::DEFAULT_PRESET_NAME        )) ;
  verifyPresetProperty(CONFIG::IS_SCREENCAP_ACTIVE_ID , var(CONFIG::DEFAULT_IS_SCREENCAP_ACTIVE)) ;
  verifyPresetProperty(CONFIG::IS_CAMERA_ACTIVE_ID    , var(CONFIG::DEFAULT_IS_CAMERA_ACTIVE   )) ;
  verifyPresetProperty(CONFIG::IS_TEXT_ACTIVE_ID      , var(CONFIG::DEFAULT_IS_TEXT_ACTIVE     )) ;
  verifyPresetProperty(CONFIG::IS_IMAGE_ACTIVE_ID     , var(CONFIG::DEFAULT_IS_IMAGE_ACTIVE    )) ;
  verifyPresetProperty(CONFIG::IS_PREVIEW_ACTIVE_ID   , var(CONFIG::DEFAULT_IS_PREVIEW_ACTIVE  )) ;
  verifyPresetProperty(CONFIG::IS_AUDIO_ACTIVE_ID     , var(CONFIG::DEFAULT_IS_AUDIO_ACTIVE    )) ;
  verifyPresetProperty(CONFIG::IS_OUTPUT_ACTIVE_ID    , var(CONFIG::DEFAULT_IS_OUTPUT_ACTIVE   )) ;
  verifyPresetProperty(CONFIG::DISPLAY_N_ID           , var(CONFIG::DEFAULT_DISPLAY_N          )) ;
  verifyPresetProperty(CONFIG::SCREEN_N_ID            , var(CONFIG::DEFAULT_SCREEN_N           )) ;
  verifyPresetProperty(CONFIG::SCREENCAP_W_ID         , var(CONFIG::DEFAULT_SCREENCAP_W        )) ;
  verifyPresetProperty(CONFIG::SCREENCAP_H_ID         , var(CONFIG::DEFAULT_SCREENCAP_H        )) ;
  verifyPresetProperty(CONFIG::OFFSET_X_ID            , var(CONFIG::DEFAULT_OFFSET_X           )) ;
  verifyPresetProperty(CONFIG::OFFSET_Y_ID            , var(CONFIG::DEFAULT_OFFSET_Y           )) ;
  verifyPresetProperty(CONFIG::CAMERA_DEVICE_ID       , var(CONFIG::DEFAULT_CAMERA_DEVICE_IDX  )) ;
  verifyPresetProperty(CONFIG::CAMERA_RES_ID          , var(CONFIG::DEFAULT_CAMERA_RES_IDX     )) ;
  verifyPresetProperty(CONFIG::AUDIO_API_ID           , var(CONFIG::DEFAULT_AUDIO_API_IDX      )) ;
  verifyPresetProperty(CONFIG::AUDIO_DEVICE_ID        , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX   )) ;
  verifyPresetProperty(CONFIG::AUDIO_CODEC_ID         , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX    )) ;
  verifyPresetProperty(CONFIG::N_CHANNELS_ID          , var(CONFIG::DEFAULT_N_CHANNELS         )) ;
  verifyPresetProperty(CONFIG::SAMPLERATE_ID          , var(CONFIG::DEFAULT_SAMPLERATE_IDX     )) ;
  verifyPresetProperty(CONFIG::AUDIO_BITRATE_ID       , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX  )) ;
  verifyPresetProperty(CONFIG::MOTD_TEXT_ID           , var(CONFIG::DEFAULT_MOTD_TEXT          )) ;
  verifyPresetProperty(CONFIG::TEXT_STYLE_ID          , var(CONFIG::DEFAULT_TEXT_STYLE_IDX     )) ;
  verifyPresetProperty(CONFIG::TEXT_POSITION_ID       , var(CONFIG::DEFAULT_TEXT_POSITION_IDX  )) ;
  verifyPresetProperty(CONFIG::IMAGE_ID               , var(CONFIG::DEFAULT_IMAGE_LOCATION     )) ;
  verifyPresetProperty(CONFIG::OUTPUT_SINK_ID         , var(CONFIG::DEFAULT_OUTPUT_SINK_IDX    )) ;
  verifyPresetProperty(CONFIG::OUTPUT_MUXER_ID        , var(CONFIG::DEFAULT_OUTPUT_MUXER_IDX   )) ;
  verifyPresetProperty(CONFIG::OUTPUT_W_ID            , var(CONFIG::DEFAULT_OUTPUT_W           )) ;
  verifyPresetProperty(CONFIG::OUTPUT_H_ID            , var(CONFIG::DEFAULT_OUTPUT_H           )) ;
  verifyPresetProperty(CONFIG::FRAMERATE_ID           , var(CONFIG::DEFAULT_FRAMERATE_IDX      )) ;
  verifyPresetProperty(CONFIG::VIDEO_BITRATE_ID       , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX  )) ;
  verifyPresetProperty(CONFIG::OUTPUT_DEST_ID         , var(CONFIG::DEFAULT_OUTPUT_DEST        )) ;
}

void AvCasterStore::verifyServers()
{
DEBUG_TRACE_VERIFY_SERVERS

  if (!this->servers.isValid()) return ;

  // verify user preset nodes
  int n_servers = this->servers.getNumChildren() ;
  for (int server_n = 0 ; server_n < n_servers ; ++server_n)
    verifyServer(this->servers.getChild(server_n)) ;
}

void AvCasterStore::verifyServer(ValueTree a_server_node)
{
DEBUG_TRACE_VERIFY_SERVER_IN

  if (!a_server_node.isValid()) return ;

  // transfer missing properties
  if (!a_server_node.hasProperty(CONFIG::HOST_ID   ) ||
      !a_server_node.hasProperty(CONFIG::PORT_ID   ) ||
      !a_server_node.hasProperty(CONFIG::CHANNEL_ID)  )
    a_server_node.getParent().removeChild(a_server_node , nullptr) ;

DEBUG_TRACE_VERIFY_SERVER_OUT
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
    this->config = this->presets.getChild(preset_n) ; sanitizePreset() ;
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
}

void AvCasterStore::storeConfig()
{
DEBUG_TRACE_STORE_CONFIG

  if (!this->root.isValid()) return ;

  // prepare storage directory
  this->configDir .createDirectory() ;
  this->configFile.deleteFile() ;

  // temmporarily ignore model change events
  listen(false) ;

  // filter transient data
  var is_config_pending = this->root  [CONFIG::IS_PENDING_ID      ] ;
  var is_output_on      = this->config[CONFIG::IS_OUTPUT_ACTIVE_ID] ;
  this->root  .removeProperty(CONFIG::IS_PENDING_ID       , nullptr) ;
  this->config.removeProperty(CONFIG::IS_OUTPUT_ACTIVE_ID , nullptr) ;

  // append presets and servers to persistent storage (ignoring chatters)
  int n_servers = this->servers.getNumChildren() ; UndoManager undo_manager ;
  for (int server_n = 0 ; server_n < n_servers ; ++server_n)
    this->servers.getChild(server_n).removeAllChildren(&undo_manager) ;
  this->root.addChild(this->presets , -1 , &undo_manager) ;
  this->root.addChild(this->servers , -1 , &undo_manager) ;

DEBUG_TRACE_DUMP_CONFIG("AvCasterStore->StoreConfig()")

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) this->root.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;

  // remove presets and servers from runtime store (restoring chatters)
  while (undo_manager.canUndo()) undo_manager.undo() ;

  // restore transient data
  this->root  .setProperty(CONFIG::IS_PENDING_ID       , is_config_pending , nullptr) ;
  this->config.setProperty(CONFIG::IS_OUTPUT_ACTIVE_ID , is_output_on      , nullptr) ;

  // re-subscribe to model change events
  listen(true) ;
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
#if JUCE_WINDOWS || JUCE_MAC
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
#endif // JUCE_WINDOWS || JUCE_MAC
#if JUCE_LINUX
  if (!APP::CAMERAS_DEV_DIR.isDirectory()) return ;

  // TODO: query device for framerates and resolutions
  String      resolutions      = String("160x120" + newLine + "320x240" + newLine + "640x480") ;
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
    device_info.setProperty(CONFIG::CAMERA_RATE_ID        , var(30           ) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_RESOLUTIONS_ID , var(resolutions  ) , nullptr) ;
    this->cameras.addChild(device_info , -1 , nullptr) ;
    ++device_info_dir ;
  }
#ifdef INJECT_DEFAULT_CAMERA_DEVICE_INFO
  if (device_info_dirs.size() == 0)
  {
    ValueTree device_info = ValueTree(Identifier("bogus-cam")) ;
    device_info.setProperty(CONFIG::CAMERA_PATH_ID        , var(String::empty ) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_NAME_ID        , var("bogus-camera") , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_RATE_ID        , var(8             ) , nullptr) ;
    device_info.setProperty(CONFIG::CAMERA_RESOLUTIONS_ID , var(resolutions   ) , nullptr) ;
    this->cameras.addChild(device_info , -1 , nullptr) ;
  }
#endif // INJECT_DEFAULT_CAMERA_DEVICE_INFO

#endif // JUCE_LINUX

DEBUG_TRACE_DETECT_CAPTURE_DEVICES
}

void AvCasterStore::loadPreset()
{
  int current_config_idx = int(this->root[CONFIG::PRESET_ID]) ;

  this->config = this->presets.getChild(current_config_idx).createCopy() ;
}

void AvCasterStore::storePreset(String preset_name)
{
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
  bool        has_idx_changed = preset_idx != AvCaster::GetPresetIdx() ;
  setConfig(CONFIG::OUTPUT_W_ID , var(jmax(fullscreen_w , camera_w , output_w))) ;
  setConfig(CONFIG::OUTPUT_H_ID , var(jmax(fullscreen_h , camera_h , output_h))) ;
#endif // FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT

  setConfig(CONFIG::PRESET_NAME_ID , preset_name) ;
  preset_store.copyPropertiesFrom(this->config , nullptr) ;
  setConfig(CONFIG::PRESET_ID      , preset_idx) ;
}

void AvCasterStore::renamePreset(String preset_name)
{
  Identifier preset_id      = CONFIG::FilterId(preset_name , APP::VALID_ID_CHARS) ;
  ValueTree  conflict_store = this->presets.getChildWithName(preset_id) ;

  if (conflict_store.isValid()) { AvCaster::Error(GUI::PRESET_RENAME_ERROR_MSG) ; return ; }

  int       preset_idx   = int(this->root[CONFIG::PRESET_ID]) ;
  ValueTree preset_store = this->presets.getChild(preset_idx) ;

DEBUG_TRACE_RENAME_PRESET

  preset_store.setProperty(CONFIG::PRESET_NAME_ID , preset_name , nullptr) ;
  setConfig               (CONFIG::PRESET_NAME_ID , preset_name) ;
}

void AvCasterStore::deletePreset()
{
  int preset_idx = int(this->root[CONFIG::PRESET_ID]) ;

  if (this->presets.getNumChildren() <= 1) return ;

DEBUG_TRACE_DELETE_PRESET

  this->presets.removeChild(preset_idx , nullptr) ;
  setConfig(CONFIG::PRESET_ID , CONFIG::DEFAULT_PRESET_IDX) ;
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

// TODO: GUI and model support
// void AvCasterStore::storeServer(String host , String port , String nick , String pass)
void AvCasterStore::storeServer(String host , String port)
{
String channel = xmpp_chat ; // TODOI: GUI support for host , port , channel
DEBUG_TRACE_STORE_SERVER

  Identifier server_id    = CONFIG::FilterId(host , APP::VALID_URI_CHARS) ;
  ValueTree  server_store = this->servers.getOrCreateChildWithName(server_id , nullptr) ;

  if (!server_store.hasProperty(CONFIG::HOST_ID))
    server_store.addChild(ValueTree(CONFIG::CHATTERS_ID) , -1 , nullptr) ;

  server_store.setProperty(CONFIG::HOST_ID    , host    , nullptr) ;
  server_store.setProperty(CONFIG::PORT_ID    , port    , nullptr) ;
//   server_store.setProperty(CONFIG::NICK_ID    , nick    , nullptr) ;
//   server_store.setProperty(CONFIG::PASS_ID    , pass    , nullptr) ;
  server_store.setProperty(CONFIG::CHANNEL_ID , channel , nullptr) ;
}


/* event handlers */

void AvCasterStore::listen(bool should_listen)
{
  if (!AvCaster::GetIsInitialized()) return ;

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

ValueTree AvCasterStore::getKeyNode(const Identifier& a_key)
{
  bool is_root_key = a_key == CONFIG::PRESET_ID || a_key == CONFIG::IS_PENDING_ID ;

  return (is_root_key    ) ? this->root         :
         (a_key.isValid()) ? this->config       :
                             ValueTree::invalid ;
}

bool AvCasterStore::isControlKey(const Identifier& a_key)
{
  // TODO: this could be a static Array<Identifier>
  return a_key == CONFIG::IS_SCREENCAP_ACTIVE_ID ||
         a_key == CONFIG::IS_CAMERA_ACTIVE_ID    ||
         a_key == CONFIG::IS_TEXT_ACTIVE_ID      ||
         a_key == CONFIG::IS_IMAGE_ACTIVE_ID     ||
         a_key == CONFIG::IS_PREVIEW_ACTIVE_ID   ||
         a_key == CONFIG::IS_AUDIO_ACTIVE_ID     ||
         a_key == CONFIG::IS_OUTPUT_ACTIVE_ID    ||
         a_key == CONFIG::IS_PENDING_ID          ||
         a_key == CONFIG::PRESET_ID               ;
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

ValueTree AvCasterStore::getCameraConfig()
{
  int camera_n = int(this->config[CONFIG::CAMERA_DEVICE_ID]) ;

  return this->cameras.getChild(camera_n) ;
}

StringArray AvCasterStore::getCameraResolutions()
{
  ValueTree camera_store = getCameraConfig() ;

  return StringArray::fromLines(STRING(camera_store[CONFIG::CAMERA_RESOLUTIONS_ID])) ;
}

void AvCasterStore::deactivateControl(const Identifier& a_key)
{
DEBUG_TRACE_DEACTIVATE_CONTROL

  listen(false) ; setConfig(a_key , var(false)) ; listen(true) ;
}

void AvCasterStore::setConfig(const Identifier& a_key , var a_value)
{
  ValueTree storage_node = getKeyNode(a_key) ;

DEBUG_TRACE_SET_CONFIG

  if (storage_node.isValid()) storage_node.setProperty(a_key , a_value , nullptr) ;
}

void AvCasterStore::updateIrcHost(StringArray alias_uris , String actual_host)
{
  // update current host for IRC network e.g. irc.debian.org => charm.oftc.org
  for (int alias_n = 0 ; alias_n < alias_uris.size() ; ++alias_n)
  {
    Identifier server_id    = CONFIG::FilterId(alias_uris[alias_n] , APP::VALID_URI_CHARS) ;
    ValueTree  server_store = this->servers.getChildWithName(server_id) ;

DEBUG_TRACE_UPDATE_IRC_HOST

    if (server_store.isValid())
      server_store.setProperty(CONFIG::HOST_ID , actual_host , nullptr) ;
  }
}

#ifdef PREFIX_CHAT_NICKS
void AvCasterStore::updateChatNicks(String host , String channel , StringArray nicks)
{
// TODO: GUI support for bitlbee_host , xmpp_chat
  bool   is_lctv  = host == bitlbee_host && channel == xmpp_chat ;
  String network  = (is_lctv) ? GUI::LCTV_USER_PREFIX : GUI::IRC_USER_PREFIX ;
  String prefixed = network + "["  + nicks.joinIntoString("] " +
                    network + "[") +                      "]"  ;
  nicks           = StringArray::fromTokens(prefixed , false) ;

#else // PREFIX_CHAT_NICKS
void AvCasterStore::updateChatNicks(String host , StringArray nicks)
{
#endif // PREFIX_CHAT_NICKS
  ValueTree   server_store   = this->servers.getChildWithProperty(CONFIG::HOST_ID , host) ;
  ValueTree   chatters_store = server_store.getChildWithName(CONFIG::CHATTERS_ID) ;
  StringArray current_nicks  = getChatNicks(chatters_store) ;

DEBUG_TRACE_UPDATE_CHAT_NICKS

  // add joining chatters
  for (String* nick = nicks.begin() ; nick != nicks.end() ; ++nick)
  {
    Identifier user_id       = CONFIG::FilterId(*nick , APP::VALID_NICK_CHARS) ;
    ValueTree  chatter_store = chatters_store.getChildWithName(user_id) ;

    if (!chatter_store.isValid())
    {
DEBUG_TRACE_ADD_CHAT_NICK

      current_nicks.add(*nick) ; current_nicks.sort(true) ;

      chatter_store = ValueTree(user_id) ;
      chatter_store.setProperty(CONFIG::CHAT_NICK_ID , var(*nick) , nullptr) ;
      chatters_store.addChild(chatter_store , current_nicks.indexOf(*nick) , nullptr) ;
    }
  }

  // remove parting chatters
  for (int chatter_n = 0 ; chatter_n < chatters_store.getNumChildren() ; ++chatter_n)
  {
    ValueTree chatter_store = chatters_store.getChild(chatter_n) ;
    String    nick          = STRING(chatter_store[CONFIG::CHAT_NICK_ID]) ;

DEBUG_TRACE_REMOVE_CHAT_NICK

    if (!nicks.contains(nick)) chatters_store.removeChild(chatter_store , nullptr) ;
  }

DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store)
}

StringArray AvCasterStore::getChatNicks(ValueTree chatters_store)
{
  return AvCasterStore::PropertyValues(chatters_store , CONFIG::CHAT_NICK_ID) ;
}
