/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/

#include <gst/interfaces/xoverlay.h>

#include "AvCaster.h"
#include "Trace/Trace.h"


/* AvCaster class variables */

// JUCEApplication* AvCaster::App = nullptr ; // Initialize()
MainContent*            AvCaster::Gui              = nullptr ; // Initialize()
GstElement*             AvCaster::OutputMonitorGst = nullptr ; // Initialize()
ScopedPointer<AvStream> AvCaster::MuxStream        = nullptr ; // Initialize()
Array<Alert*>           AvCaster::Alerts ;
bool                    AvCaster::IsAlertModal     = false ;   // Warning() , Error()


/* AvCaster class methods */

bool AvCaster::Initialize(MainContent* main_content , const String& args)
// bool AvCaster::Initialize(JUCEApplication* main_app , MainContent* main_content , const String& args)
{
//   App = main_app ;
  Gui       = main_content ;
  MuxStream = new AvStream(APP::MUX_THREAD_NAME) ;

  if (!SetVideoWindowHandles()) return false ;

  return true ;
}

bool AvCaster::SetVideoWindowHandles()
{
  //GstBus *bus;
  // initialize gStreamer
  int argc = 0 ; char** argv = {0} ; gst_init(&argc , &argv) ;
  OutputMonitorGst = gst_element_factory_make("playbin2" , "playbin2") ;
  if (!OutputMonitorGst) { AvCaster::Error(GUI::GST_INIT_ERROR_MSG) ; return false ; }

  // set GUI handles
  Component* outputMonitor = Gui->outputConfig->findChildWithID(GUI::OUTPUT_MONITOR_GUI_ID) ;
  if (outputMonitor != nullptr)
  {
    guintptr window_handle = (guintptr)(outputMonitor->getWindowHandle()) ;
    gst_x_overlay_set_window_handle(GST_X_OVERLAY(OutputMonitorGst) , window_handle) ;
  }
  else return false ;

char* SampleVideo = "http://docs.gstreamer.com/media/sintel_trailer-480p.webm" ;
  g_object_set(OutputMonitorGst , "uri" , SampleVideo , NULL) ;
  if (gst_element_set_state(OutputMonitorGst , GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
  { AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ; return false ; }

  return true ;
}

void AvCaster::Shutdown()
{
DBG("AvCaster::Shutdown()") ;

  Alerts.clear() ;

  if (!MuxStream->stopThread(2000)) { DBG("AvCaster::Shutdown() forcefully killing all avconv processes") ; system("killall avconv") ; }
//   App = nullptr ;
  MuxStream = nullptr ;

  gst_element_set_state(OutputMonitorGst , GST_STATE_NULL) ;
  gst_object_unref(OutputMonitorGst) ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID:
      if (MuxStream->isThreadRunning()) UpdateStatusGUI() ;
      break ;
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
    case APP::GUI_TIMER_LO_ID:
      if (!MuxStream->isThreadRunning()) MuxStream->startThread() ;
      break ;
  }
}

void AvCaster::UpdateStatusGUI()
{
  Gui->statusbar->setStatusL("Frame: "    + String(MuxStream->currentFrame  ) + " " +
                             "FPS: "      + String(MuxStream->currentFps    )) ;
  Gui->statusbar->setStatusC("Bitrate: "  + String(MuxStream->currentBitrate) + " " +
                             "Q: "        + String(MuxStream->currentQ      )) ;
  Gui->statusbar->setStatusR("Filesize: " + String(MuxStream->currentSize   ) + " " +
                             "Duration: " + String(MuxStream->currentTime   )) ;
}

void AvCaster::Warning(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_WARNING , message_text)) ;
}

void AvCaster::Error(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_ERROR , message_text)) ;
}

ModalComponentManager::Callback* AvCaster::getModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }


/* AvStream instance methods */

void AvStream::run()
{
  Trace::TraceState("starting '" + this->getThreadName() +"' process") ;

  if (threadShouldExit() || !isSystemSane()) { signalThreadShouldExit() ; return ; }

  detectDisplayDimensions() ;
  Trace::TraceState("detected desktop dimensions " + String(this->desktopW) + "x" + String(this->desktopH)) ;

  detectCaptureDevices() ;
  Trace::TraceState("detected " + String(this->cameraDevices.size()) + " capture devices") ;

  sanitizeParams() ;

return ;

#ifndef NO_STREAM_OUT
  while (!threadShouldExit()) sleep(APP::MUX_THREAD_SLEEP) ; return ;
#endif // NO_STREAM_OUT
DBG("AvStream::run() cmd='" + buildAvconvMuxCommand() + "'") ;

  // start avconv process and restart if it dies unexpectedly
  while (!threadShouldExit())
  {
    Trace::TraceState("restarting stream") ;

    if (!this->proc->start(buildAvconvMuxCommand()))
    { AvCaster::Error(GUI::SHELL_ERROR_MSG) ; signalThreadShouldExit() ; return ; }

// TODO: we're spinning wild somewhere here
DBG("areRuntimeErrors outer=" + String(areRuntimeErrors())) ;

    // non-blocking read from proc pipe
    while (!threadShouldExit() && this->proc->isRunning() && !areRuntimeErrors())
    {
      sleep(APP::MUX_THREAD_SLEEP) ;
      while (!threadShouldExit() && !!readProcOutputLines())
      {
        // dump avconv output
        String* line = this->proc_out_lines.begin() ;
        while (line != this->proc_out_lines.end()) Trace::TraceAvconv(*line++) ;

DBG("areRuntimeErrors inner=" + String(areRuntimeErrors())) ;

        // break on runtim error
        if (areRuntimeErrors()) break ;

        // parse stats
        String last_line = this->proc_out_lines[this->proc_out_lines.size() - 1] ;
        if (last_line.startsWith(APP::AVCONV_STATS_PREFIX))
        {
          StringArray stats    = StringArray::fromTokens(last_line , " =" , String::empty) ;
          stats.removeEmptyStrings(true) ;
          this->currentFrame   = stats[1 ].trim().getIntValue() ;
          this->currentFps     = stats[3 ].trim().getIntValue() ;
          this->currentQ       = stats[5 ].trim().getFloatValue() ;
          this->currentSize    = stats[7 ].trim() ;
          this->currentTime    = stats[9 ].trim().getFloatValue() ;
          this->currentBitrate = stats[11].trim() ;
        }
      }

      // log state
      if      (threadShouldExit()                                        )
        Trace::TraceState(Trace::THREAD_EXIT_MSG  ) ;
      else if (!this->proc->isRunning()                                  )
        Trace::TraceError(Trace::PROCESS_ERROR_MSG) ;
      else if (String(this->proc_out).contains(APP::AVCONV_CAMERA_ERROR ))
        Trace::TraceError(Trace::CAMERA_ERROR_MSG ) ;
      else if (String(this->proc_out).contains(APP::AVCONV_NETWORK_ERROR))
        Trace::TraceError(Trace::NETWORK_ERROR_MSG) ;
    }
  }
}

void AvStream::detectDisplayDimensions()
{
#ifndef CROSS_PLATFORM_RESOLUTION_DETECTION
  if (this->proc->start(APP::DISPLAY_DIMS_COMMAND) && readProcOutput())
  {
    StringArray tokens     = StringArray::fromTokens(this->proc_out , false) ;
    tokens.removeEmptyStrings(true) ;
    int         width_idx  = tokens.indexOf(APP::DISPLAY_DIMS_WIDTH_TOKEN ) + 1 ;
    int         height_idx = tokens.indexOf(APP::DISPLAY_DIMS_HEIGHT_TOKEN) + 1 ;
    if (!!width_idx && !!height_idx)
    {
      this->desktopW = tokens[width_idx ].getIntValue() ;
      this->desktopH = tokens[height_idx].getIntValue() ;
    }
  }
  else { this->desktopW = 0 ; this->desktopH = 0 ; }
#else // CROSS_PLATFORM_RESOLUTION_DETECTION
/* the JUCE way - does not reflect resolution changes (issue #2 issue #4)
                  but would eliminate platform-specific xwininfo binary dependency
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;
  this->desktopW = area.getWidth() ;
  this->desktopH = area.getHeight() ;
*/
#endif // CROSS_PLATFORM_RESOLUTION_DETECTION
}

void AvStream::detectCaptureDevices()
{
#ifndef _WIN32
#  ifndef _MAC
  File*       capture_devices_dir = new File(APP::CAPTURE_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->cameraDevices.clear() ;
  if (capture_devices_dir->containsSubDirectories()                                       &&
    !!capture_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
  {
    File* device_info_dir = device_info_dirs.begin() ;
    while (device_info_dir != device_info_dirs.end())
    {
      String device_name = device_info_dir->getChildFile("name").loadFileAsString() ;
      this->cameraDevices.add(device_name) ;
      ++device_info_dir ;
    }
  }
  else AvCaster::Warning(GUI::NO_CAMERAS_ERROR_MSG) ;

  return ;
#  endif // _MAC
#endif // _WIN32

/* mac and windows only (issue #6 issue #8)
// Returns a list of the available cameras on this machine.
  StringArray video_devs = juce::CameraDevice::getAvailableDevices() ;
DBG(video_devs.joinIntoString("\n")) ;
  while (video_devs.size())
  {
DBG("video_devs=" + video_devs[0]) ;

    video_devs.remove(0) ;
  }
*/
/* mac and windows only (issue #6 issue #8)
You can open one of these devices by calling openDevice().
static CameraDevice* CameraDevice::openDevice   (
    int   deviceIndex,
    int   minWidth = 128,
    int   minHeight = 64,
    int   maxWidth = 1024,
    int   maxHeight = 768
  )
*/
}

void AvStream::sanitizeParams()
{
  // test selected capture device
  if (this->proc->start(APP::AVPLAY_TEST_CAM_COMMAND + this->cameraDevice))
    while (!!readProcOutputLines())
    {
      if (hasSubstring(this->proc_out_lines , APP::AVCONV_CAM_BUSY_ERROR))
        AvCaster::Warning(GUI::CAM_BUSY_ERROR_MSG) ;
    }

  // sanity check capture params
  if (this->captureW == 0 || this->offsetX + this->captureW > this->desktopW)
    this->captureW = this->desktopW ;
  if (this->captureH == 0 || this->offsetY + this->captureH > this->desktopH)
    this->captureH = this->desktopH ;
  // TODO: test for device/screen existence
//     if (deviceNotExist) this->displayDevice = 0 ;
//     if (screenNotExist) this->displayScreen = 0 ;
}

String AvStream::buildAvconvMuxCommand()
{
// TODO: these should be value holders for GUI
this->framerate = "12" ;
this->cameraResolution = "160x120" ;
this->cameraDevice = "/dev/video0" ;
this->audioInput = JACK_AUDIO ;
this->outputQuality = "faster" ;
this->outputResolution = "768x480" ;
this->videoBitrate = "800k" ;
this->samplerate = "22050" ;
this->audioBitrate = "128k";
this->outputDest = "av-caster.mp4" ;
  String screen_dev = ":" + String(this->displayDevice) + "." + String(this->displayScreen) ;
  String screen_res = String(this->captureW) + "x" + String(this->captureH) ;
  String output_gop = String(this->framerate.getIntValue() * 4) ;

  String screencap_input = "-f x11grab -s " + screen_res + " -r " + this->framerate + " -i " + screen_dev ;
  String camera_input    = "-f video4linux2 -s " + this->cameraResolution +" -i " + this->cameraDevice ;
  String alsa_input      = "-f alsa -i hw:0" ;
  String pulse_input     = "-f pulse -name ffmpeg -sample_rate " + this->samplerate + " -i default" ;
  String jack_input      = "-f jack -i " + APP::JACK_CLIENT_NAME ;
  String x264_video      = "-vcodec libx264 -preset " + this->outputQuality + " -s " + this->outputResolution +
                            " -g " + output_gop + " -vb " + this->videoBitrate + " -maxrate " + this->videoBitrate + " -bufsize " + this->videoBitrate ;
  String aac_audio       = "-acodec aac -ar " + this->samplerate + " -ab " + this->audioBitrate + " -strict experimental" ;
  String file_output     = "-f flv -y " + this->outputDest ;
  String net_output      = "rtmp://usmedia3.livecoding.tv:1935/livecodingtv/" + this->outputDest ;
  String main_input ;
  String overlay_input ;
  String audio_input ;
  String audio_output ;
  String video_output ;
  String output_stream ;
main_input = screencap_input ; // GUI nyi
/*
  switch (this->mainInput)
  {
    case AvStream::SCREENCAP_INPUT:    main_input = screencap_input ;    break ;
    case AvStream::INTERSTITIAL_INPUT: main_input = interstitial_input ; break ;
    default:                                                             break ;
  }
*/
overlay_input = camera_input ; // GUI nyi
/*
  switch (this->overlayInput)
  {
    case AvStream::CAMERA_INPUT: overlay_input = camera_input ; break ;
    case AvStream::LOGO_INPUT:   overlay_input = logo_input ;   break ;
    default:                                                    break ;
  }
*/
  switch (this->audioInput)
  {
    case AvStream::ALSA_AUDIO:  audio_input = alsa_input ;  break ;
    case AvStream::PULSE_AUDIO: audio_input = pulse_input ; break ;
    case AvStream::JACK_AUDIO:  audio_input = jack_input ;  break ;
    default:                                                break ;
  }
audio_output = aac_audio ; // GUI nyi
/*
  switch (this->audioCodec)
  {
    case AvStream::AAC_AUDIO: audio_output = aac_audio ; break ;
    case AvStream::MP3_AUDIO: audio_output = mp3_audio ; break ;
    default:                                             break ;
  }
*/
video_output = x264_video ; // GUI nyi
/*
  switch (this->videoCodec)
  {
    case AvStream::X264_VIDEO: video_output = x264_video ; break ;
    default:                                               break ;
  }
*/
output_stream = file_output ; // GUI nyi
/*
  switch (this->outputStream)
  {
    case AvStream::FILE_OUTPUT: output_stream = file_output ; break ;
    case AvStream::NET_OUTPUT:  output_stream = net_output ;  break ;
    default:                                                  break ;
  }
*/
  return "avconv " + screencap_input + " " +
                     overlay_input   + " " +
                     audio_input     + " " +
                     video_output    + " " +
                     audio_output    + " " +
                     output_stream         ;
}

bool AvStream::isSystemSane()
{
  // test binary dependencies
  if (!this->proc->start(APP::TEST_WHICH_COMMAND   ) && readProcOutput()) // TODO:not cross-platform
  { AvCaster::Error(GUI::WHICH_BIN_ERROR_MSG    ) ; return false ; }
  if (!this->proc->start(APP::TEST_AVCONV_COMMAND  ) && readProcOutput())
  { AvCaster::Error(GUI::AVCONV_BIN_ERROR_MSG   ) ; return false ; }
  if (!this->proc->start(APP::TEST_AVPLAY_COMMAND  ) && readProcOutput())
  { AvCaster::Error(GUI::AVPLAY_BIN_ERROR_MSG   ) ; return false ; }
  if (!this->proc->start(APP::TEST_X11UTILS_COMMAND) && readProcOutput()) // TODO:not cross-platform
    AvCaster::Warning(GUI::XWINIFO_BIN_ERROR_MSG) ; // non-fatal

  return true ;
}

bool AvStream::readProcOutput()
{
  this->proc_out[0] = '\0' ;
  return (this->proc->readProcessOutput(this->proc_out , APP::PROC_BUFFER_SIZE) > 0) ;
}

int AvStream::readProcOutputLines()
{
  StringArray lines ;
  if (readProcOutput())
  {
    CharPointer_UTF8 proc_out_utf8 = CharPointer_UTF8(this->proc_out) ;
    lines                          = StringArray::fromLines(this->proc_out) ;

    if (this->proc_out_tail   .isNotEmpty()     )   lines.set(0 , proc_out_tail + lines[0]) ;
    if (String(proc_out_utf8).endsWithChar('\n'))   lines.add(String::empty) ;
    this->proc_out_tail = lines[lines.size() - 1] ; lines.remove(lines.size() - 1) ;
  }

  return (this->proc_out_lines = lines).size() ;
}

String AvStream::findSubstring(StringArray haystack , String needle)
{
  String* line = haystack.begin() ;
  while (line != haystack.end())
    if (!line->contains(needle)) *line++ ; else return *line ;

  return String::empty ;
}

bool AvStream::hasSubstring(StringArray haystack , String needle)
{
  return findSubstring(haystack , needle).isNotEmpty() ;
}

bool AvStream::hasAnySubstring(StringArray haystack , StringArray needles)
{
  String* needle = needles.begin() ;
  while (needle != needles.end()) if (hasSubstring(haystack , *needle)) return true ;

  return false ;
}

bool AvStream::areRuntimeErrors()
{
  return hasAnySubstring(this->proc_out_lines , APP::AVCONV_RUNTIME_ERRORS) ;
}
