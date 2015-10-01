/*
  ==============================================================================

    Config.h
    Author: bill-auger

  ==============================================================================
*/

#ifndef _CONFIG_H_INCLUDED_
#define _CONFIG_H_INCLUDED_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "Constants.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
this is the output configuration GUI
    it has it controls for setting the stream parameters
                                                                    //[/Comments]
*/
class Config  : public Component,
                public TextEditor::Listener,
                public SliderListener,
                public ComboBoxListener,
                public ButtonListener
{
public:
    //==============================================================================
    Config (Component* main_window, ValueTree config_store, ValueTree camera_store, ValueTree audio_store);
    ~Config();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

//  friend class MainContent ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void        textEditorFocusLost(TextEditor& a_text_editor) ;

  void        populateComboBoxes() ;
  void        loadConfig() ;
  StringArray node2Array(        ValueTree a_node) ;
  void        setConfig(         Identifier a_key , var a_value) ;


  ValueTree configStore ;
  ValueTree cameraDevices ;
  ValueTree audioDevices ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> screenGroup;
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
    ScopedPointer<GroupComponent> cameraGroup;
    ScopedPointer<Label> cameraDevLabel;
    ScopedPointer<ComboBox> cameraDevCombo;
    ScopedPointer<Label> cameraResLabel;
    ScopedPointer<ComboBox> cameraResCombo;
    ScopedPointer<GroupComponent> audioGroup;
    ScopedPointer<Label> audioApiLabel;
    ScopedPointer<ComboBox> audioApiCombo;
    ScopedPointer<Label> audioDevLabel;
    ScopedPointer<ComboBox> audioDevCombo;
    ScopedPointer<Label> audioCodecLabel;
    ScopedPointer<ComboBox> audioCodecCombo;
    ScopedPointer<Label> nChannelsLabel;
    ScopedPointer<Slider> nChannelsSlider;
    ScopedPointer<Label> samplerateLabel;
    ScopedPointer<ComboBox> samplerateCombo;
    ScopedPointer<Label> audioBitrateLabel;
    ScopedPointer<ComboBox> audioBitrateCombo;
    ScopedPointer<GroupComponent> textGroup;
    ScopedPointer<Label> overlayLabel;
    ScopedPointer<TextEditor> overlayText;
    ScopedPointer<Label> textStyleLabel;
    ScopedPointer<ComboBox> textStyleCombo;
    ScopedPointer<Label> textPosLabel;
    ScopedPointer<ComboBox> textPosCombo;
    ScopedPointer<GroupComponent> outputGroup;
    ScopedPointer<Label> outputStreamLabel;
    ScopedPointer<ComboBox> outputStreamCombo;
    ScopedPointer<Label> outputWidthLabel;
    ScopedPointer<TextEditor> outputWidthText;
    ScopedPointer<Label> outputHeightLabel;
    ScopedPointer<TextEditor> outputHeightText;
    ScopedPointer<Label> framerateLabel;
    ScopedPointer<ComboBox> framerateCombo;
    ScopedPointer<Label> bitrateLabel;
    ScopedPointer<ComboBox> bitrateCombo;
    ScopedPointer<Label> outputDestLabel;
    ScopedPointer<TextEditor> outputDestText;
    ScopedPointer<GroupComponent> monitorsGroup;
    ScopedPointer<ToggleButton> monitorsToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIG_H_INCLUDED_
