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

#include "../Constants/Constants.h"
#include "ChatList.h"

//[/Headers]

#include "ChatListItem.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatListItem::ChatListItem (ValueTree chatter_store)
    : chatterStore(chatter_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    kickButton.reset (new TextButton ("kickButton"));
    addAndMakeVisible (kickButton.get());
    kickButton->setButtonText (TRANS("X"));
    kickButton->addListener (this);
    kickButton->setColour (TextButton::buttonColourId, Colour (0xff400000));
    kickButton->setColour (TextButton::buttonOnColourId, Colours::maroon);
    kickButton->setColour (TextButton::textColourOffId, Colours::red);
    kickButton->setColour (TextButton::textColourOnId, Colours::red);

    kickButton->setBounds (4, 4, 15, 16);

    nickLabel.reset (new Label ("nickLabel",
                                TRANS("(connecting)")));
    addAndMakeVisible (nickLabel.get());
    nickLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nickLabel->setJustificationType (Justification::centredLeft);
    nickLabel->setEditable (false, false, false);
    nickLabel->setColour (Label::textColourId, Colours::white);
    nickLabel->setColour (TextEditor::textColourId, Colours::black);
    nickLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nickLabel->setBounds (24, 4, 72, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (104, 24);


    //[Constructor] You can add your own custom stuff here..

  String user_id = STRING(chatter_store.getType()) ;
  String nick    = STRING(this->chatterStore[CONFIG::NICK_ID]) ;

  setComponentID(user_id) ; setSize(GUI::CHATLIST_ITEM_W , GUI::CHATLIST_ITEM_H) ;
  if (nick.isNotEmpty()) this->nickLabel->setText(nick , juce::dontSendNotification) ;

#ifdef CHATLIST_KICK_BTN_NYI
  kickButton = nullptr ;
#endif // CHATLIST_KICK_BTN_NYI

    //[/Constructor]
}

ChatListItem::~ChatListItem()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

#ifdef CHATLIST_KICK_BTN_NYI
  nickLabel = nullptr ; return ;
#endif // CHATLIST_KICK_BTN_NYI

    //[/Destructor_pre]

    kickButton = nullptr;
    nickLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChatListItem::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 1.0f, y = 1.0f, width = 102.0f, height = 22.0f;
        Colour fillColour = Colour (0xff303030);
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

void ChatListItem::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

#ifdef CHATLIST_KICK_BTN_NYI
  nickLabel->setBounds(4, 4, 92, 16) ;
#endif // CHATLIST_KICK_BTN_NYI

    //[/UserResized]
}

void ChatListItem::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == kickButton.get())
    {
        //[UserButtonCode_kickButton] -- add your button handler code here..

#ifdef CHATLIST_KICK_BTN_NYI
      ;
#endif // CHATLIST_KICK_BTN_NYI

        //[/UserButtonCode_kickButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChatListItem" componentName=""
                 parentClasses="public Component" constructorParams="ValueTree chatter_store"
                 variableInitialisers="chatterStore(chatter_store)" snapPixels="4"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="104" initialHeight="24">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="1 1 102 22" cornerSize="10.0" fill="solid: ff303030" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TEXTBUTTON name="kickButton" id="5ea28eb29c334aeb" memberName="kickButton"
              virtualName="" explicitFocusOrder="0" pos="4 4 15 16" bgColOff="ff400000"
              bgColOn="ff800000" textCol="ffff0000" textColOn="ffff0000" buttonText="X"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="nickLabel" id="4316b113334d5ced" memberName="nickLabel"
         virtualName="" explicitFocusOrder="0" pos="24 4 72 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="(connecting)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

