/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill-auger

  ==============================================================================
*/
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define RAW_VIDEO_CAPS_STR "video/x-raw, width=(int)" STR(1280)                     \
                           ", height=(int)" STR(800) ", framerate=(fraction)12/1, " \
                           "format=I420, pixel-aspect-ratio=(fraction)1/1, "        \
                           "interlace-mode=(string)progressive"
#  define TESTVIDEO_MAIN_CAPS "video/x-raw, width=(int)1280, height=(int)800, " \
                              "framerate=(fraction)12/1, "                      \
                              "format=I420, pixel-aspect-ratio=(fraction)1/1, " \
                              "interlace-mode=(string)progressive"
#  define TESTVIDEO_OVERLAY_CAPS "video/x-raw, width=(int)160, height=(int)120, "  \
                                 "framerate=(fraction)12/1, "                      \
                                 "format=I420, pixel-aspect-ratio=(fraction)1/1, " \
                                 "interlace-mode=(string)progressive"
#  define SCREENCAP_CAPS "video/x-raw, width=(int)1280, height=(int)800, framerate=(fraction)12/1, pixel-aspect-ratio=(fraction)1/1"
#  define CAMERA_CAPS    "video/x-raw, width=640, height=480 , framerate=30/1, format=I420"
#  define AUDIO16_CAPS   "audio/x-raw, format=(string)S16LE, layout=(string)interleaved, rate=(int)44100, channels=(int)2"
#  define AUDIO32_CAPS   "audio/x-raw, format=(string)F32LE, layout=(string)interleaved, rate=(int)44100, channels=(int)2"
#  define TESTAUDIO_CAPS "audio/x-raw, format=(string)S16LE, endianness=(int)1234, " \
                         "signed=(boolean)true, width=(int)16, depth=(int)16, "      \
                         "rate=(int)44100, channels=(int)2"
#  define VIDEO_ENC_CAPS "video/x-h264, level=(string)4.1, profile=main"
#  define AUDIO_ENC_CAPS "audio/mpeg, mpegversion=1, layer=3, mpegaudioversion=3, rate=48000, channels=2, parsed=true"


#include <cstdlib>
#include <gst/video/videooverlay.h>
#include <gst/video/gstvideosink.h>

#include "AvCaster.h"
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterConfig> AvCaster::Config ; // Initialize()


/* AvCaster private class variables */

MainContent*  AvCaster::Gui            = nullptr ; // Initialize()
Array<Alert*> AvCaster::Alerts ;
bool          AvCaster::IsAlertModal   = false ;   // Warning() , Error()
GstElement*   AvCaster::Pipeline       = nullptr ;
GstElement*   AvCaster::ScreencapBin   = nullptr ;
GstElement*   AvCaster::ScreencapSink  = nullptr ;
GstElement*   AvCaster::CameraBin      = nullptr ;
GstElement*   AvCaster::CameraSink     = nullptr ;
GstElement*   AvCaster::AudioBin       = nullptr ;
GstElement*   AvCaster::TextBin        = nullptr ;
GstElement*   AvCaster::CompositorBin  = nullptr ;
GstElement*   AvCaster::CompositorSink = nullptr ;
GstElement*   AvCaster::MuxBin         = nullptr ;
GstElement*   AvCaster::OutputBin      = nullptr ;


/* AvCaster public class methods */

void AvCaster::Warning(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_WARNING , message_text)) ;
}

void AvCaster::Error(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_ERROR , message_text)) ;
}

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

StringArray AvCaster::DevicesNames(ValueTree a_devices_node)
{
  return Config->nodeValues(a_devices_node) ;
}


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content , const String& args)
{
  Gui = main_content ;

  // load persistent configuration
  if ((Config = new AvCasterConfig()) == nullptr) return false ;

  // instantiate GUI
  Gui->instantiate(Config->configStore , Config->cameraDevices , Config->audioDevices) ;

  // initialize gStreamer
  if (!InitGstreamer()) return false ;

DEBUG_GRAPHVIZ

#ifdef DEBUG_QUIT_IMMEDIATELY
Trace::TraceEvent("DEBUG_QUIT_IMMEDIATELY") ; return false ;
#endif // DEBUG_QUIT_IMMEDIATELY

  return true ;
}

bool AvCaster::InitGstreamer()
{
DEBUG_TRACE_INIT_PHASE1
/* TODO: not sure if we will need to handle signals
bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
gst_bus_set_sync_handler (bus, (GstBusSyncHandler) cbw, pipeline, NULL);
static GstBusSyncReply cb(GstBus * bus, GstMessage * message, GstPipeline * pipeline)
*/

  // instantiate pipeline
  gst_init(nullptr , nullptr) ;
  if (!(Pipeline        = gst_pipeline_new        ("pipeline"                        )) ||
#ifdef CONFIGURE_SCREENCAP_CHAIN
      !(ScreencapBin    = gst_bin_new             ("screen-bin"                      )) ||
      !(ScreencapSink   = gst_element_factory_make("xvimagesink"  , "screen-sink"    )) ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !(CameraBin       = gst_bin_new             ("camera-bin"                      )) ||
      !(CameraSink      = gst_element_factory_make("xvimagesink"  , "camera-sink"    )) ||
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
      !(AudioBin        = gst_bin_new             ("audio-bin"                       )) ||
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
      !(TextBin         = gst_bin_new             ("text-bin"                        )) ||
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_COMPOSITING_CHAIN
      !(CompositorBin   = gst_bin_new             ("compositor-bin"                  )) ||
      !(CompositorSink  = gst_element_factory_make("xvimagesink"  , "compositor-sink")) ||
#endif // CONFIGURE_COMPOSITING_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
      !(MuxBin          = gst_bin_new             ("mux-bin"                         )) ||
#endif // CONFIGURE_MUX_CHAIN
      !(OutputBin       = gst_bin_new             ("output-bin"                      ))  )
  { Error(GUI::GST_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE2

  // configure pipeline
#ifdef CONFIGURE_SCREENCAP_CHAIN
  if (!gst_bin_add(GST_BIN(Pipeline     ) , ScreencapBin  ) ||
//       !gst_bin_add(GST_BIN(ScreencapBin ) , ScreencapSink ) ||
#else // CONFIGURE_SCREENCAP_CHAIN
  if (!true                                               ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , CameraBin     ) ||
//       !gst_bin_add(GST_BIN(CameraBin    ) , CameraSink    ) ||
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , AudioBin      ) ||
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , TextBin       ) ||
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_COMPOSITING_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , CompositorBin ) ||
      !gst_bin_add(GST_BIN(CompositorBin) , CompositorSink) ||
#endif // CONFIGURE_COMPOSITING_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , MuxBin        ) ||
#endif // CONFIGURE_MUX_CHAIN
      !gst_bin_add(GST_BIN(Pipeline     ) , OutputBin     )  )
  { Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE3

  // configure elements
  if (!ConfigureScreencap() || !ConfigureCamera()      || !ConfigureAudio()  ||
      !ConfigureText()      || !ConfigureCompositing() || !ConfigureMux()    ||
      !ConfigureOutput()                                                      )
  { Error(GUI::GST_CONFIG_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE4

  // attach native xwindow to gStreamer overlay sinks
  guintptr window_handle = (guintptr)(Gui->getWindowHandle()) ;
#ifdef CONFIGURE_SCREENCAP_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(ScreencapSink ) , window_handle) ;
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(CameraSink    ) , window_handle) ;
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_COMPOSITING_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(CompositorSink) , window_handle) ;
#endif // CONFIGURE_COMPOSITING_CHAIN
#ifdef CONFIGURE_SCREENCAP_CHAIN
  if (!gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(ScreencapSink )          ,
                                              GUI::SCREENCAP_MONITOR_X , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H ) ||
#else // CONFIGURE_SCREENCAP_CHAIN
  if (false ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(CameraSink    )          ,
                                              GUI::CAMERA_MONITOR_X    , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H ) ||
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_COMPOSITING_CHAIN
      !gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(CompositorSink)          ,
                                              GUI::OUTPUT_MONITOR_X    , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H )  )
#else // CONFIGURE_COMPOSITING_CHAIN
      false)
#endif // CONFIGURE_COMPOSITING_CHAIN
  { Error(GUI::GST_XWIN_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE5

  // set rolling
  if (!SetGstreamerState(Pipeline , GST_STATE_PLAYING)) return false ;

  TogglePreview() ; return true ;
}

void AvCaster::Shutdown()
{
  Config = nullptr ;

  // cleanup gStreamer
  gst_element_set_state(Pipeline , GST_STATE_NULL) ;
  gst_object_unref     (Pipeline) ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID:  UpdateStatusGUI() ; break ;
    case APP::GUI_TIMER_MED_ID: DisplayAlert() ;    break ;
    case APP::GUI_TIMER_LO_ID:                      break ;
    default:                                        break ;
  }
}

void AvCaster::UpdateStatusGUI()
{
/*
  Gui->statusbar->setStatusL("Frame: "    + String(MuxStream->currentFrame  ) + " " +
                             "FPS: "      + String(MuxStream->currentFps    )       ) ;
  Gui->statusbar->setStatusC("Bitrate: "  + String(MuxStream->currentBitrate) + " " +
                             "Q: "        + String(MuxStream->currentQ      )       ) ;
  Gui->statusbar->setStatusR("Filesize: " + String(MuxStream->currentSize   ) + " " +
                             "Duration: " + String(MuxStream->currentTime   )       ) ;
*/
}

/* TODO: we may want to reconfigure the stream here (e.g. text position)
 *         => ConfigureStream() ;
 *       or perform validations (e.g. screen resolution/orientation has changed)
 *         => Gui->config->loadConfig() ;                                    */
void AvCaster::HandleConfigChanged(const Identifier& a_key)
{
  if (a_key == CONFIG::IS_PREVIEW_ON_ID) TogglePreview() ;
}

bool AvCaster::ConfigureScreencap()
{
#ifdef CONFIGURE_SCREENCAP_CHAIN

  GstElement *source , *capsfilter , *queue ;
  GstCaps    *caps ;
  String      plugin_id ;
  String      caps_str ;

  int screencap_w = int(Config->configStore[CONFIG::SCREENCAP_W_ID]) ;
  int screencap_h = int(Config->configStore[CONFIG::SCREENCAP_H_ID]) ;

DEBUG_TRACE_CONFIG_SCREENCAP

#if JUCE_LINUX
  plugin_id = "v4l2src" ; caps_str = CAMERA_CAPS ;
#endif // JUCE_LINUX

#define FAUX_VIDEO_SRC
#ifdef FAUX_VIDEO_SRC
plugin_id = "videotestsrc" ; caps_str = TESTVIDEO_OVERLAY_CAPS ;
#endif // FAUX_VIDEO_SRC

  if (!(source     = MakeElement(plugin_id    , "screen-input"     )) ||
      !(capsfilter = MakeElement("capsfilter" , "screen-capsfilter")) ||
      !(queue      = MakeElement("queue"      , "screen-queue"     )) ||
      !(caps       = gst_caps_from_string(TESTVIDEO_MAIN_CAPS)      )  )
  { Error(GUI::SCREENCAP_INIT_ERROR_MSG) ; return false ; }

#ifdef FAUX_VIDEO_SRC
g_object_set(source , "is_live" , true , NULL) ; g_object_set(source , "pattern" , 1 , NULL) ;
#else // FAUX_VIDEO_SRC
  g_object_set(G_OBJECT(source    ) , "endx"         , screencap_w - 1 , NULL) ;
  g_object_set(G_OBJECT(source    ) , "endy"         , screencap_h - 1 , NULL) ;
  g_object_set(G_OBJECT(source    ) , "use-damage"   , false           , NULL) ;
  g_object_set(G_OBJECT(source    ) , "show-pointer" , true            , NULL) ;
#endif // FAUX_VIDEO_SRC
  g_object_set(G_OBJECT(capsfilter) , "caps"         , caps            , NULL) ;
  gst_caps_unref(caps) ;


  if (!AddElement        (ScreencapBin , source    )                    ||
      !AddElement        (ScreencapBin , capsfilter)                    ||
      !AddElement        (ScreencapBin , queue     )                    ||
      !LinkElements      (source     , capsfilter)                      ||
      !LinkElements      (capsfilter , queue     )                      ||
      !MakeStaticGhostPad(ScreencapBin , queue , "src" , "screen-source"))
  { Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_SCREENCAP_CHAIN
Trace::TraceState("bypassing screencap configuration") ;
#endif // CONFIGURE_SCREENCAP_CHAIN

  return true ;
}

bool AvCaster::ConfigureCamera()
{
#ifdef CONFIGURE_CAMERA_CHAIN

  GstElement *source , *capsfilter , *queue ;
  GstCaps*    caps ;
  String      plugin_id ;
  String      caps_str ;

  int          dev_n  = int(Config->configStore[CONFIG::CAMERA_DEV_ID]) ;
  int          res_n  = int(Config->configStore[CONFIG::CAMERA_RES_ID]) ;
  const gchar* device = CHARSTAR(String("/dev/" +
                        String(Config->cameraDevices.getPropertyName(dev_n)))) ;

DEBUG_TRACE_CONFIG_CAMERA

#if JUCE_LINUX
  plugin_id = "v4l2src" ; caps_str = CAMERA_CAPS ;
#endif // JUCE_LINUX

#define FAUX_VIDEO_SRC
#ifdef FAUX_VIDEO_SRC
plugin_id = "videotestsrc" ; caps_str = TESTVIDEO_OVERLAY_CAPS ;
#else // FAUX_VIDEO_SRC
  if (Config->cameraDevices.getNumProperties() == 0) return true ;
#endif // FAUX_VIDEO_SRC

  if (!(source     = MakeElement(plugin_id    , "camera-real-source")) ||
      !(capsfilter = MakeElement("capsfilter" , "camera-caps"       )) ||
      !(queue      = MakeElement("queue"      , "camera-queue"      )) ||
      !(caps       = MakeCaps(caps_str)                              )  )
  { Error(GUI::CAMERA_INIT_ERROR_MSG) ; return false ; }

#ifdef FAUX_VIDEO_SRC
g_object_set(source , "is_live" , true , NULL) ; g_object_set(source , "pattern" , 0 , NULL) ;
#else// FAUX_VIDEO_SRC
  g_object_set(G_OBJECT(source    ) , "device" , device , NULL) ;
#endif // FAUX_VIDEO_SRC
  g_object_set(G_OBJECT(capsfilter) , "caps"   , caps   , NULL) ; gst_caps_unref(caps) ;

  if (!AddElement        (CameraBin , source    )                    ||
      !AddElement        (CameraBin , capsfilter)                    ||
      !AddElement        (CameraBin , queue     )                    ||
      !LinkElements      (source , capsfilter)                       ||
      !LinkElements      (capsfilter , queue )                       ||
      !MakeStaticGhostPad(CameraBin , queue , "src" , "camera-source"))
  { Error(GUI::CAMERA_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_CAMERA_CHAIN
Trace::TraceState("bypassing camera configuration") ;
#endif // CONFIGURE_CAMERA_CHAIN

  return true ;
}

bool AvCaster::ConfigureAudio()
{
#ifdef CONFIGURE_AUDIO_CHAIN

//   GstElement *source , *capsfilter , *queue ;
GstElement *source = nullptr;  GstElement *capsfilter = nullptr ; GstElement *queue = nullptr ;
  GstCaps*    caps ;

  int          audio_api = int(Config->configStore[CONFIG::AUDIO_API_ID]) ;
  const gchar* plugin_id ;
  const gchar* caps_str ;

  switch ((AvCasterConfig::AudioApi)audio_api)
  {
    case AvCasterConfig::ALSA_AUDIO:  plugin_id = CHARSTAR(GST::ALSA_PLUGIN_ID ) ;
                                      caps_str  = AUDIO16_CAPS ;                       break ;
    case AvCasterConfig::PULSE_AUDIO: plugin_id = CHARSTAR(GST::PULSE_PLUGIN_ID) ;
                                      caps_str  = AUDIO16_CAPS ;                       break ;
    case AvCasterConfig::JACK_AUDIO:  plugin_id = CHARSTAR(GST::JACK_PLUGIN_ID ) ;
                                      caps_str  = AUDIO32_CAPS ;                       break ;
    default:                          Error(GUI::AUDIO_CFG_ERROR_MSG) ; return false ; break ;
  }

#ifdef FAUX_AUDIO_SRC
plugin_id = "audiotestsrc" ; caps_str = TESTAUDIO_CAPS ;
#endif // FAUX_AUDIO_SRC

DEBUG_TRACE_CONFIG_AUDIO

  if (!(source     = MakeElement(plugin_id    , "audio-real-source")) ||
      !(capsfilter = MakeElement("capsfilter" , "audio-in-caps"    )) ||
      !(queue      = MakeElement("queue"      , "audio-in-queue"   )) ||
      !(caps       = gst_caps_from_string(caps_str)                 )  )
  { Error(GUI::AUDIO_INIT_ERROR_MSG) ; return false ; }

  g_object_set(G_OBJECT(capsfilter) , "caps" , caps , NULL) ; gst_caps_unref(caps) ;

#ifdef FAUX_AUDIO_SRC
g_object_set(source , "is_live" , true , NULL) ;
#endif // FAUX_AUDIO_SRC

  if (!AddElement        (AudioBin , source    )                     ||
      !AddElement        (AudioBin , capsfilter)                     ||
      !AddElement        (AudioBin , queue     )                     ||
      !LinkElements      (source     , capsfilter)                   ||
      !LinkElements      (capsfilter , queue )                       ||
      !MakeStaticGhostPad(AudioBin   , queue , "src" , "audio-source"))
  { Error(GUI::AUDIO_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_AUDIO_CHAIN
Trace::TraceState("bypassing audio configuration") ;
#endif // CONFIGURE_AUDIO_CHAIN

  return true ;
}

bool AvCaster::ConfigureText()
{
#ifdef CONFIGURE_TEXT_CHAIN

  GstElement *filesrc , *subparser , *source , *converter , *queue ;

  String overlay_text = STRING(Config->configStore[CONFIG::OVERLAY_TEXT_ID]) ;
  int    text_style_n = int   (Config->configStore[CONFIG::TEXT_STYLE_ID  ]) ;
  int    text_pos_n   = int   (Config->configStore[CONFIG::TEXT_POS_ID    ]) ;

DEBUG_TRACE_CONFIG_TEXT

/* TODO: include custom font
#include <fontconfig/fontconfig.h>
std::string yourFontFilePath = "/home/testUser/bla.ttf"
const FcChar8 * file = (const FcChar8 *)yourFontFilePath.c_str();
FcBool fontAddStatus = FcConfigAppFOntAddFile(FcConfigGetCurrent(),file);
*/
// TODO: text from storage
  if (!(filesrc   = gst_element_factory_make("filesrc"      , "text-filesrc"  )) ||
      !(subparser = gst_element_factory_make("subparse"     , "text-subparser")) ||
      !(source    = gst_element_factory_make("textrender"   , "text-input"    )) ||
      !(converter = gst_element_factory_make("videoconvert" , "text-converter")) ||
      !(queue     = gst_element_factory_make("queue"        , "text-queue"    ))  )
    { Error(GUI::TEXT_INIT_ERROR_MSG) ; return false ; }

  g_object_set(source  , "font-desc" , "Purisa Normal 40"             , NULL) ;
  g_object_set(filesrc , "location"  , "/code/av-caster/deleteme.srt" , NULL) ;

  if (!AddElement        (TextBin , filesrc  )                     ||
      !AddElement        (TextBin , subparser)                     ||
      !AddElement        (TextBin , source   )                     ||
      !AddElement        (TextBin , converter)                     ||
      !AddElement        (TextBin , queue    )                     ||
      !MakeStaticGhostPad(TextBin , queue , "src" , "text-source") ||
      !LinkElements      (filesrc   , subparser)                   ||
      !LinkElements      (subparser , source   )                   ||
      !LinkElements      (source    , converter)                   ||
      !LinkElements      (converter , queue    )                    )
  { Error(GUI::TEXT_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_TEXT_CHAIN
Trace::TraceState("bypassing text configuration") ;
#endif // CONFIGURE_TEXT_CHAIN

  return true ;
}

bool AvCaster::ConfigureCompositing()
{
#ifdef CONFIGURE_COMPOSITING_CHAIN

DEBUG_TRACE_CONFIG_COMPOSITOR

  GstElement *compositor , *capsfilter , *converter , *queue ;
  GstCaps*    caps ;
  GstPad     *main_sinkpad , *overlay_sinkpad ;

  if (!(compositor = MakeElement("compositor"   , "compositor"          )) ||
      !(capsfilter = MakeElement("capsfilter"   , "compositor-caps"     )) ||
      !(converter  = MakeElement("videoconvert" , "compositor-converter")) ||
      !(queue      = MakeElement("queue"        , "compositor-queue"    )) ||
      !(caps       = MakeCaps    (RAW_VIDEO_CAPS_STR)                    )  )
  { Error(GUI::MIXER_INIT_ERROR_MSG) ; return false ; }

  g_object_set(compositor , "background" , 1    , NULL) ;
  g_object_set(capsfilter , "caps"       , caps , NULL) ; gst_caps_unref(caps) ;

  if (!AddElement  (CompositorBin , compositor)  ||
      !AddElement  (CompositorBin , capsfilter)  ||
      !AddElement  (CompositorBin , converter )  ||
      !AddElement  (CompositorBin , queue     )  ||
      !LinkElements(compositor , capsfilter    ) ||
      !LinkElements(capsfilter , converter     ) ||
      !LinkElements(converter  , queue         ) ||
      !LinkElements(queue      , CompositorSink)  )
    { Error(GUI::MIXER_LINK_ERROR_MSG) ; return false ; }

  main_sinkpad    = MakeRequestGhostPad(CompositorBin , compositor , "sink_0" , "compositor-main-sink"   ) ;
  overlay_sinkpad = MakeRequestGhostPad(CompositorBin , compositor , "sink_1" , "compositor-overlay-sink") ;

  g_object_set(main_sinkpad    , "width" , 1280 , "height", 800 , "xpos" , 0    , "ypos" , 0   , NULL) ;
  g_object_set(overlay_sinkpad , "width" , 160  , "height", 120 , "xpos" , 1120 , "ypos" , 680 , NULL) ;

  if (!LinkElements(ScreencapBin , CompositorBin) ||
      !LinkElements(CameraBin    , CompositorBin)  )
  { Error(GUI::MIXER_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_COMPOSITING_CHAIN
Trace::TraceState("bypassing compositor configuration") ;
#endif // CONFIGURE_COMPOSITING_CHAIN

  return true ;
}

bool AvCaster::ConfigureMux()
{
#ifdef CONFIGURE_MUX_CHAIN

  GstElement *video_in_queue  , *video_converter , *video_encoder , *video_parser ,
             *video_enc_caps  , *video_enc_queue                                  ;
  GstElement *audio_in_queue , *audio_encoder , *audio_parser , *audio_enc_queue ;
  GstElement *mux ;
  GstCaps    *video_caps ;

  int   output_w        = int(Config->configStore[CONFIG::OUTPUT_W_ID     ]) ;
  int   output_h        = int(Config->configStore[CONFIG::OUTPUT_H_ID     ]) ;
  int   video_bitrate_n = int(Config->configStore[CONFIG::VIDEO_BITRATE_ID]) ;
  int   audio_bitrate_n = int(Config->configStore[CONFIG::AUDIO_BITRATE_ID]) ;
  guint video_bitrate   = CONFIG::VIDEO_BITRATES[video_bitrate_n].getIntValue() ;
  guint audio_bitrate   = CONFIG::AUDIO_BITRATES[audio_bitrate_n].getIntValue() ;

DEBUG_TRACE_CONFIG_MUX

// TODO: some or all of these may not be necessary
// audio_enc_caps is either mis-configured or unfit for this speccified insertion
GstElement *audio_converter , *audio_enc_caps , *audio_enc_queue2 , *audio_enc_queue3 , *audio_enc_queue4 ; GstCaps *audio_caps ;

  if (!(video_in_queue  = MakeElement("queue"          , "mux-video-queue")) ||
      !(video_converter = MakeElement("videoconvert"   , "video-cvt"      )) ||
      !(video_encoder   = MakeElement("x264enc"        , "video-encoder"  )) ||
      !(video_parser    = MakeElement("h264parse"      , "video-parser"   )) ||
      !(video_caps      = MakeCaps(VIDEO_ENC_CAPS)                         ) ||
      !(video_enc_caps  = MakeElement("capsfilter"     , "video-enc-caps" )) ||
      !(video_enc_queue = MakeElement("queue"          , "video-enc-queue")) ||
      !(audio_in_queue  = MakeElement("queue"          , "mux-audio-queue")) ||
!(audio_converter = MakeElement("audioconvert" , "audio-cvt")) ||
      !(audio_encoder   = MakeElement("lamemp3enc"     , "audio-encoder"  )) ||
      !(audio_parser    = MakeElement("mpegaudioparse" , "audio-parser"   )) ||
// !(audio_caps      = MakeCaps(AUDIO_ENC_CAPS)                          ) ||
// !(audio_enc_caps  = MakeElement("capsfilter"     , "audio-enc-caps" )) ||
      !(audio_enc_queue = MakeElement("queue"          , "audio-enc-queue")) ||
!(audio_enc_queue2 = MakeElement("queue"          , "audio-enc-queue2")) ||
!(audio_enc_queue3 = MakeElement("queue"          , "audio-enc-queue3")) ||
!(audio_enc_queue4 = MakeElement("queue"          , "audio-enc-queue4")) ||
      !(mux             = MakeElement("flvmux"         , "flv-mux"        ))  )
  { Error(GUI::MUX_INIT_ERROR_MSG) ; return false ; }

  g_object_set(video_encoder  , "bitrate"    , video_bitrate  , NULL) ;
  g_object_set(video_encoder  , "bframes"    , 0              , NULL) ;
  g_object_set(video_enc_caps , "caps"       , video_caps     , NULL) ;
//   g_object_set(audio_encoder  , "bitrate"    , audio_bitrate  , NULL) ; // TODO: CBR
// g_object_set(audio_encoder , "quality" , 2 , NULL) ; // VBR (default is 4)
// g_object_set(audio_enc_caps , "caps"       , audio_caps     , NULL) ;
  g_object_set(mux            , "streamable" , true           , NULL) ;
  gst_caps_unref(video_caps) ; //gst_caps_unref(audio_caps) ;

  if (!AddElement        (MuxBin , video_in_queue )                         ||
      !AddElement        (MuxBin , video_converter)                         ||
      !AddElement        (MuxBin , video_encoder  )                         ||
      !AddElement        (MuxBin , video_parser   )                         ||
      !AddElement        (MuxBin , video_enc_caps )                         ||
      !AddElement        (MuxBin , video_enc_queue)                         ||
      !AddElement        (MuxBin , audio_in_queue )                         ||
!AddElement(MuxBin , audio_converter)         ||
      !AddElement        (MuxBin , audio_encoder  )                         ||
      !AddElement        (MuxBin , audio_parser   )                         ||
// !AddElement(MuxBin , audio_enc_caps )      ||
      !AddElement        (MuxBin , audio_enc_queue)                         ||
!AddElement(MuxBin , audio_enc_queue2)       ||
!AddElement(MuxBin , audio_enc_queue3)       ||
!AddElement(MuxBin , audio_enc_queue4)       ||
      !AddElement        (MuxBin , mux            )                         ||
      !LinkElements      (video_in_queue  , video_converter)                ||
      !LinkElements      (video_converter , video_encoder  )                ||
      !LinkElements      (video_encoder   , video_parser   )                ||
      !LinkElements      (video_parser    , video_enc_caps )                ||
      !LinkElements      (video_enc_caps  , video_enc_queue)                ||
      !LinkElements      (video_enc_queue , mux            )                ||
      !MakeStaticGhostPad(MuxBin , video_in_queue , "sink" , "video-sink")  ||
#ifdef CONFIGURE_COMPOSITING_CHAIN
      !LinkElements      (CompositorBin , MuxBin)                           ||
#else // CONFIGURE_COMPOSITING_CHAIN
#  ifdef CONFIGURE_SCREENCAP_CHAIN
      !LinkElements      (ScreencapBin , MuxBin)                            ||
#  else // CONFIGURE_SCREENCAP_CHAIN
#    ifdef CONFIGURE_CAMERA_CHAIN
      !LinkElements      (CameraBin , MuxBin)                               ||
#    endif // CONFIGURE_CAMERA_CHAIN
#  endif // CONFIGURE_SCREENCAP_CHAIN
#endif // CONFIGURE_COMPOSITING_CHAIN
!LinkElements   (audio_in_queue , audio_converter)      ||
      !LinkElements      (audio_converter , audio_encoder  )                ||
      !LinkElements      (audio_encoder   , audio_parser   )                ||
// !LinkElements   (audio_parser    , audio_enc_caps )         ||
//       !LinkElements   (audio_enc_caps    , audio_enc_queue)                            ||
      !LinkElements      (audio_parser    , audio_enc_queue)                ||
!LinkElements   (audio_enc_queue , audio_enc_queue2)        ||
!LinkElements   (audio_enc_queue2 , audio_enc_queue3)       ||
!LinkElements   (audio_enc_queue3 , audio_enc_queue4)       ||
      !LinkElements      (audio_enc_queue4 , mux            )               ||
      !MakeStaticGhostPad(MuxBin , audio_in_queue , "sink" , "audio-sink")  ||
      !LinkElements      (AudioBin , MuxBin) ||
      !MakeStaticGhostPad(MuxBin , mux            , "src"  , "mux-source")   )
  { Error(GUI::MUX_LINK_ERROR_MSG) ; return false ; }

#else // CONFIGURE_MUX_CHAIN
Trace::TraceState("bypassing muxer configuration") ;
#endif // CONFIGURE_MUX_CHAIN

  return true ;
}

bool AvCaster::ConfigureOutput()
{
#ifdef CONFIGURE_OUTPUT_CHAIN

  GstElement *queue , *sink ;

  int    stream_n    = int   (Config->configStore[CONFIG::OUTPUT_STREAM_ID]) ;
  String dest        = STRING(Config->configStore[CONFIG::OUTPUT_DEST_ID  ]) ;
  String stream      = CONFIG::OUTPUT_STREAMS[stream_n] ;
  File   videos_dir  = File::getSpecialLocation(File::userMoviesDirectory) ;
  File   output_file = videos_dir.getNonexistentChildFile(dest , CONFIG::FLV_CONTAINER , true) ;
  String file_url    = output_file.getFullPathName() ;
  String rtmp_url    = GST::LCTV_RTMP_URL + dest + " live=1" ;
  String plugin_id , output_url ;

rtmp_url = GST::LCTV_RTMP_URL + String(std::getenv("LIVECODING_STREAM_KEY")) + " live=1" ;

  if      (stream == CONFIG::FILE_OUTPUT) { plugin_id = "filesink" ; output_url = file_url ; }
  else if (stream == CONFIG::RTMP_OUTPUT) { plugin_id = "rtmpsink" ; output_url = rtmp_url ; }
  else                                    { Error(GUI::OUTPUT_CFG_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIG_OUTPUT

  if (!(queue = MakeElement("queue"   , "output-queue")) ||
      !(sink  = MakeElement(plugin_id , "output-sink" ))  )
  { DBG("ERR instantiating ouput"); return false ; }

  g_object_set(G_OBJECT(sink) , "location" , CHARSTAR(output_url) , NULL) ;

  if (!AddElement        (OutputBin , queue)                          ||
      !AddElement        (OutputBin , sink )                          ||
      !LinkElements      (queue , sink)                               ||
      !MakeStaticGhostPad(OutputBin , queue , "sink" , "output-sink") ||
      !LinkElements      (MuxBin , OutputBin)                          )
  { DBG("error linking output") ; return false ; }

#else // CONFIGURE_OUTPUT_CHAIN
Trace::TraceState("bypassing output configuration") ;
#endif // CONFIGURE_OUTPUT_CHAIN

  return true ;
}

bool AvCaster::TogglePreview()
{
  bool     is_preview_on = bool(Config->configStore[CONFIG::IS_PREVIEW_ON_ID]) ;
  GstState next_state    = (is_preview_on) ? GST_STATE_PLAYING : GST_STATE_PAUSED ;

#ifdef CONFIGURE_SCREENCAP_CHAIN
  SetGstreamerState(ScreencapBin  , next_state) ;
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
  SetGstreamerState(CameraBin     , next_state) ;
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
  SetGstreamerState(AudioBin      , next_state) ;
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
  SetGstreamerState(TextBin       , next_state) ;
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_MIXER_CHAIN
  SetGstreamerState(CompositorBin , next_state) ;
#endif // CONFIGURE_MIXER_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
  SetGstreamerState(MuxBin        , next_state) ;
#endif // CONFIGURE_MUX_CHAIN
#ifdef CONFIGURE_OUTPUT_CHAIN
  SetGstreamerState(OutputBin     , next_state) ;
#endif // CONFIGURE_OUTPUT_CHAIN

  return is_preview_on ;
}

bool AvCaster::SetGstreamerState(GstElement* a_gst_element , GstState next_state)
{
DEBUG_TRACE_SET_GST_STATE

  if (gst_element_set_state(a_gst_element , next_state) == GST_STATE_CHANGE_FAILURE)
  {
    gchar* element_name = gst_element_get_name(a_gst_element) ;
    Error(GUI::GST_STATE_ERROR_MSG + String(element_name) + "'.") ;
    g_free(element_name) ; return false ;
  }

  return true ;
}

void AvCaster::DisplayAlert()
{
  if (IsAlertModal || Alerts.size() == 0) return ;

  switch (Alerts[0]->messageType)
  {
    case GUI::ALERT_TYPE_WARNING:
      Gui->warning(Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
    case GUI::ALERT_TYPE_ERROR:
      Gui->error  (Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
    default:                                                    break ;
  }
}

GstPad* AvCaster::CreateGhostPad(GstElement* an_element , String private_pad_name ,
                                                          String public_pad_name  )
{
  const gchar*  pvt_name = CHARSTAR(private_pad_name) ;
  const gchar*  pub_name = CHARSTAR(public_pad_name ) ;
  GstPad       *private_pad , *public_pad ;

  bool is_err = !(private_pad = gst_element_get_static_pad(an_element , pvt_name)   ) ||
                !(public_pad  = gst_ghost_pad_new         (pub_name   , private_pad)) ||
                !(gst_pad_set_active(public_pad , TRUE)                             )  ;

  gst_object_unref(private_pad) ;

  return (is_err) ? nullptr : public_pad ;
}

GstElement* AvCaster::MakeElement(String plugin_id , String element_id)
{
  GstElement* new_element = gst_element_factory_make(CHARSTAR(plugin_id) , CHARSTAR(element_id)) ;

DEBUG_TRACE_MAKE_ELEMENT

  return new_element ;
}

GstCaps* AvCaster::MakeCaps(String caps_str)
{
  GstCaps* new_caps = gst_caps_from_string(CHARSTAR(caps_str)) ;

DEBUG_TRACE_MAKE_CAPS

  return new_caps ;
}

bool AvCaster::AddElement(GstElement* a_bin , GstElement* an_element)
{
  bool is_err = !gst_bin_add(GST_BIN(a_bin) , an_element) ;

if (is_err)
{
  DBG("is_err") ;
}

DEBUG_TRACE_ADD_ELEMENT

  return !is_err ;
}

bool AvCaster::LinkElements(GstElement* source , GstElement* sink)
{
  bool is_err = !gst_element_link(source , sink) ;

DEBUG_TRACE_LINK_ELEMENTS

  return !is_err ;
}

bool AvCaster::MakeStaticGhostPad(GstElement* a_bin          , GstElement* an_element   ,
                                  String      private_pad_id , String      public_pad_id)
{
  const gchar*  private_id = CHARSTAR(private_pad_id) ;
  const gchar*  public_id  = CHARSTAR(public_pad_id ) ;
  GstPad       *private_pad , *public_pad ;

  bool is_err = !(private_pad = gst_element_get_static_pad(an_element , private_id )) ||
                !(public_pad  = gst_ghost_pad_new         (public_id  , private_pad)) ||
                !gst_pad_set_active(public_pad , TRUE)                                 ;

  gst_object_unref(private_pad) ;

DEBUG_TRACE_MAKE_GHOST_PAD

  if (is_err) return false ;

  is_err = !gst_element_add_pad(a_bin , public_pad) ;

DEBUG_TRACE_ADD_GHOST_PAD

  return !is_err ;
}

GstPad* AvCaster::MakeRequestGhostPad(GstElement* a_bin          , GstElement* an_element   ,
                                      String      private_pad_id , String      public_pad_id)
{
  const gchar*  private_id = CHARSTAR(private_pad_id) ;
  const gchar*  public_id  = CHARSTAR(public_pad_id ) ;
  GstPad       *private_pad , *public_pad ;

  bool is_err = !(private_pad = gst_element_get_request_pad(an_element , private_id))  ||
                !(public_pad  = gst_ghost_pad_new          (public_id  , private_pad)) ||
                !gst_pad_set_active(public_pad , TRUE)                                  ;

  gst_object_unref(private_pad) ;

DEBUG_TRACE_MAKE_GHOST_PAD

  if (is_err) return nullptr ;

  is_err = !gst_element_add_pad(a_bin , public_pad) ;

DEBUG_TRACE_ADD_GHOST_PAD

  return private_pad ;
}
