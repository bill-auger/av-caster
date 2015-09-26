/*
  ==============================================================================

    GstreamerVideo.h
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#ifndef GSTREAMERVIDEO_H_INCLUDED
#define GSTREAMERVIDEO_H_INCLUDED

#include "Constants.h"
#include "JuceHeader.h"


/**
This is a custom JUCE component that hosts a gStreamer video output.

To use this class simply instantiate one, passing in a reference Component*
and the relative X and Y positions for this component.

The GstreamerVideo component will add itself as a top-level window on the desktop
and will attempt to keep itself positioned at the specified coordinates
'within' the supplied reference component when its position changes
via a ComponentListener registered on the reference component.

  @param follow_window a reference Component* for this GstreamerVideo position
  @param local_x       X position relative to the reference component
  @param local_y       Y position relative to the reference component
*/
class GstreamerVideo : public Component , ComponentListener
{
public:

  GstreamerVideo(Component* follow_window , int local_x   , int local_y  ,
                                            int initial_w , int initial_h) ;
  ~GstreamerVideo() ;

  void paint(Graphics&) ;
  void resized() ;
  void componentMovedOrResized(Component& a_component , bool wasMoved  , bool wasResized) ;

  inline void setPosition() ;
  void        start() ;
  void        stop() ;


private:

  Component*                 followWindow ;
  ScopedPointer<Point<int> > localPosition ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GstreamerVideo)
} ;

#endif  // GSTREAMERVIDEO_H_INCLUDED
