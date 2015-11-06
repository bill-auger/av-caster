/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef TRACEGSTREAMER_H_INCLUDED
#define TRACEGSTREAMER_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_GST_INIT_PHASE_1 Trace::TraceState("instantiating pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_2 Trace::TraceState("initializing pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_3 Trace::TraceState("configuring pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_4 Trace::TraceState("starting pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_5 Trace::TraceState("Gstreamer ready") ;

#  define DEBUG_TRACE_SET_GST_STATE                                                              \
  String element_name = (!!an_element) ? String(gst_element_get_name(an_element)) : "" ;         \
  String state = (next_state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" :             \
                 (next_state == GST_STATE_NULL        ) ? "GST_STATE_NULL"         :             \
                 (next_state == GST_STATE_READY       ) ? "GST_STATE_READY"        :             \
                 (next_state == GST_STATE_PAUSED      ) ? "GST_STATE_PAUSED"       :             \
                 (next_state == GST_STATE_PLAYING     ) ? "GST_STATE_PLAYING"      : "unknown" ; \
  String dbg = " '" + element_name + "' to state " + state ;                                     \
  if (is_err) Trace::TraceError("error setting" + dbg) ;                                         \
  else        Trace::TraceConfig("set"          + dbg) ;


/* configuration */

#  define DEBUG_TRACE_CONFIGURE_PIPELINE                        \
  if (IsPlaying()) Trace::TraceState("re-configuring pipeline") ;

#  define DEBUG_TRACE_CONFIG_SCREENCAP                                \
  Trace::TraceState("configuring screencap @ "                      + \
                    String(screencap_w) + "x" + String(screencap_h) + \
                    " using "           + plugin_id                 ) ;

#  define DEBUG_TRACE_CONFIG_CAMERA                                 \
  String dev_path = (device_path.isEmpty()) ? "n/a" : device_path ; \
  Trace::TraceState("configuring camera '" + dev_path       +       \
                    "' -> "     + resolution                +       \
                    " @ "       + String(framerate) + "fps" +       \
                    " using "   + plugin_id                 )       ;

#  define DEBUG_TRACE_CONFIG_TEXT                                                \
  Trace::TraceState("configuring text " + CONFIG::TEXT_STYLES   [text_style_n] + \
                    " overlay @ "       + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define DEBUG_TRACE_CONFIG_INTERSTITIAL                                \
  Trace::TraceState("configuring interstitial '" + image_filename + "'") ;

#  define DEBUG_TRACE_CONFIG_COMPOSITOR                                 \
  Trace::TraceState("configuring compositor @ "                       + \
                    String(output_w) + "x" + String(output_h)         + \
                    " @ "                  + String(framerate) + "fps") ;

#  define DEBUG_TRACE_CONFIG_PREVIEW                          \
  Trace::TraceState("configuring preview using " + plugin_id) ;

#  define DEBUG_TRACE_CONFIG_AUDIO                                              \
  String bit_depth = (plugin_id == GST::ALSA_PLUGIN_ID ) ? "16" :               \
                     (plugin_id == GST::PULSE_PLUGIN_ID) ? "16" :               \
                     (plugin_id == GST::JACK_PLUGIN_ID ) ? "32" : "16" ;        \
  Trace::TraceState("configuring audio " + bit_depth + "bit @ "               + \
                    String(samplerate)   + "hz x "                            + \
                    String(n_channels)   + " channels" + " using " + plugin_id) ;

#  define DEBUG_TRACE_CONFIG_FLVMUX                                                     \
  Trace::TraceState(String("configuring flvmux - ")                                   + \
      "h264 video -> "     + String(output_w)      + "x"      + String(output_h)      + \
                 " @ "     + String(video_bitrate) + "kbps - "                        + \
      "mp3 audio 16bit @ " + String(samplerate)    + "hz -> " + String(audio_bitrate) + \
                 "kbps x " + String(n_channels)    + " channels"                      ) ;

#  define DEBUG_TRACE_CONFIG_OUTPUT                                               \
  String server = String((is_lctv) ? "LCTV " : "") ;                              \
  Trace::TraceState("configuring " + server + "output stream using " + plugin_id) ;

#  define DEBUG_TRACE_RECONFIGURE_BIN                                                     \
  String is_on = (bool(ConfigStore[config_key])) ? "on" : "off" ;                         \
  Trace::TraceConfig("reconfiguring pipeline - '" + String(config_key) + "' is " + is_on) ;

#  define DEBUG_TRACE_MAKE_ELEMENT                                                 \
  bool   is_err = new_element == nullptr ;                                         \
  String dbg    = " element '" + plugin_id + "' GstElement '" + element_id + "'" ; \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                          \
  else        Trace::TraceConfig("created" + dbg) ;

#  define DEBUG_TRACE_MAKE_CAPS                          \
  bool   is_err = new_caps == nullptr ;                  \
  if (is_err) Trace::TraceError("error creating caps") ; \
  else        Trace::TraceConfig("created caps") ;

#  define DEBUG_TRACE_ADD_ELEMENT                                                       \
  gchar* id  = gst_element_get_name(a_bin     ) ; String bin_id     = id ; g_free(id) ; \
  id         = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ; \
  String dbg = " element '" + element_id + "' to '" + bin_id + "'" ;                    \
  if (is_err) Trace::TraceError("error adding" + dbg) ;                                 \
  else        Trace::TraceConfig("added" + dbg) ;

#  define DEBUG_FILTER_BINS                                                                     \
  gchar* name = gst_element_get_name(a_bin) ; String binid = String(name) ;                     \
  bool should_bypass = ((!CONFIGURE_TEXT_BIN         && binid == GST::TEXT_BIN_ID        ) ||   \
                        (!CONFIGURE_INTERSTITIAL_BIN && binid == GST::INTERSTITIAL_BIN_ID)  ) ; \
  g_free(name) ; if (should_bypass) return true ;

#  define DEBUG_TRACE_ADD_BIN                                                  \
  gchar* id  = gst_element_get_name(a_bin) ; String bin_id = id ; g_free(id) ; \
  String dbg = " bin '" + bin_id + "' to Pipeline" ;                           \
  if (is_err) Trace::TraceError("error adding" + dbg) ;                        \
  else        Trace::TraceConfig("added" + dbg) ;

#  define DEBUG_TRACE_REMOVE_BIN_IN                                            \
  gchar* id  = gst_element_get_name(a_bin) ; String bin_id = id ; g_free(id) ; \
  String dbg = " bin '" + bin_id + "' from Pipeline"                           ;

#  define DEBUG_TRACE_REMOVE_BIN_OUT                      \
  if (is_err) Trace::TraceError("error removing" + dbg) ; \
  else        Trace::TraceConfig("removed" + dbg)         ;

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
  String color = (DEBUG_ANSI_COLORS) ? "\033[1;32m" : "" ;                             \
  char* graph_name = std::getenv("AVCASTER_GRAPH_NAME") ;                              \
  Trace::TraceConfig(color +  "creating graph " + String(graph_name)) ;                \
  GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(Pipeline) , GST_DEBUG_GRAPH_SHOW_ALL , graph_name) ;

#else // DEBUG

#  define DEBUG_TRACE_GST_INIT_PHASE_1   ;
#  define DEBUG_TRACE_GST_INIT_PHASE_2   ;
#  define DEBUG_TRACE_GST_INIT_PHASE_3   ;
#  define DEBUG_TRACE_GST_INIT_PHASE_4   ;
#  define DEBUG_TRACE_GST_INIT_PHASE_5   ;
#  define DEBUG_TRACE_GST_INIT_PHASE_6   ;
#  define DEBUG_TRACE_SET_GST_STATE      ;
#  define DEBUG_TRACE_CONFIGURE_PIPELINE ;
#  define DEBUG_TRACE_CONFIG_SCREENCAP   ;
#  define DEBUG_TRACE_CONFIG_CAMERA      ;
#  define DEBUG_TRACE_CONFIG_TEXT        ;
#  define DEBUG_TRACE_CONFIG_COMPOSITOR  ;
#  define DEBUG_TRACE_CONFIG_PREVIEW     ;
#  define DEBUG_TRACE_CONFIG_AUDIO       ;
#  define DEBUG_TRACE_CONFIG_FLVMUX      ;
#  define DEBUG_TRACE_CONFIG_OUTPUT      ;
#  define DEBUG_TRACE_RECONFIGURE_BIN    ;
#  define DEBUG_TRACE_MAKE_ELEMENT       ;
#  define DEBUG_TRACE_MAKE_CAPS          ;
#  define DEBUG_TRACE_ADD_ELEMENT        ;
#  define DEBUG_FILTER_BINS              ;
#  define DEBUG_TRACE_ADD_BIN            ;
#  define DEBUG_TRACE_REMOVE_BIN_IN      ;
#  define DEBUG_TRACE_REMOVE_BIN_OUT     ;
#  define DEBUG_TRACE_LINK_ELEMENTS      ;
#  define DEBUG_TRACE_LINK_PADS          ;
#  define DEBUG_TRACE_MAKE_GHOST_PAD     ;
#  define DEBUG_TRACE_ADD_GHOST_PAD      ;
#  define DEBUG_TRACE_GET_PAD            ;
#  define DEBUG_TRACE_GET_STATIC_PAD     ;
#  define DEBUG_TRACE_GET_REQUEST_PAD    ;
#  define DEBUG_MAKE_GRAPHVIZ            ;

#endif // DEBUG
#endif // TRACEGSTREAMER_H_INCLUDED
