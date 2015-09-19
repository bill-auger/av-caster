/*
  ==============================================================================

    GstreamerVideo.cpp
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#include <gst/interfaces/xoverlay.h>

#include "AvCaster.h"
#include "GstreamerVideo.h"


GstreamerVideo::GstreamerVideo()
{
  //GstBus *bus;
  // initialize gStreamer
  int argc = 0 ; char** argv = {0} ; gst_init(&argc , &argv) ;
  this->gstElement = gst_element_factory_make("playbin2" , "playbin2") ;
  if (!this->gstElement)
  {
    AvCaster::Error(GUI::GST_INIT_ERROR_MSG) ;
    throw (new GstreamerInitException()) ;
  }

//   setBufferedToImage(true) ;
  setOpaque(true) ;
}

bool GstreamerVideo::start()
{
char* SampleVideo = "http://docs.gstreamer.com/media/sintel_trailer-480p.webm" ;

  // get native X window handle
  if (!isOnDesktop()) addToDesktop(0) ; // ComponentPeer::windowRepaintedExplictly
  guintptr window_handle = (guintptr)(getWindowHandle()) ;
  gst_x_overlay_set_window_handle(GST_X_OVERLAY(this->gstElement) , window_handle) ;

  // attach media and begin rolling
  g_object_set(this->gstElement , "uri" , SampleVideo , NULL) ;
  if (gst_element_set_state(this->gstElement , GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
  { AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ; return false ; }

  return true ;
}

GstreamerVideo::~GstreamerVideo()
{
  gst_element_set_state(this->gstElement , GST_STATE_NULL) ;
  gst_object_unref(this->gstElement) ;
}

void GstreamerVideo::paint(Graphics& g) { }

void GstreamerVideo::resized() { }
