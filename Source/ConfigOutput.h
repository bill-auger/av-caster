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

#ifndef __JUCE_HEADER_7ACD300A0FFE0DA6__
#define __JUCE_HEADER_7ACD300A0FFE0DA6__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"


class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ConfigOutput is the stream output configuration GUI for the AvCaster application.
  It has it controls for setting the per-preset stream output parameters.
                                                                    //[/Comments]
*/
class ConfigOutput  : public Component,
                      public ComboBoxListener
{
public:
    //==============================================================================
    ConfigOutput ();
    ~ConfigOutput();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> outputStreamLabel;
    ScopedPointer<ComboBox> outputSinkCombo;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigOutput)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7ACD300A0FFE0DA6__
