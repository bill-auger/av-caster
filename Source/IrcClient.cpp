/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include <libirc_rfcnumeric.h>

#include "AvCaster.h"
#include "IrcClient.h"
#include "Trace/TraceIrcClient.h"


String bitlbeehost  = "localhost" ;      // TODO: GUI support
String debianhost   = "irc.debian.org" ; // TODO: GUI support
String my_nick      = "bill-auger" ;     // TODO: GUI support
String xmpp_channel = "#mychat" ;        // TODO: GUI support
String greeting     = "" ;               // TODO: GUI support


/* IrcClient class methods */

#ifdef RUN_NETWORK_AS_THREAD
IrcClient::IrcClient(ValueTree servers_store) : Thread(APP::IRC_THREAD_NAME) ,
                                                serversStore(servers_store)
#else // RUN_NETWORK_AS_THREAD
IrcClient::IrcClient(ValueTree servers_store) : serversStore(servers_store)
#endif // RUN_NETWORK_AS_THREAD
{
  // establish shared server callbacks
  memset(&this->callbacks , 0 , sizeof(this->callbacks)) ;
  this->callbacks.event_connect = OnConnect ;
  this->callbacks.event_channel = OnChannelMsg ;
  this->callbacks.event_join    = OnJoin ;
  this->callbacks.event_part    = OnPart ;
  this->callbacks.event_numeric = OnNumeric ;

  // create per server session instances and login
  int n_servers = this->serversStore.getNumChildren() ;
  for (int server_n = 0 ; server_n < n_servers ; ++server_n)
  {
    ValueTree     server_store = this->serversStore.getChild(server_n) ;
    IrcServerInfo server_info = createSession(server_store) ;

    if (!IsValidServerInfo(server_info)) continue ;

    this->servers.add(server_info) ; login(server_info) ;
  }
}

IrcClient::~IrcClient()
{
#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS
    irc_cmd_quit       (server->session , IRC::LOGOOUT_MSG) ;
    irc_disconnect     (server->session) ;
    irc_destroy_session(server->session) ;
#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
    ++server ;
  }
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS
}

IrcServerInfo IrcClient::createSession(ValueTree server_store)
{
  String         host        = STRING(server_store[CONFIG::HOST_ID]) ;
  unsigned short port        = int   (server_store[CONFIG::PORT_ID]) ;
  IrcServerInfo  server_info = { NULL , host , port , "" , my_nick , "" , "" } ;
  server_info.session        = irc_create_session(&callbacks) ;

DEBUG_TRACE_CREATE_SESSION
//irc_option_set(a_server.session , LIBIRC_OPTION_STRIPNICKS) ;
//See LIBIRC_OPTION_SSL_NO_VERIFY for servers which use self-signed SSL certificates

  return server_info ;
}

bool IrcClient::IsValidServerInfo(IrcServerInfo a_server_info)
{
  return a_server_info.session != 0      &&
         a_server_info.host.isNotEmpty() &&
         a_server_info.port > 0          &&
         a_server_info.nick.isNotEmpty()  ;
}

bool IrcClient::IsSufficientVersion()
{
  unsigned int major_version , minor_version ;

  irc_get_version(&major_version , &minor_version) ;

  return major_version >= IRC::MIN_MAJOR_VERSION &&
         minor_version >= IRC::MIN_MINOR_VERSION  ;
}

void IrcClient::OnConnect(irc_session_t* session , const char*  event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
  String host       = origin ;
  String message    = params[1] ;
  bool   is_bitlbee = host    == bitlbeehost                       &&
                      message == IRC::BITLBEE_WELCOME_MSG + my_nick ;

String OFTC_TLD = "oftc.net" ;
if (host.endsWith(OFTC_TLD))
{
DBG("AvCaster::RenameServer()") ;
  AvCaster::RenameServer(debianhost , host) ;
}
DEBUG_TRACE_IRC_CONNECTED

  // display connected message
  String logged_in_msg = CHARSTAR(String(IRC::LOGGED_IN_MSG + host)) ;
  AvCaster::AddChatLine(GUI::CLIENT_NICK , logged_in_msg) ;
  AvCaster::AddChatLine(GUI::SERVER_NICK , message      ) ;

  if (is_bitlbee)
  {
    // identify with bitlbee
    String my_pass      = "123" ;
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

void IrcClient::OnChannelMsg(irc_session_t* session , const char*  event , const char* origin ,
                             const char**   params  , unsigned int count                      )
{
DEBUG_TRACE_IRC_CHAT_MSG_VB

  if (!origin || count != 2) return ;

  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;

  String user_id          = String(origin) ;
  String nick             = nickbuf ;
  String channel          = CharPointer_UTF8(params[0]) ;
  String message          = CharPointer_UTF8(params[1]) ;
  bool   is_root_user     = user_id.startsWith(IRC::ROOT_USER + bitlbeehost) ;
  bool   is_root_channel  = channel == String (IRC::ROOT_CHANNEL           ) ;
  bool   is_xmpp_channel  = channel == String (xmpp_channel                ) ;
  bool   is_login_blocked = message.endsWith  (IRC::LOGIN_BLOCKED_MSG      ) ;
  bool   is_logged_in     = message.endsWith  (IRC::CONNECTED_MSG          ) ||
                            message.endsWith  (IRC::KICKED_SELF_MSG        )  ;

DEBUG_TRACE_IRC_CHAT_MSG

  // handle message from the bee
  if (is_root_user && is_root_channel)
    if      (is_login_blocked) AvCaster::AddChatLine(GUI::CLIENT_NICK , IRC::SESSION_BLOCKED_MSG) ;
    else if (is_logged_in    ) irc_cmd_join(session , CHARSTAR(xmpp_channel) , NULL) ;
  if (is_root_user || is_root_channel) return ;

  // handle peer messages
  AvCaster::AddChatLine(nick , message) ;
}

void IrcClient::OnJoin(irc_session_t* session , const char*  event , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick         = nickbuf ;
  String channel_name = params[0] ;

  irc_cmd_user_mode(session , "+i") ;
// bool is_xmpp_channel = strstr(params[0] , xmpp_channel) != 0 ;
// if (is_xmpp_channel) printf("is xmpp_channel\n") ;

// String stream_msg = IRC::STREAM_MSG + IRC::LCTV_URL + my_nick ;
// irc_cmd_msg(session , params[0] , CHARSTAR(stream_msg)) ;

DEBUG_TRACE_IRC_ONJOIN

  if (channel_name == IRC::ROOT_CHANNEL) return ;

#ifndef HIDE_JOIN_PART_MESSAGES
  String join_msg = nick + " just joined channel " + channel_name ;
  AvCaster::AddChatLine(GUI::CLIENT_NICK , join_msg) ;
#endif // HIDE_JOIN_PART_MESSAGES

  if      (nick == my_nick)       irc_cmd_msg(session , params[0] , IRC::LOGIN_MSG    ) ;
  else if (greeting.isNotEmpty()) irc_cmd_msg(session , params[0] , CHARSTAR(greeting)) ;

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnPart(irc_session_t* session , const char*  event , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  char nickbuf[128] ; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
  String nick         = nickbuf ;
  String channel_name = params[0] ;

DEBUG_TRACE_IRC_ONPART

#ifndef HIDE_JOIN_PART_MESSAGES
  String part_msg = nick + " just parted channel " + channel_name ;
  AvCaster::AddChatLine(GUI::CLIENT_NICK , part_msg) ;
#endif // HIDE_JOIN_PART_MESSAGES

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnNumeric(irc_session_t* session , unsigned int event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
DEBUG_TRACE_IRC_SERVER_MSG

  if (event == LIBIRC_RFC_RPL_NAMREPLY)
  {
    String      host    = origin ;
    String      channel = params[2] ;
    StringArray nicks   = StringArray::fromTokens(params[3] , false) ;

    HandleNicks(host , channel , nicks) ;
  }
}

void IrcClient::HandleNicks(String host , String channel , StringArray nicks)
{
  if (host == bitlbeehost && channel == IRC::ROOT_CHANNEL) return ;

  nicks.removeEmptyStrings() ;

DEBUG_TRACE_IRC_NICKS

  AvCaster::UpdateChatNicks(host , channel , nicks) ;
}


/* IrcClient instance methods */

bool IrcClient::login(IrcServerInfo a_server_info)
{
  //  NOTE: prefix 'server' with # for SSL
  irc_session_t* session  =          a_server_info.session ;
  const char*    host     = CHARSTAR(a_server_info.host    ) ;
  unsigned short port     =          a_server_info.port ;
  const char*    pass     = CHARSTAR(a_server_info.pass    ) ;
  const char*    nick     = CHARSTAR(a_server_info.nick    ) ;
  const char*    username = CHARSTAR(a_server_info.username) ;
  const char*    realname = CHARSTAR(a_server_info.realname) ;

DEBUG_TRACE_IRC_LOGIN_IN

  // display login message
  String logging_in_msg = CHARSTAR(String(IRC::LOGGING_IN_MSG + a_server_info.host)) ;
  AvCaster::AddChatLine(GUI::CLIENT_NICK , logging_in_msg) ;

  bool is_err = irc_connect(session , host , port , pass , nick , username , realname) ;

DEBUG_TRACE_IRC_LOGIN_OUT

  return !is_err ;
}

void IrcClient::run()
{
#ifdef RUN_NETWORK_AS_PROC
DEBUG_TRACE_IRC_THREAD_RUN_IN
  bool is_err = irc_run(this->session) ;

if (is_err) DBG("Could not connect or I/O error: " + String(irc_strerror(irc_errno(this->session)))) ;
#else // RUN_NETWORK_AS_PROC
#  ifdef RUN_NETWORK_AS_THREAD
DEBUG_TRACE_IRC_THREAD_RUN_IN

  while (!threadShouldExit())
  {
#  endif // RUN_NETWORK_AS_THREAD
#endif // RUN_NETWORK_AS_PROC

#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS
// Make sure that all the IRC sessions are connected
    if (IsValidServerInfo(*server) && !irc_is_connected(server->session))
    { login(*server) ; ++server ; continue ; }

// Create the structures for select()
struct timeval tv;
fd_set in_set, out_set;
int maxfd = 0;

// Wait 0.25 sec for the events - you can wait longer if you want to, but the library has internal timeouts
// so it needs to be called periodically even if there are no network events
tv.tv_usec = 250000;
tv.tv_sec = 0;

// Initialize the sets
FD_ZERO (&in_set);
FD_ZERO (&out_set);

// Add your own descriptors you need to wait for, if any
//...

// Add the IRC session descriptors - call irc_add_select_descriptors() for each active session
irc_add_select_descriptors(server->session , &in_set , &out_set , &maxfd) ;

// Call select()
if (select(maxfd + 1 , &in_set , &out_set , 0 , &tv) < 0) return ;// Error

// You may also check if any descriptor is active, but again the library needs to handle internal timeouts,
// so you need to call irc_process_select_descriptors() for each session at least once in a few seconds
// ...

// Call irc_process_select_descriptors() for each session with the descriptor set
if (irc_process_select_descriptors(server->session , &in_set , &out_set)) return ;// The connection failed, or the server disconnected. Handle it.

#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
    ++server ;
  }
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS

#ifdef RUN_NETWORK_AS_PROC
DEBUG_TRACE_IRC_THREAD_RUN_OUT
#else // RUN_NETWORK_AS_PROC
#  ifdef RUN_NETWORK_AS_THREAD
// Do it again
  }

DEBUG_TRACE_IRC_THREAD_RUN_OUT
#  endif // RUN_NETWORK_AS_THREAD
#endif // RUN_NETWORK_AS_PROC
}

void IrcClient::sendChat(String chat_msg)
{
#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS
    irc_cmd_msg(server->session , CHARSTAR(xmpp_channel) , CHARSTAR(chat_msg)) ;
#ifdef IRCCLIENT_HAS_MULTIPLE_SESSIONS
    ++server ;
  }
#endif // IRCCLIENT_HAS_MULTIPLE_SESSIONS
  AvCaster::AddChatLine(my_nick , chat_msg) ;
}
