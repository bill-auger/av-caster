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

#  define DEBUG_TRACE_INIT_PHASE4                \
  Trace::TraceState("attaching native xwindows") ;

#  define DEBUG_TRACE_INIT_PHASE5        \
  Trace::TraceState("starting pipeline") ;

#  define DEBUG_TRACE_SET_GST_STATE                                                              \
  String state = (next_state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" :             \
                 (next_state == GST_STATE_NULL        ) ? "GST_STATE_NULL"         :             \
                 (next_state == GST_STATE_READY       ) ? "GST_STATE_READY"        :             \
                 (next_state == GST_STATE_PAUSED      ) ? "GST_STATE_PAUSED"       :             \
                 (next_state == GST_STATE_PLAYING     ) ? "GST_STATE_PLAYING"      : "unknown" ; \
  Trace::TraceState("setting " + state + " for " + String(gst_element_get_name(a_gst_element)))  ;


/* configuration */

#  define DEBUG_TRACE_CONFIG_SCREENCAP                                 \
  Trace::TraceState("configuring screencap @ "                       + \
                    String(screencap_w) + "x"  + String(screencap_h) + \
                    " using "           + plugin_id                  ) ;

#  define DEBUG_TRACE_CONFIG_CAMERA                                                            \
  Identifier camera_id = Config->cameraDevices.getPropertyName(dev_n) ;                        \
  Trace::TraceState(String("configuring camera ") + STRING(Config->cameraDevices[camera_id]) + \
                    " (" + device + ") @ "        + CONFIG::CAMERA_RESOLUTIONS[res_n]        + \
                    " @ "                         + String(framerate) + "fps"                + \
                    " using "                     + plugin_id                                ) ;

#  define DEBUG_TRACE_CONFIG_AUDIO                                                      \
  String              api_name = CONFIG::AUDIO_APIS[audio_api] ;                        \
  AvCasterConfig::AudioApi api = (AvCasterConfig::AudioApi)audio_api ;                  \
  String bit_depth = (api == AvCasterConfig::ALSA_AUDIO ) ? "16" :                      \
                     (api == AvCasterConfig::PULSE_AUDIO) ? "16" :                      \
                     (api == AvCasterConfig::JACK_AUDIO ) ? "32" : "unknown" ;          \
  Trace::TraceState("configuring " + api_name + " audio (" + String(plugin_id) + ") " + \
                    bit_depth + "bit @ " + String(samplerate) + "hz x "               + \
                    String(n_channels) + " channels"                                  ) ;

#  define DEBUG_TRACE_CONFIG_TEXT                                                 \
  Trace::TraceState("configuring text " + CONFIG::TEXT_STYLES   [text_style_n] + \
                    " overlay @ "       + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define DEBUG_TRACE_CONFIG_COMPOSITOR                                 \
  Trace::TraceState("configuring compositor @ "                       + \
                    String(output_w) + "x" + String(output_h)         + \
                    " @ "                  + String(framerate) + "fps") ;

#  define DEBUG_TRACE_CONFIG_MUX                                                        \
  Trace::TraceState(String("configuring mux ")                                        + \
      "h264 video @ "      + String(output_w)      + "x"      + String(output_h)      + \
                   " -> "  + String(video_bitrate) + "kbps - "                        + \
      "mp3 audio 16bit @ " + String(samplerate)    + "hz -> " + String(audio_bitrate) + \
                 "kbps x " + String(n_channels)    + " channels"                      ) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                                            \
  Trace::TraceState("configuring " + stream + " output stream to " + output_url) ;

#  define DEBUG_TRACE_MAKE_ELEMENT                                                  \
  bool   is_err = new_element == nullptr ;                                         \
  String dbg    = " element '" + plugin_id + "' GstElement '" + element_id + "'" ; \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                          \
  else        Trace::TraceConfig("created" + dbg) ;

#  define DEBUG_TRACE_MAKE_CAPS                           \
  bool   is_err = new_caps == nullptr ;                  \
  if (is_err) Trace::TraceError("error creating caps") ; \
  else        Trace::TraceConfig("created caps") ;

#  define DEBUG_TRACE_ADD_ELEMENT                                                       \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id     = id ; g_free(id) ; \
  id         = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ; \
  String dbg = " element '" + element_id + "' to '" + bin_id + "'" ;                    \
  if (is_err) Trace::TraceError("error adding" + dbg) ;                                 \
  else        Trace::TraceConfig("added" + dbg) ;

#  define DEBUG_TRACE_LINK_ELEMENTS                                                    \
  gchar* id  = gst_element_get_name(source) ; String source_id = id ; g_free(id) ;     \
  id         = gst_element_get_name(sink  ) ; String sink_id   = id ; g_free(id) ;     \
  String dbg = " elements '" + String(source_id) + "' and '" + String(sink_id) + "'" ; \
  if (is_err) Trace::TraceError("error linking" + dbg) ;                               \
  else        Trace::TraceConfig("linked" + dbg) ;

#  define DEBUG_TRACE_LINK_PADS                                                            \
  GstElement* src_parent = gst_pad_get_parent_element(srcpad ) ;                           \
  GstElement* snk_parent = gst_pad_get_parent_element(sinkpad) ;                           \
  gchar* id  = gst_element_get_name(src_parent) ; String src_parent_id = id ; g_free(id) ; \
  id         = gst_element_get_name(snk_parent) ; String snk_parent_id = id ; g_free(id) ; \
  id         = gst_pad_get_name(srcpad ) ;        String src_pad_id    = id ; g_free(id) ; \
  id         = gst_pad_get_name(sinkpad) ;        String snk_pad_id    = id ; g_free(id) ; \
  gst_object_unref(src_parent) ; gst_object_unref(snk_parent) ;                            \
  String dbg = " pads '" + src_parent_id + ":" + String(src_pad_id) +                      \
               "' and '" + snk_parent_id + ":" + String(snk_pad_id) + "'" ;                \
  if (is_err) Trace::TraceError("error linking" + dbg) ;                                   \
  else        Trace::TraceConfig("linked" + dbg) ;

#  define DEBUG_TRACE_MAKE_GHOST_PAD                                                                  \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id     = id ; g_free(id) ; \
  id         = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ; \
  String dbg = " ghost pad '" + public_pad_id                               +           \
               "' on '"       + template_id   + "' of '" + element_id + "'" ;           \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                                            \
  else        Trace::TraceConfig("created" + dbg) ;

#  define DEBUG_TRACE_ADD_GHOST_PAD                                                  \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id = id ; g_free(id) ; \
         id  = gst_pad_get_name    (public_pad) ; String pad_id = id ; g_free(id) ; \
  String dbg = " ghost pad '" + pad_id + "' to '" + bin_id + "'" ;                  \
  if (is_err) Trace::TraceError("error adding" + dbg) ;                             \
  else        Trace::TraceConfig("added" + dbg) ;

#  define DEBUG_TRACE_GET_PAD                                                           \
  gchar* id  = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ; \
  String dbg = pad_avail + " pad '" + template_id + "' of '" + element_id + "'" ;       \
  if (is_err) Trace::TraceError("error getting " + dbg) ;                                \
  else        Trace::TraceConfig("got " + dbg) ;
#  define DEBUG_TRACE_GET_STATIC_PAD  String pad_avail = "static " ; DEBUG_TRACE_GET_PAD
#  define DEBUG_TRACE_GET_REQUEST_PAD String pad_avail = "request" ; DEBUG_TRACE_GET_PAD

#  define DEBUG_MAKE_GRAPHVIZ                                                          \
  char* graph_name = std::getenv("AVCASTER_GRAPH_NAME") ;                              \
  Trace::TraceConfig("creating graph " + String(graph_name)) ;                         \
  GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(Pipeline) , GST_DEBUG_GRAPH_SHOW_ALL , graph_name) ;
#else // DEBUG

#  define DEBUG_TRACE_INIT_PHASE1       ;
#  define DEBUG_TRACE_INIT_PHASE2       ;
#  define DEBUG_TRACE_INIT_PHASE3       ;
#  define DEBUG_TRACE_INIT_PHASE4       ;
#  define DEBUG_TRACE_INIT_PHASE5       ;
#  define DEBUG_TRACE_SET_GST_STATE     ;
#  define DEBUG_TRACE_CONFIG_SCREENCAP  ;
#  define DEBUG_TRACE_CONFIG_CAMERA     ;
#  define DEBUG_TRACE_CONFIG_AUDIO      ;
#  define DEBUG_TRACE_CONFIG_TEXT       ;
#  define DEBUG_TRACE_CONFIG_COMPOSITOR ;
#  define DEBUG_TRACE_CONFIG_MUX        ;
#  define DEBUG_TRACE_CONFIG_OUTPUT     ;
#  define DEBUG_TRACE_MAKE_ELEMENT      ;
#  define DEBUG_TRACE_MAKE_CAPS         ;
#  define DEBUG_TRACE_ADD_ELEMENT       ;
#  define DEBUG_TRACE_LINK_ELEMENTS     ;
#  define DEBUG_TRACE_LINK_PADS         ;
#  define DEBUG_TRACE_MAKE_GHOST_PAD    ;
#  define DEBUG_TRACE_ADD_GHOST_PAD     ;
#  define DEBUG_TRACE_GET_PAD           ;
#  define DEBUG_TRACE_GET_STATIC_PAD    ;
#  define DEBUG_TRACE_GET_REQUEST_PAD   ;
#  define DEBUG_MAKE_GRAPHVIZ           ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
