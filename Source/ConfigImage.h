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

#ifndef __JUCE_HEADER_43DBA1A9D1567EF6__
#define __JUCE_HEADER_43DBA1A9D1567EF6__

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
class ConfigImage  : public Component
{
public:
    //==============================================================================
    ConfigImage ();
    ~ConfigImage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> locationLabel;
    ScopedPointer<TextEditor> interstitialText;
    ScopedPointer<TextButton> browseButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigImage)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_43DBA1A9D1567EF6__
