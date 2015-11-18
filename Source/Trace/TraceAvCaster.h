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


#ifndef TRACEAVCASTER_H_INCLUDED
#define TRACEAVCASTER_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_INIT_VERSION printf("%s\n" , CHARSTAR(APP::CLI_VERSION_MSG)) ;

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("instantiating media") ;

#  define DEBUG_TRACE_INIT_PHASE_5 Trace::TraceState("instantiating network") ;

#  define DEBUG_TRACE_INIT_PHASE_6 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_PRE_INIT                                         \
  StringArray tokens ;                                                                   \
  if      (CliParams.contains(APP::CLI_HELP_TOKEN   )) tokens.add("CLI_HELP_TOKEN") ;    \
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN)) tokens.add("CLI_PRESETS_TOKEN") ; \
  else if (CliParams.contains(APP::CLI_VERSION_TOKEN)) tokens.add("CLI_VERSION_TOKEN") ; \
  String dbg = tokens.joinIntoString(",") ;                                              \
  if (tokens.size()) Trace::TraceConfig("found pre-init cli tokens " + dbg)              ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_POST_INIT                                 \
  StringArray tokens ;                                                            \
  if (CliParams.contains(APP::CLI_PRESET_TOKEN)) tokens.add("CLI_PRESET_TOKEN") ; \
  String dbg = tokens.joinIntoString(",") ;                                       \
  if (tokens.size()) Trace::TraceConfig("found post-init cli tokens " + dbg)      ;

#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT                                                 \
  bool is_err = false ; String dbg = "" ;                                                  \
  if (!APP::HOME_DIR   .isDirectory()) { is_err = true ; dbg += " invlaid HOME_DIR" ;    } \
  if (!APP::APPDATA_DIR.isDirectory()) { is_err = true ; dbg += " invlaid APPDATA_DIR" ; } \
  if (!APP::VIDEOS_DIR .isDirectory()) { is_err = true ; dbg += " invlaid VIDEOS_DIR" ;  } \
  if (is_err) Trace::TraceError(dbg) ; else Trace::TraceState("environment is sane")       ;

#  define DEBUG_TRACE_REFRESH_GUI                                                      \
  String gui = (is_config_pending) ? "Config" : (is_preview_on) ? "Preview" : "Chat" ; \
  Trace::TraceState("showing " + gui + " GUI")                                         ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_1 Trace::TraceState("shutting down network") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_2 Trace::TraceState("shutting down media") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_3 Trace::TraceState("shutting down storage") ;


/* config */

#  define DEBUG_TRACE_SET_CONFIG                                              \
  String    key        = (a_key.isValid()) ? String(a_key) : String("NULL") ; \
  ValueTree node       = Store->getKeyNode(a_key) ;                           \
  String    change_msg = "key '"             + key                 +          \
                         "' changing from '" + STRING(node[a_key]) +          \
                         "' to '"            + STRING(a_value    ) + "'" ;    \
  Trace::TraceGui("gui " + change_msg) ;

#  define DEBUG_TRACE_ADD_CHAT_NICK                                                \
  if (!Store->chatters.getChildWithName(user_id).isValid())                        \
    Trace::TraceConfig("adding chatter '" + String(user_id) + "' (" + *nick + ")") ;

#  define DEBUG_TRACE_REMOVE_CHAT_NICK                                     \
  String userid = String(chatter_store.getType()) ;                        \
  String nick   = STRING(chatter_store[CONFIG::CHAT_NICK_ID]) ;            \
  if (!nicks.contains(nick))                                               \
    Trace::TraceConfig("removing chatter '" + userid + "' (" + nick + ")") ;


/* helpers */

#  define DEBUG_TRACE_DISPLAY_ALERT                                                     \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text)   ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_VERSION                ;
#  define DEBUG_TRACE_INIT_PHASE_1                ;
#  define DEBUG_TRACE_INIT_PHASE_2                ;
#  define DEBUG_TRACE_INIT_PHASE_3                ;
#  define DEBUG_TRACE_INIT_PHASE_4                ;
#  define DEBUG_TRACE_INIT_PHASE_5                ;
#  define DEBUG_TRACE_INIT_PHASE_6                ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_PRE_INIT  ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_POST_INIT ;
#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT        ;
#  define DEBUG_TRACE_REFRESH_GUI                 ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_1            ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_2            ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_3            ;
#  define DEBUG_TRACE_SET_CONFIG                  ;
#  define DEBUG_TRACE_ADD_CHAT_NICK               ;
#  define DEBUG_TRACE_REMOVE_CHAT_NICK            ;
#  define DEBUG_TRACE_DISPLAY_ALERT               ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
