#ifndef _APPCONSTANTS_H_
#define _APPCONSTANTS_H_


/** the APP class defines configuration and runtime constants
        pertaining to the core AvCaster application and business logic */
class APP
{
public:

  APP() ;


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

  static const int        N_TIMERS     = 4 ;
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
  static const String PNG_FILE_EXT ;
  // static const String JPG_FILE_EXT :
  // static const String JPEG_FILE_EXT ;
  // static const String GIF_FILE_EXT ;
  String ICONS_PATH ;
  String APPS_PATH ;
  String ICON_FILENAME ;
  String DESKTOP_FILENAME ;
  File   BIN_FILE ;
  File   HOME_DIR ;
  File   APPDATA_DIR ;
  File   PICTURES_DIR ;
  File   VIDEOS_DIR ;
  File   LOGO_FILE ;
  File   ICON_FILE ;
  File   DESKTOP_FILE ;
  File   CAMERAS_DEV_DIR ;
  String DESKTOP_TEXT ;
} ;

#endif // _APPCONSTANTS_H_
