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
#include "Trace/TraceAvCasterStore.h"


AvCasterStore::AvCasterStore()
{
  // load stored configs
  ValueTree stored_config = ValueTree::invalid ;
  File      user_dir      = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  if (user_dir.isDirectory())
  {
    this->configFile               = user_dir.getChildFile(CONFIG::STORAGE_FILENAME) ;
    FileInputStream* config_stream = new FileInputStream(this->configFile) ;

    if (config_stream->openedOk()) stored_config = ValueTree::readFromStream(*config_stream) ;
    delete config_stream ;
  }

  // create shared config ValueTree from persistent storage or defaults
  this->configRoot    = verifyConfig(stored_config , CONFIG::STORAGE_ID) ;
  this->configPresets = this->configRoot.getOrCreateChildWithName(CONFIG::PRESETS_ID , nullptr) ;
  this->configStore   = ValueTree(CONFIG::VOLATILE_CONFIG_ID) ;
  this->cameraDevices = ValueTree(CONFIG::CAMERA_DEVICES_ID ) ;
  this->audioDevices  = ValueTree(CONFIG::AUDIO_DEVICES_ID  ) ;

  // detect hardware and sanitize config
  detectDisplayDimensions() ; detectCaptureDevices() ;
  validateConfig() ; sanitizeConfig() ; storeConfig() ;

  // subscribe to model changes
  this->configRoot .addListener(this) ;
  this->configStore.addListener(this) ;
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

void AvCasterStore::validateConfig()
{
DEBUG_TRACE_VALIDATE_CONFIG_ROOT

  if (!this->configRoot.isValid()) return ;

  // transfer missing properties
  validateRootProperty(CONFIG::CONFIG_VERSION_ID    , var(CONFIG::CONFIG_VERSION           )) ;
  validateRootProperty(CONFIG::IS_CONFIG_PENDING_ID , var(CONFIG::DEFAULT_IS_CONFIG_PENDING)) ;
  validateRootProperty(CONFIG::PRESET_ID            , var(CONFIG::DEFAULT_PRESET_IDX       )) ;

  // validate preset nodes
  int n_presets = this->configPresets.getNumChildren() ;
  if (!n_presets) this->configPresets.addChild(CONFIG::DEFAULT_PRESET_NODE , -1 , nullptr) ;
  n_presets     = this->configPresets.getNumChildren() ;
  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
  {
    this->configStore = this->configPresets.getChild(preset_n) ;
    validatePreset() ;
  }
  loadPreset() ;
}

void AvCasterStore::validatePreset()
{
DEBUG_TRACE_VALIDATE_CONFIG_PRESET

  if (!this->configStore.isValid()) return ;

  // transfer missing properties
  validatePresetProperty(CONFIG::IS_OUTPUT_ON_ID       , var(CONFIG::DEFAULT_IS_OUTPUT_ON        )) ;
  validatePresetProperty(CONFIG::IS_INTERSTITIAL_ON_ID , var(CONFIG::DEFAULT_IS_INTERSTITIAL_ON  )) ;
  validatePresetProperty(CONFIG::IS_SCREENCAP_ON_ID    , var(CONFIG::DEFAULT_IS_SCREENCAP_ON     )) ;
  validatePresetProperty(CONFIG::IS_CAMERA_ON_ID       , var(CONFIG::DEFAULT_IS_CAMERA_ON        )) ;
  validatePresetProperty(CONFIG::IS_TEXT_ON_ID         , var(CONFIG::DEFAULT_IS_TEXT_ON          )) ;
  validatePresetProperty(CONFIG::IS_PREVIEW_ON_ID      , var(CONFIG::DEFAULT_IS_PREVIEW_ON       )) ;
  validatePresetProperty(CONFIG::DISPLAY_N_ID          , var(CONFIG::DEFAULT_DISPLAY_N           )) ;
  validatePresetProperty(CONFIG::SCREEN_N_ID           , var(CONFIG::DEFAULT_SCREEN_N            )) ;
  validatePresetProperty(CONFIG::SCREENCAP_W_ID        , var(CONFIG::DEFAULT_SCREENCAP_W         )) ;
  validatePresetProperty(CONFIG::SCREENCAP_H_ID        , var(CONFIG::DEFAULT_SCREENCAP_H         )) ;
  validatePresetProperty(CONFIG::OFFSET_X_ID           , var(CONFIG::DEFAULT_OFFSET_X            )) ;
  validatePresetProperty(CONFIG::OFFSET_Y_ID           , var(CONFIG::DEFAULT_OFFSET_Y            )) ;
  validatePresetProperty(CONFIG::CAMERA_DEV_ID         , var(CONFIG::DEFAULT_CAMERA_DEV_IDX      )) ;
  validatePresetProperty(CONFIG::CAMERA_RES_ID         , var(CONFIG::DEFAULT_CAMERA_RES_IDX      )) ;
  validatePresetProperty(CONFIG::AUDIO_API_ID          , var(CONFIG::DEFAULT_AUDIO_API_IDX       )) ;
  validatePresetProperty(CONFIG::AUDIO_DEVICE_ID       , var(CONFIG::DEFAULT_AUDIO_DEVICE_IDX    )) ;
  validatePresetProperty(CONFIG::AUDIO_CODEC_ID        , var(CONFIG::DEFAULT_AUDIO_CODEC_IDX     )) ;
  validatePresetProperty(CONFIG::N_CHANNELS_ID         , var(CONFIG::DEFAULT_N_CHANNELS          )) ;
  validatePresetProperty(CONFIG::SAMPLERATE_ID         , var(CONFIG::DEFAULT_SAMPLERATE_IDX      )) ;
  validatePresetProperty(CONFIG::AUDIO_BITRATE_ID      , var(CONFIG::DEFAULT_AUDIO_BITRATE_IDX   )) ;
  validatePresetProperty(CONFIG::OVERLAY_TEXT_ID       , var(CONFIG::DEFAULT_OVERLAY_TEXT        )) ;
  validatePresetProperty(CONFIG::TEXT_STYLE_ID         , var(CONFIG::DEFAULT_TEXT_STYLE_IDX      )) ;
  validatePresetProperty(CONFIG::TEXT_POSITION_ID      , var(CONFIG::DEFAULT_TEXT_POSITION_IDX   )) ;
  validatePresetProperty(CONFIG::OUTPUT_STREAM_ID      , var(CONFIG::DEFAULT_OUTPUT_STREAM_IDX   )) ;
  validatePresetProperty(CONFIG::OUTPUT_CONTAINER_ID   , var(CONFIG::DEFAULT_OUTPUT_CONTAINER_IDX)) ;
  validatePresetProperty(CONFIG::OUTPUT_W_ID           , var(CONFIG::DEFAULT_OUTPUT_W            )) ;
  validatePresetProperty(CONFIG::OUTPUT_H_ID           , var(CONFIG::DEFAULT_OUTPUT_H            )) ;
  validatePresetProperty(CONFIG::FRAMERATE_ID          , var(CONFIG::DEFAULT_FRAMERATE_IDX       )) ;
  validatePresetProperty(CONFIG::VIDEO_BITRATE_ID      , var(CONFIG::DEFAULT_VIDEO_BITRATE_IDX   )) ;
  validatePresetProperty(CONFIG::OUTPUT_DEST_ID        , var(CONFIG::DEFAULT_OUTPUT_DEST         )) ;
}

void AvCasterStore::sanitizeConfig() // TODO: more
{
  if (!this->configRoot   .isValid() || !this->configStore .isValid() ||
      !this->cameraDevices.isValid() || !this->audioDevices.isValid()  ) return ;

  sanitizeRootComboProperty  (CONFIG::PRESET_ID           , CONFIG::PRESETS                  ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEV_ID       , CONFIG::CAMERA_RESOLUTIONS       ) ;
  sanitizePresetComboProperty(CONFIG::CAMERA_DEV_ID       , devicesNames(this->cameraDevices)) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_API_ID        , CONFIG::AUDIO_APIS               ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_DEVICE_ID     , devicesNames(this->audioDevices )) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_CODEC_ID      , CONFIG::AUDIO_CODECS             ) ;
  sanitizePresetComboProperty(CONFIG::SAMPLERATE_ID       , CONFIG::AUDIO_SAMPLERATES        ) ;
  sanitizePresetComboProperty(CONFIG::AUDIO_BITRATE_ID    , CONFIG::AUDIO_BITRATES           ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_STYLE_ID       , CONFIG::TEXT_STYLES              ) ;
  sanitizePresetComboProperty(CONFIG::TEXT_POSITION_ID    , CONFIG::TEXT_POSITIONS           ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_STREAM_ID    , CONFIG::OUTPUT_STREAMS           ) ;
  sanitizePresetComboProperty(CONFIG::OUTPUT_CONTAINER_ID , CONFIG::OUTPUT_CONTAINERS        ) ;
  sanitizePresetComboProperty(CONFIG::FRAMERATE_ID        , CONFIG::FRAMERATES               ) ;
  sanitizePresetComboProperty(CONFIG::VIDEO_BITRATE_ID    , CONFIG::VIDEO_BITRATES           ) ;

  validateConfig() ;
}

void AvCasterStore::storeConfig()
{
DEBUG_TRACE_DUMP_STORE_CONFIG
DEBUG_TRACE_DUMP_CONFIG_ROOT
DEBUG_TRACE_DUMP_CONFIG_PRESETS
DEBUG_TRACE_DUMP_CONFIG_VOLATILE
DEBUG_TRACE_DUMP_CONFIG_CAMERAS
DEBUG_TRACE_DUMP_CONFIG_AUDIO

  if (!this->configRoot.isValid()) return ;

  this->configFile.deleteFile() ;

  // filter transient data
  var is_config_pending = this->configRoot[CONFIG::IS_CONFIG_PENDING_ID] ;
  this->configRoot.removeProperty(CONFIG::IS_CONFIG_PENDING_ID , nullptr) ;

  // create storage directory
  File user_dir   = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  File config_dir = user_dir.getChildFile(CONFIG::STORAGE_DIRNAME) ;
  config_dir.createDirectory() ;

  // marshall configuration out to persistent binary storage
  FileOutputStream* config_stream = new FileOutputStream(this->configFile) ;
  if (!config_stream->failedToOpen()) this->configRoot.writeToStream(*config_stream) ;
  else AvCaster::Error(GUI::STORAGE_WRITE_ERROR_MSG) ;
  delete config_stream ;

  // restore transient data
  this->configRoot.setProperty(CONFIG::IS_CONFIG_PENDING_ID , is_config_pending , nullptr) ;
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
  validateProperty(this->configRoot , a_key , a_default_value) ;
}

void AvCasterStore::validatePresetProperty(Identifier a_key , var a_default_value)
{
  validateProperty(this->configStore , a_key , a_default_value) ;
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
  sanitizeIntProperty(this->configRoot , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::sanitizePresetComboProperty(Identifier a_key , StringArray options)
{
  sanitizeIntProperty(this->configStore , a_key , 0 , options.size() - 1) ;
}

void AvCasterStore::detectDisplayDimensions()
{
/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
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
  File*       camera_devices_dir = new File(APP::CAMERA_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->cameraDevices.removeAllChildren(nullptr) ;
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

      device_info.setProperty(CONFIG::CAMERA_PATH_ID , var(device_path  ) , nullptr) ;
      device_info.setProperty(CONFIG::CAMERA_NAME_ID , var(friendly_name) , nullptr) ;
      device_info.setProperty(CONFIG::FRAMERATE_ID   , var(30           ) , nullptr) ;
      this->cameraDevices.addChild(device_info , -1 , nullptr) ;
      ++device_info_dir ;
    }
  }
  else AvCaster::Warning(GUI::NO_CAMERAS_ERROR_MSG) ;

#endif // JUCE_LINUX

DEBUG_TRACE_DETECT_CAPTURE_DEVICES
}

void AvCasterStore::loadPreset()
{
  int current_config_idx = int(this->configRoot[CONFIG::PRESET_ID]) ;

  this->configStore = this->configPresets.getChild(current_config_idx).createCopy() ;
}

void AvCasterStore::storePreset(String preset_name)
{
  ValueTree preset_store = this->configPresets.getOrCreateChildWithName(preset_name , nullptr) ;
  int       preset_idx   = this->configPresets.indexOf(preset_store) ;

  preset_store.copyPropertiesFrom(this->configStore , nullptr) ;
  AvCaster::SetConfig(CONFIG::PRESET_ID , preset_idx) ;
}

void AvCasterStore::deletePreset()
{
  int current_idx = int(this->configRoot[CONFIG::PRESET_ID]) ;

  this->configPresets.removeChild(current_idx , nullptr) ;
  AvCaster::SetConfig(CONFIG::PRESET_ID , CONFIG::DEFAULT_PRESET_IDX) ;
}


/* event handlers */

void AvCasterStore::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  if (a_key == CONFIG::PRESET_ID) loadPreset() ;

  AvCaster::HandleConfigChanged(a_key) ;
}


/* helpers */

StringArray AvCasterStore::presetsNames()
{
  ValueTree   presets_node = this->configRoot.getChildWithName(CONFIG::PRESETS_ID) ;
  int         n_presets    = presets_node.getNumChildren() ;
  StringArray preset_names ;

  for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
    preset_names.add(String(presets_node.getChild(preset_n).getType())) ;

  return preset_names ;
}

StringArray AvCasterStore::devicesNames(ValueTree a_devices_node)
{
  int n_devices = a_devices_node.getNumChildren() ; StringArray device_names ;

  for (int device_n = 0 ; device_n < n_devices ; ++device_n)
  {
    ValueTree a_device    = a_devices_node.getChild(device_n) ;
    String    device_name = STRING(a_device[CONFIG::CAMERA_NAME_ID]) ;

    device_names.add(device_name) ;
  }

  return device_names ;
}
