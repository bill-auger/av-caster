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


String GstElementId(GstElement* an_element)
{
  if (!an_element) return "nil" ;

  gchar* id = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ;

  return element_id ;
}

String GstPadId(GstPad* a_pad)
{
  if (!a_pad) return "nil" ;

  gchar* id = gst_pad_get_name(a_pad) ; String pad_id = id ; g_free(id) ;

  return pad_id ;
}


/* state */

#  define DEBUG_TRACE_GST_INIT_PHASE_1 Trace::TraceState("initializing gStreamer") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_2 Trace::TraceState("instantiating pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_3 Trace::TraceState("initializing pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_4 Trace::TraceState("configuring pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_5 Trace::TraceState("starting pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_6 Trace::TraceState("gStreamer ready") ;

#  define DEBUG_GST_STATE(state)                                          \
    String((state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" : \
           (state == GST_STATE_NULL        ) ? "GST_STATE_NULL"         : \
           (state == GST_STATE_READY       ) ? "GST_STATE_READY"        : \
           (state == GST_STATE_PAUSED      ) ? "GST_STATE_PAUSED"       : \
           (state == GST_STATE_PLAYING     ) ? "GST_STATE_PLAYING"      : \
                                               "unknown"                )

#  define DEBUG_TRACE_SET_GST_STATE                              \
  String dbg = " '" + GstElementId(an_element) + "' to state " + \
               DEBUG_GST_STATE(next_state)                     ; \
  if (is_err) Trace::TraceError("error setting" + dbg) ;         \
  else        Trace::TraceState("set"           + dbg)           ;


/* configuration */

#  define DEBUG_TRACE_CONFIGURE_PIPELINE                        \
  if (IsPlaying()) Trace::TraceState("re-configuring pipeline") ;

#  define DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN                         \
  Trace::TraceState("configuring ScreencapBin @ "                   + \
                    String(screencap_w) + "x" + String(screencap_h) + \
                    " using "           + plugin_id                 ) ;

#  define DEBUG_TRACE_CONFIGURE_CAMERA_BIN                          \
  String dev_path = (device_path.isEmpty()) ? "n/a" : device_path ; \
  Trace::TraceState("configuring CameraBin '" + dev_path    +       \
                    "' -> "     + resolution                +       \
                    " @ "       + String(framerate) + "fps" +       \
                    " using "   + plugin_id                 )       ;

#  define DEBUG_TRACE_CONFIGURE_TEXT_BIN                                            \
  Trace::TraceState("configuring TextBin " + CONFIG::TEXT_STYLES   [text_style_n] + \
                    " overlay @ "          + CONFIG::TEXT_POSITIONS[text_pos_n  ] ) ;

#  define DEBUG_TRACE_CONFIGURE_INTERSTITIAL_BIN                            \
  Trace::TraceState("configuring InterstitialBin '" + image_filename + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN                          \
  Trace::TraceState("configuring CompositorBin @ "                    + \
                    String(output_w) + "x" + String(output_h)         + \
                    " @ "                  + String(framerate) + "fps") ;

#  define DEBUG_TRACE_CONFIGURE_PREVIEW_BIN                      \
  Trace::TraceState("configuring PreviewBin using " + plugin_id) ;

#  define DEBUG_TRACE_CONFIGURE_AUDIO_BIN                                          \
  String bit_depth = (plugin_id == GST::ALSA_PLUGIN_ID ) ? "16" :                  \
                     (plugin_id == GST::PULSE_PLUGIN_ID) ? "16" :                  \
                     (plugin_id == GST::JACK_PLUGIN_ID ) ? "32" : "16" ;           \
  Trace::TraceState("configuring AudioBin " + bit_depth + "bit @ "               + \
                    String(samplerate)      + "hz x "                            + \
                    String(n_channels)      + " channels" + " using " + plugin_id) ;

#  define DEBUG_TRACE_CONFIGURE_MUXER_BIN                                               \
  Trace::TraceState(String("configuring MuxerBin - ")                                 + \
      "h264 video -> "     + String(output_w)      + "x"      + String(output_h)      + \
                 " @ "     + String(video_bitrate) + "kbps - "                        + \
      "mp3 audio 16bit @ " + String(samplerate)    + "hz -> " + String(audio_bitrate) + \
                 "kbps x " + String(n_channels)    + " channels"                      ) ;

#  define DEBUG_TRACE_CONFIGURE_OUTPUT_BIN                                    \
  String server = String((is_lctv) ? "LCTV " : "") ;                          \
  Trace::TraceState("configuring " + server + "OutputBin using " + plugin_id) ;

#  define DEBUG_TRACE_RECONFIGURE                                                        \
  String value = "'"  + STRING(ConfigStore[config_key]) + "'" ;                          \
  Trace::TraceMedia("reconfiguring pipeline - '" + String(config_key) + "' => " + value) ;

#  define DEBUG_TRACE_MAKE_ELEMENT                                      \
  bool   is_err = new_element == nullptr ;                              \
  String dbg    = " '" + plugin_id + "' element '" + element_id + "'" ; \
  if (is_err) Trace::TraceError("error creating" + dbg) ;               \
  else        Trace::TraceMedia("created"        + dbg)                 ;

#  define DEBUG_TRACE_MAKE_CAPS                          \
  bool   is_err = new_caps == nullptr ;                  \
  if (is_err) Trace::TraceError("error creating caps") ; \
  else        Trace::TraceMedia("created caps"      )    ;

#  define DEBUG_TRACE_ADD_ELEMENT                          \
  String dbg = " element '" + GstElementId(an_element)   + \
               "' to '"     + GstElementId(a_bin) + "'"  ; \
  if (is_err) Trace::TraceError("error adding" + dbg) ;    \
  else        Trace::TraceMedia("added"        + dbg)      ;

#  define DEBUG_FILTER_BINS                                                                       \
  String binid         = GstElementId(a_bin) ;                                                    \
  bool   should_bypass = ((!CONFIGURE_TEXT_BIN         && binid == GST::TEXT_BIN_ID        ) ||   \
                          (!CONFIGURE_INTERSTITIAL_BIN && binid == GST::INTERSTITIAL_BIN_ID)  ) ; \
  if (should_bypass) return true ;

#  define DEBUG_TRACE_ADD_BIN                                     \
  String dbg = " bin '" + GstElementId(a_bin) + "' to Pipeline" ; \
  if (is_err) Trace::TraceError("error adding" + dbg) ;           \
  else        Trace::TraceMedia("added"        + dbg)             ;

#  define DEBUG_TRACE_REMOVE_BIN_IN                               \
  String dbg = " bin '" + GstElementId(a_bin) + "' from Pipeline" ;

#  define DEBUG_TRACE_REMOVE_BIN_OUT                      \
  if (is_err) Trace::TraceError("error removing" + dbg) ; \
  else        Trace::TraceMedia("removed"        + dbg)   ;

#  define DEBUG_TRACE_RECREATE_BIN_IN Trace::TraceMedia("re-creating '" + bin_id + "'") ;

#  define DEBUG_TRACE_RECREATE_BIN_OUT                                                  \
  if (!IsInPipeline(new_bin)) Trace::TraceError("error re-creating '" + bin_id + "'") ; \
  else                        Trace::TraceMedia("re-created '"        + bin_id + "'")   ;

#  define DEBUG_TRACE_LINK_ELEMENTS                         \
  String dbg = " elements '" + GstElementId(source) +       \
               "' and '"     + GstElementId(sink)   + "'" ; \
  if (is_err) Trace::TraceError("error linking" + dbg) ;    \
  else        Trace::TraceMedia("linked"        + dbg)      ;

#  define DEBUG_TRACE_LINK_PADS                                            \
  GstElement* src_parent    = gst_pad_get_parent_element(srcpad ) ;        \
  GstElement* snk_parent    = gst_pad_get_parent_element(sinkpad) ;        \
  String      src_parent_id = GstElementId(src_parent) ;                   \
  String      snk_parent_id = GstElementId(snk_parent) ;                   \
  gst_object_unref(src_parent) ; gst_object_unref(snk_parent) ;            \
  String dbg = " pads '" + src_parent_id + ":" + GstPadId(srcpad)  +       \
               "' and '" + snk_parent_id + ":" + GstPadId(sinkpad) + "'" ; \
  if (is_err) Trace::TraceError("error linking" + dbg) ;                   \
  else        Trace::TraceMedia("linked"        + dbg)                     ;

#  define DEBUG_TRACE_MAKE_GHOST_PAD                                     \
  String dbg = " ghost pad '" + public_pad_id + "' on '" + template_id + \
               "' of '" + GstElementId(an_element) + "'" ;               \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                \
  else        Trace::TraceMedia("created"        + dbg)                  ;

#  define DEBUG_TRACE_ADD_GHOST_PAD                     \
  String dbg = " ghost pad '" + GstPadId(public_pad) +  \
               "' to '" + GstElementId(a_bin) + "'" ;   \
  if (is_err) Trace::TraceError("error adding" + dbg) ; \
  else        Trace::TraceMedia("added"        + dbg)   ;

#  define DEBUG_TRACE_GET_PAD                              \
  String dbg = pad_avail + " pad '" + template_id        + \
               "' of '" + GstElementId(an_element) + "'" ; \
  if (is_err) Trace::TraceError("error getting " + dbg) ;  \
  else        Trace::TraceMedia("got "           + dbg)    ;
#  define DEBUG_TRACE_GET_STATIC_PAD  String pad_avail = "static " ; DEBUG_TRACE_GET_PAD
#  define DEBUG_TRACE_GET_REQUEST_PAD String pad_avail = "request" ; DEBUG_TRACE_GET_PAD

#  define DEBUG_TRACE_CONFIGURE_CAPS                                    \
  Trace::TraceMedia("configuring '" + GstElementId(a_capsfilter) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_QUEUE                              \
  Trace::TraceMedia("configuring '" + GstElementId(a_queue) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_SCREEN                                     \
  Trace::TraceMedia("configuring '" + GstElementId(a_screen_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_CAMERA                                     \
  Trace::TraceMedia("configuring '" + GstElementId(a_camera_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FAUX_VIDEO                               \
  Trace::TraceMedia("configuring '" + GstElementId(a_faux_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_TEXT                                     \
  Trace::TraceMedia("configuring '" + GstElementId(a_text_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FILE                                     \
  Trace::TraceMedia("configuring '" + GstElementId(a_file_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR                              \
  Trace::TraceMedia("configuring '" + GstElementId(a_compositor) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK                \
  Trace::TraceMedia("configuring '" + GstPadId(sinkpad) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_PREVIEW                                \
  Trace::TraceMedia("configuring '" + GstElementId(PreviewSink) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FAUX_AUDIO                               \
  Trace::TraceMedia("configuring '" + GstElementId(a_faux_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_X264ENC                                    \
  Trace::TraceMedia("configuring '" + GstElementId(an_x264_encoder) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_LAMEENC                                   \
  Trace::TraceMedia("configuring '" + GstElementId(a_lame_encoder) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FLVMUX                                \
  Trace::TraceMedia("configuring '" + GstElementId(a_flvmuxer) + "'") ;

#  define DEBUG_MAKE_GRAPHVIZ                                                                  \
  String color = (DEBUG_ANSI_COLORS) ? "\033[1;34m" : "" ;                                     \
  String cend  = (DEBUG_ANSI_COLORS) ? "\033[0m"    : "" ;                                     \
  char* graph_name = std::getenv("AVCASTER_GRAPH_NAME") ;                                      \
  Trace::TraceConfig(color +  "creating graph " + String(graph_name) + cend) ;                 \
  GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS(GST_BIN(Pipeline) , GST_DEBUG_GRAPH_SHOW_ALL , graph_name) ;

#else // DEBUG

#  define DEBUG_TRACE_GST_INIT_PHASE_1           ;
#  define DEBUG_TRACE_GST_INIT_PHASE_2           ;
#  define DEBUG_TRACE_GST_INIT_PHASE_3           ;
#  define DEBUG_TRACE_GST_INIT_PHASE_4           ;
#  define DEBUG_TRACE_GST_INIT_PHASE_5           ;
#  define DEBUG_TRACE_GST_INIT_PHASE_6           ;
#  define DEBUG_TRACE_SET_GST_STATE              ;
#  define DEBUG_TRACE_CONFIGURE_PIPELINE         ;
#  define DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN    ;
#  define DEBUG_TRACE_CONFIGURE_CAMERA_BIN       ;
#  define DEBUG_TRACE_CONFIGURE_TEXT_BIN         ;
#  define DEBUG_TRACE_CONFIGURE_INTERSTITIAL_BIN ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN   ;
#  define DEBUG_TRACE_CONFIGURE_PREVIEW_BIN      ;
#  define DEBUG_TRACE_CONFIGURE_AUDIO_BIN        ;
#  define DEBUG_TRACE_CONFIGURE_MUXER_BIN        ;
#  define DEBUG_TRACE_CONFIGURE_OUTPUT_BIN       ;
#  define DEBUG_TRACE_RECONFIGURE                ;
#  define DEBUG_TRACE_MAKE_ELEMENT               ;
#  define DEBUG_TRACE_MAKE_CAPS                  ;
#  define DEBUG_TRACE_ADD_ELEMENT                ;
#  define DEBUG_FILTER_BINS                      ;
#  define DEBUG_TRACE_ADD_BIN                    ;
#  define DEBUG_TRACE_REMOVE_BIN_IN              ;
#  define DEBUG_TRACE_REMOVE_BIN_OUT             ;
#  define DEBUG_TRACE_RECREATE_BIN_IN            ;
#  define DEBUG_TRACE_RECREATE_BIN_OUT           ;
#  define DEBUG_TRACE_LINK_ELEMENTS              ;
#  define DEBUG_TRACE_LINK_PADS                  ;
#  define DEBUG_TRACE_MAKE_GHOST_PAD             ;
#  define DEBUG_TRACE_ADD_GHOST_PAD              ;
#  define DEBUG_TRACE_GET_PAD                    ;
#  define DEBUG_TRACE_GET_STATIC_PAD             ;
#  define DEBUG_TRACE_GET_REQUEST_PAD            ;
#  define DEBUG_TRACE_CONFIGURE_CAPS             ;
#  define DEBUG_TRACE_CONFIGURE_QUEUE            ;
#  define DEBUG_TRACE_CONFIGURE_SCREEN           ;
#  define DEBUG_TRACE_CONFIGURE_CAMERA           ;
#  define DEBUG_TRACE_CONFIGURE_FAUX_VIDEO       ;
#  define DEBUG_TRACE_CONFIGURE_TEXT             ;
#  define DEBUG_TRACE_CONFIGURE_FILE             ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR       ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK  ;
#  define DEBUG_TRACE_CONFIGURE_PREVIEW          ;
#  define DEBUG_TRACE_CONFIGURE_FAUX_AUDIO       ;
#  define DEBUG_TRACE_CONFIGURE_X264ENC          ;
#  define DEBUG_TRACE_CONFIGURE_LAMEENC          ;
#  define DEBUG_TRACE_CONFIGURE_FLVMUX           ;
#  define DEBUG_MAKE_GRAPHVIZ                    ;

#endif // DEBUG
#endif // TRACEGSTREAMER_H_INCLUDED
