/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#include "IrcClient.h"
#ifndef DISABLE_CHAT

#include <libirc_rfcnumeric.h>

#include "AvCaster.h"
#include "IrcClient.h"
#include "../Trace/TraceIrcClient.h"


/* IrcClient class variables */

ValueTree       IrcClient::NetworkStore ;    // IrcClient()
irc_callbacks_t IrcClient::ServerCallbacks ; // IrcClient()
StringArray     IrcClient::Nicks ;           // HandleNicks()


/* IrcClient public instance methods */

void IrcClient::configure(bool should_create_session)
{
  // disconnect and destroy existing network connection
  destroySession() ;

  // validate and create network session (and login asynchronously)
  if (should_create_session) createSession() ;
}


/* IrcClient private class methods */

IrcClient::IrcClient(ValueTree network_store) : Thread(APP::IRC_THREAD_NAME)
{
  // validate and initialize
  if (ServerCallbacks.event_connect != OnConnect    ||
      ServerCallbacks.event_channel != OnChannelMsg ||
      ServerCallbacks.event_join    != OnJoin       ||
      ServerCallbacks.event_part    != OnPart       ||
      ServerCallbacks.event_nick    != OnNickChange ||
      ServerCallbacks.event_numeric != OnNumeric     )
  {
    // assign server callbacks (NOTE: there are many more)
    memset(&ServerCallbacks , 0 , sizeof(ServerCallbacks)) ;
    ServerCallbacks.event_connect = OnConnect ;
    ServerCallbacks.event_channel = OnChannelMsg ;
    ServerCallbacks.event_join    = OnJoin ;
    ServerCallbacks.event_part    = OnPart ;
    ServerCallbacks.event_nick    = OnNickChange ;
    ServerCallbacks.event_numeric = OnNumeric ;
  }

  NetworkStore  = network_store ;

  this->session = nullptr ; configure(true) ;
}

IrcClient::~IrcClient() { destroySession() ; NetworkStore = ValueTree::invalid ; }

void IrcClient::OnConnect(irc_session_t* session , const char*  event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  String host       = origin ;
  String message    = params[1] ;
  bool   is_bitlbee = message.startsWith(IRC::BITLBEE_WELCOME_MSG) ;
  String channel    = STRING(NetworkStore[CONFIG::CHANNEL_ID]) ;

DEBUG_TRACE_CONNECTED

  // set actual connected host for this network
  AvCaster::SetValue(CONFIG::HOST_ID , host) ;

  // display connected message
  AddClientChat(IRC::LOGGED_IN_MSG + host) ; AddServerChat(message) ;

  if (is_bitlbee)
  {
    // identify with bitlbee
    String identify_cmd = IRC::BITLBEE_IDENTIFY_CMD + "this->pass" ;

    irc_cmd_msg(session , IRC::BITLBEE_ROOT_CHANNEL , CHARSTAR(identify_cmd)) ;
    //irc_cmd_join(session , IRC::BITLBEE_XMPP_CHANNEL , NULL) ; // FIXME: when to join?
  }
  else irc_cmd_join(session , CHARSTAR(channel) , NULL) ;

  // reset retries counter
  SetRetries(IRC::MAX_N_RETRIES) ;
}

/* TODO: handle nickserv
static void event_notice (irc_session_t * session, const char * event,
                                                 const char * origin, const char ** params, unsigned int count)
{
        char buf[256];

        if ( !origin )
                return;

        if ( strcasecmp (origin, "nickserv") )
                return;

        if ( strstr (params[1], "This nick is not registered") == params[1] )
        {
                sprintf (buf, "REGISTER %s NOMAIL", gCfg.irc_nickserv_password);
                irc_cmd_msg(session, "nickserv", buf);
        }
        else if ( strstr (params[1], "This nickname is registered and protected") == params[1] )
        {
                sprintf (buf, "IDENTIFY %s", gCfg.irc_nickserv_password);
                irc_cmd_msg(session, "nickserv", buf);
        }
        else if ( strstr (params[1], "Password accepted - you are now recognized") == params[1] )
                printf ("Nickserv authentication succeed.");
}
*/

void IrcClient::OnChannelMsg(irc_session_t* session , const char* event  , const char* origin ,
                             const char**   params  , unsigned int count                      )
{
DEBUG_TRACE_CHAT_MSG_VB

  if (!origin || count != 2) return ;

  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;

  String      user_id           = String(origin ) ;
  String      nick              = String(nickbuf) ;
  String      channel           = CharPointer_UTF8(params[0]) ;
  String      filtered_message  = ProcessTextMeta (params[1]) ;
  StringArray processed_message = ProcessTimestamp(filtered_message) ;
  String      timestamp         = processed_message[0].trim() ;
  String      message           = processed_message[1].trim() ;
  bool        is_root_user      = IRC::BITLBEE_ROOT_USERS.contains(user_id) ;
  bool        is_root_channel   = channel == String(IRC::BITLBEE_ROOT_CHANNEL     ) ;
  bool        is_xmpp_channel   = channel == String(IRC::BITLBEE_XMPP_CHANNEL     ) ;
  bool        is_login_blocked  = message.endsWith (IRC::BITLBEE_LOGIN_BLOCKED_MSG) ;
  bool        has_kicked_self   = message.endsWith (IRC::BITLBEE_KICKED_SELF_MSG  ) ;
  bool        is_logged_in      = message.endsWith (IRC::BITLBEE_CONNECTED_MSG    ) ||
                                  has_kicked_self                                    ;

DEBUG_TRACE_CHAT_MSG

  // handle login confirmation from the bee
  if (is_root_user && is_root_channel)
    if      (is_login_blocked) AddClientChat(IRC::BITLBEE_SESSION_BLOCKED_MSG) ;
    else if (is_logged_in    ) irc_cmd_join(session , IRC::BITLBEE_XMPP_CHANNEL , NULL) ;
  if (is_root_user || is_root_channel) return ;

  // handle peer messages
  AddUserChat(timestamp , nick , message) ;
}

void IrcClient::OnJoin(irc_session_t* session , const char* event  , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char   nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick                  = nickbuf ;
  String channel               = params[0] ;
  String network               = STRING(NetworkStore[CONFIG::NETWORK_ID  ]) ;
  String this_nick             = STRING(NetworkStore[CONFIG::NICK_ID     ]) ;
  String peer_greeting         = STRING(NetworkStore[CONFIG::GREETING_ID ]) ;
  bool   should_show_joinparts = bool  (NetworkStore[CONFIG::JOINPARTS_ID]) ;
  bool   is_local_nick         = nick == this_nick ;
  String greeting              = (is_local_nick) ? IRC::LOGIN_GREETING : peer_greeting ;

  irc_cmd_user_mode(session , "+i") ;

DEBUG_TRACE_ONJOIN

//   if (channel_name == IRC::BITLBEE_ROOT_CHANNEL) return ; // FIXME: probably redundant now

  if (should_show_joinparts && !is_local_nick)
    AddClientChat(nick + " just joined " + network + " channel " + channel) ;

#ifndef SUPRESS_GREETING_MESSAGES
  irc_cmd_msg(session , CHARSTAR(channel) , CHARSTAR(greeting)) ;
#endif // SUPRESS_GREETING_MESSAGES

//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnPart(irc_session_t* session , const char* event  , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick                  = nickbuf ;
  String channel               = params[0] ;
  String network               = STRING(NetworkStore[CONFIG::NETWORK_ID  ]) ;
  String this_nick             = STRING(NetworkStore[CONFIG::NICK_ID     ]) ;
  bool   should_show_joinparts = bool  (NetworkStore[CONFIG::JOINPARTS_ID]) ;
  bool   is_local_nick         = nick == this_nick ;

DEBUG_TRACE_ONPART

  if (should_show_joinparts && !is_local_nick)
    AddClientChat(nick + " just parted " + network + " channel " + channel) ;

//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnNickChange(irc_session_t* session , const char* event  , const char* origin ,
                             const char**   params  , unsigned int count                      )
{
  String from_nick = origin ;
  String to_nick   = params[0] ;
  String network   = STRING(NetworkStore[CONFIG::NETWORK_ID]) ;
  String channel   = STRING(NetworkStore[CONFIG::CHANNEL_ID]) ;

DEBUG_TRACE_NICK_CHANGE

// DUMP_SERVER_PARAMS // TODO: nick changes nyi
//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnNumeric(irc_session_t* session , unsigned int event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  String nicks = params[3] ;

DEBUG_TRACE_SERVER_EVENT

  if      (event == LIBIRC_RFC_RPL_NAMREPLY  ) HandleNicks(nicks) ;
  else if (event == LIBIRC_RFC_RPL_ENDOFNAMES) UpdateNicks() ;
}

bool IrcClient::IsSufficientVersion()
{
  unsigned int major_version , minor_version ;

  irc_get_version(&major_version , &minor_version) ;

  return major_version >= IRC::MIN_MAJOR_VERSION &&
         minor_version >= IRC::MIN_MINOR_VERSION  ;
}

void IrcClient::SetRetries(int n_retries)
{
  NetworkStore.setProperty(CONFIG::RETRIES_ID , n_retries , nullptr) ;
}

void IrcClient::HandleNicks(String nicks)
{
  String network = STRING(NetworkStore[CONFIG::NETWORK_ID]) ;
  String channel = STRING(NetworkStore[CONFIG::CHANNEL_ID]) ;

  if (IRC::BITLBEE_HOSTS.contains(network) && channel == IRC::BITLBEE_ROOT_CHANNEL) return ;

  Nicks.addTokens         (nicks , false) ;
  Nicks.removeEmptyStrings() ;
  Nicks.removeString      (IRC::BITLBEE_ROOT_NICK) ;

DEBUG_TRACE_NICKS
}

void IrcClient::UpdateNicks()
{
#ifdef MOCK_CHAT_NICKS
  Nicks.clear() ; int n_nicks = 100 ;
  while (n_nicks--) Nicks.add("MockNick" + String(n_nicks)) ;
#endif // MOCK_CHAT_NICKS

  AvCaster::UpdateChatters(Nicks) ; Nicks.clear() ;
}

String IrcClient::ProcessTextMeta(const char* message)
{
  // filter formatting markup tokens
  // TODO: for now we just strip these
  // WHITE , BLACK , DARKBLUE , DARKGREEN , RED , BROWN , PURPLE , OLIVE
  // YELLOW , GREEN , TEAL , CYAN , BLUE , MAGENTA , DARKGRAY , LIGHTGRAY
  // e.g. "The tree[U]s[/U] are [COLOR=GREEN/BLACK]green[/COLOR]"
  char*  msg_cstr      = irc_color_convert_from_mirc(message) ;
  String converted_msg = CharPointer_UTF8(msg_cstr) ; delete msg_cstr ;
  String filtered_msg  = converted_msg.replace(IRC::BOLD_BEGIN   , "").replace(IRC::BOLD_END   , "")
                                      .replace(IRC::ITALIC_BEGIN , "").replace(IRC::ITALIC_END , "")
                                      .replace(IRC::ULINE_BEGIN  , "").replace(IRC::ULINE_END  , "")
                                                                      .replace(IRC::COLOR_END  , "") ;
  while (filtered_msg.contains(IRC::COLOR_BEGIN))
    filtered_msg.replace(filtered_msg.fromFirstOccurrenceOf(IRC::COLOR_BEGIN , true , false)
                                     .upToFirstOccurrenceOf("]"              , true , false) , "") ;

  return filtered_msg ;
}

StringArray IrcClient::ProcessTimestamp(String message)
{
  String timestamp     = message  .fromFirstOccurrenceOf("[" , true , false)
                                  .upToFirstOccurrenceOf("]" , true , false) ;
  String processed_msg = message  .replace(timestamp , "") ;
  bool   is_timestamp  = timestamp.isNotEmpty()                     &&
                         timestamp.replaceCharacters("[:]" , "000")
                                  .containsOnly(APP::DIGITS) ;

  return (is_timestamp) ? StringArray::fromLines(timestamp + "\n" + processed_msg) :
                          StringArray::fromLines(            "\n" + message      ) ;
}

void IrcClient::AddServerChat(String message)
{
  AvCaster::AddChatLine(String::empty , GUI::SERVER_NICK , message) ;
}

void IrcClient::AddClientChat(String message)
{
  AvCaster::AddChatLine(String::empty , GUI::CLIENT_NICK , message) ;
}

void IrcClient::AddUserChat(String prefix , String nick , String message)
{
  AvCaster::AddChatLine(prefix , nick , message) ;
}


/* IrcClient private instance methods */

void IrcClient::createSession()
{
  if (!NetworkStore.isValid()) return ;

  // create network session (and login asynchronously)
  this->session                   = irc_create_session(&ServerCallbacks) ;
  String         network          = STRING(NetworkStore[CONFIG::NETWORK_ID ]) ;
  unsigned short port             = int   (NetworkStore[CONFIG::PORT_ID    ]) ;
  String         nick             = STRING(NetworkStore[CONFIG::NICK_ID    ]) ;
  String         pass             = STRING(NetworkStore[CONFIG::PASS_ID    ]) ;
  String         channel          = STRING(NetworkStore[CONFIG::CHANNEL_ID ]) ;
  String         greeting         = STRING(NetworkStore[CONFIG::GREETING_ID]) ;
  bool           is_valid_session = this->session != 0 ;
  bool           is_valid_network = network.isNotEmpty() ;
  bool           is_valid_port    = IRC::PORT_RANGE.contains(uint16(port)) ;
  bool           is_valid_nick    = nick   .isNotEmpty() ;
  bool           is_valid_channel = channel.isNotEmpty() ;

// NOTE: text editors are implicitly sanitized in Config::Config() -> MainContent->configureTextEditor()
// NOTE: irc_option_set(session , LIBIRC_OPTION_STRIPNICKS) ;
// NOTE: See LIBIRC_OPTION_SSL_NO_VERIFY for servers which use self-signed SSL certificates

DEBUG_TRACE_CREATE_SESSION

  // set retries counter or desroy invalid session
  if (is_valid_session && is_valid_network && is_valid_port &&
      is_valid_nick    && is_valid_channel                   ) SetRetries(IRC::MAX_N_RETRIES) ;
  else if (is_valid_session)                                   destroySession() ;
}

void IrcClient::destroySession()
{
  if (this->session == nullptr) return ;

  // display login message and clear peers list
  if (irc_is_connected(this->session))
  {
DEBUG_TRACE_LOGOUT

    AddClientChat(IRC::LOGGING_OUT_MSG + network) ;
    Nicks.clear() ; UpdateNicks() ;
  }

  // disconnect and destroy network session
#ifndef SUPRESS_GREETING_MESSAGES
  irc_cmd_quit       (this->session , CHARSTAR(IRC::LOGOUT_GREETING)) ;
#else // SUPRESS_GREETING_MESSAGES
  irc_disconnect     (this->session) ;
#endif // SUPRESS_GREETING_MESSAGES
  irc_destroy_session(this->session) ;

  this->session = nullptr ;
}

void IrcClient::run()
{
  if (this->session == nullptr) return ;

  if (irc_is_connected(this->session))
  {
    // pump IRC client
    struct timeval timeout ;
    timeout.tv_usec   = 250000 ;
    timeout.tv_sec    = 0 ;
    int    maxfd      = 0 ;
    fd_set in_set , out_set ;

    FD_ZERO(&in_set) ; FD_ZERO(&out_set) ;

    irc_add_select_descriptors(this->session , &in_set , &out_set , &maxfd) ;
    if (select(maxfd + 1 , &in_set , &out_set , 0 , &timeout) < 0        ||
        irc_process_select_descriptors(this->session , &in_set , &out_set)) return ;
  }
  else login() ;
}

bool IrcClient::login()
{
  String         network   = STRING(NetworkStore[CONFIG::NETWORK_ID]) ;
  unsigned short port      = int   (NetworkStore[CONFIG::PORT_ID   ]) ;
  String         nick      = STRING(NetworkStore[CONFIG::NICK_ID   ]) ;
  int            n_retries = int   (NetworkStore[CONFIG::RETRIES_ID]) ;

DEBUG_TRACE_LOGIN_FAILED

  // fail after nRetries connection attempts
  if (n_retries != IRC::STATE_FAILED) SetRetries(--n_retries) ;
  if (n_retries == IRC::STATE_FAILED) return true ;

  // display login message
  AddClientChat(IRC::LOGGING_IN_MSG + network) ;

  bool is_err = irc_connect(this->session , CHARSTAR(network) , port    ,
                            nullptr       , CHARSTAR(nick   ) , nullptr , nullptr) ;

DEBUG_TRACE_LOGIN

  return !is_err ;
}

void IrcClient::sendChat(String chat_message)
{
  String channel = STRING(NetworkStore[CONFIG::CHANNEL_ID]) ;

  irc_cmd_msg(this->session , CHARSTAR(channel) , CHARSTAR(chat_message)) ;
}

#endif // DISABLE_CHAT
