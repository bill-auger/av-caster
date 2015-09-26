/*
  ==============================================================================

    Trace.cpp
    Created: 12 Sep 2015 10:28:49am
    Author:  bill

  ==============================================================================
*/

#include "Trace.h"


/* Trace class public class methods */

bool Trace::TraceEvent(  String msg) { if (DEBUG_TRACE_EVENTS) DBG(          "[EVENT]:   " + msg) ; return true ; }
bool Trace::TraceConfig( String msg) { if (DEBUG_TRACE_CONFIG) DBG(          "[CONFIG]:  " + msg) ; return true ; }
bool Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB    ) DBG(          "[DEBUG]:   " + msg) ; return true ; }
#ifndef DEBUG_ANSI_COLORS
bool Trace::TraceState(  String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[STATE]:   " + msg) ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[WARNING]: " + msg) ; return true ; }
bool Trace::TraceError(  String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[ERROR]:   " + msg) ; return true ; }
#else // DEBUG_ANSI_COLORS
bool Trace::TraceState(  String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[1;32m[STATE]:   " + msg + "\033[0m") ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[1;33m[WARNING]: " + msg + "\033[0m") ; return true ; }
bool Trace::TraceError(  String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ; return true ; }
#endif // DEBUG_ANSI_COLORS

String Trace::NullOr(void* a_pointer , String if_valid_msg)
{
  return (a_pointer == nullptr) ? String("NULL") : if_valid_msg ;
}

const String Trace::CAMERA_ERROR_MSG  = "camera device error - restarting" ;
const String Trace::NETWORK_ERROR_MSG = "connection error - restarting" ;
