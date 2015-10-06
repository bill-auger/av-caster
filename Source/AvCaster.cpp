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

MainContent*  AvCaster::Gui             = nullptr ; // Initialize()
Array<Alert*> AvCaster::Alerts ;
bool          AvCaster::IsAlertModal    = false ;   // Warning() , Error()
GstElement*   AvCaster::Pipeline        = nullptr ;
GstElement*   AvCaster::ScreencapBin    = nullptr ;
GstElement*   AvCaster::ScreencapSource = nullptr ;
GstElement*   AvCaster::ScreencapSink   = nullptr ;
GstElement*   AvCaster::CameraBin       = nullptr ;
GstElement*   AvCaster::CameraSource    = nullptr ;
GstElement*   AvCaster::CameraSink      = nullptr ;
GstElement*   AvCaster::AudioBin        = nullptr ;
GstElement*   AvCaster::AudioSource     = nullptr ;
GstElement*   AvCaster::TextBin         = nullptr ;
GstElement*   AvCaster::TextSource      = nullptr ;
GstElement*   AvCaster::MuxBin          = nullptr ;
GstElement*   AvCaster::OutputBin       = nullptr ;
GstElement*   AvCaster::OutputSink      = nullptr ;


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
      !(ScreencapSource = gst_element_factory_make("ximagesrc"    , "screencap-src"  )) ||
      !(ScreencapSink   = gst_element_factory_make("xvimagesink"  , "screencap-sink" )) ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !(CameraBin       = gst_bin_new             ("camera-bin"                      )) ||
      !(CameraSource    = gst_element_factory_make("autovideosrc" , "camera-src"     )) ||
      !(CameraSink      = gst_element_factory_make("xvimagesink"  , "camera-sink"    )) ||
#endif // CONFIGURE_CAMERA_CHAIN
#ifdef CONFIGURE_AUDIO_CHAIN
      !(AudioBin        = gst_bin_new             ("audio-bin"                       )) ||
#endif // CONFIGURE_AUDIO_CHAIN
#ifdef CONFIGURE_TEXT_CHAIN
      !(TextBin         = gst_bin_new             ("text-bin"                        )) ||
      !(TextSource      = gst_element_factory_make("textrender"   , "text-src"       )) ||
#endif // CONFIGURE_TEXT_CHAIN
#ifdef CONFIGURE_MUX_CHAIN
      !(MuxBin          = gst_bin_new             ("mux-bin"                         )) ||
#endif // CONFIGURE_MUX_CHAIN
      !(OutputBin       = gst_bin_new             ("output-bin"                      )) ||
      !(OutputSink      = gst_element_factory_make("xvimagesink"  , "output-sink"    ))  )
  { AvCaster::Error(GUI::GST_INIT_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE2

  // configure pipeline
#ifdef CONFIGURE_SCREENCAP_CHAIN
  if (!gst_bin_add(GST_BIN(Pipeline    ) , ScreencapBin   ) ||
      !gst_bin_add(GST_BIN(ScreencapBin) , ScreencapSource) ||
      !gst_bin_add(GST_BIN(ScreencapBin) , ScreencapSink  ) ||
#else // CONFIGURE_SCREENCAP_CHAIN
  if (!true                                                 ||
#endif // CONFIGURE_SCREENCAP_CHAIN
#ifdef CONFIGURE_CAMERA_CHAIN
      !gst_bin_add(GST_BIN(Pipeline    ) , CameraBin      ) ||
      !gst_bin_add(GST_BIN(CameraBin   ) , CameraSource   ) ||
      !gst_bin_add(GST_BIN(CameraBin   ) , CameraSink     ) ||
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
//   gst_bin_add_many(GST_BIN(OutputBin   ) , videoconvert    , x264enc       , flvmux    , OutputSink , nullptr) ;
  { AvCaster::Error(GUI::GST_ADD_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE3

  // configure elements
  if (!ConfigureScreencap() || !ConfigureCamera() || !ConfigureAudio()  ||
      !ConfigureText()      || !ConfigureMux()    || !ConfigureOutput()  )
  { AvCaster::Error(GUI::GST_CONFIG_ERROR_MSG) ; return false ; }

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
  { AvCaster::Error(GUI::GST_XWIN_ERROR_MSG) ; return false ; }

DEBUG_TRACE_INIT_PHASE5

  // set rolling
  if (!SetGstreamerState(Pipeline , GST_STATE_PLAYING)) return false ;

  TogglePreview() ; return true ;
}

void AvCaster::Shutdown()
{
  Alerts.clear() ;
  Config = nullptr ;

  // cleanup gStreamer
  gst_element_set_state(Pipeline , GST_STATE_NULL) ;
  gst_object_unref     (Pipeline) ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID: UpdateStatusGUI() ;                    break ;
    case APP::GUI_TIMER_MED_ID:
      if (!IsAlertModal && Alerts.size() > 0)
        switch (Alerts[0]->messageType)
        {
          case GUI::ALERT_TYPE_WARNING:
            Gui->warning(Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
          case GUI::ALERT_TYPE_ERROR:
            Gui->error  (Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
          default:                                                    break ;
        }
      break ;
    case APP::GUI_TIMER_LO_ID:                                        break ;
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
  int screencap_w = int(Config->configStore[CONFIG::SCREENCAP_W_ID]) ;
  int screencap_h = int(Config->configStore[CONFIG::SCREENCAP_H_ID]) ;

int   video_bitrate_n = int(Config->configStore[CONFIG::BITRATE_ID]) ;
guint video_bitrate   = CONFIG::OUTPUT_BITRATES[video_bitrate_n].getIntValue() ;
GstCaps*    vcaps ;

DEBUG_TRACE_CONFIG_SCREENCAP

#  define VIDEO_CAP_CAPS "video/x-raw, width=(int)1280, height=(int)800, " \
                         "framerate=(fraction)12/1, "                      \
                         "pixel-aspect-ratio=(fraction)1/1, "
#  define VIDEO_ENC_CAPS "video/x-h264, level=(string)4.1, profile=main"
#  define AUDIO_CAP_CAPS "audio/x-raw, format=(string)S16LE, endianness=(int)1234, " \
                         "signed=(boolean)true, width=(int)16, depth=(int)16, "      \
                         "rate=(int)44100, channels=(int)2"

GstElement* video_cap_caps  = gst_element_factory_make("capsfilter"   , "screencap-cap-caps") ;
GstElement* video_cap_queue = gst_element_factory_make("queue"        , "screencap-cap-queue"           ) ;
GstElement* video_convert   = gst_element_factory_make("videoconvert" , "screencap-cvt") ;
GstElement* video_encoder   = gst_element_factory_make("x264enc"      , "screencap-encoder") ;
GstElement* video_parser    = gst_element_factory_make("h264parse"    , "screencap-parser") ;
GstElement* video_enc_caps  = gst_element_factory_make("capsfilter"   , "screencap-end-caps") ;
GstElement* video_enc_queue = gst_element_factory_make("queue"        , "screencap-enc-queue"           ) ;

  g_object_set(G_OBJECT(ScreencapSource) , "endx"         , screencap_w - 1 , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "endy"         , screencap_h - 1 , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "use-damage"   , false           , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "show-pointer" , true            , NULL) ;

g_object_set(video_encoder , "bitrate"    , video_bitrate , NULL) ;
g_object_set(video_encoder , "bframes"    , 0             , NULL) ;
vcaps = gst_caps_from_string(VIDEO_CAP_CAPS) ;
g_object_set(video_cap_caps , "caps" , vcaps , NULL) ; gst_caps_unref(vcaps) ;
vcaps = gst_caps_from_string(VIDEO_ENC_CAPS) ;
g_object_set(video_enc_caps , "caps" , vcaps , NULL) ; gst_caps_unref(vcaps) ;

//   return gst_bin_add(GST_BIN(ScreencapBin) , video_cap_caps )                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_cap_queue)                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_convert  )                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_encoder  )                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_parser   )                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_enc_caps )                       &&
//          gst_bin_add(GST_BIN(ScreencapBin) , video_enc_queue)                       &&
//          gst_element_link_many(ScreencapSource , video_cap_caps  , video_cap_queue ,
//                                video_convert   , video_encoder   , video_parser    ,
//                                video_enc_caps  , video_enc_queue , ScreencapSink   ,
//                                nullptr                                             ) ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_cap_caps )) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_cap_queue)) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_convert  )) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_encoder  )) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_parser   )) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_enc_caps )) return false ;
if (!gst_bin_add(GST_BIN(ScreencapBin) , video_enc_queue)) return false ;
if (!gst_element_link(ScreencapSource,video_cap_caps)) return false ;
if (!gst_element_link(video_cap_caps,video_cap_queue)) return false ;
#ifdef CONFIGURE_MUX_CHAIN
if (!gst_element_link(video_cap_queue,video_convert)) return false ;
if (!gst_element_link(video_convert ,video_encoder  )) return false ;
if (!gst_element_link(video_encoder ,video_parser  )) return false ;
if (!gst_element_link(video_parser  ,video_enc_caps )) return false ;
if (!gst_element_link(video_enc_caps ,video_enc_queue )) return false ;
GstPad* queue_src_pad     = gst_element_get_static_pad(video_enc_queue , "source") ;
GstPad* screencap_src_pad = gst_ghost_pad_new("source" , queue_src_pad) ;
gst_pad_set_active(screencap_src_pad , TRUE) ;
gst_element_add_pad(ScreencapBin , screencap_src_pad) ;
gst_object_unref(queue_src_pad) ;
#else // CONFIGURE_MUX_CHAIN
if (!gst_element_link(video_convert ,ScreencapSink)) return false ;
#endif // CONFIGURE_MUX_CHAIN

  return true ;
#else // CONFIGURE_SCREENCAP_CHAIN
  return true ;
#endif // CONFIGURE_SCREENCAP_CHAIN
}

bool AvCaster::ConfigureCamera()
{
#ifdef CONFIGURE_CAMERA_CHAIN
  int camera_dev_n = int(Config->configStore[CONFIG::CAMERA_DEV_ID]) ;
  int camera_res_n = int(Config->configStore[CONFIG::CAMERA_RES_ID]) ;

DEBUG_TRACE_CONFIG_CAMERA

  return Config->cameraDevices.getNumProperties() == 0             ||
         gst_element_link_many(CameraSource , CameraSink , nullptr) ;
#else // CONFIGURE_CAMERA_CHAIN
  return true ;
#endif // CONFIGURE_CAMERA_CHAIN
}

bool AvCaster::ConfigureAudio()
{
#ifdef CONFIGURE_AUDIO_CHAIN
  int    audio_api = int(Config->configStore[CONFIG::AUDIO_API_ID]) ;
  String api_name  = CONFIG::AUDIO_APIS[audio_api] ; String plugin_id ;

  switch ((AvCasterConfig::AudioApi)audio_api)
  {
    case AvCasterConfig::ALSA_AUDIO:  plugin_id = "alsasrc" ;      break ;
    case AvCasterConfig::PULSE_AUDIO: plugin_id = "pulsesrc" ;     break ;
    case AvCasterConfig::JACK_AUDIO:  plugin_id = "jackaudiosrc" ; break ;
    default: AvCaster::Error(GUI::AUDIO_API_ERROR_MSG + api_name) ;
             return false ;                                        break ;
  }

DEBUG_TRACE_CONFIG_AUDIO

// TODO: link to output mux instead
GstElement* null_sink = gst_element_factory_make("fakesink" , NULL) ;
// GstElement* null_sink = gst_element_factory_make("autoaudiosink" , NULL) ;
  AudioSource = gst_element_factory_make(CHARSTAR(plugin_id) , NULL) ;

  return gst_bin_add(GST_BIN(AudioBin) , AudioSource            ) &&
         gst_bin_add(GST_BIN(AudioBin) , null_sink              ) &&
         gst_element_link_many(AudioSource , null_sink , nullptr)  ;
#else // CONFIGURE_AUDIO_CHAIN
  return true ;
#endif // CONFIGURE_AUDIO_CHAIN
}

bool AvCaster::ConfigureText()
{
#ifdef CONFIGURE_TEXT_CHAIN

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
GstElement* filesrc = gst_element_factory_make("filesrc" , "filesrc"    ) ;
GstElement* subparse = gst_element_factory_make("subparse" , "subparse"   ) ;
GstElement* textconvert = gst_element_factory_make("videoconvert" , "textconvert") ;
GstElement* null_sink = gst_element_factory_make("fakesink" , NULL) ;
// GstElement* null_sink = OutputSink ;
g_object_set(filesrc , "location" , "/code/av-caster/deleteme.srt" , NULL) ;
g_object_set(TextSource , "font-desc" , "Purisa Normal 40"  , NULL) ;
// TODO: link to compositor instead
return gst_bin_add(GST_BIN(TextBin) , filesrc    )                                                &&
       gst_bin_add(GST_BIN(TextBin) , subparse   )                                                &&
       gst_bin_add(GST_BIN(TextBin) , TextSource )                                                &&
       gst_bin_add(GST_BIN(TextBin) , textconvert)                                                &&
       gst_bin_add(GST_BIN(TextBin) , null_sink  )                                                &&
       gst_element_link_many(filesrc , subparse , TextSource , textconvert , null_sink , nullptr) ;
#else // CONFIGURE_TEXT_CHAIN
  return true ;
#endif // CONFIGURE_TEXT_CHAIN
}

bool AvCaster::ConfigureCompositing()
{
#ifdef CONFIGURE_COMPOSITING_CHAIN

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define RAW_VIDEO_CAPS_STR "video/x-raw, width=(int)" STR(1280)                     \
                           ", height=(int)" STR(800) ", framerate=(fraction)12/1, " \
                           "format=I420, pixel-aspect-ratio=(fraction)1/1, "        \
                           "interlace-mode=(string)progressive"
GstElement* compositor = gst_element_factory_make("compositor" , NULL                    ) ;
GstElement* capsfilter = gst_element_factory_make("capsfilter" , "video_mixer_capsfilter") ;
GstElement* queue      = gst_element_factory_make("queue"      , "vsink_queue"           ) ;
GstCaps* caps          = gst_caps_from_string(RAW_VIDEO_CAPS_STR) ;
g_object_set(compositor , "background"     , 1    , NULL) ;
g_object_set(OutputSink , "async-handling" , TRUE , NULL) ;
g_object_set(capsfilter , "caps"           , caps , NULL) ; gst_caps_unref(caps) ;
return gst_bin_add(GST_BIN(OutputBin) , compositor)                                       &&
       gst_bin_add(GST_BIN(OutputBin) , capsfilter)                                       &&
       gst_bin_add(GST_BIN(OutputBin) , queue     )                                       &&
       gst_bin_add(GST_BIN(OutputBin) , OutputSink)                                       &&
       gst_element_link_many(compositor , capsfilter , queue , OutputSink , nullptr) ;
#else // CONFIGURE_COMPOSITING_CHAIN
  return true ;
#endif // CONFIGURE_COMPOSITING_CHAIN
}

bool AvCaster::ConfigureMux()
{
#ifdef CONFIGURE_MUX_CHAIN
// gst_bin_add_many(GST_BIN(OutputBin) , videotestsrc , OutputSink , nullptr) ;
// gst_element_link_many(videotestsrc , OutputSink , nullptr) ;
// g_object_set(G_OBJECT(videotestsrc) , "pattern" , 1 , NULL) ;
  int output_w = int(Config->configStore[CONFIG::OUTPUT_W_ID]) ;
  int output_h = int(Config->configStore[CONFIG::OUTPUT_H_ID]) ;

DEBUG_TRACE_CONFIG_MUX

// TODO: factor video and audio encoding into the respective bins
//       this will couple most of the CONFIGURE_*_CHAIN debug features
#if ! defined(CONFIGURE_SCREENCAP_CHAIN) && ! defined(CONFIGURE_AUDIO_CHAIN)
DBG("creating test video and audio") ;
#  define VIDEO_CAP_CAPS "video/x-raw, width=(int)1280, height=(int)800, " \
                         "framerate=(fraction)12/1, "                      \
                         "format=I420, pixel-aspect-ratio=(fraction)1/1, " \
                         "interlace-mode=(string)progressive"
#  define VIDEO_ENC_CAPS "video/x-h264, level=(string)4.1, profile=main"
#  define AUDIO_CAP_CAPS "audio/x-raw, format=(string)S16LE, endianness=(int)1234, " \
                         "signed=(boolean)true, width=(int)16, depth=(int)16, "      \
                         "rate=(int)44100, channels=(int)2"
GstElement* video_source    = gst_element_factory_make("videotestsrc" , NULL                    ) ;
GstElement* video_cap_caps  = gst_element_factory_make("capsfilter" , "video-cap-caps") ;
GstElement* video_cap_queue = gst_element_factory_make("queue"      , "video-cap-queue"           ) ;
GstElement* video_convert   = gst_element_factory_make("videoconvert" , "video-cvt") ;
GstElement* video_encoder   = gst_element_factory_make("x264enc" , "video-encoder") ;
GstElement* video_parser    = gst_element_factory_make("h264parse" , "video-parser") ;
GstElement* video_enc_caps  = gst_element_factory_make("capsfilter" , "video-end-caps") ;
GstElement* video_enc_queue = gst_element_factory_make("queue"      , "video-enc-queue"           ) ;
int   video_bitrate_n = int(Config->configStore[CONFIG::BITRATE_ID]) ;
guint video_bitrate   = CONFIG::OUTPUT_BITRATES[video_bitrate_n].getIntValue() ;
GstCaps*    vcaps ;
g_object_set(video_source  , "is_live"    , true          , NULL) ;
g_object_set(video_encoder , "bitrate"    , video_bitrate , NULL) ;
g_object_set(video_encoder , "bframes"    , 0             , NULL) ;
vcaps = gst_caps_from_string(VIDEO_CAP_CAPS) ;
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
GstCaps*    acaps           = gst_caps_from_string(AUDIO_CAP_CAPS) ;
g_object_set(audio_source  , "is_live"    , true          , NULL) ;
g_object_set(audio_encoder , "bitrate"    , audio_bitrate , NULL) ;
g_object_set(audio_cap_caps , "caps" , acaps , NULL) ; gst_caps_unref(acaps) ;
#endif // ! defined(CONFIGURE_SCREENCAP_CHAIN) && ! defined(CONFIGURE_AUDIO_CHAIN)
GstElement* mux = gst_element_factory_make("flvmux" , "flv-mux") ;
g_object_set(mux , "streamable" , true , NULL) ;
/*
$video_caps       !             \
queue             !             \
videoconvert      !             \
x264enc bitrate=$vbitrate bframes=0
h264parse         !             \
$VIDEO_ENC_FORMAT !             \
queue             !             \
mux.                            \
$AUDIO_SRC       !                \
$audio_cap_caps    !                \
queue          !                \
lamemp3enc bitrate=$abitrate
mpegaudioparse !                \
queue          !                \
mux.                            \
flvmux name=mux streamable=true ! \
queue                         ! \
VIDEO_TEST_SRC='videotestsrc pattern=0 is-live=true'
AUDIO_TEST_SRC="audiotestsrc is-live=true"
*/

#ifndef CONFIGURE_OUTPUT_CHAIN
GstElement* null_sink = gst_element_factory_make("fakesink" , NULL) ;
#endif // CONFIGURE_OUTPUT_CHAIN

#define HARD_CODED_MUX_TO_NET_PROTOTYPE true
#if ! HARD_CODED_MUX_TO_NET_PROTOTYPE

#if ! defined(CONFIGURE_SCREENCAP_CHAIN) && ! defined(CONFIGURE_AUDIO_CHAIN)
  return gst_bin_add(GST_BIN(MuxBin) , video_source   )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_cap_caps )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_cap_queue)                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_convert  )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_encoder  )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_parser   )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_enc_caps )                              &&
         gst_bin_add(GST_BIN(MuxBin) , video_enc_queue)                              &&
         gst_element_link_many(video_source    , video_cap_caps  , video_cap_queue ,
                               video_convert   , video_encoder   , video_parser    ,
                               video_enc_caps  , video_enc_queue , nullptr         ) &&
         gst_bin_add(GST_BIN(MuxBin) , audio_source   )                              &&
         gst_bin_add(GST_BIN(MuxBin) , audio_cap_caps )                              &&
         gst_bin_add(GST_BIN(MuxBin) , audio_cap_queue)                              &&
         gst_bin_add(GST_BIN(MuxBin) , audio_encoder  )                              &&
         gst_bin_add(GST_BIN(MuxBin) , audio_parser   )                              &&
         gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue)                              &&
         gst_bin_add(GST_BIN(MuxBin) , mux            )                              &&
         gst_element_link_many(audio_source    , audio_cap_queue , audio_encoder ,
                               audio_parser    , audio_enc_queue , mux           ,
                               nullptr                                           )   &&
#else // ! defined(CONFIGURE_SCREENCAP_CHAIN) && ! defined(CONFIGURE_AUDIO_CHAIN)
GstPad* mux_video_sink_pad    = gst_element_get_static_pad(mux , "sink") ;
GstPad* muxbin_video_sink_pad = gst_ghost_pad_new("sink" , mux_video_sink_pad) ;
gst_pad_set_active(muxbin_video_sink_pad , TRUE) ;
gst_element_add_pad(MuxBin , muxbin_video_sink_pad) ;
gst_object_unref(mux_video_sink_pad) ;
  return true                                                                        &&
         gst_bin_add(GST_BIN(MuxBin) , mux)                                          &&
         gst_element_link(ScreencapBin , MuxBin)                                     &&
#endif // ! defined(CONFIGURE_SCREENCAP_CHAIN) && ! defined(CONFIGURE_AUDIO_CHAIN)
#ifndef CONFIGURE_OUTPUT_CHAIN
  gst_bin_add(GST_BIN(MuxBin) , null_sink) && gst_element_link(mux , null_sink) ;
#else // CONFIGURE_OUTPUT_CHAIN
  true ;
#endif // CONFIGURE_OUTPUT_CHAIN

#else // HARD_CODED_MUX_TO_NET_PROTOTYPE

if (!gst_bin_add(GST_BIN(MuxBin) , video_source   )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_cap_caps )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_cap_queue)                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_convert  )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_encoder  )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_parser   )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_caps )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , video_enc_queue)                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_source   )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_cap_caps )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_cap_queue)                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_encoder  )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_parser   )                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , audio_enc_queue)                                    ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , mux            )                                    ) return false ;
if (!gst_element_link(video_source,video_cap_caps)) return false ;
if (!gst_element_link(video_cap_caps ,video_cap_queue)) return false ;
if (!gst_element_link(video_cap_queue,video_convert   )) return false ;
if (!gst_element_link(video_convert   ,video_encoder   )) return false ;
if (!gst_element_link(video_encoder   ,video_parser    )) return false ;
if (!gst_element_link(video_parser   ,video_enc_caps   )) return false ;
if (!gst_element_link(video_enc_caps  ,video_enc_queue)) return false ;
if (!gst_element_link(video_enc_queue,mux             )) return false ;
if (!gst_element_link(audio_source   ,audio_cap_queue  )) return false ;
if (!gst_element_link(audio_cap_queue ,audio_encoder   )) return false ;
if (!gst_element_link(audio_encoder   ,audio_parser    )) return false ;
if (!gst_element_link(audio_parser    ,audio_enc_queue)) return false ;
if (!gst_element_link(audio_enc_queue ,mux             )) return false ;

// String stream_key = STRING(Config->configStore[CONFIG::OUTPUT_DEST_ID]) ;
String stream_key = String(std::getenv("LIVECODING_STREAM_KEY")) ;
String rtmp_url   = CONFIG::LCTV_RTMP_URL + stream_key + " live=1" ;
GstElement* output_queue = gst_element_factory_make("queue"    , "outpu-queue") ;
GstElement* rtmp_sink    = gst_element_factory_make("rtmpsink" , "rtmp-sink") ;
g_object_set(G_OBJECT(rtmp_sink) , "location"   , CHARSTAR(rtmp_url) , NULL) ;
if (!gst_bin_add(GST_BIN(MuxBin) , output_queue)            ) return false ;
if (!gst_bin_add(GST_BIN(MuxBin) , rtmp_sink   )            ) return false ;
if (!gst_element_link_many(mux , output_queue , rtmp_sink , nullptr) ) return false ;
  return true ;

#endif // HARD_CODED_MUX_TO_NET_PROTOTYPE

#else // CONFIGURE_MUX_CHAIN
  return true ;
#endif // CONFIGURE_MUX_CHAIN
}

bool AvCaster::ConfigureOutput()
{
#ifdef CONFIGURE_OUTPUT_CHAIN

  String stream_key = STRING(Config->configStore[CONFIG::OUTPUT_DEST_ID]) ;
  String rtmp_url   = CONFIG::LCTV_RTMP_URL + stream_key + " live=1" ;

//DEBUG_TRACE_CONFIG_OUTPUT

  GstElement* output_queue = gst_element_factory_make("queue"    , "outpu-queue") ;
  GstElement* rtmp_sink    = gst_element_factory_make("rtmpsink" , "rtmp-sink") ;

  g_object_set(G_OBJECT(rtmp_sink) , "location"   , CHARSTAR(rtmp_url) , NULL) ;

//   return gst_bin_add(GST_BIN(OutputBin) , output_queue)            &&
//          gst_bin_add(GST_BIN(OutputBin) , rtmp_sink   )            &&
//          gst_element_link_many(output_queue , rtmp_sink , nullptr) &&
//          gst_element_link_many(MuxBin       , OutputBin , nullptr)  ;
if (!gst_bin_add(GST_BIN(OutputBin) , output_queue)            ) return false ;
if (!gst_bin_add(GST_BIN(OutputBin) , rtmp_sink   )            ) return false ;
if (!gst_element_link_many(output_queue , rtmp_sink , nullptr) ) return false ;
if (!gst_element_link_many(MuxBin       , OutputBin , nullptr)  ) return false ;
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
  SetGstreamerState(OutputBin    , next_state) ;

  return is_preview_on ;
}

bool AvCaster::SetGstreamerState(GstElement* a_gst_element , GstState next_state)
{
DEBUG_TRACE_SET_GST_STATE

  if (gst_element_set_state(a_gst_element , next_state) == GST_STATE_CHANGE_FAILURE)
  {
    gchar* element_name = gst_element_get_name(a_gst_element) ;
    AvCaster::Error(GUI::GST_STATE_ERROR_MSG + String(element_name)) ;
    g_free(element_name) ; return false ;
  }

  return true ;
}
