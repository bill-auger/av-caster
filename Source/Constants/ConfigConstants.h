/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#ifndef _CONFIGCONSTANTS_H_
#define _CONFIGCONSTANTS_H_

#include "JuceHeader.h"


/*\ CAVEATS:
|*|  the application data model is implemented in the AvCasterStore class as JUCE ValueTrees
|*|      with a JUCE binary file-out for persistence (STORAGE_FILENAME)
|*|  when defining new nodes or properties be sure to:
|*|    * update the SCHEMA below
|*|    * if property                   -> declare *_ID and DEFAULT_* below and define in ConfigConstants.cpp
|*|                                    -> sanitize data in pertinent parent AvCasterStore::sanitize*()
|*|    * if node                       -> verify schema in new method AvCasterStore::verify*NewNodeName*()
|*|                                    -> sanitize data in AvCasterStore::sanitize*NewNodeName*()
|*|    * if persistent property        -> add to pertinent parent *_PERSISTENT_IDS in ConfigConstants.cpp
|*|                                    -> verify existence in pertinent parent AvCasterStore::verify*()
|*|    * if persistent node            -> add to pertinent parent *_PERSISTENT_NODE_IDS in ConfigConstants.cpp
|*|                                    -> verify existence in pertinent parent AvCasterStore::verify*()
|*|    * if transient property         -> add to pertinent parent *_TRANSIENT_IDS in ConfigConstants.cpp
|*|    * if transient node             -> add to pertinent parent *_TRANSIENT_NODE_IDS in ConfigConstants.cpp
|*|    * if transient property or node -> note this in the SCHEMA below as (non-persistent)
|*|                                    -> filter in AvCasterStore::storeConfig()
|*|    * if persistent root property   -> add default property to Seeds::DefaultStore()
|*|    * if persistent root node       -> add default node to Seeds::DefaultStore()
|*|    * if persistent preset property -> add instance var in Seeds class and attach in Seeds::createPreset()
|*|    * if persistent preset node     -> add instance var in Seeds class and attach in Seeds::createPreset()
|*|    * if transient root property    -> restore in AvCasterStore::restoreTransients()
|*|    * if transient root node        -> restore in AvCasterStore::restoreTransients()
|*|    * if transient preset property  -> restore in AvCasterStore::restorePresetTransients()
|*|    * if transient preset node      -> restore in AvCasterStore::restorePresetTransients()
|*|    * if compatibility broken       -> increment CONFIG_VERSION
\*/

/*\ SCHEMA:
|*|
|*| // AvCasterStore->root
|*| // NOTE: PRESETS_ID node is pruned from root on load and re-grafted on store
|*| // NOTE: all properties and nodes marked as "(non-persistent)" are pruned on store
|*| STORAGE_ID:
|*| {
|*|   // config root
|*|   CONFIG_VERSION_ID: an_int                               ,
|*|   IS_PENDING_ID:     a_bool                               , // (non-persistent)
|*|   PRESET_ID:         an_int                               ,
|*|   PRESETS_ID:        [ a-preset-id: a_preset_node , ... ]   // preset nodes as below
|*| }
|*|
|*|
|*| // AvCasterStore->presets (pruned from root on load)
|*| PRESETS_ID: [ a-preset-id: a_preset_node , ... ] // a_preset as below
|*|
|*| // a_preset
|*| // AvCasterStore->presets (each child)
|*| // AvCasterStore->config  (non-persistent)
|*| // Gstreamer::ConfigStore (non-persistent)
|*| VOLATILE_CONFIG_ID:
|*| {
|*|   // Controls
|*|   SCREENCAP_ID:     a_bool    ,
|*|   CAMERA_ID:        a_bool    ,
|*|   TEXT_ID:          a_bool    ,
|*|   IMAGE_ID:         a_bool    ,
|*|   PREVIEW_ID:       a_bool    ,
|*|   AUDIO_ID:         a_bool    ,
|*|   OUTPUT_ID:        a_bool    , // (non-persistent)
|*|   // Presets
|*|   PRESET_NAME_ID:   a_string  ,
|*|   CONFIG_PANE_ID:   a_string  ,
|*|   // ConfigScreen
|*|   DISPLAY_N_ID:     an_int    ,
|*|   SCREEN_N_ID:      an_int    ,
|*|   SCREENCAP_W_ID:   an_int    ,
|*|   SCREENCAP_H_ID:   an_int    ,
|*|   OFFSET_X_ID:      an_int    ,
|*|   OFFSET_Y_ID:      an_int    ,
|*|   // ConfigCamera
|*|   CAMERA_DEVICE_ID: an_int    ,
|*|   CAMERA_RES_ID:    an_int    ,
|*|   // ConfigAudio
|*|   AUDIO_API_ID:     an_int    ,
|*|   AUDIO_DEVICE_ID:  an_int    ,
|*|   AUDIO_CODEC_ID:   an_int    ,
|*|   N_CHANNELS_ID:    an_int    ,
|*|   SAMPLERATE_ID:    an_int    ,
|*|   AUDIO_BITRATE_ID: an_int    ,
|*|   // ConfigText
|*|   MOTD_TEXT_ID:     a_string  ,
|*|   TEXT_STYLE_ID:    an_int    ,
|*|   TEXT_POSITION_ID: an_int    ,
|*|   // ConfigImage
|*|   IMAGE_LOC_ID:     a_string  ,
|*|   // ConfigOutput
|*|   OUTPUT_SINK_ID:   an_int    ,
|*|   OUTPUT_MUXER_ID:  an_int    ,
|*|   OUTPUT_W_ID:      an_int    ,
|*|   OUTPUT_H_ID:      an_int    ,
|*|   FRAMERATE_ID:     an_int    ,
|*|   VIDEO_BITRATE_ID: an_int    ,
|*|   OUTPUT_DEST_ID:   a_string  ,
|*|   // ConfigChat
|*|   NETWORK_ID:       a_network   // network as below
|*| }
|*|
|*|
|*| // AvCasterStore->network (alias of VOLATILE_CONFIG_ID[NETWORK_ID])
|*| NETWORK_ID:                 // e.g. "irc-debian-org" via FilterId("irc.debian.org")
|*| {
|*|   // ConfigChat
|*|   NETWORK_ID:    a_string , // e.g. "irc.debian.org"
|*|   HOST_ID:       a_string , // e.g. "charm.oftc.net" (non-persistent)
|*|   PORT_ID:       an_int   ,
|*|   NICK_ID:       a_string ,
|*|   PASS_ID:       a_string ,
|*|   CHANNEL_ID:    a_string ,
|*|   TIMESTAMPS_ID: a_bool   ,
|*|   JOINPARTS_ID:  a_bool   ,
|*|   GREETING_ID:   a_string ,
|*|   RETRIES_ID:    an_int     // (non-persistent)
|*| }
|*|
|*|
|*| // AvCasterStore->chatters
|*| CHATTERS_ID: [ a_chatter , ... ] // a_chatter as below (non-persistent)
|*|
|*| // a_chatter
|*| user-id:            // e.g. "-fred-stone" via FilterId("@fred stone")
|*| {
|*|   NICK_ID: a_string // e.g. "@fred stone"
|*| }
|*|
|*|
|*| // AvCasterStore->cameras (non-persistent)
|*| CAMERA_DEVICES_ID: [ device_id: a_camera_device_info , ... ] // a_camera_device_info as below
|*| // a_camera_device_info
|*| device-id:                          // e.g. "video0"
|*| {
|*|   CAMERA_PATH_ID:        a_string , // e.g. "/dev/video0"
|*|   CAMERA_NAME_ID:        a_string , // e.g "USB Video Cam"
|*|   CAMERA_RATE_ID:        an_int   ,
|*|   CAMERA_RESOLUTIONS_ID: a_string
|*| }
|*|
|*|
|*| // AvCasterStore->audios (non-persistent)
|*| AUDIO_DEVICES_ID: [] // nyi
\*/


/** the CONFIG class defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model                 */
class CONFIG
{
public:

  // initialization
  static void Initialize() ;

  // config strings
  static StringArray CameraResolutions() ;
  static StringArray AudioApis()         ;
  static StringArray AudioCodecs()       ;
  static StringArray AudioSampleRates()  ;
  static StringArray AudioBitRates()     ;
  static StringArray TextStyles()        ;
  static StringArray TextPositions()     ;
  static StringArray OutputSinks()       ;
  static StringArray OutputMuxers()      ;
  static StringArray FrameRates()        ;
  static StringArray VideoBitRates()     ;

  // filter keys
  static StringArray RootPersistentNodes()    ;
//   static StringArray RootNodes()              ;
  static StringArray RootPersistentKeys()     ;
  static StringArray RootKeys()               ;
  static StringArray PresetPersistentNodes()  ;
//   static StringArray PresetNodes()            ;
  static StringArray PresetPersistentKeys()   ;
  static StringArray PresetKeys()             ;
  static StringArray NetworkPersistentNodes() ;
//   static StringArray NetworkNodes()           ;
  static StringArray NetworkPersistentKeys()  ;
  static StringArray NetworkKeys()            ;
  static StringArray ChatterKeys()            ;
  static StringArray CameraKeys()             ;
  static StringArray AudioKeys()              ;
  static StringArray MediaToggleKeys()        ;
  static StringArray PresetConfigKeys()       ;

  // helpers
  static Identifier FilterId(String a_string , String retain_chars) ;


  // config indices
  static const int INVALID_IDX ;
  enum             StaticPreset { FILE_PRESET_IDX , RTMP_PRESET_IDX , LCTV_PRESET_IDX } ;
  enum             AudioApi     { ALSA_AUDIO_IDX , PULSE_AUDIO_IDX , JACK_AUDIO_IDX } ;
  enum             AudioCodec   { MP3_AUDIO_IDX , AAC_AUDIO_IDX } ;
  enum             OutputStream { FILE_OUTPUT_IDX , RTMP_OUTPUT_IDX } ;

  // storage nodes
  static const Identifier STORAGE_ID ;
  static const Identifier PRESETS_ID ;
  static const Identifier VOLATILE_CONFIG_ID ;
  static const Identifier CAMERA_DEVICES_ID ;
  static const Identifier AUDIO_DEVICES_ID ;
  // root IDs
  static const Identifier CONFIG_VERSION_ID ;
  static const Identifier PRESET_ID ;
  static const Identifier IS_PENDING_ID ;
  // Controls IDs
  static const Identifier SCREEN_ID ;
  static const Identifier CAMERA_ID ;
  static const Identifier TEXT_ID ;
  static const Identifier PREVIEW_ID ;
  static const Identifier AUDIO_ID ;
  static const Identifier IMAGE_ID ;
  static const Identifier OUTPUT_ID ;
  // Presets IDs
  static const Identifier PRESET_NAME_ID ;
  static const Identifier CONFIG_PANE_ID ;
  // ConfigScreen IDs
  static const Identifier DISPLAY_N_ID ;
  static const Identifier SCREEN_N_ID ;
  static const Identifier SCREENCAP_W_ID ;
  static const Identifier SCREENCAP_H_ID ;
  static const Identifier OFFSET_X_ID ;
  static const Identifier OFFSET_Y_ID ;
  // ConfigCamera IDs
  static const Identifier CAMERA_DEVICE_ID ;
  static const Identifier CAMERA_RES_ID ;
  static const Identifier CAMERA_PATH_ID ;
  static const Identifier CAMERA_NAME_ID ;
  static const Identifier CAMERA_RATE_ID ;
  static const Identifier CAMERA_RESOLUTIONS_ID ;
  // ConfigAudio IDs
  static const Identifier AUDIO_API_ID ;
  static const Identifier AUDIO_DEVICE_ID ;
  static const Identifier AUDIO_CODEC_ID ;
  static const Identifier N_CHANNELS_ID ;
  static const Identifier SAMPLERATE_ID ;
  static const Identifier AUDIO_BITRATE_ID ;
  // ConfigText IDs
  static const Identifier MOTD_TEXT_ID ;
  static const Identifier TEXT_STYLE_ID ;
  static const Identifier TEXT_POSITION_ID ;
  // ConfigImage IDs
  static const Identifier IMAGE_LOC_ID ;
  // ConfigOutput IDs
  static const Identifier OUTPUT_SINK_ID ;
  static const Identifier OUTPUT_MUXER_ID ;
  static const Identifier OUTPUT_W_ID ;
  static const Identifier OUTPUT_H_ID ;
  static const Identifier FRAMERATE_ID ;
  static const Identifier VIDEO_BITRATE_ID ;
  static const Identifier OUTPUT_DEST_ID ;
  // ConfigChat IDs
  static const Identifier NETWORK_ID ;
  static const Identifier HOST_ID ;
  static const Identifier PORT_ID ;
  static const Identifier NICK_ID ;
  static const Identifier PASS_ID ;
  static const Identifier CHANNEL_ID ;
  static const Identifier TIMESTAMPS_ID ;
  static const Identifier JOINPARTS_ID ;
  static const Identifier GREETING_ID ;
  static const Identifier RETRIES_ID ;
  static const Identifier CHATTERS_ID ;

  // root defaults
#if JUCE_LINUX
  static const String     STORAGE_DIRNAME ;
  static const String     STORAGE_FILENAME ;
#endif // JUCE_LINUX
#if JUCE_WINDOWS
  static const String     STORAGE_DIRNAME ;
  static const String     STORAGE_FILENAME ;
#endif // JUCE_WINDOWS
  static const int        CONFIG_VERSION ;
  static const int        DEFAULT_PRESET_IDX ;
  static const int        N_STATIC_PRESETS ;
  static const bool       DEFAULT_IS_PENDING ;
  // Controls defaults
  static const bool       DEFAULT_IS_SCREEN_ACTIVE ;
  static const bool       DEFAULT_IS_CAMERA_ACTIVE ;
  static const bool       DEFAULT_IS_TEXT_ACTIVE ;
  static const bool       DEFAULT_IS_IMAGE_ACTIVE ;
  static const bool       DEFAULT_IS_PREVIEW_ACTIVE ;
  static const bool       DEFAULT_IS_AUDIO_ACTIVE ;
  static const bool       DEFAULT_IS_OUTPUT_ACTIVE ;
  // Presets defaults
  static const String     FILE_PRESET_NAME ;
  static const String     RTMP_PRESET_NAME ;
  static const String     LCTV_PRESET_NAME ;
  static const String     DEFAULT_PRESET_NAME ;
  static const String     DEFAULT_CONFIG_PANE ;
  static const Identifier DEFAULT_PRESET_ID ;
  static const Identifier FILE_PRESET_ID ;
  static const Identifier RTMP_PRESET_ID ;
  static const Identifier LCTV_PRESET_ID ;
  // ConfigScreen defaults
  static const int        DEFAULT_DISPLAY_N ;
  static const int        DEFAULT_SCREEN_N ;
  static const int        DEFAULT_SCREENCAP_W ;
  static const int        DEFAULT_SCREENCAP_H ;
  static const int        DEFAULT_OFFSET_X ;
  static const int        DEFAULT_OFFSET_Y ;
  // ConfigCamera defaults
  static const int        DEFAULT_CAMERA_DEVICE_IDX ;
  static const int        DEFAULT_CAMERA_RES_IDX ;
  static const int        DEFAULT_CAMERA_RATE ;
  // ConfigAudio defaults
  static const int        DEFAULT_AUDIO_API_IDX ;
  static const int        DEFAULT_AUDIO_DEVICE_IDX ;
  static const int        DEFAULT_AUDIO_CODEC_IDX ;
  static const int        DEFAULT_N_CHANNELS ;
  static const int        DEFAULT_SAMPLERATE_IDX ;
  static const int        DEFAULT_AUDIO_BITRATE_IDX ;
  // ConfigText defaults
  static const String     DEFAULT_MOTD_TEXT ;
  static const int        DEFAULT_TEXT_STYLE_IDX ;
  static const int        DEFAULT_TEXT_POSITION_IDX ;
  // ConfigImage defaults
  static const String     DEFAULT_IMAGE_LOCATION ;
  // ConfigOutput defaults
  static const int        DEFAULT_OUTPUT_SINK_IDX ;
  static const int        DEFAULT_OUTPUT_MUXER_IDX ;
  static const int        DEFAULT_OUTPUT_W ;
  static const int        DEFAULT_OUTPUT_H ;
  static const int        DEFAULT_FRAMERATE_IDX ;
  static const int        DEFAULT_VIDEO_BITRATE_IDX ;
  static const String     DEFAULT_OUTPUT_DEST ;
  // ConfigChat defaults
  static const String     DEFAULT_NETWORK ;
  static const String     DEFAULT_HOST ;
  static const int        DEFAULT_PORT ;
  static const String     DEFAULT_NICK ;
  static const String     DEFAULT_PASS ;
  static const String     DEFAULT_CHANNEL ;
  static const bool       DEFAULT_SHOW_TIMESTAMPS ;
  static const bool       DEFAULT_SHOW_JOINPARTS ;
  static const String     DEFAULT_GREETING ;
  static const int        DEFAULT_N_RETRIES ;
} ;

#endif // _CONFIGCONSTANTS_H_
