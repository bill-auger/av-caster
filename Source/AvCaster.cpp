/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/

#include "AvCaster.h"
#include "Trace/Trace.h"


/* AvCaster class variables */

// JUCEApplication* AvCaster::App = nullptr ; // Initialize()
MainContent*            AvCaster::Gui           = nullptr ; // Initialize()
ScopedPointer<AvStream> AvCaster::MuxStream     = nullptr ; // Initialize()
Array<Alert*>           AvCaster::Alerts ;
bool                    AvCaster::IsAlertModal  = false ;   // Warning() , Error()


/* AvCaster class methods */

bool AvCaster::Initialize(MainContent* main_content , const String& args)
// bool AvCaster::Initialize(JUCEApplication* main_app , MainContent* main_content , const String& args)
{
//   App = main_app ;
  Gui       = main_content ;
  MuxStream = new AvStream(APP::MUX_THREAD_NAME) ;

  return true ;
}

void AvCaster::Shutdown()
{
DBG("AvCaster::Shutdown()") ;

  if (!MuxStream->stopThread(2000)) { DBG("AvCaster::Shutdown() forcefully killing all avconv processes") ; system("killall avconv") ; }
//   App = nullptr ;
  MuxStream = nullptr ;
  Alerts.clear() ;
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
/*
  // the JUCE way - does not reflect resolution changes
  //                but would eliminate platform-specific xwininfo binary dependency
  Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().totalArea ;
  this->desktopW = area.getWidth() ;
  this->desktopH = area.getHeight() ;
*/
  Trace::TraceState("detected desktop dimensions " + String(desktopW) + "x" + String(desktopH)) ;

/* mac and windows only
// Returns a list of the available cameras on this machine.
  StringArray video_devs = juce::CameraDevice::getAvailableDevices() ;
DBG(video_devs.joinIntoString("\n")) ;
  while (video_devs.size())
  {
DBG("video_devs=" + video_devs[0]) ;

    video_devs.remove(0) ;
  }
*/
/* mac and windows only
You can open one of these devices by calling openDevice().
static CameraDevice* CameraDevice::openDevice   (
    int   deviceIndex,
    int   minWidth = 128,
    int   minHeight = 64,
    int   maxWidth = 1024,
    int   maxHeight = 768
  )
*/
  // get capture devices
  File*       capture_devices_dir = new File(APP::CAPTURE_DEVICES_DIR) ;
  Array<File> device_info_dirs ;
  this->captureDevices.clear() ;
  if (capture_devices_dir->containsSubDirectories()                                       &&
    !!capture_devices_dir->findChildFiles(device_info_dirs , File::findDirectories , false))
  {
    File* device_info_dir = device_info_dirs.begin() ;
    while (device_info_dir != device_info_dirs.end())
    {
      String device_name = device_info_dir->getChildFile("name").loadFileAsString() ;
      this->captureDevices.add(device_name) ;
      ++device_info_dir ;
    }
  }
  else AvCaster::Warning(GUI::NO_CAMERAS_ERROR_MSG) ;

  // test selected capture device
  if (this->proc->start(APP::AVPLAY_TEST_CAM_COMMAND + this->captureDevice))
    while (!!readProcOutputLines())
    {
      if (hasSubstring(this->proc_out_lines , APP::AVCONV_CAM_BUSY_ERROR))
        AvCaster::Warning(GUI::CAM_BUSY_ERROR_MSG) ;
    }

String SCREEN_N   = ":0.0" ; // input
String SCREEN_W   = "1280" ; // input
String SCREEN_H   = "800" ; // input
String SCREEN_RES = SCREEN_W + "x" + SCREEN_H ; // input
String STREAM_W   = "768" ; // output
String STREAM_H   = "480" ;// output
String STREAM_RES = "768x480" ;// output
uint8  FPS        = 12 ; // output (referenced both)
String CBR        = "800k" ; // output
String GOP        = String(FPS * 4) ; // implicit
String QUALITY    = "ultrafast" ; // output
//#define AUDIO_CHANNELS 2 // input
String AUDIO_SAMPLERATE = "22050" ; // input
String AUDIO_BITRATE    = "128k" ; // input

String SCREENCAP_INPUT  = "-f x11grab -s " + SCREEN_RES + " -r " + String(FPS) + " -i " + SCREEN_N ;
String JACK_INPUT       = "-f jack -i " + APP::JACK_CLIENT_NAME ;
String X264_OUUTPUT     = "-vcodec libx264 -preset " + QUALITY + " -s " + STREAM_RES +
                          " -g " + GOP + " -vb " + CBR + " -maxrate " + CBR + " -bufsize " + CBR ;
String AAC_OUTPUT       = "-acodec aac -ar " + AUDIO_SAMPLERATE + " -ab " + AUDIO_BITRATE  + " -strict experimental" ;
String DUMP_FILE        = "-y /code/livecoding.mp4" ;
// String FILE_OUTPUT      = "-f flv " + DUMP_FILE ;
String FILE_OUTPUT      = "-f flv " + DUMP_FILE ;

String MAIN_INPUT    = SCREENCAP_INPUT ;
// String OVERLAY_INPUT = WEBCAM_INPUT ;
String AUDIO_INPUT   = JACK_INPUT ;
String VIDEO_OUTPUT  = X264_OUUTPUT ;
String AUDIO_OUTPUT  = AAC_OUTPUT ;
String STREAM_OUTPUT = FILE_OUTPUT ;

String AVCONV_MUX_COMMAND = "avconv " + MAIN_INPUT    + " " +
//                                          AUDIO_INPUT   + " " +
                                        VIDEO_OUTPUT  + " " +
//                                          AUDIO_OUTPUT  + " " +
                                        STREAM_OUTPUT       ;
#ifdef NO_STREAM_OUT
  while (!threadShouldExit()) sleep(APP::MUX_THREAD_SLEEP) ; return ;
#endif // NO_STREAM_OUT
// DBG("AvStream::run() cmd='" + AVCONV_MUX_COMMAND + "'") ;

  // start avconv process and restart if it dies unexpectedly
  while (!threadShouldExit())
  {
    if (!this->proc->start(AVCONV_MUX_COMMAND))
    { AvCaster::Error(GUI::SHELL_ERROR_MSG) ; return ; }

    // non-blocking read from proc pipe
    String tail = String::empty ;
    while (!threadShouldExit() && this->proc->isRunning() && !areRuntimeErrors())
    {
      sleep(APP::MUX_THREAD_SLEEP) ;
      while (!threadShouldExit() && !!readProcOutputLines())
      {
        // dump avconv output
        String* line = this->proc_out_lines.begin() ;
        while (line != this->proc_out_lines.end()) Trace::TraceAvconv(*line++) ;

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
