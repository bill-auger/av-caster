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

#ifndef __JUCE_HEADER_D1BF7505594DC2C6__
#define __JUCE_HEADER_D1BF7505594DC2C6__

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
class ConfigCamera  : public Component,
                      public ComboBoxListener
{
public:
    //==============================================================================
    ConfigCamera ();
    ~ConfigCamera();

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
    ScopedPointer<Label> cameraDevLabel;
    ScopedPointer<ComboBox> cameraDevCombo;
    ScopedPointer<Label> cameraResLabel;
    ScopedPointer<ComboBox> cameraResCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigCamera)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D1BF7505594DC2C6__
