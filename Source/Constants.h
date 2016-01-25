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
#define TEXT_BIN_NYI  1
#define IMAGE_BIN_NYI 1
#define DISABLE_GUI_CONFIG_NYI
#define DISABLE_AUDIO   (! JUCE_LINUX) // replace audio-real-source with fakesrc
#define DISABLE_CHAT                   // TODO: add 'ircclient' dep back to jucer
#define DISABLE_PREVIEW (! JUCE_LINUX) // replace preview-sink with fakesink
//#define DISABLE_OUTPUT               // replace filesink or rtmpsink with fakesink
// #define SUPRESS_ALERTS

// debugging tweaks and kludges
#define INJECT_DEFAULT_CAMERA_DEVICE_INFO
#define FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
#define NATIVE_CAMERA_RESOLUTION_ONLY
// #define PREFIX_CHAT_NICKS
#define STATIC_PIPELINE
// #define FAKE_MUX_ENCODER_SRC_AND_SINK // isolate compositor from encoder and muxer from output

// enable tracing
#ifdef DEBUG
#  define DEBUG_TRACE 1
#else // DEBUG
#  define DEBUG_TRACE 1
#endif // DEBUG
#define DEBUG_TRACE_EVENTS (DEBUG_TRACE && 1)
#define DEBUG_TRACE_GUI    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_MEDIA  (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CONFIG (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CHAT   (DEBUG_TRACE && 0)
#define DEBUG_TRACE_STATE  (DEBUG_TRACE && 1)
#define DEBUG_TRACE_VB     (DEBUG_TRACE && 0)

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
  static const String JACK_CLIENT_NAME = APP_NAME ;
  static const String IRC_THREAD_NAME  = "av-caster-irc" ;
  static const String DIGITS           = "0123456789" ;
  static const String LETTERS          = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
  static const String ALPHANUMERIC     = DIGITS + LETTERS ;
  static const String VALID_ID_CHARS   = ALPHANUMERIC + "_- " ;
  static const String VALID_URI_CHARS  = ALPHANUMERIC + "_-.:/?=@#& " ;
  static const String VALID_NICK_CHARS = ALPHANUMERIC + "_-@#&[] " ;
  static const String FILTER_CHARS     = "_-.:/?=@#&[] " ;
  static const String REPLACE_CHARS    = String::repeatedString("-" , FILTER_CHARS.length()) ;

  // timers
  static const int N_TIMERS             = 3 ;
  static const int TIMER_HI_ID          = 1 ; static const int TIMER_HI_IVL  = 125 ;
  static const int TIMER_MED_ID         = 2 ; static const int TIMER_MED_IVL = 500 ;
  static const int TIMER_LO_ID          = 3 ; static const int TIMER_LO_IVL  = 1000 ;
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
  static const String CLI_USAGE_MSG   = "AvCaster Usage:\n\n\tav-caster [ " + CLI_HELP_TOKEN            + " | "                                                          +
                                                                              CLI_PRESETS_TOKEN         + " | "                                                          +
                                                                              CLI_VERSION_TOKEN         + " ]"                                                           +
                                                       "\n\n\tav-caster [ " + CLI_PRESET_TOKEN          + " n    ] "                                                     +
                                                         "\n\t          [ " + CLI_DISABLE_MEDIA_TOKEN   + "    ] "                                                       +
                                                                       "[ " + CLI_DISABLE_PREVIEW_TOKEN + "  ] "                                                         +
                                                                       "[ " + CLI_DISABLE_AUDIO_TOKEN   + "  ] "                                                         +
                                                                       "[ " + CLI_DISABLE_CHAT_TOKEN    + "    ]"                                                        +
                                                         "\n\t          [ " + CLI_SCREEN_ONLY_TOKEN     + " | "                                                          +
                                                                       "  " + CLI_CAMERA_ONLY_TOKEN     + " | "                                                          +
//                                                                        "  " + CLI_TEXT_ONLY_TOKEN       + " | "                                                          +
//                                                                        "  " + CLI_IMAGE_ONLY_TOKEN      + " ] "                                                          +
                                                     "\n\n\n\tINFORMATION:"                                                                                              +
                                                     "\n\n\t\t"             + CLI_HELP_TOKEN            + "\n\t\t\tprints this message and exits"                        +
                                                     "\n\n\t\t"             + CLI_PRESETS_TOKEN         + "\n\t\t\tlist stored presets and exits"                        +
                                                     "\n\n\t\t"             + CLI_VERSION_TOKEN         + "\n\t\t\tprints the application version string and exits"      +
                                                     "\n\n\n\tCONFIGURATION:"                                                                                            +
                                                     "\n\n\t\t"             + CLI_PRESET_TOKEN + " n"   + "\n\t\t\tstarts " + APP_NAME + " with initial preset number n" +
                                                     "\n\n\n\tFEATURE SWITCHES:"                                                                                         +
                                                     "\n\n\t\t"             + CLI_DISABLE_MEDIA_TOKEN   + "\n\t\t\tdisables all media and stream output"                 +
                                                     "\n\n\t\t"             + CLI_SCREEN_ONLY_TOKEN     + "\n\t\t\tdisables compositing and uses screen capture only"    +
                                                     "\n\n\t\t"             + CLI_CAMERA_ONLY_TOKEN     + "\n\t\t\tdisables compositing and uses webcam capture only"    +
//                                                      "\n\n\t\t"             + CLI_TEXT_ONLY_TOKEN       + "\n\t\t\tdisables compositing and uses text overlay only"      +
//                                                      "\n\n\t\t"             + CLI_IMAGE_ONLY_TOKEN      + "\n\t\t\tdisables compositing and uses static image only"      +
                                                     "\n\n\t\t"             + CLI_DISABLE_PREVIEW_TOKEN + "\n\t\t\tdisables realtime preview"                            +
                                                     "\n\n\t\t"             + CLI_DISABLE_AUDIO_TOKEN   + "\n\t\t\tdisables audio capture"                               +
                                                     "\n\n\t\t"             + CLI_DISABLE_CHAT_TOKEN    + "\n\t\t\tdisables chat"                                        ;

// NOTE: INPUTS are either mutually exclusive (compositor disabled) or must all be enabled (compositor enabled)
//       N_COMPOSITOR_INPUTS is coupled to AvCaster::Is*Enabled flags in AvCaster::ProcessCliParams()
#define INPUTS String(APP::CLI_SCREEN_ONLY_TOKEN + newLine + APP::CLI_CAMERA_ONLY_TOKEN + \
               String((TEXT_BIN_NYI ) ? "" :       newLine + APP::CLI_TEXT_ONLY_TOKEN)  + \
               String((IMAGE_BIN_NYI) ? "" :       newLine + APP::CLI_IMAGE_ONLY_TOKEN) )
  static const int N_COMPOSITOR_INPUTS = StringArray::fromLines(INPUTS).size() ;

  // filesystem
  static const File   HOME_DIR        = File::getSpecialLocation(File::userHomeDirectory           ) ;
  static const File   APPDATA_DIR     = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  static const File   VIDEOS_DIR      = File::getSpecialLocation(File::userMoviesDirectory         ) ;
  static const File   CAMERAS_DEV_DIR = File("/sys/class/video4linux") ;
  static const String PNG_FILE_EXT    = ".png" ;
  static const String IMG_FILE_EXTS   = "*" + APP::PNG_FILE_EXT + ",*" + APP::PNG_FILE_EXT ;
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
  static const int    TITLEBAR_H      = 24 ;
  static const int    TITLEBAR_BTNS   = DocumentWindow::minimiseButton | DocumentWindow::closeButton ;
  static const String IDLE_TITLE_TEXT = "(Idle)" ;
  static const String FILE_TITLE_TEXT = "(Recording)" ;
  static const String RTMP_TITLE_TEXT = "(Broadcasting)" ;

  // Controls
  static const String FILE_XMIT_TEXT = "Record" ;
  static const String RTMP_XMIT_TEXT = "Transmit" ;

  // Chat
  static const int    N_STATIC_CHATLIST_CHILDREN = 2 ;
  static const int    SCROLLBAR_W                = 12 ;
  static const int    CHATLIST_W                 = 128 ;
  static const int    CHATLIST_X                 = CHATLIST_W + SCROLLBAR_W + PAD8 + PAD ;
  static const int    CHATLIST_Y                 = PAD8 + PAD ;
  static const int    OFFSET_CHATLIST_X          = CHATLIST_X + SCROLLBAR_W + PAD ;
  static const int    EMPTY_CHATLIST_H           = 24 ;
  static const int    CHATLIST_ITEM_H            = 24 ;
  static const int    CHATLIST_ITEM_W            = CHATLIST_W - PAD6 ;
  static const int    PADDED_CHATLIST_ITEM_H     = CHATLIST_ITEM_H + PAD ;
  static const String CHAT_GROUP_TITLE           = "Chat" ;
  static const String CHAT_PROMPT_TEXT           = "<type some chat here - then press ENTER key to send>" ;
  static const String CLIENT_NICK                = "AvCaster" ;
  static const String SERVER_NICK                = "SERVER" ;
  static const String IRC_USER_PREFIX            = "IRC" ;
  static const String LCTV_USER_PREFIX           = "LCTV" ;

  // Config
  static const String DELETE_BTN_CANCEL_TEXT = "Cancel" ;
  static const String DELETE_BTN_DELETE_TEXT = "Delete" ;
  static const String DELETE_BTN_RESET_TEXT  = "Reset" ;
  static const int    MAX_RES_N_CHARS        = 4 ;
  static const int    MAX_MOTD_LEN           = 2048 ;
  static const int    MAX_FILENAME_LEN       = 255 ;
  static const String IMAGE_CHOOSER_TEXT     = "Select an image file ..." ;
  static const String DEST_FILE_TEXT         = "Location:" ;
  static const String DEST_RTMP_TEXT         = "URI:" ;
  static const String DEST_LCTV_TEXT         = "Stream Key:" ;
  static const int    MAX_PORT_N_CHARS       = 5 ;

  // StatusBar
  static const String INIT_STATUS_TEXT  = "Initializing" ;
  static const String READY_STATUS_TEXT = "Ready" ;

  // alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
  static const String    MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

  // user error messages
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
  static const String PRESET_NAME_ERROR_MSG       = "Enter a name for this preset in the \"Preset\" box then press \"Save\" again." ;
  static const String PRESET_RENAME_ERROR_MSG     = "A preset already exists with that name." ;
  static const String CONFIG_INVALID_ERROR_MSG    = "Invalid paramenter(s) - correct the errors indicated in red." ;
  static const String CONFIG_CHANGE_ERROR_MSG     = "Can not re-configure while the stream is active." ;
  static const String ALSA_INIT_ERROR_MSG         = "Error initializing ALSA capture device.\n\n" ;
  static const String PULSE_INIT_ERROR_MSG        = "Error connecting to PulseAudio server.\n\n" ;
  static const String JACK_INIT_ERROR_MSG         = "Error connecting to Jack server.\n\n" ;
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
|*|    * if new property        -> define *_ID and DEFAULT_* below
|*|                             -> add default property to DefaultStore
|*|                             -> sanitize data in AvCasterStore::sanitize*ParentNode*()
|*|    * if new node            -> add default node to DefaultStore
|*|                             -> verify schema in new method AvCasterStore::verifyNewNode()
|*|                             -> sanitize data in AvCasterStore::sanitize*NewNode*()
|*|    * if new root property   -> verify schema in AvCasterStore::verifyRoot()
|*|    * if new preset property -> verify schema in AvCasterStore::verifyPreset()
|*|                             -> add instance var and definition in PresetSeed class
\*/

/*\ SCHEMA:
|*|
|*| // AvCasterStore->root
|*| STORAGE_ID:
|*| {
|*|   // config root IDs
|*|   CONFIG_VERSION_ID: a_double                              ,
|*|   IS_PENDING_ID:     a_bool                                ,
|*|   PRESET_ID:         an_int                                ,
|*|   PRESETS_ID:        [ a-config-id: a_config_node , .... ] // config nodes as below
|*| }
|*|
|*| // AvCasterStore->config
|*| // AvCasterStore->presets (each child)
|*| // Gstreamer::ConfigStore
|*| VOLATILE_CONFIG_ID:
|*| {
|*|   // control IDs
|*|   PRESET_NAME_ID:         a_string ,
|*|   SCREENCAP_ID:           a_bool   ,
|*|   CAMERA_ID:              a_bool   ,
|*|   TEXT_ID:                a_bool   ,
|*|   IMAGE_ID:               a_bool   ,
|*|   PREVIEW_ID:             a_bool   ,
|*|   AUDIO_ID:               a_bool   ,
|*|   OUTPUT_ID:              a_bool   ,
|*|   // screen IDs
|*|   DISPLAY_N_ID:           an_int   ,
|*|   SCREEN_N_ID:            an_int   ,
|*|   SCREENCAP_W_ID:         an_int   ,
|*|   SCREENCAP_H_ID:         an_int   ,
|*|   OFFSET_X_ID:            an_int   ,
|*|   OFFSET_Y_ID:            an_int   ,
|*|   // camera IDs
|*|   CAMERA_DEV_ID:          an_int   ,
|*|   CAMERA_RES_ID:          an_int   ,
|*|   // audio IDs
|*|   AUDIO_API_ID:           an_int   ,
|*|   AUDIO_DEVICE_ID:        an_int   ,
|*|   AUDIO_CODEC_ID:         an_int   ,
|*|   N_CHANNELS_ID:          an_int   ,
|*|   SAMPLERATE_ID:          an_int   ,
|*|   AUDIO_BITRATE_ID:       an_int   ,
|*|   // text IDs
|*|   MOTD_TEXT_ID:           a_string ,
|*|   TEXT_STYLE_ID:          an_int   ,
|*|   TEXT_POSITION_ID:       an_int   ,
|*|   // image IDs
|*|   IMAGE_LOC_ID:           a_string ,
|*|   // output IDs
|*|   OUTPUT_SINK_ID:         an_int   ,
|*|   OUTPUT_MUXER_ID:        an_int   ,
|*|   OUTPUT_W_ID:            an_int   ,
|*|   OUTPUT_H_ID:            an_int   ,
|*|   FRAMERATE_ID:           an_int   ,
|*|   VIDEO_BITRATE_ID:       an_int   ,
|*|   OUTPUT_DEST_ID:         a_string
|*| }
|*|
|*| // AvCasterStore->cameras
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
|*| // AvCasterStore->audios
|*| AUDIO_DEVICES_ID: [] // nyi
|*|
|*| // AvCasterStore->servers
|*| SERVERS_ID: [ a_server  , ... ] // a_server as below
|*|
|*| // a_server
|*| server-id:
|*| {
|*|   HOST_ID:     a_string
|*|   PORT_ID:     an_int
|*|   CHANNEL_ID:  a_string
|*|   CHATTERS_ID: [ a_chatter , ... ] // a_chatter as below
|*| }
|*|
|*| // a_chatter
|*| user-id:                 // e.g. "-fred-stone" via FilterId("@fred stone")
|*| {
|*|   CHAT_NICK_ID: a_string // e.g. "@fred stone"
|*| }
\*/


  static Identifier FilterId(String a_string , String retain_chars)
  {
    return a_string.retainCharacters(retain_chars)
                   .toLowerCase()
                   .replaceCharacters(APP::FILTER_CHARS , APP::REPLACE_CHARS) ;
  }


  // config indices
  enum              StaticPreset       { FILE_PRESET_IDX , RTMP_PRESET_IDX , LCTV_PRESET_IDX } ;
  enum              AudioApi           { ALSA_AUDIO_IDX , PULSE_AUDIO_IDX , JACK_AUDIO_IDX } ;
  enum              AudioCodec         { MP3_AUDIO_IDX , AAC_AUDIO_IDX } ;
  enum              OutputStream       { FILE_OUTPUT_IDX , RTMP_OUTPUT_IDX } ;
  static const int  CONFIG_IDX_INVALID = -1 ;

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

  // nodes
  static const Identifier STORAGE_ID             = "av-caster-config" ;
  static const Identifier PRESETS_ID             = "presets" ;
  static const Identifier VOLATILE_CONFIG_ID     = "volatile-config" ;
  static const Identifier CAMERA_DEVICES_ID      = "camera-devices" ;
  static const Identifier AUDIO_DEVICES_ID       = "audio-devices" ;
  static const Identifier SERVERS_ID             = "irc-servers" ;
  // config root IDs
  static const Identifier CONFIG_VERSION_ID     = "config-version" ;
  static const Identifier PRESET_ID             = "current-preset-idx" ;
  static const Identifier IS_PENDING_ID         = "is-config-pending" ;
  // control IDs
  static const Identifier PRESET_NAME_ID        = "preset-name" ;
  static const Identifier SCREENCAP_ID          = "is-screencap-on" ;
  static const Identifier CAMERA_ID             = "is-camera-on" ;
  static const Identifier TEXT_ID               = "is-text-on" ;
  static const Identifier PREVIEW_ID            = "is-preview-on" ;
  static const Identifier AUDIO_ID              = "is-audio-on" ;
  static const Identifier IMAGE_ID              = "is-interstitial-on" ;
  static const Identifier OUTPUT_ID             = "is-output-on" ;
  // screen IDs
  static const Identifier DISPLAY_N_ID          = "display-n" ;
  static const Identifier SCREEN_N_ID           = "screen-n" ;
  static const Identifier SCREENCAP_W_ID        = "sceencap-w" ;
  static const Identifier SCREENCAP_H_ID        = "sceencap-h" ;
  static const Identifier OFFSET_X_ID           = "offset-x" ;
  static const Identifier OFFSET_Y_ID           = "offset-y" ;
  // camera IDs
  static const Identifier CAMERA_DEVICE_ID      = "camera-dev-idx" ;
  static const Identifier CAMERA_RES_ID         = "camera-res-idx" ;
  static const Identifier CAMERA_PATH_ID        = "camera-dev-path" ;
  static const Identifier CAMERA_NAME_ID        = "camera-dev-name" ;
  static const Identifier CAMERA_RATE_ID        = "camera-framerate" ;
  static const Identifier CAMERA_RESOLUTIONS_ID = "camera-resolutions" ;
  // audio IDs
  static const Identifier AUDIO_API_ID          = "audio-api-idx" ;
  static const Identifier AUDIO_DEVICE_ID       = "audio-dev-idx" ;
  static const Identifier AUDIO_CODEC_ID        = "audio-codec-idx" ;
  static const Identifier N_CHANNELS_ID         = "n-channels" ;
  static const Identifier SAMPLERATE_ID         = "samplerate-idx" ;
  static const Identifier AUDIO_BITRATE_ID      = "audio-bitrate-idx" ;
  // text IDs
  static const Identifier MOTD_TEXT_ID          = "motd-text" ;
  static const Identifier TEXT_STYLE_ID         = "text-style-idx" ;
  static const Identifier TEXT_POSITION_ID      = "text-pos-idx" ;
  // interstitial IDs
  static const Identifier IMAGE_LOC_ID          = "interstitial-img" ;
  // output IDs
  static const Identifier OUTPUT_SINK_ID        = "output-sink-idx" ;
  static const Identifier OUTPUT_MUXER_ID       = "output-muxer-idx" ;
  static const Identifier OUTPUT_W_ID           = "output-w" ;
  static const Identifier OUTPUT_H_ID           = "output-h" ;
  static const Identifier FRAMERATE_ID          = "framerate-idx" ;
  static const Identifier VIDEO_BITRATE_ID      = "video-bitrate-idx" ;
  static const Identifier OUTPUT_DEST_ID        = "output-dest" ;
  // chat IDs
  static const Identifier HOST_ID                = "chat-host" ;
  static const Identifier PORT_ID                = "chat-port" ;
// TODO: replace this with NICK_ID
  static const Identifier CHAT_NICK_ID           = "chat-nick" ;
  static const Identifier NICK_ID                = "chat-nick" ;
  static const Identifier PASS_ID                = "chat-pass" ;
  static const Identifier CHANNEL_ID             = "chat-channel" ;
  static const Identifier GREETING_ID            = "chat-greeting" ;
  static const Identifier JOINPART_ID            = "show-joins-parts" ;
  static const Identifier CHATTERS_ID            = "active-chatters" ;

  // root defaults
#if JUCE_LINUX
  static const String     STORAGE_DIRNAME             = ".config/av-caster/" ;
  static const String     STORAGE_FILENAME            = "av-caster.bin" ;
#endif // JUCE_LINUX
#if JUCE_WINDOWS
  static const String     STORAGE_DIRNAME             = "AvCaster\\" ;
  static const String     STORAGE_FILENAME            = "AvCaster.bin" ;
#endif // JUCE_WINDOWS
  static const double     CONFIG_VERSION              = 0.3 ;
  static const int        DEFAULT_PRESET_IDX          = FILE_PRESET_IDX ; // ASSERT: must be 0
  static const int        N_STATIC_PRESETS            = 3 ; // ASSERT: num PresetSeed subclasses
  static const bool       DEFAULT_IS_PENDING          = false ;

  // control defaults
  static const String     FILE_PRESET_NAME            = "Local File" ;
  static const String     RTMP_PRESET_NAME            = "RTMP Server" ;
  static const String     LCTV_PRESET_NAME            = "livecoding.tv" ;
  static const String     DEFAULT_PRESET_NAME         = FILE_PRESET_NAME ;
  static const Identifier DEFAULT_PRESET_ID           = FilterId(DEFAULT_PRESET_NAME , APP::VALID_ID_CHARS) ;
#ifdef DISABLE_GUI_CONFIG_NYI
  static const bool       DEFAULT_IS_SCREENCAP_ACTIVE = true ;
#else // DISABLE_GUI_CONFIG_NYI
  static const bool       DEFAULT_IS_SCREENCAP_ACTIVE = false ;
#endif // DISABLE_GUI_CONFIG_NYI
  static const bool       DEFAULT_IS_CAMERA_ACTIVE    = false ;
  static const bool       DEFAULT_IS_TEXT_ACTIVE      = false ;
  static const bool       DEFAULT_IS_IMAGE_ACTIVE     = true ;
  static const bool       DEFAULT_IS_PREVIEW_ACTIVE   = true ;
  static const bool       DEFAULT_IS_AUDIO_ACTIVE     = false ;
  static const bool       DEFAULT_IS_OUTPUT_ACTIVE    = false ;
  // screen defaults
  static const int        DEFAULT_DISPLAY_N           = 0 ;
  static const int        DEFAULT_SCREEN_N            = 0 ;
  static const int        DEFAULT_SCREENCAP_W         = 640 ;
  static const int        DEFAULT_SCREENCAP_H         = 480 ;
  static const int        DEFAULT_OFFSET_X            = 0 ;
  static const int        DEFAULT_OFFSET_Y            = 0 ;
  // camera defaults
  static const int        DEFAULT_CAMERA_DEVICE_IDX   = -1 ;
  static const int        DEFAULT_CAMERA_RES_IDX      = -1 ;
  static const int        DEFAULT_CAMERA_RATE         = 30 ;
  // audio defaults
  static const int        DEFAULT_AUDIO_API_IDX       = ALSA_AUDIO_IDX ;
  static const int        DEFAULT_AUDIO_DEVICE_IDX    = -1 ;
  static const int        DEFAULT_AUDIO_CODEC_IDX     = MP3_AUDIO_IDX ;
  static const int        DEFAULT_N_CHANNELS          = 2 ;
  static const int        DEFAULT_SAMPLERATE_IDX      = 0 ;
  static const int        DEFAULT_AUDIO_BITRATE_IDX   = 0 ;
  // text defaults
  static const String     DEFAULT_MOTD_TEXT           = "" ;
  static const int        DEFAULT_TEXT_STYLE_IDX      = 0 ;
  static const int        DEFAULT_TEXT_POSITION_IDX   = 0 ;
  // interstitial defaults
  static const String     DEFAULT_IMAGE_LOCATION      = "" ;
  // output defaults
  static const int        DEFAULT_OUTPUT_SINK_IDX     = FILE_OUTPUT_IDX ;
  static const int        DEFAULT_OUTPUT_MUXER_IDX    = 0 ;
  static const int        DEFAULT_OUTPUT_W            = 640 ;
  static const int        DEFAULT_OUTPUT_H            = 480 ;
  static const int        DEFAULT_FRAMERATE_IDX       = 0 ;
  static const int        DEFAULT_VIDEO_BITRATE_IDX   = 0 ;
  static const String     DEFAULT_OUTPUT_DEST         = APP::APP_NAME + ".flv" ;


  static ValueTree DefaultStore()
  {
    ValueTree default_store = ValueTree(STORAGE_ID) ;
    default_store.setProperty(CONFIG_VERSION_ID , CONFIG_VERSION     , nullptr) ;
    default_store.setProperty(IS_PENDING_ID     , DEFAULT_IS_PENDING , nullptr) ;
    default_store.setProperty(PRESET_ID         , DEFAULT_PRESET_IDX , nullptr) ;
    default_store.addChild   (ValueTree(PRESETS_ID) , -1 , nullptr) ;
    default_store.addChild   (ValueTree(SERVERS_ID) , -1 , nullptr) ;

    return default_store ;
  }
}


/** the GUI namespace defines configuration and runtime constants
        pertaining to the gStreamer media backend                 */
namespace GST
{
  static const unsigned int MIN_MAJOR_VERSION = 1 ;
  static const unsigned int MIN_MINOR_VERSION = 4 ;

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
}


/** the IRC namespace defines configuration constants
        pertaining to the libircclient network backend */
namespace IRC
{
  static const unsigned int MIN_MAJOR_VERSION = 1 ;
  static const unsigned int MIN_MINOR_VERSION = 8 ;

  // IDs
  static const char*  ROOT_CHANNEL = "&bitlbee" ;
  static const String ROOT_USER    = "root!root@" ;
  static const char*  ROOT_NICK    = "@root" ;
  static const String IDENTIFY_CMD = "identify " ;

  // incoming server messages
  static const char*  CONNECTED_MSG       = "Logging in: Logged in" ;
  static const String BITLBEE_WELCOME_MSG = "Welcome to the BitlBee gateway, " ;
  static const char*  LOGIN_BLOCKED_MSG   = "New request: You're already connected to this server. Would you like to take over this session?" ;
  static const char*  KICKED_SELF_MSG     = "You've successfully taken over your old session" ;

  // GUI display messages
  static const String SESSION_BLOCKED_MSG = "It appeaers that you are already connected to BitlBee with another client.  This chat will not be connected to LCTV." ;
  static const String LOGGING_IN_MSG      = "Logging into chat server: " ;
  static const String LOGGED_IN_MSG       = "Logged into chat server: " ;
  static const char*  LOGIN_MSG           = CHARSTAR(String(APP::APP_NAME + " starting up")) ;
  static const char*  LOGOOUT_MSG         = CHARSTAR(String(APP::APP_NAME + " shutting down")) ;

  // URIS
  static const String      LCTV_URL        = "https://www.livecoding.tv/" ;
  static const String      OFTC_TLD        = "oftc.net" ;
  static const String      OFTC_URI        = "irc.oftc.net" ;
  static const String      DEBIAN_URI      = "irc.debian.org" ;
  static const StringArray OFTC_ALIAS_URIS = StringArray::fromLines(OFTC_URI   + newLine +
                                                                    DEBIAN_URI           ) ;
}

#endif // _CONSTANTS_H_
