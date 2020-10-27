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

#include "ConfigImage.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigImage::ConfigImage ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    locationLabel.reset (new Label ("locationLabel",
                                    TRANS("Location:")));
    addAndMakeVisible (locationLabel.get());
    locationLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    locationLabel->setJustificationType (Justification::centredLeft);
    locationLabel->setEditable (false, false, false);
    locationLabel->setColour (Label::textColourId, Colours::white);
    locationLabel->setColour (TextEditor::textColourId, Colours::black);
    locationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    locationLabel->setBounds (0, 8, 80, 24);

    interstitialText.reset (new TextEditor ("interstitialText"));
    addAndMakeVisible (interstitialText.get());
    interstitialText->setExplicitFocusOrder (1);
    interstitialText->setMultiLine (false);
    interstitialText->setReturnKeyStartsNewLine (false);
    interstitialText->setReadOnly (false);
    interstitialText->setScrollbarsShown (true);
    interstitialText->setCaretVisible (true);
    interstitialText->setPopupMenuEnabled (true);
    interstitialText->setText (String());

    interstitialText->setBounds (88, 8, 312, 24);

    browseButton.reset (new TextButton ("browseButton"));
    addAndMakeVisible (browseButton.get());
    browseButton->setExplicitFocusOrder (2);
    browseButton->setButtonText (TRANS("Browse"));

    browseButton->setBounds (416, 8, 80, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigImage::~ConfigImage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    locationLabel = nullptr;
    interstitialText = nullptr;
    browseButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigImage::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigImage::resized()
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

<JUCER_COMPONENT documentType="Component" className="ConfigImage" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="locationLabel" id="d9e5b9eda1c0b4fe" memberName="locationLabel"
         virtualName="" explicitFocusOrder="0" pos="0 8 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Location:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="interstitialText" id="7634583caff4457b" memberName="interstitialText"
              virtualName="" explicitFocusOrder="1" pos="88 8 312 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="browseButton" id="b593253ef702db73" memberName="browseButton"
              virtualName="" explicitFocusOrder="2" pos="416 8 80 24" buttonText="Browse"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

