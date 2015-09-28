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

//[Headers] You can add your own extra header files here...

#include "Constants.h"
#include "Trace/TraceConfig.h"

//[/Headers]

#include "Config.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Config::Config (Component* main_window, ValueTree config_store)
    : configStore(config_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (screenGroup = new GroupComponent ("screenGroup",
                                                         TRANS("Screen")));
    screenGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    screenGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (displayLabel = new Label ("displayLabel",
                                                 TRANS("Display #:")));
    displayLabel->setFont (Font (15.00f, Font::plain));
    displayLabel->setJustificationType (Justification::centredLeft);
    displayLabel->setEditable (false, false, false);
    displayLabel->setColour (Label::textColourId, Colours::white);
    displayLabel->setColour (TextEditor::textColourId, Colours::black);
    displayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (displaySlider = new Slider ("displaySlider"));
    displaySlider->setExplicitFocusOrder (1);
    displaySlider->setRange (0, 10, 0);
    displaySlider->setSliderStyle (Slider::IncDecButtons);
    displaySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    displaySlider->addListener (this);

    addAndMakeVisible (screenLabel = new Label ("screenLabel",
                                                TRANS("Screen #:")));
    screenLabel->setFont (Font (15.00f, Font::plain));
    screenLabel->setJustificationType (Justification::centredLeft);
    screenLabel->setEditable (false, false, false);
    screenLabel->setColour (Label::textColourId, Colours::white);
    screenLabel->setColour (TextEditor::textColourId, Colours::black);
    screenLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (screenSlider = new Slider ("screenSlider"));
    screenSlider->setExplicitFocusOrder (2);
    screenSlider->setRange (0, 10, 0);
    screenSlider->setSliderStyle (Slider::IncDecButtons);
    screenSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    screenSlider->addListener (this);

    addAndMakeVisible (screenWidthLabel = new Label ("screenWidthLabel",
                                                     TRANS("Width:")));
    screenWidthLabel->setFont (Font (15.00f, Font::plain));
    screenWidthLabel->setJustificationType (Justification::centredLeft);
    screenWidthLabel->setEditable (false, false, false);
    screenWidthLabel->setColour (Label::textColourId, Colours::white);
    screenWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    screenWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (screenWidthText = new TextEditor ("screenWidthText"));
    screenWidthText->setExplicitFocusOrder (3);
    screenWidthText->setMultiLine (false);
    screenWidthText->setReturnKeyStartsNewLine (false);
    screenWidthText->setReadOnly (false);
    screenWidthText->setScrollbarsShown (false);
    screenWidthText->setCaretVisible (true);
    screenWidthText->setPopupMenuEnabled (true);
    screenWidthText->setText (String::empty);

    addAndMakeVisible (screenHeightLabel = new Label ("screenHeightLabel",
                                                      TRANS("Height:")));
    screenHeightLabel->setFont (Font (15.00f, Font::plain));
    screenHeightLabel->setJustificationType (Justification::centredLeft);
    screenHeightLabel->setEditable (false, false, false);
    screenHeightLabel->setColour (Label::textColourId, Colours::white);
    screenHeightLabel->setColour (TextEditor::textColourId, Colours::black);
    screenHeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (screenHeightText = new TextEditor ("screenHeightText"));
    screenHeightText->setExplicitFocusOrder (4);
    screenHeightText->setMultiLine (false);
    screenHeightText->setReturnKeyStartsNewLine (false);
    screenHeightText->setReadOnly (false);
    screenHeightText->setScrollbarsShown (false);
    screenHeightText->setCaretVisible (true);
    screenHeightText->setPopupMenuEnabled (true);
    screenHeightText->setText (String::empty);

    addAndMakeVisible (xOffsetLabel = new Label ("xOffsetLabel",
                                                 TRANS("Offset X:")));
    xOffsetLabel->setFont (Font (15.00f, Font::plain));
    xOffsetLabel->setJustificationType (Justification::centredLeft);
    xOffsetLabel->setEditable (false, false, false);
    xOffsetLabel->setColour (Label::textColourId, Colours::white);
    xOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    xOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (xOffsetText = new TextEditor ("xOffsetText"));
    xOffsetText->setExplicitFocusOrder (5);
    xOffsetText->setMultiLine (false);
    xOffsetText->setReturnKeyStartsNewLine (false);
    xOffsetText->setReadOnly (false);
    xOffsetText->setScrollbarsShown (true);
    xOffsetText->setCaretVisible (true);
    xOffsetText->setPopupMenuEnabled (true);
    xOffsetText->setText (String::empty);

    addAndMakeVisible (yOffsetLabel = new Label ("yOffsetLabel",
                                                 TRANS("Offset Y:")));
    yOffsetLabel->setFont (Font (15.00f, Font::plain));
    yOffsetLabel->setJustificationType (Justification::centredLeft);
    yOffsetLabel->setEditable (false, false, false);
    yOffsetLabel->setColour (Label::textColourId, Colours::white);
    yOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    yOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (yOffsetText = new TextEditor ("yOffsetText"));
    yOffsetText->setExplicitFocusOrder (6);
    yOffsetText->setMultiLine (false);
    yOffsetText->setReturnKeyStartsNewLine (false);
    yOffsetText->setReadOnly (false);
    yOffsetText->setScrollbarsShown (true);
    yOffsetText->setCaretVisible (true);
    yOffsetText->setPopupMenuEnabled (true);
    yOffsetText->setText (String::empty);

    addAndMakeVisible (cameraGroup = new GroupComponent ("cameraGroup",
                                                         TRANS("Camera")));
    cameraGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    cameraGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (cameraDevLabel = new Label ("cameraDevLabel",
                                                   TRANS("Device:")));
    cameraDevLabel->setFont (Font (15.00f, Font::plain));
    cameraDevLabel->setJustificationType (Justification::centredLeft);
    cameraDevLabel->setEditable (false, false, false);
    cameraDevLabel->setColour (Label::textColourId, Colours::white);
    cameraDevLabel->setColour (TextEditor::textColourId, Colours::black);
    cameraDevLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cameraDevCombo = new ComboBox ("cameraDevCombo"));
    cameraDevCombo->setExplicitFocusOrder (7);
    cameraDevCombo->setEditableText (false);
    cameraDevCombo->setJustificationType (Justification::centredLeft);
    cameraDevCombo->setTextWhenNothingSelected (TRANS("(no devices)"));
    cameraDevCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    cameraDevCombo->addListener (this);

    addAndMakeVisible (cameraResLabel = new Label ("cameraResLabel",
                                                   TRANS("Resolution:")));
    cameraResLabel->setFont (Font (15.00f, Font::plain));
    cameraResLabel->setJustificationType (Justification::centredLeft);
    cameraResLabel->setEditable (false, false, false);
    cameraResLabel->setColour (Label::textColourId, Colours::white);
    cameraResLabel->setColour (TextEditor::textColourId, Colours::black);
    cameraResLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cameraResCombo = new ComboBox ("cameraResCombo"));
    cameraResCombo->setExplicitFocusOrder (8);
    cameraResCombo->setEditableText (false);
    cameraResCombo->setJustificationType (Justification::centredLeft);
    cameraResCombo->setTextWhenNothingSelected (String::empty);
    cameraResCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cameraResCombo->addListener (this);

    addAndMakeVisible (audioGroup = new GroupComponent ("audioGroup",
                                                        TRANS("Audio")));
    audioGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    audioGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (audioApiLabel = new Label ("audioApiLabel",
                                                  TRANS("Interface:")));
    audioApiLabel->setFont (Font (15.00f, Font::plain));
    audioApiLabel->setJustificationType (Justification::centredLeft);
    audioApiLabel->setEditable (false, false, false);
    audioApiLabel->setColour (Label::textColourId, Colours::white);
    audioApiLabel->setColour (TextEditor::textColourId, Colours::black);
    audioApiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audioApiCombo = new ComboBox ("audioApiCombo"));
    audioApiCombo->setExplicitFocusOrder (9);
    audioApiCombo->setEditableText (false);
    audioApiCombo->setJustificationType (Justification::centredLeft);
    audioApiCombo->setTextWhenNothingSelected (String::empty);
    audioApiCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    audioApiCombo->addListener (this);

    addAndMakeVisible (audioDevLabel = new Label ("audioDevLabel",
                                                  TRANS("Device:")));
    audioDevLabel->setFont (Font (15.00f, Font::plain));
    audioDevLabel->setJustificationType (Justification::centredLeft);
    audioDevLabel->setEditable (false, false, false);
    audioDevLabel->setColour (Label::textColourId, Colours::white);
    audioDevLabel->setColour (TextEditor::textColourId, Colours::black);
    audioDevLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audioDevCombo = new ComboBox ("audioDevCombo"));
    audioDevCombo->setExplicitFocusOrder (10);
    audioDevCombo->setEditableText (false);
    audioDevCombo->setJustificationType (Justification::centredLeft);
    audioDevCombo->setTextWhenNothingSelected (TRANS("(no devices)"));
    audioDevCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    audioDevCombo->addListener (this);

    addAndMakeVisible (audioCodecLabel = new Label ("audioCodecLabel",
                                                    TRANS("Codec:")));
    audioCodecLabel->setFont (Font (15.00f, Font::plain));
    audioCodecLabel->setJustificationType (Justification::centredLeft);
    audioCodecLabel->setEditable (false, false, false);
    audioCodecLabel->setColour (Label::textColourId, Colours::white);
    audioCodecLabel->setColour (TextEditor::textColourId, Colours::black);
    audioCodecLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audioCodecCombo = new ComboBox ("audioCodecCombo"));
    audioCodecCombo->setExplicitFocusOrder (11);
    audioCodecCombo->setEditableText (false);
    audioCodecCombo->setJustificationType (Justification::centredLeft);
    audioCodecCombo->setTextWhenNothingSelected (String::empty);
    audioCodecCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    audioCodecCombo->addListener (this);

    addAndMakeVisible (nChannelsLabel = new Label ("nChannelsLabel",
                                                   TRANS("Channels:")));
    nChannelsLabel->setFont (Font (15.00f, Font::plain));
    nChannelsLabel->setJustificationType (Justification::centredLeft);
    nChannelsLabel->setEditable (false, false, false);
    nChannelsLabel->setColour (Label::textColourId, Colours::white);
    nChannelsLabel->setColour (TextEditor::textColourId, Colours::black);
    nChannelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nChannelsSlider = new Slider ("nChannelsSlider"));
    nChannelsSlider->setExplicitFocusOrder (12);
    nChannelsSlider->setRange (0, 10, 0);
    nChannelsSlider->setSliderStyle (Slider::IncDecButtons);
    nChannelsSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    nChannelsSlider->addListener (this);

    addAndMakeVisible (samplerateLabel = new Label ("samplerateLabel",
                                                    TRANS("Samplerate:")));
    samplerateLabel->setFont (Font (15.00f, Font::plain));
    samplerateLabel->setJustificationType (Justification::centredLeft);
    samplerateLabel->setEditable (false, false, false);
    samplerateLabel->setColour (Label::textColourId, Colours::white);
    samplerateLabel->setColour (TextEditor::textColourId, Colours::black);
    samplerateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (samplerateCombo = new ComboBox ("samplerateCombo"));
    samplerateCombo->setExplicitFocusOrder (13);
    samplerateCombo->setEditableText (false);
    samplerateCombo->setJustificationType (Justification::centredLeft);
    samplerateCombo->setTextWhenNothingSelected (String::empty);
    samplerateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    samplerateCombo->addListener (this);

    addAndMakeVisible (audioBitrateLabel = new Label ("audioBitrateLabel",
                                                      TRANS("Bitrate:")));
    audioBitrateLabel->setFont (Font (15.00f, Font::plain));
    audioBitrateLabel->setJustificationType (Justification::centredLeft);
    audioBitrateLabel->setEditable (false, false, false);
    audioBitrateLabel->setColour (Label::textColourId, Colours::white);
    audioBitrateLabel->setColour (TextEditor::textColourId, Colours::black);
    audioBitrateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audioBitrateCombo = new ComboBox ("audioBitrateCombo"));
    audioBitrateCombo->setExplicitFocusOrder (14);
    audioBitrateCombo->setEditableText (false);
    audioBitrateCombo->setJustificationType (Justification::centredLeft);
    audioBitrateCombo->setTextWhenNothingSelected (String::empty);
    audioBitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    audioBitrateCombo->addListener (this);

    addAndMakeVisible (textGroup = new GroupComponent ("textGroup",
                                                       TRANS("Text")));
    textGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    textGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (overlayLabel = new Label ("overlayLabel",
                                                 TRANS("Message:")));
    overlayLabel->setFont (Font (15.00f, Font::plain));
    overlayLabel->setJustificationType (Justification::centredLeft);
    overlayLabel->setEditable (false, false, false);
    overlayLabel->setColour (Label::textColourId, Colours::white);
    overlayLabel->setColour (TextEditor::textColourId, Colours::black);
    overlayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (overlayText = new TextEditor ("overlayText"));
    overlayText->setExplicitFocusOrder (15);
    overlayText->setMultiLine (false);
    overlayText->setReturnKeyStartsNewLine (false);
    overlayText->setReadOnly (false);
    overlayText->setScrollbarsShown (true);
    overlayText->setCaretVisible (true);
    overlayText->setPopupMenuEnabled (true);
    overlayText->setText (String::empty);

    addAndMakeVisible (textStyleLabel = new Label ("textStyleLabel",
                                                   TRANS("Style:")));
    textStyleLabel->setFont (Font (15.00f, Font::plain));
    textStyleLabel->setJustificationType (Justification::centredLeft);
    textStyleLabel->setEditable (false, false, false);
    textStyleLabel->setColour (Label::textColourId, Colours::white);
    textStyleLabel->setColour (TextEditor::textColourId, Colours::black);
    textStyleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textStyleCombo = new ComboBox ("textStyleCombo"));
    textStyleCombo->setExplicitFocusOrder (16);
    textStyleCombo->setEditableText (false);
    textStyleCombo->setJustificationType (Justification::centredLeft);
    textStyleCombo->setTextWhenNothingSelected (String::empty);
    textStyleCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textStyleCombo->addListener (this);

    addAndMakeVisible (textPosLabel = new Label ("textPosLabel",
                                                 TRANS("Position:")));
    textPosLabel->setFont (Font (15.00f, Font::plain));
    textPosLabel->setJustificationType (Justification::centredLeft);
    textPosLabel->setEditable (false, false, false);
    textPosLabel->setColour (Label::textColourId, Colours::white);
    textPosLabel->setColour (TextEditor::textColourId, Colours::black);
    textPosLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textPosCombo = new ComboBox ("textPosCombo"));
    textPosCombo->setExplicitFocusOrder (17);
    textPosCombo->setEditableText (false);
    textPosCombo->setJustificationType (Justification::centredLeft);
    textPosCombo->setTextWhenNothingSelected (String::empty);
    textPosCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textPosCombo->addListener (this);

    addAndMakeVisible (outputGroup = new GroupComponent ("outputGroup",
                                                         TRANS("Output")));
    outputGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    outputGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (outputStreamLabel = new Label ("outputStreamLabel",
                                                      TRANS("Dest:")));
    outputStreamLabel->setFont (Font (15.00f, Font::plain));
    outputStreamLabel->setJustificationType (Justification::centredLeft);
    outputStreamLabel->setEditable (false, false, false);
    outputStreamLabel->setColour (Label::textColourId, Colours::white);
    outputStreamLabel->setColour (TextEditor::textColourId, Colours::black);
    outputStreamLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputStreamCombo = new ComboBox ("outputStreamCombo"));
    outputStreamCombo->setExplicitFocusOrder (18);
    outputStreamCombo->setEditableText (false);
    outputStreamCombo->setJustificationType (Justification::centredLeft);
    outputStreamCombo->setTextWhenNothingSelected (String::empty);
    outputStreamCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    outputStreamCombo->addListener (this);

    addAndMakeVisible (outputWidthLabel = new Label ("outputWidthLabel",
                                                     TRANS("Width:")));
    outputWidthLabel->setFont (Font (15.00f, Font::plain));
    outputWidthLabel->setJustificationType (Justification::centredLeft);
    outputWidthLabel->setEditable (false, false, false);
    outputWidthLabel->setColour (Label::textColourId, Colours::white);
    outputWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    outputWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputWidthText = new TextEditor ("outputWidthText"));
    outputWidthText->setExplicitFocusOrder (19);
    outputWidthText->setMultiLine (false);
    outputWidthText->setReturnKeyStartsNewLine (false);
    outputWidthText->setReadOnly (false);
    outputWidthText->setScrollbarsShown (false);
    outputWidthText->setCaretVisible (true);
    outputWidthText->setPopupMenuEnabled (true);
    outputWidthText->setText (String::empty);

    addAndMakeVisible (outputHeightLabel = new Label ("outputHeightLabel",
                                                      TRANS("Height:")));
    outputHeightLabel->setFont (Font (15.00f, Font::plain));
    outputHeightLabel->setJustificationType (Justification::centredLeft);
    outputHeightLabel->setEditable (false, false, false);
    outputHeightLabel->setColour (Label::textColourId, Colours::white);
    outputHeightLabel->setColour (TextEditor::textColourId, Colours::black);
    outputHeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputHeightText = new TextEditor ("outputHeightText"));
    outputHeightText->setExplicitFocusOrder (20);
    outputHeightText->setMultiLine (false);
    outputHeightText->setReturnKeyStartsNewLine (false);
    outputHeightText->setReadOnly (false);
    outputHeightText->setScrollbarsShown (false);
    outputHeightText->setCaretVisible (true);
    outputHeightText->setPopupMenuEnabled (true);
    outputHeightText->setText (String::empty);

    addAndMakeVisible (framerateLabel = new Label ("framerateLabel",
                                                   TRANS("FPS:")));
    framerateLabel->setFont (Font (15.00f, Font::plain));
    framerateLabel->setJustificationType (Justification::centredLeft);
    framerateLabel->setEditable (false, false, false);
    framerateLabel->setColour (Label::textColourId, Colours::white);
    framerateLabel->setColour (TextEditor::textColourId, Colours::black);
    framerateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (framerateCombo = new ComboBox ("framerateCombo"));
    framerateCombo->setExplicitFocusOrder (21);
    framerateCombo->setEditableText (false);
    framerateCombo->setJustificationType (Justification::centredLeft);
    framerateCombo->setTextWhenNothingSelected (String::empty);
    framerateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    framerateCombo->addListener (this);

    addAndMakeVisible (bitrateLabel = new Label ("bitrateLabel",
                                                 TRANS("Bitrate:")));
    bitrateLabel->setFont (Font (15.00f, Font::plain));
    bitrateLabel->setJustificationType (Justification::centredLeft);
    bitrateLabel->setEditable (false, false, false);
    bitrateLabel->setColour (Label::textColourId, Colours::white);
    bitrateLabel->setColour (TextEditor::textColourId, Colours::black);
    bitrateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bitrateCombo = new ComboBox ("bitrateCombo"));
    bitrateCombo->setExplicitFocusOrder (22);
    bitrateCombo->setEditableText (false);
    bitrateCombo->setJustificationType (Justification::centredLeft);
    bitrateCombo->setTextWhenNothingSelected (String::empty);
    bitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    bitrateCombo->addListener (this);

    addAndMakeVisible (outputDestLabel = new Label ("outputDestLabel",
                                                    TRANS("URI:")));
    outputDestLabel->setFont (Font (15.00f, Font::plain));
    outputDestLabel->setJustificationType (Justification::centredLeft);
    outputDestLabel->setEditable (false, false, false);
    outputDestLabel->setColour (Label::textColourId, Colours::white);
    outputDestLabel->setColour (TextEditor::textColourId, Colours::black);
    outputDestLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputDestText = new TextEditor ("outputDestText"));
    outputDestText->setExplicitFocusOrder (23);
    outputDestText->setMultiLine (false);
    outputDestText->setReturnKeyStartsNewLine (false);
    outputDestText->setReadOnly (false);
    outputDestText->setScrollbarsShown (true);
    outputDestText->setCaretVisible (true);
    outputDestText->setPopupMenuEnabled (true);
    outputDestText->setText (String::empty);

    addAndMakeVisible (monitorsGroup = new GroupComponent ("monitorsGroup",
                                                           TRANS("Monitors")));
    monitorsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    monitorsGroup->setColour (GroupComponent::textColourId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  populateComboBoxes() ; loadConfig() ;
  this->screenWidthText ->addListener(this) ;
  this->screenHeightText->addListener(this) ;
  this->xOffsetText     ->addListener(this) ;
  this->yOffsetText     ->addListener(this) ;
  this->overlayText     ->addListener(this) ;
  this->outputWidthText ->addListener(this) ;
  this->outputHeightText->addListener(this) ;
  this->outputDestText  ->addListener(this) ;

  //this->displaySlider->setRange(0 , GUI::MAX_DISPLAY_N , 1) ; // TODO: ?

    //[/Constructor]
}

Config::~Config()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    screenGroup = nullptr;
    displayLabel = nullptr;
    displaySlider = nullptr;
    screenLabel = nullptr;
    screenSlider = nullptr;
    screenWidthLabel = nullptr;
    screenWidthText = nullptr;
    screenHeightLabel = nullptr;
    screenHeightText = nullptr;
    xOffsetLabel = nullptr;
    xOffsetText = nullptr;
    yOffsetLabel = nullptr;
    yOffsetText = nullptr;
    cameraGroup = nullptr;
    cameraDevLabel = nullptr;
    cameraDevCombo = nullptr;
    cameraResLabel = nullptr;
    cameraResCombo = nullptr;
    audioGroup = nullptr;
    audioApiLabel = nullptr;
    audioApiCombo = nullptr;
    audioDevLabel = nullptr;
    audioDevCombo = nullptr;
    audioCodecLabel = nullptr;
    audioCodecCombo = nullptr;
    nChannelsLabel = nullptr;
    nChannelsSlider = nullptr;
    samplerateLabel = nullptr;
    samplerateCombo = nullptr;
    audioBitrateLabel = nullptr;
    audioBitrateCombo = nullptr;
    textGroup = nullptr;
    overlayLabel = nullptr;
    overlayText = nullptr;
    textStyleLabel = nullptr;
    textStyleCombo = nullptr;
    textPosLabel = nullptr;
    textPosCombo = nullptr;
    outputGroup = nullptr;
    outputStreamLabel = nullptr;
    outputStreamCombo = nullptr;
    outputWidthLabel = nullptr;
    outputWidthText = nullptr;
    outputHeightLabel = nullptr;
    outputHeightText = nullptr;
    framerateLabel = nullptr;
    framerateCombo = nullptr;
    bitrateLabel = nullptr;
    bitrateCombo = nullptr;
    outputDestLabel = nullptr;
    outputDestText = nullptr;
    monitorsGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Config::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    g.setColour (Colour (0xff202020));
    g.fillRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), static_cast<float> (getHeight() - 16), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (8.0f, 8.0f, static_cast<float> (getWidth() - 16), static_cast<float> (getHeight() - 16), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Config::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    screenGroup->setBounds (16, 8, getWidth() - 32, 100);
    displayLabel->setBounds (32, 32, 80, 24);
    displaySlider->setBounds (120, 32, 64, 24);
    screenLabel->setBounds (32, 64, 80, 24);
    screenSlider->setBounds (120, 64, 64, 24);
    screenWidthLabel->setBounds (200, 32, 64, 24);
    screenWidthText->setBounds (264, 32, 48, 24);
    screenHeightLabel->setBounds (200, 64, 64, 24);
    screenHeightText->setBounds (264, 64, 48, 24);
    xOffsetLabel->setBounds (326, 32, 64, 24);
    xOffsetText->setBounds (390, 32, 48, 24);
    yOffsetLabel->setBounds (326, 64, 64, 24);
    yOffsetText->setBounds (390, 64, 48, 24);
    cameraGroup->setBounds (16, 116, getWidth() - 32, 64);
    cameraDevLabel->setBounds (32, 140, 80, 24);
    cameraDevCombo->setBounds (120, 140, 200, 24);
    cameraResLabel->setBounds (332, 140, 80, 24);
    cameraResCombo->setBounds (420, 140, 200, 24);
    audioGroup->setBounds (16, 188, getWidth() - 32, 100);
    audioApiLabel->setBounds (32, 212, 64, 24);
    audioApiCombo->setBounds (120, 212, 200, 24);
    audioDevLabel->setBounds (332, 212, 80, 24);
    audioDevCombo->setBounds (420, 212, 200, 24);
    audioCodecLabel->setBounds (33, 248, 80, 24);
    audioCodecCombo->setBounds (121, 248, 96, 24);
    nChannelsLabel->setBounds (232, 248, 80, 24);
    nChannelsSlider->setBounds (320, 248, 64, 24);
    samplerateLabel->setBounds (395, 248, 76, 24);
    samplerateCombo->setBounds (478, 248, 80, 24);
    audioBitrateLabel->setBounds (566, 248, 64, 24);
    audioBitrateCombo->setBounds (632, 248, 80, 24);
    textGroup->setBounds (16, 296, getWidth() - 32, 64);
    overlayLabel->setBounds (32, 320, 80, 24);
    overlayText->setBounds (120, 320, 284, 24);
    textStyleLabel->setBounds (420, 320, 52, 24);
    textStyleCombo->setBounds (480, 320, 80, 24);
    textPosLabel->setBounds (568, 320, 64, 24);
    textPosCombo->setBounds (632, 320, 80, 24);
    outputGroup->setBounds (16, 368, getWidth() - 32, 100);
    outputStreamLabel->setBounds (32, 392, 80, 24);
    outputStreamCombo->setBounds (120, 392, 64, 24);
    outputWidthLabel->setBounds (204, 392, 64, 24);
    outputWidthText->setBounds (268, 392, 48, 24);
    outputHeightLabel->setBounds (331, 392, 64, 24);
    outputHeightText->setBounds (395, 392, 48, 24);
    framerateLabel->setBounds (460, 392, 40, 24);
    framerateCombo->setBounds (505, 392, 48, 24);
    bitrateLabel->setBounds (565, 392, 64, 24);
    bitrateCombo->setBounds (632, 392, 80, 24);
    outputDestLabel->setBounds (32, 428, 80, 24);
    outputDestText->setBounds (120, 428, 592, 24);
    monitorsGroup->setBounds (16, 476, getWidth() - 32, 164);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Config::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
DBG("Config::sliderValueChanged()") ;
  Identifier key ;
  var        value = var((int)sliderThatWasMoved->getValue()) ;

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == displaySlider)
    {
        //[UserSliderCode_displaySlider] -- add your slider handling code here..

      key = CONFIG::DISPLAY_N_ID ;

        //[/UserSliderCode_displaySlider]
    }
    else if (sliderThatWasMoved == screenSlider)
    {
        //[UserSliderCode_screenSlider] -- add your slider handling code here..

      key = CONFIG::SCREEN_N_ID ;

        //[/UserSliderCode_screenSlider]
    }
    else if (sliderThatWasMoved == nChannelsSlider)
    {
        //[UserSliderCode_nChannelsSlider] -- add your slider handling code here..

      key = CONFIG::N_CHANNELS_ID ;

        //[/UserSliderCode_nChannelsSlider]
    }

    //[UsersliderValueChanged_Post]

  setConfig(key , value) ;

    //[/UsersliderValueChanged_Post]
}

void Config::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

  int        option_n    = comboBoxThatHasChanged->getSelectedItemIndex() ;
  int        default_idx ;
  Identifier key ;
  var        value ;

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cameraDevCombo)
    {
        //[UserComboBoxCode_cameraDevCombo] -- add your combo box handling code here..

      key         = CONFIG::CAMERA_DEV_ID ;
      default_idx = CONFIG::DEFAULT_CAMERA_DEV_IDX ;

        //[/UserComboBoxCode_cameraDevCombo]
    }
    else if (comboBoxThatHasChanged == cameraResCombo)
    {
        //[UserComboBoxCode_cameraResCombo] -- add your combo box handling code here..

      key         = CONFIG::CAMERA_RES_ID ;
      default_idx = CONFIG::DEFAULT_CAMERA_RES_IDX ;

        //[/UserComboBoxCode_cameraResCombo]
    }
    else if (comboBoxThatHasChanged == audioApiCombo)
    {
        //[UserComboBoxCode_audioApiCombo] -- add your combo box handling code here..

      key         = CONFIG::AUDIO_API_ID ;
      default_idx = CONFIG::DEFAULT_AUDIO_API_IDX ;

        //[/UserComboBoxCode_audioApiCombo]
    }
    else if (comboBoxThatHasChanged == audioDevCombo)
    {
        //[UserComboBoxCode_audioDevCombo] -- add your combo box handling code here..

      key         = CONFIG::AUDIO_DEVICE_ID ;
      default_idx = CONFIG::DEFAULT_AUDIO_DEVICE_IDX ;

        //[/UserComboBoxCode_audioDevCombo]
    }
    else if (comboBoxThatHasChanged == audioCodecCombo)
    {
        //[UserComboBoxCode_audioCodecCombo] -- add your combo box handling code here..

      key         = CONFIG::AUDIO_CODEC_ID ;
      default_idx = CONFIG::DEFAULT_AUDIO_CODEC_IDX ;

        //[/UserComboBoxCode_audioCodecCombo]
    }
    else if (comboBoxThatHasChanged == samplerateCombo)
    {
        //[UserComboBoxCode_samplerateCombo] -- add your combo box handling code here..

      key         = CONFIG::SAMPLERATE_ID ;
      default_idx = CONFIG::DEFAULT_SAMPLERATE_IDX ;

        //[/UserComboBoxCode_samplerateCombo]
    }
    else if (comboBoxThatHasChanged == audioBitrateCombo)
    {
        //[UserComboBoxCode_audioBitrateCombo] -- add your combo box handling code here..

      key         = CONFIG::AUDIO_BITRATE_ID ;
      default_idx = CONFIG::DEFAULT_AUDIO_BITRATE_IDX ;

        //[/UserComboBoxCode_audioBitrateCombo]
    }
    else if (comboBoxThatHasChanged == textStyleCombo)
    {
        //[UserComboBoxCode_textStyleCombo] -- add your combo box handling code here..

      key         = CONFIG::TEXT_STYLE_ID ;
      default_idx = CONFIG::DEFAULT_TEXT_STYLE_IDX ;

        //[/UserComboBoxCode_textStyleCombo]
    }
    else if (comboBoxThatHasChanged == textPosCombo)
    {
        //[UserComboBoxCode_textPosCombo] -- add your combo box handling code here..

      key         = CONFIG::TEXT_POS_ID ;
      default_idx = CONFIG::DEFAULT_TEXT_POS_IDX ;

        //[/UserComboBoxCode_textPosCombo]
    }
    else if (comboBoxThatHasChanged == outputStreamCombo)
    {
        //[UserComboBoxCode_outputStreamCombo] -- add your combo box handling code here..

      key         = CONFIG::OUTPUT_STREAM_ID ;
      default_idx = CONFIG::DEFAULT_OUTPUT_STREAM_IDX ;

        //[/UserComboBoxCode_outputStreamCombo]
    }
    else if (comboBoxThatHasChanged == framerateCombo)
    {
        //[UserComboBoxCode_framerateCombo] -- add your combo box handling code here..

      key         = CONFIG::FRAMERATE_ID ;
      default_idx = CONFIG::DEFAULT_FRAMERATE_IDX ;

        //[/UserComboBoxCode_framerateCombo]
    }
    else if (comboBoxThatHasChanged == bitrateCombo)
    {
        //[UserComboBoxCode_bitrateCombo] -- add your combo box handling code here..

      key         = CONFIG::BITRATE_ID ;
      default_idx = CONFIG::DEFAULT_BITRATE_IDX ;

        //[/UserComboBoxCode_bitrateCombo]
    }

    //[UsercomboBoxChanged_Post]

  value = var((~option_n) ? option_n : default_idx) ;
  comboBoxThatHasChanged->setSelectedItemIndex(option_n) ;
  setConfig(key , value) ;

    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Config::textEditorFocusLost(TextEditor& a_text_editor)
{
  Identifier a_key ;

  if      (&a_text_editor == this->screenWidthText ) a_key = CONFIG::SCREENCAP_W_ID  ;
  else if (&a_text_editor == this->screenHeightText) a_key = CONFIG::SCREENCAP_H_ID  ;
  else if (&a_text_editor == this->xOffsetText     ) a_key = CONFIG::OFFSET_X_ID     ;
  else if (&a_text_editor == this->yOffsetText     ) a_key = CONFIG::OFFSET_Y_ID     ;
  else if (&a_text_editor == this->overlayText     ) a_key = CONFIG::OVERLAY_TEXT_ID ;
  else if (&a_text_editor == this->outputWidthText ) a_key = CONFIG::OUTPUT_W_ID     ;
  else if (&a_text_editor == this->outputHeightText) a_key = CONFIG::OUTPUT_H_ID     ;
  else if (&a_text_editor == this->outputDestText  ) a_key = CONFIG::OUTPUT_DEST_ID  ;

  setConfig(a_key , var((&a_text_editor)->getText())) ;
}

void Config::populateComboBoxes()
{
  this->cameraResCombo   ->addItemList(CONFIG::CAMERA_RESOLUTIONS , 1) ;
  this->audioApiCombo    ->addItemList(CONFIG::AUDIO_APIS         , 1) ;
  this->audioCodecCombo  ->addItemList(CONFIG::AUDIO_CODECS       , 1) ;
  this->samplerateCombo  ->addItemList(CONFIG::AUDIO_SAMPLERATES  , 1) ;
  this->audioBitrateCombo->addItemList(CONFIG::AUDIO_BITRATES     , 1) ;
  this->textStyleCombo   ->addItemList(CONFIG::TEXT_STYLES        , 1) ;
  this->textPosCombo     ->addItemList(CONFIG::TEXT_POSITIONS     , 1) ;
  this->outputStreamCombo->addItemList(CONFIG::OUTPUT_STREAMS     , 1) ;
  this->framerateCombo   ->addItemList(CONFIG::OUTPUT_FRAMERATES  , 1) ;
  this->bitrateCombo     ->addItemList(CONFIG::OUTPUT_BITRATES    , 1) ;
}

void Config::loadConfig()
{
//DEBUG_TRACE_DUMP_CONFIG
DBG("Config::loadConfig() nChannelsSlider=" + String(this->nChannelsSlider->getValue()) +
  " N_CHANNELS_ID=" + STRING(this->configStore[CONFIG::N_CHANNELS_ID]) ) ;
  // TODO: populate these
//   this->cameraDevCombo->addItemList(camera_devs , 1) ;
//   this->audioDevCombo ->addItemList(audio_devs  , 1) ;

  double display_n         = double(this->configStore[CONFIG::DISPLAY_N_ID    ]) ;
  double screen_n          = double(this->configStore[CONFIG::SCREEN_N_ID     ]) ;
  String screencap_w       = STRING(this->configStore[CONFIG::SCREENCAP_W_ID  ]) ;
  String screencap_h       = STRING(this->configStore[CONFIG::SCREENCAP_H_ID  ]) ;
  String offset_x          = STRING(this->configStore[CONFIG::OFFSET_X_ID     ]) ;
  String offset_y          = STRING(this->configStore[CONFIG::OFFSET_Y_ID     ]) ;
  int    camera_dev_idx    = int   (this->configStore[CONFIG::CAMERA_DEV_ID   ]) ;
  int    camera_res_idx    = int   (this->configStore[CONFIG::CAMERA_RES_ID   ]) ;
  int    audio_api_idx     = int   (this->configStore[CONFIG::AUDIO_API_ID    ]) ;
  int    audio_dev_idx     = int   (this->configStore[CONFIG::AUDIO_DEVICE_ID ]) ;
  int    audio_codec_idx   = int   (this->configStore[CONFIG::AUDIO_CODEC_ID  ]) ;
  double n_channels        = double(this->configStore[CONFIG::N_CHANNELS_ID   ]) ;
  int    samplerate_idx    = int   (this->configStore[CONFIG::SAMPLERATE_ID   ]) ;
  int    audio_bitrate_idx = int   (this->configStore[CONFIG::AUDIO_BITRATE_ID]) ;
  int    text_style_idx    = int   (this->configStore[CONFIG::TEXT_STYLE_ID   ]) ;
  int    text_pos_idx      = int   (this->configStore[CONFIG::TEXT_POS_ID     ]) ;
  String overlay_text      = STRING(this->configStore[CONFIG::OVERLAY_TEXT_ID ]) ;
  int    output_stream_idx = int   (this->configStore[CONFIG::OUTPUT_STREAM_ID]) ;
  String output_w_text     = STRING(this->configStore[CONFIG::OUTPUT_W_ID     ]) ;
  String output_h_text     = STRING(this->configStore[CONFIG::OUTPUT_H_ID     ]) ;
  int    framerate_idx     = int   (this->configStore[CONFIG::FRAMERATE_ID    ]) ;
  int    bitrate_idx       = int   (this->configStore[CONFIG::BITRATE_ID      ]) ;
  String output_dest_text  = STRING(this->configStore[CONFIG::OUTPUT_DEST_ID  ]) ;

  this->displaySlider    ->setValue            (display_n) ;
  this->screenSlider     ->setValue            (42) ;
  this->screenWidthText  ->setText             (screencap_w) ;
  this->screenHeightText ->setText             (screencap_h) ;
  this->xOffsetText      ->setText             (offset_x) ;
  this->yOffsetText      ->setText             (offset_y) ;
  this->cameraDevCombo   ->setSelectedItemIndex(camera_dev_idx    , juce::dontSendNotification) ;
  this->cameraResCombo   ->setSelectedItemIndex(camera_res_idx    , juce::dontSendNotification) ;
  this->audioApiCombo    ->setSelectedItemIndex(audio_api_idx     , juce::dontSendNotification) ;
  this->audioDevCombo    ->setSelectedItemIndex(audio_dev_idx     , juce::dontSendNotification) ;
  this->audioCodecCombo  ->setSelectedItemIndex(audio_codec_idx   , juce::dontSendNotification) ;
  this->nChannelsSlider  ->setValue            (n_channels) ;
  this->samplerateCombo  ->setSelectedItemIndex(samplerate_idx    , juce::dontSendNotification) ;
  this->audioBitrateCombo->setSelectedItemIndex(audio_bitrate_idx , juce::dontSendNotification) ;
  this->overlayText      ->setText             (overlay_text) ;
  this->textStyleCombo   ->setSelectedItemIndex(text_style_idx    , juce::dontSendNotification) ;
  this->textPosCombo     ->setSelectedItemIndex(text_pos_idx      , juce::dontSendNotification) ;
  this->outputStreamCombo->setSelectedItemIndex(output_stream_idx , juce::dontSendNotification) ;
  this->outputWidthText  ->setText             (output_w_text) ;
  this->outputHeightText ->setText             (output_h_text) ;
  this->framerateCombo   ->setSelectedItemIndex(framerate_idx     , juce::dontSendNotification) ;
  this->bitrateCombo     ->setSelectedItemIndex(bitrate_idx       , juce::dontSendNotification) ;
  this->outputDestText   ->setText             (output_dest_text) ;
}

void Config::setConfig(Identifier a_key , var a_value)
{
DEBUG_TRACE_SET_CONFIG

  this->configStore.setProperty(a_key , a_value , nullptr) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Config" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="Component* main_window, ValueTree config_store"
                 variableInitialisers="configStore(config_store)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff101010">
    <ROUNDRECT pos="8 8 16M 16M" cornerSize="10" fill="solid: ff202020" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="screenGroup" id="3d078232c622c691" memberName="screenGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 8 32M 100" outlinecol="ffffffff"
                  textcol="ffffffff" title="Screen"/>
  <LABEL name="displayLabel" id="47dccaa09248b15c" memberName="displayLabel"
         virtualName="" explicitFocusOrder="0" pos="32 32 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Display #:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="displaySlider" id="2250b6248ed28fc6" memberName="displaySlider"
          virtualName="" explicitFocusOrder="1" pos="120 32 64 24" min="0"
          max="10" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="screenLabel" id="68a950dbc12277f7" memberName="screenLabel"
         virtualName="" explicitFocusOrder="0" pos="32 64 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Screen #:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="screenSlider" id="74df429060e256ad" memberName="screenSlider"
          virtualName="" explicitFocusOrder="2" pos="120 64 64 24" min="0"
          max="10" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="screenWidthLabel" id="1a8ebe15d549d3a2" memberName="screenWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="200 32 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Width:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="screenWidthText" id="179a2a3eef834bff" memberName="screenWidthText"
              virtualName="" explicitFocusOrder="3" pos="264 32 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="screenHeightLabel" id="778bbd3e6ce86ce2" memberName="screenHeightLabel"
         virtualName="" explicitFocusOrder="0" pos="200 64 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="screenHeightText" id="fabfd798833e0222" memberName="screenHeightText"
              virtualName="" explicitFocusOrder="4" pos="264 64 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="xOffsetLabel" id="fca78bd84d691a86" memberName="xOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="326 32 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Offset X:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="xOffsetText" id="a370562e4f63e34" memberName="xOffsetText"
              virtualName="" explicitFocusOrder="5" pos="390 32 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="yOffsetLabel" id="f2efae168df49c68" memberName="yOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="326 64 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Offset Y:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="yOffsetText" id="e4bb3613f81dc5f4" memberName="yOffsetText"
              virtualName="" explicitFocusOrder="6" pos="390 64 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="cameraGroup" id="5f4ffe47101cb73b" memberName="cameraGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 116 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Camera"/>
  <LABEL name="cameraDevLabel" id="b00161e3a7f27d06" memberName="cameraDevLabel"
         virtualName="" explicitFocusOrder="0" pos="32 140 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Device:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cameraDevCombo" id="f143a9d8fad92dd2" memberName="cameraDevCombo"
            virtualName="" explicitFocusOrder="7" pos="120 140 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="(no devices)" textWhenNoItems="(no devices)"/>
  <LABEL name="cameraResLabel" id="e2a00639ad344d6" memberName="cameraResLabel"
         virtualName="" explicitFocusOrder="0" pos="332 140 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resolution:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cameraResCombo" id="bcc0c59e13c46f76" memberName="cameraResCombo"
            virtualName="" explicitFocusOrder="8" pos="420 140 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="audioGroup" id="bd120721f1c416c8" memberName="audioGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 188 32M 100" outlinecol="ffffffff"
                  textcol="ffffffff" title="Audio"/>
  <LABEL name="audioApiLabel" id="70eaf09dd19cec91" memberName="audioApiLabel"
         virtualName="" explicitFocusOrder="0" pos="32 212 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Interface:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioApiCombo" id="1534dd6f247fe207" memberName="audioApiCombo"
            virtualName="" explicitFocusOrder="9" pos="120 212 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="audioDevLabel" id="12df9ce40ba72b7a" memberName="audioDevLabel"
         virtualName="" explicitFocusOrder="0" pos="332 212 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Device:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioDevCombo" id="899e83b4b547b630" memberName="audioDevCombo"
            virtualName="" explicitFocusOrder="10" pos="420 212 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="(no devices)" textWhenNoItems="(no devices)"/>
  <LABEL name="audioCodecLabel" id="7994dcfae467506e" memberName="audioCodecLabel"
         virtualName="" explicitFocusOrder="0" pos="33 248 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Codec:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioCodecCombo" id="2a7a7ebbdd0e6d60" memberName="audioCodecCombo"
            virtualName="" explicitFocusOrder="11" pos="121 248 96 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no devices)"/>
  <LABEL name="nChannelsLabel" id="96c39fde349e5dd5" memberName="nChannelsLabel"
         virtualName="" explicitFocusOrder="0" pos="232 248 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Channels:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nChannelsSlider" id="f465840b69633eb" memberName="nChannelsSlider"
          virtualName="" explicitFocusOrder="12" pos="320 248 64 24" min="0"
          max="10" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="samplerateLabel" id="9744752cbe30d209" memberName="samplerateLabel"
         virtualName="" explicitFocusOrder="0" pos="395 248 76 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Samplerate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="samplerateCombo" id="6adde69b5cba6e32" memberName="samplerateCombo"
            virtualName="" explicitFocusOrder="13" pos="478 248 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="audioBitrateLabel" id="166d559a6691cadc" memberName="audioBitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="566 248 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioBitrateCombo" id="7a1546dc1bcc36" memberName="audioBitrateCombo"
            virtualName="" explicitFocusOrder="14" pos="632 248 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="textGroup" id="223402a4fb961517" memberName="textGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 296 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Text"/>
  <LABEL name="overlayLabel" id="f17950cf5d2f42c4" memberName="overlayLabel"
         virtualName="" explicitFocusOrder="0" pos="32 320 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Message:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="overlayText" id="71e2b30829ce5057" memberName="overlayText"
              virtualName="" explicitFocusOrder="15" pos="120 320 284 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="textStyleLabel" id="3e58deec4ea2f148" memberName="textStyleLabel"
         virtualName="" explicitFocusOrder="0" pos="420 320 52 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Style:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textStyleCombo" id="1d3707271064fb55" memberName="textStyleCombo"
            virtualName="" explicitFocusOrder="16" pos="480 320 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="textPosLabel" id="6dd629239c17c38b" memberName="textPosLabel"
         virtualName="" explicitFocusOrder="0" pos="568 320 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Position:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textPosCombo" id="3074c311575e36ac" memberName="textPosCombo"
            virtualName="" explicitFocusOrder="17" pos="632 320 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="outputGroup" id="1fdfd2606ad4d79b" memberName="outputGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 368 32M 100" outlinecol="ffffffff"
                  textcol="ffffffff" title="Output"/>
  <LABEL name="outputStreamLabel" id="dac22e20ce0dd8e" memberName="outputStreamLabel"
         virtualName="" explicitFocusOrder="0" pos="32 392 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Dest:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="outputStreamCombo" id="12e0750a2c746a13" memberName="outputStreamCombo"
            virtualName="" explicitFocusOrder="18" pos="120 392 64 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no devices)"/>
  <LABEL name="outputWidthLabel" id="f42b11722ea56a92" memberName="outputWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="204 392 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Width:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputWidthText" id="57d131f0667f6b73" memberName="outputWidthText"
              virtualName="" explicitFocusOrder="19" pos="268 392 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="outputHeightLabel" id="f36b02ee3419aaaf" memberName="outputHeightLabel"
         virtualName="" explicitFocusOrder="0" pos="331 392 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputHeightText" id="eaa77dbf97344cbc" memberName="outputHeightText"
              virtualName="" explicitFocusOrder="20" pos="395 392 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="framerateLabel" id="45b2235a7a1f9614" memberName="framerateLabel"
         virtualName="" explicitFocusOrder="0" pos="460 392 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="FPS:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="framerateCombo" id="2560e172b011e11c" memberName="framerateCombo"
            virtualName="" explicitFocusOrder="21" pos="505 392 48 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bitrateLabel" id="bc6b3717e710f16c" memberName="bitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="565 392 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="bitrateCombo" id="54c30dff37473763" memberName="bitrateCombo"
            virtualName="" explicitFocusOrder="22" pos="632 392 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="outputDestLabel" id="a1c19ea70cf15d1b" memberName="outputDestLabel"
         virtualName="" explicitFocusOrder="0" pos="32 428 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="URI:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputDestText" id="569abe636085fb4a" memberName="outputDestText"
              virtualName="" explicitFocusOrder="23" pos="120 428 592 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="monitorsGroup" id="6607ba656d5c8919" memberName="monitorsGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 476 32M 164" outlinecol="ffffffff"
                  textcol="ffffffff" title="Monitors"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
