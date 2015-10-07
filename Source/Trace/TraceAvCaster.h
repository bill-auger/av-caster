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

#  define DEBUG_TRACE_CONFIG_CAMERA                                                     \
  Identifier camera_id = Config->cameraDevices.getPropertyName(dev_n) ;                 \
  Trace::TraceConfig("configuring camera " + STRING(Config->cameraDevices[camera_id]) + \
                     " @ "                 + CONFIG::CAMERA_RESOLUTIONS  [res_n]      ) ;

#  define DEBUG_TRACE_CONFIG_AUDIO                                                     \
  String api_name  = CONFIG::AUDIO_APIS[audio_api] ;                                   \
  Trace::TraceConfig("configuring " + api_name + " audio (" + String(plugin_id) + ")") ;

#  define DEBUG_TRACE_CONFIG_TEXT                                                 \
  Trace::TraceConfig("configuring text " + CONFIG::TEXT_STYLES   [text_style_n] + \
                     " overlay @ "       + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define DEBUG_TRACE_CONFIG_MIXER             \
  Trace::TraceConfig("configuring compositor") ;

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
  Trace::TraceConfig("configuring mux "                                                       + \
      String(output_w) + "x" + String(output_h) + " -> "  + String(video_bitrate) + "kbps - " + \
      samplerate       + "bit " + api_name + " audio @ 44100Hz -> " + bitrate     + "kbps"    ) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                                             \
  Trace::TraceConfig("configuring " + stream + " output stream to " + file_url) ;

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
#  define DEBUG_TRACE_CONFIG_MIXER     ;
#  define DEBUG_TRACE_CONFIG_MUX       ;
#  define DEBUG_TRACE_CONFIG_OUTPUT    ;

#endif // DEBUG
#endif  // TRACEAVCASTER_H_INCLUDED
