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

#include "ChatList.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatList::ChatList ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  this->serversStore.addListener(this) ;

  refresh() ;

    //[/Constructor]
}

ChatList::~ChatList()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..

  deleteAllChildren() ;

    //[/Destructor]
}

//==============================================================================
void ChatList::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChatList::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ChatList::reloadNicks()
{
  this->nicks.clear() ;
  for (int server_n = 0 ; server_n < this->serversStore.getNumChildren() ; ++server_n)
  {
    Identifier server_id = this->serversStore.getChild(server_n).getType() ;

    this->nicks.add(AvCaster::GetChatNicks(server_id)) ;

DEBUG_TRACE_RELOAD_NICKS
  }
}

void ChatList::refresh()
{
  bool is_scrollbar_visible = getHeight() > GUI::LIST_H ;
  int  n_list_items         = getNumChildComponents() ;
  int  list_item_h          = GUI::LIST_ITEM_H + GUI::PAD ;
  int  list_item_w          = (is_scrollbar_visible)? GUI::SCROLLING_LIST_W : GUI::LIST_W ;
  int  list_item_x          = 0 ;
  int  list_item_y          = 0 ;
  int  list_h               = GUI::PAD + (n_list_items * list_item_h) ;

  setSize(GUI::LIST_W , list_h) ;

  // resize and arrange list entries
  for (int item_n = 0 ; item_n < n_list_items ; ++item_n)
  {
    Component* list_item = getChildComponent(item_n) ;

    list_item->setSize(           list_item_w , GUI::LIST_ITEM_H) ;
    list_item->setTopLeftPosition(list_item_x , list_item_y     ) ;

    list_item_y += GUI::LIST_ITEM_H + GUI::PAD ;
  }
}

int ChatList::sortedChildIdx(ValueTree& a_parent_node , ValueTree& a_node)
{
  String     nick         = STRING(a_node[CONFIG::CHAT_NICK_ID]) ;
  Identifier server_id    = a_parent_node.getParent().getType() ;
  ValueTree  server_store = this->serversStore.getChildWithName(server_id) ;
  int        server_idx   = this->serversStore.indexOf(server_store) ;
  int        child_idx    = this->nicks[server_idx].indexOf(nick) ;

DEBUG_TRACE_LOCATE_SORTED_CHILD

  return child_idx ;
}

void ChatList::valueTreeChildAdded(ValueTree& a_parent_node , ValueTree& a_node)
{
DEBUG_TRACE_ADD_CHAT_LIST_ITEM UNUSED(a_parent_node) ;

  reloadNicks() ;

  ChatListItem* a_list_item = new ChatListItem(a_node) ;
  int           child_idx   = sortedChildIdx(a_parent_node , a_node) ;

  const MessageManagerLock mmLock ; addAndMakeVisible(a_list_item , child_idx) ;
  refresh() ;
}

void ChatList::valueTreeChildRemoved(ValueTree& a_parent_node , ValueTree& a_node)
{
  int        child_idx   = sortedChildIdx(a_parent_node , a_node) ;
  Component* a_list_item = getChildComponent(child_idx) ;

DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM UNUSED(a_parent_node) ;
DBG("a_parent_node=" + String(a_parent_node.getType()) +
    " a_node=" + String(a_node.getType()) +
    " child_idx=" + String(child_idx) +
    " a_list_item=" + String(!!a_list_item)) ;

  const MessageManagerLock mmLock ; delete a_list_item ;
  refresh() ; reloadNicks() ;
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
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
