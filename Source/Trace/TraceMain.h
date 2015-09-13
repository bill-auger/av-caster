/*
  ==============================================================================

    TraceMain.h
    Created: 12 Sep 2015 10:29:01am
    Author:  bill

  ==============================================================================
*/

#ifndef TRACEMAIN_H_INCLUDED
#define TRACEMAIN_H_INCLUDED
#if DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_SHUTDOWN_IN  Trace::TraceState("shutting down") ;
#  define DEBUG_TRACE_SHUTDOWN_OUT Trace::TraceState("clean shutdown - bye") ;

#else // DEBUG

#  define DEBUG_TRACE_SHUTDOWN_IN ;
#  define DEBUG_TRACE_SHUTDOWN_OUT ;

#endif // DEBUG
#endif  // TRACEMAIN_H_INCLUDED
