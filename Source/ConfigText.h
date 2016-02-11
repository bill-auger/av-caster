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

#ifndef __JUCE_HEADER_89BBC0574CFF63D6__
#define __JUCE_HEADER_89BBC0574CFF63D6__

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
class ConfigText  : public Component,
                    public ComboBoxListener
{
public:
    //==============================================================================
    ConfigText ();
    ~ConfigText();

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
    ScopedPointer<Label> motdLabel;
    ScopedPointer<TextEditor> motdText;
    ScopedPointer<Label> textStyleLabel;
    ScopedPointer<ComboBox> textStyleCombo;
    ScopedPointer<Label> textPosLabel;
    ScopedPointer<ComboBox> textPosCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigText)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_89BBC0574CFF63D6__
