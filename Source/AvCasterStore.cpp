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


AvCasterStore::AvCasterStore()
{
  // load stored configs
  ValueTree stored_config        = ValueTree::invalid ;
  this->configDir                = APP::APPDATA_DIR.getChildFile(CONFIG::STORAGE_DIRNAME ) ;
  this->configFile               = this->configDir .getChildFile(CONFIG::STORAGE_FILENAME) ;
  FileInputStream* config_stream = new FileInputStream(this->configFile) ;

  if (config_stream->openedOk()) stored_config = ValueTree::readFromStream(*config_stream) ;
  delete config_stream ;

  // create shared config ValueTree from persistent storage or defaults
  this->root    = verifyConfig(stored_config , CONFIG::STORAGE_ID) ;
  this->presets = verifyPresets() ;
  this->config  = ValueTree(CONFIG::VOLATILE_CONFIG_ID) ;
  this->cameras = ValueTree(CONFIG::CAMERA_DEVICES_ID ) ;
  this->audios  = ValueTree(CONFIG::AUDIO_DEVICES_ID  ) ;

  // detect hardware and sanitize config
  detectDisplayDimensions() ; detectCaptureDevices() ;
  validateConfig() ; sanitizeConfig() ; storeConfig() ;
}

AvCasterStore::~AvCasterStore() {}


/* AvCasterStore private instance methods */

ValueTree AvCasterStore::verifyConfig(ValueTree stored_config , Identifier root_node_id)
{
  bool      is_config_valid = stored_config.isValid() && stored_config.hasType(root_node_id) ;
  ValueTree config_store    = (is_config_valid) ? stored_config : ValueTree(CONFIG::STORAGE_ID) ;

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

ValueTree AvCasterStore::verifyPresets()
{
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

  this->root.removeChild(presets , nullptr) ;

  return presets ;
}

void AvCasterStore::validateConfig()
{
DEBUG_TRACE_VALIDATE_CONFIG

  if (!this->root.isValid()) return ;

  // transfer missing properties
  validateRootProperty(CONFIG::CONFIG_VERSION_ID    , var(CONFIG::CONFIG_VERSION           )) ;
  validateRootProperty(CONFIG::IS_CONFIG_PENDING_ID , var(CONFIG::DEFAULT_IS_CONFIG_PENDING)) ;
  validateRootProperty(CONFIG::PRESET_ID            , var(CONFIG::DEFAULT_PRESET_IDX       )) ;

  // validate user preset nodes
  int n_presets = this->presets.getNumChildren() ;
  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    this->config = this->presets.getChild(preset_n) ;
    validatePreset() ;
  }
  loadPreset() ;

  // TODO: validae/sanitize device nodes
}

void AvCasterStore::validatePreset()
{
DEBUG_TRACE_VALIDATE_CONFIG_PRESET

  if (!this->config.isValid()) return ;

  // transfer missing properties
  validatePresetProperty(CONFIG::PRESET_NAME_ID        , var(CONFIG::DEFAULT_PRESET_NAME       )) ;
  validatePresetProperty(CONFIG::IS_SCREENCAP_ON_ID    , var(CONFIG::DEFAULT_IS_SCREENCAP_ON   )) ;
  validatePresetProperty(CONFIG::IS_CAMERA_ON_ID       , var(CONFIG::DEFAULT_IS_CAMERA_ON      )) ;
  validatePresetProperty(CONFIG::IS_TEXT_ON_ID         , var(CONFIG::DEFAULT_IS_TEXT_ON        )) ;
  validatePresetProperty(CONFIG::IS_INTERSTITIAL_ON_ID , var(CONFIG::DEFAULT_IS_INTERSTITIAL_ON)) ;
  validatePresetProperty(CONFIG::IS_PREVIEW_ON_ID      , var(CONFIG::DEFAULT_IS_PREVIEW_ON     )) ;
  validatePresetProperty(CONFIG::IS_AUDIO_ON_ID        , var(CONFIG::DEFAULT_IS_AUDIO_ON       )) ;
  validatePresetProperty(CONFIG::IS_OUTPUT_ON_ID       , var(CONFIG::DEFAULT_IS_OUTPUT_ON      )) ;
  validatePresetProperty(CONFIG::DISPLAY_N_ID          , var(CONFIG::DEFAULT_DISPLAY_N         )) ;
  validatePresetProperty(CONFIG::SCREEN_N_ID           , var(CONFIG::DEFAULT_SCREEN_N          )) ;
  validatePresetProperty(CONFIG::SCREENCAP_W_ID        , var(CONFIG::DEFAULT_SCREENCAP_W       )) ;
  validatePresetProperty(CONFIG::SCREENCAP_H_ID        , var(CONFIG::DEFAULT_SCREENCAP_H       )) ;
  validatePresetProperty(CONFIG::OFFSET_X_ID           , var(CONFIG::DEFAULT_OFFSET_X          )) ;
  validatePresetProperty(CONFIG::OFFSET_Y_ID           , var(CONFIG::DEFAULT_OFFSET_Y          )) ;
  validatePresetProperty(CONFIG::CAMERA_DEV_ID         , var(CONFIG::DEFAULT_CAMERA_DEV_IDX    )) ;
  validatePresetProperty(CONFIG::CAMERA_RES_ID         , var(CONFIG::DEFAULT_CAMERA_RES_IDX    )) ;
  validatePresetProperty(CONFIG::AUDIO_API_ID          , var(CONFIG::DEFAULT_AUDIO_API_IDX     )) ;
  validatePresetProperty(CONFIG::AUDIO_DEVICE_ID       , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX  )) ;
  validatePresetProperty(CONFIG::AUDIO_CODEC_ID        , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX   )) ;
  validatePresetProperty(CONFIG::N_CHANNELS_ID         , var(CONFIG::DEFAULT_N_CHANNELS        )) ;
  validatePresetProperty(CONFIG::SAMPLERATE_ID         , var(CONFIG::DEFAULT_SAMPLERATE_IDX    )) ;
  validatePresetProperty(CONFIG::AUDIO_BITRATE_ID      , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX )) ;
  validatePresetProperty(CONFIG::MOTD_TEXT_ID          , var(CONFIG::DEFAULT_MOTD_TEXT         )) ;
  validatePresetProperty(CONFIG::TEXT_STYLE_ID         , var(CONFIG::DEFAULT_TEXT_STYLE_IDX    )) ;
  validatePresetProperty(CONFIG::TEXT_POSITION_ID      , var(CONFIG::DEFAULT_TEXT_POSITION_IDX )) ;
  validatePresetProperty(CONFIG::INTERSTITIAL_ID       , var(CONFIG::DEFAULT_INTERSTITIAL_LOC  )) ;
  validatePresetProperty(CONFIG::OUTPUT_SINK_ID        , var(CONFIG::DEFAULT_OUTPUT_SINK_IDX   )) ;
  validatePresetProperty(CONFIG::OUTPUT_MUXER_ID       , var(CONFIG::DEFAULT_OUTPUT_MUXER_IDX  )) ;
  validatePresetProperty(CONFIG::OUTPUT_W_ID           , var(CONFIG::DEFAULT_OUTPUT_W          )) ;
  validatePresetProperty(CONFIG::OUTPUT_H_ID           , var(CONFIG::DEFAULT_OUTPUT_H          )) ;
  validatePresetProperty(CONFIG::FRAMERATE_ID          , var(CONFIG::DEFAULT_FRAMERATE_IDX     )) ;
  validatePresetProperty(CONFIG::VIDEO_BITRATE_ID      , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX )) ;
  validatePresetProperty(CONFIG::OUTPUT_DEST_ID        , var(CONFIG::DEFAULT_OUTPUT_DEST       )) ;
}

void AvCasterStore::sanitizeConfig() // TODO: more
{
  if (!this->root   .isValid() || !this->config.isValid() ||
      !this->cameras.isValid() || !this->audios.isValid()  ) return ;

  sanitizeRootComboProperty  (CONFIG::PRESET_ID        , presetsNames()           ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEV_ID    , getCameraResolutions()   ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEV_ID    , cameraNames()            ) ;
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

  validateConfig() ;
}

void AvCasterStore::storeConfig()
{
DEBUG_TRACE_DUMP_STORE_CONFIG

  if (!this->root.isValid()) return ;

  // prepare storage directory
  this->configDir .createDirectory() ;
  this->configFile.deleteFile() ;

  // temmporarily ignore model change events
  listen(false) ;

  // filter transient data
  var is_config_pending = this->root  [CONFIG::IS_CONFIG_PENDING_ID] ;
  var is_output_on      = this->config[CONFIG::IS_OUTPUT_ON_ID     ] ;
  this->root  .removeProperty(CONFIG::IS_CONFIG_PENDING_ID , nullptr) ;
  this->config.removeProperty(CONFIG::IS_OUTPUT_ON_ID      , nullptr) ;

  // append presets to persistent storage
  this->root.addChild(this->presets , -1 , nullptr) ;

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) this->root.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;

  // remove presets from runtime store
  this->root.removeChild(this->presets , nullptr) ;

  // restore transient data
  this->root  .setProperty(CONFIG::IS_CONFIG_PENDING_ID , is_config_pending , nullptr) ;
  this->config.setProperty(CONFIG::IS_OUTPUT_ON_ID      , is_output_on      , nullptr) ;

  // re-subscribe to model change events
  listen(true) ;
}


/* runtime params */

void AvCasterStore::validateProperty(ValueTree config_store    , Identifier a_key ,
                                     var       a_default_value                    )
{
DEBUG_TRACE_VALIDATE_CONFIG_PROPERTY

  if (!config_store.hasProperty(a_key))
    config_store.setProperty(a_key , a_default_value , nullptr) ;
}

void AvCasterStore::validateRootProperty(Identifier a_key , var a_default_value)
{
  validateProperty(this->root , a_key , a_default_value) ;
}

void AvCasterStore::validatePresetProperty(Identifier a_key , var a_default_value)
{
  validateProperty(this->config , a_key , a_default_value) ;
}

void AvCasterStore::sanitizeIntProperty(ValueTree config_store , Identifier a_key ,
                                         int       min_value    , int max_value    )
{
// DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY

  int a_value = int(config_store[a_key]) ;

  if (a_value < min_value || a_value > max_value)
    config_store.removeProperty(a_key , nullptr) ;
}

void AvCasterStore::sanitizeRootComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->root , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::sanitizePresetComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->config , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::detectDisplayDimensions()
{
/* TODO: the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                       (see ComponentPeer::handleScreenSizeChange and/or Component::getParentMonitorArea)
                       gStreamer handles resolution changes gracefully so this  may not be strictly necessary */
/*
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;

  this->desktopW      = area.getWidth() ;
  this->desktopH      = area.getHeight() ;

  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;
*/
}

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

  // TODO: query device for framerates and resolutions
  String      resolutions        = String("160x120" + newLine + "320x240" + newLine + "640x480") ;
  File*       camera_devices_dir = new File(APP::CAMERA_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->cameras.removeAllChildren(nullptr) ;
  if (camera_devices_dir->containsSubDirectories()                                       &&
    !!camera_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
  {
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
  }
#ifdef INJECT_DEFAULT_CAMERA_DEVICE_INFO
else { ValueTree device_info = ValueTree(Identifier("bogus-cam")) ;
       device_info.setProperty(CONFIG::CAMERA_PATH_ID        , var(String::empty ) , nullptr) ;
       device_info.setProperty(CONFIG::CAMERA_NAME_ID        , var("bogus-camera") , nullptr) ;
       device_info.setProperty(CONFIG::CAMERA_RATE_ID        , var(8             ) , nullptr) ;
       device_info.setProperty(CONFIG::CAMERA_RESOLUTIONS_ID , var(resolutions   ) , nullptr) ;
       this->cameras.addChild(device_info , -1 , nullptr) ; }
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
  Identifier preset_id    = CONFIG::FilterId(preset_name) ;
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
  AvCaster::SetConfig(CONFIG::OUTPUT_W_ID , var(jmax(fullscreen_w , camera_w , output_w))) ;
  AvCaster::SetConfig(CONFIG::OUTPUT_H_ID , var(jmax(fullscreen_h , camera_h , output_h))) ;
  if (!has_idx_changed) AvCaster::RefreshGui() ;
#endif // FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT

  AvCaster::SetConfig(CONFIG::PRESET_NAME_ID , preset_name) ;
  preset_store.copyPropertiesFrom(this->config , nullptr) ;
  AvCaster::SetConfig(CONFIG::PRESET_ID      , preset_idx) ;
}

void AvCasterStore::renamePreset(String preset_name)
{
  Identifier preset_id      = CONFIG::FilterId(preset_name) ;
  ValueTree  conflict_store = this->presets.getChildWithName(preset_id) ;

  if (conflict_store.isValid()) { AvCaster::Error(GUI::PRESET_RENAME_ERROR_MSG) ; return ; }

  int       preset_idx   = int(this->root[CONFIG::PRESET_ID]) ;
  ValueTree preset_store = this->presets.getChild(preset_idx) ;

DEBUG_TRACE_RENAME_PRESET

  preset_store.setProperty(CONFIG::PRESET_NAME_ID , preset_name , nullptr) ;
  AvCaster::SetConfig     (CONFIG::PRESET_NAME_ID , preset_name) ;
}

void AvCasterStore::deletePreset()
{
  int preset_idx = int(this->root[CONFIG::PRESET_ID]) ;

  if (this->presets.getNumChildren() <= 1) return ;

DEBUG_TRACE_DELETE_PRESET

  this->presets.removeChild(preset_idx , nullptr) ;
  AvCaster::SetConfig(CONFIG::PRESET_ID , CONFIG::DEFAULT_PRESET_IDX) ;
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


/* event handlers */

void AvCasterStore::listen(bool should_listen)
{
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
  return (a_key == CONFIG::PRESET_ID          ||
          a_key == CONFIG::IS_CONFIG_PENDING_ID) ? this->root : this->config ;
}

bool AvCasterStore::isControlKey(const Identifier& a_key)
{
  // TODO: this could be a static Array<Identifier>
  return a_key == CONFIG::IS_SCREENCAP_ON_ID    ||
         a_key == CONFIG::IS_CAMERA_ON_ID       ||
         a_key == CONFIG::IS_TEXT_ON_ID         ||
         a_key == CONFIG::IS_INTERSTITIAL_ON_ID ||
         a_key == CONFIG::IS_PREVIEW_ON_ID      ||
         a_key == CONFIG::IS_AUDIO_ON_ID        ||
         a_key == CONFIG::IS_OUTPUT_ON_ID       ||
         a_key == CONFIG::IS_CONFIG_PENDING_ID  ||
         a_key == CONFIG::PRESET_ID              ;
}

StringArray AvCasterStore::presetsNames()
{
  int         n_presets    = this->presets.getNumChildren() ;
  StringArray preset_names ;

  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    ValueTree preset_store = this->presets.getChild(preset_n) ;
    String    preset_name  = STRING(preset_store[CONFIG::PRESET_NAME_ID]) ;

    preset_names.add(preset_name) ;
  }

  return preset_names ;
}

StringArray AvCasterStore::devicesNames(Identifier a_node_id)
{
  ValueTree devices_node = (a_node_id == CONFIG::CAMERA_DEVICES_ID) ? this->cameras       :
                           (a_node_id == CONFIG::AUDIO_DEVICES_ID ) ? this->audios        :
                                                                      ValueTree::invalid  ;

  int n_devices = devices_node.getNumChildren() ; StringArray device_names ;

  for (int device_n = 0 ; device_n < n_devices ; ++device_n)
  {
    ValueTree a_device    = devices_node.getChild(device_n) ;
    String    device_name = STRING(a_device[CONFIG::CAMERA_NAME_ID]) ;

    device_names.add(device_name) ;
  }

  return device_names ;
}

StringArray AvCasterStore::cameraNames() { return devicesNames(CONFIG::CAMERA_DEVICES_ID) ; }

StringArray AvCasterStore::audioNames() { return devicesNames(CONFIG::CAMERA_DEVICES_ID) ; }

ValueTree AvCasterStore::getCameraConfig()
{
  int camera_n = int(this->config[CONFIG::CAMERA_DEV_ID]) ;

  return this->cameras.getChild(camera_n) ;
}

StringArray AvCasterStore::getCameraResolutions()
{
  ValueTree camera_store = getCameraConfig() ;

  return StringArray::fromLines(STRING(camera_store[CONFIG::CAMERA_RESOLUTIONS_ID])) ;
}

void AvCasterStore::toogleControl(const Identifier& a_key)
{
DEBUG_TRACE_TOGGLE_CONTROL

  listen(false) ;
  AvCaster::SetConfig(a_key , !bool(this->config[a_key])) ; AvCaster::RefreshGui() ;
  listen(true) ;
}
