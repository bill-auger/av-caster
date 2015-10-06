/*
  ==============================================================================

    TraceAvCaster.h
    Author: bill-auger

  ==============================================================================
*/

#ifndef TRACEAVCASTER_H_INCLUDED
#define TRACEAVCASTER_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"



/* state */

#  define DEBUG_TRACE_INIT_PHASE1             \
  Trace::TraceState("instantiating pipeline") ;

#  define DEBUG_TRACE_INIT_PHASE2           \
  Trace::TraceState("configuring pipeline") ;

#  define DEBUG_TRACE_INIT_PHASE3           \
  Trace::TraceState("configuring elements") ;

#  define DEBUG_TRACE_INIT_PHASE4               \
  Trace::TraceState("attaching native xwindow") ;

#  define DEBUG_TRACE_INIT_PHASE5        \
  Trace::TraceState("starting pipeline") ;

#  define DEBUG_TRACE_SET_GST_STATE                                                               \
  String state =(next_state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" :             \
                (next_state == GST_STATE_NULL)         ? "GST_STATE_NULL"         :             \
                (next_state == GST_STATE_READY)        ? "GST_STATE_READY"        :             \
                (next_state == GST_STATE_PAUSED)       ? "GST_STATE_PAUSED"       :             \
                (next_state == GST_STATE_PLAYING)      ? "GST_STATE_PLAYING"      : "unknown" ; \
  Trace::TraceState("setting " + state + " for " + String(gst_element_get_name(a_gst_element))) ;


/* configuration */

#  define DEBUG_TRACE_CONFIG_SCREENCAP                                        \
  Trace::TraceConfig("configuring screencap @ " + String(screencap_w) + "x" + \
                                                  String(screencap_h)       ) ;

#  define DEBUG_TRACE_CONFIG_CAMERA                                                      \
  Identifier camera_id = Config->cameraDevices.getPropertyName(camera_dev_n) ;           \
  Trace::TraceConfig("configuring camera " + STRING(Config->cameraDevices[camera_id])  + \
                     " @ "                 + CONFIG::CAMERA_RESOLUTIONS  [camera_res_n]) ;

#  define DEBUG_TRACE_CONFIG_AUDIO                         \
  Trace::TraceConfig("configuring " + api_name + " audio") ;

#  define DEBUG_TRACE_CONFIG_TEXT                                                \
  Trace::TraceConfig("configuring "     + CONFIG::TEXT_STYLES   [text_style_n] + \
                     " text overlay @ " + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define CONFIGURE_COMPOSITING_CHAIN          \
  Trace::TraceConfig("configuring compositor") ;

#  define DEBUG_TRACE_CONFIG_MUX                                                       \
  Trace::TraceConfig("configuring mux @ " + String(output_w) + "x" + String(output_h)) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                               \
  Trace::TraceConfig("configuring network stream to " + rtmp_url) ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_PHASE1      ;
#  define DEBUG_TRACE_INIT_PHASE2      ;
#  define DEBUG_TRACE_INIT_PHASE3      ;
#  define DEBUG_TRACE_INIT_PHASE4      ;
#  define DEBUG_TRACE_INIT_PHASE5      ;
#  define DEBUG_TRACE_SET_GST_STATE    ;
#  define DEBUG_TRACE_CONFIG_SCREENCAP ;
#  define DEBUG_TRACE_CONFIG_CAMERA    ;
#  define DEBUG_TRACE_CONFIG_AUDIO     ;
#  define DEBUG_TRACE_CONFIG_TEXT      ;
#  define CONFIGURE_COMPOSITING_CHAIN  ;
#  define DEBUG_TRACE_CONFIG_MUX       ;
#  define DEBUG_TRACE_CONFIG_OUTPUT    ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
