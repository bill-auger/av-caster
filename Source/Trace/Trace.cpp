/*
  ==============================================================================

    Trace.cpp
    Created: 12 Sep 2015 10:28:49am
    Author:  bill

  ==============================================================================
*/

#if DEBUG

#  include "../Constants.h"
#  include "../FfmpegStreamer.h"
#  include "Trace.h"


/* Trace class public class methods */

bool Trace::TraceEvent(String msg)   { if (DEBUG_TRACE_EVENTS) DBG(          "[EVENT]:  " + msg) ; return true ; }
bool Trace::TraceAvconv(String msg)  { if (DEBUG_TRACE_AVCONV) DBG(          "[AVCONV]: " + msg) ; return true ; }
bool Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB    ) DBG(          "[DEBUG]:  " + msg) ; return true ; }
#ifndef DEBUG_ANSI_COLORS
bool Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG(          "[STATE]:  " + msg) ; return true ; }
bool Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG(          "[ERROR]:  " + msg) ; return true ; }
#else // DEBUG_ANSI_COLORS
bool Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG("\033[1;33m[STATE]:   " + msg + "\033[0m") ; return true ; }
bool Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ; return true ; }
#endif // DEBUG_ANSI_COLORS

#endif // #if DEBUG
