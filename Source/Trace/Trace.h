/*
  ==============================================================================

    Trace.h
    Created: 12 Sep 2015 10:28:49am
    Author:  bill

  ==============================================================================
*/

#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED
#if DEBUG

// enable debug features
#define DEBUG_ANSI_COLORS

// tracing
#define DEBUG_TRACE        DEBUG && 1
#define DEBUG_TRACE_EVENTS DEBUG && 1
#define DEBUG_TRACE_AVCONV DEBUG && 0
#define DEBUG_TRACE_STATE  DEBUG && 1
#define DEBUG_TRACE_VB     DEBUG && 1


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

  static const String THREAD_EXIT_MSG ;
  static const String PROCESS_ERROR_MSG ;
  static const String CAMERA_ERROR_MSG ;
  static const String NETWORK_ERROR_MSG ;
} ;

#endif // DEBUG
#endif  // TRACE_H_INCLUDED
