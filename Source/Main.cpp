/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#include "AvCaster.h"
#include "./Trace/TraceMain.h"


//==============================================================================
class AvCasterApplication : public JUCEApplication , public MultiTimer
{
public:

  AvCasterApplication() {}

  void initialise(const String& command_line) override
  {
DEBUG_TRACE_INIT_VERSION

    this->mainWindow = new MainWindow() ;

    if (AvCaster::Initialize(this->mainWindow->mainContent))
    {
      // start GUI update timers
//       startTimer(APP::GUI_TIMER_HI_ID  , APP::GUI_UPDATE_HI_IVL ) ;
      startTimer(APP::GUI_TIMER_MED_ID , APP::GUI_UPDATE_MED_IVL) ;
      startTimer(APP::GUI_TIMER_LO_ID  , APP::GUI_UPDATE_LO_IVL ) ;
    }
    else { setApplicationReturnValue(255) ; shutdown() ; quit() ; }
  }

  void anotherInstanceStarted (const String& command_line) override
  {
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the command_line parameter tells you what
    // the other instance's command-line arguments were.
  }

  void shutdown() override
  {
DEBUG_TRACE_SHUTDOWN_IN

    AvCaster::Shutdown() ;

    this->mainWindow = nullptr ;

DEBUG_TRACE_SHUTDOWN_OUT
  }

  void         systemRequestedQuit()        override { this->quit() ; }
  const String getApplicationName()         override { return ProjectInfo::projectName ; }
  const String getApplicationVersion()      override { return ProjectInfo::versionString ; }
  bool         moreThanOneInstanceAllowed() override { return false ; }


  //==============================================================================
  /*
      This class implements the desktop window that contains an instance of
      our MainContent class.
  */
  class MainWindow : public DocumentWindow
  {
    friend class AvCasterApplication ;


  public:

    MainWindow() : DocumentWindow(APP::APP_NAME , Colour(0xff202020) , GUI::TITLEBAR_BTNS)
    {
      // main content
      this->mainContent = new MainContent() ;
      setContentOwned(this->mainContent , true) ;

      // this main desktop window
#ifdef _MAC
      setTitleBarButtonsRequired(DocumentWindow::allButtons , true) ;
#endif // _MAC
      setTitleBarHeight(GUI::TITLEBAR_H) ;
//      setIcon(const Image &imageToUse) ;
      centreWithSize(getWidth() , getHeight()) ;
      setVisible(true) ;
    }

    ~MainWindow() { this->mainContent = nullptr ; }

    void closeButtonPressed() override
    {
      JUCEApplicationBase::getInstance()->systemRequestedQuit() ;
    }


  private:

    ScopedPointer<MainContent> mainContent ;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  } ;


private:

#ifndef DEBUG_QUIT_IMMEDIATELY
  void timerCallback(int timer_id) override { AvCaster::HandleTimer(timer_id) ; }
#else // DEBUG_QUIT_IMMEDIATELY
  void timerCallback(int timer_id) override
  {
    if (timer_id != APP::GUI_TIMER_LO_ID) AvCaster::HandleTimer(timer_id) ;
    else                                  { Trace::TraceEvent("forced quit") ; quit() ; }
  }
#endif // DEBUG_QUIT_IMMEDIATELY

  ScopedPointer<MainWindow> mainWindow ;
} ;

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(AvCasterApplication)
