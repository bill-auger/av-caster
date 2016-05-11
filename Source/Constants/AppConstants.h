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
  static const String CLI_HELP_TOKEN ;
  static const String CLI_PRESETS_TOKEN ;
  static const String CLI_VERSION_TOKEN ;
  static const String CLI_PRESET_TOKEN ;
  static const String CLI_DISABLE_MEDIA_TOKEN ;
  static const String CLI_SCREEN_ONLY_TOKEN ;
  static const String CLI_CAMERA_ONLY_TOKEN ;
  static const String CLI_TEXT_ONLY_TOKEN ;
  static const String CLI_IMAGE_ONLY_TOKEN ;
  static const String CLI_DISABLE_PREVIEW_TOKEN ;
  static const String CLI_DISABLE_AUDIO_TOKEN ;
  static const String CLI_DISABLE_CHAT_TOKEN ;
  static const String CLI_VERSION_MSG ;
  static const String CLI_USAGE_MSG ;

  // filesystem
  static String iconsPath()       ;
  static String appsPath()        ;
  static String iconFilename()    ;
  static String desktopFilename() ;
  static File   camerasDevDir()   ;
  static File   homeDir()         ;
  static File   appdataDir()      ;
  static File   picturesDir()     ;
  static File   videosDir()       ;
  static File   binFile()         ;
  static File   logoFile()        ;
  static File   iconFile()        ;
  static File   desktopFile()     ;
  static String desktopText()     ;


  // filesystem
  static const String FLV_FILE_EXT ;
  static const String PNG_FILE_EXT ;
  // static const String JPG_FILE_EXT :
  // static const String JPEG_FILE_EXT ;
  // static const String GIF_FILE_EXT ;
} ;

#endif // _APPCONSTANTS_H_
