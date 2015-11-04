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


#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// enable standard features
// #  define DISPLAY_ALERTS
#  define CONFIGURE_TEXT_BIN         0
#  define CONFIGURE_INTERSTITIAL_BIN 0
#  define CONFIGURE_OUTPUT_BIN       1

// debugging tweaks and kludges
#  define INJECT_DEFAULT_CAMERA_DEVICE_INFO
#  define FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
// #  define FAUX_SCREEN                   // replace sceen-real-source with fakesrc
// #  define FAUX_CAMERA                   // replace camera-real-source with fakesrc
// #  define FAUX_AUDIO                    // replace audio-real-source with fakesrc
// #  define FAUX_PREVIEW                  // replace composite-sink with fakesink
// #  define FAUX_OUTPUT                   // replace filesink or rtmpsink
// #  define FAKE_MUX_ENCODER_SRC_AND_SINK // isolate compositor from encoder and muxer from output


// enable debug features
#ifdef DEBUG
#  define DEBUG_ANSI_COLORS
// #  define DEBUG_QUIT_IMMEDIATELY
#endif // DEBUG


// tracing
#ifdef DEBUG
#  define DEBUG_DEFINED 1
#else // DEBUG
#  define DEBUG_DEFINED 0
#endif // DEBUG
#define DEBUG_TRACE        DEBUG_DEFINED && 1
#define DEBUG_TRACE_EVENTS DEBUG_DEFINED && 1
#define DEBUG_TRACE_GUI    DEBUG_DEFINED && 1
#define DEBUG_TRACE_CONFIG DEBUG_DEFINED && 1
#define DEBUG_TRACE_STATE  DEBUG_DEFINED && 1
#define DEBUG_TRACE_VB     DEBUG_DEFINED && 0


#include "JuceHeader.h"


/** the APP namespace defines configuration and runtime constants
        pertaining to the core AvCaster application and business logic */
namespace APP
{
  // names and IDs
  static const String APP_NAME         = "AvCaster" ;
  static const String JACK_CLIENT_NAME = APP_NAME ;
  static const String VALID_ID_CHARS   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- " ;
  static const String DIGITS           = "0123456789" ;

  // timers
  static const int GUI_TIMER_HI_ID  = 1 ; static const int GUI_UPDATE_HI_IVL  = 125 ;
  static const int GUI_TIMER_MED_ID = 2 ; static const int GUI_UPDATE_MED_IVL = 500 ;
  static const int GUI_TIMER_LO_ID  = 3 ; static const int GUI_UPDATE_LO_IVL  = 5000 ;

  // cli args
  static const String CLI_HELP_TOKEN    = "--help" ;
  static const String CLI_PRESETS_TOKEN = "--presets" ;
  static const String CLI_PRESET_TOKEN  = "--preset" ;
  static const String CLI_QUIT_TOKEN    = "--quit" ;
  static const String CLI_USAGE_MSG     = "AvCaster Usage:\n\n\tav-caster [ " + CLI_HELP_TOKEN    + "                  ] |"                                 +
                                                           "\n\t          [ " + CLI_PRESETS_TOKEN + "                  ] |"                                 +
                                                           "\n\t          [ " + CLI_PRESET_TOKEN  + " n                ] |"                                   +
                                                           "\n\t          [ " + CLI_QUIT_TOKEN    + "                  ]  "                                 +
                                                           "\n\n\t"           + CLI_HELP_TOKEN    + "\n\t\t\tprints this message"                           +
                                                           "\n\n\t"           + CLI_PRESETS_TOKEN + "\n\t\t\tlist stored presets"                           +
                                                           "\n\n\t"           + CLI_PRESET_TOKEN  + "\n\t\t\tstart with initial preset number n"            +
                                                           "\n\n\t"           + CLI_QUIT_TOKEN    + "\n\t\t\tquits the application immediately upon launch" ;

  // files
  static const File   HOME_DIR      = File::getSpecialLocation(File::userHomeDirectory           ) ;
  static const File   APPDATA_DIR   = File::getSpecialLocation(File::userApplicationDataDirectory) ;
  static const File   VIDEOS_DIR    = File::getSpecialLocation(File::userMoviesDirectory         ) ;
  static const String PNG_FILE_EXT  = ".png" ;
  static const String IMG_FILE_EXTS = "*" + APP::PNG_FILE_EXT + ",*" + APP::PNG_FILE_EXT ;

  // get device info
  static const String CAMERA_DEVICES_DIR = "/sys/class/video4linux" ;
}


/** the GUI namespace defines configuration and runtime constants
        pertaining to graphical elements                          */
namespace GUI
{
  // common
  static const int    PAD                 = 4 ;
  static const int    PAD2                = PAD * 2 ;
  static const int    PAD3                = PAD * 3 ;
  static const int    PAD4                = PAD * 4 ;
  static const Colour TEXT_BG_COLOR       = Colour(0xFF000000) ;
  static const Colour TEXT_FG_COLOR       = Colour(0xFFBBBBFF) ;
  static const Colour TEXT_CARET_COLOR    = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_HILITEBG_COLOR = Colour(0xFF000040) ;
  static const Colour TEXT_HILITE_COLOR   = Colour(0xFFFFFFFF) ;
  static const Colour TEXT_DISABLED_COLOR = Colour(0xFF808080) ;

  // Main
  static const int BORDERS_W  = 2 ;
  static const int TITLEBAR_H = 24 ;
  static const int WINDOW_W   = 760 - BORDERS_W ;
  static const int WINDOW_H   = 720 - BORDERS_W - TITLEBAR_H ;

  // Background
  static const String BACKGROUND_GUI_ID = "statusbar-gui" ;

  // StatusBar
  static const String STATUSBAR_GUI_ID  = "statusbar-gui" ;
  static const String INIT_STATUS_TEXT  = "Initializing" ;
  static const String READY_STATUS_TEXT = "Ready" ;
  static const int    STATUSBAR_H       = 24 ;
  static const int    STATUSBAR_Y       = WINDOW_H - STATUSBAR_H - PAD ;

  // MainContent
  static const String CONTENT_GUI_ID = "main-content-gui" ;
  static const int    CONTENT_W      = WINDOW_W - PAD2 ;
  static const int    CONTENT_H      = WINDOW_H - STATUSBAR_H - PAD3 ;

  // Controls
  static const String CONTROLS_GUI_ID = "controls-gui" ;
  static const String CONTROLS_TEXT   = "Controls" ;
  static const String PRESETS_TEXT    = "Presets" ;
  static const int    PREVIEW_X       = PAD4 + PAD4 ;
  static const int    PREVIEW_Y       = TITLEBAR_H + 64  + PAD4 + PAD2 ;
  static const int    PREVIEW_W       = CONTENT_W  - 32  - PAD4 - PAD2 ;
  static const int    PREVIEW_H       = CONTENT_H  - 100 + PAD2 ;

  // Config
  static const String CONFIG_GUI_ID          = "config-gui" ;
  static const int    CONFIG_H               = CONTENT_H - 80 ;
  static const int    CONFIG_Y               = WINDOW_H - CONFIG_H - STATUSBAR_H - PAD2 ;
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

  // alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
  static const String    MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

  // user error messages
  static const String GST_INIT_ERROR_MSG          = "Error creating static GstElements." ;
  static const String GST_ADD_ERROR_MSG           = "Error adding static GstElements to the pipeline." ;
  static const String GST_CONFIG_ERROR_MSG        = "Error configuring dynamic GstElements." ;
  static const String GST_XWIN_ERROR_MSG          = "Error attaching gStreamer to native x-window." ;
  static const String SCREENCAP_INIT_ERROR_MSG    = "Error creating ScreencapBin GstElements." ;
  static const String CAMERA_INIT_ERROR_MSG       = "Error creating CameraBin GstElements." ;
  static const String TEXT_INIT_ERROR_MSG         = "Error creating TextBin GstElements." ;
  static const String INTERSTITIAL_INIT_ERROR_MSG = "Error creating InterstitialBin GstElements." ;
  static const String MIXER_INIT_ERROR_MSG        = "Error creating CompositorBin GstElements." ;
  static const String MIXER_PAD_INIT_ERROR_MSG    = "Error creating CompositorBin GstPads." ;
  static const String AUDIO_INIT_ERROR_MSG        = "Error creating AudioBin GstElements." ;
  static const String MUX_INIT_ERROR_MSG          = "Error creating MuxBin GstElements." ;
  static const String OUTPUT_INIT_ERROR_MSG       = "Error creating OutputBin GstElements." ;
  static const String SCREENCAP_LINK_ERROR_MSG    = "Error linking ScreencapBin GstElements." ;
  static const String CAMERA_LINK_ERROR_MSG       = "Error linking CameraBin GstElements." ;
  static const String TEXT_LINK_ERROR_MSG         = "Error linking TextBin GstElements." ;
  static const String INTERSTITIAL_LINK_ERROR_MSG = "Error linking InterstitialBin GstElements." ;
  static const String MIXER_LINK_ERROR_MSG        = "Error linking CompositorBin GstElements." ;
  static const String MIXER_PAD_LINK_ERROR_MSG    = "Error linking CompositorBin GstPads." ;
  static const String AUDIO_LINK_ERROR_MSG        = "Error linking AudioBin GstElements." ;
  static const String MUX_LINK_ERROR_MSG          = "Error linking MuxBin GstElements." ;
  static const String OUTPUT_LINK_ERROR_MSG       = "Error linking OutputBin GstElements." ;
  static const String GST_STATE_ERROR_MSG         = "Invalid configuration." ;
  static const String STORAGE_WRITE_ERROR_MSG     = "I/O error storing configuration." ;
  static const String PRESET_NAME_ERROR_MSG       = "Enter a name for this preset in the \"Preset\" box then press \"Save\" again." ;
  static const String PRESET_RENAME_ERROR_MSG     = "A preset already exists with that name." ;
  static const String CONFIG_CHANGE_ERROR_MSG     = "Can not re-configure while the stream is active." ;
}


/** the CONFIG namespace defines keys/value pairs and default value constants
        pertaining to the configuration/persistence model                     */
namespace CONFIG
{
/*\ CAVEATS:
|*|  when defining new nodes or properties be sure to:
|*|    * if new node            - verify schema in AvCasterStore::validateConfig()
|*|    * if new root property   - verify schema in AvCasterStore::validateConfig()
|*|                             - sanitize data in AvCasterStore::sanitizeConfig()
|*|    * if new preset property - verify schema in AvCasterStore::validatePreset()
|*|    * update the SCHEMA below
\*/

/*\ SCHEMA:
|*|
|*| // AvCasterStore->configRoot
|*| STORAGE_ID:
|*| {
|*|   // config root IDs
|*|   CONFIG_VERSION_ID:    a_double                              ,
|*|   IS_CONFIG_PENDING_ID: a_bool                                ,
|*|   PRESET_ID:            an_int                                ,
|*|   PRESETS_ID:           [ a-config-id: a_config_node , .... ] // config nodes as below
|*| }
|*|
|*| // AvCasterStore->configStore
|*| // AvCasterStore->configPresets (each child)
|*| VOLATILE_CONFIG_ID:
|*| {
|*|   // control IDs
|*|   PRESET_NAME_ID:        a_string ,
|*|   IS_OUTPUT_ON_ID:       a_bool   ,
|*|   IS_INTERSTITIAL_ON_ID: a_bool   ,
|*|   IS_SCREENCAP_ON_ID:    a_bool   ,
|*|   IS_CAMERA_ON_ID:       a_bool   ,
|*|   IS_TEXT_ON_ID:         a_bool   ,
|*|   IS_PREVIEW_ON_ID:      a_bool   ,
|*|   // screen IDs
|*|   DISPLAY_N_ID:          an_int   ,
|*|   SCREEN_N_ID:           an_int   ,
|*|   SCREENCAP_W_ID:        an_int   ,
|*|   SCREENCAP_H_ID:        an_int   ,
|*|   OFFSET_X_ID:           an_int   ,
|*|   OFFSET_Y_ID:           an_int   ,
|*|   // camera IDs
|*|   CAMERA_DEV_ID:         an_int   ,
|*|   CAMERA_RES_ID:         an_int   ,
|*|   // audio IDs
|*|   AUDIO_API_ID:          an_int   ,
|*|   AUDIO_DEVICE_ID:       an_int   ,
|*|   AUDIO_CODEC_ID:        an_int   ,
|*|   N_CHANNELS_ID:         an_int   ,
|*|   SAMPLERATE_ID:         an_int   ,
|*|   AUDIO_BITRATE_ID:      an_int   ,
|*|   // text IDs
|*|   MOTD_TEXT_ID:          a_string ,
|*|   TEXT_STYLE_ID:         an_int   ,
|*|   TEXT_POSITION_ID:      an_int   ,
|*|   // interstitial IDs
|*|   INTERSTITIAL_TEXT_ID:  a_string ,
|*|   // output IDs
|*|   OUTPUT_SINK_ID:        an_int   ,
|*|   OUTPUT_MUXER_ID:       an_int   ,
|*|   OUTPUT_W_ID:           an_int   ,
|*|   OUTPUT_H_ID:           an_int   ,
|*|   FRAMERATE_ID:          an_int   ,
|*|   VIDEO_BITRATE_ID:      an_int   ,
|*|   OUTPUT_DEST_ID:        a_string
|*| }
|*|
|*| // AvCasterStore->cameraDevices
|*| CAMERA_DEVICES_ID:
|*| {
|*|   CAMERA_PATH_ID:        a_string , // e.g. "/dev/video0"
|*|   CAMERA_NAME_ID:        a_string , // e.g "USB Video Cam"
|*|   CAMERA_RATE_ID:        an_int   ,
|*|   CAMERA_RESOLUTIONS_ID: a_string
|*| }
|*|
|*| // AvCasterStore->audioDevices
|*| AUDIO_DEVICES_ID: { nyi }
\*/


  static Identifier FilterId(String a_string)
  {
    return a_string.retainCharacters(APP::VALID_ID_CHARS)
                   .toLowerCase()
                   .replaceCharacter('_', '-')
                   .replaceCharacter(' ', '-') ;
  }

  // nodes
  static const Identifier STORAGE_ID            = "av-caster-config" ;
  static const Identifier PRESETS_ID            = "presets" ;
  static const Identifier VOLATILE_CONFIG_ID    = "volatile-config" ;
  static const Identifier CAMERA_DEVICES_ID     = "camera-devices" ;
  static const Identifier AUDIO_DEVICES_ID      = "audio-devices" ;
  // config root IDs
  static const Identifier CONFIG_VERSION_ID     = "config-version" ;
  static const Identifier PRESET_ID             = "preset-idx" ;
  static const Identifier IS_CONFIG_PENDING_ID  = "is-config-pending" ;
  // control IDs
  static const Identifier PRESET_NAME_ID        = "preset-name" ;
  static const Identifier IS_OUTPUT_ON_ID       = "is-output-on" ;
  static const Identifier IS_INTERSTITIAL_ON_ID = "is-interstitial-on" ;
  static const Identifier IS_SCREENCAP_ON_ID    = "is-screencap-on" ;
  static const Identifier IS_CAMERA_ON_ID       = "is-camera-on" ;
  static const Identifier IS_TEXT_ON_ID         = "is-text-on" ;
  static const Identifier IS_PREVIEW_ON_ID      = "is-preview-on" ;
  // screen IDs
  static const Identifier DISPLAY_N_ID          = "display-n" ;
  static const Identifier SCREEN_N_ID           = "screen-n" ;
  static const Identifier SCREENCAP_W_ID        = "sceencap-w" ;
  static const Identifier SCREENCAP_H_ID        = "sceencap-h" ;
  static const Identifier OFFSET_X_ID           = "offset-x" ;
  static const Identifier OFFSET_Y_ID           = "offset-y" ;
  // camera IDs
  static const Identifier CAMERA_DEV_ID         = "camera-dev-idx" ;
  static const Identifier CAMERA_RES_ID         = "camera-res-idx" ;
  static const Identifier CAMERA_PATH_ID        = "camera-dev-path" ;
  static const Identifier CAMERA_NAME_ID        = "camera-dev-name" ;
  static const Identifier CAMERA_RATE_ID        = "camera-framerate" ;
  static const Identifier CAMERA_RESOLUTIONS_ID = "camera-resolutions" ;
  // audio IDs
  static const Identifier AUDIO_API_ID          = "audio-api-idx" ;
  static const Identifier AUDIO_DEVICE_ID       = "audio-device-idx" ;
  static const Identifier AUDIO_CODEC_ID        = "audio-codec-idx" ;
  static const Identifier N_CHANNELS_ID         = "n-channels" ;
  static const Identifier SAMPLERATE_ID         = "samplerate-idx" ;
  static const Identifier AUDIO_BITRATE_ID      = "audio-bitrate-idx" ;
  // text IDs
  static const Identifier MOTD_TEXT_ID          = "motd-text" ;
  static const Identifier TEXT_STYLE_ID         = "text-style-idx" ;
  static const Identifier TEXT_POSITION_ID      = "text-pos-idx" ;
  // interstitial IDs
  static const Identifier INTERSTITIAL_LOC_ID   = "interstitial-img" ;
  // output IDs
  static const Identifier OUTPUT_SINK_ID        = "output-sink-idx" ;
  static const Identifier OUTPUT_MUXER_ID       = "output-muxer-idx" ;
  static const Identifier OUTPUT_W_ID           = "output-w" ;
  static const Identifier OUTPUT_H_ID           = "output-h" ;
  static const Identifier FRAMERATE_ID          = "framerate-idx" ;
  static const Identifier VIDEO_BITRATE_ID      = "video-bitrate-idx" ;
  static const Identifier OUTPUT_DEST_ID        = "output-dest" ;

  // root defaults
#ifdef _WIN32
  static const String     STORAGE_DIRNAME            = "AvCaster\\" ;
#else // _WIN32
  static const String     STORAGE_DIRNAME            = ".av-caster/" ;
#endif // _WIN32
  static const String     STORAGE_FILENAME           = "AvCaster.bin" ;
  static const double     CONFIG_VERSION             = 0.3 ;
  static const int        DEFAULT_PRESET_IDX         = 0 ; // ASSERT: must be 0
  static const int        N_STATIC_PRESETS           = 3 ; // ASSERT: num PresetSeed subclasses
  static const bool       DEFAULT_IS_CONFIG_PENDING  = false ;

  // control defaults
  static const String     FILE_PRESET_NAME           = "Local File" ;
  static const String     RTMP_PRESET_NAME           = "RTMP Server" ;
  static const String     LCTV_PRESET_NAME           = "livecoding.tv" ;
  static const String     DEFAULT_PRESET_NAME        = FILE_PRESET_NAME ;
  static const Identifier DEFAULT_PRESET_ID          = FilterId(DEFAULT_PRESET_NAME) ;
  static const bool       DEFAULT_IS_OUTPUT_ON       = false ;
  static const bool       DEFAULT_IS_INTERSTITIAL_ON = true ;
  static const bool       DEFAULT_IS_SCREENCAP_ON    = false ;
  static const bool       DEFAULT_IS_CAMERA_ON       = false ;
  static const bool       DEFAULT_IS_TEXT_ON         = false ;
  static const bool       DEFAULT_IS_PREVIEW_ON      = true ;
  // screen defaults
  static const int        DEFAULT_DISPLAY_N          = 0 ;
  static const int        DEFAULT_SCREEN_N           = 0 ;
  static const int        DEFAULT_SCREENCAP_W        = 640 ;
  static const int        DEFAULT_SCREENCAP_H        = 480 ;
  static const int        DEFAULT_OFFSET_X           = 0 ;
  static const int        DEFAULT_OFFSET_Y           = 0 ;
  // camera defaults
  static const int        DEFAULT_CAMERA_DEV_IDX     = 0 ;
  static const int        DEFAULT_CAMERA_RES_IDX     = 0 ;
  // audio defaults
  static const int        DEFAULT_AUDIO_API_IDX      = 0 ;
  static const int        DEFAULT_AUDIO_DEVICE_IDX   = 0 ;
  static const int        DEFAULT_AUDIO_CODEC_IDX    = 0 ;
  static const int        DEFAULT_N_CHANNELS         = 2 ;
  static const int        DEFAULT_SAMPLERATE_IDX     = 0 ;
  static const int        DEFAULT_AUDIO_BITRATE_IDX  = 0 ;
  // text defaults
  static const String     DEFAULT_MOTD_TEXT          = "" ;
  static const int        DEFAULT_TEXT_STYLE_IDX     = 0 ;
  static const int        DEFAULT_TEXT_POSITION_IDX  = 0 ;
  // interstitial defaults
  static const String     DEFAULT_INTERSTITIAL_LOC   = "" ;
  // output defaults
  static const int        DEFAULT_OUTPUT_SINK_IDX    = 0 ;
  static const int        DEFAULT_OUTPUT_MUXER_IDX   = 0 ;
  static const int        DEFAULT_OUTPUT_W           = 640 ;
  static const int        DEFAULT_OUTPUT_H           = 480 ;
  static const int        DEFAULT_FRAMERATE_IDX      = 0 ;
  static const int        DEFAULT_VIDEO_BITRATE_IDX  = 0 ;
  static const String     DEFAULT_OUTPUT_DEST        = APP::APP_NAME + ".flv" ;

  // config indices
  static const int FILE_PRESET_IDX = 0 ;
  static const int RTMP_PRESET_IDX = 1 ;
  static const int LCTV_PRESET_IDX = 2 ;
  static const int FILE_STREAM_IDX = 0 ;
  static const int RTMP_STREAM_IDX = 1 ;

  // config strings
  static const String      FILE_OUTPUT       = "File" ;
  static const String      RTMP_OUTPUT       = "RTMP" ;
  static const String      FLV_MUXER         = ".flv" ;
  static const StringArray AUDIO_APIS        = StringArray::fromLines("ALSA"      + newLine +
                                                                      "Pulse"     + newLine +
                                                                      "JACK"                ) ;
  static const StringArray AUDIO_CODECS      = StringArray::fromLines("MP3"       + newLine +
                                                                      "AAC"                 ) ;
  static const StringArray AUDIO_SAMPLERATES = StringArray::fromLines("11025"     + newLine +
                                                                      "22050"     + newLine +
                                                                      "44100"               ) ;
  static const StringArray AUDIO_BITRATES    = StringArray::fromLines("64k"       + newLine +
                                                                      "96k"       + newLine +
                                                                      "128k"      + newLine +
                                                                      "192k"                ) ;
  static const StringArray TEXT_STYLES       = StringArray::fromLines("Static"    + newLine +
                                                                      "Marquee"             ) ;
  static const StringArray TEXT_POSITIONS    = StringArray::fromLines("Top"       + newLine +
                                                                      "Bottom"              ) ;
  static const StringArray OUTPUT_SINKS      = StringArray::fromLines(FILE_OUTPUT + newLine +
                                                                      RTMP_OUTPUT           ) ;
  static const StringArray OUTPUT_MUXERS     = StringArray::fromLines(FLV_MUXER             ) ;
  static const StringArray FRAMERATES        = StringArray::fromLines("8"         + newLine +
                                                                      "12"        + newLine +
                                                                      "20"        + newLine +
                                                                      "30"                  ) ;
  static const StringArray VIDEO_BITRATES    = StringArray::fromLines("800k"      + newLine +
                                                                      "1200k"               ) ;
}


/** the GUI namespace defines configuration and runtime constants
        pertaining to the gStreamer media backend                 */
namespace GST
{
  static const String NIX_SCREEN_PLUGIN_ID  = "ximagesrc" ;
  static const String V4L2_PLUGIN_ID        = "v4l2src" ;
  static const String FAUX_VIDEO_PLUGIN_ID  = "videotestsrc" ;
  static const String ALSA_PLUGIN_ID        = "alsasrc" ;
  static const String PULSE_PLUGIN_ID       = "pulsesrc" ;
  static const String JACK_PLUGIN_ID        = "jackaudiosrc" ;
  static const String FAUX_AUDIO_PLUGIN_ID  = "audiotestsrc" ;
  static const String NIX_PREVIEW_PLUGIN_ID = "xvimagesink" ;
  static const String FILE_SINK_PLUGIN_ID   = "filesink" ;
  static const String RTMP_SINK_PLUGIN_ID   = "rtmpsink" ;
  static const String FAUX_SINK_PLUGIN_ID   = "fakesink" ;
  static const String FAUX_AUDIO_CAPS       = "audio/x-raw, format=(string)S16LE, endianness=(int)1234, signed=(boolean)true, width=(int)16, depth=(int)16, rate=(int)44100, channels=(int)2" ;

  static const String LCTV_RTMP_URL = "rtmp://usmedia3.livecoding.tv:1935/livecodingtv/" ;
}

#endif // CONSTANTS_H_INCLUDED
