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


namespace GUI
{
  // common
  static const int PAD  = 4 ;
  static const int PAD2 = PAD * 2 ;
  static const int PAD3 = PAD * 3 ;

  // MainContent
  static const String CONTENT_GUI_ID = "main-content-gui" ;
  static const String APP_NAME       = "FfmpegStreamer" ;
  static const int    BORDERS_W      = 2 ;
  static const int    TITLEBAR_H     = 24 ;
  static const int    CONTENT_W      = 640 - BORDERS_W ;
  static const int    CONTENT_H      = 480 - BORDERS_W - TITLEBAR_H ;

  // StatusBar
  static const String STATUS_GUI_ID    = "statusbar-gui" ;
  static const String INIT_STATUS_TEXT = "Initializing" ;
  static const int    STATUSBAR_H      = 24 ;
}

namespace CLIENT
{
  static const int GUI_TIMER_HI_ID = 1 ; static const int GUI_UPDATE_HI_IVL = 125 ;
  static const int GUI_TIMER_LO_ID = 2 ; static const int GUI_UPDATE_LO_IVL = 5000 ;
}

#endif  // CONSTANTS_H_INCLUDED
