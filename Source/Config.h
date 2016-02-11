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

#ifndef __JUCE_HEADER_21AE3B746DB36E0C__
#define __JUCE_HEADER_21AE3B746DB36E0C__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "Constants.h"
#include "ConfigAudio.h"
#include "ConfigCamera.h"
#include "ConfigChat.h"
#include "ConfigImage.h"
#include "ConfigOutput.h"
#include "ConfigScreen.h"
#include "ConfigText.h"


class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Config is the presets configuration GUI for the AvCaster application.
  It has it controls for setting the stream parameters.
                                                                    //[/Comments]
*/
class Config  : public Component,
                public Button::Listener,
                public Slider::Listener,
                public TextEditor::Listener,
                public ComboBox::Listener
{
public:
    //==============================================================================
    Config (MainContent* main_content);
    ~Config();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

public:

  bool validateConfigGui() ;


private:

  void broughtToFront       ()                          override ;
  void sliderValueChanged   (Slider* a_slider)          override ;
  void comboBoxChanged      (ComboBox* a_combobox)      override ;
  void buttonClicked        (Button* a_button)          override ;
  void textEditorTextChanged(TextEditor& a_text_editor) override ;
  void textEditorFocusLost  (TextEditor& a_text_editor) override ;

  void loadConfig        () ;
  void enableComponents  () ;
  void updateVisibility  (Component* config_component) ;
  bool validateOutputDest() ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  MainContent*  mainContent ;
  Slider*       displaySlider ;
  Slider*       screenSlider ;
  TextEditor*   screenWidthText ;
  TextEditor*   screenHeightText ;
  TextEditor*   xOffsetText ;
  TextEditor*   yOffsetText ;
  ComboBox*     cameraDevCombo ;
  ComboBox*     cameraResCombo ;
  ComboBox*     audioApiCombo ;
  ComboBox*     audioDevCombo ;
  ComboBox*     audioCodecCombo ;
  Slider*       nChannelsSlider ;
  ComboBox*     samplerateCombo ;
  ComboBox*     audioBitrateCombo ;
  TextEditor*   motdText ;
  ComboBox*     textStyleCombo ;
  ComboBox*     textPosCombo ;
  TextEditor*   interstitialText ;
  TextButton*   browseButton ;
  ComboBox*     outputSinkCombo ;
  TextEditor*   outputWidthText ;
  TextEditor*   outputHeightText ;
  ComboBox*     framerateCombo ;
  ComboBox*     videoBitrateCombo ;
  Label*        outputDestLabel ;
  TextEditor*   outputDestText ;
  TextButton*   serverButton ;
  ComboBox*     hostCombo ;
  TextEditor*   portText ;
  TextEditor*   nickText ;
  TextEditor*   passText ;
  TextEditor*   channelText ;
  TextEditor*   greetingText ;
  ToggleButton* joinPartToggle ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> configGroup;
    ScopedPointer<TextButton> screenButton;
    ScopedPointer<TextButton> cameraButton;
    ScopedPointer<TextButton> audioButton;
    ScopedPointer<TextButton> textButton;
    ScopedPointer<TextButton> imageButton;
    ScopedPointer<TextButton> outputButton;
    ScopedPointer<TextButton> chatButton;
    ScopedPointer<GroupComponent> configPaneGroup;
    ScopedPointer<ConfigScreen> configScreen;
    ScopedPointer<ConfigCamera> configCamera;
    ScopedPointer<ConfigAudio> configAudio;
    ScopedPointer<ConfigText> configText;
    ScopedPointer<ConfigImage> configImage;
    ScopedPointer<ConfigOutput> configOutput;
    ScopedPointer<ConfigChat> configChat;
    ScopedPointer<Component> configSpacer;
    ScopedPointer<GroupComponent> hintsGroup;
    ScopedPointer<TextEditor> hintsText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_21AE3B746DB36E0C__
