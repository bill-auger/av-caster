/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#include "JuceHeader.h"
#include "../Constants.h"


#ifdef DEBUG

#  define DEBUG_TRACE_DUMP_CONFIG if (DEBUG_TRACE_VB) Trace::DumpConfig(this->configStore) ;

#else // DEBUG

#  define DEBUG_TRACE_DUMP_CONFIG         ;

#endif // DEBUG


#ifdef DEBUG
class Trace
{
public:

  static bool TraceEvent(  String msg) ;
  static bool TraceGui(    String msg) ;
  static bool TraceConfig( String msg) ;
  static bool TraceVerbose(String msg) ;
  static bool TraceState(  String msg) ;
  static bool TraceWarning(String msg) ;
  static bool TraceError(  String msg) ;

  static void TraceMissingProperty(ValueTree  config_store , Identifier a_property_id) ;
  static void DumpConfig(          ValueTree  config_store) ;
} ;
#endif // DEBUG

#endif // TRACE_H_INCLUDED
