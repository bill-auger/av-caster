/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef MAINCONTENT_H_INCLUDED
#define MAINCONTENT_H_INCLUDED

#include "Config.h"
#include "GstreamerVideo.h"
#include "Statusbar.h"


/** this is the main GUI container class */
class MainContent : public Component
{
  friend class AvCaster ;


public:

  MainContent(DocumentWindow* main_window) ;
  ~MainContent();

  void paint(Graphics&) ;
  void resized() ;
  void instantiate(ValueTree config_store) ;
  void startMonitors() ;


private:

  DocumentWindow*               mainWindow ;
  ScopedPointer<Config        > config ;
  ScopedPointer<GstreamerVideo> screencapMonitor ;
  ScopedPointer<GstreamerVideo> cameraMonitor ;
  ScopedPointer<GstreamerVideo> outputMonitor ;
  ScopedPointer<Statusbar     > statusbar ;

  void setTitle(String title_text) ;
  void warning( String message_text) ;
  void error(   String message_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif  // MAINCONTENT_H_INCLUDED
