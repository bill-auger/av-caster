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

#ifndef __JUCE_HEADER_8281ACCB06DD6C7C__
#define __JUCE_HEADER_8281ACCB06DD6C7C__

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
class ConfigScreen  : public Component,
                      public SliderListener
{
public:
    //==============================================================================
    ConfigScreen ();
    ~ConfigScreen();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
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


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigScreen)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8281ACCB06DD6C7C__
