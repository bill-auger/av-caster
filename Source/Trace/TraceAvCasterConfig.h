/*
  ==============================================================================

    TraceAvCasterConfig.h
    Created: 26 Sep 2015 9:11:08am
    Author:  bill-auger

  ==============================================================================
*/

#ifndef TRACEAVCASTERCONFIG_H_INCLUDED
#define TRACEAVCASTERCONFIG_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


/* persistence */

bool DbgTracing = false ;
#define DEBUG_TRACE_LOAD_CONFIG                                                   \
  DbgTracing = true ;                                                             \
  if (default_xml == nullptr || !default_xml->hasTagName(CONFIG::STORAGE_ID))     \
       Trace::TraceConfig("default config invalid - bailing") ;                   \
  else Trace::TraceConfig("default config loaded") ;                              \
  if (!config_stream->openedOk())                                                 \
      Trace::TraceConfig("stored config not found - falling back on defaults") ;  \
  else if (!validateConfig(stored_config))                                        \
      Trace::TraceConfig("stored config is invalid - falling back on defaults") ; \
  else Trace::TraceConfig("stored config found") ;                                \
  DbgTracing = false ;

#define DEBUG_TRACE_VALIDATE_CONFIG                                                            \
  String latest_version = String(CONFIG::CONFIG_VERSION) ;                                 \
  String success_msg    = "stored config parsed successfully v" + String(stored_version) ; \
  String fail_msg       = "stored config not found or invalid" ;                           \
  if (!DbgTracing)                                                                        \
    Trace::TraceConfig(((has_stored_config) ? success_msg : fail_msg              ) +      \
                       ((do_versions_match) ? ""                                  :        \
                       " (latest is v" + latest_version + " - restoring defualts)")   )    ;


/* state */

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                     \
  String key = String(a_key) ;                                \
  String val = a_node[a_key].toString() ;                     \
  Trace::TraceEvent("value changed => " + key + " => " + val) ;

#else // DEBUG

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED ;

#endif // DEBUG
#endif  // TRACEAVCASTERCONFIG_H_INCLUDED
