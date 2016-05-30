/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef _TRACEGSTREAMER_H_
#define _TRACEGSTREAMER_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_GST_INIT_PHASE_1 Trace::TraceState("initializing Gstreamer") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_2 Trace::TraceState("instantiating pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_3 Trace::TraceState("instantiating pipeline bins") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_4 Trace::TraceState("instantiating bin elements") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_5 Trace::TraceState("starting pipeline") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_6 Trace::TraceState("linking bins") ;

#  define DEBUG_TRACE_GST_INIT_PHASE_7 Trace::TraceState("Gstreamer ready") ;

#  define DEBUG_DUMP_MEDIA_SWITCHES                                            \
  if (!is_config_sane || DEBUG_TRACE_MEDIA_VB)                                 \
    Trace::TraceMedia(String("pipeline configuration params =>")             + \
                      "\n\tn_video_inputs="     + String(n_video_inputs    ) + \
                      "\n\tis_media_enabled="   + String(is_media_enabled  ) + \
                      "\n\tis_screen_enabled="  + String(is_screen_enabled ) + \
                      "\n\tis_camera_enabled="  + String(is_camera_enabled ) + \
                      "\n\tis_text_enabled="    + String(is_text_enabled   ) + \
                      "\n\tis_image_enabled="   + String(is_image_enabled  ) + \
                      "\n\tis_vmixer_enabled="  + String(is_vmixer_enabled ) + \
                      "\n\tis_preview_enabled=" + String(is_preview_enabled) + \
                      "\n\tis_audio_enabled="   + String(is_audio_enabled  ) + \
                      "\n\tis_config_sane="     + String(is_config_sane    ) ) ;

#  define DEBUG_TRACE_DISABLED_BINS                                      \
  if (!is_screen_enabled ) Trace::TraceState("ScreencapBin disabled") ;  \
  if (!is_camera_enabled ) Trace::TraceState("CameraBin disabled") ;     \
  if (!is_text_enabled   ) Trace::TraceState("TextBin disabled") ;       \
  if (!is_image_enabled  ) Trace::TraceState("ImageBin disabled") ;      \
  if (!is_vmixer_enabled ) Trace::TraceState("CompositorBin disabled") ; \
  if (!is_preview_enabled) Trace::TraceState("PreviewBin disabled") ;    \
  if (!is_audio_enabled  ) Trace::TraceState("AudioBin disabled")        ;

#  define DEBUG_TRACE_BUILD_SCREENCAP_BIN  Trace::TraceState("instantiating ScreencapBin elements") ;

#  define DEBUG_TRACE_BUILD_CAMERA_BIN     Trace::TraceState("instantiating CameraBin elements") ;

#  define DEBUG_TRACE_BUILD_TEXT_BIN       Trace::TraceState("instantiating TextBin elements") ;

#  define DEBUG_TRACE_BUILD_IMAGE_BIN      Trace::TraceState("instantiating ImageBin elements") ;

#  define DEBUG_TRACE_BUILD_COMPOSITOR_BIN Trace::TraceState("instantiating CompositorBin elements") ;

#  define DEBUG_TRACE_BUILD_PREVIEW_BIN    Trace::TraceState("instantiating PreviewBin elements") ;

#  define DEBUG_TRACE_BUILD_AUDIO_BIN      Trace::TraceState("instantiating AudioBin elements") ;

#  define DEBUG_TRACE_BUILD_MUXER_BIN      Trace::TraceState("instantiating MuxerBin elements") ;

#  define DEBUG_TRACE_BUILD_OUTPUT_BIN     Trace::TraceState("instantiating OutputBin elements") ;

#  define DEBUG_GST_STATE(state)                                          \
    String((state == GST_STATE_VOID_PENDING) ? "GST_STATE_VOID_PENDING" : \
           (state == GST_STATE_NULL        ) ? "GST_STATE_NULL"         : \
           (state == GST_STATE_READY       ) ? "GST_STATE_READY"        : \
           (state == GST_STATE_PAUSED      ) ? "GST_STATE_PAUSED"       : \
           (state == GST_STATE_PLAYING     ) ? "GST_STATE_PLAYING"      : \
                                               "unknown"                )

#  define DEBUG_TRACE_SET_GST_STATE                              \
  String dbg = " '" + GetElementId(an_element) + "' to state " + \
               DEBUG_GST_STATE(next_state)                     ; \
  if (IsInitialized())                                           \
    if (is_err) Trace::TraceError("error setting" + dbg) ;       \
    else        Trace::TraceState("set"           + dbg)         ;


/* bus messages */

#define DEBUG_TRACE_MESSAGE_EOS Trace::TraceMediaVb("GST_MESSAGE_EOS") ;

#define DEBUG_TRACE_MESSAGE_STATE_CHANGED Trace::TraceMediaVb("GST_MESSAGE_STATE_CHANGED") ;

void MessageStructEach(GstMessage* message ,  GstStructureForeachFunc each_fn)
{
  gst_structure_foreach(gst_message_get_structure(message) , each_fn , NULL) ;
}
gboolean DumpMessage(GQuark field_id , const GValue* gvalue , gpointer user_data) // aka GstStructureForeachFunc
{
  gchar* gvalue_str = g_strdup_value_contents(gvalue) ;

  LOG("DumpMessage() gvalue='" + String(gvalue_str) + "'") ;

  g_free(gvalue_str) ;
}
#  define DEBUG_TRACE_DUMP_MESSAGE_STRUCT                            \
  if (DEBUG_TRACE_MEDIA_VB) MessageStructEach(message , DumpMessage) ;

#  define DEBUG_TRACE_MESSAGE_UNHANDLED                                                         \
  Trace::TraceMediaVb("got unhandled message '" + String(GST_MESSAGE_TYPE_NAME(message)) + "'") ;

#  define DEBUG_TRACE_GST_ERROR_MESSAGE                                                     \
  bool   is_audio_error = is_alsa_init_error || is_pulse_init_error || is_jack_init_error ; \
  String is_handled_msg = (is_audio_error) ? "" : " (unhandled)" ;                          \
  Trace::TraceError("GSTError:" + is_handled_msg + " '" + error_message + "'") ;            \
  if (is_audio_error) Trace::TraceMedia("deactivating audio")                               ;


/* configuration */

#  define DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN                                         \
  String plugin_id = (is_active) ? GST::SCREEN_PLUGIN_ID : GST::TESTVIDEO_PLUGIN_ID ; \
  Trace::TraceState("configuring ScreencapBin @ "                         +           \
                    String(screencap_w) + "x" + String(screencap_h)       +           \
                    " @ "                     + String(framerate) + "fps" +           \
                    " using "                 + plugin_id                 )           ;

#  define DEBUG_TRACE_CONFIGURE_CAMERA_BIN                                               \
  String dev_path  = (use_real_src) ? device_path : "testsrc" ;                          \
  String res       = String(resolution.getX()) + "x" + String(resolution.getY()) ;       \
  String fps       = String(framerate) + "fps" ;                                         \
  String plugin_id = (use_real_src) ? GST::CAMERA_PLUGIN_ID : GST::TESTVIDEO_PLUGIN_ID ; \
  Trace::TraceState("configuring CameraBin '" + dev_path  +                              \
                    "' -> "                   + res       +                              \
                    " @ "                     + fps       +                              \
                    " using "                 + plugin_id )                              ;

#  define DEBUG_TRACE_CONFIGURE_TEXT_BIN                                               \
  Trace::TraceState("configuring TextBin " + CONFIG::TextStyles()   [text_style_idx] + \
                    " overlay @ "          + CONFIG::TextPositions()[text_pos_idx  ] ) ;

#  define DEBUG_TRACE_CONFIGURE_IMAGE_BIN                            \
  Trace::TraceState("configuring ImageBin '" + image_filename + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN                                            \
  Trace::TraceState("configuring CompositorBin @ "                    +                   \
                    String(output_w) + "x" + String(output_h)         +                   \
                    " @ "                  + String(framerate) + "fps") ;                 \
  Trace::TraceMedia("configuring compositor sinks screen_z="         + String(screen_z) + \
                                                " camera_z="         + String(camera_z) + \
                                                " image_z="          + String(image_z ) ) ;

#  define DEBUG_TRACE_CONFIGURE_PREVIEW_BIN                                           \
  String plugin_id = (is_active) ? GST::PREVIEW_PLUGIN_ID : GST::FAUXSINK_PLUGIN_ID ; \
  Trace::TraceState("configuring PreviewBin using " + plugin_id)                      ;

#  define DEBUG_TRACE_CONFIGURE_AUDIO_BIN                                                            \
  String bit_depth ; String plugin_id ;                                                              \
  switch ((CONFIG::AudioApi)audio_api_idx)                                                           \
  {                                                                                                  \
    case CONFIG::ALSA_AUDIO_IDX:  bit_depth = "16" ;  plugin_id = GST::ALSA_PLUGIN_ID ;      break ; \
    case CONFIG::PULSE_AUDIO_IDX: bit_depth = "16" ;  plugin_id = GST::PULSE_PLUGIN_ID ;     break ; \
    case CONFIG::JACK_AUDIO_IDX:  bit_depth = "32" ;  plugin_id = GST::JACK_PLUGIN_ID ;      break ; \
    default:                      bit_depth = "16" ;  plugin_id = GST::TESTAUDIO_PLUGIN_ID ; break ; \
  }                                                                                                  \
  Trace::TraceState("configuring AudioBin " + bit_depth    + "bit @ "       +                        \
                    String(samplerate) + "hz x "                            +                        \
                    String(n_channels) + " channels" + " using " + plugin_id) ;                      \
  Trace::TraceMediaVb("configuring AudioCaps with '" + caps_str + "'")                               ;

#  define DEBUG_TRACE_CONFIGURE_MUXER_BIN                                                 \
  Trace::TraceState(String("configuring MuxerBin video - ")                           +   \
      "h264 video -> "     + String(output_w)      + "x"      + String(output_h)      +   \
                 " @ "     + String(video_bitrate) + "kbps - "                        ) ; \
  Trace::TraceState(String("configuring MuxerBin audio - ")                           +   \
      "mp3 audio 16bit @ " + String(samplerate)    + "hz -> " + String(audio_bitrate) +   \
                 "kbps x " + String(n_channels)    + " channels"                      )   ;

#  define DEBUG_TRACE_CONFIGURE_OUTPUT_BIN                                     \
  String plugin_id = (next_sink == OutputFileSink) ? GST::FILESINK_PLUGIN_ID : \
                     (next_sink == OutputRtmpSink) ? GST::RTMPSINK_PLUGIN_ID : \
                     (next_sink == OutputFauxSink) ? GST::FAUXSINK_PLUGIN_ID : \
                                                     String::empty           ; \
  String url       = output_url.upToFirstOccurrenceOf("?" , true  , true) ;    \
  String server    = (next_sink == OutputFauxSink) ? ""                   :    \
                     " => '" + url + ((url.endsWith("?")) ? "...'" : "'") ;    \
  Trace::TraceState("configuring OutputBin using " + plugin_id + server )      ;

#  define DEBUG_TRACE_RECONFIGURE_IN                           \
  String bin = (configure_all    ) ? "Pipeline"     :          \
               (configure_screen ) ? "ScreencapBin" :          \
               (configure_camera ) ? "CameraBin"    :          \
               (configure_text   ) ? "TextBin"      :          \
               (configure_image  ) ? "ImageBin"     :          \
               (configure_preview) ? "PreviewBin"   :          \
               (configure_audio  ) ? "AudioBin"     :          \
               (configure_output ) ? "OutputBin"    : "n/a" ;  \
  String dbg = "reconfiguring " + bin ; Trace::TraceMedia(dbg) ;

#  define DEBUG_TRACE_RECONFIGURE_OUT if (is_error) Trace::TraceError("error " + dbg) ;

#  define DEBUG_TRACE_CONFIGURE_CAPS                                    \
  Trace::TraceMedia("configuring '" + GetElementId(a_capsfilter) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_QUEUE                              \
  Trace::TraceMedia("configuring '" + GetElementId(a_queue) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_SCREEN                                     \
  Trace::TraceMedia("configuring '" + GetElementId(a_screen_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_CAMERA                                     \
  Trace::TraceMedia("configuring '" + GetElementId(a_camera_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_TEST_VIDEO                               \
  Trace::TraceMedia("configuring '" + GetElementId(a_test_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_TEXT                                     \
  Trace::TraceMedia("configuring '" + GetElementId(a_text_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FILE_SOURCE                              \
  Trace::TraceMedia("configuring '" + GetElementId(a_file_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FILE_SINK                              \
  Trace::TraceMedia("configuring '" + GetElementId(a_file_sink) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR                              \
  Trace::TraceMedia("configuring '" + GetElementId(a_compositor) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK                \
  Trace::TraceMedia("configuring '" + GetPadId(sinkpad) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_PREVIEW                                   \
  Trace::TraceMedia("configuring '" + GetElementId(a_video_sink) + "' " + \
                    ((is_active) ? "(active)" : "(inactive)")           + \
                    String(preview_x) + "@" + String(preview_y) + " "   + \
                    String(preview_w) + "x" + String(preview_h)         ) ;

#  define DEBUG_TRACE_CONFIGURE_TEST_AUDIO                               \
  Trace::TraceMedia("configuring '" + GetElementId(a_test_source) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_X264ENC                                    \
  Trace::TraceMedia("configuring '" + GetElementId(an_x264_encoder) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_LAMEENC                                   \
  Trace::TraceMedia("configuring '" + GetElementId(a_lame_encoder) + "'") ;

#  define DEBUG_TRACE_CONFIGURE_FLVMUX                                \
  Trace::TraceMedia("configuring '" + GetElementId(a_flvmuxer) + "'") ;

#  define DEBUG_TRACE_MAKE_ELEMENT                                      \
  bool   is_err = new_element == nullptr ;                              \
  String dbg    = " '" + plugin_id + "' element '" + element_id + "'" ; \
  if (is_err) Trace::TraceError("error creating" + dbg) ;               \
  else        Trace::TraceMedia("created"        + dbg)                 ;

#  define DEBUG_TRACE_MAKE_CAPS                                     \
  if (new_caps == nullptr) Trace::TraceError("error creating caps") ;

#  define DEBUG_TRACE_ADD_ELEMENT                          \
  String dbg = " element '" + GetElementId(an_element)   + \
               "' to '"     + GetElementId(a_bin) + "'"  ; \
  if (is_err) Trace::TraceError("error adding" + dbg) ;    \
  else        Trace::TraceMedia("added"        + dbg)      ;

#  define DEBUG_TRACE_REMOVE_ELEMENT_IN                                         \
  String dbg = " element '"   + GetElementId(an_element) +                      \
               "' from bin '" + GetElementId(a_bin)      + "'" ;                \
  if (!IsInBin(a_bin , an_element)) Trace::TraceWarning("can not remove" + dbg) ;

#  define DEBUG_TRACE_REMOVE_ELEMENT_OUT                    \
  if (is_err) Trace::TraceError("error removing"   + dbg) ; \
  else        Trace::TraceMedia("removed"          + dbg)   ;

#  define DEBUG_TRACE_DESTROY_ELEMENT                                        \
  Trace::TraceMedia("destroying element '" + GetElementId(an_element) + "'") ;

#  define DEBUG_TRACE_ADD_BIN_IN                                                               \
  String dbg = " bin '" + GetElementId(a_bin) + "' to pipeline" ;                              \
  if (IsInPipeline(a_bin)) Trace::TraceWarning("can not add" + dbg + " - already in pipeline") ;

#  define DEBUG_TRACE_ADD_BIN_OUT                       \
  if (is_err) Trace::TraceError("error adding" + dbg) ; \
  else        Trace::TraceMedia("added"        + dbg)   ;

#  define DEBUG_TRACE_REMOVE_BIN_IN                                                            \
  String dbg = " bin '" + GetElementId(a_bin) + "' from pipeline" ;                            \
  if (!IsInPipeline(a_bin)) Trace::TraceWarning("can not remove" + dbg + " - not in pipeline") ;

#  define DEBUG_TRACE_REMOVE_BIN_OUT                      \
  if (is_err) Trace::TraceError("error removing" + dbg) ; \
  else        Trace::TraceMedia("removed"        + dbg)   ;

#  define DEBUG_TRACE_LINK_ELEMENTS                         \
  String dbg = " elements '" + GetElementId(source) +       \
               "' and '"     + GetElementId(sink)   + "'" ; \
  if (is_err) Trace::TraceError("error linking" + dbg) ;    \
  else        Trace::TraceMedia("linked"        + dbg)      ;

#  define DEBUG_TRACE_LINK_PADS                                            \
  GstElement* src_parent    = gst_pad_get_parent_element(srcpad ) ;        \
  GstElement* snk_parent    = gst_pad_get_parent_element(sinkpad) ;        \
  String      src_parent_id = GetElementId(src_parent) ;                   \
  String      snk_parent_id = GetElementId(snk_parent) ;                   \
  gst_object_unref(src_parent) ; gst_object_unref(snk_parent) ;            \
  String dbg = " pads '" + src_parent_id + ":" + GetPadId(srcpad)  +       \
               "' and '" + snk_parent_id + ":" + GetPadId(sinkpad) + "'" ; \
  if (is_err) Trace::TraceError("error linking" + dbg) ;                   \
  else        Trace::TraceMedia("linked"        + dbg)                     ;

#  define DEBUG_TRACE_MAKE_GHOST_PAD                                     \
  String dbg = " ghost pad '" + public_pad_id + "' on '" + template_id + \
               "' of '" + GetElementId(an_element) + "'" ;               \
  if (is_err) Trace::TraceError("error creating" + dbg) ;                \
  else        Trace::TraceMedia("created"        + dbg)                  ;

#  define DEBUG_TRACE_ADD_GHOST_PAD                     \
  String dbg = " ghost pad '" + GetPadId(public_pad) +  \
               "' to '" + GetElementId(a_bin) + "'" ;   \
  if (is_err) Trace::TraceError("error adding" + dbg) ; \
  else        Trace::TraceMedia("added"        + dbg)   ;

#  define DEBUG_TRACE_GET_PAD                              \
  String dbg = pad_avail + " pad '" + template_id        + \
               "' of '" + GetElementId(an_element) + "'" ; \
  if (is_err) Trace::TraceError("error getting " + dbg) ;  \
  else        Trace::TraceMedia("got "           + dbg)    ;
#  define DEBUG_TRACE_GET_STATIC_PAD  String pad_avail = "static " ; DEBUG_TRACE_GET_PAD
#  define DEBUG_TRACE_GET_REQUEST_PAD String pad_avail = "request" ; DEBUG_TRACE_GET_PAD

#  define DEBUG_MAKE_GRAPHVIZ                                                                  \
  String color = (DEBUG_ANSI_COLORS) ? "\033[1;34m" : "" ;                                     \
  String cend  = (DEBUG_ANSI_COLORS) ? "\033[0m"    : "" ;                                     \
  char* graph_name = std::getenv("AVCASTER_GRAPH_NAME") ;                                      \
  Trace::TraceConfig(color +  "creating graph " + String(graph_name) + cend) ;                 \
  GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS(GST_BIN(Pipeline) , GST_DEBUG_GRAPH_SHOW_ALL , graph_name) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_GST_INIT_PHASE_1          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_2          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_3          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_4          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_5          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_6          ;
#  define DEBUG_TRACE_GST_INIT_PHASE_7          ;
#  define DEBUG_DUMP_MEDIA_SWITCHES             ;
#  define DEBUG_TRACE_DISABLED_BINS             ;
#  define DEBUG_TRACE_BUILD_SCREENCAP_BIN       ;
#  define DEBUG_TRACE_BUILD_CAMERA_BIN          ;
#  define DEBUG_TRACE_BUILD_TEXT_BIN            ;
#  define DEBUG_TRACE_BUILD_IMAGE_BIN           ;
#  define DEBUG_TRACE_BUILD_COMPOSITOR_BIN      ;
#  define DEBUG_TRACE_BUILD_PREVIEW_BIN         ;
#  define DEBUG_TRACE_BUILD_AUDIO_BIN           ;
#  define DEBUG_TRACE_BUILD_MUXER_BIN           ;
#  define DEBUG_TRACE_BUILD_OUTPUT_BIN          ;
#  define DEBUG_TRACE_SET_GST_STATE             ;
#  define DEBUG_TRACE_GST_ERROR_MESSAGE         ;
#  define DEBUG_TRACE_UNHANDLED_MESSAGE         ;
#  define DEBUG_TRACE_DUMP_MESSAGE_STRUCT       ;
#  define DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN   ;
#  define DEBUG_TRACE_CONFIGURE_CAMERA_BIN      ;
#  define DEBUG_TRACE_CONFIGURE_TEXT_BIN        ;
#  define DEBUG_TRACE_CONFIGURE_IMAGE_BIN       ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN  ;
#  define DEBUG_TRACE_CONFIGURE_PREVIEW_BIN     ;
#  define DEBUG_TRACE_CONFIGURE_AUDIO_BIN       ;
#  define DEBUG_TRACE_CONFIGURE_MUXER_BIN       ;
#  define DEBUG_TRACE_CONFIGURE_OUTPUT_BIN      ;
#  define DEBUG_TRACE_RECONFIGURE_IN            ;
#  define DEBUG_TRACE_RECONFIGURE_OUT           ;
#  define DEBUG_TRACE_CONFIGURE_CAPS            ;
#  define DEBUG_TRACE_CONFIGURE_QUEUE           ;
#  define DEBUG_TRACE_CONFIGURE_SCREEN          ;
#  define DEBUG_TRACE_CONFIGURE_CAMERA          ;
#  define DEBUG_TRACE_CONFIGURE_TEST_VIDEO      ;
#  define DEBUG_TRACE_CONFIGURE_TEXT            ;
#  define DEBUG_TRACE_CONFIGURE_FILE            ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR      ;
#  define DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK ;
#  define DEBUG_TRACE_CONFIGURE_PREVIEW         ;
#  define DEBUG_TRACE_CONFIGURE_TEST_AUDIO      ;
#  define DEBUG_TRACE_CONFIGURE_X264ENC         ;
#  define DEBUG_TRACE_CONFIGURE_LAMEENC         ;
#  define DEBUG_TRACE_CONFIGURE_FLVMUX          ;
#  define DEBUG_TRACE_MAKE_ELEMENT              ;
#  define DEBUG_TRACE_MAKE_CAPS                 ;
#  define DEBUG_TRACE_ADD_ELEMENT               ;
#  define DEBUG_TRACE_REMOVE_ELEMENT_IN         ;
#  define DEBUG_TRACE_REMOVE_ELEMENT_OUT        ;
#  define DEBUG_TRACE_DESTROY_ELEMENT           ;
#  define DEBUG_TRACE_ADD_BIN_IN                ;
#  define DEBUG_TRACE_ADD_BIN_OUT               ;
#  define DEBUG_TRACE_REMOVE_BIN_IN             ;
#  define DEBUG_TRACE_REMOVE_BIN_OUT            ;
#  define DEBUG_TRACE_LINK_ELEMENTS             ;
#  define DEBUG_TRACE_LINK_PADS                 ;
#  define DEBUG_TRACE_MAKE_GHOST_PAD            ;
#  define DEBUG_TRACE_ADD_GHOST_PAD             ;
#  define DEBUG_TRACE_GET_PAD                   ;
#  define DEBUG_TRACE_GET_STATIC_PAD            ;
#  define DEBUG_TRACE_GET_REQUEST_PAD           ;
#  define DEBUG_MAKE_GRAPHVIZ                   ;

#endif // DEBUG_TRACE
#endif // _TRACEGSTREAMER_H_
