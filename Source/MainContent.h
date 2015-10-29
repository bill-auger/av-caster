/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef MAINCONTENT_H_INCLUDED
#define MAINCONTENT_H_INCLUDED

#include "Background.h"
#include "Config.h"
#include "Controls.h"
#include "Statusbar.h"


/** MainContent is the main GUI container class for the AvCaster application. */
class MainContent : public Component
{
  friend class AvCaster ;


public:

  MainContent(DocumentWindow* main_window) ;
  ~MainContent();

  void paint(Graphics&) ;
  void resized() ;


private:

  DocumentWindow*           mainWindow ;
  ScopedPointer<Background> background ;
  ScopedPointer<Controls  > controls ;
  ScopedPointer<Config    > config ;
  ScopedPointer<Statusbar > statusbar ;

  void instantiate (ValueTree config_root  , ValueTree config_store ,
                    ValueTree camera_store , ValueTree audio_store  ) ;
  void setTitle    (String title_text) ;
  void warning     (String message_text) ;
  void error       (String message_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif  // MAINCONTENT_H_INCLUDED
