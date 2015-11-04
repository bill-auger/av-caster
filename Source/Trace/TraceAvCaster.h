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

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("instantiating gStreamer") ;

#  define DEBUG_TRACE_INIT_PHASE_5 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS                                         \
  if (CliParams.contains(APP::CLI_QUIT_TOKEN)) Trace::TraceState("forced quit") ;

#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT                                                 \
  bool is_err = false ; String dbg = "" ;                                                  \
  if (!APP::HOME_DIR   .isDirectory()) { is_err = true ; dbg += " invlaid HOME_DIR" ;    } \
  if (!APP::APPDATA_DIR.isDirectory()) { is_err = true ; dbg += " invlaid APPDATA_DIR" ; } \
  if (!APP::VIDEOS_DIR .isDirectory()) { is_err = true ; dbg += " invlaid VIDEOS_DIR" ;  } \
  if (is_err) Trace::TraceError(dbg) ; else Trace::TraceState("environment is sane")       ;

#  define DEBUG_TRACE_REFRESH_GUI                                                   \
  bool should_show_config = bool(Store->configRoot[CONFIG::IS_CONFIG_PENDING_ID]) ; \
  String gui = (should_show_config) ? "Config" : "Controls" ;                       \
  Trace::TraceState("showing " + gui + " GUI") ;


/* helpers */

#  define DEBUG_TRACE_SET_CONFIG                                                     \
  String key = (a_key.isValid()) ? String(a_key) : String("NULL") ;                  \
  Trace::TraceVerbose("SetConfig() event: " + key                         + " => " + \
                                              STRING(storage_node[a_key]) + " => " + \
                                              STRING(a_value)                      ) ;

#  define DISPLAY_ALERT                                                                  \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text) ; \
  Alerts.remove(0) ; return ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_PHASE_1         ;
#  define DEBUG_TRACE_INIT_PHASE_2         ;
#  define DEBUG_TRACE_INIT_PHASE_3         ;
#  define DEBUG_TRACE_INIT_PHASE_4         ;
#  define DEBUG_TRACE_INIT_PHASE_5         ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS    ;
#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT ;
#  define DEBUG_TRACE_REFRESH_GUI          ;
#  define DEBUG_TRACE_SET_CONFIG           ;
#  define DISPLAY_ALERT                    ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
