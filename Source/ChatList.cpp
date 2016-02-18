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

#include "AvCaster.h"
#include "Trace/TraceChat.h"

//[/Headers]

#include "ChatList.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatList::ChatList (ValueTree network_store)
    : networkStore(network_store)
{
    addAndMakeVisible (chattersGroup = new GroupComponent ("chattersGroup",
                                                           TRANS("(connecting)")));
    chattersGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    chattersGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (dummyChatListItem = new ChatListItem (ValueTree::invalid));
    dummyChatListItem->setName ("dummyChatListItem");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (128, 48);


    //[Constructor] You can add your own custom stuff here..

  this->chattersStore = this->networkStore.getChildWithName(CONFIG::CHATTERS_ID) ;
  String network      = STRING(this->networkStore[CONFIG::NETWORK_ID]) ;

  this->chattersGroup->setText(network) ;
  this->chattersGroup->setTextLabelPosition(Justification::horizontallyCentred) ;

  // hide GUI designer placeholder
  this->dummyChatListItem->setVisible(false) ;

  // register interest in join/parts
  this->networkStore.addListener(this) ;

    //[/Constructor]
}

ChatList::~ChatList()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    chattersGroup = nullptr;
    dummyChatListItem = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

  this->chatListItems.clear() ;

    //[/Destructor]
}

//==============================================================================
void ChatList::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff202020));
    g.fillRoundedRectangle (4.0f, 10.0f, 120.0f, 34.0f, 4.000f);

    //[UserPaint] Add your own custom painting code here..

  g.fillRoundedRectangle(4.0f , 10.0f , getWidth() - 8.0f , getHeight() - 14.0f , 4.000f) ;

    //[/UserPaint]
}

void ChatList::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    chattersGroup->setBounds (0, 0, 128, 48);
    dummyChatListItem->setBounds (12, 16, 104, 24);
    //[UserResized] Add your own custom resize handling here..

  this->chattersGroup->setSize(getWidth() , getHeight()) ;

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ChatList::valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_node)
{
  if (a_parent_node != this->chattersStore) return ;

  ValueTree     chatter_store  = a_node ;
  int           item_idx       = sortedChatterIdx(chatter_store) + GUI::N_STATIC_CHATLIST_CHILDREN ;
  ChatListItem* chat_list_item = new ChatListItem(chatter_store) ;

DEBUG_TRACE_ADD_CHATLIST_ITEM

  const MessageManagerLock mmLock ; addAndMakeVisible(chat_list_item , item_idx) ;
  this->chatListItems.add(chat_list_item) ;

  refresh() ;
}

void ChatList::valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_node)
{
  if (a_parent_node != this->chattersStore) return ;

  ValueTree     chatter_store  = a_node ;
  int           item_idx       = sortedChatterIdx(chatter_store) + GUI::N_STATIC_CHATLIST_CHILDREN ;
  ChatListItem* chat_list_item = static_cast<ChatListItem*>(getChildComponent(item_idx)) ;

DEBUG_TRACE_REMOVE_CHATLIST_ITEM

  const MessageManagerLock mmLock ;
  this->chatListItems.removeObject(chat_list_item) ;

  refresh() ;
}

void ChatList::valueTreePropertyChanged(ValueTree& a_node , const Identifier& a_key)
{
DEBUG_TRACE_CHATLIST_TREE_CHANGED

  int int_val = int(a_node[a_key]) ;

  if (a_node == this->networkStore && a_key == CONFIG::RETRIES_ID)
  {
    // show/hide dummy user ChatListItem (asynchronously)
    int         connected_state  = int_val ;
    bool        is_dummy_visible = connected_state != IRC::STATE_CONNECTED &&
                                   connected_state != IRC::STATE_FAILED     ;
    StringArray dummy_chatter    = StringArray::fromTokens(GUI::CONNECTING_TEXT , false) ;
    StringArray no_chatters      = StringArray() ;
    StringArray nicks            = (is_dummy_visible) ? dummy_chatter : no_chatters ;
    Identifier  network_id       = this->networkStore.getType() ;

    if (connected_state != IRC::STATE_CONNECTED)
      AvCaster::UpdateChatNicks(network_id , nicks) ;
  }
}

int ChatList::sortedChatterIdx(ValueTree& chatter_store)
{
  StringArray nicks    = AvCaster::GetChatNicks(this->chattersStore) ;
  String      nick     = STRING(chatter_store[CONFIG::NICK_ID]) ;
  nicks.add(nick) ; nicks.sort(true) ;

DEBUG_TRACE_LOCATE_SORTED_CHILD

  return nicks.indexOf(nick) ;
}

void ChatList::refresh()
{
  int  n_chatters  = getNumChildComponents() - GUI::N_STATIC_CHATLIST_CHILDREN ;
  int  list_h      = GUI::EMPTY_CHATLIST_H + (n_chatters * GUI::PADDED_CHATLIST_ITEM_H) ;
  int  list_item_x = GUI::PAD3 ;
  int  list_item_y = GUI::PAD4 ;
  bool is_visible  = n_chatters > 0 ;

DEBUG_TRACE_RESIZE_CHATLIST

  const MessageManagerLock mmLock ;
  setSize(GUI::CHATLIST_W , list_h) ;

  // arrange list entries
  for (int chatter_n = 0 ; chatter_n < n_chatters ; ++chatter_n)
  {
    int        child_n   = chatter_n + GUI::N_STATIC_CHATLIST_CHILDREN ;
    Component* list_item = getChildComponent(child_n) ;

DEBUG_TRACE_MOVE_CHATLIST_ITEM

    list_item->setTopLeftPosition(list_item_x , list_item_y) ;

    list_item_y += GUI::PADDED_CHATLIST_ITEM_H ;
  }

  // set visibility and resize
  setVisible(is_visible) ;
  (static_cast<Chat*>(getParentComponent()))->refresh() ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChatList" componentName=""
                 parentClasses="public Component, public ValueTree::Listener"
                 constructorParams="ValueTree network_store" variableInitialisers="networkStore(network_store)"
                 snapPixels="4" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="128" initialHeight="48">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="4 10 120 34" cornerSize="4" fill="solid: ff202020" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="chattersGroup" id="49d2cfd1b8779149" memberName="chattersGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 0 128 48" outlinecol="ffffffff"
                  textcol="ffffffff" title="(connecting)"/>
  <GENERICCOMPONENT name="dummyChatListItem" id="56b906e64be2f4b6" memberName="dummyChatListItem"
                    virtualName="" explicitFocusOrder="0" pos="12 16 104 24" class="ChatListItem"
                    params="ValueTree::invalid"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
