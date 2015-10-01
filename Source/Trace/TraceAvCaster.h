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

#  define CONFIGURE_COMPOSITING_CHAIN           \
  Trace::TraceConfig("configuring compositing") ;

#  define DEBUG_TRACE_CONFIG_MUX                                                      \
  Trace::TraceConfig("configuring compositor and mux @ " + output_w + "x" + output_h) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                               \
  Trace::TraceConfig("configuring network stream to " + rtmp_url) ;


/* state */

#  define DEBUG_TRACE_SET_GST_STATE                                                               \
  String state =(next_state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" :             \
                (next_state == GST_STATE_NULL)         ? "GST_STATE_NULL"         :             \
                (next_state == GST_STATE_READY)        ? "GST_STATE_READY"        :             \
                (next_state == GST_STATE_PAUSED)       ? "GST_STATE_PAUSED"       :             \
                (next_state == GST_STATE_PLAYING)      ? "GST_STATE_PLAYING"      : "unknown" ; \
  Trace::TraceState("setting " + state + " for " + String(gst_element_get_name(a_gst_element))) ;

#else // DEBUG

#  define DEBUG_TRACE_SET_GST_STATE ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
