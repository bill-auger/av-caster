/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef STATUSBAR_H_INCLUDED
#define STATUSBAR_H_INCLUDED

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
This is the bottom statusbar.
                                                                    //[/Comments]
*/
class Statusbar  : public Component
{
public:
    //==============================================================================
    Statusbar ();
    ~Statusbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setStatusL(String statusText) ;
  void setStatusC(String statusText) ;
  void setStatusR(String statusText) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> statusLLabel;
    ScopedPointer<Label> statusCLabel;
    ScopedPointer<Label> statusRLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Statusbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // STATUSBAR_H_INCLUDED
