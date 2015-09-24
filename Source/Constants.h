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
  static const String CAPTURE_DEVICES_DIR       = "/sys/class/video4linux" ;
  static const String TEST_WHICH_COMMAND        = "which which" ;
  static const String TEST_AVCONV_COMMAND       = "which avconv" ;
  static const String TEST_AVPLAY_COMMAND       = "which avplay" ;
  static const String TEST_X11UTILS_COMMAND     = "which xwininfo" ;
  static const String DISPLAY_DIMS_COMMAND      = "xwininfo -root" ;
  static const String DISPLAY_DIMS_WIDTH_TOKEN  = "Width:" ;
  static const String DISPLAY_DIMS_HEIGHT_TOKEN = "Height:" ;
  static const String AVPLAY_TEST_CAM_COMMAND   = "avplay -f video4linux2 -i " ;

  // avconv state
  static const String      AVCONV_STATS_PREFIX   = "frame=" ;
// static const String AVCONV_READY_MSG          = "Press ctrl-c to stop encoding" ;
  static const String      AVCONV_CAM_BUSY_ERROR = "Input/output error" ;
  static const String      AVCONV_CAMERA_ERROR   = "Invalid data found when processing input" ;
  static const String      AVCONV_NETWORK_ERROR  = "av_interleaved_write_frame(): Operation not permitted" ;
  static const StringArray AVCONV_RUNTIME_ERRORS = StringArray::fromLines(APP::AVCONV_CAMERA_ERROR  + '\n' +
                                                                          APP::AVCONV_NETWORK_ERROR        ) ;

  // user messages
  static const char* GSTREAMER_INIT_EXCEPTION_MSG = "error initializing gStreamer" ;
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
//   static const int    MONITORS_W          = 160 ; // unused
//   static const int    MONITORS_H          = 120 ; // unused
  static const int    MONITOR_W           = 160 ;
  static const int    MONITOR_H           = 120 ;
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
  static const String SHELL_ERROR_MSG       = "Shell error.  Please restart this program." ;
  static const String WHICH_BIN_ERROR_MSG   = "The `which` program was not found on your system.  "    + APP::APP_NAME + " must exit." ;
  static const String AVCONV_BIN_ERROR_MSG  = "The `avconv` program was not found on your system.  "   + APP::APP_NAME + " must exit." ;
  static const String AVPLAY_BIN_ERROR_MSG  = "The `avplay` program was not found on your system.  "   + APP::APP_NAME + " must exit." ;
  static const String XWINIFO_BIN_ERROR_MSG = "The `xwininfo` program was not found on your system.  " + APP::APP_NAME + " has no way to know the size of your screen.  Be sure to select a screen capture resolution that is within the bounds of you display resolution or else the program will not work properly." ;
  static const String NO_CAMERAS_ERROR_MSG  = "No video capture devices were found on you system.  If you indeed have one mounted , you will need to enter its mountpoint manually." ;
  static const String CAM_BUSY_ERROR_MSG    = "The selected capture device is already in use." ;
  static const String GST_INIT_ERROR_MSG    = "Not all elements could be created." ;
  static const String GST_STATE_ERROR_MSG   = "Unable to set the pipeline to the playing state." ;
}

#endif // CONSTANTS_H_INCLUDED
