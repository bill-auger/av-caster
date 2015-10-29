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

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "Constants.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Config is the output configuration GUI for the AvCaster application..
  It has it controls for setting the stream parameters.
                                                                    //[/Comments]
*/
class Config  : public Component,
                public TextEditor::Listener,
                public SliderListener,
                public ComboBoxListener
{
public:
    //==============================================================================
    Config (ValueTree config_store, ValueTree camera_store, ValueTree audio_store);
    ~Config();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

//  friend class MainContent ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void broughtToFront() override ;
  void textEditorFocusLost(TextEditor& a_text_editor) override ;

  void populateComboBoxes() ;
  void loadConfig        () ;


  ValueTree configRoot ;
  ValueTree configPresets ;
  ValueTree configStore ;
  ValueTree cameraDevices ;
  ValueTree audioDevices ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> screenGroup;
    ScopedPointer<Label> displayLabel;
    ScopedPointer<Slider> displaySlider;
    ScopedPointer<Label> screenLabel;
    ScopedPointer<Slider> screenSlider;
    ScopedPointer<Label> screenWidthLabel;
    ScopedPointer<TextEditor> screenWidthText;
    ScopedPointer<Label> screenHeightLabel;
    ScopedPointer<TextEditor> screenHeightText;
    ScopedPointer<Label> xOffsetLabel;
    ScopedPointer<TextEditor> xOffsetText;
    ScopedPointer<Label> yOffsetLabel;
    ScopedPointer<TextEditor> yOffsetText;
    ScopedPointer<GroupComponent> cameraGroup;
    ScopedPointer<Label> cameraDevLabel;
    ScopedPointer<ComboBox> cameraDevCombo;
    ScopedPointer<Label> cameraResLabel;
    ScopedPointer<ComboBox> cameraResCombo;
    ScopedPointer<GroupComponent> audioGroup;
    ScopedPointer<Label> audioApiLabel;
    ScopedPointer<ComboBox> audioApiCombo;
    ScopedPointer<Label> audioDevLabel;
    ScopedPointer<ComboBox> audioDevCombo;
    ScopedPointer<Label> audioCodecLabel;
    ScopedPointer<ComboBox> audioCodecCombo;
    ScopedPointer<Label> nChannelsLabel;
    ScopedPointer<Slider> nChannelsSlider;
    ScopedPointer<Label> samplerateLabel;
    ScopedPointer<ComboBox> samplerateCombo;
    ScopedPointer<Label> audioBitrateLabel;
    ScopedPointer<ComboBox> audioBitrateCombo;
    ScopedPointer<GroupComponent> textGroup;
    ScopedPointer<Label> overlayLabel;
    ScopedPointer<TextEditor> overlayText;
    ScopedPointer<Label> textStyleLabel;
    ScopedPointer<ComboBox> textStyleCombo;
    ScopedPointer<Label> textPosLabel;
    ScopedPointer<ComboBox> textPosCombo;
    ScopedPointer<GroupComponent> outputGroup;
    ScopedPointer<Label> outputStreamLabel;
    ScopedPointer<ComboBox> outputStreamCombo;
    ScopedPointer<Label> outputWidthLabel;
    ScopedPointer<TextEditor> outputWidthText;
    ScopedPointer<Label> outputHeightLabel;
    ScopedPointer<TextEditor> outputHeightText;
    ScopedPointer<Label> framerateLabel;
    ScopedPointer<ComboBox> framerateCombo;
    ScopedPointer<Label> bitrateLabel;
    ScopedPointer<ComboBox> videoBitrateCombo;
    ScopedPointer<Label> outputDestLabel;
    ScopedPointer<TextEditor> outputDestText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // CONFIG_H_INCLUDED
