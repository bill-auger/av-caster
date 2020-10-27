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

#include "../Controllers/AvCaster.h"
#include "../Trace/TraceChat.h"

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat (MainContent* main_content)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    chatGroup.reset (new GroupComponent ("chatGroup",
                                         TRANS("Chat")));
    addAndMakeVisible (chatGroup.get());
    chatGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatGroup->setColour (GroupComponent::textColourId, Colours::white);

    chatHistoryGroup.reset (new GroupComponent ("chatHistoryGroup",
                                                String()));
    addAndMakeVisible (chatHistoryGroup.get());
    chatHistoryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatHistoryGroup->setColour (GroupComponent::textColourId, Colours::white);

    chatHistoryText.reset (new TextEditor ("chatHistoryText"));
    addAndMakeVisible (chatHistoryText.get());
    chatHistoryText->setMultiLine (true);
    chatHistoryText->setReturnKeyStartsNewLine (false);
    chatHistoryText->setReadOnly (true);
    chatHistoryText->setScrollbarsShown (true);
    chatHistoryText->setCaretVisible (false);
    chatHistoryText->setPopupMenuEnabled (true);
    chatHistoryText->setColour (TextEditor::textColourId, Colours::white);
    chatHistoryText->setColour (TextEditor::backgroundColourId, Colours::black);
    chatHistoryText->setText (String());

    chatEntryGroup.reset (new GroupComponent ("chatEntryGroup",
                                              String()));
    addAndMakeVisible (chatEntryGroup.get());
    chatEntryGroup->setExplicitFocusOrder (1);
    chatEntryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatEntryGroup->setColour (GroupComponent::textColourId, Colours::white);

    chatEntryText.reset (new TextEditor ("chatEntryText"));
    addAndMakeVisible (chatEntryText.get());
    chatEntryText->setExplicitFocusOrder (2);
    chatEntryText->setMultiLine (false);
    chatEntryText->setReturnKeyStartsNewLine (false);
    chatEntryText->setReadOnly (false);
    chatEntryText->setScrollbarsShown (false);
    chatEntryText->setCaretVisible (true);
    chatEntryText->setPopupMenuEnabled (true);
    chatEntryText->setColour (TextEditor::textColourId, Colours::white);
    chatEntryText->setColour (TextEditor::backgroundColourId, Colour (0xff202020));
    chatEntryText->setText (String());

    chatList.reset (new ChatList());
    addAndMakeVisible (chatList.get());
    chatList->setExplicitFocusOrder (2);
    chatList->setName ("chatList");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  // configure look and feel , validations, and listeners
  TextEditor::Listener* this_text_listener = static_cast<TextEditor::Listener*>(this) ;
  main_content->configureTextEditor(this->chatEntryText.get() , this_text_listener ,
                                    GUI::MAX_MOTD_LEN   , String()           ) ;
  this->chatEntryText->setTextToShowWhenEmpty(GUI::CHAT_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR) ;
  setFontSize() ;

  // defer visibility until connected to some chat channel
  updateVisiblilty(false) ;

    //[/Constructor]
}

Chat::~Chat()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chatGroup = nullptr;
    chatHistoryGroup = nullptr;
    chatHistoryText = nullptr;
    chatEntryGroup = nullptr;
    chatEntryText = nullptr;
    chatList = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Chat::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 20.0f, y = 18.0f, width = static_cast<float> (getWidth() - 40), height = static_cast<float> (getHeight() - 36);
        Colour fillColour = Colour (0xff282828);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 4.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Chat::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    chatGroup->setBounds (16, 8, getWidth() - 32, getHeight() - 24);
    chatHistoryGroup->setBounds (28, 22, getWidth() - 56, getHeight() - 90);
    chatHistoryText->setBounds (32, 32, getWidth() - 64, getHeight() - 104);
    chatEntryGroup->setBounds (28, getHeight() - 68, getWidth() - 56, 38);
    chatEntryText->setBounds (32, getHeight() - 58, getWidth() - 64, 24);
    chatList->setBounds (getWidth() - 160, 32, 128, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Chat public instance methods */

void Chat::updateVisiblilty(bool is_visible)
{
  String group_title = (is_visible) ? GUI::CHAT_GROUP_TITLE : AvCaster::GetVersionString() ;

DEBUG_TRACE_CHAT_VISIBILITY

  const MessageManagerLock mmLock ;
  this->chatGroup       ->setText   (group_title) ;
  this->chatHistoryGroup->setVisible(is_visible) ;
  this->chatHistoryText ->setVisible(is_visible) ;
  this->chatEntryGroup  ->setVisible(is_visible) ;
  this->chatEntryText   ->setVisible(is_visible) ;
  this->chatList        ->setVisible(is_visible) ;
}

#ifndef DISABLE_CHAT
void Chat::addChatLine(String prefix , String nick , String message)
{
  String newline = (this->chatHistoryText->getText().isEmpty()) ? String() : newLine ;
  prefix         = prefix .trim() ;
  nick           = nick   .trim() ;
  message        = message.trim() ;
  prefix         = (prefix.isEmpty()        ) ? String() : prefix + " " ;
  nick           = (nick == GUI::CLIENT_NICK) ? String() : nick   + ": " ;

  const MessageManagerLock mmLock ;
  this->chatHistoryText->moveCaretToEnd() ;
  this->chatHistoryText->insertTextAtCaret(newline + prefix + nick + message) ;
}
#endif // DISABLE_CHAT


/* Chat private instance methods */

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  if (&a_text_editor != this->chatEntryText.get()) return ;

#ifndef DISABLE_CHAT
  AvCaster::SendChat(this->chatEntryText->getText()) ;
#endif // DISABLE_CHAT
  this->chatEntryText->clear() ;
}

void Chat::setFontSize()
{
DEBUG_TRACE_SET_FONTSIZE

  Font current_font  = this->chatHistoryText->getFont() ;
  int  new_font_size = getFontSize() ;
  Font new_font      = current_font.withHeight(new_font_size) ;

  this->chatHistoryText->applyFontToAllText(new_font) ;
  this->chatEntryText  ->applyFontToAllText(new_font) ;

//   resized() ; // TODO: dynamic font size nyi
}


int Chat::getFontSize()
{
//   return GUI::FONT_SIZE ;
  return 16 ;
/* TODO: dynamic font size nyi
  int font_size_n = int(this->fontSize.getValue()) ;
  int font_size_n = int(this->fontSize.getValue()) ;
  int font_size   = GUI::FONT_SIZES[font_size_n].getIntValue() ;

  return font_size ;
*/
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Chat" componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="MainContent* main_content" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="20 18 40M 36M" cornerSize="4.0" fill="solid: ff282828" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="chatGroup" id="6607ba656d5c8919" memberName="chatGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 8 32M 24M" outlinecol="ffffffff"
                  textcol="ffffffff" title="Chat"/>
  <GROUPCOMPONENT name="chatHistoryGroup" id="258cc166964ef054" memberName="chatHistoryGroup"
                  virtualName="" explicitFocusOrder="0" pos="28 22 56M 90M" outlinecol="ffffffff"
                  textcol="ffffffff" title=""/>
  <TEXTEDITOR name="chatHistoryText" id="f98355c5e336ef72" memberName="chatHistoryText"
              virtualName="" explicitFocusOrder="0" pos="32 32 64M 104M" textcol="ffffffff"
              bkgcol="ff000000" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <GROUPCOMPONENT name="chatEntryGroup" id="da473ae049822d5c" memberName="chatEntryGroup"
                  virtualName="" explicitFocusOrder="1" pos="28 68R 56M 38" outlinecol="ffffffff"
                  textcol="ffffffff" title=""/>
  <TEXTEDITOR name="chatEntryText" id="1dd802ce165b4013" memberName="chatEntryText"
              virtualName="" explicitFocusOrder="2" pos="32 58R 64M 24" textcol="ffffffff"
              bkgcol="ff202020" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <GENERICCOMPONENT name="chatList" id="90795555172fbed0" memberName="chatList" virtualName=""
                    explicitFocusOrder="2" pos="160R 32 128 48" class="ChatList"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

