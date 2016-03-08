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


#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// enable standard features
// #define DISABLE_MEDIA
// #define SCREEN_ONLY
// #define CAMERA_ONLY
// #define TEXT_ONLY
// #define IMAGE_ONLY
// #define TRAY_ICON // TODO: requires juce_gui_extras package
#define TEXT_BIN_NYI  1
#define IMAGE_BIN_NYI 1
#define DISABLE_GUI_CONFIG_NYI
#define DISABLE_AUDIO   (! JUCE_LINUX) // replace audio-real-source with fakesrc
#define DISABLE_PREVIEW (! JUCE_LINUX) // replace preview-sink with fakesink
//#define DISABLE_OUTPUT               // replace filesink or rtmpsink with fakesink
// #define DISABLE_CHAT
#define SEED_IRC_NETWORKS (!defined(DISABLE_CHAT)) && 0
#define SUPRESS_GREETING_MESSAGES
#define SUPRESS_ALERTS
// #define CHATLIST_KICK_BTN_NYI

// debugging tweaks and kludges
// #define DUMP_COMFIG_VERBOSE
#define INJECT_DEFAULT_CAMERA_DEVICE_INFO
#define FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
#define NATIVE_CAMERA_RESOLUTION_ONLY
// #define FAKE_MUX_ENCODER_SRC_AND_SINK // isolate compositor from encoder and muxer from output
// #define MOCK_CHAT_NICKS

// enable tracing
#ifdef DEBUG
#  define DEBUG_TRACE 1
#else // DEBUG
#  define DEBUG_TRACE 1
#endif // DEBUG
#define DEBUG_TRACE_EVENTS    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_GUI       (DEBUG_TRACE && 1)
#define DEBUG_TRACE_GUI_VB    (DEBUG_TRACE && 0)
#define DEBUG_TRACE_MEDIA     (DEBUG_TRACE && 1)
#define DEBUG_TRACE_MEDIA_VB  (DEBUG_TRACE && 0)
#define DEBUG_TRACE_CONFIG    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CONFIG_VB (DEBUG_TRACE && 0)
#define DEBUG_TRACE_CHAT      (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CHAT_VB   (DEBUG_TRACE && 0)
#define DEBUG_TRACE_STATE     (DEBUG_TRACE && 1)
#define DEBUG_TRACE_ERRORS    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_VB        (DEBUG_TRACE && 0)

// enable debug features
#ifdef DEBUG_TRACE
#  define DEBUG_ANSI_COLORS 1
// #  define DEBUG_QUIT_IMMEDIATELY
#endif // DEBUG_TRACE


#include "JuceHeader.h"


/** the APP namespace defines configuration and runtime constants
        pertaining to the core AvCaster application and business logic */
namespace APP
{
  // names and IDs
  static const String APP_NAME         = "AvCaster" ;
  static const String APP_CMD          = "av-caster" ;
  static const String JACK_CLIENT_NAME = APP_NAME ;
  static const String IRC_THREAD_NAME  = "av-caster-irc" ;
  static const String DIGITS           = "0123456789" ;
  static const String LETTERS          = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
  static const String ALPHANUMERIC     = DIGITS + LETTERS ;
  static const String VALID_ID_CHARS   = ALPHANUMERIC + "_- " ;
  static const String VALID_URI_CHARS  = ALPHANUMERIC + "_-.:/?=@#&" ;
  static const String VALID_NICK_CHARS = ALPHANUMERIC + "_-@#&[]" ;
  static const String FILTER_CHARS     = "-_.:/?=@#&[] " ;
  static const String REPLACE_CHARS    = String::repeatedString("-" , FILTER_CHARS.length()) ;

  // timers
  static const int N_TIMERS             = 3 ;
  static const int TIMER_HI_ID          = 1 ; static const int TIMER_HI_IVL  = 125 ;
  static const int TIMER_MED_ID         = 2 ; static const int TIMER_MED_IVL = 500 ;
  static const int TIMER_LO_ID          = 3 ; static const int TIMER_LO_IVL  = 500 ;
  static const int TIMER_IDS [N_TIMERS] = { TIMER_HI_ID  , TIMER_MED_ID  , TIMER_LO_ID  } ;
  static const int TIMER_IVLS[N_TIMERS] = { TIMER_HI_IVL , TIMER_MED_IVL , TIMER_LO_IVL } ;

  // cli args
  static const String CLI_HELP_TOKEN            = "--help" ;
  static const String CLI_PRESETS_TOKEN         = "--presets" ;
  static const String CLI_VERSION_TOKEN         = "--version" ;
  static const String CLI_PRESET_TOKEN          = "--preset" ;
  static const String CLI_DISABLE_MEDIA_TOKEN   = "--no-media" ;
  static const String CLI_SCREEN_ONLY_TOKEN     = "--screen-only" ;
  static const String CLI_CAMERA_ONLY_TOKEN     = "--camera-only" ;
  static const String CLI_TEXT_ONLY_TOKEN       = "--text-only" ;
  static const String CLI_IMAGE_ONLY_TOKEN      = "--image-only" ;
  static const String CLI_DISABLE_PREVIEW_TOKEN = "--no-preview" ;
  static const String CLI_DISABLE_AUDIO_TOKEN   = "--no-audio" ;
  static const String CLI_DISABLE_CHAT_TOKEN    = "--no-chat" ;
#ifdef DEBUG
  static const String CLI_VERSION_MSG = "AvCaster v" + String(ProjectInfo::versionString) + " (DEBUG)" ;
#else // DEBUG
  static const String CLI_VERSION_MSG = "AvCaster v" + String(ProjectInfo::versionString) ;
#endif // DEBUG
  static const String CLI_USAGE_MSG   = "AvCaster Usage:\n\n\t" + APP_CMD + " [ "   + CLI_HELP_TOKEN            + " | "                                                          +
                                                                                      CLI_PRESETS_TOKEN         + " | "                                                          +
                                                                                      CLI_VERSION_TOKEN         + " ]"                                                           +
                                                       "\n\n\t" + APP_CMD + " [ "   + CLI_PRESET_TOKEN          + " n    ] "                                                     +
                                                         "\n\t          [ "         + CLI_DISABLE_MEDIA_TOKEN   + "    ] "                                                       +
                                                                       "[ "         + CLI_DISABLE_PREVIEW_TOKEN + "  ] "                                                         +
                                                                       "[ "         + CLI_DISABLE_AUDIO_TOKEN   + "  ] "                                                         +
                                                                       "[ "         + CLI_DISABLE_CHAT_TOKEN    + " ]"                                                           +
                                                         "\n\t          [ "         + CLI_SCREEN_ONLY_TOKEN     + " | "                                                          +
                                                                       "  "         + CLI_CAMERA_ONLY_TOKEN     + " | "                                                          +
//                                                                        "  "         + CLI_TEXT_ONLY_TOKEN       + " | "                                                          +
//                                                                        "  "         + CLI_IMAGE_ONLY_TOKEN      + " ] "                                                          +
                                                     "\n\n\n\tINFORMATION:"                                                                                                      +
                                                     "\n\n\t\t"                     + CLI_HELP_TOKEN            + "\n\t\t\tprints this message and exits"                        +
                                                     "\n\n\t\t"                     + CLI_PRESETS_TOKEN         + "\n\t\t\tlist stored presets and exits"                        +
                                                     "\n\n\t\t"                     + CLI_VERSION_TOKEN         + "\n\t\t\tprints the application version string and exits"      +
                                                     "\n\n\n\tCONFIGURATION:"                                                                                                    +
                                                     "\n\n\t\t"                     + CLI_PRESET_TOKEN + " n"   + "\n\t\t\tstarts " + APP_NAME + " with initial preset number n" +
                                                     "\n\n\n\tFEATURE SWITCHES:"                                                                                                 +
                                                     "\n\n\t\t"                     + CLI_DISABLE_MEDIA_TOKEN   + "\n\t\t\tdisables all media and stream output"                 +
                                                     "\n\n\t\t"                     + CLI_SCREEN_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders screen only"         +
                                                     "\n\n\t\t"                     + CLI_CAMERA_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders webcam only"         +
//                                                      "\n\n\t\t"                     + CLI_TEXT_ONLY_TOKEN       + "\n\t\t\tdisables compositing and renders text overlay only"   +
//                                                      "\n\n\t\t        "             + CLI_IMAGE_ONLY_TOKEN      + "\n\t\t\tdisables compositing and renders static image only"   +
                                                     "\n\n\t\t"                     + CLI_DISABLE_PREVIEW_TOKEN + "\n\t\t\tdisables realtime preview"                            +
                                                     "\n\n\t\t"                     + CLI_DISABLE_AUDIO_TOKEN   + "\n\t\t\tdisables audio capture"                               +
                                                     "\n\n\t\t"                     + CLI_DISABLE_CHAT_TOKEN    + "\n\t\t\tdisables chat"                                        ;

// NOTE: INPUTS are either mutually exclusive (compositor disabled) or must all be enabled (compositor enabled)
//       N_COMPOSITOR_INPUTS is coupled to MEDIA_INIT_ID flags in AvCaster::ProcessCliParams()
#define INPUTS String(APP::CLI_SCREEN_ONLY_TOKEN + newLine + APP::CLI_CAMERA_ONLY_TOKEN + \
               String((TEXT_BIN_NYI ) ? "" :       newLine + APP::CLI_TEXT_ONLY_TOKEN)  + \
               String((IMAGE_BIN_NYI) ? "" :       newLine + APP::CLI_IMAGE_ONLY_TOKEN) )
  static const int N_COMPOSITOR_INPUTS = StringArray::fromLines(INPUTS).size() ;

  // filesystem
  static const String PNG_FILE_EXT     = ".png" ;
//   static const String JPG_FILE_EXT    = ".jpg" ;
//   static const String JPEG_FILE_EXT   = ".jpeg" ;
//   static const String GIF_FILE_EXT    = ".gif" ;
  static const String ICONS_PATH       = ".local/share/icons/hicolor/48x48/apps/" ;
  static const String APPS_PATH        = ".local/share/applications/" ;
  static const String ICON_FILENAME    = APP_CMD + PNG_FILE_EXT ;
  static const String DESKTOP_FILENAME = APP_CMD + ".desktop" ;
  static const File   BIN_FILE         = File::getSpecialLocation(File::currentExecutableFile       ) ;
  static const File   HOME_DIR         = File::getSpecialLocation(File::userHomeDirectory           ) ;
  static const File   APPDATA_DIR      = File::getSpecialLocation(File::userApplicationDataDirectory) ;
// FIXME: segfault (if dir not exist? - or xdg-user-dir VIDEOS invalid?)
// more XDG_CONFIG_HOME ('~/.config')
//   static const File   PICTURES_DIR     = File::getSpecialLocation(File::userPicturesDirectory       ) ;
//   static const File   VIDEOS_DIR       = File::getSpecialLocation(File::userMoviesDirectory         ) ;
  static const File   PICTURES_DIR     = File("/home/bill/pics") ;
  static const File   VIDEOS_DIR       = File("/home/bill/vids") ;
  static const File   LOGO_FILE        = BIN_FILE.getSiblingFile(ICON_FILENAME                ) ;
  static const File   ICON_FILE        = HOME_DIR.getChildFile  (ICONS_PATH + ICON_FILENAME   ) ;
  static const File   DESKTOP_FILE     = HOME_DIR.getChildFile  (APPS_PATH  + DESKTOP_FILENAME) ;
  static const File   CAMERAS_DEV_DIR  = File("/sys/class/video4linux") ;
  static const String DESKTOP_TEXT     = String("[Desktop Entry]\r\n")                           +
                                         "Name=AvCaster\r\n"                                     +
                                         "GenericName=\r\n"                                      +
                                         "Comment=Desktop, webcam, and audio streaming tool\r\n" +
                                         "Categories=AudioVideo;\r\n"                            +
                                         "Exec=" + BIN_FILE .getFullPathName() + "\r\n" +        +
                                         "Icon=" + ICON_FILE.getFullPathName() + "\r\n" +        +
                                         "StartupNotify=true\r\n"                                +
                                         "Terminal=false\r\n"                                    +
                                         "Type=Application\r\n"                                  ;
}


/** the IRC namespace defines configuration constants
        pertaining to the libircclient network backend */
namespace IRC
{
  static const uint8         MIN_MAJOR_VERSION = 1 ;
  static const uint8         MIN_MINOR_VERSION = 8 ;
  static const Range<uint16> PORT_RANGE        = Range<uint16>::between(1 , 49151) ;

  // IDs
  static const String      BITLBEE_HOST             = "im.bitlbee.org" ;
  static const String      LOCAL_HOST               = "localhost" ;
  static const String      BITLBEE_REMOTE_ROOT_USER = "root!root@" + BITLBEE_HOST ;
  static const String      BITLBEE_LOCAL_ROOT_USER  = "root!root@" + LOCAL_HOST   ;
  static const StringArray BITLBEE_HOSTS            = StringArray::fromLines(BITLBEE_HOST + newLine +
                                                                             LOCAL_HOST             ) ;
  static const StringArray BITLBEE_ROOT_USERS       = StringArray::fromLines(BITLBEE_REMOTE_ROOT_USER + newLine +
                                                                             BITLBEE_LOCAL_ROOT_USER            ) ;
  static const char*       BITLBEE_ROOT_NICK        = "@root" ;
  static const char*       BITLBEE_ROOT_CHANNEL     = "&bitlbee" ;
  static const char*       BITLBEE_XMPP_CHANNEL     = "#xmpp-chat" ;
  static const String      BITLBEE_IDENTIFY_CMD     = "identify " ;

  // connection state
  static const uint8 MAX_N_RETRIES   = 5 ;
  static const uint8 STATE_FAILED    = 0 ;
  static const uint8 STATE_CONNECTED = MAX_N_RETRIES ;

  // incoming server messages
  static const char*  BITLBEE_CONNECTED_MSG     = "Logging in: Logged in" ;
  static const String BITLBEE_WELCOME_MSG       = "Welcome to the BitlBee gateway, " ;
  static const char*  BITLBEE_LOGIN_BLOCKED_MSG = "New request: You're already connected to this server. Would you like to take over this session?" ;
  static const char*  BITLBEE_KICKED_SELF_MSG   = "You've successfully taken over your old session" ;

  // formatting markup tokens
  static const String BOLD_BEGIN   = "[B]" ;
  static const String BOLD_END     = "[/B]" ;
  static const String ITALIC_BEGIN = "[I]" ;
  static const String ITALIC_END   = "[/I]" ;
  static const String ULINE_BEGIN  = "[U]" ;
  static const String ULINE_END    = "[/U]" ;
  static const String COLOR_BEGIN  = "[COLOR=" ;
  static const String COLOR_END    = "[/COLOR]" ;

  // GUI display messages
  static const String YOU_NICK                    = "You" ;
  static const char*  INVALID_PARAMS_MSG          = "Invalid network credentials." ;
  static const String BITLBEE_SESSION_BLOCKED_MSG = "It appeaers that you are already connected to BitlBee with another client.  This chat will not be connected to LCTV." ;
  static const String LOGGING_IN_MSG              = "Logging into chat server: " ;
  static const String LOGGED_IN_MSG               = "Logged into chat server: " ;
  static const String LOGGING_OUT_MSG             = "Logging out of chat server: " ;
  static const String LOGIN_GREETING              = APP::APP_NAME + " starting up" ;
  static const String LOGOUT_GREETING             = APP::APP_NAME + " shutting down" ;

  // URIS
  static const String LCTV_URL = "https://www.livecoding.tv/" ;
}


/** the CONFIG namespace defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model                     */
namespace CONFIG
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


  static Identifier FilterId(String a_string , String retain_chars)
  {
    return a_string.retainCharacters(retain_chars)
                   .toLowerCase()
                   .replaceCharacters(APP::FILTER_CHARS , APP::REPLACE_CHARS) ;
  }


  // config indices
  static const int INVALID_IDX  = -1 ;
  enum             StaticPreset { FILE_PRESET_IDX , RTMP_PRESET_IDX , LCTV_PRESET_IDX } ;
  enum             AudioApi     { ALSA_AUDIO_IDX , PULSE_AUDIO_IDX , JACK_AUDIO_IDX } ;
  enum             AudioCodec   { MP3_AUDIO_IDX , AAC_AUDIO_IDX } ;
  enum             OutputStream { FILE_OUTPUT_IDX , RTMP_OUTPUT_IDX } ;

  // config strings
  static const StringArray CAMERA_RESOLUTIONS = StringArray::fromLines("160x120" + newLine +
                                                                       "320x240" + newLine +
                                                                       "640x480"           ) ;
  static const StringArray AUDIO_APIS         = StringArray::fromLines("ALSA"    + newLine +
                                                                       "Pulse"   + newLine +
                                                                       "JACK"              ) ;
  static const StringArray AUDIO_CODECS       = StringArray::fromLines("MP3"     + newLine +
                                                                       "AAC"               ) ;
  static const StringArray AUDIO_SAMPLERATES  = StringArray::fromLines("11025"   + newLine +
                                                                       "22050"   + newLine +
                                                                       "44100"   + newLine +
                                                                       "48000"             ) ;
  static const StringArray AUDIO_BITRATES     = StringArray::fromLines("64k"     + newLine +
                                                                       "96k"     + newLine +
                                                                       "128k"    + newLine +
                                                                       "192k"              ) ;
  static const StringArray TEXT_STYLES        = StringArray::fromLines("Static"  + newLine +
                                                                       "Marquee"           ) ;
  static const StringArray TEXT_POSITIONS     = StringArray::fromLines("Top"     + newLine +
                                                                       "Bottom"            ) ;
  static const StringArray OUTPUT_SINKS       = StringArray::fromLines("File"    + newLine +
                                                                       "RTMP"              ) ;
  static const StringArray OUTPUT_MUXERS      = StringArray::fromLines(".flv"              ) ;
  static const StringArray FRAMERATES         = StringArray::fromLines("8"       + newLine +
                                                                       "12"      + newLine +
                                                                       "20"      + newLine +
                                                                       "30"                ) ;
  static const StringArray VIDEO_BITRATES     = StringArray::fromLines("800k"    + newLine +
                                                                       "1200k"             ) ;

  // storage nodes
  static const Identifier STORAGE_ID            = "av-caster-config" ;
  static const Identifier PRESETS_ID            = "presets" ;
  static const Identifier VOLATILE_CONFIG_ID    = "volatile-config" ;
  static const Identifier CAMERA_DEVICES_ID     = "camera-devices" ;
  static const Identifier AUDIO_DEVICES_ID      = "audio-devices" ;
  // root IDs
  static const Identifier CONFIG_VERSION_ID     = "config-version" ;
  static const Identifier PRESET_ID             = "current-preset-idx" ;
  static const Identifier IS_PENDING_ID         = "is-config-pending" ;
  // Controls IDs
  static const Identifier PRESET_NAME_ID        = "preset-name" ;
  static const Identifier SCREEN_ID             = "is-screencap-on" ;
  static const Identifier CAMERA_ID             = "is-camera-on" ;
  static const Identifier TEXT_ID               = "is-text-on" ;
  static const Identifier PREVIEW_ID            = "is-preview-on" ;
  static const Identifier AUDIO_ID              = "is-audio-on" ;
  static const Identifier IMAGE_ID              = "is-interstitial-on" ;
  static const Identifier OUTPUT_ID             = "is-output-on" ;
  // ConfigScreen IDs
  static const Identifier DISPLAY_N_ID          = "display-n" ;
  static const Identifier SCREEN_N_ID           = "screen-n" ;
  static const Identifier SCREENCAP_W_ID        = "sceencap-w" ;
  static const Identifier SCREENCAP_H_ID        = "sceencap-h" ;
  static const Identifier OFFSET_X_ID           = "offset-x" ;
  static const Identifier OFFSET_Y_ID           = "offset-y" ;
  // ConfigCamera IDs
  static const Identifier CAMERA_DEVICE_ID      = "camera-dev-idx" ;
  static const Identifier CAMERA_RES_ID         = "camera-res-idx" ;
  static const Identifier CAMERA_PATH_ID        = "camera-dev-path" ;
  static const Identifier CAMERA_NAME_ID        = "camera-dev-name" ;
  static const Identifier CAMERA_RATE_ID        = "camera-framerate" ;
  static const Identifier CAMERA_RESOLUTIONS_ID = "camera-resolutions" ;
  // ConfigAudio IDs
  static const Identifier AUDIO_API_ID          = "audio-api-idx" ;
  static const Identifier AUDIO_DEVICE_ID       = "audio-dev-idx" ;
  static const Identifier AUDIO_CODEC_ID        = "audio-codec-idx" ;
  static const Identifier N_CHANNELS_ID         = "n-channels" ;
  static const Identifier SAMPLERATE_ID         = "samplerate-idx" ;
  static const Identifier AUDIO_BITRATE_ID      = "audio-bitrate-idx" ;
  // ConfigText IDs
  static const Identifier MOTD_TEXT_ID          = "motd-text" ;
  static const Identifier TEXT_STYLE_ID         = "text-style-idx" ;
  static const Identifier TEXT_POSITION_ID      = "text-pos-idx" ;
  // ConfigImage IDs
  static const Identifier IMAGE_LOC_ID          = "interstitial-img" ;
  // ConfigOutput IDs
  static const Identifier OUTPUT_SINK_ID        = "output-sink-idx" ;
  static const Identifier OUTPUT_MUXER_ID       = "output-muxer-idx" ;
  static const Identifier OUTPUT_W_ID           = "output-w" ;
  static const Identifier OUTPUT_H_ID           = "output-h" ;
  static const Identifier FRAMERATE_ID          = "framerate-idx" ;
  static const Identifier VIDEO_BITRATE_ID      = "video-bitrate-idx" ;
  static const Identifier OUTPUT_DEST_ID        = "output-dest" ;
  // ConfigChat IDs
  static const Identifier NETWORK_ID            = "chat-network" ;
  static const Identifier HOST_ID               = "chat-host" ;
  static const Identifier PORT_ID               = "chat-port" ;
  static const Identifier NICK_ID               = "chat-nick" ;
  static const Identifier PASS_ID               = "chat-pass" ;
  static const Identifier CHANNEL_ID            = "chat-channel" ;
  static const Identifier TIMESTAMPS_ID         = "show-timestamps" ;
  static const Identifier JOINPARTS_ID          = "show-joins-parts" ;
  static const Identifier GREETING_ID           = "chat-greeting" ;
  static const Identifier RETRIES_ID            = "n-connect-retries" ;
  static const Identifier CHATTERS_ID           = "active-chatters" ;
  // temporary keys for disabling media via CLI args
  static const Identifier MEDIA_INIT_ID         = "media-init" ;
  static const Identifier MEDIA_DISABLED_ID     = "is-media-disabled" ;
  static const Identifier SCREENCAP_DISABLED_ID = "is-screencap-disabled" ;
  static const Identifier CAMERA_DISABLED_ID    = "is-camera-disabled" ;
  static const Identifier TEXT_DISABLED_ID      = "is-text-disabled" ;
  static const Identifier IMAGE_DISABLED_ID     = "is-interstitial-disabled" ;
  static const Identifier VMIXER_ID    = "is-compositor-disabled" ;
  static const Identifier PREVIEW_DISABLED_ID   = "is-preview-disabled" ;
  static const Identifier AUDIO_DISABLED_ID     = "is-audio-disabled" ;
  static const Identifier CHAT_DISABLED_ID      = "is-chat-disabled" ;

  // root defaults
#if JUCE_LINUX
  static const String     STORAGE_DIRNAME             = ".config/" + APP::APP_CMD + "/" ;
  static const String     STORAGE_FILENAME            = APP::APP_CMD + ".bin" ;
#endif // JUCE_LINUX
#if JUCE_WINDOWS
  static const String     STORAGE_DIRNAME             = APP::APP_NAME + "\\" ;
  static const String     STORAGE_FILENAME            = APP::APP_NAME + ".bin" ;
#endif // JUCE_WINDOWS
  static const double     CONFIG_VERSION              = 0.4 ;
  static const int        DEFAULT_PRESET_IDX          = FILE_PRESET_IDX ; // ASSERT: must be 0
  static const int        N_STATIC_PRESETS            = 3 ; // ASSERT: num PresetSeed::PresetSeeds() child nodes
  static const bool       DEFAULT_IS_PENDING          = false ;
  // Controls defaults
  static const bool       DEFAULT_IS_SCREEN_ACTIVE    = false ;
  static const bool       DEFAULT_IS_CAMERA_ACTIVE    = false ;
  static const bool       DEFAULT_IS_TEXT_ACTIVE      = false ;
  static const bool       DEFAULT_IS_IMAGE_ACTIVE     = true ;
  static const bool       DEFAULT_IS_PREVIEW_ACTIVE   = true ;
  static const bool       DEFAULT_IS_AUDIO_ACTIVE     = false ;
  static const bool       DEFAULT_IS_OUTPUT_ACTIVE    = false ;
  // Presets defaults
  static const String     FILE_PRESET_NAME            = "Local File" ;
  static const String     RTMP_PRESET_NAME            = "RTMP Server" ;
  static const String     LCTV_PRESET_NAME            = "livecoding.tv" ;
  static const String     DEFAULT_PRESET_NAME         = FILE_PRESET_NAME ;
  static const Identifier FILE_PRESET_ID              = FilterId(FILE_PRESET_NAME    , APP::VALID_ID_CHARS) ;
  static const Identifier RTMP_PRESET_ID              = FilterId(RTMP_PRESET_NAME    , APP::VALID_ID_CHARS) ;
  static const Identifier LCTV_PRESET_ID              = FilterId(LCTV_PRESET_NAME    , APP::VALID_ID_CHARS) ;
  static const Identifier DEFAULT_PRESET_ID           = FilterId(DEFAULT_PRESET_NAME , APP::VALID_ID_CHARS) ;
  // ConfigScreen defaults
  static const int        DEFAULT_DISPLAY_N           = 0 ;
  static const int        DEFAULT_SCREEN_N            = 0 ;
  static const int        DEFAULT_SCREENCAP_W         = 640 ;
  static const int        DEFAULT_SCREENCAP_H         = 480 ;
  static const int        DEFAULT_OFFSET_X            = 0 ;
  static const int        DEFAULT_OFFSET_Y            = 0 ;
  // ConfigCamera defaults
  static const int        DEFAULT_CAMERA_DEVICE_IDX   = INVALID_IDX ;
  static const int        DEFAULT_CAMERA_RES_IDX      = INVALID_IDX ;
  static const int        DEFAULT_CAMERA_RATE         = 30 ;
  // ConfigAudio defaults
  static const int        DEFAULT_AUDIO_API_IDX       = ALSA_AUDIO_IDX ;
  static const int        DEFAULT_AUDIO_DEVICE_IDX    = INVALID_IDX ;
  static const int        DEFAULT_AUDIO_CODEC_IDX     = MP3_AUDIO_IDX ;
  static const int        DEFAULT_N_CHANNELS          = 2 ;
  static const int        DEFAULT_SAMPLERATE_IDX      = 0 ;
  static const int        DEFAULT_AUDIO_BITRATE_IDX   = 0 ;
  // ConfigText defaults
  static const String     DEFAULT_MOTD_TEXT           = "" ;
  static const int        DEFAULT_TEXT_STYLE_IDX      = 0 ;
  static const int        DEFAULT_TEXT_POSITION_IDX   = 0 ;
  // ConfigImage defaults
  static const String     DEFAULT_IMAGE_LOCATION      = "" ;
  // ConfigOutput defaults
  static const int        DEFAULT_OUTPUT_SINK_IDX     = FILE_OUTPUT_IDX ;
  static const int        DEFAULT_OUTPUT_MUXER_IDX    = 0 ;
  static const int        DEFAULT_OUTPUT_W            = 640 ;
  static const int        DEFAULT_OUTPUT_H            = 480 ;
  static const int        DEFAULT_FRAMERATE_IDX       = 0 ;
  static const int        DEFAULT_VIDEO_BITRATE_IDX   = 0 ;
  static const String     DEFAULT_OUTPUT_DEST         = APP::APP_NAME + ".flv" ;
  // ConfigChat defaults
  static const String     DEFAULT_NETWORK             = "" ;
  static const String     DEFAULT_HOST                = "" ;
  static const int        DEFAULT_PORT                = 0 ;
  static const String     DEFAULT_NICK                = "" ;
  static const String     DEFAULT_PASS                = "" ;
  static const String     DEFAULT_CHANNEL             = "" ;
  static const bool       DEFAULT_SHOW_TIMESTAMPS     = false ;
  static const bool       DEFAULT_SHOW_JOINPARTS      = true ;
  static const String     DEFAULT_GREETING            = "" ;
  static const int        DEFAULT_N_RETRIES           = IRC::STATE_FAILED ; // 0


#define ROOT_PERSISTENT_NODE_IDS    String(PRESETS_ID       )
#define ROOT_TRANSIENT_NODE_IDS     String(""               )
#define ROOT_PERSISTENT_IDS         String(CONFIG_VERSION_ID) + " " + String(PRESET_ID       ) + " " + \
                                    String(PRESETS_ID       )
#define ROOT_TRANSIENT_IDS          String(IS_PENDING_ID    )
#define PRESET_PERSISTENT_NODE_IDS  String(NETWORK_ID)
#define PRESET_TRANSIENT_NODE_IDS   String(""               )
#define PRESET_PERSISTENT_IDS       String(PRESET_NAME_ID   ) + " " + String(SCREEN_ID       ) + " " + \
                                    String(CAMERA_ID        ) + " " + String(TEXT_ID         ) + " " + \
                                    String(IMAGE_ID         ) + " " + String(PREVIEW_ID      ) + " " + \
                                    String(AUDIO_ID         )                                  + " " + \
                                    String(DISPLAY_N_ID     ) + " " + String(SCREEN_N_ID     ) + " " + \
                                    String(SCREENCAP_W_ID   ) + " " + String(SCREENCAP_H_ID  ) + " " + \
                                    String(OFFSET_X_ID      ) + " " + String(OFFSET_Y_ID     ) + " " + \
                                    String(CAMERA_DEVICE_ID ) + " " + String(CAMERA_RES_ID   ) + " " + \
                                    String(AUDIO_API_ID     ) + " " + String(AUDIO_DEVICE_ID ) + " " + \
                                    String(AUDIO_CODEC_ID   ) + " " + String(N_CHANNELS_ID   ) + " " + \
                                    String(SAMPLERATE_ID    ) + " " + String(AUDIO_BITRATE_ID) + " " + \
                                    String(MOTD_TEXT_ID     ) + " " + String(TEXT_STYLE_ID   ) + " " + \
                                    String(TEXT_POSITION_ID ) + " "                                  + \
                                    String(IMAGE_LOC_ID     ) + " "                                  + \
                                    String(OUTPUT_SINK_ID   ) + " " + String(OUTPUT_MUXER_ID ) + " " + \
                                    String(OUTPUT_W_ID      ) + " " + String(OUTPUT_H_ID     ) + " " + \
                                    String(FRAMERATE_ID     ) + " " + String(VIDEO_BITRATE_ID) + " " + \
                                    String(OUTPUT_DEST_ID   )
#define PRESET_TRANSIENT_IDS        String(OUTPUT_ID)
#define NETWORK_PERSISTENT_NODE_IDS String(""               )
#define NETWORK_TRANSIENT_NODE_IDS  String(CHATTERS_ID      )
#define NETWORK_PERSISTENT_IDS      String(NETWORK_ID       ) + " " + String(PORT_ID         ) + " " + \
                                    String(NICK_ID          ) + " " + String(PASS_ID         ) + " " + \
                                    String(CHANNEL_ID       ) + " " + String(TIMESTAMPS_ID   ) + " " + \
                                    String(JOINPARTS_ID     ) + " " + String(GREETING_ID     )
#define NETWORK_TRANSIENT_IDS       String(HOST_ID          ) + " " + String(RETRIES_ID      )
#define CHATTER_TRANSIENT_IDS       String(NICK_ID          )
#define CAMERA_TRANSIENT_IDS        String(""               )
#define AUDIO_TRANSIENT_IDS         String(""               )
#define MEDIA_IDS                   String(SCREEN_ID        ) + " " + String(CAMERA_ID       ) + " " + \
                                    String(TEXT_ID          ) + " " + String(IMAGE_ID        ) + " " + \
                                    String(PREVIEW_ID       ) + " " + String(AUDIO_ID        ) + " " + \
                                    String(OUTPUT_ID        )
#define RECONFIGURE_IDS             String(IS_PENDING_ID    ) + " " + String(PRESET_ID)
  static const StringArray ROOT_PERSISTENT_NODES    = StringArray::fromTokens(ROOT_PERSISTENT_NODE_IDS    , false) ;
  static const StringArray ROOT_NODES               = StringArray::fromTokens(ROOT_PERSISTENT_NODE_IDS    + " "  +
                                                                              ROOT_TRANSIENT_NODE_IDS     , false) ;
  static const StringArray ROOT_PERSISTENT_KEYS     = StringArray::fromTokens(ROOT_PERSISTENT_IDS         , false) ;
  static const StringArray ROOT_KEYS                = StringArray::fromTokens(ROOT_PERSISTENT_IDS         + " "  +
                                                                              ROOT_TRANSIENT_IDS          , false) ;
  static const StringArray PRESET_PERSISTENT_NODES  = StringArray::fromTokens(PRESET_PERSISTENT_NODE_IDS  , false) ;
  static const StringArray PRESET_NODES             = StringArray::fromTokens(PRESET_PERSISTENT_NODE_IDS  + " "  +
                                                                              PRESET_TRANSIENT_NODE_IDS   , false) ;
  static const StringArray PRESET_PERSISTENT_KEYS   = StringArray::fromTokens(PRESET_PERSISTENT_IDS       , false) ;
  static const StringArray PRESET_KEYS              = StringArray::fromTokens(PRESET_PERSISTENT_IDS       + " "  +
                                                                              PRESET_TRANSIENT_IDS        , false) ;
  static const StringArray NETWORK_PERSISTENT_NODES = StringArray::fromTokens(NETWORK_PERSISTENT_NODE_IDS , false) ;
  static const StringArray NETWORK_NODES            = StringArray::fromTokens(NETWORK_PERSISTENT_NODE_IDS + " "  +
                                                                              NETWORK_TRANSIENT_NODE_IDS  , false) ;
  static const StringArray NETWORK_PERSISTENT_KEYS  = StringArray::fromTokens(NETWORK_PERSISTENT_IDS      , false) ;
  static const StringArray NETWORK_KEYS             = StringArray::fromTokens(NETWORK_PERSISTENT_IDS      + " "  +
                                                                              NETWORK_TRANSIENT_IDS       , false) ;
  static const StringArray CHATTER_KEYS             = StringArray::fromTokens(CHATTER_TRANSIENT_IDS       , false) ;
  static const StringArray CAMERA_KEYS              = StringArray::fromTokens(CAMERA_TRANSIENT_IDS        , false) ;
  static const StringArray AUDIO_KEYS               = StringArray::fromTokens(AUDIO_TRANSIENT_IDS         , false) ;
  static const StringArray MEDIA_KEYS               = StringArray::fromTokens(MEDIA_IDS                   , false) ;
  static const StringArray RECONFIGURE_KEYS         = StringArray::fromTokens(RECONFIGURE_IDS             , false) ;
}



/** the GST namespace defines configuration and runtime constants
        pertaining to the Gstreamer media backend class           */
namespace GST
{
  static const uint8 MIN_MAJOR_VERSION = 1 ;
  static const uint8 MIN_MINOR_VERSION = 6 ;

  // element IDs
  static const String PIPELINE_ID         = "pipeline" ;
  static const String SCREENCAP_BIN_ID    = "screencap-bin" ;
  static const String CAMERA_BIN_ID       = "camera-bin" ;
  static const String TEXT_BIN_ID         = "text-bin" ;
  static const String IMAGE_BIN_ID        = "interstitial-bin" ;
  static const String COMPOSITOR_BIN_ID   = "compositor-bin" ;
  static const String PREVIEW_BIN_ID      = "preview-bin" ;
  static const String PREVIEW_SINK_ID     = "preview-real-sink" ;
  static const String PREVIEW_FAUXSINK_ID = "preview-faux-sink" ;
  static const String PREVIEW_SINKPAD_ID  = "preview-sinkpad" ;
  static const String AUDIO_BIN_ID        = "audio-bin" ;
  static const String MUXER_BIN_ID        = "muxer-bin" ;
  static const String OUTPUT_BIN_ID       = "output-bin" ;
  // plugin IDs
#if JUCE_LINUX
  static const String SCREEN_PLUGIN_ID    = "ximagesrc" ;
  static const String CAMERA_PLUGIN_ID    = "v4l2src" ;
  static const String ALSA_PLUGIN_ID      = "alsasrc" ;
  static const String PULSE_PLUGIN_ID     = "pulsesrc" ;
  static const String JACK_PLUGIN_ID      = "jackaudiosrc" ;
  static const String PREVIEW_PLUGIN_ID   = "xvimagesink" ;
#endif //JUCE_LINUX
  static const String FAUXSRC_PLUGIN_ID   = "fakesrc" ;
  static const String FAUXSINK_PLUGIN_ID  = "fakesink" ;
  static const String TESTVIDEO_PLUGIN_ID = "videotestsrc" ;
  static const String TESTAUDIO_PLUGIN_ID = "audiotestsrc" ;
  static const String FILESINK_PLUGIN_ID  = "filesink" ;
  static const String RTMPSINK_PLUGIN_ID  = "rtmpsink" ;

  static const String LCTV_RTMP_URL = "rtmp://usmedia3.livecoding.tv:1935/livecodingtv/" ;

  // library error messages
  static const String ALSA_INIT_ERROR  = "Could not open audio device for recording. Device is being used by another application." ;
  static const String PULSE_INIT_ERROR = "Failed to connect: Connection refused" ;
  static const String JACK_INIT_ERROR  = "Jack server not found" ;
  static const String FILE_SINK_ERROR  = "No file name specified for writing." ;
}


/** the GUI namespace defines configuration and runtime constants
        pertaining to graphical elements                          */
namespace GUI
{
  // common
  static const int    PAD                   = 4 ;
  static const int    PAD3                  = (PAD * 3) ;
  static const int    PAD4                  = (PAD * 4) ;
  static const int    PAD6                  = (PAD * 6) ;
  static const int    PAD8                  = (PAD * 8) ;
  static const Colour TEXT_EMPTY_COLOR      = Colour(0x80808080) ;
  static const Colour TEXT_NORMAL_COLOR     = Colour(0xFFC0C0C0) ;
  static const Colour TEXT_INVALID_COLOR    = Colour(0xFFFF0000) ;
  static const Colour TEXT_HILITE_COLOR     = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_HILITEBG_COLOR   = Colour(0xFF000040) ;
  static const Colour TEXT_CARET_COLOR      = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_FOCUS_COLOR      = Colour(0xFF000000) ;
  static const Colour TEXT_SHADOW_COLOR     = Colour(0xFF000000) ;
  static const Colour TEXT_BG_COLOR         = Colour(0xFF000000) ;
  static const Colour TEXT_INVALID_BG_COLOR = Colour(0xFF200000) ;

  // MainWindow
  static const int    BORDERS_W       = 2 ;
  static const int    TITLEBAR_H      = 24 ;
  static const int    WINDOW_W        = 760 - BORDERS_W ;              // jucer 758
  static const int    WINDOW_H        = 788 - BORDERS_W - TITLEBAR_H ; // jucer 762
  static const int    TITLEBAR_BTNS   = DocumentWindow::minimiseButton | DocumentWindow::closeButton ;
  static const String IDLE_TITLE_TEXT = "(Idle)" ;
  static const String FILE_TITLE_TEXT = "(Recording)" ;
  static const String RTMP_TITLE_TEXT = "(Broadcasting)" ;
#ifdef TRAY_ICON
  static const String TRAY_TOOTIP     = "\nClick to show/hide\nRight-click for menu" ;
#endif // TRAY_ICON

  // Controls
  static const String FILE_XMIT_TEXT = "Record" ;
  static const String RTMP_XMIT_TEXT = "Transmit" ;

  // Chat
  static const int    N_STATIC_CHATLIST_CHILDREN = 2 ; // ASSERT: num ChatList static widgets
  static const int    SCROLLBAR_W                = 12 ;
  static const int    CHATLIST_W                 = 128 ;
  static const int    CHATLIST_X                 = CHATLIST_W + SCROLLBAR_W + PAD8 + PAD ;
  static const int    CHATLIST_Y                 = PAD8 + PAD ;
  static const int    OFFSET_CHATLIST_X          = CHATLIST_X + SCROLLBAR_W + PAD ;
  static const int    EMPTY_CHATLIST_H           = 24 ;
  static const int    CHATLIST_ITEM_H            = 24 ;
  static const int    CHATLIST_ITEM_W            = CHATLIST_W - PAD6 ;
  static const int    PADDED_CHATLIST_ITEM_H     = CHATLIST_ITEM_H + PAD ;
  static const int    FONT_SIZE                  = 16 ;
  static const String CHAT_GROUP_TITLE           = "Chat" ;
  static const String CHAT_PROMPT_TEXT           = "<type some chat here - then press ENTER key to send>" ;
  static const String CONNECTING_TEXT            = "(connecting)" ;
  static const String CLIENT_NICK                = "AvCaster" ;
  static const String SERVER_NICK                = "SERVER" ;
  static const String IRC_USER_PREFIX            = "IRC" ;
  static const String LCTV_USER_PREFIX           = "LCTV" ;

  // Config
  static const String SCREEN_GROUP_TEXT      = "Screen" ;
  static const String CAMERA_GROUP_TEXT      = "Camera" ;
  static const String AUDIO_GROUP_TEXT       = "Audio" ;
  static const String TEXT_GROUP_TEXT        = "Text" ;
  static const String IMAGE_GROUP_TEXT       = "Image" ;
  static const String OUTPUT_GROUP_TEXT      = "Output" ;
  static const String CHAT_GROUP_TEXT        = "Chat" ;
  static const String DELETE_BTN_CANCEL_TEXT = "Cancel" ;
  static const String DELETE_BTN_DELETE_TEXT = "Delete" ;
  static const String DELETE_BTN_RESET_TEXT  = "Reset" ;
  static const String IMAGE_CHOOSER_TEXT     = "Select an image file ..." ;
  static const String DEST_FILE_TEXT         = "Location:" ;
  static const String DEST_RTMP_TEXT         = "URI:" ;
  static const String DEST_LCTV_TEXT         = "Stream Key:" ;
  static const String IMG_FILE_EXTENSIONS    = "*" + APP::PNG_FILE_EXT ;
//   static const String IMG_FILE_EXTS          = "*" + APP::PNG_FILE_EXT  + ",*" +
//                                                      APP::JPEG_FILE_EXT + ",*" +
//                                                      APP::GIF_FILE_EXT         ;
  static const double MIN_DISPLAY_N    = 0.0 ;
  static const double MAX_DISPLAY_N    = 4.0 ;
  static const double MIN_SCREEN_N     = 0.0 ;
  static const double MAX_SCREEN_N     = 4.0 ;
  static const double MIN_N_CHANNELS   = 0.0 ;
  static const double MAX_N_CHANNELS   = 2.0 ;
  static const int    MAX_RES_N_CHARS  = 4 ;
  static const int    MAX_MOTD_LEN     = 2048 ;
  static const int    MAX_FILENAME_LEN = 255 ;
  static const int    MAX_PORT_N_CHARS = 5 ;

  // StatusBar
  static const String INIT_STATUS_TEXT  = "Initializing" ;
  static const String READY_STATUS_TEXT = "Ready" ;

  // Alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
  static const String    MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

  // user error messages
  static const String GST_INSUFFICIENT_ERROR_MSG  = "Insufficient gStreamer version detected.\n\n"       +
                                                    APP::APP_NAME + " requires gStreamer v"              +
                                                    String(GST::MIN_MAJOR_VERSION) + "."                 +
                                                    String(GST::MIN_MINOR_VERSION) + " or greater.\n\n"  +
                                                    "See the README.md for detailed build instructions." ;
  static const String IRC_INSUFFICIENT_ERROR_MSG  = "Insufficient libircclient version detected.\n\n"    +
                                                    APP::APP_NAME + " requires libircclient v"           +
                                                    String(IRC::MIN_MAJOR_VERSION) + "."                 +
                                                    String(IRC::MIN_MINOR_VERSION) + " or greater.\n\n"  +
                                                    "See the README.md for detailed build instructions." ;
  static const String GST_INIT_ERROR_MSG          = "Error initializing gStreamer." ;
  static const String GST_PIPELINE_INST_ERROR_MSG = "Error creating static GstElements." ;
  static const String GST_BUS_INST_ERROR_MSG      = "Error initializing pipelie message handler." ;
  static const String GST_ADD_ERROR_MSG           = "Error adding static GstElements to the pipeline." ;
  static const String GST_PIPELINE_INIT_ERROR_MSG = "Error initializing dynamic GstElements." ;
  static const String GST_CONFIG_ERROR_MSG        = "Error configuring dynamic GstElements." ;
  static const String GST_XWIN_ERROR_MSG          = "Error attaching gStreamer to native x-window." ;
  static const String SCREENCAP_INIT_ERROR_MSG    = "Error creating ScreencapBin GstElements." ;
  static const String CAMERA_INIT_ERROR_MSG       = "Error creating CameraBin GstElements." ;
  static const String TEXT_INIT_ERROR_MSG         = "Error creating TextBin GstElements." ;
  static const String IMAGE_INIT_ERROR_MSG        = "Error creating ImageBin GstElements." ;
  static const String MIXER_INIT_ERROR_MSG        = "Error creating CompositorBin GstElements." ;
  static const String MIXER_PAD_INIT_ERROR_MSG    = "Error creating CompositorBin GstPads." ;
  static const String PREVIEW_INIT_ERROR_MSG      = "Error creating PreviewBin GstElements." ;
  static const String AUDIO_INIT_ERROR_MSG        = "Error creating AudioBin GstElements." ;
  static const String MUXER_INIT_ERROR_MSG        = "Error creating MuxerBin GstElements." ;
  static const String OUTPUT_INIT_ERROR_MSG       = "Error creating OutputBin GstElements." ;
  static const String SCREENCAP_LINK_ERROR_MSG    = "Error linking ScreencapBin GstElements." ;
  static const String CAMERA_LINK_ERROR_MSG       = "Error linking CameraBin GstElements." ;
  static const String TEXT_LINK_ERROR_MSG         = "Error linking TextBin GstElements." ;
  static const String IMAGE_LINK_ERROR_MSG        = "Error linking ImageBin GstElements." ;
  static const String MIXER_LINK_ERROR_MSG        = "Error linking CompositorBin GstElements." ;
  static const String MIXER_PAD_LINK_ERROR_MSG    = "Error linking CompositorBin GstPads." ;
  static const String MIXER_BIN_LINK_ERROR_MSG    = "Error linking CompositorBin to other bins." ;
  static const String PREVIEW_LINK_ERROR_MSG      = "Error linking PreviewBin GstElements." ;
  static const String AUDIO_LINK_ERROR_MSG        = "Error linking AudioBin GstElements." ;
  static const String MUXER_LINK_ERROR_MSG        = "Error linking MuxerBin GstElements." ;
  static const String MUXER_BIN_LINK_ERROR_MSG    = "Error linking MuxerBin to other bins." ;
  static const String OUTPUT_LINK_ERROR_MSG       = "Error linking OutputBin GstElements." ;
  static const String GST_STATE_ERROR_MSG         = "Invalid configuration." ;
  static const String STORAGE_WRITE_ERROR_MSG     = "I/O error storing configuration." ;
  static const String PRESET_NAME_ERROR_MSG       = "Enter a name for this preset in the \"Preset\" box or press the \"Cancel\" button." ;
  static const String PRESET_RENAME_ERROR_MSG     = "A preset already exists with that name." ;
  static const String CONFIG_INVALID_ERROR_MSG    = "Invalid paramenter(s) - correct the errors indicated in red." ;
  static const String ALSA_INIT_ERROR_MSG         = "Error initializing ALSA capture device.\n\n" ;
  static const String PULSE_INIT_ERROR_MSG        = "Error connecting to PulseAudio server.\n\n" ;
  static const String JACK_INIT_ERROR_MSG         = "Error connecting to Jack server.\n\n" ;
  static const String FILE_SINK_ERROR_MSG         = "Error creating local output file.\n\n" ;

  // Config label texts
  static const String DISPLAY_N_LABEL   = "Display #:" ;
  static const String SCREEN_N_LABEL    = "Screen #:" ;
  static const String SCREEN_W_LABEL    = "Width:" ;
  static const String SCREEN_H_LABEL    = "Height:" ;
  static const String X_OFFSET_LABEL    = "Offset X:" ;
  static const String Y_OFFSET_LABEL    = "Offset Y:" ;
  static const String CAMERA_DEV_LABEL  = "Device:" ;
  static const String CAMERA_RES_LABEL  = "Resolution:" ;
  static const String AUDIO_API_LABEL   = "Interface:" ;
  static const String AUDIO_DEV_LABEL   = "Device:" ;
  static const String AUDIO_CODEC_LABEL = "Codec:" ;
  static const String N_CHANNELS_LABEL  = "Channels:" ;
  static const String SAMPLERATE_LABEL  = "Samplerate:" ;
  static const String AUDIO_RATE_LABEL  = "Bitrate:" ;
  static const String MOTD_LABEL        = "Message:" ;
  static const String TEXT_STYLE_LABEL  = "Style:" ;
  static const String TEXT_POS_LABEL    = "Position:" ;
  static const String IMAGE_LOC_LABEL   = "Location:" ;
  static const String IMAGE_BTN_LABEL   = "Browse:" ;
  static const String OUTPUT_SINK_LABEL = "Stream:" ;
  static const String OUTPUT_W_LABEL    = "Width:" ;
  static const String OUTPUT_H_LABEL    = "Height:" ;
  static const String FRAMERATE_LABEL   = "FPS:" ;
  static const String VIDEO_RATE_LABEL  = "Bitrate:" ;
  static const String OUTPUT_DEST_LABEL = "Destination:" ;
  static const String NETWORK_LABEL     = "Host:" ;
  static const String PORT_LABEL        = "Port:" ;
  static const String NICK_LABEL        = "Nick:" ;
  static const String PASS_LABEL        = "Password:" ;
  static const String CHANNEL_LABEL     = "Channel:" ;
  static const String GREETING_LABEL    = "Greeting:" ;
  static const String TIMESTAMP_LABEL   = "Show Timestamps:" ;
  static const String JOINPART_LABEL    = "Show Joins/Parts:" ;

  // Config help texts
  static const String CONFIG_SCREEN_HELP = "The " + SCREEN_GROUP_TEXT + " pane has controls to configure the screen capture." ;
  static const String CONFIG_CAMERA_HELP = "The " + CAMERA_GROUP_TEXT + " pane has controls to configure the camera capture device." ;
  static const String CONFIG_AUDIO_HELP  = "The " + AUDIO_GROUP_TEXT  + " pane has controls to configure the audio capture device." ;
  static const String CONFIG_TEXT_HELP   = "The " + TEXT_GROUP_TEXT   + " pane has controls to configure the text overlay. This may be left empty if overlay text is not desired." ;
  static const String CONFIG_IMAGE_HELP  = "The " + IMAGE_GROUP_TEXT  + " pane has controls to configure the interstitial image. This is a static image that will be shown to viewers when the stream is paused. If this is left empty then the default " + APP::APP_NAME + " splash image will be shown instead." ;
  static const String CONFIG_OUTPUT_HELP = "The " + OUTPUT_GROUP_TEXT + " pane has controls to configure the output stream, either to produce a local video file or to stream to a server over the network." ;
  static const String CONFIG_CHAT_HELP   = "The " + CHAT_GROUP_TEXT   + " pane has controls to configure the chat. These may be left empty if chat is not desired." ;
  static const String DISPLAY_N_HELP     = DISPLAY_N_LABEL   + " Select the X display to capture (usually 0)." ;
  static const String SCREEN_N_HELP      = SCREEN_N_LABEL    + " Select the X screen to capture (usually 0)." ;
  static const String SCREEN_W__HELP     = SCREEN_W_LABEL    + " Specify the width of the area to capture (in pixels)." ;
  static const String SCREEN_H__HELP     = SCREEN_H_LABEL    + " Specify the height of the area to capture (in pixels)." ;
  static const String X_OFFSET_HELP      = X_OFFSET_LABEL    + " Specify the left edge position of the area to capture (in pixels)." ;
  static const String Y_OFFSET_HELP      = Y_OFFSET_LABEL    + " Specify the top edge position of the area to capture (in pixels)." ;
  static const String CAMERA_DEV_HELP    = CAMERA_DEV_LABEL  + " Select the camera device to capture." ;
  static const String CAMERA_RES_HELP    = CAMERA_RES_LABEL  + " Select the camera capture resolution." ;
  static const String AUDIO_API_HELP     = AUDIO_API_LABEL   + " Select the audio driver interface." ;
  static const String AUDIO_DEV_HELP     = AUDIO_DEV_LABEL   + " Select the audio device to capture." ;
  static const String AUDIO_CODEC_HELP   = AUDIO_CODEC_LABEL + " Select the audio encoder." ;
  static const String N_CHANNELS_HELP    = N_CHANNELS_LABEL  + " Specify the number of audio channels to capture." ;
  static const String SAMPLERATE_HELP    = SAMPLERATE_LABEL  + " Select the audio sample rate (22050 is good for voice, 48000 for music)." ;
  static const String AUDIO_RATE_HELP    = AUDIO_RATE_LABEL  + " Select the audio output bit rate (64k per channel is good)." ;
  static const String MOTD_HELP          = MOTD_LABEL        + " Enter the message of the day text." ;
  static const String TEXT_STYLE_HELP    = TEXT_STYLE_LABEL  + " Select still or scrolling text overlay style." ;
  static const String TEXT_POS_HELP      = TEXT_POS_LABEL    + " Select text overlay screen position." ;
  static const String IMAGE_LOC_HELP     = IMAGE_LOC_LABEL   + " Specify the location of the image file." ;
  static const String IMAGE_BTN_HELP     = IMAGE_BTN_LABEL   + " Brwose filesystem for the image file." ;
  static const String OUTPUT_SINK_HELP   = OUTPUT_SINK_LABEL + " Select stream type." ;
  static const String OUTPUT_W__HELP     = OUTPUT_W_LABEL    + " Specify the width of the output stream (in pixels)." ;
  static const String OUTPUT_H__HELP     = OUTPUT_H_LABEL    + " Specify the width of the output stream (in pixels)." ;
  static const String FRAMERATE_HELP     = FRAMERATE_LABEL   + " Select the stream output frame rate (12 is good for screen capture, 30 for video)." ;
  static const String VIDEO_RATE_HELP    = VIDEO_RATE_LABEL  + " Select the stream output bit rate (800k - 1200k is good)." ;
  static const String OUTPUT_DEST_HELP   = OUTPUT_DEST_LABEL + " Specify the local file or stream server URL." ;
  static const String NETWORK_HELP       = NETWORK_LABEL     + " Specify the chat network or host URL." ;
  static const String PORT_HELP          = PORT_LABEL        + " Specify the chat server port." ;
  static const String NICK_HELP          = NICK_LABEL        + " Specify your nickname on the chat network." ;
  static const String PASS_HELP          = PASS_LABEL        + " Specify the server password (this is not your NICKSERV pass)." ;
  static const String CHANNEL_HELP       = CHANNEL_LABEL     + " Specify the channel to auto-join." ;
  static const String GREETING_HELP      = GREETING_LABEL    + " Specify a pounce greeting to all entering chatters." ;
  static const String TIMESTAMP_HELP     = TIMESTAMP_LABEL   + " Show or hide timestamps of chat messages." ;
  static const String JOINPART_HELP      = JOINPART_LABEL    + " Show or hide notices of chatters entering and leaving the channel." ;
  static const String SCREEN_HELP_TEXT   = String("Screen Capture Configuration:\n\n") +
                                           CONFIG_SCREEN_HELP                 + "\n\n" +
                                           DISPLAY_N_HELP                       + "\n" +
                                           SCREEN_N_HELP                        + "\n" +
                                           SCREEN_W__HELP                       + "\n" +
                                           SCREEN_H__HELP                       + "\n" +
                                           X_OFFSET_HELP                        + "\n" +
                                           Y_OFFSET_HELP                               ;
  static const String CAMERA_HELP_TEXT   = String("Camera Device Configuration:\n\n") +
                                           CONFIG_CAMERA_HELP                + "\n\n" +
                                           CAMERA_DEV_HELP                     + "\n" +
                                           CAMERA_RES_HELP                            ;
  static const String AUDIO_HELP_TEXT    = String("Audio Device Configuration:\n\n") +
                                           CONFIG_AUDIO_HELP                + "\n\n" +
                                           AUDIO_API_HELP                     + "\n" +
                                           AUDIO_DEV_HELP                     + "\n" +
                                           AUDIO_CODEC_HELP                   + "\n" +
                                           N_CHANNELS_HELP                    + "\n" +
                                           SAMPLERATE_HELP                    + "\n" +
                                           AUDIO_RATE_HELP                           ;
  static const String TEXT_HELP_TEXT     = String("Text Overlay Configuration:\n\n") +
                                           CONFIG_TEXT_HELP                 + "\n\n" +
                                           MOTD_HELP                          + "\n" +
                                           TEXT_STYLE_HELP                    + "\n" +
                                           TEXT_POS_HELP                             ;
  static const String IMAGE_HELP_TEXT    = String("Interstitial Configuration:\n\n") +
                                           CONFIG_IMAGE_HELP                + "\n\n" +
                                           IMAGE_LOC_HELP                     + "\n" +
                                           IMAGE_BTN_HELP                            ;
  static const String OUTPUT_HELP_TEXT   = String("Output Stream Configuration:\n\n") +
                                           CONFIG_OUTPUT_HELP                + "\n\n" +
                                           OUTPUT_SINK_HELP                    + "\n" +
                                           OUTPUT_W__HELP                      + "\n" +
                                           OUTPUT_H__HELP                      + "\n" +
                                           FRAMERATE_HELP                      + "\n" +
                                           VIDEO_RATE_HELP                     + "\n" +
                                           OUTPUT_DEST_HELP                           ;
  static const String CHAT_HELP_TEXT     = String("Chat Configuration:\n\n") +
                                           CONFIG_CHAT_HELP         + "\n\n" +
                                           NETWORK_HELP               + "\n" +
                                           PORT_HELP                  + "\n" +
                                           NICK_HELP                  + "\n" +
                                           PASS_HELP                  + "\n" +
                                           CHANNEL_HELP               + "\n" +
                                           GREETING_HELP              + "\n" +
                                           TIMESTAMP_HELP             + "\n" +
                                           JOINPART_HELP                     ;
}

#endif // _CONSTANTS_H_
