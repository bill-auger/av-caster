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

#  define DEBUG_TRACE_SHUTDOWN Trace::TraceState("clean shutdown - bye") ;

#else // DEBUG

#  define DEBUG_TRACE_SHUTDOWN ;

#endif // DEBUG
#endif  // TRACEMAIN_H_INCLUDED
