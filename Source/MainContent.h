/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCONTENT_H_INCLUDED
#define MAINCONTENT_H_INCLUDED

#include "OutputConfig.h"
#include "Statusbar.h"


/** this is the main GUI container class */
class MainContent : public Component
{
  friend class AvCasterApplication ;
  friend class AvCaster ;


public:

  MainContent(DocumentWindow* main_window) ;
  ~MainContent();

  void paint(Graphics&) ;
  void resized() ;
  void startMonitors() ;
  void mainWindowMoved() ;


private:

  DocumentWindow*             mainWindow ;
  ScopedPointer<OutputConfig> outputConfig ;
  ScopedPointer<Statusbar>    statusbar ;

  void setTitle(String title_text) ;
  void warning( String message_text) ;
  void error(   String message_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif  // MAINCONTENT_H_INCLUDED
