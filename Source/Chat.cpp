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

#include "AvCaster.h"
#include "Trace/TraceChat.h"

//[/Headers]

#include "Chat.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Chat::Chat ()
{
    addAndMakeVisible (chatGroup = new GroupComponent ("chatGroup",
                                                       TRANS("Chat")));
    chatGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatHistoryGroup = new GroupComponent ("chatHistoryGroup",
                                                              String::empty));
    chatHistoryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatHistoryGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatHistoryText = new TextEditor ("chatHistoryText"));
    chatHistoryText->setMultiLine (true);
    chatHistoryText->setReturnKeyStartsNewLine (false);
    chatHistoryText->setReadOnly (true);
    chatHistoryText->setScrollbarsShown (true);
    chatHistoryText->setCaretVisible (false);
    chatHistoryText->setPopupMenuEnabled (true);
    chatHistoryText->setColour (TextEditor::textColourId, Colours::white);
    chatHistoryText->setColour (TextEditor::backgroundColourId, Colours::black);
    chatHistoryText->setText (String::empty);

    addAndMakeVisible (chatEntryGroup = new GroupComponent ("chatEntryGroup",
                                                            String::empty));
    chatEntryGroup->setExplicitFocusOrder (1);
    chatEntryGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chatEntryGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (chatEntryText = new TextEditor ("chatEntryText"));
    chatEntryText->setExplicitFocusOrder (2);
    chatEntryText->setMultiLine (false);
    chatEntryText->setReturnKeyStartsNewLine (false);
    chatEntryText->setReadOnly (false);
    chatEntryText->setScrollbarsShown (false);
    chatEntryText->setCaretVisible (true);
    chatEntryText->setPopupMenuEnabled (true);
    chatEntryText->setColour (TextEditor::textColourId, Colours::white);
    chatEntryText->setColour (TextEditor::backgroundColourId, Colour (0xff202020));
    chatEntryText->setText (String::empty);

    addAndMakeVisible (dummyChatList = new ChatList (ValueTree::invalid));
    dummyChatList->setExplicitFocusOrder (2);
    dummyChatList->setName ("dummyChatList");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  // defer visibility until connected to some chat channel
  updateVisiblilty() ;

  // text editor colors
  this->chatEntryText  ->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->chatHistoryText->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatEntryText  ->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->chatHistoryText->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::outlineColourId         , GUI::TEXT_BG_COLOR      ) ;
  this->chatEntryText  ->setColour(TextEditor::outlineColourId         , GUI::TEXT_BG_COLOR      ) ;
  this->chatHistoryText->setColour(TextEditor::focusedOutlineColourId  , GUI::TEXT_FOCUS_COLOR   ) ;
  this->chatEntryText  ->setColour(TextEditor::focusedOutlineColourId  , GUI::TEXT_FOCUS_COLOR   ) ;
  this->chatHistoryText->setColour(TextEditor::shadowColourId          , GUI::TEXT_SHADOW_COLOR  ) ;
  this->chatEntryText  ->setColour(TextEditor::shadowColourId          , GUI::TEXT_SHADOW_COLOR  ) ;
  this->chatHistoryText->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;
  this->chatEntryText  ->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;

  // text editor behaviors
  this->chatEntryText->setSelectAllWhenFocused(true) ;
  this->chatEntryText->setTextToShowWhenEmpty(GUI::CHAT_PROMPT_TEXT , GUI::TEXT_EMPTY_COLOR) ;
  this->chatEntryText->setInputRestrictions(1024) ;

  // hide GUI designer placeholder
  this->dummyChatList->setVisible(false) ;

  // register interest in outgoing chat text
  this->chatEntryText->addListener(this) ;

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
    dummyChatList = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Chat::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff303030));
    g.fillRoundedRectangle (20.0f, 18.0f, static_cast<float> (getWidth() - 40), static_cast<float> (getHeight() - 36), 4.000f);

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
    dummyChatList->setBounds (getWidth() - 160, 32, 128, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Chat public instance methods */

void Chat::updateVisiblilty()
{
  int n_chatters = 0 ; int n_servers = this->serversStore.getNumChildren() ;
  for (int server_n = 0 ; server_n < n_servers ; ++server_n)
  {
    ValueTree server   = this->serversStore.getChild(server_n) ;
    ValueTree chatters = server.getChildWithName(CONFIG::CHATTERS_ID) ;
    n_chatters        += chatters.getNumChildren() ;
  }

  bool   is_visible  = n_chatters > 0 ;
  String group_title = (is_visible) ? GUI::CHAT_GROUP_TITLE : AvCaster::GetVersionString() ;

DEBUG_TRACE_CHAT_VISIBILITY

  this->chatGroup       ->setText   (group_title) ;
  this->chatHistoryGroup->setVisible(is_visible) ;
  this->chatHistoryText ->setVisible(is_visible) ;
  this->chatEntryGroup  ->setVisible(is_visible) ;
  this->chatEntryText   ->setVisible(is_visible) ;
  for (int server_n = 0 ; server_n < this->chatLists.size() ; ++server_n)
    this->chatLists[server_n]->setVisible(is_visible) ;
}

void Chat::refresh()
{
  updateVisiblilty() ;

 // calculate total height
  int server_n = this->chatLists.size() ; int lists_h = GUI::CHATLIST_Y ;
  while (server_n--) lists_h += this->chatLists[server_n]->getHeight() + GUI::PAD ;

  bool is_scrollbar_visible = lists_h > getHeight() ;
  int  list_x_offset        = (is_scrollbar_visible)? GUI::OFFSET_CHATLIST_X : GUI::CHATLIST_X ;
  int  list_x               = getWidth() - list_x_offset ;
  int  list_y               = GUI::CHATLIST_Y ;

  // arrange lists
  for (int server_n = 0 ; server_n < this->chatLists.size() ; ++server_n)
  {
    ChatList* chatList = this->chatLists[server_n] ;

    chatList->setTopLeftPosition(list_x , list_y) ;

    list_y += chatList->getHeight() ;
  }
}

void Chat::addChatLine(String prefix , String nick , String message_text)
{
  String message_header = prefix + ((nick == GUI::CLIENT_NICK) ? "" : nick + ": ") ;

  const MessageManagerLock mmLock ;
  this->chatHistoryText->moveCaretToEnd() ;
  this->chatHistoryText->insertTextAtCaret("\n" + message_header + message_text) ;
}


/* Chat private instance methods */

void Chat::textEditorReturnKeyPressed(TextEditor& a_text_editor)
{
  if (&a_text_editor != this->chatEntryText) return ;

  AvCaster::SendChat(this->chatEntryText->getText()) ;
  this->chatEntryText->clear() ;
}

void Chat::valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_node)
{
  if (isServersNode(a_parent_node , a_node)) createChatList(a_node) ;
}

void Chat::valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_node)
{
  if (isServersNode(a_parent_node , a_node)) destroyChatList(String(a_node.getType())) ;
}

void Chat::initialize(ValueTree servers_store)
{
  this->serversStore = servers_store ; this->serversStore.addListener(this) ;

  for (int server_n = 0 ; server_n < servers_store.getNumChildren() ; ++server_n)
    createChatList(this->serversStore.getChild(server_n)) ;
}

void Chat::createChatList(ValueTree server_store)
{
  ValueTree chatters_store = server_store.getChildWithName(CONFIG::CHATTERS_ID) ;

  String    server_id = String(server_store.getType()) ;
  ChatList* chat_list = new ChatList(chatters_store) ;

  chat_list->setComponentID(server_id) ; addAndMakeVisible(chat_list) ;
  this->chatLists.add(chat_list) ;

  refresh() ;
}

void Chat::destroyChatList(String server_id)
{
  for (int server_n = 0 ; server_n < this->chatLists.size() ; ++server_n)
  {
    ChatList* chatlist = this->chatLists[server_n] ;
    if (chatlist->getComponentID() == server_id) this->chatLists.removeObject(chatlist) ;
  }

  refresh() ;
}

bool Chat::isServersNode(ValueTree& a_parent_node , ValueTree& a_node)
{
  return a_parent_node.getType() == CONFIG::SERVERS_ID ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Chat" componentName="" parentClasses="public Component, public TextEditor::Listener, public ValueTree::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="1"
                 initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="20 18 40M 36M" cornerSize="4" fill="solid: ff303030" hasStroke="0"/>
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
  <GENERICCOMPONENT name="dummyChatList" id="90795555172fbed0" memberName="dummyChatList"
                    virtualName="" explicitFocusOrder="2" pos="160R 32 128 48" class="ChatList"
                    params="ValueTree::invalid"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
