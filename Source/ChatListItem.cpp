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

#include "Constants.h"
#include "ChatList.h"

//[/Headers]

#include "ChatListItem.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatListItem::ChatListItem (ValueTree chatter_store)
    : chatterStore(chatter_store)
{
    addAndMakeVisible (banButton = new TextButton ("banButton"));
    banButton->setButtonText (TRANS("X"));
    banButton->addListener (this);
    banButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    banButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    banButton->setColour (TextButton::textColourOnId, Colours::red);
    banButton->setColour (TextButton::textColourOffId, Colours::red);

    addAndMakeVisible (nickLabel = new Label ("nickLabel",
                                              String::empty));
    nickLabel->setFont (Font (15.00f, Font::plain));
    nickLabel->setJustificationType (Justification::centredLeft);
    nickLabel->setEditable (false, false, false);
    nickLabel->setColour (Label::textColourId, Colours::white);
    nickLabel->setColour (TextEditor::textColourId, Colours::black);
    nickLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  String nick = STRING(this->chatterStore[CONFIG::CHAT_NICK_ID]) ;

  nickLabel->setText(nick , juce::dontSendNotification) ;

    //[/Constructor]
}

ChatListItem::~ChatListItem()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    banButton = nullptr;
    nickLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChatListItem::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff282828));
    g.fillRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 10.000f);

    g.setColour (Colours::white);
    g.drawRoundedRectangle (1.0f, 1.0f, static_cast<float> (getWidth() - 2), static_cast<float> (getHeight() - 2), 10.000f, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChatListItem::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    banButton->setBounds (4, 4, 15, 16);
    nickLabel->setBounds (24, 4, getWidth() - 32, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ChatListItem::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == banButton)
    {
        //[UserButtonCode_banButton] -- add your button handler code here..
        //[/UserButtonCode_banButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChatListItem" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree chatter_store"
                 variableInitialisers="chatterStore(chatter_store)" snapPixels="4"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="1 1 2M 2M" cornerSize="10" fill="solid: ff282828" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TEXTBUTTON name="banButton" id="5ea28eb29c334aeb" memberName="banButton"
              virtualName="" explicitFocusOrder="0" pos="4 4 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="nickLabel" id="4316b113334d5ced" memberName="nickLabel"
         virtualName="" explicitFocusOrder="0" pos="24 4 1M 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
