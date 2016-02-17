/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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
//[/Headers]

#include "ConfigChat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigChat::ConfigChat ()
{
    addAndMakeVisible (serverButton = new TextButton ("serverButton"));
    serverButton->setExplicitFocusOrder (1);
    serverButton->setButtonText (TRANS("Add Server"));

    addAndMakeVisible (hostLabel = new Label ("hostLabel",
                                              TRANS("Host:")));
    hostLabel->setFont (Font (15.00f, Font::plain));
    hostLabel->setJustificationType (Justification::centredLeft);
    hostLabel->setEditable (false, false, false);
    hostLabel->setColour (Label::textColourId, Colours::white);
    hostLabel->setColour (TextEditor::textColourId, Colours::black);
    hostLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hostCombo = new ComboBox ("hostCombo"));
    hostCombo->setExplicitFocusOrder (2);
    hostCombo->setEditableText (true);
    hostCombo->setJustificationType (Justification::centredLeft);
    hostCombo->setTextWhenNothingSelected (TRANS("(enter hostname)"));
    hostCombo->setTextWhenNoChoicesAvailable (String::empty);
    hostCombo->addListener (this);

    addAndMakeVisible (portLabel = new Label ("portLabel",
                                              TRANS("Port:")));
    portLabel->setFont (Font (15.00f, Font::plain));
    portLabel->setJustificationType (Justification::centredLeft);
    portLabel->setEditable (false, false, false);
    portLabel->setColour (Label::textColourId, Colours::white);
    portLabel->setColour (TextEditor::textColourId, Colours::black);
    portLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (portText = new TextEditor ("portText"));
    portText->setExplicitFocusOrder (3);
    portText->setMultiLine (false);
    portText->setReturnKeyStartsNewLine (false);
    portText->setReadOnly (false);
    portText->setScrollbarsShown (true);
    portText->setCaretVisible (true);
    portText->setPopupMenuEnabled (true);
    portText->setText (String::empty);

    addAndMakeVisible (nickLabel = new Label ("nickLabel",
                                              TRANS("Nick:")));
    nickLabel->setFont (Font (15.00f, Font::plain));
    nickLabel->setJustificationType (Justification::centredLeft);
    nickLabel->setEditable (false, false, false);
    nickLabel->setColour (Label::textColourId, Colours::white);
    nickLabel->setColour (TextEditor::textColourId, Colours::black);
    nickLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nickText = new TextEditor ("nickText"));
    nickText->setExplicitFocusOrder (4);
    nickText->setMultiLine (false);
    nickText->setReturnKeyStartsNewLine (false);
    nickText->setReadOnly (false);
    nickText->setScrollbarsShown (true);
    nickText->setCaretVisible (true);
    nickText->setPopupMenuEnabled (true);
    nickText->setText (String::empty);

    addAndMakeVisible (passLabel = new Label ("passLabel",
                                              TRANS("Password:")));
    passLabel->setFont (Font (15.00f, Font::plain));
    passLabel->setJustificationType (Justification::centredLeft);
    passLabel->setEditable (false, false, false);
    passLabel->setColour (Label::textColourId, Colours::white);
    passLabel->setColour (TextEditor::textColourId, Colours::black);
    passLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (passText = new TextEditor ("passText"));
    passText->setExplicitFocusOrder (5);
    passText->setMultiLine (false);
    passText->setReturnKeyStartsNewLine (false);
    passText->setReadOnly (false);
    passText->setScrollbarsShown (true);
    passText->setCaretVisible (true);
    passText->setPopupMenuEnabled (true);
    passText->setText (String::empty);

    addAndMakeVisible (channelLabel = new Label ("channelLabel",
                                                 TRANS("Channel:")));
    channelLabel->setFont (Font (15.00f, Font::plain));
    channelLabel->setJustificationType (Justification::centredLeft);
    channelLabel->setEditable (false, false, false);
    channelLabel->setColour (Label::textColourId, Colours::white);
    channelLabel->setColour (TextEditor::textColourId, Colours::black);
    channelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (channelText = new TextEditor ("channelText"));
    channelText->setExplicitFocusOrder (6);
    channelText->setMultiLine (false);
    channelText->setReturnKeyStartsNewLine (false);
    channelText->setReadOnly (false);
    channelText->setScrollbarsShown (true);
    channelText->setCaretVisible (true);
    channelText->setPopupMenuEnabled (true);
    channelText->setText (String::empty);

    addAndMakeVisible (greetingLabel = new Label ("greetingLabel",
                                                  TRANS("Greeting:")));
    greetingLabel->setFont (Font (15.00f, Font::plain));
    greetingLabel->setJustificationType (Justification::centredLeft);
    greetingLabel->setEditable (false, false, false);
    greetingLabel->setColour (Label::textColourId, Colours::white);
    greetingLabel->setColour (TextEditor::textColourId, Colours::black);
    greetingLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (greetingText = new TextEditor ("greetingText"));
    greetingText->setExplicitFocusOrder (7);
    greetingText->setMultiLine (false);
    greetingText->setReturnKeyStartsNewLine (false);
    greetingText->setReadOnly (false);
    greetingText->setScrollbarsShown (true);
    greetingText->setCaretVisible (true);
    greetingText->setPopupMenuEnabled (true);
    greetingText->setText (String::empty);

    addAndMakeVisible (joinPartToggle = new ToggleButton ("joinPartToggle"));
    joinPartToggle->setExplicitFocusOrder (8);
    joinPartToggle->setButtonText (TRANS("Show Join/Part"));
    joinPartToggle->setToggleState (true, dontSendNotification);
    joinPartToggle->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigChat::~ConfigChat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    serverButton = nullptr;
    hostLabel = nullptr;
    hostCombo = nullptr;
    portLabel = nullptr;
    portText = nullptr;
    nickLabel = nullptr;
    nickText = nullptr;
    passLabel = nullptr;
    passText = nullptr;
    channelLabel = nullptr;
    channelText = nullptr;
    greetingLabel = nullptr;
    greetingText = nullptr;
    joinPartToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigChat::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigChat::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    serverButton->setBounds (0, 8, 96, 24);
    hostLabel->setBounds (0, 48, 80, 24);
    hostCombo->setBounds (88, 48, 128, 24);
    portLabel->setBounds (0, 88, 40, 24);
    portText->setBounds (88, 88, 48, 24);
    nickLabel->setBounds (0, 128, 40, 24);
    nickText->setBounds (88, 128, 128, 24);
    passLabel->setBounds (0, 168, 72, 24);
    passText->setBounds (88, 168, 128, 24);
    channelLabel->setBounds (0, 208, 80, 24);
    channelText->setBounds (88, 208, 128, 24);
    greetingLabel->setBounds (234, 8, 72, 24);
    greetingText->setBounds (234, 32, 270, 208);
    joinPartToggle->setBounds (392, 8, 112, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigChat::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == hostCombo)
    {
        //[UserComboBoxCode_hostCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_hostCombo]
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

<JUCER_COMPONENT documentType="Component" className="ConfigChat" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <TEXTBUTTON name="serverButton" id="2728ddd5e468423a" memberName="serverButton"
              virtualName="" explicitFocusOrder="1" pos="0 8 96 24" buttonText="Add Server"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <LABEL name="hostLabel" id="17d2e75add77ef88" memberName="hostLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Host:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="hostCombo" id="5d47d4124d2dffbb" memberName="hostCombo"
            virtualName="" explicitFocusOrder="2" pos="88 48 128 24" editable="1"
            layout="33" items="" textWhenNonSelected="(enter hostname)" textWhenNoItems=""/>
  <LABEL name="portLabel" id="c9766d1550ca03d" memberName="portLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Port:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="portText" id="884822c04a8baf5b" memberName="portText" virtualName=""
              explicitFocusOrder="3" pos="88 88 48 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="nickLabel" id="2762611946169823" memberName="nickLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Nick:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="nickText" id="33c730fea5d389aa" memberName="nickText" virtualName=""
              explicitFocusOrder="4" pos="88 128 128 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="passLabel" id="f5de0cc5921d9a6a" memberName="passLabel"
         virtualName="" explicitFocusOrder="0" pos="0 168 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Password:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="passText" id="af6a1e14762cfebf" memberName="passText" virtualName=""
              explicitFocusOrder="5" pos="88 168 128 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="channelLabel" id="64c9a775a77af61c" memberName="channelLabel"
         virtualName="" explicitFocusOrder="0" pos="0 208 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Channel:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="channelText" id="ca5aa4f4a77b4469" memberName="channelText"
              virtualName="" explicitFocusOrder="6" pos="88 208 128 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="greetingLabel" id="460772215644ef5" memberName="greetingLabel"
         virtualName="" explicitFocusOrder="0" pos="234 8 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Greeting:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="greetingText" id="7d47de6dcee921f5" memberName="greetingText"
              virtualName="" explicitFocusOrder="7" pos="234 32 270 208" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="joinPartToggle" id="b365bf54ac5a17da" memberName="joinPartToggle"
                virtualName="" explicitFocusOrder="8" pos="392 8 112 24" txtcol="ffffffff"
                buttonText="Show Join/Part" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
