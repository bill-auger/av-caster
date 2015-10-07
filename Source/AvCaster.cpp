/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill-auger

  ==============================================================================
*/

#include <cstdlib>
#include <gst/video/videooverlay.h>
#include <gst/video/gstvideosink.h>

#include "AvCaster.h"
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterConfig> AvCaster::Config ; // Initialize()


/* AvCaster private class variables */

MainContent*  AvCaster::Gui           = nullptr ; // Initialize()
Array<Alert*> AvCaster::Alerts ;
bool          AvCaster::IsAlertModal  = false ;   // Warning() , Error()
GstElement*   AvCaster::Pipeline      = nullptr ;
GstElement*   AvCaster::ScreencapBin  = nullptr ;
GstElement*   AvCaster::ScreencapSink = nullptr ;
GstElement*   AvCaster::CameraBin     = nullptr ;
GstElement*   AvCaster::CameraSink    = nullptr ;
GstElement*   AvCaster::AudioBin      = nullptr ;
GstElement*   AvCaster::TextBin       = nullptr ;
GstElement*   AvCaster::MixerBin      = nullptr ;
GstElement*   AvCaster::MuxBin        = nullptr ;
GstElement*   AvCaster::OutputBin     = nullptr ;
GstElement*   AvCaster::OutputSink    = nullptr ;


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
  Gui->instantiate(Config->configStore , Config->cameraDevices, Config->audioDevices) ;

  // initialize gStreamer
  if (!InitGstreamer()) return false ;

#ifdef QUIT_IMMEDIATELY
DBG("AvCaster::Initialize() QUIT_IMMEDIATELY") ;
  return false ;
#endif // QUIT_IMMEDIATELY

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
      !(ScreencapBin    = gst_bin_new             ("screencap-bin"                   )) ||
      !(ScreencapSink   = gst_element_factory_make("xvimagesink"  , "screencap-sink" )) ||
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
#ifdef CONFIGURE_MIXER_CHAIN
      !(MxerBin         = gst_bin_new             ("mixer-bin"                       )) ||
#endif // CONFIGURE_MIXER_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
      !(MuxBin          = gst_bin_new             ("mux-bin"                         )) ||
#endif // CONFIGURE_MUX_CHAIN
      !(OutputBin       = gst_bin_new             ("output-bin"                      )) ||
      !(OutputSink      = gst_element_factory_make("xvimagesink"  , "output-sink"    ))  )
  { Error(GUI::GST_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE2

  // configure pipeline
#ifdef CONFIGURE_SCREENCAP_CHAIN
  if (!gst_bin_add(GST_BIN(Pipeline    ) , ScreencapBin   ) ||
      !gst_bin_add(GST_BIN(ScreencapBin) , ScreencapSink  ) ||
#else // CONFIGURE_SCREENCAP_CHAIN
  if (!true                                                 ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , CameraBin      ) ||
//       !gst_bin_add(GST_BIN(CameraBin   ) , CameraSink     ) ||
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , AudioBin       ) ||
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , TextBin        ) ||
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , MuxBin         ) ||
#endif // CONFIGURE_MUX_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , OutputBin      )  )
//   gst_bin_add_many(GST_BIN(OutputBin   ) , videoconvert    , x264enc       , flvmux    , OutputSink , nullptr)
  { Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE3

  // configure elements
  if (!ConfigureScreencap() || !ConfigureCamera() || !ConfigureAudio()  ||
      !ConfigureText()      || !ConfigureMux()    || !ConfigureOutput()  )
  { Error(GUI::GST_CONFIG_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE4

  // attach native xwindow to gStreamer overlay sinks
  guintptr window_handle = (guintptr)(Gui->getWindowHandle()) ;
#ifdef CONFIGURE_SCREENCAP_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(ScreencapSink) , window_handle) ;
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(CameraSink   ) , window_handle) ;
#endif // CONFIGURE_CAMERA_CHAIN
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(OutputSink   ) , window_handle) ;
#ifdef CONFIGURE_SCREENCAP_CHAIN
  if (!gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(ScreencapSink)           ,
                                              GUI::SCREENCAP_MONITOR_X , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H ) ||
#else // CONFIGURE_SCREENCAP_CHAIN
  if (false ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(CameraSink   )           ,
                                              GUI::CAMERA_MONITOR_X    , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H ) ||
#endif // CONFIGURE_CAMERA_CHAIN
      !gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(OutputSink   )           ,
                                              GUI::OUTPUT_MONITOR_X    , GUI::MONITORS_Y ,
                                              GUI::MONITORS_W          , GUI::MONITORS_H )  )
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

#  define VIDEO_CAPS "video/x-raw, width=1280, height=800, framerate=12/1, pixel-aspect-ratio=1/1"

  GstElement *screencap_source , *video_caps  ;
  GstCaps    *caps ;

  int screencap_w = int(Config->configStore[CONFIG::SCREENCAP_W_ID]) ;
  int screencap_h = int(Config->configStore[CONFIG::SCREENCAP_H_ID]) ;

DEBUG_TRACE_CONFIG_SCREENCAP

  if (!(screencap_source = gst_element_factory_make("ximagesrc"  , "screencap-input")) ||
      !(video_caps       = gst_element_factory_make("capsfilter" , "video-in-caps"  )) ||
//       !(queue            = gst_element_factory_make("queue"      , "camera-queue"   )) ||
      !(caps             = gst_caps_from_string(VIDEO_CAPS)                          )  )
    { Error(GUI::SCREENCAP_INIT_ERROR_MSG) ; return false ; }

  g_object_set(G_OBJECT(screencap_source) , "endx"         , screencap_w - 1 , NULL) ;
  g_object_set(G_OBJECT(screencap_source) , "endy"         , screencap_h - 1 , NULL) ;
  g_object_set(G_OBJECT(screencap_source) , "use-damage"   , false           , NULL) ;
  g_object_set(G_OBJECT(screencap_source) , "show-pointer" , true            , NULL) ;
  g_object_set(G_OBJECT(video_caps      ) , "caps"         , caps            , NULL) ;
  gst_caps_unref(caps) ;

//   if (!gst_bin_add        (GST_BIN(ScreencapBin) , screencap_source)                          ||
//       !gst_bin_add        (GST_BIN(ScreencapBin) , video_caps      )                          ||
//       !gst_element_link   (screencap_source , video_caps)                                     ||
//       !gst_element_add_pad(ScreencapBin , CreateGhostPad(video_caps , "src" , "screen-source")))
//   { Error(GUI::SCREENCAP_LINK_ERROR_MSG) ; return false ; }

GstPad* apad ;
GstElement *cvt = gst_element_factory_make("videoconvert" , "video-in-cvt") ;
if (!gst_bin_add        (GST_BIN(ScreencapBin) , cvt)) { DBG("cvt->ScreencapBin nfg") ; return false ; }
if (!gst_bin_add        (GST_BIN(ScreencapBin) , screencap_source)) { DBG("screencap_source->ScreencapBin nfg") ; return false ; }
if (!gst_bin_add        (GST_BIN(ScreencapBin) , video_caps      )) { DBG("video_caps->ScreencapBin nfg") ; return false ; }
if (!(apad = CreateGhostPad(screencap_source , "src" , "screen-source"))){ DBG("screenpad nfg") ; return false ; }
if (!gst_element_link   (screencap_source , cvt) ) { DBG("screencap_source->video_caps nfg") ; return false ; }
if (!gst_element_link   (cvt , video_caps)           ) { DBG("video_caps-> cvt nfg") ; return false ; }
if (!gst_element_link   (video_caps , ScreencapSink)           ) { DBG("cvt->ScreencapSink nfg") ; return false ; }
if (!gst_element_add_pad(ScreencapBin , apad)) { DBG("ghost_pad->ScreencapBin nfg") ; return false ; }

  return true ;

#else // CONFIGURE_SCREENCAP_CHAIN
  return true ;
#endif // CONFIGURE_SCREENCAP_CHAIN
}

bool AvCaster::ConfigureCamera()
{
#  define CAMERA_CAPS "video/x-raw, width=640, height=480 , framerate=30/1, format=I420"
#  define TESTVIDEO_CAPS "video/x-raw, width=(int)1280, height=(int)800, " \
                         "framerate=(fraction)12/1, "                      \
                         "format=I420, pixel-aspect-ratio=(fraction)1/1, " \
                         "interlace-mode=(string)progressive"

#ifdef CONFIGURE_CAMERA_CHAIN

  GstElement   *source , *capsfilter , *queue ;
  GstCaps*      caps ;
  String        plugin_id ;
  const gchar*  caps_str ;

  int          dev_n  = int(Config->configStore[CONFIG::CAMERA_DEV_ID]) ;
  int          res_n  = int(Config->configStore[CONFIG::CAMERA_RES_ID]) ;
  const gchar* device = CHARSTAR(String("/dev/" +
                        String(Config->cameraDevices.getPropertyName(dev_n)))) ;

#if JUCE_LINUX
  plugin_id = "v4l2src" ; caps_str = CAMERA_CAPS ;
#endif // JUCE_LINUX

#ifdef FAUX_VIDEO_SRC
plugin_id = "videotestsrc" ; caps_str = TESTVIDEO_CAPS ;
#endif // FAUX_VIDEO_SRC

DEBUG_TRACE_CONFIG_CAMERA

  if (Config->cameraDevices.getNumProperties() == 0) return true ;

//GstElement *queue ; // TODO: may not need

  if (!(source     = gst_element_factory_make(CHARSTAR(plugin_id) , "camera-input")) ||
      !(capsfilter = gst_element_factory_make("capsfilter"        , "camera-caps" )) ||
      !(queue      = gst_element_factory_make("queue"             , "camera-queue")) ||
      !(caps       = gst_caps_from_string(caps_str)                                )  )
  { Error(GUI::CAMERA_INIT_ERROR_MSG) ; return false ; }

#ifdef FAUX_VIDEO_SRC
g_object_set(source    , "is_live"    , true           , NULL) ;
#endif // FAUX_VIDEO_SRC

  g_object_set(G_OBJECT(source    ) , "device" , device , NULL) ;
  g_object_set(G_OBJECT(capsfilter) , "caps"   , caps   , NULL) ; gst_caps_unref(caps) ;

  if (!gst_bin_add        (GST_BIN(CameraBin) , source    )                           ||
      !gst_bin_add        (GST_BIN(CameraBin) , capsfilter)                           ||
      !gst_bin_add        (GST_BIN(CameraBin) , queue     )                           ||
      !gst_element_link   (source     , capsfilter)                                   ||
      !gst_element_link   (capsfilter , queue)                                        ||
      !gst_element_add_pad(CameraBin , CreateGhostPad(queue , "src" , "camera-source")))
  { Error(GUI::CAMERA_LINK_ERROR_MSG) ; return false ; }

#endif // CONFIGURE_CAMERA_CHAIN

  return true ;
}

bool AvCaster::ConfigureAudio()
{
#  define AUDIO16_CAPS "audio/x-raw, format=(string)S16LE, layout=(string)interleaved, rate=(int)44100, channels=(int)2"
#  define AUDIO32_CAPS "audio/x-raw, format=(string)F32LE, layout=(string)interleaved, rate=(int)44100, channels=(int)2"
#  define TESTAUDIO_CAPS "audio/x-raw, format=(string)S16LE, endianness=(int)1234, " \
                         "signed=(boolean)true, width=(int)16, depth=(int)16, "      \
                         "rate=(int)44100, channels=(int)2"

#ifdef CONFIGURE_AUDIO_CHAIN

  GstElement *source , *capsfilter , *queue ;
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

  if (!(source     = gst_element_factory_make(plugin_id    , "audio-real-source")) ||
      !(capsfilter = gst_element_factory_make("capsfilter" , "audio-in-caps"    )) ||
      !(queue      = gst_element_factory_make("queue"      , "audio-in-queue"   )) ||
      !(caps       = gst_caps_from_string(caps_str)                              )  )
    { Error(GUI::AUDIO_INIT_ERROR_MSG) ; return false ; }

  g_object_set(G_OBJECT(capsfilter) , "caps" , caps , NULL) ; gst_caps_unref(caps) ;

#ifdef FAUX_AUDIO_SRC
g_object_set(source , "is_live" , true , NULL) ;
#endif // FAUX_AUDIO_SRC

  if (!gst_bin_add        (GST_BIN(AudioBin) , source    )                            ||
      !gst_bin_add        (GST_BIN(AudioBin) , capsfilter)                            ||
      !gst_bin_add        (GST_BIN(AudioBin) , queue     )                            ||
      !gst_element_link   (source     , capsfilter)                                   ||
      !gst_element_link   (capsfilter , queue     )                                   ||
      !gst_element_add_pad(AudioBin   , CreateGhostPad(queue , "src" , "audio-source")))
    { Error(GUI::AUDIO_LINK_ERROR_MSG) ; return false ; }

// same as above but print errors
// if (!gst_bin_add(GST_BIN(AudioBin) , source ) )  { DBG("source ->AudioBin nfg"); return false ; }
// if (!gst_bin_add(GST_BIN(AudioBin) , capsfilter ) ) { DBG("capsfilter ->AudioBin nfg"); return false ; }
// if (!gst_bin_add(GST_BIN(AudioBin) , queue) ) { DBG("queue->AudioBin nfg"); return false ; }
// if (!gst_element_link(source , capsfilter)) { DBG("source->capsfilter nfg"); return false ; }
// if (!gst_element_link(capsfilter , queue)) { DBG("capsfilter->queue nfg"); return false ; }
// if (!gst_element_add_pad(AudioBin , CreateGhostPad(queue , "src" , "audio-source")) )  { DBG("audio-source->AudioBin nfg"); return false ; }

#endif // CONFIGURE_AUDIO_CHAIN

  return true ;
}

bool AvCaster::ConfigureText()
{
#ifdef CONFIGURE_TEXT_CHAIN

  GstElement *source , *filesrc , *subparse , *convert , *queue ;
  GstPad*     public_source ;

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
  if (!(source        = gst_element_factory_make("textrender"   , "text-input"   )) ||
      !(filesrc       = gst_element_factory_make("filesrc"      , "text-filesrc" )) ||
      !(subparse      = gst_element_factory_make("subparse"     , "text-subparse")) ||
      !(convert       = gst_element_factory_make("videoconvert" , "text-cvt"     )) ||
      !(queue         = gst_element_factory_make("queue"        , "text-queue"   )) ||
      !(public_source = createGhostPad          (queue , "src" , "text-source")   )  )
    { Error(GUI::TEXT_INIT_ERROR_MSG) ; return false ; }

#  ifndef CONFIGURE_COMPOSITING_CHAIN
GstElement* null_sink = gst_element_factory_make("fakesink" , NULL) ;
// GstElement* null_sink = OutputSink ;
#  endif // CONFIGURE_COMPOSITING_CHAIN

  g_object_set(filesrc , "location" , "/code/av-caster/deleteme.srt" , NULL) ;
  g_object_set(source , "font-desc" , "Purisa Normal 40"  , NULL) ;

// TODO: link to compositor instead
#  ifdef CONFIGURE_COMPOSITING_CHAIN
  if (!gst_bin_add          (GST_BIN(TextBin) , filesrc      )                       ||
      !gst_bin_add          (GST_BIN(TextBin) , subparse     )                       ||
      !gst_bin_add          (GST_BIN(TextBin) , source       )                       ||
      !gst_bin_add          (GST_BIN(TextBin) , convert      )                       ||
      !gst_bin_add          (GST_BIN(TextBin) , queue        )                       ||
      !gst_element_add_pad  (TextBin          , public_source)                       ||
      !gst_element_link_many(filesrc , subparse , source , convert , queue , nullptr) )
  { Error(GUI::TEXT_LINK_ERROR_MSG) ; return false ; }

  return true ;
#  else // CONFIGURE_COMPOSITING_CHAIN
return gst_bin_add(GST_BIN(TextBin) , filesrc    )                                                   &&
       gst_bin_add(GST_BIN(TextBin) , subparse   )                                                   &&
       gst_bin_add(GST_BIN(TextBin) , source     )                                                   &&
       gst_bin_add(GST_BIN(TextBin) , textconvert)                                                   &&
      gst_bin_add (GST_BIN(TextBin) , queue      )                                                   &&
       gst_bin_add(GST_BIN(TextBin) , null_sink  )                                                   &&
       gst_element_link_many(filesrc , subparse , source , textconvert , queue , null_sink , nullptr) ;
#  endif // CONFIGURE_COMPOSITING_CHAIN
#else // CONFIGURE_TEXT_CHAIN
  return true ;
#endif // CONFIGURE_TEXT_CHAIN
}

bool AvCaster::ConfigureCompositing()
{
#ifdef CONFIGURE_COMPOSITING_CHAIN

DEBUG_TRACE_CONFIG_MIXER

  GstElement *compositor , *capsfilter , *queue ;
  GstPad     *main_sink , *overlay_sink , *text_sink , *public_source ;
  GstCaps*   caps ;
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define RAW_VIDEO_CAPS_STR "video/x-raw, width=(int)" STR(1280)                     \
                           ", height=(int)" STR(800) ", framerate=(fraction)12/1, " \
                           "format=I420, pixel-aspect-ratio=(fraction)1/1, "        \
                           "interlace-mode=(string)progressive"

  if (!(compositor    = gst_element_factory_make("compositor" , "compositor"      )) ||
      !(capsfilter    = gst_element_factory_make("capsfilter" , "compositor-caps" )) ||
      !(queue         = gst_element_factory_make("queue"      , "compositor-queue")) ||
      !(main_sink     = createGhostPad          (queue , "sink" , "sink"  )        ) ||
      !(overlay_sink  = createGhostPad          (queue , "sink" , "sink"  )        ) ||
      !(text_sink     = createGhostPad          (queue , "sink" , "sink"  )        ) ||
      !(public_source = createGhostPad          (queue , "src"  , "mixer-source")  ) ||
      !(caps          = gst_caps_from_string    (RAW_VIDEO_CAPS_STR)               )  )
    { Error(GUI::MIXER_INIT_ERROR_MSG) ; return false ; }

g_object_set(compositor , "background"     , 1    , NULL) ;
g_object_set(OutputSink , "async-handling" , TRUE , NULL) ;
g_object_set(capsfilter , "caps"           , caps , NULL) ; gst_caps_unref(caps) ;
  if (!gst_bin_add          (GST_BIN(OutputBin) , compositor   )                    ||
      !gst_bin_add          (GST_BIN(OutputBin) , capsfilter   )                    ||
      !gst_bin_add          (GST_BIN(OutputBin) , queue        )                    ||
      !gst_bin_add          (GST_BIN(OutputBin) , OutputSink   )                    ||
      !gst_element_add_pad  (OutputBin          , main_sink    )                    ||
      !gst_element_add_pad  (OutputBin          , overlay_sink )                    ||
      !gst_element_add_pad  (OutputBin          , text_sink    )                    ||
      !gst_element_add_pad  (OutputBin          , public_source)                    ||
      !gst_element_link_many(compositor , capsfilter , queue , OutputSink , nullptr) )
  { Error(GUI::MIXER_LINK_ERROR_MSG) ; return false ; }

  return true ;
#else // CONFIGURE_COMPOSITING_CHAIN
  return true ;
#endif // CONFIGURE_COMPOSITING_CHAIN
}

// #define SELF_CONTAINED_WORKING_PROTO
#ifdef SELF_CONTAINED_WORKING_PROTO
bool AvCaster::ConfigureMux()
{
  int output_w = int(Config->configStore[CONFIG::OUTPUT_W_ID]) ;
  int output_h = int(Config->configStore[CONFIG::OUTPUT_H_ID]) ;

DEBUG_TRACE_CONFIG_MUX

#  define TESTVIDEO_CAPS "video/x-raw, width=(int)1280, height=(int)800, " \
                         "framerate=(fraction)12/1, "                      \
                         "format=I420, pixel-aspect-ratio=(fraction)1/1, " \
                         "interlace-mode=(string)progressive"
#  define VIDEO_ENC_CAPS "video/x-h264, level=(string)4.1, profile=main"
#  define TESTAUDIO_CAPS "audio/x-raw, format=(string)S16LE, endianness=(int)1234, " \
                         "signed=(boolean)true, width=(int)16, depth=(int)16, "      \
                         "rate=(int)44100, channels=(int)2"
GstElement* video_source    = gst_element_factory_make("videotestsrc" , NULL                    ) ;
GstElement* video_cap_caps  = gst_element_factory_make("capsfilter" , "video-cap-caps") ;
GstElement* video_cap_queue = gst_element_factory_make("queue"      , "video-cap-queue"           ) ;
GstElement* video_converter = gst_element_factory_make("videoconvert" , "video-cvt") ;
GstElement* video_encoder   = gst_element_factory_make("x264enc" , "video-encoder") ;
GstElement* video_parser    = gst_element_factory_make("h264parse" , "video-parser") ;
GstElement* video_enc_caps  = gst_element_factory_make("capsfilter" , "video-end-caps") ;
GstElement* video_enc_queue = gst_element_factory_make("queue"      , "video-enc-queue"           ) ;
int   video_bitrate_n = int(Config->configStore[CONFIG::VIDEO_BITRATE_ID]) ;
guint video_bitrate   = CONFIG::VIDEO_BITRATES[video_bitrate_n].getIntValue() ;
GstCaps*    vcaps ;
g_object_set(video_source  , "is_live"    , true          , NULL) ;
g_object_set(video_encoder , "bitrate"    , video_bitrate , NULL) ;
g_object_set(video_encoder , "bframes"    , 0             , NULL) ;
vcaps = gst_caps_from_string(TESTVIDEO_CAPS) ;
g_object_set(video_cap_caps , "caps" , vcaps , NULL) ; gst_caps_unref(vcaps) ;
vcaps = gst_caps_from_string(VIDEO_ENC_CAPS) ;
g_object_set(video_enc_caps , "caps" , vcaps , NULL) ; gst_caps_unref(vcaps) ;

int   audio_bitrate_n = int(Config->configStore[CONFIG::AUDIO_BITRATE_ID]) ;
guint audio_bitrate   = CONFIG::AUDIO_BITRATES[audio_bitrate_n].getIntValue() ;
GstElement* audio_source    = gst_element_factory_make("audiotestsrc" , NULL                    ) ;
GstElement* audio_cap_caps  = gst_element_factory_make("capsfilter" , "audio-caps-caps") ;
GstElement* audio_cap_queue = gst_element_factory_make("queue"      , "audio-cap-queue"           ) ;
GstElement* audio_encoder   = gst_element_factory_make("lamemp3enc" , "audio-encoder") ;
GstElement* audio_parser    = gst_element_factory_make("mpegaudioparse" , "audio-parser") ;
// TODO: we may want audio encoding caps here
GstElement* audio_enc_queue = gst_element_factory_make("queue"      , "audio-enc-queue"           ) ;
GstCaps*    acaps           = gst_caps_from_string(TESTAUDIO_CAPS) ;
g_object_set(audio_source  , "is_live"    , true          , NULL) ;
g_object_set(audio_encoder , "bitrate"    , audio_bitrate , NULL) ;
g_object_set(audio_cap_caps , "caps" , acaps , NULL) ; gst_caps_unref(acaps) ;

GstElement* mux = gst_element_factory_make("flvmux" , "flv-mux") ;
g_object_set(mux , "streamable" , true , NULL) ;

if (!gst_bin_add(GST_BIN(MuxBin) , video_source   ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_cap_caps ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_cap_queue) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_converter) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_encoder  ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_parser   ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_caps ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_queue) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_source   ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_cap_caps ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_cap_queue) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_encoder  ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_parser   ) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue) ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , mux            ) ) return false ;
if (!gst_element_link(video_source,video_cap_caps)) return false ;
if (!gst_element_link(video_cap_caps ,video_cap_queue)) return false ;
if (!gst_element_link(video_cap_queue,video_converterer )) return false ;
if (!gst_element_link(video_converter   ,video_encoder   )) return false ;
if (!gst_element_link(video_encoder   ,video_parser    )) return false ;
if (!gst_element_link(video_parser   ,video_enc_caps   )) return false ;
if (!gst_element_link(video_enc_caps  ,video_enc_queue)) return false ;
if (!gst_element_link(video_enc_queue,mux             )) return false ;
if (!gst_element_link(audio_source   ,audio_cap_queue  )) return false ;
if (!gst_element_link(audio_cap_queue ,audio_encoder   )) return false ;
if (!gst_element_link(audio_encoder   ,audio_parser    )) return false ;
if (!gst_element_link(audio_parser    ,audio_enc_queue)) return false ;
if (!gst_element_link(audio_enc_queue ,mux             )) return false ;

GstPad* ghost_src ;
GstPad* source_pad ;
if (!(ghost_src = createGhostPad(mux , "src" , "mux-source"))) { DBG("ghost_src nfg"); return false ; }
if (!gst_element_add_pad(MuxBin , ghost_src)             )  { DBG("ghost_src->MuxBin nfg"); return false ; }
if (!(source_pad = gst_element_get_static_pad(MuxBin , "mux-source") )) { DBG("src_pad nfg"); return false ; }

  return true ;
}
#else // SELF_CONTAINED_WORKING_PROTO
bool AvCaster::ConfigureMux()
{
#ifdef CONFIGURE_MUX_CHAIN

#  define VIDEO_ENC_CAPS "video/x-h264, level=(string)4.1, profile=main"
#  define AUDIO_ENC_CAPS "audio/mpeg, mpegversion=1, layer=3, mpegaudioversion=3, rate=48000, channels=2, parsed=true"

  GstElement *video_in_queue  , *video_converter , *video_encoder , *video_parser ,
             *video_enc_caps  , *video_enc_queue ;
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

  if (!(video_in_queue  = gst_element_factory_make("queue"          , "mux-video-queue")) ||
      !(video_converter = gst_element_factory_make("videoconvert"   , "video-cvt"      )) ||
      !(video_encoder   = gst_element_factory_make("x264enc"        , "video-encoder"  )) ||
      !(video_parser    = gst_element_factory_make("h264parse"      , "video-parser"   )) ||
      !(video_caps      = gst_caps_from_string(VIDEO_ENC_CAPS)                          ) ||
      !(video_enc_caps  = gst_element_factory_make("capsfilter"     , "video-enc-caps" )) ||
      !(video_enc_queue = gst_element_factory_make("queue"          , "video-enc-queue")) ||
      !(audio_in_queue  = gst_element_factory_make("queue"          , "mux-audio-queue")) ||
!(audio_converter = gst_element_factory_make("audioconvert" , "audio-cvt")) ||
      !(audio_encoder   = gst_element_factory_make("lamemp3enc"     , "audio-encoder"  )) ||
      !(audio_parser    = gst_element_factory_make("mpegaudioparse" , "audio-parser"   )) ||
// !(audio_caps      = gst_caps_from_string(AUDIO_ENC_CAPS)                          ) ||
// !(audio_enc_caps  = gst_element_factory_make("capsfilter"     , "audio-enc-caps" )) ||
      !(audio_enc_queue = gst_element_factory_make("queue"          , "audio-enc-queue")) ||
!(audio_enc_queue2 = gst_element_factory_make("queue"          , "audio-enc-queue2")) ||
!(audio_enc_queue3 = gst_element_factory_make("queue"          , "audio-enc-queue3")) ||
!(audio_enc_queue4 = gst_element_factory_make("queue"          , "audio-enc-queue4")) ||
      !(mux             = gst_element_factory_make("flvmux"         , "flv-mux"        ))  )
  { Error(GUI::MUX_INIT_ERROR_MSG) ; return false ; }

  g_object_set(video_encoder  , "bitrate"    , video_bitrate  , NULL) ;
  g_object_set(video_encoder  , "bframes"    , 0              , NULL) ;
  g_object_set(video_enc_caps , "caps"       , video_caps     , NULL) ;
//   g_object_set(audio_encoder  , "bitrate"    , audio_bitrate  , NULL) ; // TODO: CBR
// g_object_set(audio_encoder , "quality" , 2 , NULL) ; // VBR (default is 4)
// g_object_set(audio_enc_caps , "caps"       , audio_caps     , NULL) ;
  g_object_set(mux            , "streamable" , true           , NULL) ;
  gst_caps_unref(video_caps) ; //gst_caps_unref(audio_caps) ;

  if (!gst_bin_add        (GST_BIN(MuxBin) , video_in_queue )                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , video_converter)                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , video_encoder  )                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , video_parser   )                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , video_enc_caps )                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , video_enc_queue)                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , audio_in_queue )                               ||
!gst_bin_add        (GST_BIN(MuxBin) , audio_converter)         ||
      !gst_bin_add        (GST_BIN(MuxBin) , audio_encoder  )                               ||
      !gst_bin_add        (GST_BIN(MuxBin) , audio_parser   )                               ||
// !gst_bin_add        (GST_BIN(MuxBin) , audio_enc_caps )      ||
      !gst_bin_add        (GST_BIN(MuxBin) , audio_enc_queue)                               ||
!gst_bin_add        (GST_BIN(MuxBin) , audio_enc_queue2)       ||
!gst_bin_add        (GST_BIN(MuxBin) , audio_enc_queue3)       ||
!gst_bin_add        (GST_BIN(MuxBin) , audio_enc_queue4)       ||
      !gst_bin_add        (GST_BIN(MuxBin) , mux            )                               ||
      !gst_element_link   (video_in_queue  , video_converter)                               ||
      !gst_element_link   (video_converter , video_encoder  )                               ||
      !gst_element_link   (video_encoder   , video_parser   )                               ||
      !gst_element_link   (video_parser    , video_enc_caps )                               ||
      !gst_element_link   (video_enc_caps  , video_enc_queue)                               ||
      !gst_element_link   (video_enc_queue , mux            )                               ||
      !gst_element_add_pad(MuxBin , CreateGhostPad(video_in_queue , "sink" , "video-sink")) ||
      !gst_element_link   (CameraBin , MuxBin)                                              ||
!gst_element_link   (audio_in_queue , audio_converter)      ||
      !gst_element_link   (audio_converter , audio_encoder  )                               ||
      !gst_element_link   (audio_encoder   , audio_parser   )                               ||
// !gst_element_link   (audio_parser    , audio_enc_caps )         ||
//       !gst_element_link   (audio_enc_caps    , audio_enc_queue)                            ||
      !gst_element_link   (audio_parser    , audio_enc_queue)                               ||
!gst_element_link   (audio_enc_queue , audio_enc_queue2)        ||
!gst_element_link   (audio_enc_queue2 , audio_enc_queue3)       ||
!gst_element_link   (audio_enc_queue3 , audio_enc_queue4)       ||
      !gst_element_link   (audio_enc_queue4 , mux            )                              ||
      !gst_element_add_pad(MuxBin , CreateGhostPad(audio_in_queue , "sink" , "audio-sink")) ||
      !gst_element_link   (AudioBin , MuxBin) ||
      !gst_element_add_pad(MuxBin , CreateGhostPad(mux , "src" , "mux-source"))              )
  { Error(GUI::MUX_LINK_ERROR_MSG) ; return false ; }

/*
// same as above but print errors
if (!gst_bin_add(GST_BIN(MuxBin) , video_converter) ) { DBG("video_converter->MuxBin nfg") ; return false ; }
if (!gst_bin_add(GST_BIN(MuxBin) , video_encoder  ) ) { DBG("video_encoder->MuxBin nfg") ; return false ; }
if (!gst_bin_add(GST_BIN(MuxBin) , video_parser   ) ) { DBG("video_parser->MuxBin nfg") ; return false ; }
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_caps ) ) { DBG("video_enc_caps->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_queue) ) { DBG("video_enc_queue->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_converter) ) { DBG("audio_converter->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_encoder  ) ) { DBG("audio_encoder->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_parser   ) ) { DBG("audio_parser->MuxBin nfg") ; return false ; };
// if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_caps ) ) { DBG("audio_enc_caps->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue) ) { DBG("audio_enc_queue->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue2) ) { DBG("audio_enc_queue2->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue3) ) { DBG("audio_enc_queue3->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue4) ) { DBG("audio_enc_queue3->MuxBin nfg") ; return false ; };
if (!gst_bin_add(GST_BIN(MuxBin) , mux            ) ) { DBG("mux->MuxBin nfg") ; return false ; };
if (!gst_element_link(video_in_queue,video_converter   )) { DBG("video_in_queue->video_converter nfg") ; return false ; }
if (!gst_element_link(video_converter   ,video_encoder   )) { DBG("video_converter->video_encoder nfg") ; return false ; }
if (!gst_element_link(video_encoder   ,video_parser    )) { DBG("video_encoder->video_parser nfg") ; return false ; }
if (!gst_element_link(video_parser   ,video_enc_caps   )) { DBG("video_parser->video_enc_caps nfg") ; return false ; }
if (!gst_element_link(video_enc_caps  ,video_enc_queue)) { DBG("video_enc_caps->video_enc_queue nfg") ; return false ; }
if (!gst_element_link(video_enc_queue,mux             )) { DBG("video_enc_queue->mux nfg") ; return false ; }
if (!gst_element_add_pad(MuxBin , CreateGhostPad(video_in_queue , "sink" , "video-sink")))  { DBG("public_video_sink->MuxBin nfg"); return false ; }
if (!gst_element_link(CameraBin    , MuxBin)) { DBG("CameraBin->MuxBin nfg") ; return false ; }
if (!gst_element_link(audio_in_queue ,audio_converter)) { DBG("audio_in_queue->audio_converter nfg") ; return false ; }
if (!gst_element_link(audio_converter ,audio_encoder   )) { DBG("audio_converter->audio_encoder nfg") ; return false ; }
if (!gst_element_link(audio_encoder   ,audio_parser    )) { DBG("audio_encoder->audio_parser nfg") ; return false ; }
// if (!gst_element_link(audio_parser    ,audio_enc_caps)) { DBG("audio_parser->audio_enc_caps nfg") ; return false ; }
// if (!gst_element_link(audio_enc_caps, audio_enc_queue)) { DBG("audio_enc_caps->audio_enc_queue nfg") ; return false ; }
if (!gst_element_link(audio_parser    ,audio_enc_queue)) { DBG("audio_enc_caps->audio_enc_queue nfg") ; return false ; }
if (!gst_element_link(audio_enc_queue,audio_enc_queue2)) { DBG("video_enc_caps->video_enc_queue nfg") ; return false ; }
if (!gst_element_link(audio_enc_queue2,audio_enc_queue3)) { DBG("video_enc_caps->video_enc_queue nfg") ; return false ; }
if (!gst_element_link(audio_enc_queue3,audio_enc_queue4)) { DBG("video_enc_caps->video_enc_queue nfg") ; return false ; }
if (!gst_element_link(audio_enc_queue4,mux             )) { DBG("audio_enc_queue->mux nfg") ; return false ; }
if (!gst_element_add_pad(MuxBin , CreateGhostPad(audio_in_queue , "sink" , "audio-sink"))) { DBG("public_audio_sink->MuxBin nfg"); return false ; }
if (!gst_element_link(AudioBin , MuxBin)) { DBG("AudioBin->MuxBin nfg") ; return false ; }
if (!gst_element_add_pad(MuxBin , CreateGhostPad(mux , "src" , "mux-source"))) { DBG("public_source->MuxBin nfg") ; return false ; }
*/
#endif // CONFIGURE_MUX_CHAIN

  return true ;
}
#endif // SELF_CONTAINED_WORKING_PROTO

bool AvCaster::ConfigureOutput()
{
#ifdef CONFIGURE_OUTPUT_CHAIN

  GstElement *queue , *sink ;

  int    stream_n = int   (Config->configStore[CONFIG::OUTPUT_STREAM_ID]) ;
  String dest     = STRING(Config->configStore[CONFIG::OUTPUT_DEST_ID  ]) ;
  String stream   = CONFIG::OUTPUT_STREAMS[stream_n] ;
  File   videos_dir      = File::getSpecialLocation(File::userMoviesDirectory) ;
  File   output_file     = videos_dir.getNonexistentChildFile(dest , CONFIG::FLV_CONTAINER , true) ;
  String file_url        = output_file.getFullPathName() ;
  String rtmp_url        = GST::LCTV_RTMP_URL + dest + " live=1" ;
  String plugin_id , output_url ;

rtmp_url = GST::LCTV_RTMP_URL + String(std::getenv("LIVECODING_STREAM_KEY")) + " live=1" ;

  if      (stream == CONFIG::FILE_OUTPUT) { plugin_id = "filesink" ; output_url = file_url ; }
  else if (stream == CONFIG::RTMP_OUTPUT) { plugin_id = "rtmpsink" ; output_url = rtmp_url ; }
  else                                    { Error(GUI::OUTPUT_CFG_ERROR_MSG) ; return false ; }

DEBUG_TRACE_CONFIG_OUTPUT

  if (!(queue = gst_element_factory_make("queue"             , "output-queue")) ||
      !(sink  = gst_element_factory_make(CHARSTAR(plugin_id) , "output-sink" ))  )
  { DBG("ERR instantiating ouput"); return false ; }

// same as above but print errors
// if (!(queue = gst_element_factory_make("queue"             , "output-queue"))) { DBG("output_queue nfg"); return false ; }
// if (!(sink  = gst_element_factory_make(CHARSTAR(plugin_id) , "output-sink" ))) { DBG("output_sink nfg"); return false ; }

  g_object_set(G_OBJECT(sink) , "location" , CHARSTAR(output_url) , NULL) ;

  if (!gst_bin_add        (GST_BIN(OutputBin) , queue)                          ||
      !gst_bin_add        (GST_BIN(OutputBin) , sink )                          ||
      !gst_element_link   (queue , sink)                                        ||
      !gst_element_add_pad(OutputBin , CreateGhostPad(queue , "sink" , "sink")) ||
      !gst_element_link   (MuxBin    , OutputBin)                                )
  { DBG("error linking output"); return false ; }

// same as above but print errors
// if (!gst_bin_add(GST_BIN(OutputBin) , queue)) { DBG("output_queue->OutputBin nfg"); return false ; }
// if (!gst_bin_add(GST_BIN(OutputBin) , sink   )) { DBG("output_sink->OutputBin nfg"); return false ; }
// if (!gst_element_link(queue , sink)    ) { DBG("output_sink->output_queue nfg"); return false ; }
// if (!gst_element_add_pad(OutputBin , CreateGhostPad(queue , "sink" , "sink")))  { DBG("public_sink->OutputBin nfg"); return false ; }
// if (!gst_element_link(MuxBin , OutputBin)          ) { DBG("output_sink->output_queue nfg"); return false ; }

  return true ;

#else // CONFIGURE_OUTPUT_CHAIN
  return true ;
#endif // CONFIGURE_OUTPUT_CHAIN
}

bool AvCaster::TogglePreview()
{
  bool     is_preview_on = bool(Config->configStore[CONFIG::IS_PREVIEW_ON_ID]) ;
  GstState next_state    = (is_preview_on) ? GST_STATE_PLAYING : GST_STATE_PAUSED ;

#ifdef CONFIGURE_SCREENCAP_CHAIN
  SetGstreamerState(ScreencapBin , next_state) ;
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
  SetGstreamerState(CameraBin    , next_state) ;
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
  SetGstreamerState(AudioBin     , next_state) ;
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
  SetGstreamerState(TextBin      , next_state) ;
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_COMPOSITING_CHAIN
DBG("wtf") ;
  SetGstreamerState(MixerBin     , next_state) ;
#endif // CONFIGURE_COMPOSITING_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
  SetGstreamerState(MuxBin       , next_state) ;
#endif // CONFIGURE_MUX_CHAIN
#ifdef CONFIGURE_OUTPUT_CHAIN
  SetGstreamerState(OutputBin    , next_state) ;
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
