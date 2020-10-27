/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "Constants.h"


#define APP_CMD_PAD String("").paddedLeft(' ' , APP_CMD.length())


// names and IDs
const String APP::APP_NAME         = ProjectInfo::projectName ;
const String APP::APP_VERSION      = ProjectInfo::versionString ;
const String APP::APP_CMD          = "av-caster" ;
const String APP::JACK_CLIENT_NAME = APP_NAME ;
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
const Array<int> APP::TIMER_IDS  = Array<int>(timer_ids  , N_TIMERS) ;
const Array<int> APP::TIMER_IVLS = Array<int>(timer_ivls , N_TIMERS) ;

// cli args
const String      APP::CLI_HELP_TOKEN            = "--help" ;
const String      APP::CLI_VERSION_TOKEN         = "--version" ;
const String      APP::CLI_PRESETS_TOKEN         = "--presets" ;
const String      APP::CLI_PRESET_TOKEN          = "--preset" ;
const String      APP::CLI_DISABLE_MEDIA_TOKEN   = "--no-media" ;
const String      APP::CLI_SCREEN_ONLY_TOKEN     = "--screen-only" ;
const String      APP::CLI_CAMERA_ONLY_TOKEN     = "--camera-only" ;
const String      APP::CLI_TEXT_ONLY_TOKEN       = "--text-only" ;
const String      APP::CLI_IMAGE_ONLY_TOKEN      = "--image-only" ;
const String      APP::CLI_DISABLE_PREVIEW_TOKEN = "--no-preview" ;
const String      APP::CLI_DISABLE_AUDIO_TOKEN   = "--no-audio" ;
const String      APP::CLI_DISABLE_CHAT_TOKEN    = "--no-chat" ;
const StringArray APP::CLI_USAGE_MSG             = StringArray::fromLines(
    String("AvCaster Usage:\n")                                                                                               +
    "\n\t" + APP_CMD     + " [ " + CLI_HELP_TOKEN            + " | "                                                          +
                                   CLI_VERSION_TOKEN         + " | "                                                          +
                                   CLI_PRESETS_TOKEN         + " ]"                                                           +
    "\n\t" + APP_CMD     + " [ " + CLI_PRESET_TOKEN          + " <N> ]"                                                       +
    "\n\t" + APP_CMD_PAD + " [ " + CLI_DISABLE_MEDIA_TOKEN   + " | "                                                          +
                                   CLI_SCREEN_ONLY_TOKEN     + " | "                                                          +
                                   CLI_CAMERA_ONLY_TOKEN     + " ]"                                                           +
//                                    CLI_TEXT_ONLY_TOKEN       + " | "                                                          +
//                                    CLI_IMAGE_ONLY_TOKEN      + " ]"                                                           +
    "\n\t" + APP_CMD_PAD + " [ " + CLI_DISABLE_PREVIEW_TOKEN + " ]"                                                           +
                           " [ " + CLI_DISABLE_AUDIO_TOKEN   + " ]"                                                           +
                           " [ " + CLI_DISABLE_CHAT_TOKEN    + " ]"                                                           +
    "\n\n\n\tINFORMATION:"                                                                                                    +
    "\n\n\t\t"                   + CLI_HELP_TOKEN            + "\n\t\t\tprints this message and exits"                        +
    "\n\n\t\t"                   + CLI_VERSION_TOKEN         + "\n\t\t\tprints the application version string and exits"      +
    "\n\n\t\t"                   + CLI_PRESETS_TOKEN         + "\n\t\t\tlist stored presets and exits"                        +
    "\n\n\n\tCONFIGURATION:"                                                                                                  +
    "\n\n\t\t"                   + CLI_PRESET_TOKEN + " <N>" + "\n\t\t\tstarts " + APP_NAME + " with initial preset number N" +
    "\n\n\n\tFEATURE SWITCHES:"                                                                                               +
    "\n\n\t\t"                   + CLI_DISABLE_MEDIA_TOKEN   + "\n\t\t\tdisables all media input and output (safe mode)"      +
    "\n\n\t\t"                   + CLI_SCREEN_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders screen only"         +
    "\n\n\t\t"                   + CLI_CAMERA_ONLY_TOKEN     + "\n\t\t\tdisables compositing and renders webcam only"         +
//     "\n\n\t\t"                   + CLI_TEXT_ONLY_TOKEN       + "\n\t\t\tdisables compositing and renders text overlay only"   +
//     "\n\n\t\t"                   + CLI_IMAGE_ONLY_TOKEN      + "\n\t\t\tdisables compositing and renders static image only"   +
    "\n\n\t\t"                   + CLI_DISABLE_PREVIEW_TOKEN + "\n\t\t\tdisables realtime preview"                            +
    "\n\n\t\t"                   + CLI_DISABLE_AUDIO_TOKEN   + "\n\t\t\tdisables audio capture"                               +
    "\n\n\t\t"                   + CLI_DISABLE_CHAT_TOKEN    + "\n\t\t\tdisables chat"                                        ) ;

// filesystem
const String APP::FLV_FILE_EXT = ".flv" ;
const String APP::PNG_FILE_EXT = ".png" ;
// const String APP::JPG_FILE_EXT  = ".jpg" ;
// const String APP::JPEG_FILE_EXT = ".jpeg" ;
// const String APP::GIF_FILE_EXT  = ".gif" ;


String APP::IconFilename()    { return APP_CMD + PNG_FILE_EXT ;                   }
String APP::DesktopFilename() { return APP_CMD + ".desktop" ;                     }
String APP::IconsPath()       { return ".local/share/icons/hicolor/48x48/apps/" ; }
String APP::AppsPath()        { return ".local/share/applications/" ;             }
File   APP::CamerasDevDir()   { return File("/sys/class/video4linux") ;                           }
File   APP::HomeDir()         { return File::getSpecialLocation(File::userHomeDirectory           ) ; }
File   APP::AppdataDir()      { return File::getSpecialLocation(File::userApplicationDataDirectory) ; }
File   APP::PicturesDir()     { return File::getSpecialLocation(File::userPicturesDirectory       ) ; }
File   APP::VideosDir()       { return File::getSpecialLocation(File::userMoviesDirectory         ) ; }
File   APP::BinFile()         { return File::getSpecialLocation(File::currentExecutableFile       ) ; }
File   APP::LogoFile()        { return BinFile().getSiblingFile(IconFilename()) ;                  }
File   APP::IconFile()        { return HomeDir().getChildFile  (IconsPath() + IconFilename()   ) ; }
File   APP::DesktopFile()     { return HomeDir().getChildFile  (AppsPath()  + DesktopFilename()) ; }
String APP::DesktopText()     { return String("[Desktop Entry]\r\n")                                  +
                                              "Name=AvCaster\r\n"                                     +
                                              "GenericName=\r\n"                                      +
                                              "Comment=Desktop, webcam, and audio streaming tool\r\n" +
                                              "Categories=AudioVideo;\r\n"                            +
                                              "Exec=" + BinFile() .getFullPathName() + "\r\n" +       +
                                              "Icon=" + IconFile().getFullPathName() + "\r\n" +       +
                                              "StartupNotify=true\r\n"                                +
                                              "Terminal=false\r\n"                                    +
                                              "Type=Application\r\n"                                  ; }
