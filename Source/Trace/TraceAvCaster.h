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

#  define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("instantiating Gstreamer") ;

#  define DEBUG_TRACE_INIT_PHASE_5 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_TOGGLE_CONFIG                                                 \
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

#  define DEBUG_TRACE_INIT_PHASE_1  ;
#  define DEBUG_TRACE_INIT_PHASE_2  ;
#  define DEBUG_TRACE_INIT_PHASE_3  ;
#  define DEBUG_TRACE_INIT_PHASE_4  ;
#  define DEBUG_TRACE_INIT_PHASE_5  ;
#  define DEBUG_TRACE_TOGGLE_CONFIG ;
#  define DEBUG_TRACE_SET_CONFIG    ;
#  define DISPLAY_ALERT             ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
