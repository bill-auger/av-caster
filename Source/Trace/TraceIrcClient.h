
#ifndef TRACEIRCCLIENT_H_INCLUDED
#define TRACEIRCCLIENT_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"

#  define DUMP_SERVER_PARAMS String dbg = "" ;                    \
  for (int i = 0 ; i < count ; ++i)                               \
    dbg += "\n\tparams[" + String(i) + "]=" + String(params[i]) ; \
  Trace::TraceChat(dbg) ;                                         \

#  define DEBUG_TRACE_IRC_LOGIN                                                            \
  if (is_err) Trace::TraceError("error connecting to " + String(a_server.host) + " - " +   \
                                String(irc_strerror(irc_errno(a_server.session)))      ) ; \
  else        Trace::TraceChat("connecting to " + String(a_server.host))                   ;

#  define DEBUG_TRACE_IRC_CONNECTED Trace::TraceChat("connected to " + String(origin)) ;

#  define DEBUG_TRACE_IRC_SERVER_MSG if (DEBUG_TRACE_VB)                                      \
  { if      (event == LIBIRC_RFC_RPL_NAMREPLY  ) Trace::TraceChat("received names reply") ;   \
    else if (event == LIBIRC_RFC_RPL_ENDOFNAMES) Trace::TraceChat("received end of names") ;  \
    else { Trace::TraceChat(String("received code: ") + String(event)) ; DUMP_SERVER_PARAMS } }

#  define DEBUG_TRACE_IRC_NICKS                                                   \
  String names = (DEBUG_TRACE_VB || 1) ? " [" + nicks.joinIntoString(",") + "]" : "" ; \
  Trace::TraceChat("got " + String(nicks.size())                +                 \
                   " nicks for channel: " + channel_name + names)                 ;

#  define DEBUG_TRACE_IRC_CHAT_MSG_VB                                                       \
  if (DEBUG_TRACE_VB && count == 2)                                                         \
    Trace::TraceChat("'" + String((!!origin) ? origin : "someone") + "' said in channel " + \
                     String(params[0]) + ": " + String(params[1]) + "")                     ;

#  define DEBUG_TRACE_IRC_CHAT_MSG                                \
  bool has_kicked_self = message.endsWith(IRC::KICKED_SELF_MSG) ; \
  if (is_root_channel ) Trace::TraceVerbose("is_root_channel" ) ; \
  if (is_root_user    ) Trace::TraceVerbose("is_root_user"    ) ; \
  if (is_my_channel   ) Trace::TraceVerbose("is_my_channel"   ) ; \
  if (is_login_blocked) Trace::TraceVerbose("is_login_blocked") ; \
  if (is_logged_in    ) Trace::TraceVerbose("is_logged_in"    ) ; \
  if (has_kicked_self ) Trace::TraceVerbose("has_kicked_self" ) ; \
  String dbg = ((is_root_user && is_root_channel  ) ?                                        \
               ((is_logged_in                     ) ? "logged into bitlbee"              :   \
               ((is_login_blocked                 ) ? "already logged into bitlbee" : "")) : \
               ((!is_root_user && !is_root_channel) ? nick + " said: " + message :           \
               ((DEBUG_TRACE_VB                   ) ? "unhandled msg" : "")      )      ) ;  \
  if (dbg.isNotEmpty()) Trace::TraceChat(dbg)                                                ;

#  define DEBUG_TRACE_IRC_ONJOIN                                  \
  Trace::TraceChat(nick + " just joined channel " + channel_name) ;

#  define DEBUG_TRACE_IRC_ONPART                                  \
  Trace::TraceChat(nick + " just parted channel " + channel_name) ;

#  define DEBUG_TRACE_IRC_THREAD_RUN_IN                                \
  Trace::TraceState("starting '" + this->getThreadName() + "' thread") ;

#  define DEBUG_TRACE_IRC_THREAD_RUN_OUT                               \
  Trace::TraceState("stopping '" + this->getThreadName() + "' thread") ;

#else // DEBUG

#  define DEBUG_TRACE_IRC_LOGIN          ;
#  define DEBUG_TRACE_IRC_CONNECTED      ;
#  define DEBUG_TRACE_IRC_SERVER_MSG     ;
#  define DEBUG_TRACE_IRC_NICKS          ;
#  define DEBUG_TRACE_IRC_CHAT_MSG_VB    ;
#  define DEBUG_TRACE_IRC_CHAT_MSG       ;
#  define DEBUG_TRACE_IRC_ONJOIN         ;
#  define DEBUG_TRACE_IRC_ONPART         ;
#  define DEBUG_TRACE_IRC_THREAD_RUN_IN  ;
#  define DEBUG_TRACE_IRC_THREAD_RUN_OUT ;

#endif // DEBUG
#endif // TRACEIRCCLIENT_H_INCLUDED
