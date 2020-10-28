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

#include "ConfigScreen.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigScreen::ConfigScreen ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    displayLabel.reset (new Label ("displayLabel",
                                   TRANS("Display #:")));
    addAndMakeVisible (displayLabel.get());
    displayLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    displayLabel->setJustificationType (Justification::centredLeft);
    displayLabel->setEditable (false, false, false);
    displayLabel->setColour (Label::textColourId, Colours::white);
    displayLabel->setColour (TextEditor::textColourId, Colours::black);
    displayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    displayLabel->setBounds (0, 8, 80, 24);

    displaySlider.reset (new Slider ("displaySlider"));
    addAndMakeVisible (displaySlider.get());
    displaySlider->setExplicitFocusOrder (1);
    displaySlider->setRange (0, 10, 0);
    displaySlider->setSliderStyle (Slider::IncDecButtons);
    displaySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    displaySlider->addListener (this);

    displaySlider->setBounds (88, 8, 64, 24);

    screenLabel.reset (new Label ("screenLabel",
                                  TRANS("Screen #:")));
    addAndMakeVisible (screenLabel.get());
    screenLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    screenLabel->setJustificationType (Justification::centredLeft);
    screenLabel->setEditable (false, false, false);
    screenLabel->setColour (Label::textColourId, Colours::white);
    screenLabel->setColour (TextEditor::textColourId, Colours::black);
    screenLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    screenLabel->setBounds (0, 48, 80, 24);

    screenSlider.reset (new Slider ("screenSlider"));
    addAndMakeVisible (screenSlider.get());
    screenSlider->setExplicitFocusOrder (2);
    screenSlider->setRange (0, 10, 0);
    screenSlider->setSliderStyle (Slider::IncDecButtons);
    screenSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 24, 20);
    screenSlider->addListener (this);

    screenSlider->setBounds (88, 48, 64, 24);

    screenWidthLabel.reset (new Label ("screenWidthLabel",
                                       TRANS("Width:")));
    addAndMakeVisible (screenWidthLabel.get());
    screenWidthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    screenWidthLabel->setJustificationType (Justification::centredLeft);
    screenWidthLabel->setEditable (false, false, false);
    screenWidthLabel->setColour (Label::textColourId, Colours::white);
    screenWidthLabel->setColour (TextEditor::textColourId, Colours::black);
    screenWidthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    screenWidthLabel->setBounds (0, 88, 64, 24);

    screenWidthText.reset (new TextEditor ("screenWidthText"));
    addAndMakeVisible (screenWidthText.get());
    screenWidthText->setExplicitFocusOrder (3);
    screenWidthText->setMultiLine (false);
    screenWidthText->setReturnKeyStartsNewLine (false);
    screenWidthText->setReadOnly (false);
    screenWidthText->setScrollbarsShown (false);
    screenWidthText->setCaretVisible (true);
    screenWidthText->setPopupMenuEnabled (true);
    screenWidthText->setText (String());

    screenWidthText->setBounds (88, 88, 48, 24);

    screenHeightLabel.reset (new Label ("screenHeightLabel",
                                        TRANS("Height:")));
    addAndMakeVisible (screenHeightLabel.get());
    screenHeightLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    screenHeightLabel->setJustificationType (Justification::centredLeft);
    screenHeightLabel->setEditable (false, false, false);
    screenHeightLabel->setColour (Label::textColourId, Colours::white);
    screenHeightLabel->setColour (TextEditor::textColourId, Colours::black);
    screenHeightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    screenHeightLabel->setBounds (0, 128, 64, 24);

    screenHeightText.reset (new TextEditor ("screenHeightText"));
    addAndMakeVisible (screenHeightText.get());
    screenHeightText->setExplicitFocusOrder (4);
    screenHeightText->setMultiLine (false);
    screenHeightText->setReturnKeyStartsNewLine (false);
    screenHeightText->setReadOnly (false);
    screenHeightText->setScrollbarsShown (false);
    screenHeightText->setCaretVisible (true);
    screenHeightText->setPopupMenuEnabled (true);
    screenHeightText->setText (String());

    screenHeightText->setBounds (88, 128, 48, 24);

    xOffsetLabel.reset (new Label ("xOffsetLabel",
                                   TRANS("Offset X:")));
    addAndMakeVisible (xOffsetLabel.get());
    xOffsetLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    xOffsetLabel->setJustificationType (Justification::centredLeft);
    xOffsetLabel->setEditable (false, false, false);
    xOffsetLabel->setColour (Label::textColourId, Colours::white);
    xOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    xOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    xOffsetLabel->setBounds (0, 168, 64, 24);

    xOffsetText.reset (new TextEditor ("xOffsetText"));
    addAndMakeVisible (xOffsetText.get());
    xOffsetText->setExplicitFocusOrder (5);
    xOffsetText->setMultiLine (false);
    xOffsetText->setReturnKeyStartsNewLine (false);
    xOffsetText->setReadOnly (false);
    xOffsetText->setScrollbarsShown (true);
    xOffsetText->setCaretVisible (true);
    xOffsetText->setPopupMenuEnabled (true);
    xOffsetText->setText (String());

    xOffsetText->setBounds (88, 168, 48, 24);

    yOffsetLabel.reset (new Label ("yOffsetLabel",
                                   TRANS("Offset Y:")));
    addAndMakeVisible (yOffsetLabel.get());
    yOffsetLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    yOffsetLabel->setJustificationType (Justification::centredLeft);
    yOffsetLabel->setEditable (false, false, false);
    yOffsetLabel->setColour (Label::textColourId, Colours::white);
    yOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    yOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    yOffsetLabel->setBounds (0, 208, 64, 24);

    yOffsetText.reset (new TextEditor ("yOffsetText"));
    addAndMakeVisible (yOffsetText.get());
    yOffsetText->setExplicitFocusOrder (6);
    yOffsetText->setMultiLine (false);
    yOffsetText->setReturnKeyStartsNewLine (false);
    yOffsetText->setReadOnly (false);
    yOffsetText->setScrollbarsShown (true);
    yOffsetText->setCaretVisible (true);
    yOffsetText->setPopupMenuEnabled (true);
    yOffsetText->setText (String());

    yOffsetText->setBounds (88, 208, 48, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigScreen::~ConfigScreen()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigScreen::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigScreen::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigScreen::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == displaySlider.get())
    {
        //[UserSliderCode_displaySlider] -- add your slider handling code here..

      // NOTE: handled in Config

        //[/UserSliderCode_displaySlider]
    }
    else if (sliderThatWasMoved == screenSlider.get())
    {
        //[UserSliderCode_screenSlider] -- add your slider handling code here..

      // NOTE: handled in Config

        //[/UserSliderCode_screenSlider]
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

<JUCER_COMPONENT documentType="Component" className="ConfigScreen" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="displayLabel" id="47dccaa09248b15c" memberName="displayLabel"
         virtualName="" explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Display #:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="displaySlider" id="2250b6248ed28fc6" memberName="displaySlider"
          virtualName="" explicitFocusOrder="1" pos="88 8 64 24" min="0.0"
          max="10.0" int="0.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="screenLabel" id="68a950dbc12277f7" memberName="screenLabel"
         virtualName="" explicitFocusOrder="0" pos="0 48 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Screen #:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="screenSlider" id="74df429060e256ad" memberName="screenSlider"
          virtualName="" explicitFocusOrder="2" pos="88 48 64 24" min="0.0"
          max="10.0" int="0.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="24" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="screenWidthLabel" id="1a8ebe15d549d3a2" memberName="screenWidthLabel"
         virtualName="" explicitFocusOrder="0" pos="0 88 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Width:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="screenWidthText" id="179a2a3eef834bff" memberName="screenWidthText"
              virtualName="" explicitFocusOrder="3" pos="88 88 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="screenHeightLabel" id="778bbd3e6ce86ce2" memberName="screenHeightLabel"
         virtualName="" explicitFocusOrder="0" pos="0 128 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Height:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="screenHeightText" id="fabfd798833e0222" memberName="screenHeightText"
              virtualName="" explicitFocusOrder="4" pos="88 128 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <LABEL name="xOffsetLabel" id="fca78bd84d691a86" memberName="xOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="0 168 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Offset X:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="xOffsetText" id="a370562e4f63e34" memberName="xOffsetText"
              virtualName="" explicitFocusOrder="5" pos="88 168 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="yOffsetLabel" id="f2efae168df49c68" memberName="yOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="0 208 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Offset Y:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="yOffsetText" id="e4bb3613f81dc5f4" memberName="yOffsetText"
              virtualName="" explicitFocusOrder="6" pos="88 208 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

