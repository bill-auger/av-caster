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

#include "Statusbar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Statusbar::Statusbar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Statusbar");
    statusLLabel.reset (new Label ("statusLLabel",
                                   String()));
    addAndMakeVisible (statusLLabel.get());
    statusLLabel->setExplicitFocusOrder (1);
    statusLLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    statusLLabel->setJustificationType (Justification::centredLeft);
    statusLLabel->setEditable (false, false, false);
    statusLLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusLLabel->setColour (Label::textColourId, Colours::grey);
    statusLLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusLLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusLLabel->setBounds (8, 4, 152, 16);

    statusCLabel.reset (new Label ("statusCLabel",
                                   String()));
    addAndMakeVisible (statusCLabel.get());
    statusCLabel->setExplicitFocusOrder (2);
    statusCLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    statusCLabel->setJustificationType (Justification::centred);
    statusCLabel->setEditable (false, false, false);
    statusCLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusCLabel->setColour (Label::textColourId, Colours::grey);
    statusCLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusCLabel->setColour (TextEditor::textColourId, Colours::black);
    statusCLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusRLabel.reset (new Label ("statusRLabel",
                                   String()));
    addAndMakeVisible (statusRLabel.get());
    statusRLabel->setExplicitFocusOrder (3);
    statusRLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    statusRLabel->setJustificationType (Justification::centredRight);
    statusRLabel->setEditable (false, false, false);
    statusRLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    statusRLabel->setColour (Label::textColourId, Colours::grey);
    statusRLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    statusRLabel->setColour (TextEditor::textColourId, Colours::black);
    statusRLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

  setStatusL(String()) ; setStatusC(String()) ; setStatusR(String()) ;

    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Statusbar::~Statusbar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    statusLLabel = nullptr;
    statusCLabel = nullptr;
    statusRLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Statusbar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour = Colour (0xff181818);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 168.0f, y = 4.0f, width = static_cast<float> (getWidth() - 336), height = 16.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = static_cast<float> (getWidth() - 4 - 160), y = 4.0f, width = 160.0f, height = 16.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 4.0f, y = 4.0f, width = 160.0f, height = 16.0f;
        Colour fillColour = Colours::black;
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Statusbar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    statusCLabel->setBounds (172, 4, getWidth() - 342, 16);
    statusRLabel->setBounds (getWidth() - 8 - 152, 4, 152, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Statusbar::setStatusL(String statusText)
{ this->statusLLabel->setText(statusText , juce::dontSendNotification) ; }

void Statusbar::setStatusC(String statusText)
{ this->statusCLabel->setText(statusText , juce::dontSendNotification) ; }

void Statusbar::setStatusR(String statusText)
{ this->statusRLabel->setText(statusText , juce::dontSendNotification) ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Statusbar" componentName="Statusbar"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill="solid: ff181818" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="168 4 336M 16" cornerSize="10.0" fill="solid: ff000000"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4Rr 4 160 16" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <ROUNDRECT pos="4 4 160 16" cornerSize="10.0" fill="solid: ff000000" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <LABEL name="statusLLabel" id="2b89e84fd708c8e0" memberName="statusLLabel"
         virtualName="" explicitFocusOrder="1" pos="8 4 152 16" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="statusCLabel" id="4acd1cc773c3be28" memberName="statusCLabel"
         virtualName="" explicitFocusOrder="2" pos="172 4 342M 16" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="statusRLabel" id="d9ab2c99c74ba401" memberName="statusRLabel"
         virtualName="" explicitFocusOrder="3" pos="8Rr 4 152 16" bkgCol="0"
         textCol="ff808080" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

