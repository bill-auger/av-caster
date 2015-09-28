/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef TRACECONFIG_H_INCLUDED
#define TRACECONFIG_H_INCLUDED

#include "Trace.h"


#if DEBUG

#  define DEBUG_TRACE_SET_CONFIG                                           \
  DBG("Config::setConfig() " + String(a_key)                    + " => " + \
                               STRING(this->configStore[a_key]) + " => " + \
                               STRING(a_value)                           ) ;

#else // DEBUG

#  define DEBUG_TRACE_SET_CONFIG ;

#endif // DEBUG

#endif  // TRACECONFIG_H_INCLUDED
