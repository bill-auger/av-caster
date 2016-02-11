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
//[/Headers]

#include "ConfigText.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigText::ConfigText ()
{
    addAndMakeVisible (motdLabel = new Label ("motdLabel",
                                              TRANS("Message:")));
    motdLabel->setFont (Font (15.00f, Font::plain));
    motdLabel->setJustificationType (Justification::centredLeft);
    motdLabel->setEditable (false, false, false);
    motdLabel->setColour (Label::textColourId, Colours::white);
    motdLabel->setColour (TextEditor::textColourId, Colours::black);
    motdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (motdText = new TextEditor ("motdText"));
    motdText->setExplicitFocusOrder (1);
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
    textStyleCombo->setExplicitFocusOrder (2);
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
    textPosCombo->setExplicitFocusOrder (3);
    textPosCombo->setEditableText (false);
    textPosCombo->setJustificationType (Justification::centredLeft);
    textPosCombo->setTextWhenNothingSelected (String::empty);
    textPosCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    textPosCombo->addListener (this);


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

    motdLabel->setBounds (0, 8, 80, 24);
    motdText->setBounds (88, 8, 284, 24);
    textStyleLabel->setBounds (0, 48, 52, 24);
    textStyleCombo->setBounds (88, 48, 80, 24);
    textPosLabel->setBounds (0, 88, 64, 24);
    textPosCombo->setBounds (88, 88, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigText::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == textStyleCombo)
    {
        //[UserComboBoxCode_textStyleCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_textStyleCombo]
    }
    else if (comboBoxThatHasChanged == textPosCombo)
    {
        //[UserComboBoxCode_textPosCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_textPosCombo]
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

<JUCER_COMPONENT documentType="Component" className="ConfigText" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="motdLabel" id="e26a158d569b8f" memberName="motdLabel" virtualName=""
         explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Message:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="motdText" id="fb4f8a059431ce61" memberName="motdText" virtualName=""
              explicitFocusOrder="1" pos="88 8 284 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="textStyleLabel" id="3e58deec4ea2f148" memberName="textStyleLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 52 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Style:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textStyleCombo" id="1d3707271064fb55" memberName="textStyleCombo"
            virtualName="" explicitFocusOrder="2" pos="88 48 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="textPosLabel" id="6dd629239c17c38b" memberName="textPosLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Position:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="textPosCombo" id="3074c311575e36ac" memberName="textPosCombo"
            virtualName="" explicitFocusOrder="3" pos="88 88 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
