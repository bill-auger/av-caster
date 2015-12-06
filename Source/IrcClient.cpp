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


/* TODO: */ String my_nick = "bill-auger" ;


/* IrcClient class methods */

IrcClient::IrcClient(const String& thread_name) : Thread(thread_name)
{
  memset(&this->callbacks , 0 , sizeof(this->callbacks)) ;

  this->callbacks.event_connect = OnConnect ;
  this->callbacks.event_channel = OnChannelMsg ;
  this->callbacks.event_join    = OnJoin ;
  this->callbacks.event_part    = OnPart ;
  this->callbacks.event_numeric = OnNumeric ;

// TODO: servers_store.each -> sessions or multiple AVCaster::IrcCLients
  IrcServerInfo server = {NULL , "localhost" , 6667 , 0 , CHARSTAR(my_nick) , 0 , 0} ;
  createSession(server) ;
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

void IrcClient::createSession(IrcServerInfo a_server)
{
  a_server.session = irc_create_session(&callbacks) ;

if (a_server.session == 0) DBG("Could not create this->session") ;
//irc_option_set(a_server.session , LIBIRC_OPTION_STRIPNICKS) ;
//See LIBIRC_OPTION_SSL_NO_VERIFY for servers which use self-signed SSL certificates

  if (a_server.session == 0) return ;

  this->servers.add(a_server) ; login(a_server) ;
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
DEBUG_TRACE_IRC_CONNECTED

  bool is_bitlbee = String(origin)    == "localhost"                       &&
                    String(params[1]) == IRC::BITLBEE_WELCOME_MSG + my_nick ;

  if (is_bitlbee)
  {
    // identify with bitlbee
    String my_pass      = "123" ;
    String identify_cmd = IRC::IDENTIFY_CMD + my_pass ;

    irc_cmd_msg(session , IRC::ROOT_CHANNEL , CHARSTAR(identify_cmd)) ;
  }
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

  String user_id                  = String(origin) ;
  String nick                     = nickbuf ;
  String channel                  = params[0] ;
  String message                  = params[1] ;
  bool   is_root_user             = user_id.startsWith(IRC::ROOT_USER            ) ;
  bool   is_root_channel          = channel == String (IRC::ROOT_CHANNEL         ) ;
  bool   is_my_channel            = channel == String (IRC::MY_CHANNEL           ) ;
  bool   is_already_logged_in_msg = message.endsWith  (IRC::ALREADY_LOGGED_IN_MSG) ;
  bool   is_logged_in_msg         = message.endsWith  (IRC::LOGGED_IN_MSG        ) ||
                                    message.endsWith  (IRC::KICKED_SELF_MSG      )  ;

DEBUG_TRACE_IRC_CHAT_MSG

  // handle message from the bee
  if (is_root_user && is_root_channel)
    if      (is_already_logged_in_msg) AvCaster::AddChatLine(GUI::SERVER_NICK , IRC::SESSION_BLOCKED_MSG) ;
    else if (is_logged_in_msg        ) irc_cmd_join(session , IRC::MY_CHANNEL   , 0) ; //0=>NULL
  if (is_root_user || is_root_channel) return ;

  // handle peer messages
  AvCaster::AddChatLine(nick , message) ;
}

void IrcClient::OnJoin(irc_session_t* session , const char*  event , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  irc_cmd_user_mode(session , "+i") ;

  String channel_name = params[0] ;
// bool is_my_channel = strstr(params[0] , IRC::MY_CHANNEL) != 0 ;
// if (is_my_channel) printf("is my_channel\n") ;

// String stream_msg = IRC::STREAM_MSG + IRC::LCTV_URL + my_nick ;
// irc_cmd_msg(session , params[0] , CHARSTAR(stream_msg)) ;

char nickbuf[128]; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
// char greeting[255] ; snprintf(greeting , 255 , "%s just joined" , nickbuf) ;
String nick = nickbuf ;
DEBUG_TRACE_IRC_ONJOIN

  if (channel_name == IRC::ROOT_CHANNEL) return ;

  String join_msg = nick + " just joined channel " + channel_name ;
  AvCaster::AddChatLine(GUI::SERVER_NICK , join_msg) ;
  if (nick == my_nick) irc_cmd_msg(session , params[0] , IRC::LOGIN_MSG) ;
//   else                 irc_cmd_msg(session , params[0] , greeting) ;

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnPart(irc_session_t* session , const char*  event , const char* origin ,
                       const char**   params  , unsigned int count                      )
{
  String channel_name = params[0] ;

char nickbuf[128]; irc_target_get_nick(origin , nickbuf , sizeof(nickbuf)) ;
// char greeting[255] ; snprintf(greeting , 255 , "%s just parted" , nickbuf) ;
String nick = nickbuf ;
DEBUG_TRACE_IRC_ONPART

  String part_msg = nick + " just parted channel " + channel_name ;
  AvCaster::AddChatLine(GUI::SERVER_NICK , part_msg) ;
//   irc_cmd_msg(session , params[0] , greeting) ;

  // TODO: this maybe redundant
  irc_cmd_names(session , CHARSTAR(channel_name)) ;
}

void IrcClient::OnNumeric(irc_session_t* session , unsigned int event , const char* origin ,
                          const char**   params  , unsigned int count                      )
{
DEBUG_TRACE_IRC_SERVER_MSG

  if (event == LIBIRC_RFC_RPL_NAMREPLY) HandleNicks(params) ;
}

void IrcClient::HandleNicks(const char** params)
{
  String      channel_name = params[2] ;
  String      network_name = (channel_name == IRC::MY_CHANNEL) ? "LCTV" : "IRC" ;
  StringArray nicks        = StringArray::fromTokens(params[3] , false) ;

  if (channel_name == IRC::ROOT_CHANNEL) return ;

  nicks.removeEmptyStrings() ; nicks.removeString(IRC::ROOT_NICK) ;

DEBUG_TRACE_IRC_NICKS

  String branded = network_name + "["  + nicks.joinIntoString("] " +
                   network_name + "[") +                      "]"  ;
  nicks          = StringArray::fromTokens(branded , false) ;

  AvCaster::UpdateChatNicks(nicks) ;
}


/* IrcClient instance methods */

bool IrcClient::login(IrcServerInfo a_server)
{
  String logging_in_msg = CHARSTAR(String(IRC::LOGGING_IN_MSG + a_server.host)) ;
  AvCaster::AddChatLine(my_nick , logging_in_msg) ;

  //  NOTE: prefix 'server' with # for SSL
  bool is_err = irc_connect(a_server.session  , a_server.host     , a_server.port ,
                            a_server.password , a_server.nick     ,
                            a_server.username , a_server.realname                 ) ;

DEBUG_TRACE_IRC_LOGIN

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
// Make sure that all the IRC sessions are connected

  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
    if (!irc_is_connected(server->session)) { login(*server) ; continue ; }

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

    ++server ;
  }
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
  IrcServerInfo* server = this->servers.begin() ;
  while (server != this->servers.end())
  {
    irc_cmd_msg(server->session , IRC::MY_CHANNEL , CHARSTAR(chat_msg)) ; // TODO: get channel from irc_get_ctx()
    ++server ;
  }
  AvCaster::AddChatLine(my_nick , chat_msg) ;
}