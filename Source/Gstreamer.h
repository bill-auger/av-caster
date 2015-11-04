/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


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
  static void Shutdown  () ;

  // configuration
  static bool Configure              () ;
  static bool ConfigureTodo          () ;
  static bool ConfigureScreencap     () ;
  static bool ConfigureCamera        () ;
  static bool ConfigureText          () ;
  static bool ConfigureInterstitial  () ;
  static bool ConfigureCompositor    () ;
  static bool ConfigureAudio         () ;
  static bool ConfigureMux           () ;
  static bool ConfigureOutput        () ;
  static void ReconfigureOutput      () ;
  static void ReconfigureInterstitial() ;
  static void ReconfigureScreencap   () ;
  static void ReconfigureCamera      () ;
  static void ReconfigureText        () ;
  static void ReconfigurePreview     () ;

  // stream state
  static bool TogglePreview() ;
//   static bool ToggleOutput() ;
  static bool SetState     (GstElement* an_element , GstState next_state) ;

  // helpers
  static GstElement* MakeElement        (String plugin_id , String element_id) ;
  static GstCaps*    MakeCaps           (String caps_str) ;
  static bool        AddElement         (GstElement* a_bin , GstElement* an_element) ;
  static bool        AddBin             (GstElement* a_bin) ;
  static bool        RemoveBin          (GstElement* a_bin) ;
  static bool        LinkElements       (GstElement* source , GstElement* sink) ;
  static bool        LinkPads           (GstPad* srcpad , GstPad* sinkpad) ;
  static bool        AddGhostPad        (GstElement* a_bin , GstPad* public_pad) ;
  static GstPad*     AddGhostSrcPad     (GstElement* a_bin         , GstElement* an_element ,
                                         String      public_pad_id                          ) ;
  static GstPad*     AddGhostSinkPad    (GstElement* a_bin         , GstElement* an_element ,
                                         String      public_pad_id                          ) ;
  static GstPad*     AddGhostPad        (GstElement* a_bin          , GstElement* an_element   ,
                                         String      private_pad_id , String      public_pad_id) ;
  static GstPad*     NewStaticSinkPad   (GstElement* an_element) ;
  static GstPad*     NewStaticSrcPad    (GstElement* an_element) ;
  static GstPad*     NewStaticPad       (GstElement* an_element , String template_id) ;
  static GstPad*     NewRequestSinkPad  (GstElement* an_element) ;
  static GstPad*     NewRequestSrcPad   (GstElement* an_element) ;
  static GstPad*     NewRequestPad      (GstElement* an_element , String template_id) ;
  static bool        IsInPipeline       (GstElement* an_element) ;
  static String      MakeVideoCapsString(int width , int height , int framerate) ;
  static String      MakeLctvUrl        (String dest) ;


  // pipeline
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* CameraBin ;
  static GstElement* TextBin ;
  static GstElement* InterstitialBin ;
  static GstElement* CompositorBin ;
  static GstElement* AudioBin ;
  static GstElement* MuxBin ;
  static GstElement* OutputBin ;

  // configuration
  static ValueTree ConfigStore ;
  static guintptr  WindowHandle ;
} ;

#endif // GSTREAMER_H_INCLUDED


/* CompositorBin topology
=> static sink
-> static src
<? ghost sink
?> ghost src
{? request src       - (corresponds to number of calls to NewRequestSrcPad())
?} request sink      - (corresponds to number of calls to NewRequestSinkPad())
<=> ghost pad link   - (corresponds to number of calls to AddGhostSinkPad() or AddGhostSrcPad())
<-> request pad link - (corresponds to number of calls to LinkPads())

  CompositorBin<? <=> =>fullscreen_queue-> <-> ?
                                                }compositor->
  CompositorBin<? <=> =>overlay_queue   -> <-> ?

  ?                                                           ?
   }compositor-> =>capsfilter-> =>converter-> =>composite_tee{
  ?                                                           ?

                   ? <-> =>composite_sink_queue->     =>composite_sink
  =>composite-tee {
                   ? <-> =>composite_thru_queue-> <=> ?>CompositorBin
*/
