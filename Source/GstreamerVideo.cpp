/*
  ==============================================================================

    GstreamerVideo.cpp
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#include "Trace/Trace.h"
#include "AvCaster.h"
#include "GstreamerVideo.h"


GstreamerVideo::GstreamerVideo(Component* follow_window , int local_x , int local_y)
{
  // initialize GUI
  this->followWindow  = follow_window ;
  this->localPosition = new Point<int>(local_x , local_y + GUI::TITLEBAR_H) ;

  setSize(GUI::MONITOR_W , GUI::MONITOR_H) ;
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

void GstreamerVideo::start()
{
  if (!isOnDesktop())
  {
    // subscribe to follow window position events
    this->followWindow->addComponentListener(this) ;

    // detach from main window
    addToDesktop(0) ; // ComponentPeer::windowRepaintedExplictly
  }

  setPosition() ; setVisible(true) ;
}

void GstreamerVideo::stop() { setVisible(true) ; }
