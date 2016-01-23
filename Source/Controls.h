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

#ifndef __JUCE_HEADER_7E49606CC1E6A40__
#define __JUCE_HEADER_7E49606CC1E6A40__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Controls is the media selection and preview GUI for the AvCaster application.
  It serves only as a consistent backdrop and/or interstitial.
                                                                    //[/Comments]
*/
class Controls  : public Component,
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    Controls ();
    ~Controls();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* preferencessystem_png;
    static const int preferencessystem_pngSize;
    static const char* confighover_png;
    static const int confighover_pngSize;
    static const char* configpushed_png;
    static const int configpushed_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void broughtToFront() override ;

  void loadConfig() ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> controlsGroup;
    ScopedPointer<ToggleButton> screencapToggle;
    ScopedPointer<ToggleButton> cameraToggle;
    ScopedPointer<ToggleButton> textToggle;
    ScopedPointer<ToggleButton> interstitialToggle;
    ScopedPointer<ToggleButton> previewToggle;
    ScopedPointer<ToggleButton> audioToggle;
    ScopedPointer<ToggleButton> outputToggle;
    ScopedPointer<ComboBox> presetsCombo;
    ScopedPointer<ImageButton> configButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7E49606CC1E6A40__
