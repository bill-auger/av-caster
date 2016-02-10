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


String bitlbeehost  = "localhost" ;      // TODO: GUI support
// String debianhost   = "irc.debian.org" ; // TODO: GUI support
String my_nick      = "bill-auger" ;     // TODO: GUI support
String xmpp_channel = "#mychat" ;        // TODO: GUI support
String greeting     = "" ;               // TODO: GUI support


/* IrcClient class methods */

IrcClient::IrcClient(ValueTree servers_store) : Thread(APP::IRC_THREAD_NAME) ,
                                                serversStore(servers_store)
{
 // create per server session instances and login
  int n_servers = this->serversStore.getNumChildren() ;
  for (int server_n = 0 ; server_n < n_servers ; ++server_n)
  {
    ValueTree     server_store = this->serversStore.getChild(server_n) ;
    IrcServerInfo server_info  = createSession(server_store) ;

    if (IsValidServerInfo(&server_info))
      this->servers.add(server_info) ; login(&server_info) ;
  }
}

IrcClient::~IrcClient()
{
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
    irc_cmd_quit       (server->session , IRC::LOGOOUT_MSG) ;
    irc_disconnect     (server->session) ;
    irc_destroy_session(server->session) ;
    ++server ;
  }
}


IrcServerInfo IrcClient::createSession(ValueTree server_store)
{
  // assign shared server callbacks
  irc_callbacks_t callbacks ;
  memset(&callbacks , 0 , sizeof(callbacks)) ;
  callbacks.event_connect = OnConnect ;
  callbacks.event_channel = OnChannelMsg ;
  callbacks.event_join    = OnJoin ;
  callbacks.event_part    = OnPart ;
  callbacks.event_nick    = OnNickChange ;
  callbacks.event_numeric = OnNumeric ;

  // create session
  String         host        = STRING(server_store[CONFIG::HOST_ID]) ;
  unsigned short port        = int   (server_store[CONFIG::PORT_ID]) ;
  IrcServerInfo  server_info = { NULL , host , port , my_nick } ;
  server_info.session        = irc_create_session(&callbacks) ;

DEBUG_TRACE_CREATE_SESSION
//irc_option_set(a_server.session , LIBIRC_OPTION_STRIPNICKS) ;
//See LIBIRC_OPTION_SSL_NO_VERIFY for servers which use self-signed SSL certificates

  return server_info ;
}

void IrcClient::OnConnect(irc_session_t* session , const char*  event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  String host       = origin ;
  String message    = params[1] ;
  bool   is_bitlbee = host    == bitlbeehost                       &&
                      message == IRC::BITLBEE_WELCOME_MSG + my_nick ;

DEBUG_TRACE_CONNECTED

// String OFTC_TLD = "oftc.net" ;
//   if (host.endsWith(IRC::OFTC_TLD)) AvCaster::RenameServer(debianhost , host) ;
  if (host.endsWith(IRC::OFTC_TLD)) AvCaster::UpdateIrcHost(IRC::OFTC_ALIAS_URIS , host) ;

  // display connected message
  AddClientChat(IRC::LOGGED_IN_MSG + host) ; AddServerChat(message) ;

  if (is_bitlbee)
  {
    // identify with bitlbee
    String my_pass      = "123" ; // TODO: GUI and model support
    String identify_cmd = IRC::IDENTIFY_CMD + my_pass ;

    irc_cmd_msg(session , IRC::ROOT_CHANNEL , CHARSTAR(identify_cmd)) ;
  }
  else irc_cmd_join(session , CHARSTAR(xmpp_channel) , NULL) ;
}

/* handle nickserv
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

  String      user_id           = String(origin) ;
  String      nick              = nickbuf ;
  String      channel           = CharPointer_UTF8(params[0]) ;
  String      filtered_message  = ProcessTextMeta(params[1]) ;
  StringArray processed_message = ProcessTimestamp(filtered_message) ;
  String      timestamp         = processed_message[0] ;
  String      message           = processed_message[1] ;
  bool        is_root_user      = user_id.startsWith(IRC::ROOT_USER + bitlbeehost) ;
  bool        is_root_channel   = channel == String (IRC::ROOT_CHANNEL           ) ;
  bool        is_xmpp_channel   = channel == String (xmpp_channel                ) ;
  bool        is_login_blocked  = message.endsWith  (IRC::LOGIN_BLOCKED_MSG      ) ;
  bool        is_logged_in      = message.endsWith  (IRC::CONNECTED_MSG          ) ||
                                  message.endsWith  (IRC::KICKED_SELF_MSG        )  ;

DEBUG_TRACE_CHAT_MSG

  // handle login message from the bee
  if (is_root_user && is_root_channel)
    if      (is_login_blocked) AddClientChat(IRC::SESSION_BLOCKED_MSG) ;
    else if (is_logged_in    ) irc_cmd_join(session , CHARSTAR(xmpp_channel) , NULL) ;
  if (is_root_user || is_root_channel) return ;

  // handle peer messages
  AddUserChat(timestamp , nick , message) ;
}

void IrcClient::OnJoin(irc_session_t* session , const char* event  , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick         = nickbuf ;
  String channel_name = params[0] ;

  irc_cmd_user_mode(session , "+i") ;

DEBUG_TRACE_ONJOIN

  if (channel_name == IRC::ROOT_CHANNEL) return ;

#ifndef HIDE_JOIN_PART_MESSAGES // TODO: GUI support
  AddClientChat(nick + " just joined channel " + channel_name) ;
#endif // HIDE_JOIN_PART_MESSAGES

  if      (nick == my_nick)       irc_cmd_msg(session , params[0] , IRC::LOGIN_MSG    ) ;
  else if (greeting.isNotEmpty()) irc_cmd_msg(session , params[0] , CHARSTAR(greeting)) ;

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnPart(irc_session_t* session , const char* event  , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick         = nickbuf ;
  String channel_name = params[0] ;

DEBUG_TRACE_ONPART

#ifndef HIDE_JOIN_PART_MESSAGES
  AddClientChat(nick + " just parted channel " + channel_name) ;
#endif // HIDE_JOIN_PART_MESSAGES

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnNickChange(irc_session_t* session , const char* event , const char* origin ,
                             const char**   params  , unsigned int count                     )
{
  String from_nick    = origin ;
  String to_nick      = params[0] ;
//   String channel_name = session. ; // TODO: may need to add session_ctx

DEBUG_TRACE_NICK_CHANGE
// DUMP_SERVER_PARAMS
//   irc_cmd_names(session , CHARSTAR(channel_name)) ;
}
void IrcClient::OnNumeric(irc_session_t* session , unsigned int event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
DEBUG_TRACE_SERVER_MSG

  if (event == LIBIRC_RFC_RPL_NAMREPLY)
  {
    String      host    = origin ;
    String      channel = params[2] ;
    StringArray nicks   = StringArray::fromTokens(params[3] , false) ;

    HandleNicks(host , channel , nicks) ;
  }
}

bool IrcClient::IsValidServerInfo(IrcServerInfo* a_server_info)
{
DEBUG_TRACE_SERVER_INFO

  return a_server_info->session != 0      &&
         a_server_info->host.isNotEmpty() &&
         a_server_info->port > 0          &&
         a_server_info->nick.isNotEmpty()  ;
}

bool IrcClient::IsSufficientVersion()
{
  unsigned int major_version , minor_version ;

  irc_get_version(&major_version , &minor_version) ;

  return major_version >= IRC::MIN_MAJOR_VERSION &&
         minor_version >= IRC::MIN_MINOR_VERSION  ;
}

void IrcClient::HandleNicks(String host , String channel , StringArray nicks)
{
  if (host == bitlbeehost && channel == IRC::ROOT_CHANNEL) return ;

  nicks.removeEmptyStrings() ; nicks.removeString(IRC::ROOT_NICK) ;

DEBUG_TRACE_NICKS

#ifdef PREFIX_CHAT_NICKS
  AvCaster::UpdateChatNicks(host , channel , nicks) ;
#else // PREFIX_CHAT_NICKS
  AvCaster::UpdateChatNicks(host , nicks) ;
#endif // PREFIX_CHAT_NICKS
}

String IrcClient::ProcessTextMeta(const char* message)
{
  // TODO: for now we just strip these - see docs for irc_color_convert_to_mirc()
  char*  msg_cstr      = irc_color_convert_from_mirc(message) ;
  String converted_msg = CharPointer_UTF8(msg_cstr) ; delete msg_cstr ;
  String filtered_msg  = converted_msg.replace("[B]" , "").replace("[/B]"     , "") // bold
                                      .replace("[I]" , "").replace("[/I]"     , "") // italic
                                      .replace("[U]" , "").replace("[/U]"     , "") // underline
                                                          .replace("[/COLOR]" , "") ;

  while (filtered_msg.contains("[COLOR="))
    filtered_msg.replace(filtered_msg.fromFirstOccurrenceOf("[COLOR=" , true , false)
                                     .upToFirstOccurrenceOf("]"       , true , false) , "") ;

  return filtered_msg ;
}

StringArray IrcClient::ProcessTimestamp(String message)
{
  String timestamp     = message.fromFirstOccurrenceOf("[" , true , false)
                                .upToFirstOccurrenceOf("]" , true , false) ;
  String processed_msg = message.replace(timestamp , "") ;
  bool   is_timestamp  = timestamp.replaceCharacters("[:]" , "000")
                                  .containsOnly(APP::DIGITS) ;

  return (is_timestamp) ? StringArray::fromLines(timestamp + " \n" + processed_msg) :
                          StringArray::fromLines("\n" + message)                    ;
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


/* IrcClient instance methods */

bool IrcClient::login(IrcServerInfo* a_server_info)
{
  //  NOTE: prefix 'server' with # for SSL
  irc_session_t* session =          a_server_info->session ;
  const char*    host    = CHARSTAR(a_server_info->host    ) ;
  unsigned short port    =          a_server_info->port ;
  const char*    nick    = CHARSTAR(a_server_info->nick    ) ;

  // display login message
  AddClientChat(IRC::LOGGING_IN_MSG + a_server_info->host) ;

  bool is_err = irc_connect(session , host , port , 0 , nick , 0 , 0) ;

DEBUG_TRACE_LOGIN

  return !is_err ;
}

void IrcClient::run()
{
#ifdef RUN_NETWORK_AS_PROC
DEBUG_TRACE_THREAD_RUN_IN

  bool is_err = irc_run(this->session) ;

DEBUG_TRACE_THREAD_RUN_OUT

  return ;
#endif // RUN_NETWORK_AS_PROC

  if (threadShouldExit()) return ;

  for (IrcServerInfo* server = this->servers.begin() ; server != this->servers.end() ; ++server)
    if (!irc_is_connected(server->session)) { login(server) ; continue ; }

  struct timeval timeout ;
  timeout.tv_usec   = 250000 ;
  timeout.tv_sec    = 0 ;
  int    maxfd = 0 ;
  fd_set in_set , out_set ;

  FD_ZERO(&in_set) ; FD_ZERO(&out_set) ;

  for (IrcServerInfo* server = this->servers.begin() ; server != this->servers.end() ; ++server)
    irc_add_select_descriptors(server->session , &in_set , &out_set , &maxfd) ;

  if (select(maxfd + 1 , &in_set , &out_set , 0 , &timeout) < 0) return ;

  for (IrcServerInfo* server = this->servers.begin() ; server != this->servers.end() ; ++server)
    if (irc_process_select_descriptors(server->session , &in_set , &out_set)) continue ;
}

void IrcClient::sendChat(String chat_msg)
{
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
    irc_cmd_msg((server++)->session , CHARSTAR(xmpp_channel) , CHARSTAR(String(chat_msg))) ;

  AddUserChat(String::empty , my_nick , chat_msg) ;
}

#endif // DISABLE_CHAT
