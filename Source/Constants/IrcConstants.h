#ifndef _IRCCONSTANTS_H_
#define _IRCCONSTANTS_H_


/** the IRC class defines configuration constants
        pertaining to the libircclient network backend */
class IRC
{
public:

  static const uint8         MIN_MAJOR_VERSION ;
  static const uint8         MIN_MINOR_VERSION ;
  static const Range<uint16> PORT_RANGE ;

  // IDs
  static const String      BITLBEE_HOST ;
  static const String      LOCAL_HOST ;
  static const String      BITLBEE_REMOTE_ROOT_USER ;
  static const String      BITLBEE_LOCAL_ROOT_USER ;
  static const StringArray BITLBEE_HOSTS ;
  static const StringArray BITLBEE_ROOT_USERS ;
  static const char*       BITLBEE_ROOT_NICK ;
  static const char*       BITLBEE_ROOT_CHANNEL ;
  static const char*       BITLBEE_XMPP_CHANNEL ;
  static const String      BITLBEE_IDENTIFY_CMD ;

  // connection state
  static const uint8 MAX_N_RETRIES ;
  static const uint8 STATE_FAILED ;
  static const uint8 STATE_CONNECTED ;

  // incoming server messages
  static const char*  BITLBEE_CONNECTED_MSG ;
  static const String BITLBEE_WELCOME_MSG ;
  static const char*  BITLBEE_LOGIN_BLOCKED_MSG ;
  static const char*  BITLBEE_KICKED_SELF_MSG ;

  // formatting markup tokens
  static const String BOLD_BEGIN ;
  static const String BOLD_END ;
  static const String ITALIC_BEGIN ;
  static const String ITALIC_END ;
  static const String ULINE_BEGIN ;
  static const String ULINE_END ;
  static const String COLOR_BEGIN ;
  static const String COLOR_END ;

  // GUI display messages
  static const String YOU_NICK ;
  static const char*  INVALID_PARAMS_MSG ;
  static const String BITLBEE_SESSION_BLOCKED_MSG ;
  static const String LOGGING_IN_MSG ;
  static const String LOGGED_IN_MSG ;
  static const String LOGGING_OUT_MSG ;
  static const String LOGIN_GREETING ;
  static const String LOGOUT_GREETING ;

  // URIS
  static const String LCTV_URL ;
} ;

#endif // _IRCCONSTANTS_H_
