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

#  define DEBUG_TRACE_CONFIG_CAMERA                                                     \
  Identifier camera_id = Config->cameraDevices.getPropertyName(dev_n) ;                 \
  Trace::TraceState("configuring camera "  + STRING(Config->cameraDevices[camera_id]) + \
                    " (" + device + ") @ " + CONFIG::CAMERA_RESOLUTIONS  [res_n]      + \
                    " using "              + plugin_id                                ) ;

#  define DEBUG_TRACE_CONFIG_AUDIO                                                    \
  String api_name  = CONFIG::AUDIO_APIS[audio_api] ;                                  \
  Trace::TraceState("configuring " + api_name + " audio (" + String(plugin_id) + ")") ;

#  define DEBUG_TRACE_CONFIG_TEXT                                                 \
  Trace::TraceState("configuring text " + CONFIG::TEXT_STYLES   [text_style_n] + \
                    " overlay @ "       + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define DEBUG_TRACE_CONFIG_COMPOSITOR       \
  Trace::TraceState("configuring compositor") ;

#  define DEBUG_TRACE_CONFIG_MUX                                                                \
  int    audio_api = int(Config->configStore[CONFIG::AUDIO_API_ID]) ;                           \
  String api_name  = CONFIG::AUDIO_APIS[audio_api] ; String samplerate ;                        \
  String bitrate   = String(audio_bitrate) ;                                                    \
  switch ((AvCasterConfig::AudioApi)audio_api)                                                  \
  {                                                                                             \
    case AvCasterConfig::ALSA_AUDIO:  samplerate = "16" ; break ;                               \
    case AvCasterConfig::PULSE_AUDIO: samplerate = "16" ; break ;                               \
    case AvCasterConfig::JACK_AUDIO:  samplerate = "32" ; break ;                               \
  }                                                                                             \
  Trace::TraceState("configuring mux "                                                        + \
      String(output_w) + "x" + String(output_h) + " -> "  + String(video_bitrate) + "kbps - " + \
      samplerate       + "bit " + api_name + " audio @ 44100Hz -> " + bitrate     + "kbps"    ) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                                            \
  Trace::TraceState("configuring " + stream + " output stream to " + file_url) ;

# define DEBUG_TRACE_MAKE_ELEMENT                           \
  bool   is_err = new_element == nullptr ;                  \
  String dbg    = plugin_id + " GstElement " + element_id ; \
  if (is_err) Trace::TraceError("error creating " + dbg) ;  \
  else        Trace::TraceConfig("created " + dbg) ;

# define DEBUG_TRACE_MAKE_CAPS                           \
  bool   is_err = new_caps == nullptr ;                  \
  String dbg    = "" ;                                   \
  if (is_err) Trace::TraceError("error creating caps") ; \
  else        Trace::TraceConfig("created caps") ;

#  define DEBUG_TRACE_ADD_ELEMENT                                                               \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id     = String(id) ; g_free(id) ; \
  id         = gst_element_get_name(an_element) ; String element_id = String(id) ; g_free(id) ; \
  String dbg = element_id + " to " + bin_id ;                                                   \
  if (is_err) Trace::TraceError("error adding " + dbg) ;                                        \
  else        Trace::TraceConfig("added " + dbg) ;

#  define DEBUG_TRACE_LINK_ELEMENTS                                                        \
  gchar* id  = gst_element_get_name(source) ; String source_id = String(id) ; g_free(id) ; \
  id         = gst_element_get_name(sink  ) ; String sink_id   = String(id) ; g_free(id) ; \
  String dbg = String(source_id) + " and " + String(sink_id) ;                             \
  if (is_err) Trace::TraceError("error linking " + dbg) ;                                  \
  else        Trace::TraceConfig("linked " + dbg) ;

# define DEBUG_TRACE_MAKE_GHOST_PAD                                                             \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id     = String(id) ; g_free(id) ; \
  id         = gst_element_get_name(an_element) ; String element_id = String(id) ; g_free(id) ; \
  String dbg = " ghost pad " + public_pad_id + " on " + private_pad_id + " of " + element_id  ; \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                                       \
  else        Trace::TraceConfig("created" + dbg) ;

# define DEBUG_TRACE_ADD_GHOST_PAD                                             \
  dbg = "adding ghost pad " + public_pad_id + " to " + bin_id ;                \
  if (is_err) Trace::TraceError("error " + dbg) ; else Trace::TraceConfig(dbg) ;

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
#  define DEBUG_TRACE_LINK_ELEMENT      ;
#  define DEBUG_TRACE_MAKE_GHOST_PAD    ;
#  define DEBUG_TRACE_ADD_GHOST_PAD     ;
#  define DEBUG_MAKE_GRAPHVIZ           ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
