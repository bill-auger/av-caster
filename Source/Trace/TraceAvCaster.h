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

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("instantiating Gstreamer") ;

#  define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("AvCaster ready") ;


/* helpers */

#  define DEBUG_TRACE_SET_CONFIG                                                     \
  Trace::TraceVerbose("SetConfig() event: " + String(a_key)               + " => " + \
                                              STRING(storage_node[a_key]) + " => " + \
                                              STRING(a_value)                      ) ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_PHASE_1 ;
#  define DEBUG_TRACE_INIT_PHASE_2 ;
#  define DEBUG_TRACE_INIT_PHASE_3 ;
#  define DEBUG_TRACE_INIT_PHASE_4 ;
#  define DEBUG_TRACE_SET_CONFIG   ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
