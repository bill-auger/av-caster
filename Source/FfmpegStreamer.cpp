/*
  ==============================================================================

    FfmpegStreamer.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/
/*
#include <sys/types.h> // fork
#include <signal.h>    // fork
#include <unistd.h>    // fork
#include <stdio.h>
*/

#include "FfmpegStreamer.h"
#include "Trace/Trace.h"


/* FfmpegStreamer class variables */

// JUCEApplication* FfmpegStreamer::App = nullptr ; // Initialize()
MainContent*                FfmpegStreamer::Gui       = nullptr ; // Initialize()
ScopedPointer<FfmpegStream> FfmpegStreamer::MuxStream = nullptr ; // Initialize()


/* FfmpegStreamer class methods */

bool FfmpegStreamer::Initialize(MainContent* main_content , const String& args)
// bool FfmpegStreamer::Initialize(JUCEApplication* main_app , MainContent* main_content , const String& args)
{
//   App = main_app ;
  Gui = main_content ;


/*
// Returns a list of the available cameras on this machine.
  StringArray video_devs = CameraDevice::getAvailableDevices() ;
DBG(video_devs.joinIntoString("-")) ;
  while (video_devs.size())
  {
printf("video_devs=%s\n" , video_devs[0]) ;

    video_devs.remove(0) ;
  }
*/
/*


You can open one of these devices by calling openDevice().
static CameraDevice* CameraDevice::openDevice   (   int   deviceIndex,
    int   minWidth = 128,
    int   minHeight = 64,
    int   maxWidth = 1024,
    int   maxHeight = 768
  )
*/


const String MUX_STREAM_NAME = "MuxStream" ;
  MuxStream = new FfmpegStream(MUX_STREAM_NAME) ;

  return true ;
}

void FfmpegStreamer::Shutdown()
{
DBG("FfmpegStreamer::Shutdown()") ;
//   App = nullptr ;
  if (!MuxStream->stopThread(2000)) { DBG("FfmpegStreamer::Shutdown() forcefully killing all avconv processes") ; system("killall avconv") ; }
  MuxStream = nullptr ;
}

void FfmpegStreamer::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case CLIENT::GUI_TIMER_HI_ID:
      if (MuxStream->isThreadRunning()) UpdateStatusGUI() ;
      break ;

    case CLIENT::GUI_TIMER_LO_ID:
      if (!MuxStream->isThreadRunning()) MuxStream->startThread() ;

/* memory leaks (doesnt shutdown forked proc properly?)
    int pid ; if ((pid = fork()) < 0) return ;

    if (pid == 0)
    {
      printf("child\n");
      App->quit() ;
      char* args[] = {"", "", "", ""};
      execv("ls" , args) ;
    }
    else
    {
      printf("parent - child pid=%d\n" , pid) ;
      usleep(1000000) ;
      kill(pid , SIGTERM) ;
      printf("he dead\n") ;
    }
*/

      break ;
  }
}

void FfmpegStreamer::UpdateStatusGUI()
{
  Gui->statusbar->setStatusL("Frame: "    + String(MuxStream->currentFrame  ) + " " +
                             "FPS: "      + String(MuxStream->currentFps    )) ;
  Gui->statusbar->setStatusC("Bitrate: "  + String(MuxStream->currentBitrate) + " " +
                             "Q: "        + String(MuxStream->currentQ      )) ;
  Gui->statusbar->setStatusR("Filesize: " + String(MuxStream->currentSize   ) + " " +
                             "Duration: " + String(MuxStream->currentTime   )) ;
}


/* FfmpegStream class methods */

void FfmpegStream::run()
{
  Trace::TraceState("starting '" + this->getThreadName() +"' process") ;

String SCREEN_N   = ":0.0" ;
String SCREEN_W   = "1280" ;
String SCREEN_H   = "800" ;
String SCREEN_RES = "800x600" ;
String STREAM_W   = "768" ;
String STREAM_H   = "480" ;
String STREAM_RES = "768x480" ;
uint8  FPS        = 12 ;
String CBR        = "800k" ;
String GOP        = String(FPS * 4) ;
//#define AUDIO_CHANNELS 2
String AUDIO_SAMPLERATE = "22050" ;
String AUDIO_BITRATE    = "128k" ;
String QUALITY          = "ultrafast" ;

String SCREENCAP_INPUT  = "-f x11grab -s " + SCREEN_RES + " -r " + String(FPS) + " -i " + SCREEN_N ;
String JACK_CLIENT_NAME = GUI::APP_NAME ;
String JACK_INPUT       = "-f jack -i " + JACK_CLIENT_NAME ;
String X264_OUUTPUT     = "-vcodec libx264 -preset " + QUALITY + " -s " + STREAM_RES +
                          " -g " + GOP + " -vb " + CBR + " -maxrate " + CBR + " -bufsize " + CBR ;
String AAC_OUTPUT       = "-acodec aac -ar " + AUDIO_SAMPLERATE + " -ab " + AUDIO_BITRATE  + " -strict experimental" ;
String DUMP_FILE        = "-y /code/livecoding.mp4" ;
// String FILE_OUTPUT      = "-f flv " + DUMP_FILE ;
String FILE_OUTPUT      = "-f flv " + DUMP_FILE ;

String MAIN_INPUT    = SCREENCAP_INPUT ;
String AUDIO_INPUT   = JACK_INPUT ;
String VIDEO_OUTPUT  = X264_OUUTPUT ;
String AUDIO_OUTPUT  = AAC_OUTPUT ;
String STREAM_OUTPUT = FILE_OUTPUT ;

const uint8 POPEN_BUFFER_SIZE = 255 ;
const uint8 MUX_THREAD_SLEEP  = 125 ;
// const String AVCONV_READY_MSG        = "Press ctrl-c to stop encoding" ;
const String AVCONV_PROC_ERROR_MSG    = "FfmpegStream::run() proc error - bailing" ;
const String AVCONV_CAMERA_ERROR_MSG  = "/dev/video0: Invalid data found when processing input" ;
const String AVCONV_NETWORK_ERROR_MSG = "av_interleaved_write_frame(): Operation not permitted" ;
const String THREAD_EXIT_MSG   = "threadShouldExit() - exiting" ;
const String PROCESS_ERROR_MSG = "avconv process died - restarting" ;
const String CAMERA_ERROR_MSG  = "camera device error - restarting" ;
const String NETWORK_ERROR_MSG = "connection error - restarting" ;
const String STREAM_STATS_PREFIX = "frame=" ;

  String cmd = "avconv " + MAIN_INPUT    + " " +
//                             AUDIO_INPUT   + " " +
                           VIDEO_OUTPUT  + " " +
//                             AUDIO_OUTPUT  + " " +
                           STREAM_OUTPUT       ;
  char buffer[POPEN_BUFFER_SIZE] ;

// DBG("FfmpegStream::run() cmd='" + cmd + "'") ;

  // start avconv process and restart if it dies unexpectedly
  while (!threadShouldExit())
  {
    ChildProcess* avconv_proc = new ChildProcess() ;
    if (!avconv_proc->start(cmd)) { Trace::TraceError(AVCONV_PROC_ERROR_MSG) ; return ; }
//     if (!avconv_proc->start(cmd , ChildProcess::wantStdErr) { DBG("FfmpegStream::run() proc error - bailing") ; return ; }

    // non-blocking read from avconv_proc STDERR
    String tail = String::empty ;
    while (!threadShouldExit() && avconv_proc->isRunning()     &&
          !(String(buffer).contains(AVCONV_CAMERA_ERROR_MSG )) &&
          !(String(buffer).contains(AVCONV_NETWORK_ERROR_MSG))  )
    {
      sleep(MUX_THREAD_SLEEP) ;
      while (!threadShouldExit()                                           &&
            avconv_proc->readProcessOutput(buffer , POPEN_BUFFER_SIZE) > 0 &&
            !String(buffer).contains(AVCONV_CAMERA_ERROR_MSG )             &&
            !String(buffer).contains(AVCONV_NETWORK_ERROR_MSG)              )
      {
        StringArray lines = StringArray::fromLines(buffer) ;
        if (tail          .isNotEmpty()      ) lines.set(0 , tail + lines[0]) ;
        if (String(buffer).endsWithChar('\n')) lines.add(String::empty) ;
        tail = lines[lines.size() - 1] ; lines.remove(lines.size() - 1) ;

        // dump avconv output
        String last_line = lines[lines.size() - 1] ;
        while (lines.size()) { Trace::TraceAvconv(lines[0]) ; lines.remove(0) ; }
        if (!last_line.startsWith(STREAM_STATS_PREFIX)) continue ;

        // parse stats
        StringArray stats    = StringArray::fromTokens(last_line , " =" , String::empty) ;
        stats.removeEmptyStrings(true) ;
        this->currentFrame   = stats[1 ].trim().getIntValue() ;
        this->currentFps     = stats[3 ].trim().getIntValue() ;
        this->currentQ       = stats[5 ].trim().getFloatValue() ;
        this->currentSize    = stats[7 ].trim() ;
        this->currentTime    = stats[9 ].trim().getFloatValue() ;
        this->currentBitrate = stats[11].trim() ;
      }

      // log state
      if      (threadShouldExit()                               )
        Trace::TraceState(THREAD_EXIT_MSG  ) ;
      else if (!avconv_proc->isRunning()                        )
        Trace::TraceError(PROCESS_ERROR_MSG) ;
      else if (String(buffer).contains(AVCONV_CAMERA_ERROR_MSG ))
        Trace::TraceError(CAMERA_ERROR_MSG ) ;
      else if (String(buffer).contains(AVCONV_NETWORK_ERROR_MSG))
        Trace::TraceError(NETWORK_ERROR_MSG) ;

/*
    FILE* avconv_proc = popen(cmd.toStdString().c_str()  , "r") ;

// non-blocking popen
#include <fcntl.h>
FILE *proc = popen("tail -f /tmp/test.txt", "r");
int fd = fileno(proc);
int flags;
flags = fcntl(fd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(fd, F_SETFL, flags);

    while (!threadShouldExit()                                          &&
           fgets  (buffer , POPEN_BUFFER_SIZE , avconv_proc   ) != NULL &&
           !String(buffer).startsWith(AVCONV_CAMERA_ERROR_MSG )         &&
           !String(buffer).startsWith(AVCONV_NETWORK_ERROR_MSG)          )
      DBG("AVCONV: " + String(buffer)) ;
    pclose(avconv_proc) ;
DBG("FfmpegStream::run() loop " + String(
   (threadShouldExit()                               ) ? "threadShouldExit() - exiting" :
   (String(buffer).contains(AVCONV_CAMERA_ERROR_MSG )) ? "cam error - restarting"       :
   (String(buffer).contains(AVCONV_NETWORK_ERROR_MSG)) ? "server error - restarting"    :
                                                         "EOF - restarting"            )) ;
*/
    }
    avconv_proc->kill() ; delete avconv_proc ;
  }
}
