/*
  ==============================================================================

    Trace.h
    Created: 12 Sep 2015 10:28:49am
    Author:  bill

  ==============================================================================
*/

#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#include "JuceHeader.h"


// enable debug features
#define DEBUG_ANSI_COLORS
// #define DEBUG_NO_INSTANTIATE_MONITORS
#define NO_STREAM_OUT

// tracing
#ifdef DEBUG
#  define DEBUG_DEFINED 1
#else // DEBUG
#  define DEBUG_DEFINED 0
#endif // DEBUG
#define DEBUG_TRACE        DEBUG_DEFINED && 1
#define DEBUG_TRACE_EVENTS DEBUG_DEFINED && 1
#define DEBUG_TRACE_AVCONV DEBUG_DEFINED && 0
#define DEBUG_TRACE_STATE  DEBUG_DEFINED && 1
#define DEBUG_TRACE_VB     DEBUG_DEFINED && 1


#ifdef DEBUG

#define DEBUG_DUMP_WINDOW_HANDLES                                                                                                                                         \
    DBG("GstreamerVideo::start() isOnDesktop()=" + String(isOnDesktop()) + " this->isDetached=" + String(this->isDetached)) ;                                             \
    DBG("GstreamerVideo::start() parent->getWindowHandle()=" + ((getParentComponent()   == nullptr) ? "NULL" : String((int)getParentComponent()->getWindowHandle()  ))) ; \
    DBG("GstreamerVideo::start() peer->getNativeHandle()  =" + ((getPeer()              == nullptr) ? "NULL" : String((int)getPeer()->getNativeHandle()             ))) ; \
    DBG("GstreamerVideo::start() this->getWindowHandle()  =" + ((getWindowHandle()      == nullptr) ? "NULL" : String((int)getWindowHandle()                        ))) ; \
    DBG("GstreamerVideo::start() Top->getWindowHandle()   =" + ((getTopLevelComponent() == nullptr) ? "NULL" : String((int)getTopLevelComponent()->getWindowHandle()))) ;

#else // DEBUG

#define DEBUG_DUMP_WINDOW_HANDLES ;

#endif // DEBUG


class Trace
{
public:

  static bool TraceEvent(  String msg) ;
  static bool TraceGui(    String msg) ;
  static bool TraceAvconv( String msg) ;
  static bool TraceVerbose(String msg) ;
  static bool TraceState(  String msg) ;
  static bool TraceWarning(String msg) ;
  static bool TraceError(  String msg) ;

  static String NullOr(void* a_pointer , String if_valid_msg) ;

  static const String THREAD_EXIT_MSG ;
  static const String PROCESS_ERROR_MSG ;
  static const String CAMERA_ERROR_MSG ;
  static const String NETWORK_ERROR_MSG ;
} ;

#endif // TRACE_H_INCLUDED
