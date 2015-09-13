/*
  ==============================================================================

    FfmpegStreamer.h
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/

#ifndef FFMPEGSTREAMER_H_INCLUDED
#define FFMPEGSTREAMER_H_INCLUDED

#include "Constants.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "MainContent.h"


class FfmpegStream : public Thread
{
  friend class FfmpegStreamer ;


  FfmpegStream(const String& stream_name) : Thread(stream_name)
  {
    currentFrame = 0 ;   currentFps     = 0 ;
    currentQ     = 0.0 ; currentSize    = String::empty ;
    currentTime  = 0.0 ; currentBitrate = String::empty ;
  }

  void run() override ;


private:

  uint32 currentFrame ;
  uint8  currentFps ;
  float  currentQ ;
  String currentSize ;
  float  currentTime ;
  String currentBitrate ;
} ;


class FfmpegStreamer
{
  friend class FfmpegStreamerApplication ;

private:

  // setup
  static bool Initialize(MainContent* main_content , const String& args) ;
//   static bool Initialize(JUCEApplication* main_app , MainContent* main_content ,
//                          const String&    args                                 ) ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer(int timer_id) ;
  static void UpdateStatusGUI() ;

//   static JUCEApplication* App ;
  static MainContent*                Gui ;
  static ScopedPointer<FfmpegStream> MuxStream ;
} ;

#endif  // FFMPEGSTREAMER_H_INCLUDED
