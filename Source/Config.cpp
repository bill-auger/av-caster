/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/

//[Headers] You can add your own extra header files here...

#include "AvCaster.h"
#include "Trace/TraceConfig.h"

//[/Headers]

#include "Config.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Config::Config ()
{
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
    cameraDevCombo->setTextWhenNothingSelected (TRANS("(no camera devices)"));
    cameraDevCombo->setTextWhenNoChoicesAvailable (TRANS("(no camera devices)"));
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
    audioDevCombo->setTextWhenNothingSelected (TRANS("(no audio devices)"));
    audioDevCombo->setTextWhenNoChoicesAvailable (TRANS("(no audio devices)"));
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

    addAndMakeVisible (motdLabel = new Label ("motdLabel",
                                              TRANS("Message:")));
    motdLabel->setFont (Font (15.00f, Font::plain));
    motdLabel->setJustificationType (Justification::centredLeft);
    motdLabel->setEditable (false, false, false);
    motdLabel->setColour (Label::textColourId, Colours::white);
    motdLabel->setColour (TextEditor::textColourId, Colours::black);
    motdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (motdText = new TextEditor ("motdText"));
    motdText->setExplicitFocusOrder (15);
    motdText->setMultiLine (false);
    motdText->setReturnKeyStartsNewLine (false);
    motdText->setReadOnly (false);
    motdText->setScrollbarsShown (true);
    motdText->setCaretVisible (true);
    motdText->setPopupMenuEnabled (true);
    motdText->setText (String::empty);

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

    addAndMakeVisible (interstitialGroup = new GroupComponent ("interstitialGroup",
                                                               TRANS("Interstitial")));
    interstitialGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    interstitialGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (locationLabel = new Label ("locationLabel",
                                                  TRANS("Location:")));
    locationLabel->setFont (Font (15.00f, Font::plain));
    locationLabel->setJustificationType (Justification::centredLeft);
    locationLabel->setEditable (false, false, false);
    locationLabel->setColour (Label::textColourId, Colours::white);
    locationLabel->setColour (TextEditor::textColourId, Colours::black);
    locationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (interstitialText = new TextEditor ("interstitialText"));
    interstitialText->setExplicitFocusOrder (18);
    interstitialText->setMultiLine (false);
    interstitialText->setReturnKeyStartsNewLine (false);
    interstitialText->setReadOnly (false);
    interstitialText->setScrollbarsShown (true);
    interstitialText->setCaretVisible (true);
    interstitialText->setPopupMenuEnabled (true);
    interstitialText->setText (String::empty);

    addAndMakeVisible (browseButton = new TextButton ("browseButton"));
    browseButton->setExplicitFocusOrder (19);
    browseButton->setButtonText (TRANS("Browse"));
    browseButton->addListener (this);

    addAndMakeVisible (outputGroup = new GroupComponent ("outputGroup",
                                                         TRANS("Output")));
    outputGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    outputGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (outputStreamLabel = new Label ("outputStreamLabel",
                                                      TRANS("Destination:")));
    outputStreamLabel->setFont (Font (15.00f, Font::plain));
    outputStreamLabel->setJustificationType (Justification::centredLeft);
    outputStreamLabel->setEditable (false, false, false);
    outputStreamLabel->setColour (Label::textColourId, Colours::white);
    outputStreamLabel->setColour (TextEditor::textColourId, Colours::black);
    outputStreamLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputSinkCombo = new ComboBox ("outputSinkCombo"));
    outputSinkCombo->setExplicitFocusOrder (20);
    outputSinkCombo->setEditableText (false);
    outputSinkCombo->setJustificationType (Justification::centredLeft);
    outputSinkCombo->setTextWhenNothingSelected (String::empty);
    outputSinkCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    outputSinkCombo->addListener (this);

    addAndMakeVisible (outputWidthLabel = new Label ("outputWidthLabel",
                                                     TRANS("Width:")));
    outputWidthLabel->setFont (Font (15.00f, Font::plain));
    outputWidthLabel->setJustificationType (Justification::centredLeft);
    outputWidthLabel->setEditable (false, false, false);
    outputWidthLabel->setColour (Label::textColourId, Colours::white);
    outputWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    outputWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputWidthText = new TextEditor ("outputWidthText"));
    outputWidthText->setExplicitFocusOrder (21);
    outputWidthText->setMultiLine (false);
    outputWidthText->setReturnKeyStartsNewLine (false);
    outputWidthText->setReadOnly (false);
    outputWidthText->setScrollbarsShown (false);
    outputWidthText->setCaretVisible (false);
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
    outputHeightText->setExplicitFocusOrder (22);
    outputHeightText->setMultiLine (false);
    outputHeightText->setReturnKeyStartsNewLine (false);
    outputHeightText->setReadOnly (false);
    outputHeightText->setScrollbarsShown (false);
    outputHeightText->setCaretVisible (false);
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
    framerateCombo->setExplicitFocusOrder (23);
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

    addAndMakeVisible (videoBitrateCombo = new ComboBox ("videoBitrateCombo"));
    videoBitrateCombo->setExplicitFocusOrder (24);
    videoBitrateCombo->setEditableText (false);
    videoBitrateCombo->setJustificationType (Justification::centredLeft);
    videoBitrateCombo->setTextWhenNothingSelected (String::empty);
    videoBitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    videoBitrateCombo->addListener (this);

    addAndMakeVisible (outputDestLabel = new Label ("outputDestLabel",
                                                    TRANS("Location:")));
    outputDestLabel->setFont (Font (15.00f, Font::plain));
    outputDestLabel->setJustificationType (Justification::centredLeft);
    outputDestLabel->setEditable (false, false, false);
    outputDestLabel->setColour (Label::textColourId, Colours::white);
    outputDestLabel->setColour (TextEditor::textColourId, Colours::black);
    outputDestLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputDestText = new TextEditor ("outputDestText"));
    outputDestText->setExplicitFocusOrder (25);
    outputDestText->setMultiLine (false);
    outputDestText->setReturnKeyStartsNewLine (false);
    outputDestText->setReadOnly (false);
    outputDestText->setScrollbarsShown (true);
    outputDestText->setCaretVisible (true);
    outputDestText->setPopupMenuEnabled (true);
    outputDestText->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  configureSlider(this->displaySlider  ) ;
  configureSlider(this->screenSlider   ) ;
  configureSlider(this->nChannelsSlider) ;

  configureTextEditor(this->screenWidthText  , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->screenHeightText , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->xOffsetText      , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->yOffsetText      , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->motdText         , GUI::MAX_MOTD_LEN      , ""                  ) ;
  configureTextEditor(this->interstitialText , GUI::MAX_FILENAME_LEN  , APP::VALID_ID_CHARS ) ;
  configureTextEditor(this->outputWidthText  , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->outputHeightText , GUI::MAX_RES_N_CHARS   , APP::DIGITS         ) ;
  configureTextEditor(this->outputDestText   , GUI::MAX_FILENAME_LEN  , APP::VALID_URI_CHARS) ;

  configureCombobox(this->cameraDevCombo   ) ;
  configureCombobox(this->cameraResCombo   ) ;
  configureCombobox(this->audioApiCombo    ) ;
  configureCombobox(this->audioDevCombo    ) ;
  configureCombobox(this->audioCodecCombo  ) ;
  configureCombobox(this->samplerateCombo  ) ;
  configureCombobox(this->audioBitrateCombo) ;
  configureCombobox(this->textStyleCombo   ) ;
  configureCombobox(this->textPosCombo     ) ;
  configureCombobox(this->outputSinkCombo  ) ;
  configureCombobox(this->framerateCombo   ) ;
  configureCombobox(this->videoBitrateCombo) ;

  // TODO: validations here or AvCasterStore->sanitizeConfig()
  //this->displaySlider->setRange(0 , GUI::MAX_DISPLAY_N , 1) ;

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
    motdLabel = nullptr;
    motdText = nullptr;
    textStyleLabel = nullptr;
    textStyleCombo = nullptr;
    textPosLabel = nullptr;
    textPosCombo = nullptr;
    interstitialGroup = nullptr;
    locationLabel = nullptr;
    interstitialText = nullptr;
    browseButton = nullptr;
    outputGroup = nullptr;
    outputStreamLabel = nullptr;
    outputSinkCombo = nullptr;
    outputWidthLabel = nullptr;
    outputWidthText = nullptr;
    outputHeightLabel = nullptr;
    outputHeightText = nullptr;
    framerateLabel = nullptr;
    framerateCombo = nullptr;
    bitrateLabel = nullptr;
    videoBitrateCombo = nullptr;
    outputDestLabel = nullptr;
    outputDestText = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Config::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 18.0f, static_cast<float> (getWidth() - 40), 86.0f, 4.000f);

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 126.0f, static_cast<float> (getWidth() - 40), 52.0f, 4.000f);

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 198.0f, static_cast<float> (getWidth() - 40), 88.0f, 4.000f);

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 304.0f, static_cast<float> (getWidth() - 40), 52.0f, 4.000f);

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 376.0f, static_cast<float> (getWidth() - 40), 54.0f, 4.000f);

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 450.0f, static_cast<float> (getWidth() - 40), 86.0f, 4.000f);

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
    audioBitrateLabel->setBounds (574, 248, 64, 24);
    audioBitrateCombo->setBounds (640, 248, 80, 24);
    textGroup->setBounds (16, 296, getWidth() - 32, 64);
    motdLabel->setBounds (32, 320, 80, 24);
    motdText->setBounds (120, 320, 284, 24);
    textStyleLabel->setBounds (420, 320, 52, 24);
    textStyleCombo->setBounds (480, 320, 80, 24);
    textPosLabel->setBounds (568, 320, 64, 24);
    textPosCombo->setBounds (640, 320, 80, 24);
    interstitialGroup->setBounds (18, 368, getWidth() - 32, 64);
    locationLabel->setBounds (34, 392, 80, 24);
    interstitialText->setBounds (122, 392, 486, 24);
    browseButton->setBounds (640, 392, 80, 24);
    outputGroup->setBounds (16, 440, getWidth() - 32, 100);
    outputStreamLabel->setBounds (32, 464, 80, 24);
    outputSinkCombo->setBounds (120, 464, 64, 24);
    outputWidthLabel->setBounds (204, 464, 64, 24);
    outputWidthText->setBounds (268, 464, 48, 24);
    outputHeightLabel->setBounds (332, 464, 64, 24);
    outputHeightText->setBounds (396, 464, 48, 24);
    framerateLabel->setBounds (460, 464, 40, 24);
    framerateCombo->setBounds (506, 464, 48, 24);
    bitrateLabel->setBounds (572, 464, 64, 24);
    videoBitrateCombo->setBounds (640, 464, 80, 24);
    outputDestLabel->setBounds (32, 500, 80, 24);
    outputDestText->setBounds (120, 500, 600, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Config::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

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

  AvCaster::SetConfig(key , value) ;

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

      key         = CONFIG::CAMERA_DEVICE_ID ;
      default_idx = CONFIG::DEFAULT_CAMERA_DEVICE_IDX ;

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

      key         = CONFIG::TEXT_POSITION_ID ;
      default_idx = CONFIG::DEFAULT_TEXT_POSITION_IDX ;

        //[/UserComboBoxCode_textPosCombo]
    }
    else if (comboBoxThatHasChanged == outputSinkCombo)
    {
        //[UserComboBoxCode_outputSinkCombo] -- add your combo box handling code here..

      key         = CONFIG::OUTPUT_SINK_ID ;
      default_idx = CONFIG::DEFAULT_OUTPUT_SINK_IDX ;

        //[/UserComboBoxCode_outputSinkCombo]
    }
    else if (comboBoxThatHasChanged == framerateCombo)
    {
        //[UserComboBoxCode_framerateCombo] -- add your combo box handling code here..

      key         = CONFIG::FRAMERATE_ID ;
      default_idx = CONFIG::DEFAULT_FRAMERATE_IDX ;

        //[/UserComboBoxCode_framerateCombo]
    }
    else if (comboBoxThatHasChanged == videoBitrateCombo)
    {
        //[UserComboBoxCode_videoBitrateCombo] -- add your combo box handling code here..

      key         = CONFIG::VIDEO_BITRATE_ID ;
      default_idx = CONFIG::DEFAULT_VIDEO_BITRATE_IDX ;

        //[/UserComboBoxCode_videoBitrateCombo]
    }

    //[UsercomboBoxChanged_Post]

  else return ;

  value = var((~option_n) ? option_n : default_idx) ;
  comboBoxThatHasChanged->setSelectedItemIndex(int(value) , juce::dontSendNotification) ;
  AvCaster::SetConfig(key , value) ;

    //[/UsercomboBoxChanged_Post]
}

void Config::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  Identifier key ;
  var        value ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == browseButton)
    {
        //[UserButtonCode_browseButton] -- add your button handler code here..

      FileChooser chooser(GUI::IMAGE_CHOOSER_TEXT , APP::HOME_DIR , APP::IMG_FILE_EXTS) ;
      if (!chooser.browseForFileToOpen()) return ;

      key   = CONFIG::IMAGE_ID ;
      value = var(chooser.getResult().getFullPathName()) ;

        //[/UserButtonCode_browseButton]
    }

    //[UserbuttonClicked_Post]

  AvCaster::SetConfig(key , value) ;

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Config::broughtToFront() { loadConfig() ; }

void Config::textEditorFocusLost(TextEditor& a_text_editor)
{
  TextEditor* ed      = &a_text_editor ;
  var         str_var = var(ed->getText()) ;
  var         int_var = var(ed->getText().getIntValue()) ;
  Identifier  key ;
  var         value ;

  if      (ed == this->screenWidthText ) { key = CONFIG::SCREENCAP_W_ID ;  value = int_var ; }
  else if (ed == this->screenHeightText) { key = CONFIG::SCREENCAP_H_ID ;  value = int_var ; }
  else if (ed == this->xOffsetText     ) { key = CONFIG::OFFSET_X_ID ;     value = int_var ; }
  else if (ed == this->yOffsetText     ) { key = CONFIG::OFFSET_Y_ID ;     value = int_var ; }
  else if (ed == this->motdText        ) { key = CONFIG::MOTD_TEXT_ID ;    value = str_var ; }
  else if (ed == this->interstitialText) { key = CONFIG::IMAGE_ID ; value = str_var ; }
  else if (ed == this->outputWidthText ) { key = CONFIG::OUTPUT_W_ID ;     value = int_var ; }
  else if (ed == this->outputHeightText) { key = CONFIG::OUTPUT_H_ID ;     value = int_var ; }
  else if (ed == this->outputDestText  ) { key = CONFIG::OUTPUT_DEST_ID ;  value = str_var ; }
  else                                   return ;

  AvCaster::SetConfig(key , value) ;
}

void Config::configureSlider(Slider* a_slider)
{
  a_slider->setColour(Slider::textBoxBackgroundColourId   , GUI::TEXT_BG_COLOR      ) ;
  a_slider->setColour(Slider::textBoxTextColourId         , GUI::TEXT_NORMAL_COLOR  ) ;
  a_slider->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  a_slider->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  a_slider->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
}

void Config::configureTextEditor(TextEditor*  a_text_editor , int max_n_chars ,
                                 const String allowed_chars                   )
{
  a_text_editor->setSelectAllWhenFocused(true) ;
  a_text_editor->setInputRestrictions(max_n_chars , allowed_chars) ;
  a_text_editor->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;
  a_text_editor->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  a_text_editor->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  a_text_editor->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  a_text_editor->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;

  a_text_editor->addListener(this) ;
}

void Config::configureCombobox(ComboBox* a_combobox)
{
  a_combobox->setColour(ComboBox::textColourId       , GUI::TEXT_NORMAL_COLOR) ;
  a_combobox->setColour(ComboBox::backgroundColourId , GUI::TEXT_BG_COLOR    ) ;
}

void Config::loadConfig()
{
  ValueTree   config_store       = AvCaster::GetConfigStore() ;
  StringArray camera_devices     = AvCaster::GetCameraNames() ;
  StringArray camera_resolutions = AvCaster::GetCameraResolutions() ;
  StringArray audio_devices      = AvCaster::GetAudioNames() ;

DEBUG_TRACE_CONFIG_LOAD_CONFIG

  double display_n         = double(config_store[CONFIG::DISPLAY_N_ID    ]) ;
  double screen_n          = double(config_store[CONFIG::SCREEN_N_ID     ]) ;
  String screencap_w       = STRING(config_store[CONFIG::SCREENCAP_W_ID  ]) ;
  String screencap_h       = STRING(config_store[CONFIG::SCREENCAP_H_ID  ]) ;
  String offset_x          = STRING(config_store[CONFIG::OFFSET_X_ID     ]) ;
  String offset_y          = STRING(config_store[CONFIG::OFFSET_Y_ID     ]) ;
  int    camera_dev_idx    = int   (config_store[CONFIG::CAMERA_DEVICE_ID]) ;
  int    camera_res_idx    = int   (config_store[CONFIG::CAMERA_RES_ID   ]) ;
  int    audio_api_idx     = int   (config_store[CONFIG::AUDIO_API_ID    ]) ;
  int    audio_dev_idx     = int   (config_store[CONFIG::AUDIO_DEVICE_ID ]) ;
  int    audio_codec_idx   = int   (config_store[CONFIG::AUDIO_CODEC_ID  ]) ;
  double n_channels        = double(config_store[CONFIG::N_CHANNELS_ID   ]) ;
  int    samplerate_idx    = int   (config_store[CONFIG::SAMPLERATE_ID   ]) ;
  int    audio_bitrate_idx = int   (config_store[CONFIG::AUDIO_BITRATE_ID]) ;
  int    text_style_idx    = int   (config_store[CONFIG::TEXT_STYLE_ID   ]) ;
  int    text_pos_idx      = int   (config_store[CONFIG::TEXT_POSITION_ID]) ;
  String motd_text         = STRING(config_store[CONFIG::MOTD_TEXT_ID    ]) ;
  String interstitial_text = STRING(config_store[CONFIG::IMAGE_ID ]) ;
  int    output_sink_idx   = int   (config_store[CONFIG::OUTPUT_SINK_ID  ]) ;
  String output_w_text     = STRING(config_store[CONFIG::OUTPUT_W_ID     ]) ;
  String output_h_text     = STRING(config_store[CONFIG::OUTPUT_H_ID     ]) ;
  int    framerate_idx     = int   (config_store[CONFIG::FRAMERATE_ID    ]) ;
  int    video_bitrate_idx = int   (config_store[CONFIG::VIDEO_BITRATE_ID]) ;
  String output_dest_text  = STRING(config_store[CONFIG::OUTPUT_DEST_ID  ]) ;
  bool   is_lctv           = AvCaster::GetPresetIdx() == CONFIG::LCTV_PRESET_IDX ;
  String output_sink       = CONFIG::OUTPUT_SINKS[output_sink_idx] ;
  String output_label_text = (is_lctv                           ) ? GUI::DEST_LCTV_TEXT :
                             (output_sink == CONFIG::FILE_OUTPUT) ? GUI::DEST_FILE_TEXT :
                             (output_sink == CONFIG::RTMP_OUTPUT) ? GUI::DEST_RTMP_TEXT :
                                                                    "ERR"               ;

  this->displaySlider    ->setValue            (display_n ) ;
  this->screenSlider     ->setValue            (screen_n  ) ;
  this->nChannelsSlider  ->setValue            (n_channels) ;
  this->screenWidthText  ->setText             (screencap_w      ) ;
  this->screenHeightText ->setText             (screencap_h      ) ;
  this->xOffsetText      ->setText             (offset_x         ) ;
  this->yOffsetText      ->setText             (offset_y         ) ;
  this->motdText         ->setText             (motd_text        ) ;
  this->interstitialText ->setText             (interstitial_text) ;
  this->outputWidthText  ->setText             (output_w_text    ) ;
  this->outputHeightText ->setText             (output_h_text    ) ;
  this->outputDestText   ->setText             (output_dest_text ) ;
  this->outputDestLabel  ->setText             (output_label_text , juce::dontSendNotification) ;
  this->cameraDevCombo   ->clear               (juce::dontSendNotification) ;
  this->cameraResCombo   ->clear               (juce::dontSendNotification) ;
  this->audioDevCombo    ->clear               (juce::dontSendNotification) ;
  this->audioApiCombo    ->clear               (juce::dontSendNotification) ;
  this->audioCodecCombo  ->clear               (juce::dontSendNotification) ;
  this->samplerateCombo  ->clear               (juce::dontSendNotification) ;
  this->audioBitrateCombo->clear               (juce::dontSendNotification) ;
  this->textStyleCombo   ->clear               (juce::dontSendNotification) ;
  this->textPosCombo     ->clear               (juce::dontSendNotification) ;
  this->outputSinkCombo  ->clear               (juce::dontSendNotification) ;
  this->framerateCombo   ->clear               (juce::dontSendNotification) ;
  this->videoBitrateCombo->clear               (juce::dontSendNotification) ;
  this->cameraDevCombo   ->addItemList         (camera_devices            , 1) ;
  this->cameraResCombo   ->addItemList         (camera_resolutions        , 1) ;
  this->audioApiCombo    ->addItemList         (CONFIG::AUDIO_APIS        , 1) ;
  this->audioDevCombo    ->addItemList         (audio_devices             , 1) ;
  this->audioCodecCombo  ->addItemList         (CONFIG::AUDIO_CODECS      , 1) ;
  this->samplerateCombo  ->addItemList         (CONFIG::AUDIO_SAMPLERATES , 1) ;
  this->audioBitrateCombo->addItemList         (CONFIG::AUDIO_BITRATES    , 1) ;
  this->textStyleCombo   ->addItemList         (CONFIG::TEXT_STYLES       , 1) ;
  this->textPosCombo     ->addItemList         (CONFIG::TEXT_POSITIONS    , 1) ;
  this->outputSinkCombo  ->addItemList         (CONFIG::OUTPUT_SINKS      , 1) ;
  this->framerateCombo   ->addItemList         (CONFIG::FRAMERATES        , 1) ;
  this->videoBitrateCombo->addItemList         (CONFIG::VIDEO_BITRATES    , 1) ;
  this->cameraDevCombo   ->setSelectedItemIndex(camera_dev_idx    , juce::dontSendNotification) ;
  this->cameraResCombo   ->setSelectedItemIndex(camera_res_idx    , juce::dontSendNotification) ;
  this->audioApiCombo    ->setSelectedItemIndex(audio_api_idx     , juce::dontSendNotification) ;
  this->audioDevCombo    ->setSelectedItemIndex(audio_dev_idx     , juce::dontSendNotification) ;
  this->audioCodecCombo  ->setSelectedItemIndex(audio_codec_idx   , juce::dontSendNotification) ;
  this->samplerateCombo  ->setSelectedItemIndex(samplerate_idx    , juce::dontSendNotification) ;
  this->audioBitrateCombo->setSelectedItemIndex(audio_bitrate_idx , juce::dontSendNotification) ;
  this->textStyleCombo   ->setSelectedItemIndex(text_style_idx    , juce::dontSendNotification) ;
  this->textPosCombo     ->setSelectedItemIndex(text_pos_idx      , juce::dontSendNotification) ;
  this->outputSinkCombo  ->setSelectedItemIndex(output_sink_idx   , juce::dontSendNotification) ;
  this->framerateCombo   ->setSelectedItemIndex(framerate_idx     , juce::dontSendNotification) ;
  this->videoBitrateCombo->setSelectedItemIndex(video_bitrate_idx , juce::dontSendNotification) ;

  enableComponents() ;
}

void Config::enableComponents()
{
  bool is_static_preset = AvCaster::IsStaticPreset() ;

  this->audioCodecCombo->setEnabled(!is_static_preset) ; // TODO: videoCodecCombo
  this->outputSinkCombo->setEnabled(!is_static_preset) ; // TODO: outputMuxerCombo

#ifdef DISABLE_CONTROLS_NYI
this->displaySlider   ->setEnabled(false) ;
this->screenSlider    ->setEnabled(false) ;
this->xOffsetText     ->setEnabled(false) ;
this->yOffsetText     ->setEnabled(false) ;
this->cameraResCombo  ->setEnabled(false) ;
this->audioDevCombo   ->setEnabled(false) ;
this->audioCodecCombo ->setEnabled(false) ;
this->motdText        ->setEnabled(false) ;
this->textStyleCombo  ->setEnabled(false) ;
this->textPosCombo    ->setEnabled(false) ;
this->interstitialText->setEnabled(false) ;
this->browseButton    ->setEnabled(false) ;
#endif // DISABLE_CONTROLS_NYI
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
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1"
                 initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="20 18 40M 86" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
    <ROUNDRECT pos="20 126 40M 52" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
    <ROUNDRECT pos="20 198 40M 88" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
    <ROUNDRECT pos="20 304 40M 52" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
    <ROUNDRECT pos="20 376 40M 54" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
    <ROUNDRECT pos="20 450 40M 86" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
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
            layout="33" items="" textWhenNonSelected="(no camera devices)"
            textWhenNoItems="(no camera devices)"/>
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
            layout="33" items="" textWhenNonSelected="(no audio devices)"
            textWhenNoItems="(no audio devices)"/>
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
         virtualName="" explicitFocusOrder="0" pos="574 248 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioBitrateCombo" id="7a1546dc1bcc36" memberName="audioBitrateCombo"
            virtualName="" explicitFocusOrder="14" pos="640 248 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="textGroup" id="223402a4fb961517" memberName="textGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 296 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Text"/>
  <LABEL name="motdLabel" id="e26a158d569b8f" memberName="motdLabel" virtualName=""
         explicitFocusOrder="0" pos="32 320 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Message:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="motdText" id="fb4f8a059431ce61" memberName="motdText" virtualName=""
              explicitFocusOrder="15" pos="120 320 284 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
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
            virtualName="" explicitFocusOrder="17" pos="640 320 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="interstitialGroup" id="21b5d7e16b61393b" memberName="interstitialGroup"
                  virtualName="" explicitFocusOrder="0" pos="18 368 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Interstitial"/>
  <LABEL name="locationLabel" id="d9e5b9eda1c0b4fe" memberName="locationLabel"
         virtualName="" explicitFocusOrder="0" pos="34 392 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Location:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="interstitialText" id="7634583caff4457b" memberName="interstitialText"
              virtualName="" explicitFocusOrder="18" pos="122 392 486 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="browseButton" id="b593253ef702db73" memberName="browseButton"
              virtualName="" explicitFocusOrder="19" pos="640 392 80 24" buttonText="Browse"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="outputGroup" id="1fdfd2606ad4d79b" memberName="outputGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 440 32M 100" outlinecol="ffffffff"
                  textcol="ffffffff" title="Output"/>
  <LABEL name="outputStreamLabel" id="dac22e20ce0dd8e" memberName="outputStreamLabel"
         virtualName="" explicitFocusOrder="0" pos="32 464 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Destination:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="outputSinkCombo" id="12e0750a2c746a13" memberName="outputSinkCombo"
            virtualName="" explicitFocusOrder="20" pos="120 464 64 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no devices)"/>
  <LABEL name="outputWidthLabel" id="f42b11722ea56a92" memberName="outputWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="204 464 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Width:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputWidthText" id="57d131f0667f6b73" memberName="outputWidthText"
              virtualName="" explicitFocusOrder="21" pos="268 464 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="1"/>
  <LABEL name="outputHeightLabel" id="786372012685b65a" memberName="outputHeightLabel"
         virtualName="" explicitFocusOrder="0" pos="332 464 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputHeightText" id="7e14834485ae7a91" memberName="outputHeightText"
              virtualName="" explicitFocusOrder="22" pos="396 464 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="1"/>
  <LABEL name="framerateLabel" id="45b2235a7a1f9614" memberName="framerateLabel"
         virtualName="" explicitFocusOrder="0" pos="460 464 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="FPS:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="framerateCombo" id="2560e172b011e11c" memberName="framerateCombo"
            virtualName="" explicitFocusOrder="23" pos="506 464 48 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bitrateLabel" id="bc6b3717e710f16c" memberName="bitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="572 464 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="videoBitrateCombo" id="54c30dff37473763" memberName="videoBitrateCombo"
            virtualName="" explicitFocusOrder="24" pos="640 464 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="outputDestLabel" id="a1c19ea70cf15d1b" memberName="outputDestLabel"
         virtualName="" explicitFocusOrder="0" pos="32 500 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Location:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputDestText" id="569abe636085fb4a" memberName="outputDestText"
              virtualName="" explicitFocusOrder="25" pos="120 500 600 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
