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

#ifndef __JUCE_HEADER_B5AA576BA216A776__
#define __JUCE_HEADER_B5AA576BA216A776__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Instances of ChatListItem are subcomponents of the ChatList container
  They each represent an individual chat user.
                                                                    //[/Comments]
*/
class ChatListItem  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    ChatListItem (ValueTree chatter_store);
    ~ChatListItem();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree chatterStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> banButton;
    ScopedPointer<Label> nickLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatListItem)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B5AA576BA216A776__
