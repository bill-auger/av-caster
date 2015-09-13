/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCONTENT_H_INCLUDED
#define MAINCONTENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Statusbar.h"


/** this is the main GUI container class */
class MainContent : public Component
{
  friend class FfmpegStreamer ;


public:

  MainContent(DocumentWindow* main_window) ;
  ~MainContent();

  void paint(Graphics&) ;
  void resized() ;


private:

  ScopedPointer<Statusbar> statusbar ;
  DocumentWindow*          mainWindow ;

  void setTitle(String title_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif  // MAINCONTENT_H_INCLUDED
