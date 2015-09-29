/*
  ==============================================================================

    GstreamerVideo.cpp
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#include <gst/video/videooverlay.h>

#include "AvCaster.h"
#include "GstreamerVideo.h"
#include "Trace/Trace.h"


GstreamerVideo::GstreamerVideo(Component* follow_window , int local_x   , int local_y  ,
                                                          int initial_w , int initial_h)
{
  // initialize GUI
  DocumentWindow* main_window   = (DocumentWindow*)follow_window->getTopLevelComponent() ;
  int             titlebar_h    = main_window->getTitleBarHeight() ;
  this->          followWindow  = follow_window ;
  this->          localPosition = new Point<int>(local_x , local_y + titlebar_h) ;

  setSize(initial_w , initial_h) ;
  setOpaque(true) ;
  setAlwaysOnTop(true) ;

// DBG("GstreamerVideo::GstreamerVideo() this->outputMonitor->getBounds()=" + getBounds().toString()) ;
// DBG("GstreamerVideo::GstreamerVideo() this->local_position=" + String(local_x) + "x" + String(local_y)) ;
// DBG("GstreamerVideo::GstreamerVideo() this->localPosition=" + this->localPosition->toString()) ;
}

GstreamerVideo::~GstreamerVideo() { this->localPosition = nullptr ; }

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

void GstreamerVideo::setState(GstElement* sink_element , bool is_preview_on)
{
  if (is_preview_on) starting(sink_element) ; else stopping() ;
}

void GstreamerVideo::starting(GstElement* sink_element)
{
  if (!isOnDesktop())
  {
    // subscribe to follow window position events
    this->followWindow->addComponentListener(this) ;

    // detach from main window and attach to gStreamer
    addToDesktop(0) ;
    guintptr window_handle = (guintptr)(this->getWindowHandle()) ;
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink_element) , window_handle) ;
  }

  setPosition() ; setVisible(true) ;
}

void GstreamerVideo::stopping() { setVisible(false) ; }
