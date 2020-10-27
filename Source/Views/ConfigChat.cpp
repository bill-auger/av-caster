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

#include "ConfigChat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigChat::ConfigChat ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    timestampToggle.reset (new ToggleButton ("timestampToggle"));
    addAndMakeVisible (timestampToggle.get());
    timestampToggle->setExplicitFocusOrder (6);
    timestampToggle->setButtonText (TRANS("Show Timestamps"));
    timestampToggle->setColour (ToggleButton::textColourId, Colours::white);

    timestampToggle->setBounds (234, 8, 128, 24);

    joinPartToggle.reset (new ToggleButton ("joinPartToggle"));
    addAndMakeVisible (joinPartToggle.get());
    joinPartToggle->setExplicitFocusOrder (7);
    joinPartToggle->setButtonText (TRANS("Show Joins/Parts"));
    joinPartToggle->setToggleState (true, dontSendNotification);
    joinPartToggle->setColour (ToggleButton::textColourId, Colours::white);

    joinPartToggle->setBounds (376, 8, 128, 24);

    networkLabel.reset (new Label ("networkLabel",
                                   TRANS("Host:")));
    addAndMakeVisible (networkLabel.get());
    networkLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    networkLabel->setJustificationType (Justification::centredLeft);
    networkLabel->setEditable (false, false, false);
    networkLabel->setColour (Label::textColourId, Colours::white);
    networkLabel->setColour (TextEditor::textColourId, Colours::black);
    networkLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    networkLabel->setBounds (0, 8, 80, 24);

    portLabel.reset (new Label ("portLabel",
                                TRANS("Port:")));
    addAndMakeVisible (portLabel.get());
    portLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    portLabel->setJustificationType (Justification::centredLeft);
    portLabel->setEditable (false, false, false);
    portLabel->setColour (Label::textColourId, Colours::white);
    portLabel->setColour (TextEditor::textColourId, Colours::black);
    portLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    portLabel->setBounds (0, 48, 40, 24);

    portText.reset (new TextEditor ("portText"));
    addAndMakeVisible (portText.get());
    portText->setExplicitFocusOrder (2);
    portText->setMultiLine (false);
    portText->setReturnKeyStartsNewLine (false);
    portText->setReadOnly (false);
    portText->setScrollbarsShown (true);
    portText->setCaretVisible (true);
    portText->setPopupMenuEnabled (true);
    portText->setText (String());

    portText->setBounds (80, 48, 56, 24);

    nickLabel.reset (new Label ("nickLabel",
                                TRANS("Nick:")));
    addAndMakeVisible (nickLabel.get());
    nickLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nickLabel->setJustificationType (Justification::centredLeft);
    nickLabel->setEditable (false, false, false);
    nickLabel->setColour (Label::textColourId, Colours::white);
    nickLabel->setColour (TextEditor::textColourId, Colours::black);
    nickLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nickLabel->setBounds (0, 88, 40, 24);

    nickText.reset (new TextEditor ("nickText"));
    addAndMakeVisible (nickText.get());
    nickText->setExplicitFocusOrder (3);
    nickText->setMultiLine (false);
    nickText->setReturnKeyStartsNewLine (false);
    nickText->setReadOnly (false);
    nickText->setScrollbarsShown (true);
    nickText->setCaretVisible (true);
    nickText->setPopupMenuEnabled (true);
    nickText->setText (String());

    nickText->setBounds (80, 88, 136, 24);

    passLabel.reset (new Label ("passLabel",
                                TRANS("Password:")));
    addAndMakeVisible (passLabel.get());
    passLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    passLabel->setJustificationType (Justification::centredLeft);
    passLabel->setEditable (false, false, false);
    passLabel->setColour (Label::textColourId, Colours::white);
    passLabel->setColour (TextEditor::textColourId, Colours::black);
    passLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    passLabel->setBounds (0, 128, 72, 24);

    passText.reset (new TextEditor ("passText"));
    addAndMakeVisible (passText.get());
    passText->setExplicitFocusOrder (4);
    passText->setMultiLine (false);
    passText->setReturnKeyStartsNewLine (false);
    passText->setReadOnly (false);
    passText->setScrollbarsShown (true);
    passText->setCaretVisible (true);
    passText->setPopupMenuEnabled (true);
    passText->setText (String());

    passText->setBounds (80, 128, 136, 24);

    channelLabel.reset (new Label ("channelLabel",
                                   TRANS("Channel:")));
    addAndMakeVisible (channelLabel.get());
    channelLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    channelLabel->setJustificationType (Justification::centredLeft);
    channelLabel->setEditable (false, false, false);
    channelLabel->setColour (Label::textColourId, Colours::white);
    channelLabel->setColour (TextEditor::textColourId, Colours::black);
    channelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    channelLabel->setBounds (0, 168, 80, 24);

    channelText.reset (new TextEditor ("channelText"));
    addAndMakeVisible (channelText.get());
    channelText->setExplicitFocusOrder (5);
    channelText->setMultiLine (false);
    channelText->setReturnKeyStartsNewLine (false);
    channelText->setReadOnly (false);
    channelText->setScrollbarsShown (true);
    channelText->setCaretVisible (true);
    channelText->setPopupMenuEnabled (true);
    channelText->setText (String());

    channelText->setBounds (80, 168, 136, 24);

    greetingLabel.reset (new Label ("greetingLabel",
                                    TRANS("Greeting:")));
    addAndMakeVisible (greetingLabel.get());
    greetingLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    greetingLabel->setJustificationType (Justification::centredLeft);
    greetingLabel->setEditable (false, false, false);
    greetingLabel->setColour (Label::textColourId, Colours::white);
    greetingLabel->setColour (TextEditor::textColourId, Colours::black);
    greetingLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    greetingLabel->setBounds (234, 48, 72, 24);

    greetingText.reset (new TextEditor ("greetingText"));
    addAndMakeVisible (greetingText.get());
    greetingText->setExplicitFocusOrder (8);
    greetingText->setMultiLine (true);
    greetingText->setReturnKeyStartsNewLine (true);
    greetingText->setReadOnly (false);
    greetingText->setScrollbarsShown (true);
    greetingText->setCaretVisible (true);
    greetingText->setPopupMenuEnabled (true);
    greetingText->setText (String());

    greetingText->setBounds (234, 72, 270, 120);

    networkText.reset (new TextEditor ("networkText"));
    addAndMakeVisible (networkText.get());
    networkText->setExplicitFocusOrder (1);
    networkText->setMultiLine (false);
    networkText->setReturnKeyStartsNewLine (false);
    networkText->setReadOnly (false);
    networkText->setScrollbarsShown (true);
    networkText->setCaretVisible (true);
    networkText->setPopupMenuEnabled (true);
    networkText->setText (String());

    networkText->setBounds (80, 8, 136, 24);


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

    timestampToggle = nullptr;
    joinPartToggle = nullptr;
    networkLabel = nullptr;
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
    networkText = nullptr;


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

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigChat" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <TOGGLEBUTTON name="timestampToggle" id="1ec45429906b24f5" memberName="timestampToggle"
                virtualName="" explicitFocusOrder="6" pos="234 8 128 24" txtcol="ffffffff"
                buttonText="Show Timestamps" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="joinPartToggle" id="b365bf54ac5a17da" memberName="joinPartToggle"
                virtualName="" explicitFocusOrder="7" pos="376 8 128 24" txtcol="ffffffff"
                buttonText="Show Joins/Parts" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="1"/>
  <LABEL name="networkLabel" id="17d2e75add77ef88" memberName="networkLabel"
         virtualName="" explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Host:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="portLabel" id="c9766d1550ca03d" memberName="portLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Port:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="portText" id="884822c04a8baf5b" memberName="portText" virtualName=""
              explicitFocusOrder="2" pos="80 48 56 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="nickLabel" id="2762611946169823" memberName="nickLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Nick:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="nickText" id="33c730fea5d389aa" memberName="nickText" virtualName=""
              explicitFocusOrder="3" pos="80 88 136 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="passLabel" id="f5de0cc5921d9a6a" memberName="passLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Password:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="passText" id="af6a1e14762cfebf" memberName="passText" virtualName=""
              explicitFocusOrder="4" pos="80 128 136 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="channelLabel" id="64c9a775a77af61c" memberName="channelLabel"
         virtualName="" explicitFocusOrder="0" pos="0 168 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Channel:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="channelText" id="ca5aa4f4a77b4469" memberName="channelText"
              virtualName="" explicitFocusOrder="5" pos="80 168 136 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="greetingLabel" id="460772215644ef5" memberName="greetingLabel"
         virtualName="" explicitFocusOrder="0" pos="234 48 72 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Greeting:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="greetingText" id="7d47de6dcee921f5" memberName="greetingText"
              virtualName="" explicitFocusOrder="8" pos="234 72 270 120" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="networkText" id="a4f0c88c1e1ddb44" memberName="networkText"
              virtualName="" explicitFocusOrder="1" pos="80 8 136 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

