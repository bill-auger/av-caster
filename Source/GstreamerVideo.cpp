/*
  ==============================================================================

    GstreamerVideo.cpp
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#include <gst/interfaces/xoverlay.h>

#include "Trace/Trace.h"
#include "AvCaster.h"
#include "GstreamerVideo.h"


GstreamerVideo::GstreamerVideo(Component* follow_window , int local_x , int local_y)
{
  //GstBus *bus;
  // initialize gStreamer
  int argc = 0 ; char** argv = {0} ; gst_init(&argc , &argv) ;
  this->gstElement = gst_element_factory_make("playbin2" , "playbin2") ;
  if (!this->gstElement)
  {
    AvCaster::Error(GUI::GST_INIT_ERROR_MSG) ; throw (new GstreamerInitException()) ;
  }

  // initialize GUI
  this->followWindow  = follow_window ;
  this->localPosition = new Point<int>(local_x , local_y + GUI::TITLEBAR_H) ;
//   setBufferedToImage(true) ;
  setSize(GUI::MONITOR_W , GUI::MONITOR_H) ;
  setOpaque(true) ;
  setAlwaysOnTop(true) ;

// DBG("GstreamerVideo::GstreamerVideo() this->outputMonitor->getBounds()=" + getBounds().toString()) ;
// DBG("GstreamerVideo::GstreamerVideo() this->local_position=" + String(local_x) + "x" + String(local_y)) ;
// DBG("GstreamerVideo::GstreamerVideo() this->localPosition=" + this->localPosition->toString()) ;
}

GstreamerVideo::~GstreamerVideo()
{
  gst_element_set_state(this->gstElement , GST_STATE_NULL) ;
  gst_object_unref(     this->gstElement) ;
}

void GstreamerVideo::paint(Graphics& g) { }

void GstreamerVideo::resized() { }

void GstreamerVideo::componentMovedOrResized(Component& a_component , bool wasMoved  ,
                                                                      bool wasResized)
{
  setPosition() ;
}

void GstreamerVideo::setPosition()
{
// DBG("this->localPosition=" + this->localPosition->toString()) ;
// DBG("localPointToGlobal=" + followWindow->localPointToGlobal(*this->localPosition).toString()) ;

  this->setTopLeftPosition(followWindow->localPointToGlobal(*this->localPosition)) ;
}

bool GstreamerVideo::start(String uri)
{
// DEBUG_DUMP_WINDOW_HANDLES

  if (!isOnDesktop()) attachNativeWindow() ;
  if (uri.isEmpty()) return false ;

DBG("GstreamerVideo::start() launching sample") ;

  setPosition() ; setVisible(true) ;

  // attach media and begin rolling
  g_object_set(this->gstElement , "uri" , uri.toStdString().c_str() , NULL) ;
  if (gst_element_set_state(this->gstElement , GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
  { AvCaster::Error(GUI::GST_STATE_ERROR_MSG) ; return false ; }

  return true ;
}

bool GstreamerVideo::attachNativeWindow()
{
  // subscribe to follow window position events
  this->followWindow->addComponentListener(this) ;

  // detach from main window and pass our handle to gStreamer
  addToDesktop(0) ; // ComponentPeer::windowRepaintedExplictly
  guintptr window_handle = (guintptr)(getWindowHandle()) ;
  gst_x_overlay_set_window_handle(GST_X_OVERLAY(this->gstElement) , window_handle) ;
}
