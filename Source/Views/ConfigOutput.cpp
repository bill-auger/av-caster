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

#include "ConfigOutput.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigOutput::ConfigOutput ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    outputStreamLabel.reset (new Label ("outputStreamLabel",
                                        TRANS("Stream:")));
    addAndMakeVisible (outputStreamLabel.get());
    outputStreamLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputStreamLabel->setJustificationType (Justification::centredLeft);
    outputStreamLabel->setEditable (false, false, false);
    outputStreamLabel->setColour (Label::textColourId, Colours::white);
    outputStreamLabel->setColour (TextEditor::textColourId, Colours::black);
    outputStreamLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputStreamLabel->setBounds (0, 8, 80, 24);

    outputSinkCombo.reset (new ComboBox ("outputSinkCombo"));
    addAndMakeVisible (outputSinkCombo.get());
    outputSinkCombo->setExplicitFocusOrder (1);
    outputSinkCombo->setEditableText (false);
    outputSinkCombo->setJustificationType (Justification::centredLeft);
    outputSinkCombo->setTextWhenNothingSelected (String());
    outputSinkCombo->setTextWhenNoChoicesAvailable (TRANS("(no devices)"));
    outputSinkCombo->addListener (this);

    outputSinkCombo->setBounds (88, 8, 64, 24);

    outputWidthLabel.reset (new Label ("outputWidthLabel",
                                       TRANS("Width:")));
    addAndMakeVisible (outputWidthLabel.get());
    outputWidthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputWidthLabel->setJustificationType (Justification::centredLeft);
    outputWidthLabel->setEditable (false, false, false);
    outputWidthLabel->setColour (Label::textColourId, Colours::white);
    outputWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    outputWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputWidthLabel->setBounds (0, 48, 64, 24);

    outputWidthText.reset (new TextEditor ("outputWidthText"));
    addAndMakeVisible (outputWidthText.get());
    outputWidthText->setExplicitFocusOrder (2);
    outputWidthText->setMultiLine (false);
    outputWidthText->setReturnKeyStartsNewLine (false);
    outputWidthText->setReadOnly (false);
    outputWidthText->setScrollbarsShown (false);
    outputWidthText->setCaretVisible (false);
    outputWidthText->setPopupMenuEnabled (true);
    outputWidthText->setText (String());

    outputWidthText->setBounds (88, 48, 48, 24);

    outputHeightLabel.reset (new Label ("outputHeightLabel",
                                        TRANS("Height:")));
    addAndMakeVisible (outputHeightLabel.get());
    outputHeightLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputHeightLabel->setJustificationType (Justification::centredLeft);
    outputHeightLabel->setEditable (false, false, false);
    outputHeightLabel->setColour (Label::textColourId, Colours::white);
    outputHeightLabel->setColour (TextEditor::textColourId, Colours::black);
    outputHeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputHeightLabel->setBounds (0, 88, 64, 24);

    outputHeightText.reset (new TextEditor ("outputHeightText"));
    addAndMakeVisible (outputHeightText.get());
    outputHeightText->setExplicitFocusOrder (3);
    outputHeightText->setMultiLine (false);
    outputHeightText->setReturnKeyStartsNewLine (false);
    outputHeightText->setReadOnly (false);
    outputHeightText->setScrollbarsShown (false);
    outputHeightText->setCaretVisible (false);
    outputHeightText->setPopupMenuEnabled (true);
    outputHeightText->setText (String());

    outputHeightText->setBounds (88, 88, 48, 24);

    framerateLabel.reset (new Label ("framerateLabel",
                                     TRANS("FPS:")));
    addAndMakeVisible (framerateLabel.get());
    framerateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    framerateLabel->setJustificationType (Justification::centredLeft);
    framerateLabel->setEditable (false, false, false);
    framerateLabel->setColour (Label::textColourId, Colours::white);
    framerateLabel->setColour (TextEditor::textColourId, Colours::black);
    framerateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    framerateLabel->setBounds (0, 128, 40, 24);

    framerateCombo.reset (new ComboBox ("framerateCombo"));
    addAndMakeVisible (framerateCombo.get());
    framerateCombo->setExplicitFocusOrder (4);
    framerateCombo->setEditableText (false);
    framerateCombo->setJustificationType (Justification::centredLeft);
    framerateCombo->setTextWhenNothingSelected (String());
    framerateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    framerateCombo->addListener (this);

    framerateCombo->setBounds (88, 128, 48, 24);

    bitrateLabel.reset (new Label ("bitrateLabel",
                                   TRANS("Bitrate:")));
    addAndMakeVisible (bitrateLabel.get());
    bitrateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bitrateLabel->setJustificationType (Justification::centredLeft);
    bitrateLabel->setEditable (false, false, false);
    bitrateLabel->setColour (Label::textColourId, Colours::white);
    bitrateLabel->setColour (TextEditor::textColourId, Colours::black);
    bitrateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bitrateLabel->setBounds (0, 168, 64, 24);

    videoBitrateCombo.reset (new ComboBox ("videoBitrateCombo"));
    addAndMakeVisible (videoBitrateCombo.get());
    videoBitrateCombo->setExplicitFocusOrder (5);
    videoBitrateCombo->setEditableText (false);
    videoBitrateCombo->setJustificationType (Justification::centredLeft);
    videoBitrateCombo->setTextWhenNothingSelected (String());
    videoBitrateCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    videoBitrateCombo->addListener (this);

    videoBitrateCombo->setBounds (88, 168, 80, 24);

    outputDestLabel.reset (new Label ("outputDestLabel",
                                      TRANS("Destination:")));
    addAndMakeVisible (outputDestLabel.get());
    outputDestLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputDestLabel->setJustificationType (Justification::centredLeft);
    outputDestLabel->setEditable (false, false, false);
    outputDestLabel->setColour (Label::textColourId, Colours::white);
    outputDestLabel->setColour (TextEditor::textColourId, Colours::black);
    outputDestLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputDestLabel->setBounds (0, 208, 80, 24);

    outputDestText.reset (new TextEditor ("outputDestText"));
    addAndMakeVisible (outputDestText.get());
    outputDestText->setExplicitFocusOrder (6);
    outputDestText->setMultiLine (false);
    outputDestText->setReturnKeyStartsNewLine (false);
    outputDestText->setReadOnly (false);
    outputDestText->setScrollbarsShown (true);
    outputDestText->setCaretVisible (true);
    outputDestText->setPopupMenuEnabled (true);
    outputDestText->setText (String());

    outputDestText->setBounds (88, 208, 408, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigOutput::~ConfigOutput()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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
void ConfigOutput::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigOutput::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigOutput::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == outputSinkCombo.get())
    {
        //[UserComboBoxCode_outputSinkCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_outputSinkCombo]
    }
    else if (comboBoxThatHasChanged == framerateCombo.get())
    {
        //[UserComboBoxCode_framerateCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_framerateCombo]
    }
    else if (comboBoxThatHasChanged == videoBitrateCombo.get())
    {
        //[UserComboBoxCode_videoBitrateCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_videoBitrateCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigOutput" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="outputStreamLabel" id="dac22e20ce0dd8e" memberName="outputStreamLabel"
         virtualName="" explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Stream:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="outputSinkCombo" id="12e0750a2c746a13" memberName="outputSinkCombo"
            virtualName="" explicitFocusOrder="1" pos="88 8 64 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no devices)"/>
  <LABEL name="outputWidthLabel" id="f42b11722ea56a92" memberName="outputWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Width:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputWidthText" id="57d131f0667f6b73" memberName="outputWidthText"
              virtualName="" explicitFocusOrder="2" pos="88 48 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="1"/>
  <LABEL name="outputHeightLabel" id="786372012685b65a" memberName="outputHeightLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputHeightText" id="7e14834485ae7a91" memberName="outputHeightText"
              virtualName="" explicitFocusOrder="3" pos="88 88 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="0" popupmenu="1"/>
  <LABEL name="framerateLabel" id="45b2235a7a1f9614" memberName="framerateLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="FPS:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="framerateCombo" id="2560e172b011e11c" memberName="framerateCombo"
            virtualName="" explicitFocusOrder="4" pos="88 128 48 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="bitrateLabel" id="bc6b3717e710f16c" memberName="bitrateLabel"
         virtualName="" explicitFocusOrder="0" pos="0 168 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bitrate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="videoBitrateCombo" id="54c30dff37473763" memberName="videoBitrateCombo"
            virtualName="" explicitFocusOrder="5" pos="88 168 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="outputDestLabel" id="a1c19ea70cf15d1b" memberName="outputDestLabel"
         virtualName="" explicitFocusOrder="0" pos="0 208 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Destination:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="outputDestText" id="569abe636085fb4a" memberName="outputDestText"
              virtualName="" explicitFocusOrder="6" pos="88 208 408 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

