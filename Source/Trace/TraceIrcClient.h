/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#ifndef _TRACEIRCCLIENT_H_
#define _TRACEIRCCLIENT_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"

  // IRC event codes
static HashMap<int , String> IRC_EVENT_CODES ;
static void PopulateEventCodes()
{
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_WELCOME       , "RPL_WELCOME"      ) ; // 001
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_YOURHOST      , "RPL_YOURHOST"     ) ; // 002
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_CREATED       , "RPL_CREATED"      ) ; // 003
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_MYINFO        , "RPL_MYINFO"       ) ; // 004
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_BOUNCE        , "RPL_BOUNCE"       ) ; // 005
  IRC_EVENT_CODES.set(42                           , "RPL_YOURID"       ) ; // 042 non-RFC
  IRC_EVENT_CODES.set(250                          , "RPL_STATSDLINE"   ) ; // 250
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_LUSERCLIENT   , "RPL_LUSERCLIENT"  ) ; // 251
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_LUSEROP       , "RPL_LUSEROP"      ) ; // 252
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_LUSERUNKNOWN  , "RPL_LUSERUNKNOWN" ) ; // 253
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_LUSERCHANNELS , "RPL_LUSERCHANNELS") ; // 254
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_LUSERME       , "RPL_LUSERME"      ) ; // 255
  IRC_EVENT_CODES.set(256                          , "RPL_ADMINME"      ) ; // 256
  IRC_EVENT_CODES.set(265                          , "RPL_LOCALUSERS"   ) ; // 265 non-RFC
  IRC_EVENT_CODES.set(266                          , "RPL_GLOBALUSERS"  ) ; // 266 non-RFC
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_NAMREPLY      , "RPL_NAMREPLY"     ) ; // 353
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_ENDOFNAMES    , "RPL_ENDOFNAMES"   ) ; // 366
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_MOTD          , "RPL_MOTD"         ) ; // 372
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_MOTDSTART     , "RPL_MOTDSTART"    ) ; // 375
  IRC_EVENT_CODES.set(LIBIRC_RFC_RPL_ENDOFMOTD     , "RPL_ENDOFMOTD"    ) ; // 376
}


#  define DUMP_SERVER_PARAMS String dbg = "" ;                         \
  for (int i = 0 ; i < count ; ++i)                                    \
    dbg += "\tparams[" + String(i) + "]=" + String(params[i]) + "\n" ; \
  Trace::TraceChatVb(dbg) ;

#  define DEBUG_TRACE_CREATE_SESSION                                                   \
  String dbg = " session for network '" + String(network) + "'" ;                      \
  String err = (network.isEmpty())       ? String() :                                  \
               String((is_valid_session) ? String() : " session invalid") +            \
               String((is_valid_port   ) ? String() : " port invalid"   ) +            \
               String((is_valid_nick   ) ? String() : " nick invalid"   ) +            \
               String((is_valid_channel) ? String() : " channel invalid") ;            \
  if      (err.isNotEmpty()) Trace::TraceError("error creating" + dbg + " - " + err) ; \
  else if (is_valid_network) Trace::TraceChat("created" + dbg)                         ;

#  define DEBUG_TRACE_LOGIN_FAILED                                      \
  if (n_retries == IRC::STATE_FAILED + 1)                               \
    Trace::TraceError("error connecting to '" + String(network)       + \
                      ":"                     + String(port   )       + \
                      "' as '"                + String(nick   ) + "'" ) ;

#  define DEBUG_TRACE_LOGIN                                                     \
  String err              = String(irc_strerror(irc_errno(session))) ;          \
  bool   is_connect_error = err != String("Illegal operation for this state") ; \
  String dbg              = "connecting to '" + String(network) +               \
                            ":"               + String(port   ) +               \
                            "' as '"          + String(nick   ) + "'" ;         \
  if      (!is_err         ) Trace::TraceChat(dbg) ;                            \
  else if (is_connect_error) Trace::TraceError("error " + dbg + " - " + err)    ;

#  define DEBUG_TRACE_CONNECTED                                                             \
  String network = STRING(NetworkStore[CONFIG::NETWORK_ID]) ;                               \
  Trace::TraceState("connected to '" + network + "' host (" + host + ")") ;                 \
  if (network != host) Trace::TraceConfig("updating '" + network + "' host (" + host + ")") ;

#  define DEBUG_TRACE_LOGOUT                                        \
  String network = STRING(NetworkStore[CONFIG::NETWORK_ID]) ;       \
  int    port    = int   (NetworkStore[CONFIG::PORT_ID   ]) ;       \
  String nick    = STRING(NetworkStore[CONFIG::NICK_ID   ]) ;       \
  Trace::TraceChat("disconnecting from '" + String(network)       + \
                   ":"                    + String(port   )       + \
                   "' as '"               + String(nick   ) + "'" ) ;

#  define DEBUG_TRACE_SERVER_EVENT                                                     \
  if (IRC_EVENT_CODES.size() == 0) PopulateEventCodes() ;                              \
  String code = (IRC_EVENT_CODES.contains(event)) ? IRC_EVENT_CODES[event]           : \
                                                    String("code: ") + String(event) ; \
  Trace::TraceChatVb(String("received ") + code) ; DUMP_SERVER_PARAMS

#  define DEBUG_TRACE_NICKS                                                     \
  StringArray newnicks     = StringArray::fromTokens(nicks , false) ;           \
  String      nnewnicks    = String(newnicks.size()) ;                          \
  String      ntotalnicks  = String(Nicks.size()   ) ;                          \
  String      newnicks_csv = newnicks.joinIntoString(",") ;                     \
  Trace::TraceChat("got ("          + nnewnicks + "/"           + ntotalnicks + \
                   ") NAMES from '" + network   + "' channel: " + channel     + \
                   ((Trace::ChatVbEnabled) ? " [" + newnicks_csv + "]" : "")  ) ;

#  define DEBUG_TRACE_CHAT_MSG_VB                                                        \
  if (count == 2) Trace::TraceChatVb("'" + String((!!origin) ? origin : "someone") +     \
                                     "' said in channel " + String(params[0])      +     \
                                     ": "                 + String(params[1])      + "") ;

#  define DEBUG_TRACE_CHAT_MSG                                   \
  if (is_root_channel ) Trace::TraceChatVb("is_root_channel" ) ; \
  if (is_root_user    ) Trace::TraceChatVb("is_root_user"    ) ; \
  if (is_xmpp_channel ) Trace::TraceChatVb("is_my_channel"   ) ; \
  if (is_login_blocked) Trace::TraceChatVb("is_login_blocked") ; \
  if (is_logged_in    ) Trace::TraceChatVb("is_logged_in"    ) ; \
  if (has_kicked_self ) Trace::TraceChatVb("has_kicked_self" ) ; \
  String dbg = ((is_root_user && is_root_channel  ) ?                                        \
               ((is_logged_in                     ) ? "logged into bitlbee"              :   \
               ((is_login_blocked                 ) ? "already logged into bitlbee" : "")) : \
               ((!is_root_user && !is_root_channel) ? nick + " said: '" + message + "'" :    \
               ((DEBUG_TRACE_CHAT_VB              ) ? "unhandled msg" : "")      )      ) ;  \
  if (dbg.isNotEmpty()) Trace::TraceChat(dbg)                                                ;

#  define DEBUG_TRACE_ONJOIN Trace::TraceChat(nick + " just joined channel " + channel) ;

#  define DEBUG_TRACE_ONPART Trace::TraceChat(nick + " just parted channel " + channel) ;

#  define DEBUG_TRACE_NICK_CHANGE                                          \
  IrcClient* client = static_cast<IrcClient*>(irc_get_ctx(session)) ;      \
  Trace::TraceChat("'"     + from_nick + "' changed nick to '" + to_nick + \
                   "' on " + network   + channel                         ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CREATE_SESSION ;
#  define DEBUG_TRACE_LOGIN          ;
#  define DEBUG_TRACE_LOGIN_FAILED   ;
#  define DEBUG_TRACE_CONNECTED      ;
#  define DEBUG_TRACE_SERVER_EVENT   ;
#  define DEBUG_TRACE_NICKS          ;
#  define DEBUG_TRACE_CHAT_MSG_VB    ;
#  define DEBUG_TRACE_CHAT_MSG       ;
#  define DEBUG_TRACE_ONJOIN         ;
#  define DEBUG_TRACE_ONPART         ;
#  define DEBUG_TRACE_NICK_CHANGE    ;

#endif // DEBUG_TRACE
#endif // _TRACEIRCCLIENT_H_
