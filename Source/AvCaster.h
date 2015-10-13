/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

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
  friend class AvCasterConfig ;


public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error(  String message_text) ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* GetModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;

  // helpers
  static StringArray DevicesNames(ValueTree a_devices_node) ;


  // persistence
  static ScopedPointer<AvCasterConfig> Config ;


private:

  // setup
  static bool Initialize(MainContent* main_content , const String& args) ;
  static bool InitGstreamer() ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer(        int timer_id) ;
  static void UpdateStatusGUI() ;
  static void HandleConfigChanged(const Identifier& a_key) ;

  // stream state
  static bool ConfigureScreencap() ;
  static bool ConfigureCamera() ;
  static bool ConfigureAudio() ;
  static bool ConfigureText() ;
  static bool ConfigureCompositing() ;
  static bool ConfigureMux() ;
  static bool ConfigureOutput() ;
  static bool TogglePreview() ;
  static bool SetGstreamerState(GstElement* a_gst_element , GstState next_state) ;

  // helpers
  static void        DisplayAlert() ;
  static GstPad*     CreateGhostPad(GstElement* an_element , String private_pad_name ,
                                                         String public_pad_name  ) ;
  static GstElement* MakeElement(   String plugin_id , String element_id) ;
  static GstCaps*    MakeCaps(      String caps_str) ;
  static bool        AddElement(    GstElement* a_bin , GstElement* an_element) ;
  static bool        LinkElements(  GstElement* source , GstElement* sink) ;
  static bool        AddGhostPad(   GstElement* a_bin          , GstElement* an_element   ,
                                    String      private_pad_id , String      public_pad_id) ;

  static MainContent*  Gui ;
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;

  // gStreamer
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* ScreencapSink ;
  static GstElement* CameraBin ;
  static GstElement* CameraSink ;
  static GstElement* AudioBin ;
  static GstElement* TextBin ;
  static GstElement* MixerBin ;
  static GstElement* MixerSink ;
  static GstElement* MuxBin ;
  static GstElement* OutputBin ;
} ;

#endif  // AVCASTER_H_INCLUDED
