/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#ifndef _CHATLIST_H_
#define _CHATLIST_H_

//[Headers]     -- You can add your own extra header files here --

#include "ChatListItem.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ChatList is the GUI container for ChatListItem instances
                                                                    //[/Comments]
*/
class ChatList  : public Component,
                  public ValueTree::Listener
{
public:
    //==============================================================================
    ChatList ();
    ~ChatList();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

private:

  friend class MainContent ;


  void valueTreeChildAdded     (ValueTree& a_parent_node , ValueTree&        a_node          ) override ;
  void valueTreeChildRemoved   (ValueTree& a_parent_node , ValueTree&        a_node , int idx) override ;
  void valueTreePropertyChanged(ValueTree& a_node        , const Identifier& a_key           ) override ;

  void initialize        (ValueTree network_store , ValueTree chatters_store) ;
  void createChatListItem(int child_idx) ;
  int  sortedChatterIdx  (ValueTree& chatter_store) ;
  void refresh           () ;

  // unused ValueTree::Listener interface implementations
  void valueTreeChildOrderChanged(ValueTree& /*a_parent_node*/ , int /*prev_idx*/ , int /*curr_idx*/) override {}
  void valueTreeParentChanged    (ValueTree& /*a_node*/                                             ) override {}
  void valueTreeRedirected       (ValueTree& /*a_node*/                                             ) override {}

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree                networkStore ;
  ValueTree                chattersStore ;
  OwnedArray<ChatListItem> chatListItems ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> chattersGroup;
    ScopedPointer<ChatListItem> dummyChatListItem;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatList)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // _CHATLIST_H_
