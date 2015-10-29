#ifndef GSTREAMER_H_INCLUDED
#define GSTREAMER_H_INCLUDED

#include <gst/gst.h>

#include "Constants.h"


/**
  Gstreamer is a the media handling class for the AvCaster application.
  It encapsulates interactions with the libgstreamer C library.
*/
class Gstreamer
{
  friend class AvCaster ;

private:

  // setup
  static bool Initialize(void* x_window_handle) ;
  static void Shutdown() ;

  // configuration
  static bool Configure() ;
  static bool ConfigureScreencap() ;
  static bool ConfigureCamera() ;
  static bool ConfigureText() ;
  static bool ConfigureCompositor() ;
  static bool ConfigureAudio() ;
  static bool ConfigureInterstitial() ;
  static bool ConfigureMux() ;
  static bool ConfigureOutput() ;

  // stream state
  static bool TogglePreview() ;
//   static bool ToggleOutput() ;
  static bool SetState(GstElement* an_element , GstState next_state) ;

  // helpers
  static GstElement* MakeElement      (String plugin_id , String element_id) ;
  static GstCaps*    MakeCaps         (String caps_str) ;
  static bool        AddElement       (GstElement* a_bin , GstElement* an_element) ;
  static bool        AddBin           (GstElement* a_bin) ;
  static bool        RemoveBin        (GstElement* a_bin) ;
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
  static bool        IsInPipeline(     GstElement* an_element) ;
  static String      StateName(        GstState next_state) ;


  // pipeline
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* CameraBin ;
  static GstElement* TextBin ;
  static GstElement* CompositorBin ;
  static GstElement* AudioBin ;
  static GstElement* InterstitialBin ;
  static GstElement* FullscreenSink ;
  static GstElement* OverlaySink ;
  static GstElement* CompositeSink ;
  static GstElement* MuxBin ;
  static GstElement* OutputBin ;
static guintptr WindowHandle ;
} ;
#endif // GSTREAMER_H_INCLUDED


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
