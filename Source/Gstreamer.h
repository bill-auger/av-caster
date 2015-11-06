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
  static bool ConfigurePipeline    () ;
  static bool ConfigureScreencap   () ;
  static bool ConfigureCamera      () ;
  static bool ConfigureText        () ;
  static bool ConfigureInterstitial() ;
  static bool ConfigureCompositor  () ;
  static bool ConfigurePreview     () ;
  static bool ConfigureAudio       () ;
  static bool ConfigureMuxer       () ;
  static bool ConfigureOutput      () ;
  static bool Reconfigure          (const Identifier& config_key) ;
//   static bool ReconfigureBin       (String      bin_id       , GstElement* a_bin) ;

    // state
  static bool SetState(GstElement* an_element , GstState next_state) ;

  // element creation and destruction
  static GstElement* NewPipeline      (String pipeline_id) ;
  static GstElement* NewBin           (String bin_id) ;
  static GstElement* NewElement       (String plugin_id , String element_id) ;
  static GstCaps*    NewCaps          (String caps_str) ;
  static bool        AddElement       (GstElement* a_bin , GstElement* an_element) ;
  static void        DeleteElement    (GstElement* an_element) ;
  static bool        AddBin           (GstElement* a_bin) ;
  static bool        RemoveBin        (GstElement* a_bin) ;
  static void        DestroyBin       (GstElement* a_bin) ;
  static GstElement* RecreateBin      (GstElement* a_bin , String bin_id) ;
  static bool        LinkElements     (GstElement* source , GstElement* sink) ;
  static bool        LinkPads         (GstPad* srcpad , GstPad* sinkpad) ;
  static GstPad*     NewGhostSrcPad   (GstElement* a_bin         , GstElement* an_element ,
                                       String      public_pad_id                          ) ;
  static GstPad*     NewGhostSinkPad  (GstElement* a_bin         , GstElement* an_element ,
                                       String      public_pad_id                          ) ;
  static GstPad*     NewGhostPad      (GstElement* a_bin          , GstElement* an_element   ,
                                       String      private_pad_id , String      public_pad_id) ;
  static bool        AddGhostPad      (GstElement* a_bin , GstPad* public_pad) ;
  static GstPad*     NewStaticSinkPad (GstElement* an_element) ;
  static GstPad*     NewStaticSrcPad  (GstElement* an_element) ;
  static GstPad*     NewStaticPad     (GstElement* an_element , String template_id) ;
  static GstPad*     NewRequestSinkPad(GstElement* an_element) ;
  static GstPad*     NewRequestSrcPad (GstElement* an_element) ;
  static GstPad*     NewRequestPad    (GstElement* an_element , String template_id) ;

  // helpers
  static String MakeVideoCapsString (int width , int height , int framerate) ;
  static String MakeScreenCapsString(int screencap_w , int screencap_h , int framerate) ;
  static String MakeCameraCapsString(int camera_w , int camera_h , int framerate) ;
  static String MakeAudioCapsString (String format , int samplerate , int n_channels) ;
  static String MakeH264CapsString  (int output_w , int output_h , int framerate) ;
  static String MakeMp3CapsString   (int samplerate , int n_channels) ;
  static String MakeLctvUrl         (String dest) ;
  static bool   IsPlaying           () ;
  static bool   IsInPipeline        (GstElement* an_element) ;


  // pipeline
  static GstElement* Pipeline ;
  static GstElement* ScreencapBin ;
  static GstElement* CameraBin ;
  static GstElement* TextBin ;
  static GstElement* InterstitialBin ;
  static GstElement* CompositorBin ;
  static GstElement* PreviewBin ;
  static GstElement* AudioBin ;
  static GstElement* MuxerBin ;
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
