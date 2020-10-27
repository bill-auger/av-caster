/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
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

#include "ConfigText.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigText::ConfigText ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    motdLabel.reset (new Label ("motdLabel",
                                TRANS("Message:")));
    addAndMakeVisible (motdLabel.get());
    motdLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    motdLabel->setJustificationType (Justification::centredLeft);
    motdLabel->setEditable (false, false, false);
    motdLabel->setColour (Label::textColourId, Colours::white);
    motdLabel->setColour (TextEditor::textColourId, Colours::black);
    motdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    motdLabel->setBounds (0, 8, 80, 24);

    motdText.reset (new TextEditor ("motdText"));
    addAndMakeVisible (motdText.get());
    motdText->setExplicitFocusOrder (1);
    motdText->setMultiLine (false);
    motdText->setReturnKeyStartsNewLine (false);
    motdText->setReadOnly (false);
    motdText->setScrollbarsShown (true);
    motdText->setCaretVisible (true);
    motdText->setPopupMenuEnabled (true);
    motdText->setText (String());

    motdText->setBounds (88, 8, 284, 24);

    textStyleLabel.reset (new Label ("textStyleLabel",
                                     TRANS("Style:")));
    addAndMakeVisible (textStyleLabel.get());
    textStyleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    textStyleLabel->setJustificationType (Justification::centredLeft);
    textStyleLabel->setEditable (false, false, false);
    textStyleLabel->setColour (Label::textColourId, Colours::white);
    textStyleLabel->setColour (TextEditor::textColourId, Colours::black);
    textStyleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    textStyleLabel->setBounds (0, 48, 52, 24);

    textStyleCombo.reset (new ComboBox ("textStyleCombo"));
    addAndMakeVisible (textStyleCombo.get());
    textStyleCombo->setExplicitFocusOrder (2);
    textStyleCombo->setEditableText (false);
    textStyleCombo->setJustificationType (Justification::centredLeft);
    textStyleCombo->setTextWhenNothingSelected (String());
    textStyleCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textStyleCombo->addListener (this);

    textStyleCombo->setBounds (88, 48, 80, 24);

    textPosLabel.reset (new Label ("textPosLabel",
                                   TRANS("Position:")));
    addAndMakeVisible (textPosLabel.get());
    textPosLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    textPosLabel->setJustificationType (Justification::centredLeft);
    textPosLabel->setEditable (false, false, false);
    textPosLabel->setColour (Label::textColourId, Colours::white);
    textPosLabel->setColour (TextEditor::textColourId, Colours::black);
    textPosLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    textPosLabel->setBounds (0, 88, 64, 24);

    textPosCombo.reset (new ComboBox ("textPosCombo"));
    addAndMakeVisible (textPosCombo.get());
    textPosCombo->setExplicitFocusOrder (3);
    textPosCombo->setEditableText (false);
    textPosCombo->setJustificationType (Justification::centredLeft);
    textPosCombo->setTextWhenNothingSelected (String());
    textPosCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textPosCombo->addListener (this);

    textPosCombo->setBounds (88, 88, 80, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigText::~ConfigText()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    motdLabel = nullptr;
    motdText = nullptr;
    textStyleLabel = nullptr;
    textStyleCombo = nullptr;
    textPosLabel = nullptr;
    textPosCombo = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigText::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigText::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigText::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == textStyleCombo.get())
    {
        //[UserComboBoxCode_textStyleCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_textStyleCombo]
    }
    else if (comboBoxThatHasChanged == textPosCombo.get())
    {
        //[UserComboBoxCode_textPosCombo] -- add your combo box handling code here..

      // NOTE: handled in Config

        //[/UserComboBoxCode_textPosCombo]
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

<JUCER_COMPONENT documentType="Component" className="ConfigText" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="motdLabel" id="e26a158d569b8f" memberName="motdLabel" virtualName=""
         explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Message:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="motdText" id="fb4f8a059431ce61" memberName="motdText" virtualName=""
              explicitFocusOrder="1" pos="88 8 284 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="textStyleLabel" id="3e58deec4ea2f148" memberName="textStyleLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 52 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Style:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textStyleCombo" id="1d3707271064fb55" memberName="textStyleCombo"
            virtualName="" explicitFocusOrder="2" pos="88 48 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="textPosLabel" id="6dd629239c17c38b" memberName="textPosLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Position:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textPosCombo" id="3074c311575e36ac" memberName="textPosCombo"
            virtualName="" explicitFocusOrder="3" pos="88 88 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

