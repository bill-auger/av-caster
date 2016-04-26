#ifndef _CONFIGCONSTANTS_H_
#define _CONFIGCONSTANTS_H_


#include "JuceHeader.h"


/** the CONFIG class defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model                 */
class CONFIG
{
/*\ CAVEATS:
|*|  the application data model is implemented in the AvCasterStore class as JUCE ValueTrees
|*|      with a JUCE binary file-out for persistence (STORAGE_FILENAME)
|*|  when defining new nodes or properties be sure to:
|*|    * update the SCHEMA below
|*|    * if property                   -> define *_ID and DEFAULT_* below
|*|                                    -> sanitize data in AvCasterStore::sanitize*ParentNode*()
|*|    * if node                       -> verify schema in new method AvCasterStore::verifyNewNode()
|*|                                    -> sanitize data in AvCasterStore::sanitize*NewNode*()
|*|    * if persistent property        -> add to ROOT_PERSISTENT_IDS
|*|                                    -> verify in AvCasterStore::verify*ParentNode*()
|*|    * if persistent node            -> add to ROOT_PERSISTENT_NODE_IDS
|*|                                    -> verify in AvCasterStore::verify*ParentNode*()
|*|    * if transient property         -> add to ROOT_TRANSIENT_IDS
|*|    * if transient node             -> add to ROOT_TRANSIENT_NODE_IDS
|*|    * if transient property or node -> note this in the SCHEMA below as (non-persistent)
|*|                                    -> filter in AvCasterStore::storeConfig()
|*|    * if persistent root property   -> add default property to CONFIG::DefaultStore() below
|*|    * if persistent root node       -> add default node to CONFIG::DefaultStore() below
|*|    * if persistent preset property -> add instance var and definition in PresetSeed class
|*|    * if persistent preset node     -> add instance var and definition in PresetSeed class
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
|*|   CONFIG_VERSION_ID: a_double                             ,
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
|*|   PRESET_NAME_ID:   a_string  ,
|*|   SCREENCAP_ID:     a_bool    ,
|*|   CAMERA_ID:        a_bool    ,
|*|   TEXT_ID:          a_bool    ,
|*|   IMAGE_ID:         a_bool    ,
|*|   PREVIEW_ID:       a_bool    ,
|*|   AUDIO_ID:         a_bool    ,
|*|   OUTPUT_ID:        a_bool    , // (non-persistent)
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


public:

  // helpers
  static Identifier FilterId(String a_string , String retain_chars) ;


  // config indices
  static const int INVALID_IDX ;
  enum             StaticPreset { FILE_PRESET_IDX , RTMP_PRESET_IDX , LCTV_PRESET_IDX } ;
  enum             AudioApi     { ALSA_AUDIO_IDX , PULSE_AUDIO_IDX , JACK_AUDIO_IDX } ;
  enum             AudioCodec   { MP3_AUDIO_IDX , AAC_AUDIO_IDX } ;
  enum             OutputStream { FILE_OUTPUT_IDX , RTMP_OUTPUT_IDX } ;

  // config strings
  static const StringArray CAMERA_RESOLUTIONS ;
  static const StringArray AUDIO_APIS ;
  static const StringArray AUDIO_CODECS ;
  static const StringArray AUDIO_SAMPLERATES ;
  static const StringArray AUDIO_BITRATES ;
  static const StringArray TEXT_STYLES ;
  static const StringArray TEXT_POSITIONS ;
  static const StringArray OUTPUT_SINKS ;
  static const StringArray OUTPUT_MUXERS ;
  static const StringArray FRAMERATES ;
  static const StringArray VIDEO_BITRATES ;

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
  static const Identifier PRESET_NAME_ID ;
  static const Identifier SCREEN_ID ;
  static const Identifier CAMERA_ID ;
  static const Identifier TEXT_ID ;
  static const Identifier PREVIEW_ID ;
  static const Identifier AUDIO_ID ;
  static const Identifier IMAGE_ID ;
  static const Identifier OUTPUT_ID ;
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
  static const double     CONFIG_VERSION ;
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
  static const Identifier FILE_PRESET_ID ;
  static const Identifier RTMP_PRESET_ID ;
  static const Identifier LCTV_PRESET_ID ;
  static const Identifier DEFAULT_PRESET_ID ;
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

  // filter keys
  static const StringArray ROOT_PERSISTENT_NODES ;
  static const StringArray ROOT_NODES ;
  static const StringArray ROOT_PERSISTENT_KEYS ;
  static const StringArray ROOT_KEYS ;
  static const StringArray PRESET_PERSISTENT_NODES ;
  static const StringArray PRESET_NODES ;
  static const StringArray PRESET_PERSISTENT_KEYS ;
  static const StringArray PRESET_KEYS ;
  static const StringArray NETWORK_PERSISTENT_NODES ;
  static const StringArray NETWORK_NODES ;
  static const StringArray NETWORK_PERSISTENT_KEYS ;
  static const StringArray NETWORK_KEYS ;
  static const StringArray CHATTER_KEYS ;
  static const StringArray CAMERA_KEYS ;
  static const StringArray AUDIO_KEYS ;
  static const StringArray MEDIA_KEYS ;
  static const StringArray RECONFIGURE_KEYS ;
} ;

#endif // _CONFIGCONSTANTS_H_
