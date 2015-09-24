
#include "AvCaster.h"
#include "MainContent.h"
#include "Trace/Trace.h"


MainContent::MainContent(DocumentWindow* main_window)
{
  // MainWindow
  this->mainWindow = main_window ;

  // MainContent
  setName("MainContent") ;
  setSize(GUI::CONTENT_W , GUI::CONTENT_H) ;

  // configuration
  this->outputConfig = new OutputConfig(main_window) ;
  this->addChildAndSetID(this->outputConfig , GUI::OUTPUT_GUI_ID) ;

  // video monitors
  this->screencapMonitor = new GstreamerVideo(main_window , GUI::SCREENCAP_MONITOR_X , GUI::MONITORS_Y) ;
  this->cameraMonitor    = new GstreamerVideo(main_window , GUI::CAMERA_MONITOR_X    , GUI::MONITORS_Y) ;
  this->outputMonitor    = new GstreamerVideo(main_window , GUI::OUTPUT_MONITOR_X    , GUI::MONITORS_Y) ;

  // statusbar
  this->statusbar = new Statusbar() ;
  this->addChildAndSetID(this->statusbar , GUI::STATUS_GUI_ID) ;
  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::INIT_STATUS_TEXT) ;
}

MainContent::~MainContent()
{
  this->outputConfig     = nullptr ;
  this->screencapMonitor = nullptr ;
  this->cameraMonitor    = nullptr ;
  this->outputMonitor    = nullptr ;
  this->statusbar        = nullptr ;
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

  // output config
  int output_x = GUI::PAD ;
  int output_y = GUI::PAD ;
  int output_w = content_w ;
  int output_h = content_h ;

  // statusbar
  int status_x = GUI::PAD ;
  int status_y = window_h - GUI::STATUSBAR_H - GUI::PAD ;
  int status_w = content_w ;
  int status_h = GUI::STATUSBAR_H ;

  this->outputConfig->setBounds(output_x , output_y , output_w , output_h) ;
  this->statusbar   ->setBounds(status_x , status_y , status_w , status_h) ;
}

void MainContent::startMonitors()
{
  this->screencapMonitor->start() ;
  this->cameraMonitor   ->start() ;
  this->outputMonitor   ->start() ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(APP::APP_NAME + " - " + title_text) ;
}

void MainContent::warning(String message_text)
{
  Trace::TraceWarning(message_text) ;
  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon , GUI::MODAL_WARNING_TITLE ,
                                   message_text          , String::empty            ,
                                   nullptr               , AvCaster::GetModalCb()   ) ;
}

void MainContent::error(String message_text)
{
  Trace::TraceError(message_text) ;
  AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon , GUI::MODAL_ERROR_TITLE ,
                                   message_text             , String::empty          ,
                                   nullptr                  , AvCaster::GetModalCb() ) ;
}
