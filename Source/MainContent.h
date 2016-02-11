/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_262A4C4094138A40__
#define __JUCE_HEADER_262A4C4094138A40__

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
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class AvCaster ;


  void configureButton    (Button* a_button , Button::Listener* a_button_listener) ;
  void configureSlider    (Slider* a_slider , Slider::Listener* a_slider_listener ,
                           double  min_val  , double            max_val           ,
                           double  step                                           ) ;
  void configureTextEditor(TextEditor* a_text_editor , TextEditor::Listener* a_text_listener ,
                           int         max_n_chars   , const String          allowed_chars   ) ;
  void configureCombobox  (ComboBox* a_combobox , ComboBox::Listener* a_combobox_listener = nullptr) ;
  void loadPresetsCombo   (ComboBox* a_combobox) ;


private:

  void           initialize      (ValueTree servers_store) ;
  void           disableControls (bool is_media_enabled  , bool is_screen_enabled  ,
                                  bool is_camera_enabled , bool is_text_enabled    ,
                                  bool is_image_enabled  , bool is_preview_enabled ,
                                  bool is_audio_enabled                            ) ;
  void           warning         (String message_text) ;
  void           error           (String message_text) ;
  Rectangle<int> getPreviewBounds() ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Background> background;
    ScopedPointer<Controls> controls;
    ScopedPointer<Chat> chat;
    ScopedPointer<Preview> preview;
    ScopedPointer<Presets> presets;
    ScopedPointer<Config> config;
    ScopedPointer<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_262A4C4094138A40__
