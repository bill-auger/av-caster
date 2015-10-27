/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// enable standard features
#  define CONFIGURE_SCREENCAP_BIN   1
#  define CONFIGURE_CAMERA_BIN      1
#  define CONFIGURE_AUDIO_BIN       1
#  define CONFIGURE_TEXT_BIN        0
#  define CONFIGURE_COMPOSITING_BIN (1 && CONFIGURE_SCREENCAP_BIN && CONFIGURE_CAMERA_BIN)
#  define CONFIGURE_MUX_BIN         (CONFIGURE_AUDIO_BIN && (CONFIGURE_SCREENCAP_BIN || CONFIGURE_CAMERA_BIN || CONFIGURE_COMPOSITING_BIN))
#  define CONFIGURE_OUTPUT_BIN      (1 && CONFIGURE_MUX_BIN)
#  define CONFIGURE_TEES            (1 && CONFIGURE_COMPOSITING_BIN)
// #  define DISABLE_SCREENCAP
// #  define DISABLE_CAMERA
// #  define FAUX_SCREEN_SRC
// #  define FAUX_CAMERA_SRC
// #  define FAUX_AUDIO_SRC
// #  define FAKE_MUX_ENCODER_SRC_AND_SINK          // isolate compositor from encoder and muxer from output
// #define FAUX_FULLSCREEN_SINK                     // instatiate FullscreenSink as fakesink
// #define FAUX_OVERLAY_SINK                        // instatiate OverlaySink    as fakesink
// #define FAUX_COMPOSITE_SINK                      // instatiate CompositeSink  as fakesink
// #define FAUX_COMPOSITOR_COMPOSITE_FULLSCREEN_SRC // replace static  srcpad  on fullscreen_thru_queue (nyi)
// #define FAUX_COMPOSITOR_COMPOSITE_OVERLAY_SRC    // replace static  srcpad  on overlay_thru_queue (nyi)
// #define FAUX_COMPOSITOR_FULLSCREEN_THRU_SINK     // replace request snkpad  on compositor (nyi)
// #define FAUX_COMPOSITOR_OVERLAY_THRU_SINK        // replace request snkpad  on compositor (nyi)
// #ifndef CONFIGURE_SCREENCAP_BIN                // replace ghost   sinkpad on fullscreen-tee
// #ifndef CONFIGURE_CAMERA_BIN                   // replace ghost   sinkpad on overlay-tee
// #ifndef CONFIGURE_MUX_BIN                      // replace ghost   srcpad  on composite_thru_queue


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
#define DEBUG_TRACE_CONFIG DEBUG_DEFINED && 1
#define DEBUG_TRACE_STATE  DEBUG_DEFINED && 1
#define DEBUG_TRACE_VB     DEBUG_DEFINED && 0


#include "JuceHeader.h"


namespace APP
{
  // names and IDs
  static const String APP_NAME         = "AvCaster" ;
  static const String JACK_CLIENT_NAME = APP_NAME ;

  // timers
  static const int GUI_TIMER_HI_ID  = 1 ; static const int GUI_UPDATE_HI_IVL  = 125 ;
  static const int GUI_TIMER_MED_ID = 2 ; static const int GUI_UPDATE_MED_IVL = 500 ;
  static const int GUI_TIMER_LO_ID  = 3 ; static const int GUI_UPDATE_LO_IVL  = 5000 ;

  // get device info
  static const String CAMERA_DEVICES_DIR      = "/sys/class/video4linux" ;
  static const String AVPLAY_TEST_CAM_COMMAND = "avplay -f video4linux2 -i " ;
  static const String AVPLAY_CAM_BUSY_ERROR   = "Input/output error" ;
}

namespace GUI
{
  // common
  static const int PAD  = 4 ;
  static const int PAD2 = PAD * 2 ;
  static const int PAD3 = PAD * 3 ;

  // MainContent
  static const String CONTENT_GUI_ID = "main-content-gui" ;
  static const int    BORDERS_W      = 2 ;
  static const int    TITLEBAR_H     = 24 ;
  static const int    CONTENT_W      = 800 - BORDERS_W ;
  static const int    CONTENT_H      = 720 - BORDERS_W - TITLEBAR_H ;

  // Config
  static const String OUTPUT_GUI_ID        = "output-config-gui" ;
  static const int    MONITORS_W           = 160 ;
  static const int    MONITORS_H           = 120 ;
  static const int    MONITORS_Y           = 504 + TITLEBAR_H ;
  static const int    FULLSCREEN_MONITOR_X = 40 ;
  static const int    OVERLAY_MONITOR_X    = 224 ;
  static const int    COMPOSITE_MONITOR_X  = 408 ;

  // StatusBar
  static const String STATUS_GUI_ID    = "statusbar-gui" ;
  static const String INIT_STATUS_TEXT = "Initializing" ;
  static const int    STATUSBAR_H      = 24 ;

  // alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String     MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
  static const String     MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

  // user error messages
  static const String GST_INIT_ERROR_MSG          = "Error creating static GstElements." ;
  static const String GST_ADD_ERROR_MSG           = "Error adding static GstElements to the pipeline." ;
  static const String GST_CONFIG_ERROR_MSG        = "Error configuring dynamic GstElements." ;
  static const String GST_XWIN_ERROR_MSG          = "Error attaching gStreamer to native x-window." ;
  static const String AUDIO_CFG_ERROR_MSG         = "Error reading AudioBin config." ;
  static const String OUTPUT_CFG_ERROR_MSG        = "Error reading OutputBin config." ;
  static const String SCREENCAP_INIT_ERROR_MSG    = "Error creating ScreencapBin GstElements." ;
  static const String CAMERA_INIT_ERROR_MSG       = "Error creating CameraBin GstElements." ;
  static const String TEXT_INIT_ERROR_MSG         = "Error creating TextBin GstElements." ;
  static const String MIXER_INIT_ERROR_MSG        = "Error creating CompositorBin GstElements." ;
  static const String MIXER_PAD_INIT_ERROR_MSG    = "Error creating CompositorBin GstPads." ;
  static const String AUDIO_INIT_ERROR_MSG        = "Error creating AudioBin GstElements." ;
  static const String INTERSTITIAL_INIT_ERROR_MSG = "Error creating InterstitialBin GstElements." ;
  static const String MUX_INIT_ERROR_MSG          = "Error creating MuxBin GstElements." ;
  static const String OUTPUT_INIT_ERROR_MSG       = "Error creating OutputBin GstElements." ;
  static const String SCREENCAP_LINK_ERROR_MSG    = "Error linking ScreencapBin GstElements." ;
  static const String CAMERA_LINK_ERROR_MSG       = "Error linking CameraBin GstElements." ;
  static const String TEXT_LINK_ERROR_MSG         = "Error linking TextBin GstElements." ;
  static const String MIXER_LINK_ERROR_MSG        = "Error linking CompositorBin GstElements." ;
  static const String MIXER_PAD_LINK_ERROR_MSG    = "Error linking CompositorBin GstPads." ;
  static const String AUDIO_LINK_ERROR_MSG        = "Error linking AudioBin GstElements." ;
  static const String INTERSTITIAL_LINK_ERROR_MSG = "Error linking InterstitialBin GstElements." ;
  static const String MUX_LINK_ERROR_MSG          = "Error linking MuxBin GstElements." ;
  static const String OUTPUT_LINK_ERROR_MSG       = "Error linking OutputBin GstElements." ;
  static const String GST_STATE_ERROR_MSG         = "Invalid configuration." ;
  static const String NO_CAMERAS_ERROR_MSG        = "No video capture devices were found on you system.  If you indeed have one mounted , you will need to enter its mountpoint manually." ;
  static const String CAM_BUSY_ERROR_MSG          = "The selected capture device is already in use." ;
  static const String STORAGE_WRITE_ERROR_MSG     = "I/O error storing configuration." ;
}

namespace CONFIG
{
/*\ CAVEATS:
|*|  when adding nodes or properties to AvCasterConfig->configStore be sure to:
|*|    * if new node     - verify schema in   AvCasterConfig::validateConfig()
|*|    * if new property - verify schema in   AvCasterConfig::validateConfig()
|*|                      - sanitize data in   AvCasterConfig::sanitizeConfig()
|*|    * validate and trace data/errors in    #define DEBUG_TRACE_VALIDATE_CONFIG
|*|                                           #define DEBUG_TRACE_SANITIZE_CONFIG
\*/

  // nodes
  static const Identifier STORAGE_ID          = "av-caster-config" ;
  static const Identifier CAMERA_DEVICES_ID   = "camera-devices" ;
  static const Identifier CAMERA_PATH_ID      = "device-path" ;
  static const Identifier CAMERA_NAME_ID      = "device-name" ;
  static const Identifier AUDIO_DEVICES_ID    = "audio-devices" ;
  // config root
  static const Identifier CONFIG_VERSION_ID   = "config-version" ;
  // screen IDs
  static const Identifier DISPLAY_N_ID        = "display-n" ;
  static const Identifier SCREEN_N_ID         = "screen-n" ;
  static const Identifier SCREENCAP_W_ID      = "sceencap-w" ;
  static const Identifier SCREENCAP_H_ID      = "sceencap-h" ;
  static const Identifier OFFSET_X_ID         = "offset-x" ;
  static const Identifier OFFSET_Y_ID         = "offset-y" ;
  // camera IDs
  static const Identifier CAMERA_DEV_ID       = "camera-dev-idx" ;
  static const Identifier CAMERA_RES_ID       = "camera-res-idx" ;
  // audio IDs
  static const Identifier AUDIO_API_ID        = "audio-api-idx" ;
  static const Identifier AUDIO_DEVICE_ID     = "audio-device-idx" ;
  static const Identifier AUDIO_CODEC_ID      = "audio-codec-idx" ;
  static const Identifier N_CHANNELS_ID       = "n-channels" ;
  static const Identifier SAMPLERATE_ID       = "samplerate-idx" ;
  static const Identifier AUDIO_BITRATE_ID    = "audio-bitrate-idx" ;
  // text IDs
  static const Identifier OVERLAY_TEXT_ID     = "overlay-text" ;
  static const Identifier TEXT_STYLE_ID       = "text-style-idx" ;
  static const Identifier TEXT_POSITION_ID    = "text-pos-idx" ;
  // output IDs
  static const Identifier OUTPUT_STREAM_ID    = "output-stream-idx" ;
  static const Identifier OUTPUT_CONTAINER_ID = "output-container-idx" ;
  static const Identifier OUTPUT_W_ID         = "output-w" ;
  static const Identifier OUTPUT_H_ID         = "output-h" ;
  static const Identifier FRAMERATE_ID        = "framerate-idx" ;
  static const Identifier VIDEO_BITRATE_ID    = "video-bitrate-idx" ;
  static const Identifier OUTPUT_DEST_ID      = "output-dest" ;
  static const Identifier IS_PREVIEW_ON_ID    = "is-preview-on" ;

  // root defaults
#ifdef _WIN32
  static const String STORAGE_DIRNAME              = "AvCaster\\" ;
#else // _WIN32
  static const String STORAGE_DIRNAME              = ".av-caster/" ;
#endif // _WIN32
  static const String STORAGE_FILENAME             = STORAGE_DIRNAME + "AvCaster.bin" ;
  static const double CONFIG_VERSION               = 0.1 ;
  // screen defulats
  static const int    DEFAULT_DISPLAY_N            = 0 ;
  static const int    DEFAULT_SCREEN_N             = 0 ;
  static const int    DEFAULT_SCREENCAP_W          = 640 ;
  static const int    DEFAULT_SCREENCAP_H          = 480 ;
  static const int    DEFAULT_OFFSET_X             = 0 ;
  static const int    DEFAULT_OFFSET_Y             = 0 ;
  // camera defulats
  static const int    DEFAULT_CAMERA_DEV_IDX       = 0 ;
  static const int    DEFAULT_CAMERA_RES_IDX       = 0 ;
  // audio defulats
  static const int    DEFAULT_AUDIO_API_IDX        = 0 ;
  static const int    DEFAULT_AUDIO_DEVICE_IDX     = 0 ;
  static const int    DEFAULT_AUDIO_CODEC_IDX      = 0 ;
  static const int    DEFAULT_N_CHANNELS           = 2 ;
  static const int    DEFAULT_SAMPLERATE_IDX       = 0 ;
  static const int    DEFAULT_AUDIO_BITRATE_IDX    = 0 ;
  // text defulats
  static const String DEFAULT_OVERLAY_TEXT         = "" ;
  static const int    DEFAULT_TEXT_STYLE_IDX       = 0 ;
  static const int    DEFAULT_TEXT_POSITION_IDX    = 0 ;
  // output defulats
  static const int    DEFAULT_OUTPUT_STREAM_IDX    = 0 ;
  static const int    DEFAULT_OUTPUT_CONTAINER_IDX = 0 ;
  static const int    DEFAULT_OUTPUT_W             = 640 ;
  static const int    DEFAULT_OUTPUT_H             = 480 ;
  static const int    DEFAULT_FRAMERATE_IDX        = 0 ;
  static const int    DEFAULT_VIDEO_BITRATE_IDX    = 0 ;
  static const String DEFAULT_OUTPUT_DEST          = APP::APP_NAME + ".mp4" ;
  static const bool   DEFAULT_IS_PREVIEW_ON        = true ;

  // config strings
  static const String FILE_OUTPUT   = "File" ;
  static const String RTMP_OUTPUT   = "RTMP" ;
  static const String FLV_CONTAINER = ".flv" ;
  static const StringArray CAMERA_RESOLUTIONS = StringArray::fromLines("160x120"   + newLine +
                                                                       "320x240"   + newLine +
                                                                       "640x480"             ) ;
  static const StringArray AUDIO_APIS         = StringArray::fromLines("ALSA"      + newLine +
                                                                       "Pulse"     + newLine +
                                                                       "JACK"                ) ;
  static const StringArray AUDIO_CODECS       = StringArray::fromLines("AAC"       + newLine +
                                                                       "MP3"                 ) ;
  static const StringArray AUDIO_SAMPLERATES  = StringArray::fromLines("11025"     + newLine +
                                                                       "22050"     + newLine +
                                                                       "44100"               ) ;
  static const StringArray AUDIO_BITRATES     = StringArray::fromLines("64k"       + newLine +
                                                                       "96k"       + newLine +
                                                                       "128k"      + newLine +
                                                                       "192k"                ) ;
  static const StringArray TEXT_STYLES        = StringArray::fromLines("Static"    + newLine +
                                                                       "Marquee"             ) ;
  static const StringArray TEXT_POSITIONS     = StringArray::fromLines("Top"       + newLine +
                                                                       "Bottom"              ) ;
  static const StringArray OUTPUT_STREAMS     = StringArray::fromLines(FILE_OUTPUT + newLine +
                                                                       RTMP_OUTPUT           ) ;
  static const StringArray OUTPUT_CONTAINERS  = StringArray::fromLines(FLV_CONTAINER         ) ;
  static const StringArray FRAMERATES         = StringArray::fromLines("8"         + newLine +
                                                                       "12"        + newLine +
                                                                       "20"        + newLine +
                                                                       "30"                  ) ;
  static const StringArray VIDEO_BITRATES     = StringArray::fromLines("800k"      + newLine +
                                                                       "1200k"               ) ;
}

namespace GST
{
  static const String ALSA_PLUGIN_ID  = "alsasrc" ;
  static const String PULSE_PLUGIN_ID = "pulsesrc" ;
  static const String JACK_PLUGIN_ID  = "jackaudiosrc" ;

  static const String LCTV_RTMP_URL = "rtmp://usmedia3.livecoding.tv:1935/livecodingtv/" ;
}

#endif // CONSTANTS_H_INCLUDED
