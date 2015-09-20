/*
  ==============================================================================

    GstreamerVideo.h
    Created: 19 Sep 2015 4:30:31am
    Author:  bill-auger

  ==============================================================================
*/

#ifndef GSTREAMERVIDEO_H_INCLUDED
#define GSTREAMERVIDEO_H_INCLUDED

#include <exception>
#include <gst/gst.h>

#include "Constants.h"
#include "JuceHeader.h"


class GstreamerInitException : public std::exception
{
  virtual const char* what() const throw() { return APP::GSTREAMER_INIT_EXCEPTION_MSG ; }
} ;


/**
This is a custom JUCE component that hosts a gStreamer video output.
*/
class GstreamerVideo : public Component
{
public:

  GstreamerVideo() ;
  ~GstreamerVideo() ;

  void paint(Graphics&) ;
  void resized() ;
  bool start(String uri) ;
  bool attachNativeWindow() ;


private:

  GstElement* gstElement ;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GstreamerVideo)
} ;

#endif  // GSTREAMERVIDEO_H_INCLUDED
