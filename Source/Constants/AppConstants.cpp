
#include "Constants.h"


// names and IDs
const String APP::APP_NAME         = "AvCaster" ;
const String APP::APP_CMD          = "av-caster" ;
const String APP::JACK_CLIENT_NAME = APP::APP_NAME ;
const String APP::IRC_THREAD_NAME  = "av-caster-irc" ;
const String APP::DIGITS           = "0123456789" ;
const String APP::LETTERS          = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
const String APP::ALPHANUMERIC     = DIGITS + LETTERS ;
const String APP::VALID_ID_CHARS   = ALPHANUMERIC + "_- " ;
const String APP::VALID_URI_CHARS  = ALPHANUMERIC + "_-.:/?=@#&" ;
const String APP::VALID_NICK_CHARS = ALPHANUMERIC + "_-@#&[]" ;
const String APP::FILTER_CHARS     = "-_.:/?=@#&[] " ;
const String APP::REPLACE_CHARS    = String::repeatedString("-" , FILTER_CHARS.length()) ;

// timers
int timer_ids[]  = { APP::TIMER_HI_ID  , APP::TIMER_MED_ID  , APP::TIMER_LO_ID  } ;
int timer_ivls[] = { APP::TIMER_HI_IVL , APP::TIMER_MED_IVL , APP::TIMER_LO_IVL } ;
const Array<int> APP::TIMER_IDS  = Array<int>(timer_ids  , APP::N_TIMERS) ;
const Array<int> APP::TIMER_IVLS = Array<int>(timer_ivls , APP::N_TIMERS) ;

// cli args
const String APP::CLI_HELP_TOKEN            = "--help" ;
const String APP::CLI_PRESETS_TOKEN         = "--presets" ;
const String APP::CLI_VERSION_TOKEN         = "--version" ;
const String APP::CLI_PRESET_TOKEN          = "--preset" ;
const String APP::CLI_DISABLE_MEDIA_TOKEN   = "--no-media" ;
const String APP::CLI_SCREEN_ONLY_TOKEN     = "--screen-only" ;
const String APP::CLI_CAMERA_ONLY_TOKEN     = "--camera-only" ;
const String APP::CLI_TEXT_ONLY_TOKEN       = "--text-only" ;
const String APP::CLI_IMAGE_ONLY_TOKEN      = "--image-only" ;
const String APP::CLI_DISABLE_PREVIEW_TOKEN = "--no-preview" ;
const String APP::CLI_DISABLE_AUDIO_TOKEN   = "--no-audio" ;
const String APP::CLI_DISABLE_CHAT_TOKEN    = "--no-chat" ;
#ifdef DEBUG
const String APP::CLI_VERSION_MSG = "AvCaster v" + String(ProjectInfo::versionString) + " (DEBUG)" ;
#else // DEBUG
const String APP::CLI_VERSION_MSG = "AvCaster v" + String(ProjectInfo::versionString) ;
#endif // DEBUG
const String APP::CLI_USAGE_MSG   = "AvCaster Usage:\n\n\t" + APP::APP_CMD + " [ "  + CLI_HELP_TOKEN            + " | "                                                               +
                                                                                      CLI_PRESETS_TOKEN         + " | "                                                               +
                                                                                      CLI_VERSION_TOKEN         + " ]"                                                                +
                                                     "\n\t" + APP::APP_CMD + " [ "  + CLI_PRESET_TOKEN          + " N    ] "                                                          +
                                                     "\n\t" + APP::APP_CMD + " [ "  + CLI_DISABLE_MEDIA_TOKEN   + "    ] "                                                            +
                                                                              "[ "  + CLI_DISABLE_PREVIEW_TOKEN + "  ] "                                                              +
                                                                              "[ "  + CLI_DISABLE_AUDIO_TOKEN   + "  ] "                                                              +
                                                                              "[ "  + CLI_DISABLE_CHAT_TOKEN    + " ]"                                                                +
                                                     "\n\t" + APP::APP_CMD + " [ "  + CLI_SCREEN_ONLY_TOKEN     + " | "                                                               +
                                                                              "  "  + CLI_CAMERA_ONLY_TOKEN     + " | "                                                               +
      //                                                                             "  "  + CLI_TEXT_ONLY_TOKEN       + " | "                                                          +
      //                                                                             "  "  + CLI_IMAGE_ONLY_TOKEN      + " ] "                                                          +
                                                   "\n\n\n\tINFORMATION:"                                                                                                             +
                                                   "\n\n\t\t"                       + CLI_HELP_TOKEN            + "\n\t\t\tprints this message and exits"                             +
                                                   "\n\n\t\t"                       + CLI_PRESETS_TOKEN         + "\n\t\t\tlist stored presets and exits"                             +
                                                   "\n\n\t\t"                       + CLI_VERSION_TOKEN         + "\n\t\t\tprints the application version string and exits"           +
                                                   "\n\n\n\tCONFIGURATION:"                                                                                                           +
                                                   "\n\n\t\t"                       + CLI_PRESET_TOKEN + " n"   + "\n\t\t\tstarts " + APP::APP_NAME + " with initial preset number N" +
                                                   "\n\n\n\tFEATURE SWITCHES:"                                                                                                        +
                                                   "\n\n\t\t"                       + CLI_DISABLE_MEDIA_TOKEN   + "\n\t\t\tdisables all media and stream output"                      +
                                                   "\n\n\t\t"                       + CLI_SCREEN_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders screen only"              +
                                                   "\n\n\t\t"                       + CLI_CAMERA_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders webcam only"              +
//                                                       "\n\n\t\t"                       + CLI_TEXT_ONLY_TOKEN       + "\n\t\t\tdisables compositing and renders text overlay only"   +
//                                                       "\n\n\t\t"                       + CLI_IMAGE_ONLY_TOKEN      + "\n\t\t\tdisables compositing and renders static image only"   +
                                                   "\n\n\t\t"                       + CLI_DISABLE_PREVIEW_TOKEN + "\n\t\t\tdisables realtime preview"                                 +
                                                   "\n\n\t\t"                       + CLI_DISABLE_AUDIO_TOKEN   + "\n\t\t\tdisables audio capture"                                    +
                                                   "\n\n\t\t"                       + CLI_DISABLE_CHAT_TOKEN    + "\n\t\t\tdisables chat"                                             ;

// filesystem
const String APP::FLV_FILE_EXT  = ".flv" ;
const String APP::PNG_FILE_EXT  = ".png" ;
// const String APP::JPG_FILE_EXT  = ".jpg" ;
// const String APP::JPEG_FILE_EXT = ".jpeg" ;
// const String APP::GIF_FILE_EXT  = ".gif" ;
String APP::iconsPath()       { return ".local/share/icons/hicolor/48x48/apps/" ; }
String APP::appsPath()        { return ".local/share/applications/" ;             }
String APP::iconFilename()    { return APP_CMD + PNG_FILE_EXT ;                   }
String APP::desktopFilename() { return APP_CMD + ".desktop" ;                     }
File   APP::camerasDevDir()   { return File("/sys/class/video4linux") ;                           }
File   APP::homeDir()         { return File::getSpecialLocation(File::userHomeDirectory           ) ; }
File   APP::appdataDir()      { return File::getSpecialLocation(File::userApplicationDataDirectory) ; }
File   APP::picturesDir()     { return File::getSpecialLocation(File::userPicturesDirectory       ) ; }
File   APP::videosDir()       { return File::getSpecialLocation(File::userMoviesDirectory         ) ; }
File   APP::binFile()         { return File::getSpecialLocation(File::currentExecutableFile       ) ; }
File   APP::logoFile()        { return binFile().getSiblingFile(iconFilename()) ;                  }
File   APP::iconFile()        { return homeDir().getChildFile  (iconsPath() + iconFilename()   ) ; }
File   APP::desktopFile()     { return homeDir().getChildFile  (appsPath()  + desktopFilename()) ; }
String APP::desktopText()     { return String("[Desktop Entry]\r\n")                                  +
                                              "Name=AvCaster\r\n"                                     +
                                              "GenericName=\r\n"                                      +
                                              "Comment=Desktop, webcam, and audio streaming tool\r\n" +
                                              "Categories=AudioVideo;\r\n"                            +
                                              "Exec=" + binFile() .getFullPathName() + "\r\n" +       +
                                              "Icon=" + iconFile().getFullPathName() + "\r\n" +       +
                                              "StartupNotify=true\r\n"                                +
                                              "Terminal=false\r\n"                                    +
                                              "Type=Application\r\n"                                  ; }
