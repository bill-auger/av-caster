/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_CF0070E7070C0E60__
#define __JUCE_HEADER_CF0070E7070C0E60__

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
    ChatList (ValueTree chatters_store);
    ~ChatList();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void valueTreeChildAdded  (ValueTree& chatters_store , ValueTree& chatter_store) override ;
  void valueTreeChildRemoved(ValueTree& chatters_store , ValueTree& chatter_store) override ;

  void createChatListItem(int child_idx) ;
  int  sortedChildIdx    (ValueTree& a_parent_node , ValueTree& a_node) ;
  void refresh           () ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(  ValueTree& a_node , const Identifier& a_key) override { UNUSED(a_node) ; UNUSED(a_key) ;  } ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                    override { UNUSED(a_parent_node) ;           } ;
  void valueTreeParentChanged(    ValueTree& a_node)                           override { UNUSED(a_node) ;                  } ;
  void valueTreeRedirected(       ValueTree& a_node)                           override { UNUSED(a_node) ;                  } ;


  ValueTree chattersStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> chattersGroup;
    ScopedPointer<ChatListItem> dummyChatListItem;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatList)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CF0070E7070C0E60__
