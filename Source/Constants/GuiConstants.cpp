
#include "Constants.h"


// common
const int    GUI::PAD                   = 4 ;
const int    GUI::PAD3                  = (PAD * 3) ;
const int    GUI::PAD4                  = (PAD * 4) ;
const int    GUI::PAD6                  = (PAD * 6) ;
const int    GUI::PAD8                  = (PAD * 8) ;
const Colour GUI::TEXT_EMPTY_COLOR      = Colour(0x80808080) ;
const Colour GUI::TEXT_NORMAL_COLOR     = Colour(0xFFC0C0C0) ;
const Colour GUI::TEXT_INVALID_COLOR    = Colour(0xFFFF0000) ;
const Colour GUI::TEXT_HILITE_COLOR     = Colour(0xFFFFFFFF) ;
const Colour GUI::TEXT_HILITEBG_COLOR   = Colour(0xFF000040) ;
const Colour GUI::TEXT_CARET_COLOR      = Colour(0xFFFFFFFF) ;
const Colour GUI::TEXT_FOCUS_COLOR      = Colour(0xFF000000) ;
const Colour GUI::TEXT_SHADOW_COLOR     = Colour(0xFF000000) ;
const Colour GUI::TEXT_BG_COLOR         = Colour(0xFF000000) ;
const Colour GUI::TEXT_INVALID_BG_COLOR = Colour(0xFF200000) ;

// MainWindow
const int    GUI::BORDERS_W       = 2 ;
const int    GUI::TITLEBAR_H      = 24 ;
const int    GUI::WINDOW_W        = 760 - BORDERS_W ;              // jucer 758
const int    GUI::WINDOW_H        = 788 - BORDERS_W - TITLEBAR_H ; // jucer 762
const int    GUI::TITLEBAR_BTNS   = DocumentWindow::minimiseButton | DocumentWindow::closeButton ;
const String GUI::IDLE_TITLE_TEXT = "(Idle)" ;
const String GUI::FILE_TITLE_TEXT = "(Recording)" ;
const String GUI::RTMP_TITLE_TEXT = "(Broadcasting)" ;
#ifdef TRAY_ICON
const String GUI::TRAY_TOOTIP     = "\nClick to show/hide\nRight-click for menu" ;
#endif // TRAY_ICON

// Controls
const String GUI::FILE_XMIT_TEXT = "Record" ;
const String GUI::RTMP_XMIT_TEXT = "Transmit" ;

// Chat
const int    GUI::N_STATIC_CHATLIST_CHILDREN = 2 ; // ASSERT: num ChatList static widgets
const int    GUI::SCROLLBAR_W                = 12 ;
const int    GUI::CHATLIST_W                 = 128 ;
const int    GUI::CHATLIST_X                 = CHATLIST_W + SCROLLBAR_W + PAD8 + PAD ;
const int    GUI::CHATLIST_Y                 = PAD8 + PAD ;
const int    GUI::OFFSET_CHATLIST_X          = CHATLIST_X + SCROLLBAR_W + PAD ;
const int    GUI::EMPTY_CHATLIST_H           = 24 ;
const int    GUI::CHATLIST_ITEM_H            = 24 ;
const int    GUI::CHATLIST_ITEM_W            = CHATLIST_W - PAD6 ;
const int    GUI::PADDED_CHATLIST_ITEM_H     = CHATLIST_ITEM_H + PAD ;
const int    GUI::FONT_SIZE                  = 16 ;
const String GUI::CHAT_GROUP_TITLE           = "Chat" ;
const String GUI::CHAT_PROMPT_TEXT           = "<type some chat here - then press ENTER key to send>" ;
const String GUI::CONNECTING_TEXT            = "(connecting)" ;
const String GUI::CLIENT_NICK                = "AvCaster" ;
const String GUI::SERVER_NICK                = "SERVER" ;
const String GUI::IRC_USER_PREFIX            = "IRC" ;
const String GUI::LCTV_USER_PREFIX           = "LCTV" ;

// Config
const String GUI::SCREEN_GROUP_TEXT      = "Screen" ;
const String GUI::CAMERA_GROUP_TEXT      = "Camera" ;
const String GUI::AUDIO_GROUP_TEXT       = "Audio" ;
const String GUI::TEXT_GROUP_TEXT        = "Text" ;
const String GUI::IMAGE_GROUP_TEXT       = "Image" ;
const String GUI::OUTPUT_GROUP_TEXT      = "Output" ;
const String GUI::CHAT_GROUP_TEXT        = "Chat" ;
const String GUI::DELETE_BTN_CANCEL_TEXT = "Cancel" ;
const String GUI::DELETE_BTN_DELETE_TEXT = "Delete" ;
const String GUI::DELETE_BTN_RESET_TEXT  = "Reset" ;
const String GUI::IMAGE_CHOOSER_TEXT     = "Select an image file ..." ;
const String GUI::DEST_FILE_TEXT         = "Location:" ;
const String GUI::DEST_RTMP_TEXT         = "URI:" ;
const String GUI::DEST_LCTV_TEXT         = "Stream Key:" ;
const String GUI::IMG_FILE_EXTENSIONS    = "*" + APP::PNG_FILE_EXT ;
// const String GUI::IMG_FILE_EXTS          = "*" + APP::PNG_FILE_EXT  + ",*" +
//                                                  APP::JPEG_FILE_EXT + ",*" +
//                                                  APP::GIF_FILE_EXT         ;
const double GUI::MIN_DISPLAY_N    = 0.0 ;
const double GUI::MAX_DISPLAY_N    = 4.0 ;
const double GUI::MIN_SCREEN_N     = 0.0 ;
const double GUI::MAX_SCREEN_N     = 4.0 ;
const double GUI::MIN_N_CHANNELS   = 0.0 ;
const double GUI::MAX_N_CHANNELS   = 2.0 ;
const int    GUI::MAX_RES_N_CHARS  = 4 ;
const int    GUI::MAX_MOTD_LEN     = 2048 ;
const int    GUI::MAX_FILENAME_LEN = 255 ;
const int    GUI::MAX_PORT_N_CHARS = 5 ;

// StatusBar
const String GUI::INIT_STATUS_TEXT  = "Initializing" ;
const String GUI::READY_STATUS_TEXT = "Ready" ;

// Alerts
const String GUI::MODAL_WARNING_TITLE = APP::APP_NAME + " Warning" ;
const String GUI::MODAL_ERROR_TITLE   = APP::APP_NAME + " Error" ;

// user error messages
const String GUI::GST_INSUFFICIENT_ERROR_MSG  = "Insufficient gStreamer version detected.\n\n"       +
                                                APP::APP_NAME + " requires gStreamer v"    +
                                                String(GST::MIN_MAJOR_VERSION) + "."                 +
                                                String(GST::MIN_MINOR_VERSION) + " or greater.\n\n"  +
                                                "See the README.md for detailed build instructions." ;
const String GUI::IRC_INSUFFICIENT_ERROR_MSG  = "Insufficient libircclient version detected.\n\n"    +
                                                APP::APP_NAME + " requires libircclient v" +
                                                String(IRC::MIN_MAJOR_VERSION) + "."                 +
                                                String(IRC::MIN_MINOR_VERSION) + " or greater.\n\n"  +
                                                "See the README.md for detailed build instructions." ;
const String GUI::GST_INIT_ERROR_MSG          = "Error initializing gStreamer." ;
const String GUI::GST_PIPELINE_INST_ERROR_MSG = "Error creating static GstElements." ;
const String GUI::GST_BUS_INST_ERROR_MSG      = "Error initializing pipelie message handler." ;
const String GUI::GST_ADD_ERROR_MSG           = "Error adding static GstElements to the pipeline." ;
const String GUI::GST_PIPELINE_INIT_ERROR_MSG = "Error initializing dynamic GstElements." ;
const String GUI::GST_CONFIG_ERROR_MSG        = "Error configuring dynamic GstElements." ;
const String GUI::GST_XWIN_ERROR_MSG          = "Error attaching gStreamer to native x-window." ;
const String GUI::SCREENCAP_INIT_ERROR_MSG    = "Error creating ScreencapBin GstElements." ;
const String GUI::CAMERA_INIT_ERROR_MSG       = "Error creating CameraBin GstElements." ;
const String GUI::TEXT_INIT_ERROR_MSG         = "Error creating TextBin GstElements." ;
const String GUI::IMAGE_INIT_ERROR_MSG        = "Error creating ImageBin GstElements." ;
const String GUI::VMIXER_INIT_ERROR_MSG       = "Error creating CompositorBin GstElements." ;
const String GUI::VMIXER_PAD_INIT_ERROR_MSG   = "Error creating CompositorBin GstPads." ;
const String GUI::PREVIEW_INIT_ERROR_MSG      = "Error creating PreviewBin GstElements." ;
const String GUI::AUDIO_INIT_ERROR_MSG        = "Error creating AudioBin GstElements." ;
const String GUI::MUXER_INIT_ERROR_MSG        = "Error creating MuxerBin GstElements." ;
const String GUI::OUTPUT_INIT_ERROR_MSG       = "Error creating OutputBin GstElements." ;
const String GUI::SCREENCAP_LINK_ERROR_MSG    = "Error linking ScreencapBin GstElements." ;
const String GUI::CAMERA_LINK_ERROR_MSG       = "Error linking CameraBin GstElements." ;
const String GUI::TEXT_LINK_ERROR_MSG         = "Error linking TextBin GstElements." ;
const String GUI::IMAGE_LINK_ERROR_MSG        = "Error linking ImageBin GstElements." ;
const String GUI::VMIXER_LINK_ERROR_MSG       = "Error linking CompositorBin GstElements." ;
const String GUI::VMIXER_PAD_LINK_ERROR_MSG   = "Error linking CompositorBin GstPads." ;
const String GUI::VMIXER_BIN_LINK_ERROR_MSG   = "Error linking CompositorBin to other bins." ;
const String GUI::PREVIEW_LINK_ERROR_MSG      = "Error linking PreviewBin GstElements." ;
const String GUI::AUDIO_LINK_ERROR_MSG        = "Error linking AudioBin GstElements." ;
const String GUI::MUXER_LINK_ERROR_MSG        = "Error linking MuxerBin GstElements." ;
const String GUI::MUXER_BIN_LINK_ERROR_MSG    = "Error linking MuxerBin to other bins." ;
const String GUI::OUTPUT_LINK_ERROR_MSG       = "Error linking OutputBin GstElements." ;
const String GUI::GST_STATE_ERROR_MSG         = "Invalid configuration." ;
const String GUI::STORAGE_WRITE_ERROR_MSG     = "I/O error storing configuration." ;
const String GUI::PRESET_NAME_ERROR_MSG       = "Enter a name for this preset in the \"Preset\" box or press the \"Cancel\" button." ;
const String GUI::PRESET_RENAME_ERROR_MSG     = "A preset already exists with that name." ;
const String GUI::CONFIG_INVALID_ERROR_MSG    = "Invalid paramenter(s) - correct the errors indicated in red." ;
const String GUI::ALSA_INIT_ERROR_MSG         = "Error initializing ALSA capture device.\n\n" ;
const String GUI::PULSE_INIT_ERROR_MSG        = "Error connecting to PulseAudio server.\n\n" ;
const String GUI::JACK_INIT_ERROR_MSG         = "Error connecting to Jack server.\n\n" ;
const String GUI::FILE_SINK_ERROR_MSG         = "Error creating local output file.\n\n" ;

// Config label texts
const String GUI::DISPLAY_N_LABEL   = "Display #:" ;
const String GUI::SCREEN_N_LABEL    = "Screen #:" ;
const String GUI::SCREEN_W_LABEL    = "Width:" ;
const String GUI::SCREEN_H_LABEL    = "Height:" ;
const String GUI::X_OFFSET_LABEL    = "Offset X:" ;
const String GUI::Y_OFFSET_LABEL    = "Offset Y:" ;
const String GUI::CAMERA_DEV_LABEL  = "Device:" ;
const String GUI::CAMERA_RES_LABEL  = "Resolution:" ;
const String GUI::AUDIO_API_LABEL   = "Interface:" ;
const String GUI::AUDIO_DEV_LABEL   = "Device:" ;
const String GUI::AUDIO_CODEC_LABEL = "Codec:" ;
const String GUI::N_CHANNELS_LABEL  = "Channels:" ;
const String GUI::SAMPLERATE_LABEL  = "Samplerate:" ;
const String GUI::AUDIO_RATE_LABEL  = "Bitrate:" ;
const String GUI::MOTD_LABEL        = "Message:" ;
const String GUI::TEXT_STYLE_LABEL  = "Style:" ;
const String GUI::TEXT_POS_LABEL    = "Position:" ;
const String GUI::IMAGE_LOC_LABEL   = "Location:" ;
const String GUI::IMAGE_BTN_LABEL   = "Browse:" ;
const String GUI::OUTPUT_SINK_LABEL = "Stream:" ;
const String GUI::OUTPUT_W_LABEL    = "Width:" ;
const String GUI::OUTPUT_H_LABEL    = "Height:" ;
const String GUI::FRAMERATE_LABEL   = "FPS:" ;
const String GUI::VIDEO_RATE_LABEL  = "Bitrate:" ;
const String GUI::OUTPUT_DEST_LABEL = "Destination:" ;
const String GUI::NETWORK_LABEL     = "Host:" ;
const String GUI::PORT_LABEL        = "Port:" ;
const String GUI::NICK_LABEL        = "Nick:" ;
const String GUI::PASS_LABEL        = "Password:" ;
const String GUI::CHANNEL_LABEL     = "Channel:" ;
const String GUI::GREETING_LABEL    = "Greeting:" ;
const String GUI::TIMESTAMP_LABEL   = "Show Timestamps:" ;
const String GUI::JOINPART_LABEL    = "Show Joins/Parts:" ;

// Config help texts
const String GUI::CONFIG_SCREEN_HELP = "The " + SCREEN_GROUP_TEXT + " pane has controls to configure the screen capture." ;
const String GUI::CONFIG_CAMERA_HELP = "The " + CAMERA_GROUP_TEXT + " pane has controls to configure the camera capture device." ;
const String GUI::CONFIG_AUDIO_HELP  = "The " + AUDIO_GROUP_TEXT  + " pane has controls to configure the audio capture device." ;
const String GUI::CONFIG_TEXT_HELP   = "The " + TEXT_GROUP_TEXT   + " pane has controls to configure the text overlay. This may be left empty if overlay text is not desired." ;
const String GUI::CONFIG_IMAGE_HELP  = "The " + IMAGE_GROUP_TEXT  + " pane has controls to configure the interstitial image. This is a static image that will be shown to viewers when the stream is paused. If this is left empty then the default " + APP::APP_NAME + " splash image will be shown instead." ;
const String GUI::CONFIG_OUTPUT_HELP = "The " + OUTPUT_GROUP_TEXT + " pane has controls to configure the output stream, either to produce a local video file or to stream to a server over the network." ;
const String GUI::CONFIG_CHAT_HELP   = "The " + CHAT_GROUP_TEXT   + " pane has controls to configure the chat. These may be left empty if chat is not desired." ;
const String GUI::DISPLAY_N_HELP     = DISPLAY_N_LABEL   + " Select the X display to capture (usually 0)." ;
const String GUI::SCREEN_N_HELP      = SCREEN_N_LABEL    + " Select the X screen to capture (usually 0)." ;
const String GUI::SCREEN_W__HELP     = SCREEN_W_LABEL    + " Specify the width of the area to capture (in pixels)." ;
const String GUI::SCREEN_H__HELP     = SCREEN_H_LABEL    + " Specify the height of the area to capture (in pixels)." ;
const String GUI::X_OFFSET_HELP      = X_OFFSET_LABEL    + " Specify the left edge position of the area to capture (in pixels)." ;
const String GUI::Y_OFFSET_HELP      = Y_OFFSET_LABEL    + " Specify the top edge position of the area to capture (in pixels)." ;
const String GUI::CAMERA_DEV_HELP    = CAMERA_DEV_LABEL  + " Select the camera device to capture." ;
const String GUI::CAMERA_RES_HELP    = CAMERA_RES_LABEL  + " Select the camera capture resolution." ;
const String GUI::AUDIO_API_HELP     = AUDIO_API_LABEL   + " Select the audio driver interface." ;
const String GUI::AUDIO_DEV_HELP     = AUDIO_DEV_LABEL   + " Select the audio device to capture." ;
const String GUI::AUDIO_CODEC_HELP   = AUDIO_CODEC_LABEL + " Select the audio encoder." ;
const String GUI::N_CHANNELS_HELP    = N_CHANNELS_LABEL  + " Specify the number of audio channels to capture." ;
const String GUI::SAMPLERATE_HELP    = SAMPLERATE_LABEL  + " Select the audio sample rate (22050 is good for voice, 48000 for music)." ;
const String GUI::AUDIO_RATE_HELP    = AUDIO_RATE_LABEL  + " Select the audio output bit rate (64k per channel is good)." ;
const String GUI::MOTD_HELP          = MOTD_LABEL        + " Enter the message of the day text." ;
const String GUI::TEXT_STYLE_HELP    = TEXT_STYLE_LABEL  + " Select still or scrolling text overlay style." ;
const String GUI::TEXT_POS_HELP      = TEXT_POS_LABEL    + " Select text overlay screen position." ;
const String GUI::IMAGE_LOC_HELP     = IMAGE_LOC_LABEL   + " Specify the location of the image file." ;
const String GUI::IMAGE_BTN_HELP     = IMAGE_BTN_LABEL   + " Brwose filesystem for the image file." ;
const String GUI::OUTPUT_SINK_HELP   = OUTPUT_SINK_LABEL + " Select stream type." ;
const String GUI::OUTPUT_W__HELP     = OUTPUT_W_LABEL    + " Specify the width of the output stream (in pixels)." ;
const String GUI::OUTPUT_H__HELP     = OUTPUT_H_LABEL    + " Specify the width of the output stream (in pixels)." ;
const String GUI::FRAMERATE_HELP     = FRAMERATE_LABEL   + " Select the stream output frame rate (12 is good for screen capture, 30 for video)." ;
const String GUI::VIDEO_RATE_HELP    = VIDEO_RATE_LABEL  + " Select the stream output bit rate (800k - 1200k is good)." ;
const String GUI::OUTPUT_DEST_HELP   = OUTPUT_DEST_LABEL + " Specify the local file or stream server URL." ;
const String GUI::NETWORK_HELP       = NETWORK_LABEL     + " Specify the chat network or host URL." ;
const String GUI::PORT_HELP          = PORT_LABEL        + " Specify the chat server port." ;
const String GUI::NICK_HELP          = NICK_LABEL        + " Specify your nickname on the chat network." ;
const String GUI::PASS_HELP          = PASS_LABEL        + " Specify the server password (this is not your NICKSERV pass)." ;
const String GUI::CHANNEL_HELP       = CHANNEL_LABEL     + " Specify the channel to auto-join." ;
const String GUI::GREETING_HELP      = GREETING_LABEL    + " Specify a pounce greeting to all entering chatters." ;
const String GUI::TIMESTAMP_HELP     = TIMESTAMP_LABEL   + " Show or hide timestamps of chat messages." ;
const String GUI::JOINPART_HELP      = JOINPART_LABEL    + " Show or hide notices of chatters entering and leaving the channel." ;
const String GUI::SCREEN_HELP_TEXT   = String("Screen Capture Configuration:\n\n") +
                                       CONFIG_SCREEN_HELP                 + "\n\n" +
                                       DISPLAY_N_HELP                       + "\n" +
                                       SCREEN_N_HELP                        + "\n" +
                                       SCREEN_W__HELP                       + "\n" +
                                       SCREEN_H__HELP                       + "\n" +
                                       X_OFFSET_HELP                        + "\n" +
                                       Y_OFFSET_HELP                               ;
const String GUI::CAMERA_HELP_TEXT   = String("Camera Device Configuration:\n\n") +
                                       CONFIG_CAMERA_HELP                + "\n\n" +
                                       CAMERA_DEV_HELP                     + "\n" +
                                       CAMERA_RES_HELP                            ;
const String GUI::AUDIO_HELP_TEXT    = String("Audio Device Configuration:\n\n") +
                                       CONFIG_AUDIO_HELP                + "\n\n" +
                                       AUDIO_API_HELP                     + "\n" +
                                       AUDIO_DEV_HELP                     + "\n" +
                                       AUDIO_CODEC_HELP                   + "\n" +
                                       N_CHANNELS_HELP                    + "\n" +
                                       SAMPLERATE_HELP                    + "\n" +
                                       AUDIO_RATE_HELP                           ;
const String GUI::TEXT_HELP_TEXT     = String("Text Overlay Configuration:\n\n") +
                                       CONFIG_TEXT_HELP                 + "\n\n" +
                                       MOTD_HELP                          + "\n" +
                                       TEXT_STYLE_HELP                    + "\n" +
                                       TEXT_POS_HELP                             ;
const String GUI::IMAGE_HELP_TEXT    = String("Interstitial Configuration:\n\n") +
                                       CONFIG_IMAGE_HELP                + "\n\n" +
                                       IMAGE_LOC_HELP                     + "\n" +
                                       IMAGE_BTN_HELP                            ;
const String GUI::OUTPUT_HELP_TEXT   = String("Output Stream Configuration:\n\n") +
                                       CONFIG_OUTPUT_HELP                + "\n\n" +
                                       OUTPUT_SINK_HELP                    + "\n" +
                                       OUTPUT_W__HELP                      + "\n" +
                                       OUTPUT_H__HELP                      + "\n" +
                                       FRAMERATE_HELP                      + "\n" +
                                       VIDEO_RATE_HELP                     + "\n" +
                                       OUTPUT_DEST_HELP                           ;
const String GUI::CHAT_HELP_TEXT     = String("Chat Configuration:\n\n") +
                                       CONFIG_CHAT_HELP         + "\n\n" +
                                       NETWORK_HELP               + "\n" +
                                       PORT_HELP                  + "\n" +
                                       NICK_HELP                  + "\n" +
                                       PASS_HELP                  + "\n" +
                                       CHANNEL_HELP               + "\n" +
                                       GREETING_HELP              + "\n" +
                                       TIMESTAMP_HELP             + "\n" +
                                       JOINPART_HELP                     ;
