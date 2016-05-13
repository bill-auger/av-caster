#ifndef _GUICONSTANTS_H_
#define _GUICONSTANTS_H_


#include "JuceHeader.h"


/** the GUI class defines configuration and runtime constants
        pertaining to graphical elements                      */
class GUI
{
public:

  // common
  static const int    PAD ;
  static const int    PAD3 ;
  static const int    PAD4 ;
  static const int    PAD6 ;
  static const int    PAD8 ;
  static const Colour TEXT_EMPTY_COLOR ;
  static const Colour TEXT_NORMAL_COLOR ;
  static const Colour TEXT_INVALID_COLOR ;
  static const Colour TEXT_HILITE_COLOR ;
  static const Colour TEXT_HILITEBG_COLOR ;
  static const Colour TEXT_CARET_COLOR ;
  static const Colour TEXT_FOCUS_COLOR ;
  static const Colour TEXT_SHADOW_COLOR ;
  static const Colour TEXT_BG_COLOR ;
  static const Colour TEXT_INVALID_BG_COLOR ;

  // MainWindow
  static const int    BORDERS_W ;
  static const int    TITLEBAR_H ;
  static const int    WINDOW_W ;
  static const int    WINDOW_H ;
  static const int    TITLEBAR_BTNS ;
  static const String IDLE_TITLE_TEXT ;
  static const String FILE_TITLE_TEXT ;
  static const String RTMP_TITLE_TEXT ;
#ifdef TRAY_ICON
  static const String TRAY_TOOTIP ;
#endif // TRAY_ICON

  // Controls
  static const String FILE_XMIT_TEXT ;
  static const String RTMP_XMIT_TEXT ;

  // Chat
  static const int    N_STATIC_CHATLIST_CHILDREN ;
  static const int    SCROLLBAR_W ;
  static const int    CHATLIST_W ;
  static const int    CHATLIST_X ;
  static const int    CHATLIST_Y ;
  static const int    OFFSET_CHATLIST_X ;
  static const int    EMPTY_CHATLIST_H ;
  static const int    CHATLIST_ITEM_H ;
  static const int    CHATLIST_ITEM_W ;
  static const int    PADDED_CHATLIST_ITEM_H ;
  static const int    FONT_SIZE ;
  static const String CHAT_GROUP_TITLE ;
  static const String CHAT_PROMPT_TEXT ;
  static const String CONNECTING_TEXT ;
  static const String CLIENT_NICK ;
  static const String SERVER_NICK ;
  static const String IRC_USER_PREFIX ;
  static const String LCTV_USER_PREFIX ;

  // Config
  static const String SCREEN_GROUP_TEXT ;
  static const String CAMERA_GROUP_TEXT ;
  static const String AUDIO_GROUP_TEXT ;
  static const String TEXT_GROUP_TEXT ;
  static const String IMAGE_GROUP_TEXT ;
  static const String OUTPUT_GROUP_TEXT ;
  static const String CHAT_GROUP_TEXT ;
  static const String DELETE_BTN_CANCEL_TEXT ;
  static const String DELETE_BTN_DELETE_TEXT ;
  static const String DELETE_BTN_RESET_TEXT ;
  static const String IMAGE_CHOOSER_TEXT ;
  static const String DISPLAY_N_TEXT ;
  static const String SCREEN_N_TEXT ;
  static const String SCREEN_W_TEXT ;
  static const String SCREEN_H_TEXT ;
  static const String X_OFFSET_TEXT ;
  static const String Y_OFFSET_TEXT ;
  static const String CAMERA_DEV_TEXT ;
  static const String CAMERA_RES_TEXT ;
  static const String AUDIO_API_TEXT ;
  static const String AUDIO_DEV_TEXT ;
  static const String AUDIO_CODEC_TEXT ;
  static const String N_CHANNELS_TEXT ;
  static const String SAMPLERATE_TEXT ;
  static const String AUDIO_RATE_TEXT ;
  static const String MOTD_TEXT ;
  static const String TEXT_STYLE_TEXT ;
  static const String TEXT_POS_TEXT ;
  static const String IMAGE_LOC_TEXT ;
  static const String IMAGE_BTN_TEXT ;
  static const String OUTPUT_SINK_TEXT ;
  static const String OUTPUT_W_TEXT ;
  static const String OUTPUT_H_TEXT ;
  static const String FRAMERATE_TEXT ;
  static const String VIDEO_RATE_TEXT ;
  static const String DEST_FILE_TEXT ;
  static const String DEST_RTMP_TEXT ;
  static const String DEST_LCTV_TEXT ;
  static const String NETWORK_TEXT ;
  static const String PORT_TEXT ;
  static const String NICK_TEXT ;
  static const String PASS_TEXT ;
  static const String CHANNEL_TEXT ;
  static const String GREETING_TEXT ;
  static const String TIMESTAMP_TEXT ;
  static const String JOINPART_TEXT ;
  static const String IMG_FILE_EXTS ;
  static const double MIN_DISPLAY_N ;
  static const double MAX_DISPLAY_N ;
  static const double MIN_SCREEN_N ;
  static const double MAX_SCREEN_N ;
  static const double MIN_N_CHANNELS ;
  static const double MAX_N_CHANNELS ;
  static const int    MAX_RES_N_CHARS ;
  static const int    MAX_MOTD_LEN ;
  static const int    MAX_FILENAME_LEN ;
  static const int    MAX_PORT_N_CHARS ;

  // StatusBar
  static const String INIT_STATUS_TEXT ;
  static const String READY_STATUS_TEXT ;

  // Alerts
  enum         AlertType { ALERT_TYPE_WARNING , ALERT_TYPE_ERROR } ;
  static const String    MODAL_WARNING_TITLE ;
  static const String    MODAL_ERROR_TITLE ;

  // Config help texts
  static const String CONFIG_SCREEN_HELP ;
  static const String CONFIG_CAMERA_HELP ;
  static const String CONFIG_AUDIO_HELP ;
  static const String CONFIG_TEXT_HELP ;
  static const String CONFIG_IMAGE_HELP ;
  static const String CONFIG_OUTPUT_HELP ;
  static const String CONFIG_CHAT_HELP ;
  static const String DISPLAY_N_HELP ;
  static const String SCREEN_N_HELP ;
  static const String SCREEN_W__HELP ;
  static const String SCREEN_H__HELP ;
  static const String X_OFFSET_HELP ;
  static const String Y_OFFSET_HELP ;
  static const String CAMERA_DEV_HELP ;
  static const String CAMERA_RES_HELP ;
  static const String AUDIO_API_HELP ;
  static const String AUDIO_DEV_HELP ;
  static const String AUDIO_CODEC_HELP ;
  static const String N_CHANNELS_HELP ;
  static const String SAMPLERATE_HELP ;
  static const String AUDIO_RATE_HELP ;
  static const String MOTD_HELP ;
  static const String TEXT_STYLE_HELP ;
  static const String TEXT_POS_HELP ;
  static const String IMAGE_LOC_HELP ;
  static const String IMAGE_BTN_HELP ;
  static const String OUTPUT_SINK_HELP ;
  static const String OUTPUT_W__HELP ;
  static const String OUTPUT_H__HELP ;
  static const String FRAMERATE_HELP ;
  static const String VIDEO_RATE_HELP ;
  static const String DEST_FILE_HELP ;
  static const String DEST_RTMP_HELP ;
  static const String DEST_LCTV_HELP ;
  static const String NETWORK_HELP ;
  static const String PORT_HELP ;
  static const String NICK_HELP ;
  static const String PASS_HELP ;
  static const String CHANNEL_HELP ;
  static const String GREETING_HELP ;
  static const String TIMESTAMP_HELP ;
  static const String JOINPART_HELP ;
  static const String SCREEN_HELP_TEXT ;
  static const String CAMERA_HELP_TEXT ;
  static const String AUDIO_HELP_TEXT ;
  static const String TEXT_HELP_TEXT ;
  static const String IMAGE_HELP_TEXT ;
  static const String FILE_HELP_TEXT ;
  static const String RTMP_HELP_TEXT ;
  static const String LCTV_HELP_TEXT ;
  static const String CHAT_HELP_TEXT ;

  // user error messages
  static const String GST_INSUFFICIENT_ERROR_MSG ;
  static const String IRC_INSUFFICIENT_ERROR_MSG ;
  static const String GST_INIT_ERROR_MSG ;
  static const String GST_PIPELINE_INST_ERROR_MSG ;
  static const String GST_BUS_INST_ERROR_MSG ;
  static const String GST_ADD_ERROR_MSG ;
  static const String GST_PIPELINE_INIT_ERROR_MSG ;
  static const String GST_CONFIG_ERROR_MSG ;
  static const String GST_XWIN_ERROR_MSG ;
  static const String SCREENCAP_INIT_ERROR_MSG ;
  static const String CAMERA_INIT_ERROR_MSG ;
  static const String TEXT_INIT_ERROR_MSG ;
  static const String IMAGE_INIT_ERROR_MSG ;
  static const String VMIXER_INIT_ERROR_MSG ;
  static const String VMIXER_PAD_INIT_ERROR_MSG ;
  static const String PREVIEW_INIT_ERROR_MSG ;
  static const String AUDIO_INIT_ERROR_MSG ;
  static const String MUXER_INIT_ERROR_MSG ;
  static const String OUTPUT_INIT_ERROR_MSG ;
  static const String SCREENCAP_LINK_ERROR_MSG ;
  static const String CAMERA_LINK_ERROR_MSG ;
  static const String TEXT_LINK_ERROR_MSG ;
  static const String IMAGE_LINK_ERROR_MSG ;
  static const String VMIXER_LINK_ERROR_MSG ;
  static const String VMIXER_PAD_LINK_ERROR_MSG ;
  static const String VMIXER_BIN_LINK_ERROR_MSG ;
  static const String PREVIEW_LINK_ERROR_MSG ;
  static const String AUDIO_LINK_ERROR_MSG ;
  static const String MUXER_LINK_ERROR_MSG ;
  static const String MUXER_BIN_LINK_ERROR_MSG ;
  static const String OUTPUT_LINK_ERROR_MSG ;
  static const String GST_STATE_ERROR_MSG ;
  static const String STORAGE_WRITE_ERROR_MSG ;
  static const String PRESET_NAME_ERROR_MSG ;
  static const String PRESET_RENAME_ERROR_MSG ;
  static const String CONFIG_INVALID_ERROR_MSG ;
  static const String ALSA_INIT_ERROR_MSG ;
  static const String PULSE_INIT_ERROR_MSG ;
  static const String JACK_INIT_ERROR_MSG ;
  static const String FILE_SINK_ERROR_MSG ;
} ;

#endif // _GUICONSTANTS_H_
