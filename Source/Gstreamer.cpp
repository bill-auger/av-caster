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


#include <cstdlib>
#include <gst/video/videooverlay.h>
#include <gst/video/gstvideosink.h>

#include "AvCaster.h"
#include "Gstreamer.h"
#include "Trace/TraceGstreamer.h"


/* GstElement private class variables */

GstElement* Gstreamer::Pipeline         = nullptr ;
GstElement* Gstreamer::ScreencapBin     = nullptr ;
GstElement* Gstreamer::ScreenRealSource = nullptr ;
GstElement* Gstreamer::ScreenFauxSource = nullptr ;
GstElement* Gstreamer::ScreenCaps       = nullptr ;
GstElement* Gstreamer::CameraBin        = nullptr ;
GstElement* Gstreamer::CameraRealSource = nullptr ;
GstElement* Gstreamer::CameraFauxSource = nullptr ;
GstElement* Gstreamer::CameraCaps       = nullptr ;
GstElement* Gstreamer::TextBin          = nullptr ;
GstElement* Gstreamer::ImageBin         = nullptr ;
GstElement* Gstreamer::CompositorBin    = nullptr ;
GstElement* Gstreamer::PreviewBin       = nullptr ;
GstElement* Gstreamer::PreviewQueue     = nullptr ;
GstElement* Gstreamer::PreviewFauxSink  = nullptr ;
GstElement* Gstreamer::PreviewRealSink  = nullptr ;
GstElement* Gstreamer::AudioBin         = nullptr ;
GstElement* Gstreamer::AudioAlsaSource  = nullptr ;
GstElement* Gstreamer::AudioPulseSource = nullptr ;
GstElement* Gstreamer::AudioJackSource  = nullptr ;
GstElement* Gstreamer::AudioTestSource  = nullptr ;
GstElement* Gstreamer::AudioCaps        = nullptr ;
GstElement* Gstreamer::MuxerBin         = nullptr ;
GstElement* Gstreamer::OutputBin        = nullptr ;
guintptr    Gstreamer::PreviewXwin      = 0    ;               // Initialize()
ValueTree   Gstreamer::ConfigStore      = ValueTree::invalid ; // Configure()


/* GstElement private class methods */

bool Gstreamer::Initialize(void* x_window_handle)
{
  PreviewXwin = (guintptr)x_window_handle ;

  // determine static pipeline macro configuration
  // TODO: ideally it should be robust to always build all bins
  //       eliminating all Is*Enabled() getters - their vars merely to override Is*Active() getters
  //       but also perhaps it is more efficient to simply not build unused bins
  //       (ASSERT: the 'link bins' section below and Shutdown() reflect the current implementation)
  bool should_build_pipeline       = AvCaster::GetIsMediaEnabled() ;
  bool should_build_screen_bin     = AvCaster::GetIsScreenEnabled() ;
  bool should_build_camera_bin     = AvCaster::GetIsCameraEnabled() ;
  bool should_build_text_bin       = AvCaster::GetIsTextEnabled() ;
  bool should_build_image_bin      = AvCaster::GetIsImageEnabled() ;
  bool should_build_compositor_bin = AvCaster::GetIsCompositorEnabled() ;
  bool should_build_preview_bin    = AvCaster::GetIsPreviewEnabled() ;
  bool should_build_audio_bin      = AvCaster::GetIsAudioEnabled() ;
  bool should_build_muxer_bin      = should_build_pipeline ;
  bool should_build_output_bin     = should_build_pipeline ;

DEBUG_TRACE_GST_INIT_PHASE_1

  // initialize gStreamer (NOTE: this will terminate the app on failure)
  gst_init(nullptr , nullptr) ;

DEBUG_TRACE_GST_INIT_PHASE_2

  // instantiate pipeline
  if ((should_build_pipeline       && !(Pipeline      = NewPipeline(GST::PIPELINE_ID      ))) ||
      (should_build_screen_bin     && !(ScreencapBin  = NewBin     (GST::SCREENCAP_BIN_ID ))) ||
      (should_build_camera_bin     && !(CameraBin     = NewBin     (GST::CAMERA_BIN_ID    ))) ||
      (should_build_text_bin       && !(TextBin       = NewBin     (GST::TEXT_BIN_ID      ))) ||
      (should_build_image_bin      && !(ImageBin      = NewBin     (GST::IMAGE_BIN_ID     ))) ||
      (should_build_compositor_bin && !(CompositorBin = NewBin     (GST::COMPOSITOR_BIN_ID))) ||
      (should_build_preview_bin    && !(PreviewBin    = NewBin     (GST::PREVIEW_BIN_ID   ))) ||
      (should_build_audio_bin      && !(AudioBin      = NewBin     (GST::AUDIO_BIN_ID     ))) ||
      (should_build_muxer_bin      && !(MuxerBin      = NewBin     (GST::MUXER_BIN_ID     ))) ||
      (should_build_output_bin     && !(OutputBin     = NewBin     (GST::OUTPUT_BIN_ID    )))  )
  { AvCaster::Error(GUI::GST_PIPELINE_INST_ERROR_MSG) ; return false ; }

  SetMessageHandler(GST_PIPELINE(Pipeline) , (GstBusSyncHandler)HandleMessage) ;

DEBUG_TRACE_GST_INIT_PHASE_3

  // configure pipeline
  if ((should_build_screen_bin     && !AddBin(ScreencapBin )) ||
      (should_build_camera_bin     && !AddBin(CameraBin    )) ||
      (should_build_text_bin       && !AddBin(TextBin      )) ||
      (should_build_image_bin      && !AddBin(ImageBin     )) ||
      (should_build_compositor_bin && !AddBin(CompositorBin)) ||
      (should_build_preview_bin    && !AddBin(PreviewBin   )) ||
      (should_build_audio_bin      && !AddBin(AudioBin     )) ||
      (should_build_muxer_bin      && !AddBin(MuxerBin     )) ||
      (should_build_output_bin     && !AddBin(OutputBin    ))  )
  { AvCaster::Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_4 DEBUG_TRACE_DISABLED_BINS

  // configure bins
  ReloadConfig() ;
  if ((should_build_screen_bin     && !BuildScreencapBin ()) ||
      (should_build_camera_bin     && !BuildCameraBin    ()) ||
      (should_build_text_bin       && !BuildTextBin      ()) ||
      (should_build_image_bin      && !BuildImageBin     ()) ||
      (should_build_compositor_bin && !BuildCompositorBin()) ||
      (should_build_preview_bin    && !BuildPreviewBin   ()) ||
      (should_build_audio_bin      && !BuildAudioBin     ()) ||
      (should_build_muxer_bin      && !BuildMuxerBin     ()) ||
      (should_build_output_bin     && !BuildOutputBin    ())  )
  { AvCaster::Error(GUI::GST_PIPELINE_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_5

  // link bins
  if (should_build_compositor_bin)
  {
    if ((should_build_screen_bin                   &&
        !LinkElements(ScreencapBin  , CompositorBin)) ||
        (should_build_camera_bin                   &&
        !LinkElements(CameraBin     , CompositorBin)) ||
//         !LinkElements(TextBin   , CompositorBin) ||
//         !LinkElements  (ImageBin   , CompositorBin  ) ||
        !LinkElements(CompositorBin , MuxerBin     )  ||
        (should_build_preview_bin                  &&
        !LinkElements(CompositorBin , PreviewBin   ))  )
    { AvCaster::Error(GUI::MIXER_BIN_LINK_ERROR_MSG) ; return false ; }
  }
  else
  {
    if ((should_build_screen_bin && !LinkElements(ScreencapBin , MuxerBin)) ||
        (should_build_camera_bin && !LinkElements(CameraBin    , MuxerBin)) ||
        (should_build_text_bin   && !LinkElements(TextBin      , MuxerBin)) ||
        (should_build_image_bin  && !LinkElements(ImageBin     , MuxerBin))  )
    { AvCaster::Error(GUI::MIXER_BIN_LINK_ERROR_MSG) ; return false ; }
  }
  if ((should_build_audio_bin           &&
      !LinkElements(AudioBin , MuxerBin )) ||
      !LinkElements(MuxerBin , OutputBin)   )
  { AvCaster::Error(GUI::MUXER_BIN_LINK_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_6

  // set rolling
  if (!SetState(Pipeline , GST_STATE_PLAYING)) return false ;

DEBUG_TRACE_GST_INIT_PHASE_7
// DEBUG_MAKE_GRAPHVIZ

  return true ;
}

void Gstreamer::ReloadConfig() { ConfigStore = AvCaster::GetConfigStore() ; }

void Gstreamer::Shutdown()
{
// DEBUG_MAKE_GRAPHVIZ

  // TODO: to shut down correctly (flushing the buffers)
  //       gst_element_send_event(Pipeline , gst_event_eos()) ;
  //       then wait for EOS message on bus before setting pipeline state to NULL
// FIXME: setting (ScreencapBin to state null here causes X to throw error:
//          "ERROR: X returned BadShmSeg (invalid shared segment parameter) for operation Unknown"

/* TODO: see note in Initialize() regarding static pipeline macro configuration
  if (!IsInPipeline(OutputBin)    ) SetState(OutputBin     , GST_STATE_NULL) ;
  if (!IsInPipeline(MuxerBin)     ) SetState(MuxerBin      , GST_STATE_NULL) ;
  if (!IsInPipeline(AudioBin)     ) SetState(AudioBin      , GST_STATE_NULL) ;
  if (!IsInPipeline(PreviewBin)   ) SetState(PreviewBin    , GST_STATE_NULL) ;
  if (!IsInPipeline(CompositorBin)) SetState(CompositorBin , GST_STATE_NULL) ;
  if (!IsInPipeline(ImageBin)     ) SetState(ImageBin      , GST_STATE_NULL) ;
  if (!IsInPipeline(TextBin)      ) SetState(TextBin       , GST_STATE_NULL) ;
  if (!IsInPipeline(CameraBin)    ) SetState(CameraBin     , GST_STATE_NULL) ;
  if (!IsInPipeline(ScreencapBin) ) SetState(ScreencapBin  , GST_STATE_NULL) ;
*/

  SetState(ScreenRealSource , GST_STATE_NULL) ;
  SetState(ScreenFauxSource , GST_STATE_NULL) ;
  SetState(PreviewRealSink  , GST_STATE_NULL) ;
  SetState(PreviewFauxSink  , GST_STATE_NULL) ;
  SetState(AudioAlsaSource  , GST_STATE_NULL) ;
  SetState(AudioPulseSource , GST_STATE_NULL) ;
  SetState(AudioJackSource  , GST_STATE_NULL) ;
  SetState(AudioTestSource  , GST_STATE_NULL) ;
  DestroyElement(Pipeline) ;

  ConfigStore = ValueTree::invalid ;
}

bool Gstreamer::BuildScreencapBin()
{
DEBUG_TRACE_BUILD_SCREENCAP_BIN

  GstElement *source , *converter , *queue ;

  // instantiate elements
  if (!(ScreenRealSource = NewElement(GST::SCREEN_PLUGIN_ID    , "screen-real-source")) ||
      !(ScreenFauxSource = NewElement(GST::TESTVIDEO_PLUGIN_ID , "screen-faux-source")) ||
      !(ScreenCaps       = NewElement("capsfilter"             , "screen-capsfilter" )) ||
      !(converter        = NewElement("videoconvert"           , "screen-converter"  )) ||
      !(queue            = NewElement("queue"                  , "screen-queue"      ))  )
  { AvCaster::Error(GUI::SCREENCAP_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  source = ConfigureScreen() ;
  ConfigureQueue(queue , 0 , 0 , 0) ;

  // link elements
  if (!AddElement    (ScreencapBin , source    )            ||
      !AddElement    (ScreencapBin , ScreenCaps)            ||
      !AddElement    (ScreencapBin , converter )            ||
      !AddElement    (ScreencapBin , queue     )            ||
      !LinkElements  (source     , ScreenCaps)              ||
      !LinkElements  (ScreenCaps , converter )              ||
      !LinkElements  (converter  , queue     )              ||
      !NewGhostSrcPad(ScreencapBin , queue , "screen-source"))
  { AvCaster::Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildCameraBin()
{
DEBUG_TRACE_BUILD_CAMERA_BIN

  GstElement *source , *converter , *queue ;

  // instantiate elements
  if (!(CameraRealSource = NewElement(GST::CAMERA_PLUGIN_ID    , "camera-real-source")) ||
      !(CameraFauxSource = NewElement(GST::TESTVIDEO_PLUGIN_ID , "camera-faux-source")) ||
      !(CameraCaps       = NewElement("capsfilter"   , "camera-capsfilter"           )) ||
      !(converter        = NewElement("videoconvert" , "camera-converter"            )) ||
      !(queue            = NewElement("queue"        , "camera-queue"                ))  )
  { AvCaster::Error(GUI::CAMERA_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  source = ConfigureCamera() ;

  // link elements
  if (!AddElement    (CameraBin , source    )            ||
      !AddElement    (CameraBin , CameraCaps)            ||
      !AddElement    (CameraBin , converter )            ||
      !AddElement    (CameraBin , queue     )            ||
      !LinkElements  (source     , CameraCaps)           ||
      !LinkElements  (CameraCaps , converter )           ||
      !LinkElements  (converter  , queue     )           ||
      !NewGhostSrcPad(CameraBin , queue , "camera-source"))
  { AvCaster::Error(GUI::CAMERA_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildTextBin()
{
DEBUG_TRACE_BUILD_TEXT_BIN

  GstElement *filesrc , *subparser , *source , *converter , *queue ;

  bool   is_enabled   = bool  (ConfigStore[CONFIG::IS_TEXT_ACTIVE_ID]) ;
  String motd_text    = STRING(ConfigStore[CONFIG::MOTD_TEXT_ID     ]) ;
  int    text_style_n = int   (ConfigStore[CONFIG::TEXT_STYLE_ID    ]) ;
  int    text_pos_n   = int   (ConfigStore[CONFIG::TEXT_POSITION_ID ]) ;

/* TODO: include custom font
#include <fontconfig/fontconfig.h>
std::string yourFontFilePath = "/home/testUser/bla.ttf"
const FcChar8 * file = (const FcChar8 *)yourFontFilePath.c_str();
FcBool fontAddStatus = FcConfigAppFOntAddFile(FcConfigGetCurrent(),file);
*/

  // instantiate elements
// TODO: text from storage
  if (!(filesrc   = gst_element_factory_make("filesrc"      , "text-filesrc"  )) ||
      !(subparser = gst_element_factory_make("subparse"     , "text-subparser")) ||
      !(source    = gst_element_factory_make("textrender"   , "text-input"    )) ||
      !(converter = gst_element_factory_make("videoconvert" , "text-converter")) ||
      !(queue     = gst_element_factory_make("queue"        , "text-queue"    ))  )
  { AvCaster::Error(GUI::TEXT_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_TEXT_BIN

  // configure elements
  ConfigureTextSource(source  , "Purisa Normal 40"            ) ;
  ConfigureFileSource(filesrc , "/code/av-caster/deleteme.srt") ;

  // link elements
  if (!AddElement    (TextBin , filesrc  )           ||
      !AddElement    (TextBin , subparser)           ||
      !AddElement    (TextBin , source   )           ||
      !AddElement    (TextBin , converter)           ||
      !AddElement    (TextBin , queue    )           ||
      !LinkElements  (filesrc   , subparser)         ||
      !LinkElements  (subparser , source   )         ||
      !LinkElements  (source    , converter)         ||
      !LinkElements  (converter , queue    )         ||
      !NewGhostSrcPad(TextBin , queue , "text-source"))
  { AvCaster::Error(GUI::TEXT_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildImageBin()
{
DEBUG_TRACE_BUILD_IMAGE_BIN
//#define STATIC_IMAGE
#  ifdef STATIC_IMAGE

  GstElement *source  , *decoder        , *converter ,
             *scaler  , *scaler_filter  ,
             *freezer , *freezer_filter , *queue ;
  GstCaps    *scaler_caps , *freezer_caps ;

  bool   is_enabled       = bool(ConfigStore[CONFIG::IS_IMAGE_ACTIVE_ID]) ;
  int    interstitial_w   = int (ConfigStore[CONFIG::SCREENCAP_W_ID    ]) ;
  int    interstitial_h   = int (ConfigStore[CONFIG::SCREENCAP_H_ID    ]) ;
  int    framerate_n      = int (ConfigStore[CONFIG::FRAMERATE_ID      ]) ;
  int    framerate        = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
  String image_filename   = "/home/bill/img/tech-diff.png" ;
  String scaler_caps_str  = String("video/x-raw, ")                                  +
                            "width=(int)"          + String(interstitial_w) + ", "   +
                            "height=(int)"         + String(interstitial_h) + ", "   +
                            "framerate=(fraction)0/1, "                              +
                            "format=(string)YUY2,"                                   +
                            "interlace-mode=(string)progressive, "                   +
                            "pixel-aspect-ratio=(fraction)1/1"                       ;
  String freezer_caps_str = String("video/x-raw, ")                                  +
                            "width=(int)"          + String(interstitial_w) + ", "   +
                            "height=(int)"         + String(interstitial_h) + ", "   +
                            "framerate=(fraction)" + String(framerate     ) + "/1, " +
                            "format=(string)YUY2,"                                   +
                            "interlace-mode=(string)progressive, "                   +
                            "pixel-aspect-ratio=(fraction)1/1"                       ;

  // instantiate elements
  if (!(source         = NewElement("filesrc"      , "interstitial-real-source" )) ||
      !(decoder        = NewElement("pngdec"       , "interstitial-decoder"     )) ||
      !(converter      = NewElement("videoconvert" , "interstitial-converter"   )) ||
      !(scaler         = NewElement("videoscale"   , "interstitial-scaler"      )) ||
      !(scaler_filter  = NewElement("capsfilter"   , "interstitial-scaler-caps" )) ||
      !(freezer        = NewElement("imagefreeze"  , "interstitial-freezer"     )) ||
      !(freezer_filter = NewElement("capsfilter"   , "interstitial-freezer-caps")) ||
      !(queue          = NewElement("queue"        , "interstitial-queue"       )) ||
      !(scaler_caps    = NewCaps   (scaler_caps_str)                             ) ||
      !(freezer_caps   = NewCaps   (freezer_caps_str)                            )  )
  { AvCaster::Error(GUI::IMAGE_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_IMAGE_BIN

  // configure elements
  ConfigureFile (source         , image_filename        ) ;
  ConfigureCaps (scaler_filter  , scaler_caps           ) ;
  ConfigureCaps (freezer_filter , freezer_caps          ) ;
  ConfigureQueue(queue          , 0              , 0 , 0) ;

  // link elements
  if (!AddElement    (ImageBin , source        )              ||
      !AddElement    (ImageBin , decoder       )              ||
      !AddElement    (ImageBin , converter     )              ||
      !AddElement    (ImageBin , scaler        )              ||
      !AddElement    (ImageBin , scaler_filter )              ||
      !AddElement    (ImageBin , freezer       )              ||
      !AddElement    (ImageBin , freezer_filter)              ||
      !AddElement    (ImageBin , queue         )              ||
      !LinkElements  (source         , decoder       )        ||
      !LinkElements  (decoder        , converter     )        ||
      !LinkElements  (converter      , scaler        )        ||
      !LinkElements  (scaler         , scaler_filter )        ||
      !LinkElements  (scaler_filter  , freezer       )        ||
      !LinkElements  (freezer        , freezer_filter)        ||
      !LinkElements  (freezer_filter , queue         )        ||
      !NewGhostSrcPad(ImageBin , queue , "interstitial-source"))
  { AvCaster::Error(GUI::IMAGE_LINK_ERROR_MSG) ; return false ; }

#  else // STATIC_IMAGE

  GstElement *source , *capsfilter , *converter , *queue ;
  GstCaps    *caps ;

  // TODO: static image src
  int    interstitial_w = int(ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int    interstitial_h = int(ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int    framerate_n    = int(ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int    framerate      = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
  String plugin_id      = GST::TESTVIDEO_PLUGIN_ID ;
  String caps_str       = String("video/x-raw, ")                                  +
                          "width=(int)"          + String(interstitial_w) + ", "   +
                          "height=(int)"         + String(interstitial_h) + ", "   +
                          "framerate=(fraction)" + String(framerate     ) + "/1, " +
                          "format=I420, "                                          +
                          "pixel-aspect-ratio=(fraction)1/1, "                     +
                          "interlace-mode=(string)progressive"                     ;

//DEBUG_TRACE_CONFIGURE_IMAGE

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "interstitial-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "interstitial-capsfilter" )) ||
      !(converter  = NewElement("videoconvert" , "interstitial-converter"  )) ||
      !(queue      = NewElement("queue"        , "interstitial-queue"      )) ||
      !(caps       = NewCaps   (caps_str)                                   )  )
  { AvCaster::Error(GUI::IMAGE_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureTestVideo(source , 1) ;
  ConfigureCaps(capsfilter , caps) ;

  // link elements
  if (!AddElement    (ImageBin , source    )             ||
      !AddElement    (ImageBin , capsfilter)             ||
      !AddElement    (ImageBin , converter )             ||
      !AddElement    (ImageBin , queue     )             ||
      !LinkElements  (source     , capsfilter)           ||
      !LinkElements  (capsfilter , converter )           ||
      !LinkElements  (converter  , queue     )           ||
      !NewGhostSrcPad(ImageBin   , queue , "image-source"))
  { AvCaster::Error(GUI::IMAGE_LINK_ERROR_MSG) ; return false ; }

#  endif // STATIC_IMAGE

  return true ;
}

bool Gstreamer::BuildCompositorBin()
{
DEBUG_TRACE_BUILD_COMPOSITOR_BIN

  GstElement *fullscreen_queue , *overlay_queue                                ,
             *compositor       , *capsfilter           , *converter            ,
             *composite_tee    , *composite_sink_queue , *composite_thru_queue ;
  GstCaps*    caps ;
  GstPad     *compositor_fullscreen_sinkpad , *compositor_overlay_sinkpad ;

  int         fullscreen_w = int (ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int         fullscreen_h = int (ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int         output_w     = int (ConfigStore[CONFIG::OUTPUT_W_ID   ]) ;
  int         output_h     = int (ConfigStore[CONFIG::OUTPUT_H_ID   ]) ;
  int         framerate_n  = int (ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int         framerate    = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
  String      overlay_res  = AvCaster::GetCameraResolution() ;
  StringArray res_tokens   = StringArray::fromTokens(overlay_res , "x" , "") ;
  int         overlay_w    = res_tokens[0].getIntValue() ;
  int         overlay_h    = res_tokens[1].getIntValue() ;
  int         overlay_x    = fullscreen_w - overlay_w ;
  int         overlay_y    = fullscreen_h - overlay_h ;
  String      caps_str     = MakeVideoCapsString(output_w , output_h , framerate) ;

  // instantiate elements
  if (!(fullscreen_queue     = NewElement("queue"        , "compositor-fullscreen-queue")) ||
      !(overlay_queue        = NewElement("queue"        , "compositor-overlay-queue"   )) ||
      !(compositor           = NewElement("compositor"   , "compositor"                 )) ||
      !(capsfilter           = NewElement("capsfilter"   , "compositor-capsfilter"      )) ||
      !(converter            = NewElement("videoconvert" , "compositor-converter"       )) ||
      !(composite_tee        = NewElement("tee"          , "compositor-tee"             )) ||
      !(composite_sink_queue = NewElement("queue"        , "compositor-sink-queue"      )) ||
      !(composite_thru_queue = NewElement("queue"        , "compositor-thru-queue"      )) ||
      !(caps                 = NewCaps   (caps_str)                                      )  )
  { AvCaster::Error(GUI::MIXER_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN

  // configure elements
  ConfigureQueue     (fullscreen_queue     , 0    , 0 , 0) ;
  ConfigureQueue     (overlay_queue        , 0    , 0 , 0) ;
  ConfigureCompositor(compositor           , 3           ) ;
  ConfigureCaps      (capsfilter           , caps        ) ;
  ConfigureQueue     (composite_sink_queue , 0    , 0 , 0) ;
  ConfigureQueue     (composite_thru_queue , 0    , 0 , 0) ;

  // link elements
  if (!AddElement  (CompositorBin , fullscreen_queue    )  ||
      !AddElement  (CompositorBin , overlay_queue       )  ||
      !AddElement  (CompositorBin , compositor          )  ||
      !AddElement  (CompositorBin , capsfilter          )  ||
      !AddElement  (CompositorBin , converter           )  ||
      !AddElement  (CompositorBin , composite_tee       )  ||
      !AddElement  (CompositorBin , composite_sink_queue)  ||
      !AddElement  (CompositorBin , composite_thru_queue)  ||
      !LinkElements(compositor           , capsfilter    ) ||
      !LinkElements(capsfilter           , converter     ) ||
      !LinkElements(converter            , composite_tee )  )
  { AvCaster::Error(GUI::MIXER_LINK_ERROR_MSG) ; return false ; }

  // instantiate request pads
  GstPad *composite_tee_thru_srcpad , *composite_tee_monitor_srcpad ;

  if (!NewGhostSinkPad(CompositorBin , fullscreen_queue , "compositor-fullscreen-sink") ||
      !NewGhostSinkPad(CompositorBin , overlay_queue    , "compositor-overlay-sink"   ) ||
      !(compositor_fullscreen_sinkpad = NewRequestSinkPad(compositor   )              ) ||
      !(compositor_overlay_sinkpad    = NewRequestSinkPad(compositor   )              ) ||
      !(composite_tee_thru_srcpad     = NewRequestSrcPad (composite_tee)              ) ||
      !(composite_tee_monitor_srcpad  = NewRequestSrcPad (composite_tee)              )  )
  { AvCaster::Error(GUI::MIXER_PAD_INIT_ERROR_MSG) ; return false ; }

  // configure request pads
  ConfigureCompositorSink(compositor_fullscreen_sinkpad , fullscreen_w , fullscreen_h ,
                                                          0            , 0            ) ;
  ConfigureCompositorSink(compositor_overlay_sinkpad    , overlay_w    , overlay_h    ,
                                                          overlay_x    , overlay_y    ) ;

  // link ghost pads and request pads
  GstPad *fullscreen_thru_srcpad , *overlay_thru_srcpad    ,
         *composite_thru_sinkpad , *composite_sink_sinkpad ;
  if (!(fullscreen_thru_srcpad = NewStaticSrcPad (fullscreen_queue    )            ) ||
      !(overlay_thru_srcpad    = NewStaticSrcPad (overlay_queue       )            ) ||
      !(composite_thru_sinkpad = NewStaticSinkPad(composite_thru_queue)            ) ||
      !(composite_sink_sinkpad = NewStaticSinkPad(composite_sink_queue)            ) ||
      !LinkPads       (fullscreen_thru_srcpad       , compositor_fullscreen_sinkpad) ||
      !LinkPads       (overlay_thru_srcpad          , compositor_overlay_sinkpad   ) ||
      !LinkPads       (composite_tee_thru_srcpad    , composite_thru_sinkpad       ) ||
      !LinkPads       (composite_tee_monitor_srcpad , composite_sink_sinkpad       ) ||
      !NewGhostSrcPad(CompositorBin , composite_thru_queue , "compositor-source")    ||
      !NewGhostSrcPad(CompositorBin , composite_sink_queue , "preview-source"   )     )
  { AvCaster::Error(GUI::MIXER_PAD_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildPreviewBin()
{
DEBUG_TRACE_BUILD_PREVIEW_BIN

  GstElement* preview_sink ;

  // instantiate elements
  if (!(PreviewQueue    = NewElement("queue"                 , "preview-queue"         )) ||
      !(PreviewRealSink = NewElement(GST::PREVIEW_PLUGIN_ID  , GST::PREVIEW_SINK_ID    )) ||
      !(PreviewFauxSink = NewElement(GST::FAUXSINK_PLUGIN_ID , GST::PREVIEW_FAUXSINK_ID))  )
  { AvCaster::Error(GUI::PREVIEW_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureQueue(PreviewQueue , 0 , 0 , 0) ;
  preview_sink = ConfigurePreview() ; if (preview_sink == nullptr) return false ;

  // link elements
  if (!AddElement     (PreviewBin , PreviewQueue                          ) ||
      !AddElement     (PreviewBin , preview_sink                          ) ||
      !NewGhostSinkPad(PreviewBin , PreviewQueue , GST::PREVIEW_SINKPAD_ID) ||
      !LinkElements   (PreviewQueue  , preview_sink)                         )
  { AvCaster::Error(GUI::PREVIEW_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildAudioBin()
{
DEBUG_TRACE_BUILD_AUDIO_BIN

  GstElement *source , *converter , *queue ;

  // instantiate elements
  if (!(AudioAlsaSource  = NewElement(GST::ALSA_PLUGIN_ID      , "audio-alsa-source" )) ||
      !(AudioPulseSource = NewElement(GST::PULSE_PLUGIN_ID     , "audio-pulse-source")) ||
      !(AudioJackSource  = NewElement(GST::JACK_PLUGIN_ID      , "audio-jack-source" )) ||
      !(AudioTestSource  = NewElement(GST::TESTAUDIO_PLUGIN_ID , "audio-test-source" )) ||
      !(AudioCaps        = NewElement("capsfilter"             , "audio-capsfilter"  )) ||
      !(converter        = NewElement("audioconvert"           , "audio-converter"   )) ||
      !(queue            = NewElement("queue"                  , "audio-queue"       ))  )
  { AvCaster::Error(GUI::AUDIO_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  source = ConfigureAudio() ;
  ConfigureQueue(queue , 0 , 0 , 0) ;

  // link elements
  if (!AddElement    (AudioBin , source   )             ||
      !AddElement    (AudioBin , AudioCaps)             ||
      !AddElement    (AudioBin , converter)             ||
      !AddElement    (AudioBin , queue    )             ||
      !LinkElements  (source    , AudioCaps)            ||
      !LinkElements  (AudioCaps , converter)            ||
      !LinkElements  (converter , queue    )            ||
      !NewGhostSrcPad(AudioBin  , queue , "audio-source"))
  { AvCaster::Error(GUI::AUDIO_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildMuxerBin()
{
DEBUG_TRACE_BUILD_MUXER_BIN

  GstElement *video_in_queue , *video_converter , *video_encoder , *video_parser ,
             *video_enc_caps , *video_enc_queue                                  ;
  GstElement *audio_in_queue , *audio_converter , *audio_encoder , *audio_parser ,
             *audio_enc_caps , *audio_enc_queue ;
  GstElement *muxer ;
  GstCaps    *video_caps , *audio_caps ;

  int   output_w        = int(ConfigStore[CONFIG::OUTPUT_W_ID     ]) ;
  int   output_h        = int(ConfigStore[CONFIG::OUTPUT_H_ID     ]) ;
  int   video_bitrate_n = int(ConfigStore[CONFIG::VIDEO_BITRATE_ID]) ;
  int   audio_bitrate_n = int(ConfigStore[CONFIG::AUDIO_BITRATE_ID]) ;
  int   framerate_n     = int(ConfigStore[CONFIG::FRAMERATE_ID    ]) ;
  int   n_channels      = int(ConfigStore[CONFIG::N_CHANNELS_ID   ]) ;
  int   samplerate_n    = int(ConfigStore[CONFIG::SAMPLERATE_ID   ]) ;
  guint video_bitrate   = CONFIG::VIDEO_BITRATES   [video_bitrate_n].getIntValue() ;
  guint audio_bitrate   = CONFIG::AUDIO_BITRATES   [audio_bitrate_n].getIntValue() ;
  int   framerate       = CONFIG::FRAMERATES       [framerate_n    ].getIntValue() ;
  int   samplerate      = CONFIG::AUDIO_SAMPLERATES[samplerate_n   ].getIntValue() ;
  String h264_caps_str  = MakeH264CapsString(output_w , output_h , framerate) ;
  String mp3_caps_str   = MakeMp3CapsString(samplerate , n_channels) ;
  String video_caps_str = h264_caps_str ;
  String audio_caps_str = mp3_caps_str ;

  if (!(video_in_queue  = NewElement("queue"          , "mux-video-queue"    )) ||
      !(video_converter = NewElement("videoconvert"   , "mux-video-converter")) ||
      !(video_encoder   = NewElement("x264enc"        , "mux-video-encoder"  )) ||
      !(video_parser    = NewElement("h264parse"      , "mux-video-parser"   )) ||
      !(video_caps      = NewCaps   (video_caps_str)                          ) ||
      !(video_enc_caps  = NewElement("capsfilter"     , "mux-video-enc-caps" )) ||
      !(video_enc_queue = NewElement("queue"          , "mux-video-enc-queue")) ||
      !(audio_in_queue  = NewElement("queue"          , "mux-audio-queue"    )) ||
      !(audio_converter = NewElement("audioconvert"   , "audio-converter"    )) ||
      !(audio_encoder   = NewElement("lamemp3enc"     , "mux-audio-encoder"  )) ||
      !(audio_parser    = NewElement("mpegaudioparse" , "mux-audio-parser"   )) ||
      !(audio_caps      = NewCaps   (audio_caps_str)                          ) ||
      !(audio_enc_caps  = NewElement("capsfilter"     , "mux-audio-enc-caps" )) ||
      !(audio_enc_queue = NewElement("queue"          , "mux-audio-enc-queue")) ||
      !(muxer           = NewElement("flvmux"         , "mux-flvmux"         ))  )
  { AvCaster::Error(GUI::MUXER_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_MUXER_BIN

  ConfigureX264Encoder(video_encoder   , video_bitrate) ;
  ConfigureCaps       (video_enc_caps  , video_caps   ) ;
  ConfigureLameEncoder(audio_encoder   , audio_bitrate) ;
  ConfigureCaps       (audio_enc_caps  , audio_caps   ) ;
  ConfigureQueue      (audio_enc_queue , 0 , 0 , 0    ) ;
  ConfigureFlvmux     (muxer) ;

  if (!AddElement     (MuxerBin , video_in_queue )                   ||
      !AddElement     (MuxerBin , video_converter)                   ||
      !AddElement     (MuxerBin , video_encoder  )                   ||
      !AddElement     (MuxerBin , video_enc_caps )                   ||
      !AddElement     (MuxerBin , video_parser   )                   ||
      !AddElement     (MuxerBin , video_enc_queue)                   ||
      !AddElement     (MuxerBin , audio_in_queue )                   ||
      !AddElement     (MuxerBin , audio_converter)                   ||
      !AddElement     (MuxerBin , audio_encoder  )                   ||
      !AddElement     (MuxerBin , audio_parser   )                   ||
      !AddElement     (MuxerBin , audio_enc_caps )                   ||
      !AddElement     (MuxerBin , audio_enc_queue)                   ||
      !AddElement     (MuxerBin , muxer          )                   ||
      !LinkElements   (video_in_queue  , video_converter)            ||
#  ifdef FAKE_MUX_ENCODER_SRC_AND_SINK
      !LinkElements   (video_converter , fake_enc_sink  )            ||
      !LinkElements   (fake_enc_src    , video_encoder  )            ||
#  else // FAKE_MUX_ENCODER_SRC_AND_SINK
      !LinkElements   (video_converter , video_encoder  )            ||
#  endif // FAKE_MUX_ENCODER_SRC_AND_SINK
      !LinkElements   (video_encoder   , video_enc_caps )            ||
      !LinkElements   (video_enc_caps  , video_parser   )            ||
      !LinkElements   (video_parser    , video_enc_queue)            ||
      !LinkElements   (video_enc_queue , muxer          )            ||
      !NewGhostSinkPad(MuxerBin , video_in_queue , "mux-video-sink") ||
      !LinkElements   (audio_in_queue  , audio_converter)            ||
      !LinkElements   (audio_converter , audio_encoder  )            ||
      !LinkElements   (audio_encoder   , audio_enc_caps )            ||
      !LinkElements   (audio_enc_caps  , audio_parser   )            ||
      !LinkElements   (audio_parser    , audio_enc_queue)            ||
      !LinkElements   (audio_enc_queue , muxer          )            ||
      !NewGhostSinkPad(MuxerBin , audio_in_queue , "mux-audio-sink") ||
      !NewGhostSrcPad (MuxerBin , muxer          , "mux-source"    )  )
  { AvCaster::Error(GUI::MUXER_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildOutputBin()
{
DEBUG_TRACE_BUILD_OUTPUT_BIN

  GstElement *queue , *sink ;

  bool   is_enabled  = bool  (ConfigStore[CONFIG::IS_OUTPUT_ACTIVE_ID]) ;
  int    muxer_idx   = int   (ConfigStore[CONFIG::OUTPUT_MUXER_ID    ]) ;
  int    sink_idx    = int   (ConfigStore[CONFIG::OUTPUT_SINK_ID     ]) ;
  String dest        = STRING(ConfigStore[CONFIG::OUTPUT_DEST_ID     ]) ;
  String file_ext    = CONFIG::OUTPUT_MUXERS[muxer_idx] ;
  String filename    = dest.upToLastOccurrenceOf(file_ext , false , true) ;
  File   output_file = APP::VIDEOS_DIR.getNonexistentChildFile(filename , file_ext , false) ;
  String file_url    = output_file.getFullPathName() ;
  bool   is_lctv     = AvCaster::GetPresetIdx() == CONFIG::LCTV_PRESET_IDX ;
  String rtmp_url    = (is_lctv) ? MakeLctvUrl(dest) : dest ;

#ifdef DISABLE_OUTPUT
UNUSED(is_enabled) ; is_enabled = false ;
#endif // DISABLE_OUTPUT

  if (!is_enabled) sink_idx = -1 ; String plugin_id , output_url ;
  switch ((CONFIG::OutputStream)sink_idx)
  {
    case CONFIG::FILE_OUTPUT_IDX: plugin_id = GST::FILESINK_PLUGIN_ID ; output_url = file_url ; break ;
    case CONFIG::RTMP_OUTPUT_IDX: plugin_id = GST::RTMPSINK_PLUGIN_ID ; output_url = rtmp_url ; break ;
    default:                      plugin_id = GST::FAUXSINK_PLUGIN_ID ; is_enabled = false ;    break ;
  }

#ifdef DEBUG
if (sink_idx == CONFIG::RTMP_OUTPUT_IDX)
{
  String env_url = std::getenv("AVCASTER_RTMP_DEST") ;
  if (env_url.isNotEmpty()) output_url = (is_lctv) ? MakeLctvUrl(env_url) : env_url ;
  else
  {
    AvCaster::Error(DEBUG_RTMP_DEST_ERROR_MSG) ;
    plugin_id = GST::FILESINK_PLUGIN_ID ; output_url = file_url ;
  }
}
#endif // DEBUG

  if (!(queue = NewElement("queue"   , "output-queue"    )) ||
      !(sink  = NewElement(plugin_id , "output-real-sink"))  )
  { AvCaster::Error(GUI::OUTPUT_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_OUTPUT_BIN

  ConfigureQueue(queue , 0 , 0 , 0) ;
  if (is_enabled) ConfigureFileSource(sink , output_url) ;

  if (!AddElement     (OutputBin , queue)               ||
      !AddElement     (OutputBin , sink )               ||
      !LinkElements   (queue  , sink)                   ||
      !NewGhostSinkPad(OutputBin , queue , "output-sink"))
  { AvCaster::Error(GUI::OUTPUT_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::Reconfigure(const Identifier& config_key)
{
  bool configure_all     = (config_key == CONFIG::PRESET_ID    ||
                            config_key == CONFIG::IS_PENDING_ID ) && !AvCaster::GetIsConfigPending() ;
  bool configure_screen  =  config_key == CONFIG::IS_SCREENCAP_ACTIVE_ID || configure_all ;
  bool configure_camera  =  config_key == CONFIG::IS_CAMERA_ACTIVE_ID    || configure_all ;
  bool configure_text    =  config_key == CONFIG::IS_TEXT_ACTIVE_ID      || configure_all ;
  bool configure_image   =  config_key == CONFIG::IS_IMAGE_ACTIVE_ID     || configure_all ;
  bool configure_preview =  config_key == CONFIG::IS_PREVIEW_ACTIVE_ID   ||
                            config_key == CONFIG::IS_PENDING_ID          || configure_all ;
  bool configure_audio   =  config_key == CONFIG::IS_AUDIO_ACTIVE_ID     || configure_all ;
  bool configure_output  =  config_key == CONFIG::IS_OUTPUT_ACTIVE_ID    || configure_all ;

DEBUG_TRACE_RECONFIGURE_IN

  ReloadConfig() ; SetState(Pipeline , GST_STATE_READY) ;

  bool is_error = (configure_screen  && ConfigureScreen()  == nullptr) ||
                  (configure_camera  && ConfigureCamera()  == nullptr) ||
                  (configure_text    && ConfigureText()    == nullptr) ||
                  (configure_image   && ConfigureImage()   == nullptr) ||
                  (configure_preview && ConfigurePreview() == nullptr) ||
                  (configure_audio   && ConfigureAudio()   == nullptr) ||
                  (configure_output  && ConfigureOutput()  == nullptr)  ;

DEBUG_TRACE_RECONFIGURE_OUT

  // NOTE: an error here should cause Gstreamer::HandleErrorMessage() to fire
  //         which should attempt revovery to a same configuration
  is_error = !SetState(Pipeline , GST_STATE_PLAYING) || is_error ;

// DEBUG_MAKE_GRAPHVIZ

  return !is_error ;
}

GstElement* Gstreamer::ConfigureScreen()
{
  bool        is_active       = AvCaster::GetIsScreenEnabled()                   &&
                                bool(ConfigStore[CONFIG::IS_SCREENCAP_ACTIVE_ID]) ;
  int         screencap_w     = int (ConfigStore[CONFIG::SCREENCAP_W_ID        ]) ;
  int         screencap_h     = int (ConfigStore[CONFIG::SCREENCAP_H_ID        ]) ;
  int         framerate_n     = int (ConfigStore[CONFIG::FRAMERATE_ID          ]) ;
  int         framerate       = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
  String      screen_caps_str = MakeScreenCapsString(screencap_w , screencap_h , framerate) ;
  String      faux_caps_str   = MakeVideoCapsString (screencap_w , screencap_h , framerate) ;
  String      caps_str        = (is_active) ? screen_caps_str : faux_caps_str ;
  GstElement* next_source     = (is_active) ? ScreenRealSource : ScreenFauxSource ;
  GstElement* current_source  = (IsInBin(ScreencapBin , ScreenRealSource)) ? ScreenRealSource :
                                (IsInBin(ScreencapBin , ScreenFauxSource)) ? ScreenFauxSource :
                                                                             nullptr          ;

DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN

  // configure elements
  ConfigureScreenSource(next_source , screencap_w , screencap_h , 0 , is_active) ;
  ConfigureCaps        (ScreenCaps , NewCaps(caps_str)) ;

  // re-link elements
  if (current_source != nullptr)
  {
    if (!RemoveElement(ScreencapBin , current_source) ||
        !AddElement   (ScreencapBin , next_source   ) ||
        !LinkElements (next_source , ScreenCaps)       )
    { AvCaster::Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureCamera()
{
  // TODO: query device for resolutions (eliminate CONFIG::CAMERA_RESOLUTIONS)
  String      device_path     = AvCaster::GetCameraPath() ;
  int         framerate       = AvCaster::GetCameraRate() ;
  String      resolution      = AvCaster::GetCameraResolution() ;
  bool        is_active       = AvCaster::GetIsCameraEnabled()                 &&
                                bool(ConfigStore[CONFIG::IS_CAMERA_ACTIVE_ID]) &&
                                device_path.isNotEmpty()                        ;
  StringArray res_tokens      = StringArray::fromTokens(resolution , "x" , "") ;
  int         camera_w        = res_tokens[0].getIntValue() ;
  int         camera_h        = res_tokens[1].getIntValue() ;
  String      camera_caps_str = MakeCameraCapsString(camera_w , camera_h , framerate) ;
  String      faux_caps_str   = MakeVideoCapsString (camera_w , camera_h , framerate) ;
  String      caps_str        = (is_active) ? camera_caps_str : faux_caps_str ;
  GstElement* next_source     = (is_active) ? CameraRealSource : CameraFauxSource ;
  GstElement* current_source  = (IsInBin(CameraBin , CameraRealSource)) ? CameraRealSource :
                                (IsInBin(CameraBin , CameraFauxSource)) ? CameraFauxSource :
                                                                          nullptr          ;

DEBUG_TRACE_CONFIGURE_CAMERA_BIN

  // configure elements
  ConfigureCameraSource(next_source , device_path , 1 , is_active) ;
  ConfigureCaps        (CameraCaps , NewCaps(caps_str)) ;

  // re-link elements
  if (current_source != nullptr)
  {
    if (!RemoveElement(CameraBin , current_source) ||
        !AddElement   (CameraBin , next_source   ) ||
        !LinkElements (next_source , CameraCaps)    )
    { AvCaster::Error(GUI::CAMERA_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureText() {}

GstElement* Gstreamer::ConfigureImage() {}

GstElement* Gstreamer::ConfigurePreview()
{
  GstElement *current_sink , *next_sink ;

  bool is_enabled = AvCaster::GetIsPreviewEnabled() && AvCaster::GetIsPreviewActive() ;
  current_sink    = (IsInBin(PreviewBin , PreviewRealSink)) ? PreviewRealSink :
                    (IsInBin(PreviewBin , PreviewFauxSink)) ? PreviewFauxSink : nullptr ;
  next_sink       = (is_enabled) ? PreviewRealSink : PreviewFauxSink ;

DEBUG_TRACE_CONFIGURE_PREVIEW_BIN

  // configure elements
  if (next_sink == PreviewRealSink)
  {
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(PreviewRealSink) , PreviewXwin) ;
    if (!ConfigureVideoSink(PreviewRealSink))
    { AvCaster::Error(GUI::GST_XWIN_ERROR_MSG) ; return nullptr ; }
  }
  else gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(PreviewRealSink) , 0) ;
  gst_video_overlay_expose(GST_VIDEO_OVERLAY(PreviewRealSink)) ;

  // re-link elements
  if (current_sink != nullptr)
  {
    if (!RemoveElement(PreviewBin , current_sink) ||
        !AddElement   (PreviewBin , next_sink)    ||
        !LinkElements (PreviewQueue , next_sink)   )
    { AvCaster::Error(GUI::PREVIEW_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_sink ;
}

GstElement* Gstreamer::ConfigureAudio()
{
  GstElement *current_source , *next_source ;
  String      caps_str ;

  bool   is_enabled       = AvCaster::GetIsAudioEnabled()                &&
                            bool(ConfigStore[CONFIG::IS_AUDIO_ACTIVE_ID]) ;
  int    audio_api_idx    = int (ConfigStore[CONFIG::AUDIO_API_ID      ]) ;
  int    n_channels       = int (ConfigStore[CONFIG::N_CHANNELS_ID     ]) ;
  int    samplerate_n     = int (ConfigStore[CONFIG::SAMPLERATE_ID     ]) ;
  int    samplerate       = CONFIG::AUDIO_SAMPLERATES[samplerate_n].getIntValue() ;
  String audio16_caps_str = MakeAudioCapsString("S16LE" , samplerate , n_channels) ;
  String audio32_caps_str = MakeAudioCapsString("F32LE" , samplerate , n_channels) ;

  current_source = (IsInBin(AudioBin , AudioAlsaSource )) ? AudioAlsaSource  :
                   (IsInBin(AudioBin , AudioPulseSource)) ? AudioPulseSource :
                   (IsInBin(AudioBin , AudioJackSource )) ? AudioJackSource  :
                   (IsInBin(AudioBin , AudioTestSource )) ? AudioTestSource  : nullptr ;

  if (!is_enabled) audio_api_idx = CONFIG::CONFIG_IDX_INVALID ;
  switch ((CONFIG::AudioApi)audio_api_idx)
  {
    case CONFIG::ALSA_AUDIO_IDX:  next_source = AudioAlsaSource ;  caps_str = audio16_caps_str ; break ;
    case CONFIG::PULSE_AUDIO_IDX: next_source = AudioPulseSource ; caps_str = audio16_caps_str ; break ;
    case CONFIG::JACK_AUDIO_IDX:  next_source = AudioJackSource ;  caps_str = audio32_caps_str ; break ;
    default:                      next_source = AudioTestSource ;  caps_str = audio16_caps_str ; break ;
  }

DEBUG_TRACE_CONFIGURE_AUDIO_BIN

  // configure elements
  if (next_source == AudioTestSource) ConfigureFauxSource(AudioTestSource) ;
  ConfigureCaps(AudioCaps , NewCaps(caps_str)) ;

  // re-link elements
  if (current_source != nullptr)
  {
    if (!RemoveElement(AudioBin , current_source) ||
        !AddElement   (AudioBin , next_source)    ||
        !LinkElements (next_source , AudioCaps)    )
    { AvCaster::Error(GUI::AUDIO_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureOutput()
{

}

void Gstreamer::ConfigureFauxSource(GstElement* a_faux_source)
{
DEBUG_TRACE_CONFIGURE_FAUX_SRC

 g_object_set(G_OBJECT(a_faux_source) , "is_live" , true , NULL) ;
}

void Gstreamer::ConfigureCaps(GstElement* a_capsfilter , GstCaps* a_caps)
{
DEBUG_TRACE_CONFIGURE_CAPS

  g_object_set(G_OBJECT(a_capsfilter) , "caps" , a_caps , NULL) ; gst_caps_unref(a_caps) ;
}

void Gstreamer::ConfigureQueue(GstElement* a_queue  , guint max_bytes  ,
                               guint64     max_time , guint max_buffers)
{
DEBUG_TRACE_CONFIGURE_QUEUE

  g_object_set(G_OBJECT(a_queue) , "max-size-bytes"   , max_bytes   , NULL) ;
  g_object_set(G_OBJECT(a_queue) , "max-size-time"    , max_time    , NULL) ;
  g_object_set(G_OBJECT(a_queue) , "max-size-buffers" , max_buffers , NULL) ;
}

void Gstreamer::ConfigureScreenSource(GstElement* a_screen_source , guint capture_w , guint capture_h ,
                                      guint       pattern_n       , bool  is_active                   )
{
DEBUG_TRACE_CONFIGURE_SCREEN

  if (is_active)
  {
    g_object_set(G_OBJECT(a_screen_source) , "endx"       , capture_w - 1 , NULL) ;
    g_object_set(G_OBJECT(a_screen_source) , "endy"       , capture_h - 1 , NULL) ;
    g_object_set(G_OBJECT(a_screen_source) , "use-damage" , false         , NULL) ;
  }
  else ConfigureTestVideo(a_screen_source , pattern_n) ;
}

void Gstreamer::ConfigureCameraSource(GstElement* a_camera_source , String device_path ,
                                      guint       pattern_n       , bool   is_active   )
{
DEBUG_TRACE_CONFIGURE_CAMERA

  if (is_active)
    g_object_set(G_OBJECT(a_camera_source) , "device" , CHARSTAR(device_path) , NULL) ;
  else ConfigureTestVideo(a_camera_source , pattern_n) ;
}

void Gstreamer::ConfigureTestVideo(GstElement* a_test_source , guint pattern_n)
{
DEBUG_TRACE_CONFIGURE_TEST_VIDEO

  ConfigureFauxSource(a_test_source) ;
  g_object_set(G_OBJECT(a_test_source) , "pattern" , pattern_n , NULL) ;
}

void Gstreamer::ConfigureTextSource(GstElement* a_text_source , String font_desc)
{
DEBUG_TRACE_CONFIGURE_TEXT

  g_object_set(G_OBJECT(a_text_source) , "font-desc" , CHARSTAR(font_desc) , NULL) ;
}

void Gstreamer::ConfigureFileSource(GstElement* a_file_source , String file_path)
{
DEBUG_TRACE_CONFIGURE_FILE

  g_object_set(G_OBJECT(a_file_source) , "location" , CHARSTAR(file_path) , NULL) ;
}

void Gstreamer::ConfigureCompositor(GstElement* a_compositor , guint background_n)
{
DEBUG_TRACE_CONFIGURE_COMPOSITOR

  g_object_set(G_OBJECT(a_compositor) , "background" , background_n , NULL) ;
}

void Gstreamer::ConfigureCompositorSink(GstPad* sinkpad , gint w , gint h ,
                                                          gint x , gint y )
{
DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK

  g_object_set(G_OBJECT(sinkpad) , "width"  , w , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "height" , h , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "xpos"   , x , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "ypos"   , y , NULL) ;
}

bool Gstreamer::ConfigureVideoSink(GstElement* a_video_sink)
{
DEBUG_TRACE_CONFIGURE_PREVIEW

  if (!AvCaster::GetIsPreviewEnabled()) return true ;

  Rectangle<int> preview_bounds = AvCaster::GetPreviewBounds() ;
  gint           preview_x      = preview_bounds.getX() ;
  gint           preview_y      = preview_bounds.getY() ;
  gint           preview_w      = preview_bounds.getWidth() ;
  gint           preview_h      = preview_bounds.getHeight() ;

//   g_object_set(a_video_sink , "async-handling" , TRUE , NULL) ;

  return gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(a_video_sink) ,
                                                preview_x , preview_y           ,
                                                preview_w , preview_h           ) ;
}

void Gstreamer::ConfigureX264Encoder(GstElement* an_x264_encoder , guint bitrate)
{
DEBUG_TRACE_CONFIGURE_X264ENC

  g_object_set(G_OBJECT(an_x264_encoder) , "bitrate" , bitrate , NULL) ;
//   g_object_set(G_OBJECT(video_encoder)  , "tune"       , 0x00000004     , NULL) ; // may lower quality in favor of latency
}

void Gstreamer::ConfigureLameEncoder(GstElement* a_lame_encoder , guint bitrate)
{
DEBUG_TRACE_CONFIGURE_LAMEENC

  g_object_set(G_OBJECT(a_lame_encoder) , "target"  , 1       , NULL) ;
  g_object_set(G_OBJECT(a_lame_encoder) , "cbr"     , true    , NULL) ; // CBR
  g_object_set(G_OBJECT(a_lame_encoder) , "bitrate" , bitrate , NULL) ; // CBR
// g_object_set(G_OBJECT(audio_encoder) , "quality" , 2 , NULL) ; // VBR (default is 4) // VBR
}

void Gstreamer::ConfigureFlvmux(GstElement* a_flvmuxer)
{
DEBUG_TRACE_CONFIGURE_FLVMUX

  g_object_set(G_OBJECT(a_flvmuxer) , "streamable" , true , NULL) ;
}

bool Gstreamer::SetState(GstElement* an_element , GstState next_state)
{
  bool is_err = an_element != nullptr                                                     &&
                gst_element_set_state(an_element , next_state) == GST_STATE_CHANGE_FAILURE ;

DEBUG_TRACE_SET_GST_STATE

  if (is_err) AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ;

  return !is_err ;
}


GstBusSyncReply Gstreamer::HandleMessage(GstBus* message_bus , GstMessage* message , GstPipeline* pipeline)
{
  switch (GST_MESSAGE_TYPE(message))
  {
    case GST_MESSAGE_ERROR:         HandleErrorMessage(message) ;         break ;
    case GST_MESSAGE_EOS:           LOG("GST_MESSAGE_EOS") ;              break ;
    case GST_MESSAGE_STATE_CHANGED:                                       break ;
    case GST_MESSAGE_STREAM_STATUS: /* DEBUG_TRACE_DUMP_MESSAGE_STRUCT */ break ;
    default:                        DEBUG_TRACE_UNHANDLED_MESSAGE         break ;
/* GST_MESSAGE_TYPE types
GST_MESSAGE_UNKNOWN           = 0,
GST_MESSAGE_EOS               = (1 << 0),
GST_MESSAGE_ERROR             = (1 << 1),
GST_MESSAGE_WARNING           = (1 << 2),
GST_MESSAGE_INFO              = (1 << 3),
GST_MESSAGE_TAG               = (1 << 4),
GST_MESSAGE_BUFFERING         = (1 << 5),
GST_MESSAGE_STATE_CHANGED     = (1 << 6),
GST_MESSAGE_STATE_DIRTY       = (1 << 7),
GST_MESSAGE_STEP_DONE         = (1 << 8),
GST_MESSAGE_CLOCK_PROVIDE     = (1 << 9),
GST_MESSAGE_CLOCK_LOST        = (1 << 10),
GST_MESSAGE_NEW_CLOCK         = (1 << 11),
GST_MESSAGE_STRUCTURE_CHANGE  = (1 << 12),
GST_MESSAGE_STREAM_STATUS     = (1 << 13),
GST_MESSAGE_APPLICATION       = (1 << 14),
GST_MESSAGE_ELEMENT           = (1 << 15),
GST_MESSAGE_SEGMENT_START     = (1 << 16),
GST_MESSAGE_SEGMENT_DONE      = (1 << 17),
GST_MESSAGE_DURATION          = (1 << 18),
GST_MESSAGE_LATENCY           = (1 << 19),
GST_MESSAGE_ASYNC_START       = (1 << 20),
GST_MESSAGE_ASYNC_DONE        = (1 << 21),
GST_MESSAGE_ANY               = ~0
*/
  }
/*  The result values for a GstBusSyncHandler.
GST_BUS_DROP   drop the message
GST_BUS_PASS   pass the message to the async queue
GST_BUS_ASYNC  pass message to async queue, continue if message is handled
*/
  return GST_BUS_PASS ;
}

void Gstreamer::HandleErrorMessage(GstMessage* message)
{
  GError *error ;
  gchar  *debug ;

  gst_message_parse_error(message , &error , &debug) ;
  String error_message       = String(error->message) ;
  bool   is_alsa_init_error  = error_message == GST::ALSA_INIT_ERROR ;
  bool   is_pulse_init_error = error_message == GST::PULSE_INIT_ERROR ;
  bool   is_jack_init_error  = error_message == GST::JACK_INIT_ERROR ;

DEBUG_TRACE_GST_ERROR_MESSAGE

  if (is_alsa_init_error || is_pulse_init_error || is_jack_init_error)
  {
    // re-configure with null source
    AvCaster::DeactivateControl(CONFIG::IS_AUDIO_ACTIVE_ID) ;
    ConfigureAudio() ;

    // alert user
    String warning_msg = (is_alsa_init_error ) ? GUI::ALSA_INIT_ERROR_MSG  :
                         (is_pulse_init_error) ? GUI::PULSE_INIT_ERROR_MSG :
                         (is_jack_init_error ) ? GUI::JACK_INIT_ERROR_MSG  : String::empty ;
    AvCaster::Warning(warning_msg + error_message) ;
  }

  g_error_free(error) ; g_free(debug) ;
}

GstElement* Gstreamer::NewPipeline(String pipeline_id) { return gst_pipeline_new(CHARSTAR(pipeline_id)) ; }

GstElement* Gstreamer::NewBin(String bin_id) { return gst_bin_new(CHARSTAR(bin_id)) ; }

GstElement* Gstreamer::NewElement(String plugin_id , String element_id)
{
  GstElement* new_element = gst_element_factory_make(CHARSTAR(plugin_id) , CHARSTAR(element_id)) ;

DEBUG_TRACE_MAKE_ELEMENT

  return new_element ;
}

GstCaps* Gstreamer::NewCaps(String caps_str)
{
  GstCaps* new_caps = gst_caps_from_string(CHARSTAR(caps_str)) ;

DEBUG_TRACE_MAKE_CAPS

  return new_caps ;
}

void Gstreamer::SetMessageHandler(GstPipeline* pipeline , GstBusSyncHandler on_message_cb)
{
  GstBus* message_bus = gst_pipeline_get_bus(pipeline) ;

  gst_bus_set_sync_handler(message_bus , on_message_cb , pipeline , NULL) ;
  gst_object_unref(message_bus) ;
}

bool Gstreamer::AddElement(GstElement* a_bin , GstElement* an_element)
{
  bool is_err = !gst_bin_add(GST_BIN(a_bin) , an_element)    ||
                !gst_element_sync_state_with_parent(an_element) ;

DEBUG_TRACE_ADD_ELEMENT

  return !is_err ;
}

bool Gstreamer::RemoveElement(GstElement* a_bin , GstElement* an_element)
{
DEBUG_TRACE_REMOVE_ELEMENT_IN
//   bool is_err = !IsInBin(a_bin , an_element) || !SetState(an_element , GST_STATE_NULL) ||
//                 !gst_bin_remove(GST_BIN(a_bin) , an_element) ;
  bool is_err = !IsInBin(a_bin , an_element) || !gst_bin_remove(GST_BIN(a_bin) , an_element) ;

DEBUG_TRACE_REMOVE_ELEMENT_OUT

  return !is_err ;
}

void Gstreamer::DestroyElement(GstElement* an_element)
{
DEBUG_TRACE_DESTROY_ELEMENT

  if (an_element != nullptr && SetState(an_element , GST_STATE_NULL))
    gst_object_unref(an_element) ;
}

bool Gstreamer::AddBin(GstElement* a_bin)
{
DEBUG_TRACE_ADD_BIN_IN

  bool is_err = a_bin == nullptr || IsInPipeline(a_bin)    ||
                (!gst_bin_add(GST_BIN(Pipeline) , a_bin)   ||
                 !gst_element_sync_state_with_parent(a_bin) ) ;

DEBUG_TRACE_ADD_BIN_OUT

  return !is_err ;
}

bool Gstreamer::RemoveBin(GstElement* a_bin)
{
DEBUG_TRACE_REMOVE_BIN_IN

  bool is_err = !IsInPipeline(a_bin) || !gst_bin_remove(GST_BIN(Pipeline) , a_bin) ;

DEBUG_TRACE_REMOVE_BIN_OUT

  return !is_err ;
}

bool Gstreamer::LinkElements(GstElement* source , GstElement* sink)
{
  bool is_err = !gst_element_link(source , sink) ;

DEBUG_TRACE_LINK_ELEMENTS

  return !is_err ;
}

bool Gstreamer::LinkPads(GstPad* srcpad , GstPad* sinkpad)
{
  bool is_err = gst_pad_link(srcpad , sinkpad) != GST_PAD_LINK_OK ;

DEBUG_TRACE_LINK_PADS

  return !is_err ;
}

GstPad* Gstreamer::NewGhostSrcPad(GstElement* a_bin         , GstElement* an_element ,
                                  String      public_pad_id                          )
{
  return NewGhostPad(a_bin , an_element , "src" , public_pad_id) ;
}

GstPad* Gstreamer::NewGhostSinkPad(GstElement* a_bin         , GstElement* an_element ,
                                   String      public_pad_id                          )
{
  return NewGhostPad(a_bin , an_element , "sink" , public_pad_id) ;
}

GstPad* Gstreamer::NewGhostPad(GstElement* a_bin       , GstElement* an_element   ,
                               String      template_id , String      public_pad_id)
{
  const gchar*  private_id = UTF8(template_id  ) ;
  const gchar*  public_id  = UTF8(public_pad_id) ;
  GstPad       *private_pad , *public_pad ;

  bool is_err = !(private_pad = gst_element_get_static_pad(an_element , private_id )) ||
                !(public_pad  = gst_ghost_pad_new         (public_id  , private_pad)) ||
                !gst_pad_set_active(public_pad , TRUE)                                 ;
  gst_object_unref(private_pad) ;

DEBUG_TRACE_MAKE_GHOST_PAD

  is_err = is_err || !AddGhostPad(a_bin , public_pad) ;
  if (is_err) gst_object_unref(public_pad) ;

  return (!is_err) ? public_pad : nullptr ;
}

bool Gstreamer::AddGhostPad(GstElement* a_bin , GstPad* public_pad)
{
  bool is_err = a_bin == nullptr || !gst_element_add_pad(a_bin , public_pad) ;

DEBUG_TRACE_ADD_GHOST_PAD ; UNUSED(is_err) ;

  return !is_err ;
}

GstPad* Gstreamer::NewStaticSinkPad(GstElement* an_element)
{
  return NewStaticPad(an_element , "sink") ;
}

GstPad* Gstreamer::NewStaticSrcPad(GstElement* an_element)
{
  return NewStaticPad(an_element , "src") ;
}

GstPad* Gstreamer::NewStaticPad(GstElement* an_element , String template_id)
{
  const gchar*  private_id = UTF8(template_id) ;
  GstPad*       private_pad ;

  bool is_err = !(private_pad = gst_element_get_static_pad(an_element , private_id)) ;

DEBUG_TRACE_GET_STATIC_PAD ; UNUSED(is_err) ;

  return private_pad ;
}

GstPad* Gstreamer::NewRequestSinkPad(GstElement* an_element)
{
  return NewRequestPad(an_element , "sink_%u") ;
}

GstPad* Gstreamer::NewRequestSrcPad(GstElement* an_element)
{
  return NewRequestPad(an_element , "src_%u") ;
}

GstPad* Gstreamer::NewRequestPad(GstElement* an_element , String template_id)
{
  const gchar*  private_id = UTF8(template_id) ;
  GstPad*       private_pad ;

  bool is_err = !(private_pad = gst_element_get_request_pad(an_element , private_id)) ;

DEBUG_TRACE_GET_REQUEST_PAD ; UNUSED(is_err) ;

  return private_pad ;
}

String Gstreamer::MakeVideoCapsString(int width , int height , int framerate)
{
  return String("video/x-raw, ")                                    +
                "width=(int)"          + String(width    ) + ", "   +
                "height=(int)"         + String(height   ) + ", "   +
                "framerate=(fraction)" + String(framerate) + "/1, " +
//                 "format=ARGB, "                                     +
                "format=I420, "                                     +
                "pixel-aspect-ratio=(fraction)1/1, "                +
                "interlace-mode=(string)progressive"                ;
}

String Gstreamer::MakeScreenCapsString(int screencap_w , int screencap_h , int framerate)
{
  return String("video/x-raw, ")                               +
         "width=(int)"          + String(screencap_w) + ", "   +
         "height=(int)"         + String(screencap_h) + ", "   +
         "framerate=(fraction)" + String(framerate  ) + "/1, " +
         "pixel-aspect-ratio=(fraction)1/1"                    ;
}

String Gstreamer::MakeCameraCapsString(int camera_w , int camera_h , int framerate)
{
  return String("video/x-raw, ")                             +
#ifndef NATIVE_CAMERA_RESOLUTION_ONLY
         "width=(int)"          + String(camera_w ) + ", "   +
         "height=(int)"         + String(camera_h ) + ", "   +
         "framerate=(fraction)" + String(framerate) + "/1, " +
         "format=I420, "                                     +
#endif // NATIVE_CAMERA_RESOLUTION_ONLY
         "pixel-aspect-ratio=(fraction)1/1"                  ;
}

String Gstreamer::MakeAudioCapsString(String format , int samplerate , int n_channels)
{
  return String("audio/x-raw, "               )                             +
         String("layout=(string)interleaved, ")                             +
         String("format=(string)"             ) + format             + ", " +
         String("rate=(int)"    )               + String(samplerate) + ", " +
         String("channels=(int)")               + String(n_channels)        ;
//"channel-mask=(bitmask)0x03"
}

String Gstreamer::MakeH264CapsString(int output_w , int output_h , int framerate)
{
  return String("video/x-h264, ")                            +
         "width=(int)"          + String(output_w ) + ", "   +
         "height=(int)"         + String(output_h ) + ", "   +
         "framerate=(fraction)" + String(framerate) + "/1, " +
         "stream-format=avc, alignment=au, profile=main"     ;
//   String h264_caps_str  = "video/x-h264, level=(string)4.1, profile=main" ;
}

String Gstreamer::MakeMp3CapsString(int samplerate , int n_channels)
{
  return String("audio/mpeg, mpegversion=1, layer=3, ")       +
         String("rate=(int)"    ) + String(samplerate) + ", " +
         String("channels=(int)") + String(n_channels)        ;
//   String mp3_caps_str   = String("audio/mpeg, mpegversion=1, layer=3, mpegaudioversion=3, ") +
}

String Gstreamer::MakeLctvUrl(String dest)
{
  return GST::LCTV_RTMP_URL                                            +
         dest.fromFirstOccurrenceOf(GST::LCTV_RTMP_URL , false , true) +
         dest.upToLastOccurrenceOf (" live=1"          , false , true) +
         " live=1"                                                     ;
}

bool Gstreamer::IsSufficientVersion()
{
  guint major_version , minor_version , micro_version , nano_version ;

  gst_version(&major_version , &minor_version , &micro_version , &nano_version) ;

  return major_version >= GST::MIN_MAJOR_VERSION &&
         minor_version >= GST::MIN_MINOR_VERSION  ;
}

String Gstreamer::GetElementId(GstElement* an_element)
{
  if (!an_element) return "nil" ;

  gchar* id = gst_element_get_name(an_element) ; String element_id = id ; g_free(id) ;

  return element_id ;
}

String Gstreamer::GetPadId(GstPad* a_pad)
{
  if (!a_pad) return "nil" ;

  gchar* id = gst_pad_get_name(a_pad) ; String pad_id = id ; g_free(id) ;

  return pad_id ;
}

bool Gstreamer::IsInitialized() { return gst_is_initialized() ; }

bool Gstreamer::IsPlaying()
{
  return !!Pipeline && GST_STATE(Pipeline) == GST_STATE_PLAYING ;
}

bool Gstreamer::IsInPipeline(GstElement* an_element)
{
  return IsInBin(Pipeline , an_element) ;
}

bool Gstreamer::IsInBin(GstElement* a_parent_element , GstElement* a_child_element)
{
  return !!a_child_element && !!a_parent_element                &&
         GST_ELEMENT_PARENT(a_child_element) == a_parent_element ;
}
