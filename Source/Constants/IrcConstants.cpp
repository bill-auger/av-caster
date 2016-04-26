
#include "Constants.h"


const uint8         IRC::MIN_MAJOR_VERSION = 1 ;
const uint8         IRC::MIN_MINOR_VERSION = 8 ;
const Range<uint16> IRC::PORT_RANGE        = Range<uint16>::between(1 , 49151) ;

// IDs
const String      IRC::BITLBEE_HOST             = "im.bitlbee.org" ;
const String      IRC::LOCAL_HOST               = "localhost" ;
const String      IRC::BITLBEE_REMOTE_ROOT_USER = "root!root@" + BITLBEE_HOST ;
const String      IRC::BITLBEE_LOCAL_ROOT_USER  = "root!root@" + LOCAL_HOST   ;
const StringArray IRC::BITLBEE_HOSTS            = StringArray::fromLines(BITLBEE_HOST + newLine +
                                                                         LOCAL_HOST             ) ;
const StringArray IRC::BITLBEE_ROOT_USERS       = StringArray::fromLines(BITLBEE_REMOTE_ROOT_USER + newLine +
                                                                         BITLBEE_LOCAL_ROOT_USER            ) ;
const char*       IRC::BITLBEE_ROOT_NICK        = "@root" ;
const char*       IRC::BITLBEE_ROOT_CHANNEL     = "&bitlbee" ;
const char*       IRC::BITLBEE_XMPP_CHANNEL     = "#xmpp-chat" ;
const String      IRC::BITLBEE_IDENTIFY_CMD     = "identify " ;

// connection state
const uint8 IRC::MAX_N_RETRIES   = 5 ;
const uint8 IRC::STATE_FAILED    = 0 ;
const uint8 IRC::STATE_CONNECTED = MAX_N_RETRIES ;

// incoming server messages
const char*  IRC::BITLBEE_CONNECTED_MSG     = "Logging in: Logged in" ;
const String IRC::BITLBEE_WELCOME_MSG       = "Welcome to the BitlBee gateway, " ;
const char*  IRC::BITLBEE_LOGIN_BLOCKED_MSG = "New request: You're already connected to this server. Would you like to take over this session?" ;
const char*  IRC::BITLBEE_KICKED_SELF_MSG   = "You've successfully taken over your old session" ;

// formatting markup tokens
const String IRC::BOLD_BEGIN   = "[B]" ;
const String IRC::BOLD_END     = "[/B]" ;
const String IRC::ITALIC_BEGIN = "[I]" ;
const String IRC::ITALIC_END   = "[/I]" ;
const String IRC::ULINE_BEGIN  = "[U]" ;
const String IRC::ULINE_END    = "[/U]" ;
const String IRC::COLOR_BEGIN  = "[COLOR=" ;
const String IRC::COLOR_END    = "[/COLOR]" ;

// GUI display messages
const String IRC::YOU_NICK                    = "You" ;
const char*  IRC::INVALID_PARAMS_MSG          = "Invalid network credentials." ;
const String IRC::BITLBEE_SESSION_BLOCKED_MSG = "It appeaers that you are already connected to BitlBee with another client.  This chat will not be connected to LCTV." ;
const String IRC::LOGGING_IN_MSG              = "Logging into chat server: " ;
const String IRC::LOGGED_IN_MSG               = "Logged into chat server: " ;
const String IRC::LOGGING_OUT_MSG             = "Logging out of chat server: " ;
const String IRC::LOGIN_GREETING              = APP::APP_NAME + " starting up" ;
const String IRC::LOGOUT_GREETING             = APP::APP_NAME + " shutting down" ;

// URIS
const String IRC::LCTV_URL = "https://www.livecoding.tv/" ;
