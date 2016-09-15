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


#include <gst/video/videooverlay.h>
#include <gst/video/gstvideosink.h>

#include "AvCaster.h"
#include "Gstreamer.h"
#include "../Trace/TraceGstreamer.h"


/* Gstreamer private class variables */

GstElement* Gstreamer::Pipeline                = nullptr ;            // Initialize()
GstElement* Gstreamer::ScreencapBin            = nullptr ;            // Initialize()
GstElement* Gstreamer::ScreenRealSource        = nullptr ;            // BuildScreencapBin()
GstElement* Gstreamer::ScreenFauxSource        = nullptr ;            // BuildScreencapBin()
GstElement* Gstreamer::ScreenCapsfilter        = nullptr ;            // BuildScreencapBin()
GstElement* Gstreamer::CameraBin               = nullptr ;            // Initialize()
GstElement* Gstreamer::CameraRealSource        = nullptr ;            // BuildCameraBin()
GstElement* Gstreamer::CameraFauxSource        = nullptr ;            // BuildCameraBin()
GstElement* Gstreamer::CameraCapsfilter        = nullptr ;            // BuildCameraBin()
GstElement* Gstreamer::TextBin                 = nullptr ;            // Initialize()
GstElement* Gstreamer::ImageBin                = nullptr ;            // Initialize()
GstElement* Gstreamer::CompositorBin           = nullptr ;            // Initialize()
GstPad*     Gstreamer::CompositorScreenSinkpad = nullptr ;            // BuildCompositorBin()
GstPad*     Gstreamer::CompositorCameraSinkpad = nullptr ;            // BuildCompositorBin()
GstPad*     Gstreamer::CompositorTextSinkpad   = nullptr ;            // BuildCompositorBin()
GstPad*     Gstreamer::CompositorImageSinkpad  = nullptr ;            // BuildCompositorBin()
#ifndef GST_COMPOSITOR_BUG
GstElement* Gstreamer::CompositorCapsfilter    = nullptr ;            // BuildCompositorBin()
#endif // GST_COMPOSITOR_BUG
GstElement* Gstreamer::PreviewBin              = nullptr ;            // Initialize()
GstElement* Gstreamer::PreviewQueue            = nullptr ;            // BuildPreviewBin()
GstElement* Gstreamer::PreviewFauxSink         = nullptr ;            // BuildPreviewBin()
GstElement* Gstreamer::PreviewRealSink         = nullptr ;            // BuildPreviewBin()
GstElement* Gstreamer::AudioBin                = nullptr ;            // Initialize()
GstElement* Gstreamer::AudioAlsaSource         = nullptr ;            // BuildAudioBin()
GstElement* Gstreamer::AudioPulseSource        = nullptr ;            // BuildAudioBin()
GstElement* Gstreamer::AudioJackSource         = nullptr ;            // BuildAudioBin()
GstElement* Gstreamer::AudioFauxSource         = nullptr ;            // BuildAudioBin()
GstElement* Gstreamer::AudioCaps               = nullptr ;            // BuildAudioBin()
GstElement* Gstreamer::MuxerBin                = nullptr ;            // Initialize()
GstElement* Gstreamer::OutputBin               = nullptr ;            // Initialize()
GstElement* Gstreamer::OutputQueue             = nullptr ;            // BuildOutputBin()
GstElement* Gstreamer::OutputFileSink          = nullptr ;            // BuildOutputBin()
GstElement* Gstreamer::OutputRtmpSink          = nullptr ;            // BuildOutputBin()
GstElement* Gstreamer::OutputFauxSink          = nullptr ;            // BuildOutputBin()
ValueTree   Gstreamer::ConfigStore             = ValueTree::invalid ; // Initialize()
guintptr    Gstreamer::PreviewXwin             = 0 ;                  // Initialize()


/* Gstreamer private class methods */

bool Gstreamer::Initialize(ValueTree      config_store , void* x_window ,
                           NamedValueSet& disabled_features             )
{
  ConfigStore = config_store ;
  PreviewXwin = (guintptr)x_window ;

DEBUG_TRACE_GST_INIT_PHASE_1

  // initialize gStreamer (NOTE: this will terminate the application on failure)
  InitializeGst(nullptr , nullptr) ;

DEBUG_TRACE_GST_INIT_PHASE_2

  // determine static pipeline macro configuration
  // TODO: ideally it should be robust to always build all bins
  //           with Is*Enabled() vars merely guarding config/re-config
  //       but perhaps it is more efficient to simply not build unused bins
  //       (ASSERT: the 'link bins' section below and Shutdown() reflect the current implementation)
  bool is_media_enabled   = !disabled_features.contains(CONFIG::OUTPUT_ID ) ;
  bool is_screen_enabled  = !disabled_features.contains(CONFIG::SCREEN_ID ) ;
  bool is_camera_enabled  = !disabled_features.contains(CONFIG::CAMERA_ID ) ;
  bool is_text_enabled    = !disabled_features.contains(CONFIG::TEXT_ID   ) ;
  bool is_image_enabled   = !disabled_features.contains(CONFIG::IMAGE_ID  ) ;
  bool is_preview_enabled = !disabled_features.contains(CONFIG::PREVIEW_ID) ;
  bool is_audio_enabled   = !disabled_features.contains(CONFIG::AUDIO_ID  ) ;
  bool is_vmixer_enabled ;

  // assert dependent compositor elements (TODO: remove these restrictions allowing any configuration)
  int n_video_inputs  = ((is_screen_enabled) ? 1 : 0) + ((is_camera_enabled) ? 1 : 0) +
                        ((is_text_enabled  ) ? 1 : 0) + ((is_image_enabled ) ? 1 : 0) ;
  is_vmixer_enabled   = is_media_enabled && n_video_inputs == GST::N_COMPOSITOR_INPUTS ;
  is_preview_enabled  = is_preview_enabled && is_vmixer_enabled ;
  bool is_config_sane = !is_media_enabled || is_vmixer_enabled || n_video_inputs == 1 ;

DEBUG_DUMP_MEDIA_SWITCHES

  if (!is_config_sane) return false ;

  // instantiate pipeline
  if ((is_media_enabled   && !(Pipeline      = NewPipeline(GST::PIPELINE_ID      ))) ||
      (is_screen_enabled  && !(ScreencapBin  = NewBin     (GST::SCREENCAP_BIN_ID ))) ||
      (is_camera_enabled  && !(CameraBin     = NewBin     (GST::CAMERA_BIN_ID    ))) ||
      (is_text_enabled    && !(TextBin       = NewBin     (GST::TEXT_BIN_ID      ))) ||
      (is_image_enabled   && !(ImageBin      = NewBin     (GST::IMAGE_BIN_ID     ))) ||
      (is_vmixer_enabled  && !(CompositorBin = NewBin     (GST::COMPOSITOR_BIN_ID))) ||
      (is_preview_enabled && !(PreviewBin    = NewBin     (GST::PREVIEW_BIN_ID   ))) ||
      (is_audio_enabled   && !(AudioBin      = NewBin     (GST::AUDIO_BIN_ID     ))) ||
      (is_media_enabled   && !(MuxerBin      = NewBin     (GST::MUXER_BIN_ID     ))) ||
      (is_media_enabled   && !(OutputBin     = NewBin     (GST::OUTPUT_BIN_ID    )))  )
  { AvCaster::Error(GUI::GST_PIPELINE_INST_ERROR_MSG) ; return false ; }

  SetMessageHandler(GST_PIPELINE(Pipeline) , (GstBusSyncHandler)HandleMessage) ;

DEBUG_TRACE_GST_INIT_PHASE_3

  // configure pipeline
  if ((is_screen_enabled  && !AddBin(ScreencapBin )) ||
      (is_camera_enabled  && !AddBin(CameraBin    )) ||
      (is_text_enabled    && !AddBin(TextBin      )) ||
      (is_image_enabled   && !AddBin(ImageBin     )) ||
      (is_vmixer_enabled  && !AddBin(CompositorBin)) ||
      (is_preview_enabled && !AddBin(PreviewBin   )) ||
      (is_audio_enabled   && !AddBin(AudioBin     )) ||
      (is_media_enabled   && !AddBin(MuxerBin     )) ||
      (is_media_enabled   && !AddBin(OutputBin    ))  )
  { AvCaster::Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_4 DEBUG_TRACE_DISABLED_BINS

  // configure bins
  if ((is_screen_enabled  && !BuildScreencapBin ()) ||
      (is_camera_enabled  && !BuildCameraBin    ()) ||
      (is_text_enabled    && !BuildTextBin      ()) ||
      (is_image_enabled   && !BuildImageBin     ()) ||
      (is_vmixer_enabled  && !BuildCompositorBin()) ||
      (is_preview_enabled && !BuildPreviewBin   ()) ||
      (is_audio_enabled   && !BuildAudioBin     ()) ||
      (is_media_enabled   && !BuildMuxerBin     ()) ||
      (is_media_enabled   && !BuildOutputBin    ())  )
  { AvCaster::Error(GUI::GST_PIPELINE_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_5

  // link bins
  if (is_vmixer_enabled)
  {
    if ((is_screen_enabled  && !LinkElements(ScreencapBin  , CompositorBin)) ||
        (is_camera_enabled  && !LinkElements(CameraBin     , CompositorBin)) ||
        (is_text_enabled    && !LinkElements(TextBin       , CompositorBin)) ||
        (is_image_enabled   && !LinkElements(ImageBin      , CompositorBin)) ||
        (is_vmixer_enabled  && !LinkElements(CompositorBin , MuxerBin     )) ||
        (is_preview_enabled && !LinkElements(CompositorBin , PreviewBin   ))  )
    { AvCaster::Error(GUI::VMIXER_BIN_LINK_ERROR_MSG) ; return false ; }
  }
  else
  {
    if ((is_screen_enabled && !LinkElements(ScreencapBin , MuxerBin)) ||
        (is_camera_enabled && !LinkElements(CameraBin    , MuxerBin)) ||
        (is_text_enabled   && !LinkElements(TextBin      , MuxerBin)) ||
        (is_image_enabled  && !LinkElements(ImageBin     , MuxerBin))  )
    { AvCaster::Error(GUI::VMIXER_BIN_LINK_ERROR_MSG) ; return false ; }
  }
  if ((is_audio_enabled && !LinkElements(AudioBin , MuxerBin )) ||
      (is_media_enabled && !LinkElements(MuxerBin , OutputBin))  )
  { AvCaster::Error(GUI::MUXER_BIN_LINK_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_6

  // set rolling
  if (!SetState(Pipeline , GST_STATE_PLAYING)) return false ;

DEBUG_TRACE_GST_INIT_PHASE_7
// DEBUG_MAKE_GRAPHVIZ

  return true ;
}

void Gstreamer::Shutdown()
{
// DEBUG_MAKE_GRAPHVIZ

  // TODO: to shut down correctly (flushing the buffers)
  //       gst_element_send_event(Pipeline , gst_event_eos()) ;
  //       then wait for EOS message on bus before setting pipeline state to NULL
// FIXME: setting (ScreencapBin to state null here may cause X to throw error:
//          "ERROR: X returned BadShmSeg (invalid shared segment parameter) for operation Unknown"

  if (!IsInBin(ScreencapBin , ScreenRealSource)) DestroyElement(ScreenRealSource) ;
  if (!IsInBin(ScreencapBin , ScreenFauxSource)) DestroyElement(ScreenFauxSource) ;
  if (!IsInBin(CameraBin    , CameraRealSource)) DestroyElement(CameraRealSource) ;
  if (!IsInBin(CameraBin    , CameraFauxSource)) DestroyElement(CameraFauxSource) ;
  if (!IsInBin(PreviewBin   , PreviewRealSink )) DestroyElement(PreviewRealSink ) ;
  if (!IsInBin(PreviewBin   , PreviewFauxSink )) DestroyElement(PreviewFauxSink ) ;
  if (!IsInBin(AudioBin     , AudioAlsaSource )) DestroyElement(AudioAlsaSource ) ;
  if (!IsInBin(AudioBin     , AudioPulseSource)) DestroyElement(AudioPulseSource) ;
  if (!IsInBin(AudioBin     , AudioJackSource )) DestroyElement(AudioJackSource ) ;
  if (!IsInBin(AudioBin     , AudioFauxSource )) DestroyElement(AudioFauxSource ) ;
  if (!IsInBin(OutputBin    , OutputFileSink  )) DestroyElement(OutputFileSink  ) ;
  if (!IsInBin(OutputBin    , OutputRtmpSink  )) DestroyElement(OutputRtmpSink  ) ;
  if (!IsInBin(OutputBin    , OutputFauxSink  )) DestroyElement(OutputFauxSink  ) ;
  DestroyElement(Pipeline) ;
}

bool Gstreamer::BuildScreencapBin()
{
DEBUG_TRACE_BUILD_SCREENCAP_BIN

  GstElement *initial_source , *converter , *queue ;

  // instantiate elements
  if (!(ScreenRealSource = NewElement(GST::SCREEN_PLUGIN_ID    , "screen-real-source")) ||
      !(ScreenFauxSource = NewElement(GST::TESTVIDEO_PLUGIN_ID , "screen-faux-source")) ||
      !(ScreenCapsfilter = NewElement("capsfilter"             , "screen-capsfilter" )) ||
      !(converter        = NewElement("videoconvert"           , "screen-converter"  )) ||
      !(queue            = NewElement("queue"                  , "screen-queue"      ))  )
  { AvCaster::Error(GUI::SCREENCAP_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  initial_source = ConfigureScreenBin() ;
  ConfigureQueue(queue , 0 , 0 , 0) ;

  // link elements
  if (!AddElement    (ScreencapBin , initial_source  )      ||
      !AddElement    (ScreencapBin , ScreenCapsfilter)      ||
      !AddElement    (ScreencapBin , converter       )      ||
      !AddElement    (ScreencapBin , queue           )      ||
      !LinkElements  (initial_source   , ScreenCapsfilter)  ||
      !LinkElements  (ScreenCapsfilter , converter       )  ||
      !LinkElements  (converter        , queue           )  ||
      !NewGhostSrcPad(ScreencapBin , queue , "screen-source"))
  { AvCaster::Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildCameraBin()
{
DEBUG_TRACE_BUILD_CAMERA_BIN

  GstElement *initial_source , *converter , *queue ;

  // instantiate elements
  if (!(CameraRealSource = NewElement(GST::CAMERA_PLUGIN_ID    , "camera-real-source")) ||
      !(CameraFauxSource = NewElement(GST::TESTVIDEO_PLUGIN_ID , "camera-faux-source")) ||
      !(CameraCapsfilter = NewElement("capsfilter"             , "camera-capsfilter" )) ||
      !(converter        = NewElement("videoconvert"           , "camera-converter"  )) ||
      !(queue            = NewElement("queue"                  , "camera-queue"      ))  )
  { AvCaster::Error(GUI::CAMERA_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  initial_source = ConfigureCameraBin() ;

  // link elements
  if (!AddElement    (CameraBin , initial_source  )        ||
      !AddElement    (CameraBin , CameraCapsfilter)        ||
      !AddElement    (CameraBin , converter       )        ||
      !AddElement    (CameraBin , queue           )        ||
      !LinkElements  (initial_source   , CameraCapsfilter) ||
      !LinkElements  (CameraCapsfilter , converter       ) ||
      !LinkElements  (converter        , queue           ) ||
      !NewGhostSrcPad(CameraBin , queue , "camera-source")  )
  { AvCaster::Error(GUI::CAMERA_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildTextBin()
{
DEBUG_TRACE_BUILD_TEXT_BIN
#ifdef TEXT_BIN_NYI
  return false ;
#endif // TEXT_BIN_NYI

  GstElement *filesrc , *subparser , *source , *converter , *queue ;

//   bool   is_enabled     = bool  (ConfigStore[CONFIG::TEXT_ID         ]) ;
  String motd_text      = STRING(ConfigStore[CONFIG::MOTD_TEXT_ID    ]) ;
  int    text_style_idx = int   (ConfigStore[CONFIG::TEXT_STYLE_ID   ]) ;
  int    text_pos_idx   = int   (ConfigStore[CONFIG::TEXT_POSITION_ID]) ;
//   String display_text   = (is_enabled) ? motd_text : String::empty ;

/* TODO: include custom font
#include <fontconfig/fontconfig.h>
std::string yourFontFilePath = "/home/testUser/bla.ttf"
const FcChar8 * file = (const FcChar8 *)yourFontFilePath.c_str();
FcBool fontAddStatus = FcConfigAppFOntAddFile(FcConfigGetCurrent(),file);
*/

  // instantiate elements
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
/*
  GstElement *source  , *decoder        , *converter ,
             *scaler  , *scaler_filter  ,
             *freezer , *freezer_filter , *queue ;
  GstCaps    *scaler_caps , *freezer_caps ;

  bool   is_enabled       = bool(ConfigStore[CONFIG::IMAGE_ID      ]) ;
  int    interstitial_w   = int (ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int    interstitial_h   = int (ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int    framerate_idx    = int (ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int    framerate        = CONFIG::FRAMERATES[framerate_idx].getIntValue() ;
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
*/
#  else // STATIC_IMAGE

  GstElement *source , *capsfilter , *converter , *queue ;

  // TODO: static image src
  int    interstitial_w = int(ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int    interstitial_h = int(ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int    framerate_idx  = int(ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int    framerate      = CONFIG::FrameRates()[framerate_idx].getIntValue() ;
  String plugin_id      = GST::TESTVIDEO_PLUGIN_ID ;
  String faux_caps_str  = MakeVideoCapsString (interstitial_w , interstitial_h , framerate) ;

//DEBUG_TRACE_CONFIGURE_IMAGE

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "interstitial-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "interstitial-capsfilter" )) ||
      !(converter  = NewElement("videoconvert" , "interstitial-converter"  )) ||
      !(queue      = NewElement("queue"        , "interstitial-queue"      ))  )
  { AvCaster::Error(GUI::IMAGE_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureTestVideo(source , 18           ) ;
  ConfigureCaps(capsfilter  , faux_caps_str) ;

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

  GstElement *screen_queue  , *camera_queue         , *image_queue          ,
#ifndef GST_COMPOSITOR_BUG
             *compositor    , *converter            ,
#else // GST_COMPOSITOR_BUG
             *compositor    ,
#endif // GST_COMPOSITOR_BUG
             *composite_tee , *composite_sink_queue , *composite_thru_queue ;

  // instantiate elements
  if (!(screen_queue         = NewElement("queue"        , "compositor-screen-queue")) ||
      !(camera_queue         = NewElement("queue"        , "compositor-camera-queue")) ||
      !(image_queue          = NewElement("queue"        , "compositor-image-queue" )) ||
      !(compositor           = NewElement("compositor"   , "compositor"             )) ||
#ifndef GST_COMPOSITOR_BUG
      !(CompositorCapsfilter = NewElement("capsfilter"   , "compositor-capsfilter"  )) ||
      !(converter            = NewElement("videoconvert" , "compositor-converter"   )) ||
#endif // GST_COMPOSITOR_BUG
      !(composite_tee        = NewElement("tee"          , "compositor-tee"         )) ||
      !(composite_sink_queue = NewElement("queue"        , "compositor-sink-queue"  )) ||
      !(composite_thru_queue = NewElement("queue"        , "compositor-thru-queue"  ))  )
  { AvCaster::Error(GUI::VMIXER_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureQueue     (screen_queue         , 0    , 0 , 0) ;
  ConfigureQueue     (camera_queue         , 0    , 0 , 0) ;
  ConfigureQueue     (image_queue          , 0    , 0 , 0) ;
  ConfigureCompositor(compositor           , 3           ) ;
  ConfigureQueue     (composite_sink_queue , 0    , 0 , 0) ;
  ConfigureQueue     (composite_thru_queue , 0    , 0 , 0) ;

  // link elements
  if (!AddElement  (CompositorBin , screen_queue        )        ||
      !AddElement  (CompositorBin , camera_queue        )        ||
      !AddElement  (CompositorBin , image_queue         )        ||
      !AddElement  (CompositorBin , compositor          )        ||
#ifndef GST_COMPOSITOR_BUG
      !AddElement  (CompositorBin , CompositorCapsfilter)        ||
      !AddElement  (CompositorBin , converter           )        ||
#endif // GST_COMPOSITOR_BUG
      !AddElement  (CompositorBin , composite_tee       )        ||
      !AddElement  (CompositorBin , composite_sink_queue)        ||
      !AddElement  (CompositorBin , composite_thru_queue)        ||
#ifndef GST_COMPOSITOR_BUG
      !LinkElements(compositor           , CompositorCapsfilter) ||
      !LinkElements(CompositorCapsfilter , converter           ) ||
      !LinkElements(converter            , composite_tee)      )
#else // GST_COMPOSITOR_BUG
      !LinkElements(compositor , composite_tee)            )
#endif // GST_COMPOSITOR_BUG
  { AvCaster::Error(GUI::VMIXER_LINK_ERROR_MSG) ; return false ; }

  // instantiate request pads
  GstPad *composite_tee_thru_srcpad , *composite_tee_monitor_srcpad ;
  if (!NewGhostSinkPad(CompositorBin , screen_queue , "compositor-screen-sink") ||
      !NewGhostSinkPad(CompositorBin , camera_queue , "compositor-camera-sink") ||
      !NewGhostSinkPad(CompositorBin , image_queue  , "compositor-image-sink" ) ||
      !(CompositorScreenSinkpad      = NewRequestSinkPad(compositor   )       ) ||
      !(CompositorCameraSinkpad      = NewRequestSinkPad(compositor   )       ) ||
      !(CompositorImageSinkpad       = NewRequestSinkPad(compositor   )       ) ||
      !(composite_tee_thru_srcpad    = NewRequestSrcPad (composite_tee)       ) ||
      !(composite_tee_monitor_srcpad = NewRequestSrcPad (composite_tee)       )  )
  { AvCaster::Error(GUI::VMIXER_PAD_INIT_ERROR_MSG) ; return false ; }

  // configure sink pads
  ConfigureCompositorBin() ;

  // link ghost pads and request pads
  GstPad *screen_thru_srcpad     , *camera_thru_srcpad     , *image_thru_srcpad ,
         *composite_thru_sinkpad , *composite_sink_sinkpad                      ;
  if (!(screen_thru_srcpad     = NewStaticSrcPad (screen_queue        )     )     ||
      !(camera_thru_srcpad     = NewStaticSrcPad (camera_queue        )     )     ||
      !(image_thru_srcpad      = NewStaticSrcPad (image_queue         )     )     ||
      !(composite_thru_sinkpad = NewStaticSinkPad(composite_thru_queue)     )     ||
      !(composite_sink_sinkpad = NewStaticSinkPad(composite_sink_queue)     )     ||
      !LinkPads      (screen_thru_srcpad           , CompositorScreenSinkpad)     ||
      !LinkPads      (camera_thru_srcpad           , CompositorCameraSinkpad)     ||
      !LinkPads      (image_thru_srcpad            , CompositorImageSinkpad )     ||
      !LinkPads      (composite_tee_thru_srcpad    , composite_thru_sinkpad )     ||
      !LinkPads      (composite_tee_monitor_srcpad , composite_sink_sinkpad )     ||
      !NewGhostSrcPad(CompositorBin , composite_thru_queue , "compositor-source") ||
      !NewGhostSrcPad(CompositorBin , composite_sink_queue , "preview-source"   )  )
  { AvCaster::Error(GUI::VMIXER_PAD_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildPreviewBin()
{
DEBUG_TRACE_BUILD_PREVIEW_BIN

  GstElement* initial_sink ;

  // instantiate elements
  if (!(PreviewQueue    = NewElement("queue"                 , "preview-queue"         )) ||
      !(PreviewRealSink = NewElement(GST::PREVIEW_PLUGIN_ID  , GST::PREVIEW_SINK_ID    )) ||
      !(PreviewFauxSink = NewElement(GST::FAUXSINK_PLUGIN_ID , GST::PREVIEW_FAUXSINK_ID))  )
  { AvCaster::Error(GUI::PREVIEW_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureQueue(PreviewQueue , 0 , 0 , 0) ;
  initial_sink = ConfigurePreviewBin() ;

  // link elements
  if (!AddElement     (PreviewBin , PreviewQueue                          ) ||
      !AddElement     (PreviewBin , initial_sink                          ) ||
      !NewGhostSinkPad(PreviewBin , PreviewQueue , GST::PREVIEW_SINKPAD_ID) ||
      !LinkElements   (PreviewQueue , initial_sink)                          )
  { AvCaster::Error(GUI::PREVIEW_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::BuildAudioBin()
{
DEBUG_TRACE_BUILD_AUDIO_BIN

  GstElement *initial_source , *converter , *queue ;

  // instantiate elements
  if (!(AudioAlsaSource  = NewElement(GST::ALSA_PLUGIN_ID      , "audio-alsa-source" )) ||
      !(AudioPulseSource = NewElement(GST::PULSE_PLUGIN_ID     , "audio-pulse-source")) ||
      !(AudioJackSource  = NewElement(GST::JACK_PLUGIN_ID      , "audio-jack-source" )) ||
      !(AudioFauxSource  = NewElement(GST::TESTAUDIO_PLUGIN_ID , "audio-test-source" )) ||
      !(AudioCaps        = NewElement("capsfilter"             , "audio-capsfilter"  )) ||
      !(converter        = NewElement("audioconvert"           , "audio-converter"   )) ||
      !(queue            = NewElement("queue"                  , "audio-queue"       ))  )
  { AvCaster::Error(GUI::AUDIO_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  initial_source = ConfigureAudioBin() ;
  ConfigureTestAudio(AudioFauxSource) ;
  ConfigureQueue(queue , 0 , 0 , 0) ;

  // link elements
  if (!AddElement    (AudioBin , initial_source)       ||
      !AddElement    (AudioBin , AudioCaps     )       ||
      !AddElement    (AudioBin , converter     )       ||
      !AddElement    (AudioBin , queue         )       ||
      !LinkElements  (initial_source , AudioCaps)      ||
      !LinkElements  (AudioCaps      , converter)      ||
      !LinkElements  (converter      , queue    )      ||
      !NewGhostSrcPad(AudioBin , queue , "audio-source"))
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

  int   output_w          = int(ConfigStore[CONFIG::OUTPUT_W_ID     ]) ;
  int   output_h          = int(ConfigStore[CONFIG::OUTPUT_H_ID     ]) ;
  int   video_bitrate_idx = int(ConfigStore[CONFIG::VIDEO_BITRATE_ID]) ;
  int   audio_bitrate_idx = int(ConfigStore[CONFIG::AUDIO_BITRATE_ID]) ;
  int   framerate_idx     = int(ConfigStore[CONFIG::FRAMERATE_ID    ]) ;
  int   n_channels        = int(ConfigStore[CONFIG::N_CHANNELS_ID   ]) ;
  int   samplerate_idx    = int(ConfigStore[CONFIG::SAMPLERATE_ID   ]) ;
  guint video_bitrate     = CONFIG::VideoBitRates()   [video_bitrate_idx].getIntValue() ;
  guint audio_bitrate     = CONFIG::AudioBitRates()   [audio_bitrate_idx].getIntValue() ;
  int   framerate         = CONFIG::FrameRates()      [framerate_idx    ].getIntValue() ;
  int   samplerate        = CONFIG::AudioSampleRates()[samplerate_idx   ].getIntValue() ;
  String h264_caps_str    = MakeH264CapsString(output_w , output_h , framerate) ;
  String mp3_caps_str     = MakeMp3CapsString(samplerate , n_channels) ;
  String video_caps_str   = h264_caps_str ;
  String audio_caps_str   = mp3_caps_str ;

  if (!(video_in_queue  = NewElement("queue"          , "mux-video-queue"    )) ||
      !(video_converter = NewElement("videoconvert"   , "mux-video-converter")) ||
      !(video_encoder   = NewElement("x264enc"        , "mux-video-encoder"  )) ||
      !(video_parser    = NewElement("h264parse"      , "mux-video-parser"   )) ||
      !(video_enc_caps  = NewElement("capsfilter"     , "mux-video-enc-caps" )) ||
      !(video_enc_queue = NewElement("queue"          , "mux-video-enc-queue")) ||
      !(audio_in_queue  = NewElement("queue"          , "mux-audio-queue"    )) ||
      !(audio_converter = NewElement("audioconvert"   , "audio-converter"    )) ||
      !(audio_encoder   = NewElement("lamemp3enc"     , "mux-audio-encoder"  )) ||
      !(audio_parser    = NewElement("mpegaudioparse" , "mux-audio-parser"   )) ||
      !(audio_enc_caps  = NewElement("capsfilter"     , "mux-audio-enc-caps" )) ||
      !(audio_enc_queue = NewElement("queue"          , "mux-audio-enc-queue")) ||
      !(muxer           = NewElement("flvmux"         , "mux-flvmux"         ))  )
  { AvCaster::Error(GUI::MUXER_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIGURE_MUXER_BIN

  ConfigureX264Encoder(video_encoder   , video_bitrate ) ;
  ConfigureCaps       (video_enc_caps  , video_caps_str) ;
  ConfigureLameEncoder(audio_encoder   , audio_bitrate ) ;
  ConfigureCaps       (audio_enc_caps  , audio_caps_str) ;
  ConfigureQueue      (audio_enc_queue , 0 , 0 , 0     ) ;
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

  GstElement* initial_sink ;

  if (!(OutputQueue    = NewElement("queue"                 , "output-queue"    )) ||
      !(OutputFileSink = NewElement(GST::FILESINK_PLUGIN_ID , "output-file-sink")) ||
      !(OutputRtmpSink = NewElement(GST::RTMPSINK_PLUGIN_ID , "output-rtmp-sink")) ||
      !(OutputFauxSink = NewElement(GST::FAUXSINK_PLUGIN_ID , "output-faux-sink"))  )
  { AvCaster::Error(GUI::OUTPUT_INIT_ERROR_MSG) ; return false ; }

  ConfigureQueue(OutputQueue , 0 , 0 , 0) ;
  initial_sink = ConfigureOutputBin() ;

  if (!AddElement     (OutputBin , OutputQueue )              ||
      !AddElement     (OutputBin , initial_sink)              ||
      !LinkElements   (OutputQueue , initial_sink)            ||
      !NewGhostSinkPad(OutputBin , OutputQueue , "output-sink"))
  { AvCaster::Error(GUI::OUTPUT_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::Reconfigure(const Identifier& config_key)
{
  bool is_config_pending    = AvCaster::GetIsConfigPending() ;
  bool configure_all        = (config_key == CONFIG::PRESET_ID      ||
                               config_key == CONFIG::IS_PENDING_ID) && !is_config_pending ;
  bool configure_screen     =  config_key == CONFIG::SCREEN_ID      || configure_all ;
  bool configure_camera     =  config_key == CONFIG::CAMERA_ID      || configure_all ;
  bool configure_text       =  config_key == CONFIG::TEXT_ID        || configure_all ;
  bool configure_image      =  config_key == CONFIG::IMAGE_ID       || configure_all ;
  bool configure_compositor =  configure_screen || configure_camera ||
                               configure_text   || configure_image  || configure_all ;
  bool configure_preview    =  config_key == CONFIG::PREVIEW_ID     ||
                               config_key == CONFIG::IS_PENDING_ID  || configure_all ;
  bool configure_audio      =  config_key == CONFIG::AUDIO_ID       || configure_all ;
  bool configure_output     =  config_key == CONFIG::OUTPUT_ID      || configure_all ;

DEBUG_TRACE_RECONFIGURE_IN

  SetState(Pipeline , GST_STATE_READY) ;

  bool is_error = (configure_screen     && ConfigureScreenBin()     == nullptr) ||
                  (configure_camera     && ConfigureCameraBin()     == nullptr) ||
                  (configure_text       && ConfigureTextBin()       == nullptr) ||
                  (configure_image      && ConfigureImageBin()      == nullptr) ||
                  (configure_compositor && ConfigureCompositorBin() == false  ) ||
                  (configure_preview    && ConfigurePreviewBin()    == nullptr) ||
                  (configure_audio      && ConfigureAudioBin()      == nullptr) ||
                  (configure_output     && ConfigureOutputBin()     == nullptr)  ;

DEBUG_TRACE_RECONFIGURE_OUT

  // NOTE: an error here should cause Gstreamer::HandleErrorMessage() to fire
  //         which should attempt recovery to a same configuration
  is_error = !SetState(Pipeline , GST_STATE_PLAYING) || is_error ;

// DEBUG_MAKE_GRAPHVIZ

  return !is_error ;
}

GstElement* Gstreamer::ConfigureScreenBin()
{
  bool        is_active       = bool(ConfigStore[CONFIG::SCREEN_ID     ]) ;
  int         screencap_w     = int (ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int         screencap_h     = int (ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int         framerate_idx   = int (ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int         framerate       = CONFIG::FrameRates()[framerate_idx].getIntValue() ;
  String      screen_caps_str = MakeScreenCapsString(screencap_w , screencap_h , framerate) ;
  String      faux_caps_str   = MakeVideoCapsString (screencap_w , screencap_h , framerate) ;
  String      caps_str        = (is_active) ? screen_caps_str  : faux_caps_str ;
  GstElement* next_source     = (is_active) ? ScreenRealSource : ScreenFauxSource ;
  GstElement* current_source  = (IsInBin(ScreencapBin , ScreenRealSource)) ? ScreenRealSource :
                                (IsInBin(ScreencapBin , ScreenFauxSource)) ? ScreenFauxSource :
                                                                             nullptr          ;

DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN

  // configure elements
  ConfigureScreenSource(ScreenRealSource , screencap_w , screencap_h) ;
  ConfigureTestVideo   (ScreenFauxSource , 1                        ) ;
  ConfigureCaps        (ScreenCapsfilter , caps_str                 ) ;

  // swap source elements
  if (IsInBin(ScreencapBin , current_source) && next_source != current_source)
  {
    if (!RemoveElement(ScreencapBin , current_source  ) ||
        !AddElement   (ScreencapBin , next_source     ) ||
        !LinkElements (next_source  , ScreenCapsfilter)  )
    { AvCaster::Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureCameraBin()
{
  // TODO: query device for resolutions (eliminate CONFIG::CAMERA_RESOLUTIONS)
  String      device_path     = AvCaster::GetCameraPath() ;
  int         framerate       = AvCaster::GetCameraRate() ;
  Point<int>  resolution      = AvCaster::GetCameraResolution() ;
  int         camera_w        = resolution.getX() ;
  int         camera_h        = resolution.getY() ;
  bool        is_active       = bool(ConfigStore[CONFIG::CAMERA_ID]) ;
  bool        use_real_src    = is_active && device_path.isNotEmpty() ;
  String      camera_caps_str = MakeCameraCapsString(camera_w , camera_h , framerate) ;
  String      faux_caps_str   = MakeVideoCapsString (camera_w , camera_h , framerate) ;
  String      caps_str        = (use_real_src) ? camera_caps_str  : faux_caps_str ;
  GstElement* next_source     = (use_real_src) ? CameraRealSource : CameraFauxSource ;
  GstElement* current_source  = (IsInBin(CameraBin , CameraRealSource)) ? CameraRealSource :
                                (IsInBin(CameraBin , CameraFauxSource)) ? CameraFauxSource :
                                                                          nullptr          ;

DEBUG_TRACE_CONFIGURE_CAMERA_BIN

  // configure elements
  ConfigureCameraSource(CameraRealSource , device_path) ;
  ConfigureTestVideo   (CameraFauxSource , 0          ) ;
  ConfigureCaps        (CameraCapsfilter , caps_str   ) ;

  // swap source elements
  if (IsInBin(CameraBin , current_source) && next_source != current_source)
  {
    if (!RemoveElement(CameraBin   , current_source  ) ||
        !AddElement   (CameraBin   , next_source     ) ||
        !LinkElements (next_source , CameraCapsfilter)  )
    { AvCaster::Error(GUI::CAMERA_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureTextBin() { return Pipeline ; } // FIXME: should return aTextSource

GstElement* Gstreamer::ConfigureImageBin() { return Pipeline ; } // FIXME: should return anImageSource

bool Gstreamer::ConfigureCompositorBin()
{
  bool       is_screen_active = bool(ConfigStore[CONFIG::SCREEN_ID     ]) ;
  bool       is_camera_active = bool(ConfigStore[CONFIG::CAMERA_ID     ]) ;
#ifndef TEXT_BIN_NYI
  bool       is_text_active   = bool(ConfigStore[CONFIG::TEXT_ID       ]) ;
#endif // TEXT_BIN_NYI
  bool       is_image_active  = bool(ConfigStore[CONFIG::IMAGE_ID      ]) ;
  int        screen_w         = int (ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int        screen_h         = int (ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int        output_w         = int (ConfigStore[CONFIG::OUTPUT_W_ID   ]) ;
  int        output_h         = int (ConfigStore[CONFIG::OUTPUT_H_ID   ]) ;
  int        framerate_idx    = int (ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int        framerate        = CONFIG::FrameRates()[framerate_idx].getIntValue() ;
  Point<int> resolution       = AvCaster::GetCameraResolution() ;
  int        screen_x         = 0 ;
  int        screen_y         = 0 ;
  int        image_w          = output_w ;
  int        image_h          = output_h ;
  int        image_x          = 0 ;
  int        image_y          = 0 ;
  int        camera_w         = resolution.getX() ;
  int        camera_h         = resolution.getY() ;
  int        camera_x         = screen_w - camera_w ;
  int        camera_y         = screen_h - camera_h ;
  int        screen_z         = (  is_screen_active                     )                     ? 2 : 0 ;
  int        camera_z         = ( !is_screen_active ||  is_camera_active)                     ? 3 : 0 ;
  int        image_z          = ((!is_screen_active && !is_camera_active) || is_image_active) ? 4 : 1 ;
  String     caps_str         = MakeVideoCapsString(output_w , output_h , framerate) ;

DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN

#ifdef NO_DYNAMIC_MEDIA_Z_ORDER
image_z = 0 ; screen_z = 1 ; camera_z = 2 ;
#endif // NO_DYNAMIC_MEDIA_Z_ORDER

#ifndef GST_COMPOSITOR_BUG
  ConfigureCaps          (CompositorCapsfilter    , caps_str                      ) ;
#endif // GST_COMPOSITOR_BUG
  ConfigureCompositorSink(CompositorScreenSinkpad , screen_w , screen_h ,
                                                    screen_x , screen_y , screen_z) ;
  ConfigureCompositorSink(CompositorCameraSinkpad , camera_w , camera_h ,
                                                    camera_x , camera_y , camera_z) ;
  ConfigureCompositorSink(CompositorImageSinkpad  , image_w  , image_h  ,
                                                    image_x  , image_y  , image_z ) ;

  return true ;
}

GstElement* Gstreamer::ConfigurePreviewBin()
{
  GstElement *current_sink , *next_sink ;

  bool is_active = AvCaster::GetIsPreviewActive() ;
  current_sink   = (IsInBin(PreviewBin , PreviewRealSink)) ? PreviewRealSink :
                   (IsInBin(PreviewBin , PreviewFauxSink)) ? PreviewFauxSink : nullptr ;
  next_sink      = (is_active) ? PreviewRealSink : PreviewFauxSink ;

DEBUG_TRACE_CONFIGURE_PREVIEW_BIN

  // configure elements
  if (!ConfigureVideoSink(PreviewRealSink) && is_active)
    AvCaster::Error(GUI::GST_XWIN_ERROR_MSG) ;

  // swap sink elements
  if (IsInBin(PreviewBin , current_sink) && next_sink != current_sink)
  {
    if (!RemoveElement(PreviewBin   , current_sink) ||
        !AddElement   (PreviewBin   , next_sink   ) ||
        !LinkElements (PreviewQueue , next_sink   )  )
    { AvCaster::Error(GUI::PREVIEW_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_sink ;
}

GstElement* Gstreamer::ConfigureAudioBin()
{
  GstElement *current_source , *next_source ;
  String      caps_str ;

  // TODO: JACK init fails if samplerate mismatch (issue #37)
  bool   is_enabled       = bool(ConfigStore[CONFIG::AUDIO_ID     ]) ;
  int    audio_api_idx    = int (ConfigStore[CONFIG::AUDIO_API_ID ]) ;
  int    n_channels       = int (ConfigStore[CONFIG::N_CHANNELS_ID]) ;
  int    samplerate_idx   = int (ConfigStore[CONFIG::SAMPLERATE_ID]) ;
  int    samplerate       = CONFIG::AudioSampleRates()[samplerate_idx].getIntValue() ;
  String audio16_caps_str = MakeAudioCapsString("S16LE" , samplerate , n_channels) ;
  String audio32_caps_str = MakeAudioCapsString("F32LE" , samplerate , n_channels) ;

  current_source = (IsInBin(AudioBin , AudioAlsaSource )) ? AudioAlsaSource  :
                   (IsInBin(AudioBin , AudioPulseSource)) ? AudioPulseSource :
                   (IsInBin(AudioBin , AudioJackSource )) ? AudioJackSource  :
                   (IsInBin(AudioBin , AudioFauxSource )) ? AudioFauxSource  : nullptr ;

  if (!is_enabled) audio_api_idx = CONFIG::INVALID_IDX ;
  switch ((CONFIG::AudioApi)audio_api_idx)
  {
    case CONFIG::ALSA_AUDIO_IDX:  next_source = AudioAlsaSource ;  caps_str = audio16_caps_str ; break ;
    case CONFIG::PULSE_AUDIO_IDX: next_source = AudioPulseSource ; caps_str = audio16_caps_str ; break ;
    case CONFIG::JACK_AUDIO_IDX:  next_source = AudioJackSource ;  caps_str = audio32_caps_str ; break ;
    default:                      next_source = AudioFauxSource ;  caps_str = audio16_caps_str ; break ;
  }

DEBUG_TRACE_CONFIGURE_AUDIO_BIN

  // configure elements
  ConfigureCaps(AudioCaps , caps_str) ;

  // swap source elements
  if (IsInBin(AudioBin , current_source) && current_source != next_source)
  {
    if (!RemoveElement(AudioBin    , current_source) ||
        !AddElement   (AudioBin    , next_source   ) ||
        !LinkElements (next_source , AudioCaps     )  )
    { AvCaster::Error(GUI::AUDIO_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_source ;
}

GstElement* Gstreamer::ConfigureOutputBin()
{
  bool        is_enabled   = bool  (ConfigStore[CONFIG::OUTPUT_ID      ]) ;
  int         muxer_idx    = int   (ConfigStore[CONFIG::OUTPUT_MUXER_ID]) ;
  int         sink_idx     = int   (ConfigStore[CONFIG::OUTPUT_SINK_ID ]) ;
  String      destination  = STRING(ConfigStore[CONFIG::OUTPUT_DEST_ID ]) ;
  String      file_ext     = CONFIG::OutputMuxers()[muxer_idx] ;
  String      file_url     = MakeFileName(destination , file_ext) ;
  String      rtmp_url     = MakeRtmpUrl (destination) ;
  GstElement* current_sink = (IsInBin(OutputBin , OutputFileSink)) ? OutputFileSink :
                             (IsInBin(OutputBin , OutputRtmpSink)) ? OutputRtmpSink :
                             (IsInBin(OutputBin , OutputFauxSink)) ? OutputFauxSink :
                                                                     nullptr        ;
  GstElement* next_sink ; String output_url ;

#ifdef DISABLE_OUTPUT
UNUSED(is_enabled) ; is_enabled = (false) ? (bool)0 : false ;
#endif // DISABLE_OUTPUT

  if (!is_enabled) sink_idx = -1 ;
  switch ((CONFIG::OutputStream)sink_idx)
  {
    case CONFIG::FILE_OUTPUT_IDX: next_sink = OutputFileSink ; output_url = file_url ; break ;
    case CONFIG::RTMP_OUTPUT_IDX: next_sink = OutputRtmpSink ; output_url = rtmp_url ; break ;
    default:                      next_sink = OutputFauxSink ; is_enabled = false ;    break ;
  }

DEBUG_TRACE_CONFIGURE_OUTPUT_BIN

  // configure elements
  if (is_enabled) ConfigureFileSink(next_sink , output_url) ;

  // swap sink elements
  if (IsInBin(OutputBin , current_sink) && next_sink != current_sink)
  {
    if (!RemoveElement(OutputBin   , current_sink) ||
        !AddElement   (OutputBin   , next_sink   ) ||
        !LinkElements (OutputQueue , next_sink   )  )
    { AvCaster::Error(GUI::OUTPUT_LINK_ERROR_MSG) ; return nullptr ; }
  }

  return next_sink ;
}

void Gstreamer::ConfigureCaps(GstElement* a_capsfilter , String caps_str)
{
DEBUG_TRACE_CONFIGURE_CAPS

  g_object_set(G_OBJECT(a_capsfilter) , "caps" , NewCaps(caps_str) , NULL) ;
}

void Gstreamer::ConfigureQueue(GstElement* a_queue  , guint max_bytes  ,
                               guint64     max_time , guint max_buffers)
{
DEBUG_TRACE_CONFIGURE_QUEUE

  g_object_set(G_OBJECT(a_queue) , "max-size-bytes"   , max_bytes   , NULL) ;
  g_object_set(G_OBJECT(a_queue) , "max-size-time"    , max_time    , NULL) ;
  g_object_set(G_OBJECT(a_queue) , "max-size-buffers" , max_buffers , NULL) ;
}

void Gstreamer::ConfigureScreenSource(GstElement* a_screen_source , guint capture_w , guint capture_h)
{
DEBUG_TRACE_CONFIGURE_SCREEN

  g_object_set(G_OBJECT(a_screen_source) , "endx"       , capture_w - 1 , NULL) ;
  g_object_set(G_OBJECT(a_screen_source) , "endy"       , capture_h - 1 , NULL) ;
  g_object_set(G_OBJECT(a_screen_source) , "use-damage" , false         , NULL) ;
}

void Gstreamer::ConfigureCameraSource(GstElement* a_camera_source , String device_path)
{
DEBUG_TRACE_CONFIGURE_CAMERA

  g_object_set(G_OBJECT(a_camera_source) , "device" , CHARSTAR(device_path) , NULL) ;
}

void Gstreamer::ConfigureTestVideo(GstElement* a_test_source , guint pattern_n)
{
DEBUG_TRACE_CONFIGURE_TEST_VIDEO

  g_object_set(G_OBJECT(a_test_source) , "is_live" , (gboolean)true       , NULL) ;
  g_object_set(G_OBJECT(a_test_source) , "pattern" , (guint   )pattern_n  , NULL) ;
}

void Gstreamer::ConfigureTextSource(GstElement* a_text_source , String font_desc)
{
DEBUG_TRACE_CONFIGURE_TEXT

  g_object_set(G_OBJECT(a_text_source) , "font-desc" , CHARSTAR(font_desc) , NULL) ;
}

void Gstreamer::ConfigureFileSource(GstElement* a_file_source , String location)
{
DEBUG_TRACE_CONFIGURE_FILE_SOURCE

  g_object_set(G_OBJECT(a_file_source) , "location" , CHARSTAR(location) , NULL) ;
}

void Gstreamer::ConfigureFileSink(GstElement* a_file_sink , String location)
{
DEBUG_TRACE_CONFIGURE_FILE_SINK

  g_object_set(G_OBJECT(a_file_sink) , "location" , CHARSTAR(location) , NULL) ;
}

void Gstreamer::ConfigureCompositor(GstElement* a_compositor , guint background_n)
{
DEBUG_TRACE_CONFIGURE_COMPOSITOR

  g_object_set(G_OBJECT(a_compositor) , "background" , background_n , NULL) ;
}

void Gstreamer::ConfigureCompositorSink(GstPad* sinkpad , gint w , gint h ,
                                                          gint x , gint y , gint z)
{
DEBUG_TRACE_CONFIGURE_COMPOSITOR_SINK

  g_object_set(G_OBJECT(sinkpad) , "width"  , w , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "height" , h , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "xpos"   , x , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "ypos"   , y , NULL) ;
  g_object_set(G_OBJECT(sinkpad) , "zorder" , z , NULL) ;
}

bool Gstreamer::ConfigureVideoSink(GstElement* a_video_sink)
{
  bool           is_active       = AvCaster::GetIsPreviewActive() ;
  Rectangle<int> preview_bounds  = AvCaster::GetPreviewBounds() ;
  guintptr       x_window_handle = (is_active) ? PreviewXwin : 0 ;
  gint           preview_x       = preview_bounds.getX() ;
  gint           preview_y       = preview_bounds.getY() ;
  gint           preview_w       = preview_bounds.getWidth() ;
  gint           preview_h       = preview_bounds.getHeight() ;

DEBUG_TRACE_CONFIGURE_PREVIEW

  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(a_video_sink) , x_window_handle) ;
//   gst_video_overlay_expose(GST_VIDEO_OVERLAY(a_video_sink)) ;
//   g_object_set(a_video_sink , "async-handling" , TRUE , NULL) ;

  return gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(a_video_sink) ,
                                                preview_x , preview_y           ,
                                                preview_w , preview_h           ) ;
}

void Gstreamer::ConfigureTestAudio(GstElement* a_test_source)
{
DEBUG_TRACE_CONFIGURE_TEST_AUDIO

 g_object_set(G_OBJECT(a_test_source) , "is_live" , true , NULL) ;
 g_object_set(G_OBJECT(a_test_source) , "volume"  , 0.1  , NULL) ;
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

bool Gstreamer::InitializeGst(int *argc , char **argv[]) { gst_init(nullptr , nullptr) ; }

GstBusSyncReply Gstreamer::HandleMessage(GstBus*      message_bus , GstMessage* message ,
                                         GstPipeline* pipeline                          )
{
  switch (GST_MESSAGE_TYPE(message))
  {
    case GST_MESSAGE_ERROR:         HandleErrorMessage(message) ;     break ;
    case GST_MESSAGE_EOS:           DEBUG_TRACE_MESSAGE_EOS           break ;
    case GST_MESSAGE_STATE_CHANGED: DEBUG_TRACE_MESSAGE_STATE_CHANGED break ;
    case GST_MESSAGE_STREAM_STATUS: DEBUG_TRACE_DUMP_MESSAGE_STRUCT   break ;
    default:                        DEBUG_TRACE_MESSAGE_UNHANDLED     break ;
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
  String warning_msg         = String::empty ;
  bool   is_alsa_init_error  = error_message == GST::ALSA_INIT_ERROR ;
  bool   is_pulse_init_error = error_message == GST::PULSE_INIT_ERROR ;
  bool   is_jack_init_error  = error_message == GST::JACK_INIT_ERROR ;
  bool   is_xv_init_error    = error_message == GST::XV_INIT_ERROR ;
  bool   is_file_sink_error  = error_message == GST::FILE_SINK_ERROR ;

DEBUG_TRACE_GST_ERROR_MESSAGE

  // disable control toggle and re-configure with null source or sink
  if (is_alsa_init_error || is_pulse_init_error || is_jack_init_error)
  {
    AvCaster::DeactivateControl(CONFIG::AUDIO_ID) ; ConfigureAudioBin() ;

    warning_msg = (is_alsa_init_error ) ? GUI::ALSA_INIT_ERROR_MSG  :
                  (is_pulse_init_error) ? GUI::PULSE_INIT_ERROR_MSG :
                  (is_jack_init_error ) ? GUI::JACK_INIT_ERROR_MSG  : String::empty ;
  }
  else if (is_xv_init_error)
  {
    AvCaster::DeactivateControl(CONFIG::PREVIEW_ID) ; ConfigurePreviewBin() ;

    warning_msg = GUI::XV_INIT_ERROR_MSG ;
  }
  else if (is_file_sink_error)
  {
    AvCaster::DeactivateControl(CONFIG::OUTPUT_ID) ; ConfigureOutputBin() ;

    warning_msg = GUI::FILE_SINK_ERROR_MSG ;
  }

else { DEBUG_MAKE_GRAPHVIZ }

  // alert user
  if (warning_msg.isNotEmpty()) AvCaster::Warning(warning_msg + error_message) ;

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
  GstBus* message_bus ;

  if (!GST_IS_ELEMENT(pipeline)                               ||
      !GST_IS_BUS(message_bus = gst_pipeline_get_bus(pipeline)))
  { AvCaster::Error(GUI::GST_BUS_INST_ERROR_MSG) ; return ; }

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

#ifdef JUCE_DEBUG
// FIXME: on shutdown --> GStreamer-CRITICAL **: gst_object_unref: assertion '((GObject *) object)->ref_count > 0' failed
if (an_element != NULL) { gchar* element_name = gst_element_get_name(an_element) ;
                          DBG("Gstreamer::DestroyElement(" + String(element_name) +
                              ") refcount=" + String(GST_OBJECT_REFCOUNT_VALUE(an_element))) ;
                          g_free(element_name) ; }
#endif // JUCE_DEBUG

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

/*
bool Gstreamer::RemoveBin(GstElement* a_bin)
{
DEBUG_TRACE_REMOVE_BIN_IN

  bool is_err = !IsInPipeline(a_bin) || !gst_bin_remove(GST_BIN(Pipeline) , a_bin) ;

DEBUG_TRACE_REMOVE_BIN_OUT

  return !is_err ;
}
*/

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
  const gchar* private_id = UTF8(template_id) ;
  GstPad*      private_pad ;

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
  const gchar* private_id = UTF8(template_id) ;
  GstPad*      private_pad ;

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

String Gstreamer::MakeFileName(String destination , String file_ext)
{
  String filename    = (destination.isEmpty()) ? APP::APP_NAME         :
                       destination.upToLastOccurrenceOf(file_ext , false , true) ;
  File   output_file = APP::videosDir().getNonexistentChildFile(filename , file_ext , false) ;

  return output_file.getFullPathName() ;
}

String Gstreamer::MakeRtmpUrl(String destination)
{
  bool   is_lctv = AvCaster::GetPresetIdx() == CONFIG::LCTV_PRESET_IDX ;
  String env_url = std::getenv("AVCASTER_RTMP_DEST") ;
//   String env_url = SystemStats::getEnvironmentVariable("AVCASTER_RTMP_DEST" , "") ;
  destination    = destination.retainCharacters(APP::VALID_URI_CHARS) ;

  if (destination.isEmpty()) destination = env_url ;
  if (destination.isEmpty()) AvCaster::Error(GUI::OUTPUT_INIT_ERROR_MSG) ;

  if (is_lctv)
  {
    // trim input allowing either stream key or full url
    if (destination.contains(GST::LCTV_RTMP_URL))
      destination = destination.fromFirstOccurrenceOf(GST::LCTV_RTMP_URL , false , true) ;
    if (destination.contains(" live=1"         ))
      destination = destination.upToLastOccurrenceOf (" live=1"          , false , true) ;
    destination = GST::LCTV_RTMP_URL + destination + " live=1" ;
  }

  return destination ;
}

String Gstreamer::VersionMsg()
{
  guint major_version , minor_version , micro_version , nano_version ;

  gst_version(&major_version , &minor_version , &micro_version , &nano_version) ;

  return "gStreamer v" + String(major_version) + "." + String(minor_version) +
                   "." + String(micro_version) + "." + String(nano_version ) ;
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

// bool Gstreamer::IsPlaying() { return !!Pipeline && GST_STATE(Pipeline) == GST_STATE_PLAYING ; }

bool Gstreamer::IsInPipeline(GstElement* an_element)
{
  return IsInBin(Pipeline , an_element) ;
}

bool Gstreamer::IsInBin(GstElement* a_parent_element , GstElement* a_child_element)
{
  return !!a_child_element && !!a_parent_element                &&
         GST_ELEMENT_PARENT(a_child_element) == a_parent_element ;
}
