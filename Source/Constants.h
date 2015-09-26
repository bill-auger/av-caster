/*
  ==============================================================================

    Constants.h
    Created: 12 Sep 2015 10:27:53am
    Author:  bill

  ==============================================================================
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

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

  static const uint8 PROC_BUFFER_SIZE = 255 ;
  static const uint8 MUX_THREAD_SLEEP = 125 ;

  // default ffmpeg params
  static const String DEFAULT_CAPTURE_DEVICE = "/dev/video0" ;

  // get device info
  static const String CAPTURE_DEVICES_DIR     = "/sys/class/video4linux" ;
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

  // OutputConfig
  static const String OUTPUT_GUI_ID       = "output-config-gui" ;
  static const int    MONITORS_W          = 160 ;
  static const int    MONITORS_H          = 120 ;
  static const int    MONITORS_Y          = 504 ;
  static const int    SCREENCAP_MONITOR_X = 40 ;
  static const int    CAMERA_MONITOR_X    = 224 ;
  static const int    OUTPUT_MONITOR_X    = 408 ;

  // StatusBar
  static const String STATUS_GUI_ID    = "statusbar-gui" ;
  static const String INIT_STATUS_TEXT = "Initializing" ;
  static const int    STATUSBAR_H      = 24 ;

  // alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String     MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
  static const String     MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

  // user error messages
  static const String GST_INIT_ERROR_MSG      = "Not all elements could be created." ;
  static const String GST_STATE_ERROR_MSG     = "Unable to set the pipeline to the playing state." ;
  static const String NO_CAMERAS_ERROR_MSG    = "No video capture devices were found on you system.  If you indeed have one mounted , you will need to enter its mountpoint manually." ;
  static const String CAM_BUSY_ERROR_MSG      = "The selected capture device is already in use." ;
  static const String STORAGE_WRITE_ERROR_MSG = "I/O error storing configuration" ;
}

namespace CONFIG
{
  // config root
  static const Identifier CONFIG_VERSION_ID = "config-version" ;
  static const Identifier STORAGE_ID        = "av-caster-config" ;
  // screen IDs
  static const Identifier DISPLAY_N_ID     = "display-n" ;
  static const Identifier SCREEN_N_ID      = "screen-n" ;
  static const Identifier CAPTURE_W_ID     = "capture-w" ;
  static const Identifier CAPTURE_H_ID     = "capture-h" ;
  static const Identifier OFFSET_X_ID      = "offset-x" ;
  static const Identifier OFFSET_Y_ID      = "offset-y" ;
  // camera IDs
  static const Identifier CAMERA_DEV_ID    = "camera-dev-idx" ;
  static const Identifier CAMERA_RES_ID    = "camera-res-idx" ;
  // audio IDs
  static const Identifier AUDIO_API_ID     = "audio-api-idx" ;
  static const Identifier AUDIO_INPUT_ID   = "audio-input-idx" ;
  static const Identifier AUDIO_CODEC_ID   = "audio-codec-idx" ;
  static const Identifier N_CHANNELS_ID    = "n-channels" ;
  static const Identifier SAMPLERATE_ID    = "samplerate-idx" ;
  static const Identifier AUDIO_BITRATE_ID = "audio-bitrate-idx" ;
  // text IDs
  static const Identifier OVERLAY_TEXT_ID  = "overlay-text-idx" ;
  static const Identifier TEXT_STYLE_ID    = "text-style-idx" ;
  static const Identifier TEXT_POS_ID      = "text-pos-idx" ;
  // output IDs
  static const Identifier OUTPUT_STREAM_ID = "output-stream-idx" ;
  static const Identifier OUTPUT_DEST_ID   = "output-dest-idx" ;
  static const Identifier OUTPUT_RES_ID    = "output-res-idx" ;
  static const Identifier FRAMERATE_ID     = "framerate-idx" ;
  static const Identifier BITRATE_ID       = "bitrate-idx" ;

  // root defaults
  // persistence and storage
#ifdef _WIN32
  static const String STORAGE_DIRNAME       = "AvCaster\\" ;
#else // _WIN32
  static const String STORAGE_DIRNAME       = ".av-caster/" ;
#endif // _WIN32
  static const String STORAGE_FILENAME      = STORAGE_DIRNAME + "AvCaster.bin" ;
  static const double CONFIG_VERSION        = 0.1 ;
  // screen defulats
  static const int    DEFAULT_DISPLAY_N     = 0 ;
  static const int    DEFAULT_SCREEN_N      = 0 ;
  static const int    DEFAULT_CAPTURE_W     = 640 ;
  static const int    DEFAULT_CAPTURE_H     = 480 ;
  static const int    DEFAULT_OFFSET_X      = 0 ;
  static const int    DEFAULT_OFFSET_Y      = 0 ;
  // camera defulats
  static const int    DEFAULT_CAMERA_DEV    = -1 ;
  static const int    DEFAULT_CAMERA_RES    = 0 ;
  // audio defulats
  static const int    DEFAULT_AUDIO_API     = 0 ;
  static const int    DEFAULT_AUDIO_INPUT   = -1 ;
  static const int    DEFAULT_AUDIO_CODEC   = 0 ;
  static const int    DEFAULT_N_CHANNELS    = 2 ;
  static const int    DEFAULT_SAMPLERATE    = 0 ;
  static const int    DEFAULT_AUDIO_BITRATE = 0 ;
  // text defulats
  static const String DEFAULT_OVERLAY_TEXT  = "" ;
  static const int    DEFAULT_TEXT_STYLE    = 0 ;
  static const int    DEFAULT_TEXT_POS      = 0 ;
  // output defulats
  static const int    DEFAULT_OUTPUT_STREAM = 0 ;
  static const String DEFAULT_OUTPUT_DEST   = APP::APP_NAME + ".mp4" ;
  static const int    DEFAULT_OUTPUT_RES    = 0 ;
  static const int    DEFAULT_FRAMERATE     = 0 ;
  static const int    DEFAULT_BITRATE       = 0 ;

  static const String DEFAULT_CONFIG_XML = String("<?xml version=\"1.0\"?><"     +      \
      String(STORAGE_ID)          +                                         " "  +      \
        String(CONFIG_VERSION_ID) + "=\"" + String(CONFIG_VERSION       ) + "\"" +      \
        String(DISPLAY_N_ID     ) + "=\"" + String(DEFAULT_DISPLAY_N    ) + "\"" +      \
        String(SCREEN_N_ID      ) + "=\"" + String(DEFAULT_SCREEN_N     ) + "\"" +      \
        String(CAPTURE_W_ID     ) + "=\"" + String(DEFAULT_CAPTURE_W    ) + "\"" +      \
        String(CAPTURE_H_ID     ) + "=\"" + String(DEFAULT_CAPTURE_H    ) + "\"" +      \
        String(OFFSET_X_ID      ) + "=\"" + String(DEFAULT_OFFSET_X     ) + "\"" +      \
        String(OFFSET_Y_ID      ) + "=\"" + String(DEFAULT_OFFSET_Y     ) + "\"" +      \
        String(CAMERA_DEV_ID    ) + "=\"" + String(DEFAULT_CAMERA_DEV   ) + "\"" +      \
        String(CAMERA_RES_ID    ) + "=\"" + String(DEFAULT_CAMERA_RES   ) + "\"" +      \
        String(AUDIO_API_ID     ) + "=\"" + String(DEFAULT_AUDIO_API    ) + "\"" +      \
        String(AUDIO_INPUT_ID   ) + "=\"" + String(DEFAULT_AUDIO_INPUT  ) + "\"" +      \
        String(AUDIO_CODEC_ID   ) + "=\"" + String(DEFAULT_AUDIO_CODEC  ) + "\"" +      \
        String(N_CHANNELS_ID    ) + "=\"" + String(DEFAULT_N_CHANNELS   ) + "\"" +      \
        String(SAMPLERATE_ID    ) + "=\"" + String(DEFAULT_SAMPLERATE   ) + "\"" +      \
        String(AUDIO_BITRATE_ID ) + "=\"" + String(DEFAULT_AUDIO_BITRATE) + "\"" +      \
        String(OVERLAY_TEXT_ID  ) + "=\"" + String(DEFAULT_OVERLAY_TEXT ) + "\"" +      \
        String(TEXT_STYLE_ID    ) + "=\"" + String(DEFAULT_TEXT_STYLE   ) + "\"" +      \
        String(TEXT_POS_ID      ) + "=\"" + String(DEFAULT_TEXT_POS     ) + "\"" +      \
        String(OUTPUT_STREAM_ID ) + "=\"" + String(DEFAULT_OUTPUT_STREAM) + "\"" +      \
        String(OUTPUT_DEST_ID   ) + "=\"" + String(DEFAULT_OUTPUT_DEST  ) + "\"" +      \
        String(OUTPUT_RES_ID    ) + "=\"" + String(DEFAULT_OUTPUT_RES   ) + "\"" +      \
        String(FRAMERATE_ID     ) + "=\"" + String(DEFAULT_FRAMERATE    ) + "\"" +      \
        String(BITRATE_ID       ) + "=\"" + String(DEFAULT_BITRATE      ) + "\"" +      \
      "></" + String(STORAGE_ID)                                                 + ">") ;

  static const StringArray CAMERA_RESOLUTIONS = StringArray::fromLines("160x120"    + newLine +
                                                                       "320x240"    + newLine +
                                                                       "640x480"              ) ;
  static const StringArray AUDIO_APIS         = StringArray::fromLines("ALSA"       + newLine +
                                                                       "PulseAudio" + newLine +
                                                                       "JACK"                 ) ;
  static const StringArray AUDIO_CODECS       = StringArray::fromLines("AAC"        + newLine +
                                                                       "MP3"                  ) ;
  static const StringArray AUDIO_SAMPLERATES  = StringArray::fromLines("22050"      + newLine +
                                                                       "44100"      + newLine +
                                                                       "48000"                ) ;
  static const StringArray AUDIO_BITRATES     = StringArray::fromLines("96k"        + newLine +
                                                                       "128k"       + newLine +
                                                                       "192k"                 ) ;
  static const StringArray TEXT_STYLES        = StringArray::fromLines("Static"     + newLine +
                                                                       "Marquee"              ) ;
  static const StringArray TEXT_POSITIONS     = StringArray::fromLines("Top"        + newLine +
                                                                       "Bottom"               ) ;
  static const StringArray OUTPUT_STREAMS     = StringArray::fromLines("File"       + newLine +
                                                                       "RTMP"                 ) ;
  static const StringArray OUTPUT_RESOLUTIONS = StringArray::fromLines("768x480"    + newLine +
                                                                       "1280x800"   + newLine +
                                                                       "1920x1200"            ) ;
  static const StringArray OUTPUT_FRAMERATES  = StringArray::fromLines("12"         + newLine +
                                                                       "20"         + newLine +
                                                                       "30"                   ) ;
  static const StringArray OUTPUT_BITRATES    = StringArray::fromLines("800k"       + newLine +
                                                                       "1200k"                ) ;
}

#endif // CONSTANTS_H_INCLUDED
