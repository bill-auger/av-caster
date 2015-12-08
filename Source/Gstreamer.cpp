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

GstElement* Gstreamer::Pipeline        = nullptr ;
GstElement* Gstreamer::ScreencapBin    = nullptr ;
GstElement* Gstreamer::CameraBin       = nullptr ;
GstElement* Gstreamer::TextBin         = nullptr ;
GstElement* Gstreamer::InterstitialBin = nullptr ;
GstElement* Gstreamer::CompositorBin   = nullptr ;
GstElement* Gstreamer::PreviewBin      = nullptr ;
GstElement* Gstreamer::PreviewSink     = nullptr ;
GstElement* Gstreamer::AudioBin        = nullptr ;
GstElement* Gstreamer::MuxerBin        = nullptr ;
GstElement* Gstreamer::OutputBin       = nullptr ;
ValueTree   Gstreamer::ConfigStore ;               // Configure()


/* GstElement private class methods */

bool Gstreamer::Initialize()
{
DEBUG_TRACE_GST_INIT_PHASE_1

  // initialize gStreamer (NOTE: this will terminate the app on failure)
  gst_init(nullptr , nullptr) ;

DEBUG_TRACE_GST_INIT_PHASE_2

  // instantiate pipeline
  if (!(Pipeline        = NewPipeline(GST::PIPELINE_ID        )) ||
      !(ScreencapBin    = NewBin     (GST::SCREENCAP_BIN_ID   )) ||
      !(CameraBin       = NewBin     (GST::CAMERA_BIN_ID      )) ||
      !(TextBin         = NewBin     (GST::TEXT_BIN_ID        )) ||
      !(InterstitialBin = NewBin     (GST::INTERSTITIAL_BIN_ID)) ||
      !(CompositorBin   = NewBin     (GST::COMPOSITOR_BIN_ID  )) ||
      !(PreviewBin      = NewBin     (GST::PREVIEW_BIN_ID     )) ||
      !(AudioBin        = NewBin     (GST::AUDIO_BIN_ID       )) ||
      !(MuxerBin        = NewBin     (GST::MUXER_BIN_ID       )) ||
      !(OutputBin       = NewBin     (GST::OUTPUT_BIN_ID      ))  )
  { AvCaster::Error(GUI::GST_PIPELINE_INST_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_3

  // configure pipeline
  if (!AddBin(ScreencapBin   ) || !AddBin(CameraBin    ) || !AddBin(TextBin   ) ||
      !AddBin(InterstitialBin) || !AddBin(CompositorBin) || !AddBin(PreviewBin) ||
      !AddBin(AudioBin       ) || !AddBin(MuxerBin     ) || !AddBin(OutputBin )  )
  { AvCaster::Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_GST_INIT_PHASE_4

  // configure elements
  if (!InitializePipeline()) return false ;

DEBUG_TRACE_GST_INIT_PHASE_5

  // set rolling
  if (!SetState(Pipeline , GST_STATE_PLAYING)) return false ;

// FIXME: this is a kludge for an exploratory implementation of Reconfigure()
#ifdef DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
if (!bool(ConfigStore[CONFIG::IS_PREVIEW_ON_ID])) RemoveBin(PreviewBin) ;
#endif // DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
#ifdef DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE
if (!bool(ConfigStore[CONFIG::IS_OUTPUT_ON_ID]))  RemoveBin(OutputBin) ;
#endif // DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE

DEBUG_TRACE_GST_INIT_PHASE_6
DEBUG_MAKE_GRAPHVIZ

  return true ;
}

void Gstreamer::Shutdown()
{
  // cleanup gStreamer
  // TODO: to shut down correctly (flushing the buffers)
  //       gst_element_send_event(Pipeline , gst_event_eos()) ;
  //       then wait for EOS message on bus before setting pipeline state to NULL
// FIXME: setting (ScreencapBin to state null here cause x to throw error:
//          "ERROR: X returned BadShmSeg (invalid shared segment parameter) for operation Unknown"

  if (!IsInPipeline(OutputBin      )) SetState(OutputBin        , GST_STATE_NULL) ;
  if (!IsInPipeline(MuxerBin       )) SetState(MuxerBin         , GST_STATE_NULL) ;
  if (!IsInPipeline(AudioBin       )) SetState(AudioBin         , GST_STATE_NULL) ;
  if (!IsInPipeline(PreviewBin     )) SetState(PreviewBin       , GST_STATE_NULL) ;
  if (!IsInPipeline(CompositorBin  )) SetState(CompositorBin    , GST_STATE_NULL) ;
  if (!IsInPipeline(InterstitialBin)) SetState(InterstitialBin  , GST_STATE_NULL) ;
  if (!IsInPipeline(TextBin        )) SetState(TextBin          , GST_STATE_NULL) ;
  if (!IsInPipeline(CameraBin      )) SetState(CameraBin        , GST_STATE_NULL) ;
  if (!IsInPipeline(ScreencapBin   )) SetState(ScreencapBin     , GST_STATE_NULL) ;
  DeleteElement(Pipeline) ;

  ConfigStore = ValueTree::invalid ;
}

bool Gstreamer::InitializePipeline()
{
DEBUG_TRACE_INITIALIZE_PIPELINE

  if (!IsInitialized()) return false ;

  ConfigStore = AvCaster::GetConfigStore() ;

  if (!ConfigureCompositorBin() || !ConfigureMuxerBin()        ||
      !ConfigureScreencapBin()  || !ConfigureCameraBin()       ||
      !ConfigureTextBin()       || !ConfigureInterstitialBin() ||
      !ConfigurePreviewBin()    || !ConfigureAudioBin()        ||
      !ConfigureOutputBin()                                     )
  { AvCaster::Error(GUI::GST_PIPELINE_INIT_ERROR_MSG) ; return false ; }

  return true ;
}
/*
bool Gstreamer::ConfigurePipeline()
{
DEBUG_TRACE_CONFIGURE_PIPELINE

  if (!IsInitialized()) return false ;

  ConfigStore = AvCaster::GetConfigStore() ;

  if (!ConfigureCompositor() || !ConfigureMuxer() || !ConfigureScreencap()    ||
      !ConfigureCamera()     || !ConfigureText()  || !ConfigureInterstitial() ||
      !ConfigurePreview()    || !ConfigureAudio() || !ConfigureOutput()        )
  { AvCaster::Error(GUI::GST_CONFIG_ERROR_MSG) ; return false ; }

  return true ;
}
*/
bool Gstreamer::ConfigureScreencapBin()
{
  GstElement *source , *capsfilter , *converter , *queue ;
  GstCaps    *caps ;

  bool   is_enabled  = bool(ConfigStore[CONFIG::IS_SCREENCAP_ON_ID]) ;
  int    screencap_w = int (ConfigStore[CONFIG::SCREENCAP_W_ID    ]) ;
  int    screencap_h = int (ConfigStore[CONFIG::SCREENCAP_H_ID    ]) ;
  int    framerate_n = int (ConfigStore[CONFIG::FRAMERATE_ID      ]) ;
  int    framerate   = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
#if JUCE_LINUX
  String plugin_id   = GST::NIX_SCREEN_PLUGIN_ID ;
  String caps_str    = MakeScreenCapsString(screencap_w , screencap_h , framerate) ;
#endif // JUCE_LINUX

#ifdef FAUX_SCREEN
UNUSED(is_enabled) ; is_enabled = false ;
#endif // FAUX_SCREEN

  if (!is_enabled)
  {
    plugin_id = GST::FAUX_VIDEO_PLUGIN_ID ;
    caps_str  = MakeVideoCapsString(screencap_w , screencap_h , framerate) ;
  }

DEBUG_TRACE_CONFIGURE_SCREENCAP_BIN

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "screen-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "screen-capsfilter" )) ||
      !(converter  = NewElement("videoconvert" , "screen-converter"  )) ||
      !(queue      = NewElement("queue"        , "screen-queue"      )) ||
      !(caps       = NewCaps   (caps_str)                             )  )
  { AvCaster::Error(GUI::SCREENCAP_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureScreen(source     , screencap_w , screencap_h , 1 , is_enabled) ;
  ConfigureCaps  (capsfilter , caps                                      ) ;
  ConfigureQueue (queue      , 0           , 0           , 0             ) ;

  // link elements
  if (!AddElement    (ScreencapBin , source    )              ||
      !AddElement    (ScreencapBin , capsfilter)              ||
      !AddElement    (ScreencapBin , converter )              ||
      !AddElement    (ScreencapBin , queue     )              ||
      !LinkElements  (source       , capsfilter   )           ||
      !LinkElements  (capsfilter   , converter    )           ||
      !LinkElements  (converter    , queue        )           ||
      !NewGhostSrcPad(ScreencapBin , queue , "screen-source") ||
      !LinkElements  (ScreencapBin , CompositorBin)            )
  { AvCaster::Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigureCameraBin()
{
  GstElement* source , *capsfilter , *converter , *queue ;
  GstCaps*    caps ;

  // TODO: query device for resolutions (eliminate CONFIG::CAMERA_RESOLUTIONS)
  String      device_path = AvCaster::GetCameraPath() ;
  int         framerate   = AvCaster::GetCameraRate() ;
  String      resolution  = AvCaster::GetCameraResolution() ;
  bool        is_enabled  = bool(ConfigStore[CONFIG::IS_CAMERA_ON_ID]) &&
                            device_path.isNotEmpty()                    ;
  StringArray res_tokens  = StringArray::fromTokens(resolution , "x" , "") ;
  int         camera_w    = res_tokens[0].getIntValue() ;
  int         camera_h    = res_tokens[1].getIntValue() ;
#if JUCE_LINUX
  String      plugin_id   = GST::V4L2_PLUGIN_ID ;
  String      caps_str    = MakeCameraCapsString(camera_w , camera_h , framerate) ;
#else // JUCE_LINUX
  UNUSED(camera_w) ; UNUSED(camera_h) ; UNUSED(framerate) ;
#endif // JUCE_LINUX

#ifdef FAUX_CAMERA
UNUSED(is_enabled) ; is_enabled = false ; // TODO: GUI support
#endif // FAUX_CAMERA

  if (!is_enabled)
  {
    plugin_id = GST::FAUX_VIDEO_PLUGIN_ID ;
    caps_str  = MakeVideoCapsString(160 , 120 , 12) ;
  }

DEBUG_TRACE_CONFIGURE_CAMERA_BIN

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "camera-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "camera-capsfilter" )) ||
      !(converter  = NewElement("videoconvert" , "camera-converter"  )) ||
      !(queue      = NewElement("queue"        , "camera-queue"      )) ||
      !(caps       = NewCaps   (caps_str)                             )  )
  { AvCaster::Error(GUI::CAMERA_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureCamera(source     , device_path , 0 , is_enabled) ;
  ConfigureCaps  (capsfilter , caps                        ) ;

  // link elements
  if (!AddElement    (CameraBin , source    )              ||
      !AddElement    (CameraBin , capsfilter)              ||
      !AddElement    (CameraBin , converter )              ||
      !AddElement    (CameraBin , queue     )              ||
      !LinkElements  (source     , capsfilter   )          ||
      !LinkElements  (capsfilter , converter    )          ||
      !LinkElements  (converter  , queue        )          ||
      !NewGhostSrcPad(CameraBin , queue , "camera-source") ||
      !LinkElements  (CameraBin  , CompositorBin)           )
  { AvCaster::Error(GUI::CAMERA_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigureTextBin()
{
#if CONFIGURE_TEXT_BIN

  GstElement *filesrc , *subparser , *source , *converter , *queue ;

  bool   is_enabled   = bool  (ConfigStore[CONFIG::IS_TEXT_ON_ID]) ;
  String motd_text    = STRING(ConfigStore[CONFIG::MOTD_TEXT_ID ]) ;
  int    text_style_n = int   (ConfigStore[CONFIG::TEXT_STYLE_ID]) ;
  int    text_pos_n   = int   (ConfigStore[CONFIG::TEXT_POS_ID  ]) ;

DEBUG_TRACE_CONFIGURE_TEXT_BIN

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

  // configure elements
  ConfigureText(source  , "Purisa Normal 40"            ) ;
  ConfigureFile(filesrc , "/code/av-caster/deleteme.srt") ;

  // link elements
  if (!AddElement    (TextBin , filesrc  )             ||
      !AddElement    (TextBin , subparser)             ||
      !AddElement    (TextBin , source   )             ||
      !AddElement    (TextBin , converter)             ||
      !AddElement    (TextBin , queue    )             ||
      !LinkElements  (filesrc   , subparser    )       ||
      !LinkElements  (subparser , source       )       ||
      !LinkElements  (source    , converter    )       ||
      !LinkElements  (converter , queue        )       ||
      !NewGhostSrcPad(TextBin , queue , "text-source") ||
      !LinkElements  (TextBin   , CompositorBin)        )
  { AvCaster::Error(GUI::TEXT_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_TEXT_BIN
#  ifdef DEBUG
Trace::TraceState("bypassing text configuration") ;
#  endif // DEBUG
#endif // CONFIGURE_TEXT_BIN

  return true ;
}

bool Gstreamer::ConfigureInterstitialBin()
{
#if CONFIGURE_INTERSTITIAL_BIN

//#define STATIC_INTERSTITIAL
#  ifdef STATIC_INTERSTITIAL

  GstElement *source  , *decoder        , *converter ,
             *scaler  , *scaler_filter  ,
             *freezer , *freezer_filter , *queue ;
  GstCaps    *scaler_caps , *freezer_caps ;

  bool   is_enabled       = bool(ConfigStore[CONFIG::IS_INTERSTITIAL_ON_ID]) ;
  int    interstitial_w   = int (ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int    interstitial_h   = int (ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int    framerate_n      = int (ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
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

DEBUG_TRACE_CONFIGURE_INTERSTITIAL_BIN

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
  { AvCaster::Error(GUI::INTERSTITIAL_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureFile (source         , image_filename        ) ;
  ConfigureCaps (scaler_filter  , scaler_caps           ) ;
  ConfigureCaps (freezer_filter , freezer_caps          ) ;
  ConfigureQueue(queue          , 0              , 0 , 0) ;

  // link elements
  if (!AddElement    (CameraBin , source        )                ||
      !AddElement    (CameraBin , decoder       )                ||
      !AddElement    (CameraBin , converter     )                ||
      !AddElement    (CameraBin , scaler        )                ||
      !AddElement    (CameraBin , scaler_filter )                ||
      !AddElement    (CameraBin , freezer       )                ||
      !AddElement    (CameraBin , freezer_filter)                ||
      !AddElement    (CameraBin , queue         )                ||
      !LinkElements  (source         , decoder       )           ||
      !LinkElements  (decoder        , converter     )           ||
      !LinkElements  (converter      , scaler        )           ||
      !LinkElements  (scaler         , scaler_filter )           ||
      !LinkElements  (scaler_filter  , freezer       )           ||
      !LinkElements  (freezer        , freezer_filter)           ||
      !LinkElements  (freezer_filter , queue         )           ||
      !NewGhostSrcPad(CameraBin , queue , "interstitial-source") ||
      !LinkElements  (CameraBin      , CompositorBin )            )
  { AvCaster::Error(GUI::INTERSTITIAL_LINK_ERROR_MSG) ; return false ; }

#  else // STATIC_INTERSTITIAL

  GstElement *source , *capsfilter , *converter , *queue ;
  GstCaps    *caps ;

  // TODO: static image src
  int    interstitial_w = int(ConfigStore[CONFIG::SCREENCAP_W_ID]) ;
  int    interstitial_h = int(ConfigStore[CONFIG::SCREENCAP_H_ID]) ;
  int    framerate_n    = int(ConfigStore[CONFIG::FRAMERATE_ID  ]) ;
  int    framerate      = CONFIG::FRAMERATES[framerate_n].getIntValue() ;
  String plugin_id      = GST::FAUX_VIDEO_PLUGIN_ID ;
  String caps_str       = String("video/x-raw, ")                                  +
                          "width=(int)"          + String(interstitial_w) + ", "   +
                          "height=(int)"         + String(interstitial_h) + ", "   +
                          "framerate=(fraction)" + String(framerate     ) + "/1, " +
                          "format=I420, "                                          +
                          "pixel-aspect-ratio=(fraction)1/1, "                     +
                          "interlace-mode=(string)progressive"                     ;

//DEBUG_TRACE_CONFIGURE_INTERSTITIAL

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "interstitial-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "interstitial-capsfilter" )) ||
      !(converter  = NewElement("videoconvert" , "interstitial-converter"  )) ||
      !(queue      = NewElement("queue"        , "interstitial-queue"      )) ||
      !(caps       = NewCaps   (caps_str)                                   )  )
  { AvCaster::Error(GUI::INTERSTITIAL_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  ConfigureFauxVideo(source , 1) ;
  ConfigureCaps(capsfilter , caps) ;

  // link elements
  if (!AddElement    (InterstitialBin , source    )                    ||
      !AddElement    (InterstitialBin , capsfilter)                    ||
      !AddElement    (InterstitialBin , converter )                    ||
      !AddElement    (InterstitialBin , queue     )                    ||
      !LinkElements  (source     , capsfilter)                         ||
      !LinkElements  (capsfilter , converter )                         ||
      !LinkElements  (converter  , queue     )                         ||
      !NewGhostSrcPad(InterstitialBin   , queue , "interstitial-source"))
// !LinkElements(InterstitialBin  , CompositorBin)
  { AvCaster::Error(GUI::INTERSTITIAL_LINK_ERROR_MSG) ; return false ; }

#  endif // STATIC_INTERSTITIAL

#else // CONFIGURE_INTERSTITIAL_BIN
#  ifdef DEBUG
Trace::TraceState("bypassing interstitial configuration") ;
#  endif // DEBUG
#endif // CONFIGURE_INTERSTITIAL_BIN

  return true ;
}

bool Gstreamer::ConfigureCompositorBin()
{
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

DEBUG_TRACE_CONFIGURE_COMPOSITOR_BIN

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

  if (!IsPlaying()) return true ;

  // re-link to input and output bins
  if (!LinkElements(ScreencapBin  , CompositorBin) ||
      !LinkElements(CameraBin     , CompositorBin) ||
      !LinkElements(CompositorBin , MuxerBin     ) ||
      !LinkElements(CompositorBin , PreviewBin   )  )
  { AvCaster::Error(GUI::MIXER_BIN_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigurePreviewBin()
{
#ifndef RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE
  // NOTE: x_window_handle must be attached before pipline is started
  //           so PreviewSink must never be FAUX_SINK_PLUGIN_ID if it is to be usable
  bool   is_enabled = AvCaster::GetIsPreviewOn() ;
  String plugin_id  = (is_enabled) ? GST::NIX_PREVIEW_PLUGIN_ID : GST::FAUX_SINK_PLUGIN_ID ;

#  ifdef DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
UNUSED(is_enabled) ; is_enabled = true ; plugin_id  = GST::NIX_PREVIEW_PLUGIN_ID ; // FIXME: no fake sink needed ?
#  endif // DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
#else // RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE
#  if JUCE_LINUX
  String plugin_id = GST::NIX_PREVIEW_PLUGIN_ID ;
#  endif //JUCE_LINUX
#endif // RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE

#  if FAUX_PREVIEW
plugin_id = GST::FAUX_SINK_PLUGIN_ID ;
#  endif // FAUX_PREVIEW

DEBUG_TRACE_CONFIGURE_PREVIEW_BIN

  // instantiate elements
  if (!(PreviewSink = NewElement(plugin_id , "preview-real-sink")) )
  { AvCaster::Error(GUI::PREVIEW_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  if (plugin_id != GST::FAUX_SINK_PLUGIN_ID)
  {
    guintptr x_window_handle = (guintptr)AvCaster::GetGuiXwinHandle() ;
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(PreviewSink) , x_window_handle) ;

    if (!ConfigurePreview())
    { AvCaster::Error(GUI::GST_XWIN_ERROR_MSG) ; return false ; }
  }

  // link elements
  if (!AddElement     (PreviewBin , PreviewSink                 ) ||
      !NewGhostSinkPad(PreviewBin , PreviewSink , "preview-sink") ||
      !LinkElements   (CompositorBin , PreviewBin)                 )
  { AvCaster::Error(GUI::PREVIEW_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigureAudioBin()
{
  GstElement *source , *capsfilter , *converter , *queue ;
  GstCaps*    caps ;

  bool   is_enabled       = bool(ConfigStore[CONFIG::IS_AUDIO_ON_ID]) ;
  int    audio_api        = int (ConfigStore[CONFIG::AUDIO_API_ID  ]) ;
  int    n_channels       = int (ConfigStore[CONFIG::N_CHANNELS_ID ]) ;
  int    samplerate_n     = int (ConfigStore[CONFIG::SAMPLERATE_ID ]) ;
  int    samplerate       = CONFIG::AUDIO_SAMPLERATES[samplerate_n].getIntValue() ;
  String audio16_caps_str = MakeAudioCapsString("S16LE" , samplerate , n_channels) ;
  String audio32_caps_str = MakeAudioCapsString("F32LE" , samplerate , n_channels) ;
  String plugin_id , caps_str ;

UNUSED(is_enabled) ; is_enabled = true ; // TODO: GUI support
#ifdef FAUX_AUDIO
UNUSED(is_enabled) ; is_enabled = false ;
#endif // FAUX_AUDIO

  switch ((AvCasterStore::AudioApi)audio_api)
  {
    case AvCasterStore::ALSA_AUDIO:  plugin_id  = GST::ALSA_PLUGIN_ID ;
                                     caps_str   = audio16_caps_str ;          break ;
    case AvCasterStore::PULSE_AUDIO: plugin_id  = GST::PULSE_PLUGIN_ID ;
                                     caps_str   = audio16_caps_str ;          break ;
    case AvCasterStore::JACK_AUDIO:  plugin_id  = GST::JACK_PLUGIN_ID ;
                                     caps_str   = audio32_caps_str ;          break ;
    default:                         plugin_id  = GST::FAUX_AUDIO_PLUGIN_ID ;
                                     caps_str   = GST::FAUX_AUDIO_CAPS ;
                                     is_enabled = false ;                     break ;
  }

  if (!is_enabled)
  {
    plugin_id = GST::FAUX_AUDIO_PLUGIN_ID ;
    caps_str  = GST::FAUX_AUDIO_CAPS ;
  }

DEBUG_TRACE_CONFIGURE_AUDIO_BIN

  // instantiate elements
  if (!(source     = NewElement(plugin_id      , "audio-real-source")) ||
      !(capsfilter = NewElement("capsfilter"   , "audio-capsfilter" )) ||
      !(converter  = NewElement("audioconvert" , "audio-converter"  )) ||
      !(queue      = NewElement("queue"        , "audio-queue"      )) ||
      !(caps       = NewCaps   (caps_str)                            )  )
  { AvCaster::Error(GUI::AUDIO_INIT_ERROR_MSG) ; return false ; }

  // configure elements
  if (!is_enabled) ConfigureFauxAudio(source) ;
  ConfigureCaps (capsfilter , caps        ) ;
  ConfigureQueue(queue      , 0    , 0 , 0) ;

  // link elements
  if (!AddElement    (AudioBin , source    )               ||
      !AddElement    (AudioBin , capsfilter)               ||
      !AddElement    (AudioBin , converter )               ||
      !AddElement    (AudioBin , queue     )               ||
      !LinkElements  (source     , capsfilter)             ||
      !LinkElements  (capsfilter , converter )             ||
      !LinkElements  (converter  , queue     )             ||
      !NewGhostSrcPad(AudioBin   , queue , "audio-source") ||
      !LinkElements(AudioBin     , MuxerBin  )              )
  { AvCaster::Error(GUI::AUDIO_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigureMuxerBin()
{
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

DEBUG_TRACE_CONFIGURE_MUXER_BIN

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

  // re-link to input bins
  if ((!IsPlaying() && !LinkElements(CompositorBin , MuxerBin)) ||
       (IsPlaying() && !LinkElements(AudioBin      , MuxerBin))  )
  { AvCaster::Error(GUI::MUXER_BIN_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::ConfigureOutputBin()
{
  GstElement *queue , *sink ;

  bool   is_enabled  = bool  (ConfigStore[CONFIG::IS_OUTPUT_ON_ID]) ;
  int    muxer_idx   = int   (ConfigStore[CONFIG::OUTPUT_MUXER_ID]) ;
  int    sink_idx    = int   (ConfigStore[CONFIG::OUTPUT_SINK_ID ]) ;
  String dest        = STRING(ConfigStore[CONFIG::OUTPUT_DEST_ID ]) ;
  String file_ext    = CONFIG::OUTPUT_MUXERS[muxer_idx] ;
  String filename    = dest.upToLastOccurrenceOf(file_ext , false , true) ;
  File   output_file = APP::VIDEOS_DIR.getNonexistentChildFile(filename , file_ext , false) ;
  String file_url    = output_file.getFullPathName() ;
  bool   is_lctv     = AvCaster::GetPresetIdx() == CONFIG::LCTV_PRESET_IDX ;
  String rtmp_url    = (is_lctv) ? MakeLctvUrl(dest) : dest ;

#ifdef FAUX_OUTPUT
UNUSED(is_enabled) ; is_enabled = false ;
#endif // FAUX_OUTPUT
#ifdef DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE
UNUSED(is_enabled) ; is_enabled = true ; // FIXME: no fake sink needed ?
#endif // DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE

  if (!is_enabled) sink_idx = -1 ; String plugin_id , output_url ;
  switch (sink_idx)
  {
    case CONFIG::FILE_STREAM_IDX: plugin_id = GST::FILE_SINK_PLUGIN_ID ; output_url = file_url ; break ;
    case CONFIG::RTMP_STREAM_IDX: plugin_id = GST::RTMP_SINK_PLUGIN_ID ; output_url = rtmp_url ; break ;
    default:                      plugin_id = GST::FAUX_SINK_PLUGIN_ID ; is_enabled = false ;    break ;
  }

DEBUG_TRACE_CONFIGURE_OUTPUT_BIN

#ifdef DEBUG
if (sink_idx == CONFIG::RTMP_STREAM_IDX)
{
  String env_url = std::getenv("AVCASTER_RTMP_DEST") ;
  if (env_url.isNotEmpty()) output_url = (is_lctv) ? MakeLctvUrl(env_url) : env_url ;
  else
  {
    AvCaster::Error(DEBUG_RTMP_DEST_ERROR_MSG) ;
    plugin_id = GST::FILE_SINK_PLUGIN_ID ; output_url = file_url ;
  }
}
#endif // DEBUG

  if (!(queue = NewElement("queue"   , "output-queue"    )) ||
      !(sink  = NewElement(plugin_id , "output-real-sink"))  )
  { AvCaster::Error(GUI::OUTPUT_INIT_ERROR_MSG) ; return false ; }

  ConfigureQueue(queue , 0 , 0 , 0) ;
  if (is_enabled) ConfigureFile(sink , output_url) ;

  if (!AddElement     (OutputBin , queue)                 ||
      !AddElement     (OutputBin , sink )                 ||
      !LinkElements   (queue  , sink       )              ||
      !NewGhostSinkPad(OutputBin , queue , "output-sink") ||
      !LinkElements   (MuxerBin , OutputBin)               )
  { AvCaster::Error(GUI::OUTPUT_LINK_ERROR_MSG) ; return false ; }

  return true ;
}

bool Gstreamer::Reconfigure(const Identifier& config_key , bool is_config_pending)
{
DEBUG_TRACE_RECONFIGURE

/*
  if      (config_key == CONFIG::PRESET_ID             )
  { if (!ConfigurePipeline())                                     return false ; }
  else if (config_key == CONFIG::IS_PENDING_ID         )
  { if (!is_config_pending && !ConfigurePipeline())               return false ; }
  else if (config_key == CONFIG::IS_SCREENCAP_ON_ID    )
  { ScreencapBin    = RecreateBin(ScreencapBin    , GST::SCREENCAP_BIN_ID   ) ;
    if (!ConfigureScreencap()   ) { DestroyBin(ScreencapBin   ) ; return false ; } }
  else if (config_key == CONFIG::IS_CAMERA_ON_ID       )
  { CameraBin       = RecreateBin(CameraBin       , GST::CAMERA_BIN_ID      ) ;
    if (!ConfigureCamera()      ) { DestroyBin(CameraBin      ) ; return false ; } }
  else if (config_key == CONFIG::IS_TEXT_ON_ID         )
  { TextBin         = RecreateBin(TextBin         , GST::TEXT_BIN_ID        ) ;
    if (!ConfigureText()        ) { DestroyBin(TextBin        ) ; return false ; } }
  else if (config_key == CONFIG::IS_INTERSTITIAL_ON_ID)
  { InterstitialBin = RecreateBin(InterstitialBin , GST::INTERSTITIAL_BIN_ID) ;
    if (!ConfigureInterstitial()) { DestroyBin(InterstitialBin) ; return false ; } }
  else if (config_key == CONFIG::IS_AUDIO_ON_ID        )
  { AudioBin        = RecreateBin(AudioBin        , GST::AUDIO_BIN_ID       ) ;
    if (!ConfigureAudio()       ) { DestroyBin(AudioBin       ) ; return false ; } }
*/
// FIXME: it should be possible to handle all toggles consistently
//        perhaps using RecreateBin()/DestroyBin() as below (currently leaky)
//        or ReconfigureBin()
//        or simply detaching/re-attaching bins
  if (config_key == CONFIG::IS_PENDING_ID    ||
      config_key == CONFIG::IS_PREVIEW_ON_ID  )
#ifdef RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE
  { if (!ConfigurePreview()) return false ; }
#else // RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE
#  ifdef DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
  {
    if (!is_on &&  !RemoveBin(PreviewBin) ||
         is_on && (!AddBin   (PreviewBin) || !LinkElements(CompositorBin , PreviewBin)))
      return false ;
// SetState(Pipeline , GST_STATE_PLAYING) ;
  }
#  else // DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
  { PreviewBin      = RecreateBin(PreviewBin      , GST::PREVIEW_BIN_ID     ) ;
    if (!ConfigurePreviewBin()     ) { DestroyBin(PreviewBin     ) ; return false ; } }
#  endif // DETACH_PREVIEW_BIN_INSTEAD_OF_RECREATE
#endif // RESIZE_PREVIEW_BIN_INSTEAD_OF_RECREATE
  else if (config_key == CONFIG::IS_OUTPUT_ON_ID       )
#ifdef DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE
  {
DBG("detachingOutputBin") ;
    bool is_on = bool(ConfigStore[CONFIG::IS_OUTPUT_ON_ID]) ;
    if (!is_on &&  !RemoveBin(OutputBin) ||
         is_on && (!AddBin   (OutputBin) || !LinkElements(MuxerBin , OutputBin)))
      return false ;
  }
#else // DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE
{DBG("recreating OutputBin") ;
    OutputBin       = RecreateBin(OutputBin       , GST::OUTPUT_BIN_ID      ) ;
    if (!ConfigureOutputBin()      ) { DestroyBin(OutputBin      ) ; return false ; } }
#endif // DETACH_OUTPUT_BIN_INSTEAD_OF_RECREATE

// DEBUG_MAKE_GRAPHVIZ

  return true ;
}

void Gstreamer::DestroyBin(GstElement* a_bin) { RemoveBin(a_bin) ; DeleteElement(a_bin) ; }
/* recreate then reconfigure bin
 * TODO: refactor with fn_pointer ?
  if      (config_key == CONFIG::IS_SCREENCAP_ON_ID   )
    return ReconfigureBin(GST::SCREENCAP_BIN_ID    , ScreencapBin   , fn_pointer) ;
  else if (config_key == CONFIG::IS_CAMERA_ON_ID      )
    return ReconfigureBin(GST::CAMERA_BIN_ID       , CameraBin      , fn_pointer) ;
  else if (config_key == CONFIG::IS_TEXT_ON_ID        )
    return ReconfigureBin(GST::TEXT_BIN_ID         , TextBin        , fn_pointer) ;
  else if (config_key == CONFIG::IS_INTERSTITIAL_ON_ID)
    return ReconfigureBin(GST::INTERSTITIAL_BIN_ID , InterstitialBin, fn_pointer) ;
  else if (config_key == CONFIG::IS_PREVIEW_ON_ID     )
    return ReconfigureBin(GST::PREVIEW_BIN_ID      , PreviewBin     , fn_pointer) ;
  else if (config_key == CONFIG::IS_AUDIO_ON_ID       )
    return ReconfigureBin(GST::AUDIO_BIN_ID        , AudioBin       , fn_pointer) ;
  else if (config_key == CONFIG::IS_OUTPUT_ON_ID      )
    return ReconfigureBin(GST::OUTPUT_BIN_ID       , OutputBin      , fn_pointer) ;
  else return false ;
bool Gstreamer::ReconfigureBin(String      bin_id       , GstElement* a_bin)
{
DEBUG_TRACE_RECONFIGURE_BIN

  a_bin       = RecreateBin(a_bin , bin_id) ;
  bool is_err = (bin_id == GST::SCREENCAP_BIN_ID    && !ConfigureScreencap   (a_bin)) ||
                (bin_id == GST::CAMERA_BIN_ID       && !ConfigureCamera      (a_bin)) ||
                (bin_id == GST::TEXT_BIN_ID         && !ConfigureText        (a_bin)) ||
                (bin_id == GST::INTERSTITIAL_BIN_ID && !ConfigureInterstitial(a_bin)) ||
                (bin_id == GST::AUDIO_BIN_ID        && !ConfigureAudio       (a_bin)) ||
                (bin_id == GST::PREVIEW_BIN_ID      && !ConfigurePreviewBin     (a_bin)) ||
                (bin_id == GST::OUTPUT_BIN_ID       && !ConfigureOutput      (a_bin))  ;

  if (is_err) { RemoveBin(a_bin) ; DeleteElement(a_bin) ; }

  return !is_err ;
}
*/

bool Gstreamer::SetState(GstElement* an_element , GstState next_state)
{
  bool is_err = an_element == nullptr                                                     ||
                gst_element_set_state(an_element , next_state) == GST_STATE_CHANGE_FAILURE ;

DEBUG_TRACE_SET_GST_STATE

  if (is_err) AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ;

  return !is_err ;
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

bool Gstreamer::AddElement(GstElement* a_bin , GstElement* an_element)
{
  bool is_err = !gst_bin_add(GST_BIN(a_bin) , an_element)    ||
                !gst_element_sync_state_with_parent(an_element) ;

DEBUG_TRACE_ADD_ELEMENT

  return !is_err ;
}

void Gstreamer::DeleteElement(GstElement* an_element)
{
  if (an_element != nullptr && SetState(an_element , GST_STATE_NULL))
    gst_object_unref(an_element) ;
}

bool Gstreamer::AddBin(GstElement* a_bin)
{
DEBUG_FILTER_BINS // NOTE: this may return (true) early here

  bool is_err = !gst_bin_add(GST_BIN(Pipeline) , a_bin)   ||
                !gst_element_sync_state_with_parent(a_bin) ;

DEBUG_TRACE_ADD_BIN

  return !is_err ;
}

bool Gstreamer::RemoveBin(GstElement* a_bin)
{
DEBUG_TRACE_REMOVE_BIN_IN

  bool is_err = !gst_bin_remove(GST_BIN(Pipeline) , a_bin) ;

DEBUG_TRACE_REMOVE_BIN_OUT

  return !is_err ;
}

GstElement* Gstreamer::RecreateBin(GstElement* a_bin , String bin_id)
{
DEBUG_TRACE_RECREATE_BIN_IN

  GstElement* new_bin ;

  if (RemoveBin(a_bin) && (new_bin = NewBin(bin_id)) != nullptr)
    if (AddBin(new_bin)) { DeleteElement(a_bin) ; a_bin = new_bin ; }

  if (!IsInPipeline(new_bin)) { AddBin(a_bin) ; DeleteElement(new_bin) ; }

DEBUG_TRACE_RECREATE_BIN_OUT

  return a_bin ;
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

void Gstreamer::ConfigureScreen(GstElement* a_screen_source , guint capture_w  , guint capture_h ,
                                guint       pattern_n       , bool  is_enabled                   )
{
DEBUG_TRACE_CONFIGURE_SCREEN

  if (is_enabled)
  {
    g_object_set(G_OBJECT(a_screen_source) , "endx"       , capture_w - 1 , NULL) ;
    g_object_set(G_OBJECT(a_screen_source) , "endy"       , capture_h - 1 , NULL) ;
    g_object_set(G_OBJECT(a_screen_source) , "use-damage" , false         , NULL) ;
  }
  else ConfigureFauxVideo(a_screen_source , pattern_n) ;
}

void Gstreamer::ConfigureCamera(GstElement* a_camera_source , String device_path ,
                                guint       pattern_n       , bool   is_enabled  )
{
DEBUG_TRACE_CONFIGURE_CAMERA

  if (is_enabled)
    g_object_set(G_OBJECT(a_camera_source) , "device" , CHARSTAR(device_path) , NULL) ;
  else ConfigureFauxVideo(a_camera_source , pattern_n) ;
}

void Gstreamer::ConfigureFauxVideo(GstElement* a_faux_source , guint pattern_n)
{
DEBUG_TRACE_CONFIGURE_FAUX_VIDEO

  g_object_set(G_OBJECT(a_faux_source) , "is_live" , true      , NULL) ;
  g_object_set(G_OBJECT(a_faux_source) , "pattern" , pattern_n , NULL) ;
}

void Gstreamer::ConfigureText(GstElement* a_text_source , String font_desc)
{
DEBUG_TRACE_CONFIGURE_TEXT

  g_object_set(G_OBJECT(a_text_source) , "font-desc" , CHARSTAR(font_desc) , NULL) ;
}

void Gstreamer::ConfigureFile(GstElement* a_file_source , String file_path)
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

bool Gstreamer::ConfigurePreview()
{
DEBUG_TRACE_CONFIGURE_PREVIEW
#if FAUX_PREVIEW
// TODO: ensure this is never called with PreviewSink as FAUX_SINK_PLUGIN_ID
  return true ;
#endif // FAUX_PREVIEW

  bool           is_enabled     = AvCaster::GetIsPreviewOn() ;
  Rectangle<int> preview_bounds = AvCaster::GetPreviewBounds() ;
  gint           preview_x      = (is_enabled) ? preview_bounds.getX()      : -1 ;
  gint           preview_y      = (is_enabled) ? preview_bounds.getY()      : -1 ;
  gint           preview_w      = (is_enabled) ? preview_bounds.getWidth()  : 1 ;
  gint           preview_h      = (is_enabled) ? preview_bounds.getHeight() : 1 ;
#ifdef SHOW_DISABLED_PREVIEW_TINY
preview_x = (is_enabled) ? preview_bounds.getX()      : 1 ;
preview_y = (is_enabled) ? preview_bounds.getY()      : 1 ;
preview_w = (is_enabled) ? preview_bounds.getWidth()  : 160 ;
preview_h = (is_enabled) ? preview_bounds.getHeight() : 120 ;
#endif // SHOW_DISABLED_PREVIEW_TINY

  return gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(PreviewSink) ,
                                                preview_x , preview_y          ,
                                                preview_w , preview_h          ) ;
}

void Gstreamer::ConfigureFauxAudio(GstElement* a_faux_source)
{
DEBUG_TRACE_CONFIGURE_FAUX_AUDIO

 g_object_set(G_OBJECT(a_faux_source) , "is_live" , true , NULL) ;
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

bool Gstreamer::IsInitialized() { return gst_is_initialized() ; }

bool Gstreamer::IsPlaying()
{
  return !!Pipeline && GST_STATE(Pipeline) == GST_STATE_PLAYING ;
}

bool Gstreamer::IsInPipeline(GstElement* an_element)
{
  return !!an_element && GST_ELEMENT_PARENT(an_element) == Pipeline ;
}
