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

#ifndef __JUCE_HEADER_3520605495A2C0DC__
#define __JUCE_HEADER_3520605495A2C0DC__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"


class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConfigChat  : public Component,
                    public ComboBoxListener
{
public:
    //==============================================================================
    ConfigChat ();
    ~ConfigChat();

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
    ScopedPointer<TextButton> serverButton;
    ScopedPointer<Label> hostLabel;
    ScopedPointer<ComboBox> hostCombo;
    ScopedPointer<Label> portLabel;
    ScopedPointer<TextEditor> portText;
    ScopedPointer<Label> nickLabel;
    ScopedPointer<TextEditor> nickText;
    ScopedPointer<Label> passLabel;
    ScopedPointer<TextEditor> passText;
    ScopedPointer<Label> channelLabel;
    ScopedPointer<TextEditor> channelText;
    ScopedPointer<Label> greetingLabel;
    ScopedPointer<TextEditor> greetingText;
    ScopedPointer<ToggleButton> joinPartToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigChat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3520605495A2C0DC__
