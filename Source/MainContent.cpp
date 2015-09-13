
#include "FfmpegStreamer.h"
#include "MainContent.h"
#include "Trace/Trace.h"


MainContent::MainContent(DocumentWindow* main_window)
{
  // MainWindow
  this->mainWindow = main_window ;

  // MainContent
  setName("MainContent") ;
  setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;

  // statusbar
  this->statusbar = new Statusbar() ;
  this->addChildAndSetID(this->statusbar , GUI::STATUS_GUI_ID) ;
  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::INIT_STATUS_TEXT) ;
}

MainContent::~MainContent()
{
  this->statusbar = nullptr ;
}

void MainContent::paint(Graphics& g)
{
  g.fillAll (Colour (0xff202020));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContent::resized()
{
  if (this->statusbar == nullptr) return ;

  int window_w = getWidth() ;
  int window_h = getHeight() ;

  // content
  int content_w = window_w - GUI::PAD2 ;
  int content_h = window_h - GUI::STATUSBAR_H - GUI::PAD3 ;

  // statusbar
  int status_x = GUI::PAD ;
  int status_y = window_h - GUI::STATUSBAR_H - GUI::PAD ;
  int status_w = content_w ;
  int status_h = GUI::STATUSBAR_H ;

  this->statusbar->setBounds(status_x , status_y , status_w , status_h) ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(APP::APP_NAME + " - " + title_text) ;
}

void MainContent::warning(String message_text)
{
  Trace::TraceWarning(message_text) ;
  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon  ,
                                   GUI::APP_WARNING_TITLE , message_text) ;
}

void MainContent::error(String message_text)
{
  Trace::TraceError(message_text) ;
  AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon ,
                                   GUI::APP_ERROR_TITLE     , message_text) ;
}
