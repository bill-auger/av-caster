/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "Background.h"
#include "Chat.h"
#include "Config.h"
#include "Controls.h"
#include "Preview.h"
#include "Presets.h"
#include "Statusbar.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  MainContent is the main GUI container class for the AvCaster application.
                                                                    //[/Comments]
*/
class MainContent  : public Component
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class AvCaster ;


  void   configureButton    (Button* a_button , Button::Listener* a_button_listener) ;
  void   configureSlider    (Slider* a_slider , Slider::Listener* a_slider_listener ,
                             double  min_val  , double            max_val           ,
                             double  step                                           ) ;
  void   configureTextEditor(TextEditor* a_text_editor , TextEditor::Listener* a_text_listener ,
                             int         max_n_chars   , const String          allowed_chars   ) ;
  void   configureCombobox  (ComboBox*           a_combobox                   ,
                             ComboBox::Listener* a_combobox_listener = nullptr) ;
  void   loadPresetsCombo   (ComboBox* a_combobox) ;
  Colour btnTickColor       (bool is_active) ;
  Colour btnTextColor       (bool is_active) ;


private:

  void           initialize      (ValueTree config_store   , ValueTree network_store         ,
                                  ValueTree chatters_store , NamedValueSet& disabled_features) ;
  Rectangle<int> getPreviewBounds() ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  DocumentWindow*                        mainWindow ;
#ifdef TRAY_ICON
  std::unique_ptr<SystemTrayIconComponent> trayIcon ;
#endif // TRAY_ICON

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Background> background;
    std::unique_ptr<Controls> controls;
    std::unique_ptr<Chat> chat;
    std::unique_ptr<Preview> preview;
    std::unique_ptr<Presets> presets;
    std::unique_ptr<Config> config;
    std::unique_ptr<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...

#ifdef TRAY_ICON
/**
  AvCasterTrayIconComponent is the system tray GUI for the AvCaster application.
  It is just what it says on the tin.
*/
class AvCasterTrayIconComponent : public SystemTrayIconComponent
{
public:

  AvCasterTrayIconComponent(ResizableWindow* main_window) : mainWindow(main_window) {}

  void mouseDown(const MouseEvent& mouse_event) ;


private:

  ResizableWindow* mainWindow ;
} ;
#endif // TRAY_ICON


/**
  Alert is a public helper class for the AvCaster application.
  It queues and presents GUI message boxes to the user.
*/
class Alert
{
  friend class AvCaster ;


public:

  static void Push         (GUI::AlertType message_type , String message_text) ;
  static bool AreAnyPending() ;


private:

  Alert(GUI::AlertType message_type , String message_text) : messageType(message_type) ,
                                                             messageText(message_text) {}

  GUI::AlertType messageType ;
  String         messageText ;

  static void Display         () ;
  static void Warning         (String message_text) ;
  static void Error           (String message_text) ;
  static void OnModalDismissed(int /*result*/ , int /*unused*/) ;

  // runtime state
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;
} ;

//[/EndFile]

