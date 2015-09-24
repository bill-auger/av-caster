/*
  ==============================================================================

    AvCaster.h
    Created: 12 Sep 2015 10:26:17am
    Author:  bill

  ==============================================================================
*/

#ifndef AVCASTER_H_INCLUDED
#define AVCASTER_H_INCLUDED


#include <gst/gst.h>

#include "Constants.h"
#include "AvCasterConfig.h"
#include "MainContent.h"


class Alert
{
public:

  Alert(GUI::AlertType message_type , String message_text)
  {
    this->messageType = message_type ;
    this->messageText = message_text ;
  }

  GUI::AlertType messageType ;
  String         messageText ;
} ;


class AvCaster
{
  friend class AvCasterApplication ;


public:

  // GUI dispatchers
  static void Warning(      String message_text) ;
  static void Error(        String message_text) ;
  static void StartMonitors() ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* GetModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;


  // persistence
  static ScopedPointer<AvCasterConfig> Config ;


private:

  // setup
  static bool Initialize(MainContent* main_content , const String& args) ;
  static bool InitGstreamer() ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer(    int timer_id) ;
  static void UpdateStatusGUI() ;

  static MainContent*  Gui ;
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;

  // gStreamer
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* ScreencapSource ;
  static GstElement* Videoconvert ;
  static GstElement* ScreencapSink ;
  static GstElement* CameraBin ;
  static GstElement* CameraSource ;
  static GstElement* CameraSink ;
//   static GstElement* TextSource ;
  static GstElement* OutputBin ;
  static GstElement* OutputSink ;
} ;

#endif  // AVCASTER_H_INCLUDED
