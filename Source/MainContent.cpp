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
#include "MainContent.h"
#include "Trace/Trace.h"


MainContent::MainContent(DocumentWindow* main_window)
{
  // MainWindow
  this->mainWindow = main_window ;

  // MainContent
  setName("MainContent") ;
  setSize(GUI::WINDOW_W , GUI::WINDOW_H) ;
}

MainContent::~MainContent()
{
  this->background  = nullptr ;
  this->controls    = nullptr ;
  this->config      = nullptr ;
  this->statusbar   = nullptr ;
}

void MainContent::paint(Graphics& g)
{
  g.fillAll (Colour (0xff202020));
  g.setFont (Font (16.0f));
  g.setColour (Colours::black);
}

void MainContent::resized()
{
  if (this->controls  == nullptr || this->config == nullptr ||
      this->statusbar == nullptr                             ) return ;

  // background
  int background_x = GUI::PAD ;
  int background_y = GUI::CONFIG_Y ;
  int background_w = GUI::CONTENT_W ;
  int background_h = GUI::CONFIG_H ;

  // config
  int config_x = GUI::PAD ;
  int config_y = GUI::CONFIG_Y ;
  int config_w = GUI::CONTENT_W ;
  int config_h = GUI::CONFIG_H ;

  // controls
  int controls_x = GUI::PAD ;
  int controls_y = GUI::PAD ;
  int controls_w = GUI::CONTENT_W ;
  int controls_h = GUI::CONTENT_H ;

  // statusbar
  int status_x = GUI::PAD ;
  int status_y = GUI::STATUSBAR_Y ;
  int status_w = GUI::CONTENT_W ;
  int status_h = GUI::STATUSBAR_H ;

  this->background->setBounds(background_x , background_y , background_w , background_h) ;
  this->controls  ->setBounds(controls_x   , controls_y   , controls_w   , controls_h  ) ;
  this->config    ->setBounds(config_x     , config_y     , config_w     , config_h    ) ;
  this->statusbar ->setBounds(status_x     , status_y     , status_w     , status_h    ) ;
}

void MainContent::instantiate(ValueTree config_root  , ValueTree config_store ,
                              ValueTree camera_store , ValueTree audio_store  )
{
  // background
  this->background = new Background() ;
  this->addChildAndSetID(this->background , GUI::BACKGROUND_GUI_ID) ;

  // controls
  this->controls = new Controls(config_root , config_store) ;
  this->addChildAndSetID(this->controls , GUI::CONTROLS_GUI_ID) ;

  // config
  this->config = new Config(config_store , camera_store , audio_store) ;
  this->addChildAndSetID(this->config , GUI::CONFIG_GUI_ID) ;

  // statusbar
  this->statusbar = new Statusbar() ;
  this->addChildAndSetID(this->statusbar , GUI::STATUSBAR_GUI_ID) ;
  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::INIT_STATUS_TEXT) ;

  resized() ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(APP::APP_NAME + " - " + title_text) ;
}

void MainContent::warning(String message_text)
{
#ifdef DEBUG
  Trace::TraceWarning(message_text) ;
#endif // DEBUG

  if (JUCEApplicationBase::getInstance()->isInitialising()) return ;

  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon , GUI::MODAL_WARNING_TITLE ,
                                   message_text          , String::empty            ,
                                   nullptr               , AvCaster::GetModalCb()   ) ;
}

void MainContent::error(String message_text)
{
#ifdef DEBUG
  Trace::TraceError(message_text) ;
#endif // DEBUG

  if (JUCEApplicationBase::getInstance()->isInitialising()) return ;

  AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon , GUI::MODAL_ERROR_TITLE ,
                                   message_text             , String::empty          ,
                                   nullptr                  , AvCaster::GetModalCb() ) ;
}
