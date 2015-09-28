/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill-auger

  ==============================================================================
*/

#include <gst/video/videooverlay.h>

#include "AvCaster.h"
#include "Trace/Trace.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterConfig> AvCaster::Config ; // Initialize()


/* AvCaster private class variables */

MainContent*  AvCaster::Gui             = nullptr ; // Initialize()
Array<Alert*> AvCaster::Alerts ;
bool          AvCaster::IsAlertModal    = false ;   // Warning() , Error()
GstElement*   AvCaster::Pipeline        = nullptr ;
GstElement*   AvCaster::ScreencapBin    = nullptr ;
GstElement*   AvCaster::ScreencapSource = nullptr ;
GstElement*   AvCaster::Videoconvert    = nullptr ;
GstElement*   AvCaster::ScreencapSink   = nullptr ;
GstElement*   AvCaster::CameraBin       = nullptr ;
GstElement*   AvCaster::CameraSource    = nullptr ;
GstElement*   AvCaster::CameraSink      = nullptr ;
// GstElement*   AvCaster::TextSource      = nullptr ;
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
  Gui->instantiate(Config->configStore) ;

  // initialize gStreamer
  if (!InitGstreamer()) return false ;

#ifdef QUIT_IMMEDIATELY
  return false ;
#endif // QUIT_IMMEDIATELY

  return true ;
}

bool AvCaster::InitGstreamer()
{
  // instantiate pipeline
  gst_init(nullptr , nullptr) ;
  if (!(Pipeline        = gst_pipeline_new        ("xvoverlay"          )) ||
      !(ScreencapBin    = gst_bin_new             ("screencap-bin"      )) ||
//    !(ScreencapSource = gst_element_factory_make("videotestsrc" , NULL)) || // OK
      !(ScreencapSource = gst_element_factory_make("ximagesrc"    , NULL)) ||
      !(Videoconvert    = gst_element_factory_make("videoconvert" , NULL)) ||
      !(ScreencapSink   = gst_element_factory_make("xvimagesink"  , NULL)) ||
      !(CameraBin       = gst_bin_new             ("camera-bin"         )) ||
      !(CameraSource    = gst_element_factory_make("v4l2src"      , NULL)) ||
      !(CameraSink      = gst_element_factory_make("xvimagesink"  , NULL))  )//||
//       !(OutputBin       = gst_bin_new             ("output-bin"         )) ||
//       !(OutputSink      = gst_element_factory_make("xvimagesink"  , NULL))  )
  {
    AvCaster::Error(GUI::GST_INIT_ERROR_MSG) ; return false ;
  }


// TODO: none of these are working yet
// GstElement* videoconvert = gst_element_factory_make("videoconvert" , NULL) ;
// GstElement* x264enc      = gst_element_factory_make("x264enc"      , NULL) ;
// GstElement* flvmux       = gst_element_factory_make("flvmux"       , NULL) ;
// GstElement* rtmpsink     = gst_element_factory_make("rtmpsink"     , NULL) ;


// NOTE: mis-configured or blocked elements (e.g. v4l2 device already in use)
//           block all pipeline progress (other elements show only first frame)
//           (this is why we have CameraBin unused here - it is otherwise working)

  // configure pipeline
  gst_bin_add_many(GST_BIN(Pipeline    ) , ScreencapBin    , CameraBin    ,                 nullptr) ;
//   gst_bin_add_many(GST_BIN(Pipeline    ) , ScreencapBin    ,                                nullptr) ;
  gst_bin_add_many(GST_BIN(ScreencapBin) , ScreencapSource , Videoconvert , ScreencapSink , nullptr) ;
  gst_bin_add_many(GST_BIN(CameraBin   ) , CameraSource    , CameraSink   ,                 nullptr) ;
//   gst_bin_add_many(GST_BIN(OutputBin   ) , videoconvert    , x264enc       , flvmux    , OutputSink , nullptr) ;
  gst_element_link_many(                   ScreencapSource , Videoconvert , ScreencapSink , nullptr) ;
  gst_element_link_many(                   CameraSource    , CameraSink   ,                 nullptr) ;
//   gst_element_link_many(videoconvert    , x264enc       , flvmux , OutputSink , nullptr) ;

  // configure plugins
  int screencap_w = int(Config->configStore[CONFIG::SCREENCAP_W_ID]) ;
  int screencap_h = int(Config->configStore[CONFIG::SCREENCAP_H_ID]) ;
DBG("screencap_w=" + String(screencap_w) + " screencap_h=" + String(screencap_h)) ;
// screencap_w = 1680 ; screencap_h = 1050 ;
  g_object_set(G_OBJECT(ScreencapSource) , "endx"         , screencap_w - 1 , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "endy"         , screencap_h - 1 , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "use-damage"   , false           , NULL) ;
  g_object_set(G_OBJECT(ScreencapSource) , "show-pointer" , true            , NULL) ;
// g_object_set(G_OBJECT(x264enc        ) , "bitrate"      , 800   , NULL) ;
// g_object_set(G_OBJECT(flvmux         ) , "name"         , "mux" , NULL) ;
// g_object_set(G_OBJECT(flvmux         ) , "streamable"   , true  , NULL) ;
// gchar* url = "rtmp://127.0.0.1:1935/live1/live live=1" ;
// g_object_set(G_OBJECT(rtmpsink) , "location"   , url   , NULL) ;


  // attach GstreamerVideo native xwindows to gStreamer overlay sinks
  StartMonitors() ;
  guintptr screencap_window_handle = (guintptr)(Gui->screencapMonitor->getWindowHandle()) ;
  guintptr camera_window_handle    = (guintptr)(Gui->cameraMonitor   ->getWindowHandle()) ;
//   guintptr output_window_handle    = (guintptr)(Gui->outputMonitor   ->getWindowHandle()) ;
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(ScreencapSink) , screencap_window_handle) ;
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(CameraSink   ) , camera_window_handle   ) ;
//   gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(OutputSink   ) , output_window_handle   ) ;

  // set rolling
  if (gst_element_set_state(Pipeline , GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
  {
    AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ; return false ;
  }

  return true ;
}

void AvCaster::Shutdown()
{
  Alerts.clear() ;
  Config = nullptr ;

  // cleanup gStreamer
  gst_element_set_state(Pipeline , GST_STATE_NULL) ;
  gst_object_unref(     Pipeline) ;
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
                             "FPS: "      + String(MuxStream->currentFps    )) ;
  Gui->statusbar->setStatusC("Bitrate: "  + String(MuxStream->currentBitrate) + " " +
                             "Q: "        + String(MuxStream->currentQ      )) ;
  Gui->statusbar->setStatusR("Filesize: " + String(MuxStream->currentSize   ) + " " +
                             "Duration: " + String(MuxStream->currentTime   )) ;
*/
}

// TODO: this method is actually unnecessary at this point (see note in issue #11)
void AvCaster::HandleConfigChanged(const Identifier& a_key) { Gui->config->loadConfig() ; }

void AvCaster::StartMonitors() { Gui->startMonitors() ; }
