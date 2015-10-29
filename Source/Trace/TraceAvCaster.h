/*
  ==============================================================================

    TraceAvCaster.h
    Author: bill-auger

  ==============================================================================
*/

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
