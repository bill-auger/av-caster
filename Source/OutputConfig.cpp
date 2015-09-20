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

//[Headers] You can add your own extra header files here...

#include "Constants.h"

//[/Headers]

#include "OutputConfig.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OutputConfig::OutputConfig (Component* main_window)
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

    addAndMakeVisible (textGroup2 = new GroupComponent ("textGroup",
                                                        TRANS("Audio")));
    textGroup2->setColour (GroupComponent::outlineColourId, Colours::white);
    textGroup2->setColour (GroupComponent::textColourId, Colours::white);

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

    addAndMakeVisible (nChannelsLabel = new Label ("nChannelsLabel",
                                                   TRANS("Channels:")));
    nChannelsLabel->setFont (Font (15.00f, Font::plain));
    nChannelsLabel->setJustificationType (Justification::centredLeft);
    nChannelsLabel->setEditable (false, false, false);
    nChannelsLabel->setColour (Label::textColourId, Colours::white);
    nChannelsLabel->setColour (TextEditor::textColourId, Colours::black);
    nChannelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nChannelsSlider = new Slider ("nChannelsSlider"));
    nChannelsSlider->setExplicitFocusOrder (10);
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
    samplerateCombo->setExplicitFocusOrder (11);
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
    audioBitrateCombo->setExplicitFocusOrder (12);
    audioBitrateCombo->setEditableText (false);
    audioBitrateCombo->setJustificationType (Justification::centredLeft);
    audioBitrateCombo->setTextWhenNothingSelected (String::empty);
    audioBitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    audioBitrateCombo->addListener (this);

    addAndMakeVisible (textGroup = new GroupComponent ("textGroup",
                                                       TRANS("Text")));
    textGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    textGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (messageLabel = new Label ("messageLabel",
                                                 TRANS("Message:")));
    messageLabel->setFont (Font (15.00f, Font::plain));
    messageLabel->setJustificationType (Justification::centredLeft);
    messageLabel->setEditable (false, false, false);
    messageLabel->setColour (Label::textColourId, Colours::white);
    messageLabel->setColour (TextEditor::textColourId, Colours::black);
    messageLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (messageText = new TextEditor ("messageText"));
    messageText->setExplicitFocusOrder (13);
    messageText->setMultiLine (false);
    messageText->setReturnKeyStartsNewLine (false);
    messageText->setReadOnly (false);
    messageText->setScrollbarsShown (true);
    messageText->setCaretVisible (true);
    messageText->setPopupMenuEnabled (true);
    messageText->setText (String::empty);

    addAndMakeVisible (textStyleLabel = new Label ("textStyleLabel",
                                                   TRANS("Style:")));
    textStyleLabel->setFont (Font (15.00f, Font::plain));
    textStyleLabel->setJustificationType (Justification::centredLeft);
    textStyleLabel->setEditable (false, false, false);
    textStyleLabel->setColour (Label::textColourId, Colours::white);
    textStyleLabel->setColour (TextEditor::textColourId, Colours::black);
    textStyleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textStyleCombo = new ComboBox ("textStyleCombo"));
    textStyleCombo->setExplicitFocusOrder (14);
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
    textPosCombo->setExplicitFocusOrder (15);
    textPosCombo->setEditableText (false);
    textPosCombo->setJustificationType (Justification::centredLeft);
    textPosCombo->setTextWhenNothingSelected (String::empty);
    textPosCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textPosCombo->addListener (this);

    addAndMakeVisible (outputGroup = new GroupComponent ("outputGroup",
                                                         TRANS("Output")));
    outputGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    outputGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (outputResLabel = new Label ("outputResLabel",
                                                   TRANS("Resolution:")));
    outputResLabel->setFont (Font (15.00f, Font::plain));
    outputResLabel->setJustificationType (Justification::centredLeft);
    outputResLabel->setEditable (false, false, false);
    outputResLabel->setColour (Label::textColourId, Colours::white);
    outputResLabel->setColour (TextEditor::textColourId, Colours::black);
    outputResLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputResCombo = new ComboBox ("outputResCombo"));
    outputResCombo->setExplicitFocusOrder (16);
    outputResCombo->setEditableText (false);
    outputResCombo->setJustificationType (Justification::centredLeft);
    outputResCombo->setTextWhenNothingSelected (String::empty);
    outputResCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    outputResCombo->addListener (this);

    addAndMakeVisible (qualityLabel = new Label ("qualityLabel",
                                                 TRANS("Quality:")));
    qualityLabel->setFont (Font (15.00f, Font::plain));
    qualityLabel->setJustificationType (Justification::centredLeft);
    qualityLabel->setEditable (false, false, false);
    qualityLabel->setColour (Label::textColourId, Colours::white);
    qualityLabel->setColour (TextEditor::textColourId, Colours::black);
    qualityLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (qualityCombo = new ComboBox ("qualityCombo"));
    qualityCombo->setExplicitFocusOrder (17);
    qualityCombo->setEditableText (false);
    qualityCombo->setJustificationType (Justification::centredLeft);
    qualityCombo->setTextWhenNothingSelected (String::empty);
    qualityCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    qualityCombo->addListener (this);

    addAndMakeVisible (fpsLabel = new Label ("fpsLabel",
                                             TRANS("FPS:")));
    fpsLabel->setFont (Font (15.00f, Font::plain));
    fpsLabel->setJustificationType (Justification::centredLeft);
    fpsLabel->setEditable (false, false, false);
    fpsLabel->setColour (Label::textColourId, Colours::white);
    fpsLabel->setColour (TextEditor::textColourId, Colours::black);
    fpsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fpsCombo = new ComboBox ("fpsCombo"));
    fpsCombo->setExplicitFocusOrder (18);
    fpsCombo->setEditableText (false);
    fpsCombo->setJustificationType (Justification::centredLeft);
    fpsCombo->setTextWhenNothingSelected (String::empty);
    fpsCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    fpsCombo->addListener (this);

    addAndMakeVisible (bitrateLabel = new Label ("bitrateLabel",
                                                 TRANS("Bitrate:")));
    bitrateLabel->setFont (Font (15.00f, Font::plain));
    bitrateLabel->setJustificationType (Justification::centredLeft);
    bitrateLabel->setEditable (false, false, false);
    bitrateLabel->setColour (Label::textColourId, Colours::white);
    bitrateLabel->setColour (TextEditor::textColourId, Colours::black);
    bitrateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bitrateCombo = new ComboBox ("bitrateCombo"));
    bitrateCombo->setExplicitFocusOrder (19);
    bitrateCombo->setEditableText (false);
    bitrateCombo->setJustificationType (Justification::centredLeft);
    bitrateCombo->setTextWhenNothingSelected (String::empty);
    bitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    bitrateCombo->addListener (this);

    addAndMakeVisible (monitorsGroup = new GroupComponent ("monitorsGroup",
                                                           TRANS("Monitors")));
    monitorsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    monitorsGroup->setColour (GroupComponent::textColourId, Colours::white);


    //[UserPreSize]

#ifndef DEBUG_NO_INSTANTIATE_MONITORS
  // video monitors
  this->screencapMonitor = new GstreamerVideo(main_window , GUI::SCREENCAP_MONITOR_X , GUI::MONITORS_Y) ;
  this->cameratMonitor   = new GstreamerVideo(main_window , GUI::CAMERA_MONITOR_X    , GUI::MONITORS_Y) ;
  this->outputMonitor    = new GstreamerVideo(main_window , GUI::OUTPUT_MONITOR_X    , GUI::MONITORS_Y) ;
#endif // DEBUG_NO_INSTANTIATE_MONITORS

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OutputConfig::~OutputConfig()
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
    textGroup2 = nullptr;
    audioApiLabel = nullptr;
    audioApiCombo = nullptr;
    nChannelsLabel = nullptr;
    nChannelsSlider = nullptr;
    samplerateLabel = nullptr;
    samplerateCombo = nullptr;
    audioBitrateLabel = nullptr;
    audioBitrateCombo = nullptr;
    textGroup = nullptr;
    messageLabel = nullptr;
    messageText = nullptr;
    textStyleLabel = nullptr;
    textStyleCombo = nullptr;
    textPosLabel = nullptr;
    textPosCombo = nullptr;
    outputGroup = nullptr;
    outputResLabel = nullptr;
    outputResCombo = nullptr;
    qualityLabel = nullptr;
    qualityCombo = nullptr;
    fpsLabel = nullptr;
    fpsCombo = nullptr;
    bitrateLabel = nullptr;
    bitrateCombo = nullptr;
    monitorsGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

  screencapMonitor = nullptr ;
  cameratMonitor   = nullptr ;
  outputMonitor    = nullptr ;

    //[/Destructor]
}

//==============================================================================
void OutputConfig::paint (Graphics& g)
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

void OutputConfig::resized()
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
    cameraGroup->setBounds (16, 116, getWidth() - 32, 100);
    cameraDevLabel->setBounds (32, 140, 80, 24);
    cameraDevCombo->setBounds (120, 140, 200, 24);
    cameraResLabel->setBounds (32, 172, 80, 24);
    cameraResCombo->setBounds (120, 172, 200, 24);
    textGroup2->setBounds (16, 224, getWidth() - 32, 64);
    audioApiLabel->setBounds (32, 248, 64, 24);
    audioApiCombo->setBounds (120, 248, 96, 24);
    nChannelsLabel->setBounds (245, 248, 80, 24);
    nChannelsSlider->setBounds (333, 248, 64, 24);
    samplerateLabel->setBounds (408, 248, 76, 24);
    samplerateCombo->setBounds (480, 248, 80, 24);
    audioBitrateLabel->setBounds (568, 248, 64, 24);
    audioBitrateCombo->setBounds (632, 248, 80, 24);
    textGroup->setBounds (16, 296, getWidth() - 32, 64);
    messageLabel->setBounds (32, 320, 80, 24);
    messageText->setBounds (120, 320, 284, 24);
    textStyleLabel->setBounds (420, 320, 52, 24);
    textStyleCombo->setBounds (480, 320, 80, 24);
    textPosLabel->setBounds (568, 320, 64, 24);
    textPosCombo->setBounds (632, 320, 80, 24);
    outputGroup->setBounds (16, 368, getWidth() - 32, 100);
    outputResLabel->setBounds (32, 392, 80, 24);
    outputResCombo->setBounds (120, 392, 200, 24);
    qualityLabel->setBounds (32, 424, 80, 24);
    qualityCombo->setBounds (120, 424, 200, 24);
    fpsLabel->setBounds (340, 392, 64, 24);
    fpsCombo->setBounds (404, 392, 48, 24);
    bitrateLabel->setBounds (340, 424, 64, 24);
    bitrateCombo->setBounds (404, 424, 80, 24);
    monitorsGroup->setBounds (16, 476, getWidth() - 32, 164);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OutputConfig::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == displaySlider)
    {
        //[UserSliderCode_displaySlider] -- add your slider handling code here..
        //[/UserSliderCode_displaySlider]
    }
    else if (sliderThatWasMoved == screenSlider)
    {
        //[UserSliderCode_screenSlider] -- add your slider handling code here..
        //[/UserSliderCode_screenSlider]
    }
    else if (sliderThatWasMoved == nChannelsSlider)
    {
        //[UserSliderCode_nChannelsSlider] -- add your slider handling code here..
        //[/UserSliderCode_nChannelsSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void OutputConfig::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cameraDevCombo)
    {
        //[UserComboBoxCode_cameraDevCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_cameraDevCombo]
    }
    else if (comboBoxThatHasChanged == cameraResCombo)
    {
        //[UserComboBoxCode_cameraResCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_cameraResCombo]
    }
    else if (comboBoxThatHasChanged == audioApiCombo)
    {
        //[UserComboBoxCode_audioApiCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_audioApiCombo]
    }
    else if (comboBoxThatHasChanged == samplerateCombo)
    {
        //[UserComboBoxCode_samplerateCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_samplerateCombo]
    }
    else if (comboBoxThatHasChanged == audioBitrateCombo)
    {
        //[UserComboBoxCode_audioBitrateCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_audioBitrateCombo]
    }
    else if (comboBoxThatHasChanged == textStyleCombo)
    {
        //[UserComboBoxCode_textStyleCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_textStyleCombo]
    }
    else if (comboBoxThatHasChanged == textPosCombo)
    {
        //[UserComboBoxCode_textPosCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_textPosCombo]
    }
    else if (comboBoxThatHasChanged == outputResCombo)
    {
        //[UserComboBoxCode_outputResCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_outputResCombo]
    }
    else if (comboBoxThatHasChanged == qualityCombo)
    {
        //[UserComboBoxCode_qualityCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_qualityCombo]
    }
    else if (comboBoxThatHasChanged == fpsCombo)
    {
        //[UserComboBoxCode_fpsCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_fpsCombo]
    }
    else if (comboBoxThatHasChanged == bitrateCombo)
    {
        //[UserComboBoxCode_bitrateCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_bitrateCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OutputConfig" componentName=""
                 parentClasses="public Component" constructorParams="Component* main_window"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
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
                  virtualName="" explicitFocusOrder="0" pos="16 116 32M 100" outlinecol="ffffffff"
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
         virtualName="" explicitFocusOrder="0" pos="32 172 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resolution:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cameraResCombo" id="bcc0c59e13c46f76" memberName="cameraResCombo"
            virtualName="" explicitFocusOrder="8" pos="120 172 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="textGroup" id="bd120721f1c416c8" memberName="textGroup2"
                  virtualName="" explicitFocusOrder="0" pos="16 224 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Audio"/>
  <LABEL name="audioApiLabel" id="70eaf09dd19cec91" memberName="audioApiLabel"
         virtualName="" explicitFocusOrder="0" pos="32 248 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Interface:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioApiCombo" id="1534dd6f247fe207" memberName="audioApiCombo"
            virtualName="" explicitFocusOrder="9" pos="120 248 96 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="nChannelsLabel" id="96c39fde349e5dd5" memberName="nChannelsLabel"
         virtualName="" explicitFocusOrder="0" pos="245 248 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Channels:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="nChannelsSlider" id="f465840b69633eb" memberName="nChannelsSlider"
          virtualName="" explicitFocusOrder="10" pos="333 248 64 24" min="0"
          max="10" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="samplerateLabel" id="9744752cbe30d209" memberName="samplerateLabel"
         virtualName="" explicitFocusOrder="0" pos="408 248 76 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Samplerate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="samplerateCombo" id="6adde69b5cba6e32" memberName="samplerateCombo"
            virtualName="" explicitFocusOrder="11" pos="480 248 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="audioBitrateLabel" id="166d559a6691cadc" memberName="audioBitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="568 248 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioBitrateCombo" id="7a1546dc1bcc36" memberName="audioBitrateCombo"
            virtualName="" explicitFocusOrder="12" pos="632 248 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="textGroup" id="223402a4fb961517" memberName="textGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 296 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Text"/>
  <LABEL name="messageLabel" id="f17950cf5d2f42c4" memberName="messageLabel"
         virtualName="" explicitFocusOrder="0" pos="32 320 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Message:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="messageText" id="71e2b30829ce5057" memberName="messageText"
              virtualName="" explicitFocusOrder="13" pos="120 320 284 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="textStyleLabel" id="3e58deec4ea2f148" memberName="textStyleLabel"
         virtualName="" explicitFocusOrder="0" pos="420 320 52 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Style:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textStyleCombo" id="1d3707271064fb55" memberName="textStyleCombo"
            virtualName="" explicitFocusOrder="14" pos="480 320 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="textPosLabel" id="6dd629239c17c38b" memberName="textPosLabel"
         virtualName="" explicitFocusOrder="0" pos="568 320 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Position:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textPosCombo" id="3074c311575e36ac" memberName="textPosCombo"
            virtualName="" explicitFocusOrder="15" pos="632 320 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="outputGroup" id="1fdfd2606ad4d79b" memberName="outputGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 368 32M 100" outlinecol="ffffffff"
                  textcol="ffffffff" title="Output"/>
  <LABEL name="outputResLabel" id="89b96f9677997734" memberName="outputResLabel"
         virtualName="" explicitFocusOrder="0" pos="32 392 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resolution:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="outputResCombo" id="be92db8f9d61539a" memberName="outputResCombo"
            virtualName="" explicitFocusOrder="16" pos="120 392 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="qualityLabel" id="3e3fc79312764817" memberName="qualityLabel"
         virtualName="" explicitFocusOrder="0" pos="32 424 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Quality:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="qualityCombo" id="71cfff3261da7b1a" memberName="qualityCombo"
            virtualName="" explicitFocusOrder="17" pos="120 424 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="fpsLabel" id="45b2235a7a1f9614" memberName="fpsLabel" virtualName=""
         explicitFocusOrder="0" pos="340 392 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="FPS:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="fpsCombo" id="2560e172b011e11c" memberName="fpsCombo" virtualName=""
            explicitFocusOrder="18" pos="404 392 48 24" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bitrateLabel" id="bc6b3717e710f16c" memberName="bitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="340 424 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="bitrateCombo" id="54c30dff37473763" memberName="bitrateCombo"
            virtualName="" explicitFocusOrder="19" pos="404 424 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="monitorsGroup" id="6607ba656d5c8919" memberName="monitorsGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 476 32M 164" outlinecol="ffffffff"
                  textcol="ffffffff" title="Monitors"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
