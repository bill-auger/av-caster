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

#include "JuceHeader.h"
#include "../Constants/Constants.h"
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
  Config is the presets configuration GUI container for the AvCaster application.
  It acts as a tabbed interface with controls for selecting among the
      the per-feature configuration group panes.
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
    ~Config() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

public:

  friend class MainContent ;


//   bool validateParams() ;


private:

  void broughtToFront       ()                          override ;
  void sliderValueChanged   (Slider* a_slider)          override ;
  void comboBoxChanged      (ComboBox* a_combobox)      override ;
  void buttonClicked        (Button* a_button)          override ;
  void textEditorTextChanged(TextEditor& a_text_editor) override ;
  void textEditorFocusLost  (TextEditor& a_text_editor) override ;

  void   initialize        (ValueTree config_store , ValueTree network_store) ;
  void   loadConfig        () ;
  void   enableComponents  () ;
  void   updateVisibility  (var pane_name) ;
  void   setHintsText      (String hints_text) ;
  String outputHintsText   () ;
  bool   validateOutputDest() ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  MainContent*  mainContent ;
  ValueTree     configStore ;
  ValueTree     networkStore ;
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
  TextEditor*   networkText ;
  TextEditor*   portText ;
  TextEditor*   nickText ;
  TextEditor*   passText ;
  TextEditor*   channelText ;
  TextEditor*   greetingText ;
  ToggleButton* timestampToggle ;
  ToggleButton* joinPartToggle ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> configGroup;
    std::unique_ptr<TextButton> screenButton;
    std::unique_ptr<TextButton> cameraButton;
    std::unique_ptr<TextButton> audioButton;
    std::unique_ptr<TextButton> textButton;
    std::unique_ptr<TextButton> imageButton;
    std::unique_ptr<TextButton> outputButton;
    std::unique_ptr<TextButton> chatButton;
    std::unique_ptr<GroupComponent> configPaneGroup;
    std::unique_ptr<ConfigScreen> configScreen;
    std::unique_ptr<ConfigCamera> configCamera;
    std::unique_ptr<ConfigAudio> configAudio;
    std::unique_ptr<ConfigText> configText;
    std::unique_ptr<ConfigImage> configImage;
    std::unique_ptr<ConfigOutput> configOutput;
    std::unique_ptr<ConfigChat> configChat;
    std::unique_ptr<Component> dummyConfigPane;
    std::unique_ptr<GroupComponent> hintsGroup;
    std::unique_ptr<TextEditor> hintsText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

