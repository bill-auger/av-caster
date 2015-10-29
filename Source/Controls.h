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

#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Controls  : public Component,
                  public ButtonListener,
                  public ComboBoxListener
{
public:
    //==============================================================================
    Controls (ValueTree config_root, ValueTree config_store);
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

  void toggleControls(bool is_config_pending) ;
  void loadConfig() ;
  bool rejectConfigChange() ;


  ValueTree configRoot ;
  ValueTree configPresets ;
  ValueTree configStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> controlGroup;
    ScopedPointer<ToggleButton> outputToggle;
    ScopedPointer<ToggleButton> interstitialToggle;
    ScopedPointer<ToggleButton> screencapToggle;
    ScopedPointer<ToggleButton> cameraToggle;
    ScopedPointer<ToggleButton> textToggle;
    ScopedPointer<ToggleButton> previewToggle;
    ScopedPointer<ComboBox> presetCombo;
    ScopedPointer<ImageButton> configButton;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> newButton;
    ScopedPointer<TextButton> deleteButton;
    ScopedPointer<Label> presetLabel;
    ScopedPointer<GroupComponent> previewGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // CONTROLS_H_INCLUDED
