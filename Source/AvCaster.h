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
  static bool Initialize(MainContent* main_content) ;
  static bool InitGstreamer() ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void UpdateStatusGUI() ;
  static void HandleConfigChanged(const Identifier& a_key) ;

  // stream state
  static bool ConfigureScreencap() ;
  static bool ConfigureCamera() ;
  static bool ConfigureAudio() ;
  static bool ConfigureText() ;
  static bool ConfigureCompositor() ;
  static bool ConfigureMux() ;
  static bool ConfigureOutput() ;
  static bool TogglePreview() ;
  static bool SetGstreamerState(GstElement* a_gst_element , GstState next_state) ;

  // helpers
  static void        DisplayAlert() ;
  static GstElement* MakeElement      (String plugin_id , String element_id) ;
  static GstCaps*    MakeCaps         (String caps_str) ;
  static bool        AddElement       (GstElement* a_bin , GstElement* an_element) ;
  static bool        LinkElements     (GstElement* source , GstElement* sink) ;
  static bool        LinkPads         (GstPad* srcpad , GstPad* sinkpad) ;
  static bool        AddGhostPad      (GstElement* a_bin , GstPad* public_pad) ;
  static GstPad*     AddGhostSrcPad   (GstElement* a_bin         , GstElement* an_element ,
                                       String      public_pad_id                          ) ;
  static GstPad*     AddGhostSinkPad  (GstElement* a_bin         , GstElement* an_element ,
                                       String      public_pad_id                          ) ;
  static GstPad*     AddGhostPad      (GstElement* a_bin          , GstElement* an_element   ,
                                       String      private_pad_id , String      public_pad_id) ;
#if ! CONFIGURE_TEES
  static GstPad*     MakeRequestSrcPad  (GstElement* a_bin         , GstElement* an_element ,
                                         String      public_pad_id                          ) ;
  static GstPad*     MakeRequestSinkPad (GstElement* a_bin         , GstElement* an_element ,
                                         String      public_pad_id                          ) ;
  static GstPad*     MakeRequestGhostPad(GstElement* a_bin          , GstElement* an_element   ,
                                         String      private_pad_id , String      public_pad_id) ;
#endif // CONFIGURE_TEES
  static GstPad*     NewStaticSinkPad (GstElement* an_element) ;
  static GstPad*     NewStaticSrcPad  (GstElement* an_element) ;
  static GstPad*     NewStaticPad     (GstElement* an_element , String template_id) ;
  static GstPad*     NewRequestSinkPad(GstElement* an_element) ;
  static GstPad*     NewRequestSrcPad (GstElement* an_element) ;
  static GstPad*     NewRequestPad    (GstElement* an_element , String template_id) ;

  static MainContent*  Gui ;
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;

  // gStreamer
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* CameraBin ;
  static GstElement* AudioBin ;
  static GstElement* TextBin ;
  static GstElement* CompositorBin ;
  static GstElement* FullscreenSink ;
  static GstElement* OverlaySink ;
  static GstElement* CompositeSink ;
  static GstElement* MuxBin ;
  static GstElement* OutputBin ;
} ;

#endif  // AVCASTER_H_INCLUDED


/* CompositorBin topology
=> static sink
-> static src
<? ghost sink
?> ghost src
{? request src
?} request sink
<=> ghost pad link   - (corresponds to number of calls to AddGhostSinkPad() or AddGhostSrcPad())
<-> request pad link - (corresponds to number of calls to LinkPads())
                                     ? <-> =>fullscreen_sink_queue-> =>FullscreenSink
CompositorBin<? <=> =>fullscreen-tee{
                                     ? <-> =>fullscreen_thru_queue-> <-> ?
                                                                          }compositor->
                                     ? <-> =>overlay_thru_queue   -> <-> ?
CompositorBin<? <=> =>overlay-tee   {
                                     ? <-> =>overlay_sink_queue   -> =>OverlaySink

?                                                           ?
 }compositor-> =>capsfilter-> =>converter-> =>composite-tee{
?                                                           ?

                                     ? <-> =>composite_sink_queue ->     =>CompositeSink
                    =>composite-tee {
                                     ? <-> =>composite_thru_queue -> <=> ?>CompositorBin
*/
