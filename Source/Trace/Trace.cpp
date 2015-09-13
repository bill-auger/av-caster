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

bool Trace::TraceEvent(String msg)   { if (DEBUG_TRACE_EVENTS) DBG(          "[EVENT]:   " + msg) ; return true ; }
bool Trace::TraceAvconv(String msg)  { if (DEBUG_TRACE_AVCONV) DBG(          "[AVCONV]:  " + msg) ; return true ; }
bool Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB    ) DBG(          "[DEBUG]:   " + msg) ; return true ; }
#ifndef DEBUG_ANSI_COLORS
bool Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG(          "[STATE]:   " + msg) ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[WARNING]: " + msg) ; return true ; }
bool Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG(          "[ERROR]:   " + msg) ; return true ; }
#else // DEBUG_ANSI_COLORS
bool Trace::TraceState(String msg)   { if (DEBUG_TRACE_STATE)  DBG("\033[1;32m[STATE]:   " + msg + "\033[0m") ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[1;33m[WARNING]: " + msg + "\033[0m") ; return true ; }
bool Trace::TraceError(String msg)   { if (DEBUG_TRACE_STATE)  DBG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ; return true ; }
#endif // DEBUG_ANSI_COLORS

const String Trace::THREAD_EXIT_MSG   = "closing stream: " ;
const String Trace::PROCESS_ERROR_MSG = "avconv process died - restarting" ;
const String Trace::CAMERA_ERROR_MSG  = "camera device error - restarting" ;
const String Trace::NETWORK_ERROR_MSG = "connection error - restarting" ;

#endif // #if DEBUG
