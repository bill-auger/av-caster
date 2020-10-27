/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ConfigAudio.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigAudio::ConfigAudio ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    audioApiLabel.reset (new Label ("audioApiLabel",
                                    TRANS("Interface:")));
    addAndMakeVisible (audioApiLabel.get());
    audioApiLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    audioApiLabel->setJustificationType (Justification::centredLeft);
    audioApiLabel->setEditable (false, false, false);
    audioApiLabel->setColour (Label::textColourId, Colours::white);
    audioApiLabel->setColour (TextEditor::textColourId, Colours::black);
    audioApiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    audioApiLabel->setBounds (0, 8, 64, 24);

    audioApiCombo.reset (new ComboBox ("audioApiCombo"));
    addAndMakeVisible (audioApiCombo.get());
    audioApiCombo->setExplicitFocusOrder (1);
    audioApiCombo->setEditableText (false);
    audioApiCombo->setJustificationType (Justification::centredLeft);
    audioApiCombo->setTextWhenNothingSelected (String());
    audioApiCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    audioApiCombo->addListener (this);

    audioApiCombo->setBounds (88, 8, 200, 24);

    audioDevLabel.reset (new Label ("audioDevLabel",
                                    TRANS("Device:")));
    addAndMakeVisible (audioDevLabel.get());
    audioDevLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    audioDevLabel->setJustificationType (Justification::centredLeft);
    audioDevLabel->setEditable (false, false, false);
    audioDevLabel->setColour (Label::textColourId, Colours::white);
    audioDevLabel->setColour (TextEditor::textColourId, Colours::black);
    audioDevLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    audioDevLabel->setBounds (0, 48, 80, 24);

    audioDevCombo.reset (new ComboBox ("audioDevCombo"));
    addAndMakeVisible (audioDevCombo.get());
    audioDevCombo->setExplicitFocusOrder (2);
    audioDevCombo->setEditableText (false);
    audioDevCombo->setJustificationType (Justification::centredLeft);
    audioDevCombo->setTextWhenNothingSelected (TRANS("(no audio devices)"));
    audioDevCombo->setTextWhenNoChoicesAvailable (TRANS("(no audio devices)"));
    audioDevCombo->addListener (this);

    audioDevCombo->setBounds (88, 48, 200, 24);

    audioCodecLabel.reset (new Label ("audioCodecLabel",
                                      TRANS("Codec:")));
    addAndMakeVisible (audioCodecLabel.get());
    audioCodecLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    audioCodecLabel->setJustificationType (Justification::centredLeft);
    audioCodecLabel->setEditable (false, false, false);
    audioCodecLabel->setColour (Label::textColourId, Colours::white);
    audioCodecLabel->setColour (TextEditor::textColourId, Colours::black);
    audioCodecLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    audioCodecLabel->setBounds (0, 88, 80, 24);

    audioCodecCombo.reset (new ComboBox ("audioCodecCombo"));
    addAndMakeVisible (audioCodecCombo.get());
    audioCodecCombo->setExplicitFocusOrder (3);
    audioCodecCombo->setEditableText (false);
    audioCodecCombo->setJustificationType (Justification::centredLeft);
    audioCodecCombo->setTextWhenNothingSelected (String());
    audioCodecCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    audioCodecCombo->addListener (this);

    audioCodecCombo->setBounds (88, 88, 96, 24);

    nChannelsLabel.reset (new Label ("nChannelsLabel",
                                     TRANS("Channels:")));
    addAndMakeVisible (nChannelsLabel.get());
    nChannelsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nChannelsLabel->setJustificationType (Justification::centredLeft);
    nChannelsLabel->setEditable (false, false, false);
    nChannelsLabel->setColour (Label::textColourId, Colours::white);
    nChannelsLabel->setColour (TextEditor::textColourId, Colours::black);
    nChannelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nChannelsLabel->setBounds (0, 128, 80, 24);

    nChannelsSlider.reset (new Slider ("nChannelsSlider"));
    addAndMakeVisible (nChannelsSlider.get());
    nChannelsSlider->setExplicitFocusOrder (4);
    nChannelsSlider->setRange (0, 10, 0);
    nChannelsSlider->setSliderStyle (Slider::IncDecButtons);
    nChannelsSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    nChannelsSlider->addListener (this);

    nChannelsSlider->setBounds (88, 128, 64, 24);

    samplerateLabel.reset (new Label ("samplerateLabel",
                                      TRANS("Samplerate:")));
    addAndMakeVisible (samplerateLabel.get());
    samplerateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    samplerateLabel->setJustificationType (Justification::centredLeft);
    samplerateLabel->setEditable (false, false, false);
    samplerateLabel->setColour (Label::textColourId, Colours::white);
    samplerateLabel->setColour (TextEditor::textColourId, Colours::black);
    samplerateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    samplerateLabel->setBounds (0, 168, 76, 24);

    samplerateCombo.reset (new ComboBox ("samplerateCombo"));
    addAndMakeVisible (samplerateCombo.get());
    samplerateCombo->setExplicitFocusOrder (5);
    samplerateCombo->setEditableText (false);
    samplerateCombo->setJustificationType (Justification::centredLeft);
    samplerateCombo->setTextWhenNothingSelected (String());
    samplerateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    samplerateCombo->addListener (this);

    samplerateCombo->setBounds (88, 168, 80, 24);

    audioBitrateLabel.reset (new Label ("audioBitrateLabel",
                                        TRANS("Bitrate:")));
    addAndMakeVisible (audioBitrateLabel.get());
    audioBitrateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    audioBitrateLabel->setJustificationType (Justification::centredLeft);
    audioBitrateLabel->setEditable (false, false, false);
    audioBitrateLabel->setColour (Label::textColourId, Colours::white);
    audioBitrateLabel->setColour (TextEditor::textColourId, Colours::black);
    audioBitrateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    audioBitrateLabel->setBounds (0, 208, 64, 24);

    audioBitrateCombo.reset (new ComboBox ("audioBitrateCombo"));
    addAndMakeVisible (audioBitrateCombo.get());
    audioBitrateCombo->setExplicitFocusOrder (6);
    audioBitrateCombo->setEditableText (false);
    audioBitrateCombo->setJustificationType (Justification::centredLeft);
    audioBitrateCombo->setTextWhenNothingSelected (String());
    audioBitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    audioBitrateCombo->addListener (this);

    audioBitrateCombo->setBounds (88, 208, 80, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigAudio::~ConfigAudio()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigAudio::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigAudio::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigAudio::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == audioApiCombo.get())
    {
        //[UserComboBoxCode_audioApiCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_audioApiCombo]
    }
    else if (comboBoxThatHasChanged == audioDevCombo.get())
    {
        //[UserComboBoxCode_audioDevCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_audioDevCombo]
    }
    else if (comboBoxThatHasChanged == audioCodecCombo.get())
    {
        //[UserComboBoxCode_audioCodecCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_audioCodecCombo]
    }
    else if (comboBoxThatHasChanged == samplerateCombo.get())
    {
        //[UserComboBoxCode_samplerateCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_samplerateCombo]
    }
    else if (comboBoxThatHasChanged == audioBitrateCombo.get())
    {
        //[UserComboBoxCode_audioBitrateCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_audioBitrateCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ConfigAudio::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == nChannelsSlider.get())
    {
        //[UserSliderCode_nChannelsSlider] -- add your slider handling code here..

      // NOTE: handled in Config

        //[/UserSliderCode_nChannelsSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigAudio" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="4" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="audioApiLabel" id="70eaf09dd19cec91" memberName="audioApiLabel"
         virtualName="" explicitFocusOrder="0" pos="0 8 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Interface:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioApiCombo" id="1534dd6f247fe207" memberName="audioApiCombo"
            virtualName="" explicitFocusOrder="1" pos="88 8 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="audioDevLabel" id="12df9ce40ba72b7a" memberName="audioDevLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Device:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioDevCombo" id="899e83b4b547b630" memberName="audioDevCombo"
            virtualName="" explicitFocusOrder="2" pos="88 48 200 24" editable="0"
            layout="33" items="" textWhenNonSelected="(no audio devices)"
            textWhenNoItems="(no audio devices)"/>
  <LABEL name="audioCodecLabel" id="7994dcfae467506e" memberName="audioCodecLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Codec:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioCodecCombo" id="2a7a7ebbdd0e6d60" memberName="audioCodecCombo"
            virtualName="" explicitFocusOrder="3" pos="88 88 96 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no devices)"/>
  <LABEL name="nChannelsLabel" id="96c39fde349e5dd5" memberName="nChannelsLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Channels:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="nChannelsSlider" id="f465840b69633eb" memberName="nChannelsSlider"
          virtualName="" explicitFocusOrder="4" pos="88 128 64 24" min="0.0"
          max="10.0" int="0.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="samplerateLabel" id="9744752cbe30d209" memberName="samplerateLabel"
         virtualName="" explicitFocusOrder="0" pos="0 168 76 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Samplerate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="samplerateCombo" id="6adde69b5cba6e32" memberName="samplerateCombo"
            virtualName="" explicitFocusOrder="5" pos="88 168 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="audioBitrateLabel" id="166d559a6691cadc" memberName="audioBitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="0 208 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="audioBitrateCombo" id="7a1546dc1bcc36" memberName="audioBitrateCombo"
            virtualName="" explicitFocusOrder="6" pos="88 208 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

