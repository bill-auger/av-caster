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


#ifndef _APPCONSTANTS_H_
#define _APPCONSTANTS_H_

#include "JuceHeader.h"


/** the APP class defines configuration and runtime constants
        pertaining to the core AvCaster application and business logic */
class APP
{
public:

  // names and IDs
  static const String APP_NAME ;
  static const String APP_VERSION ;
  static const String APP_CMD ;
  static const String JACK_CLIENT_NAME ;
  static const String IRC_THREAD_NAME ;
  static const String DIGITS ;
  static const String LETTERS ;
  static const String ALPHANUMERIC ;
  static const String VALID_ID_CHARS ;
  static const String VALID_URI_CHARS ;
  static const String VALID_NICK_CHARS ;
  static const String FILTER_CHARS ;
  static const String REPLACE_CHARS ;

  // timers
  static const int        N_TIMERS     = 3 ; // ASSERT: n timers defined below
  static const int        TIMER_HI_ID  = 1 ; static const int TIMER_HI_IVL  = 125 ;
  static const int        TIMER_MED_ID = 2 ; static const int TIMER_MED_IVL = 500 ;
  static const int        TIMER_LO_ID  = 3 ; static const int TIMER_LO_IVL  = 500 ;
  static const Array<int> TIMER_IDS ;
  static const Array<int> TIMER_IVLS ;

  // cli args
  static const String      CLI_HELP_TOKEN ;
  static const String      CLI_VERSION_TOKEN ;
  static const String      CLI_PRESETS_TOKEN ;
  static const String      CLI_PRESET_TOKEN ;
  static const String      CLI_DISABLE_MEDIA_TOKEN ;
  static const String      CLI_SCREEN_ONLY_TOKEN ;
  static const String      CLI_CAMERA_ONLY_TOKEN ;
  static const String      CLI_TEXT_ONLY_TOKEN ;
  static const String      CLI_IMAGE_ONLY_TOKEN ;
  static const String      CLI_DISABLE_PREVIEW_TOKEN ;
  static const String      CLI_DISABLE_AUDIO_TOKEN ;
  static const String      CLI_DISABLE_CHAT_TOKEN ;
  static const StringArray CLI_USAGE_MSG ;

  // filesystem
  static const String FLV_FILE_EXT ;
  static const String PNG_FILE_EXT ;
  // static const String JPG_FILE_EXT :
  // static const String JPEG_FILE_EXT ;
  // static const String GIF_FILE_EXT ;


  // filesystem
  static String IconFilename()    ;
  static String DesktopFilename() ;
  static String IconsPath()       ;
  static String AppsPath()        ;
  static File   CamerasDevDir()   ;
  static File   HomeDir()         ;
  static File   AppdataDir()      ;
  static File   PicturesDir()     ;
  static File   VideosDir()       ;
  static File   BinFile()         ;
  static File   LogoFile()        ;
  static File   IconFile()        ;
  static File   DesktopFile()     ;
  static String DesktopText()     ;
} ;

#endif // _APPCONSTANTS_H_
