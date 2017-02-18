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


#ifndef _TRACEMAIN_H_
#define _TRACEMAIN_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_INIT_VERSION                        \
  if (!cli_params.contains(APP::CLI_VERSION_TOKEN))       \
    LOG(AvCaster::VersionMsg().joinIntoString("\n") + "\n") ;

#  define DEBUG_TRACE_SHUTDOWN_IN  Trace::TraceState("shutting down") ;

#  define DEBUG_TRACE_SHUTDOWN_OUT Trace::TraceState("clean shutdown - bye") ;


/* alerts */

#  define DEBUG_TRACE_ALERT                                                             \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text)   ;

#  define DEBUG_TRACE_DISPLAY_ALERT                                                \
  Trace::TraceGuiVb("displaying alert - (" + String(Alerts.size()) + " remaining") ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_INIT_VERSION  ;
#  define DEBUG_TRACE_SHUTDOWN_IN   ;
#  define DEBUG_TRACE_SHUTDOWN_OUT  ;
#  define DEBUG_TRACE_ALERT         ;
#  define DEBUG_TRACE_DISPLAY_ALERT ;

#endif // DEBUG_TRACE
#endif // _TRACEMAIN_H_
