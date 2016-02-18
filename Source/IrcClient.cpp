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

#include <libircclient/libirc_rfcnumeric.h>

#include "AvCaster.h"
#include "IrcClient.h"
#include "Trace/TraceIrcClient.h"


/* IrcClient class variables */

irc_callbacks_t IrcClient::ServerCallbacks ;      // IrcClient()
bool            IrcClient::ShouldShowTimestamps ; // IrcClient() , reconfigure()
bool            IrcClient::ShouldShowJoinParts ;  // IrcClient() , reconfigure()


/* IrcClient public instance methods */

void IrcClient::configure(bool should_create_sessions , bool should_show_timestamps ,
                                                        bool should_show_joinparts  )
{
  // validate and initialize
  if (ServerCallbacks.event_connect != OnConnect    ||
      ServerCallbacks.event_channel != OnChannelMsg ||
      ServerCallbacks.event_join    != OnJoin       ||
      ServerCallbacks.event_part    != OnPart       ||
      ServerCallbacks.event_nick    != OnNickChange ||
      ServerCallbacks.event_numeric != OnNumeric     )
  {
    // assign shared server callbacks (NOTE: there are many more)
    memset(&ServerCallbacks , 0 , sizeof(ServerCallbacks)) ;
    ServerCallbacks.event_connect = OnConnect ;
    ServerCallbacks.event_channel = OnChannelMsg ;
    ServerCallbacks.event_join    = OnJoin ;
    ServerCallbacks.event_part    = OnPart ;
    ServerCallbacks.event_nick    = OnNickChange ;
    ServerCallbacks.event_numeric = OnNumeric ;
  }

  // destroy any existing network connections
  destroySessions() ;

  // set common properties
  ShouldShowTimestamps = should_show_timestamps ;
  ShouldShowJoinParts  = should_show_joinparts ;

  // create per network session instances (and login asynchronously)
  if (should_create_sessions) createSessions() ;
}


/* IrcClient private class methods */

IrcClient::IrcClient(ValueTree networks_store , bool should_show_timestamps , bool should_show_joinparts) :
                     Thread(APP::IRC_THREAD_NAME) , networksStore(networks_store)
{
  configure(true , should_show_timestamps , should_show_joinparts) ;
}

IrcClient::~IrcClient() { destroySessions() ; }

void IrcClient::OnConnect(irc_session_t* session , const char*  event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  String          host         = origin ;
  String          message      = params[1] ;
  IrcNetworkInfo* network_info = IrcClient::GetNetworkInfo(session) ;
  bool            is_bitlbee   = message.startsWith(IRC::BITLBEE_WELCOME_MSG) ;
  bool            is_oftc      = network_info->network.endsWith(IRC::OFTC_TLD) ;

DEBUG_TRACE_CONNECTED

  if (is_oftc) AvCaster::UpdateIrcHost(IRC::OFTC_ALIAS_URIS , host) ;

  // display connected message
  AddClientChat(IRC::LOGGED_IN_MSG + host) ; AddServerChat(message) ;

  if (is_bitlbee)
  {
    // identify with bitlbee
    String identify_cmd = IRC::BITLBEE_IDENTIFY_CMD + "this->pass" ;

    irc_cmd_msg(session , IRC::BITLBEE_ROOT_CHANNEL , CHARSTAR(identify_cmd)) ;
    //irc_cmd_join(session , IRC::BITLBEE_XMPP_CHANNEL , NULL) ; // FIXME: when to join?
  }
  else irc_cmd_join(session , CHARSTAR(network_info->channel) , NULL) ;

  // reset retries counter
  SetRetries(network_info->network_id , IRC::MAX_N_RETRIES) ;
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
  bool        is_root_user      = user_id.startsWith(IRC::BITLBEE_REMOTE_ROOT_USER) ||
                                  user_id.startsWith(IRC::BITLBEE_LOCAL_ROOT_USER )  ;
  bool        is_root_channel   = channel == String (IRC::BITLBEE_ROOT_CHANNEL) ;
  bool        is_xmpp_channel   = channel == String (IRC::BITLBEE_XMPP_CHANNEL) ;
  bool        is_login_blocked  = message.endsWith  (IRC::BITLBEE_LOGIN_BLOCKED_MSG) ;
  bool        has_kicked_self   = message.endsWith  (IRC::BITLBEE_KICKED_SELF_MSG  ) ;
  bool        is_logged_in      = message.endsWith  (IRC::BITLBEE_CONNECTED_MSG    ) ||
                                  has_kicked_self                                     ;

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
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String          nick          = nickbuf ;
  String          channel       = params[0] ;
  IrcNetworkInfo* network_info  = IrcClient::GetNetworkInfo(session) ;
  bool            is_local_nick = nick == network_info->nick ;
  String          greeting      = (is_local_nick) ? IRC::LOGIN_MSG : network_info->greeting ;

  irc_cmd_user_mode(session , "+i") ;

DEBUG_TRACE_ONJOIN

  if (is_local_nick) return ;
//   if (channel_name == IRC::BITLBEE_ROOT_CHANNEL) return ; // FIXME: probably redundant now

  if (ShouldShowJoinParts)
    AddClientChat(nick + " just joined " + network_info->network + " channel " + channel) ;

#ifndef SUPRESS_GREETING_MESSAGES
  irc_cmd_msg(session , CHARSTAR(channel) , CHARSTAR(greeting)) ;
#endif // SUPRESS_GREETING_MESSAGES

//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnPart(irc_session_t* session , const char* event  , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String          nick         = nickbuf ;
  String          channel       = params[0] ;
  IrcNetworkInfo* network_info = IrcClient::GetNetworkInfo(session) ;

DEBUG_TRACE_ONPART

  if (nick == network_info->nick) return ;

  if (ShouldShowJoinParts)
    AddClientChat(nick + " just parted " + network_info->network + " channel " + channel) ;

//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnNickChange(irc_session_t* session , const char* event  , const char* origin ,
                             const char**   params  , unsigned int count                      )
{
  String          from_nick    = origin ;
  String          to_nick      = params[0] ;
  IrcNetworkInfo* network_info = IrcClient::GetNetworkInfo(session) ;

DEBUG_TRACE_NICK_CHANGE
// DUMP_SERVER_PARAMS // TODO: nick changes untested
//   irc_cmd_names(session , CHARSTAR(channel_name)) ; // FIXME: this maybe redundant
}

void IrcClient::OnNumeric(irc_session_t* session , unsigned int event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  IrcNetworkInfo* network_info = IrcClient::GetNetworkInfo(session) ;
  String          channel      = params[2] ;
  String          nicks        = params[3] ;

DEBUG_TRACE_SERVER_EVENT

  if      (event == LIBIRC_RFC_RPL_NAMREPLY  ) HandleNicks(network_info , nicks) ;
  else if (event == LIBIRC_RFC_RPL_ENDOFNAMES) UpdateNicks(network_info) ;
}

bool IrcClient::IsSufficientVersion()
{
  unsigned int major_version , minor_version ;

  irc_get_version(&major_version , &minor_version) ;

  return major_version >= IRC::MIN_MAJOR_VERSION &&
         minor_version >= IRC::MIN_MINOR_VERSION  ;
}

IrcClient::IrcNetworkInfo* IrcClient::GetNetworkInfo(irc_session_t* session)
{
  return static_cast<IrcNetworkInfo*>(irc_get_ctx(session)) ;
}

void IrcClient::SetRetries(Identifier network_id , int n_retries)
{
  ValueTree network_store = AvCaster::GetNetworkStore(network_id) ;

  network_store.setProperty(CONFIG::RETRIES_ID , n_retries , nullptr) ;
}

int IrcClient::GetRetries(Identifier network_id)
{
  ValueTree network_store = AvCaster::GetNetworkStore(network_id) ;

  return int(network_store[CONFIG::RETRIES_ID]) ;
}

void IrcClient::HandleNicks(IrcNetworkInfo* network_info , String nicks)
{
  String network = network_info->network ;
  String channel = network_info->channel ;

  if ((network == IRC::BITLBEE_HOST         || network == IRC::LOCAL_HOST) &&
       channel == IRC::BITLBEE_ROOT_CHANNEL                                 ) return ;

  network_info->nicks.addTokens         (nicks , false) ;
  network_info->nicks.removeEmptyStrings() ;
  network_info->nicks.removeString      (IRC::BITLBEE_ROOT_NICK) ;

DEBUG_TRACE_NICKS
}

void IrcClient::UpdateNicks(IrcNetworkInfo* network_info)
{
#ifdef MOCK_CHAT_NICKS
  network_info->nicks.clear() ; int n_nicks = 100 ;
  while (n_nicks--) network_info->nicks.add("MockNick" + String(n_nicks)) ;
#endif // MOCK_CHAT_NICKS

  AvCaster::UpdateChatNicks(network_info->network_id , network_info->nicks) ;
  network_info->nicks.clear() ;
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

void IrcClient::createSessions()
{
  // create per network sessions (and login asynchronously)
  for (int network_n = 0 ; network_n < this->networksStore.getNumChildren() ; ++network_n)
  {
    ValueTree       network_store = this->networksStore.getChild(network_n) ;
    IrcNetworkInfo* network_info  = new IrcNetworkInfo() ;
    network_info->session         = irc_create_session(&ServerCallbacks) ;
    network_info->network_id      =        network_store.getType() ;
    network_info->network         = STRING(network_store[CONFIG::NETWORK_ID ]) ;
    network_info->port            = int   (network_store[CONFIG::PORT_ID    ]) ;
    network_info->nick            = STRING(network_store[CONFIG::NICK_ID    ]) ;
    network_info->pass            = STRING(network_store[CONFIG::PASS_ID    ]) ;
    network_info->channel         = STRING(network_store[CONFIG::CHANNEL_ID ]) ;
    network_info->greeting        = STRING(network_store[CONFIG::GREETING_ID]) ;
/*  network_info->nicks           = StringArray() ; */
    bool is_valid_session         = network_info->session != 0 ;
    bool is_valid_network         = network_info->network.isNotEmpty() ;
    bool is_valid_port            = IRC::PORT_RANGE.contains(uint16(network_info->port)) ;
    bool is_valid_nick            = network_info->nick   .isNotEmpty() ;
    bool is_valid_channel         = network_info->channel.isNotEmpty() ;

// TODO: perhaps move these validations intp Config->validateParams() ;
// NOTE: irc_option_set(session , LIBIRC_OPTION_STRIPNICKS) ;
// NOTE: See LIBIRC_OPTION_SSL_NO_VERIFY for servers which use self-signed SSL certificates

DEBUG_TRACE_CREATE_SESSION

    if (is_valid_session && is_valid_network && is_valid_port &&
        is_valid_nick    && is_valid_channel                   )
    {
      // add to active sessions
      this->networks.add(network_info) ;

      // set circular reference in session to network_info object
      irc_set_ctx(network_info->session , network_info) ;

      // set retries counter
      SetRetries(network_info->network_id , IRC::MAX_N_RETRIES) ;
    }
    else { irc_destroy_session(network_info->session) ; delete network_info ; }
  }
}

void IrcClient::destroySessions()
{
  // disconnect and destroy network sessions
  for (int network_n = 0 ; network_n < this->networks.size() ; ++network_n)
  {
    IrcNetworkInfo* network_info = this->networks[network_n] ;

#ifndef SUPRESS_GREETING_MESSAGES
    irc_cmd_quit       (network_info->session , CHARSTAR(IRC::LOGOUT_MSG)) ;
#else // SUPRESS_GREETING_MESSAGES
    irc_disconnect     (network_info->session) ;
#endif // SUPRESS_GREETING_MESSAGES
    irc_destroy_session(network_info->session) ;
  }

  this->networks.clear() ;
}

void IrcClient::run()
{
  for (int network_n = 0 ; network_n < this->networks.size() ; ++network_n)
  {
    IrcNetworkInfo* network_info = this->networks[network_n] ;
    irc_session_t*  session      = network_info->session ;

    if (irc_is_connected(session))
    {
      // pump IRC client
      struct timeval timeout ;
      timeout.tv_usec   = 250000 ;
      timeout.tv_sec    = 0 ;
      int    maxfd      = 0 ;
      fd_set in_set , out_set ;

      FD_ZERO(&in_set) ; FD_ZERO(&out_set) ;

      irc_add_select_descriptors(session , &in_set , &out_set , &maxfd) ;
      if (select(maxfd + 1 , &in_set , &out_set , 0 , &timeout) < 0        ||
          irc_process_select_descriptors(session , &in_set , &out_set)) return ;
    }
    else login(network_info) ;
  }
}

bool IrcClient::login(IrcNetworkInfo* network_info)
{
  irc_session_t* session    = network_info->session ;
  Identifier     network_id = network_info->network_id ;
  String         network    = network_info->network ;
  unsigned short port       = network_info->port ;
  String         nick       = network_info->nick ;

DEBUG_TRACE_LOGIN_FAILED

  // fail after nRetries connection attempts
  int n_retries = GetRetries(network_id) ;
  if (n_retries != IRC::STATE_FAILED) SetRetries(network_id , --n_retries) ;
  if (n_retries == IRC::STATE_FAILED) return true ;

  // display login message
  AddClientChat(IRC::LOGGING_IN_MSG + network) ;

  bool is_err = irc_connect(session , CHARSTAR(network) , port    ,
                            nullptr , CHARSTAR(nick   ) , nullptr , nullptr) ;

DEBUG_TRACE_LOGIN

  return !is_err ;
}

void IrcClient::sendChat(String chat_message)
{
  for (int network_n = 0 ; network_n < this->networks.size() ; ++network_n)
  {
    IrcNetworkInfo* network_info = this->networks[network_n] ;
    irc_session_t*  session      = network_info->session ;
    String          channel      = network_info->channel ;

    irc_cmd_msg(session , CHARSTAR(channel) , CHARSTAR(chat_message)) ;
  }
}

#endif // DISABLE_CHAT
