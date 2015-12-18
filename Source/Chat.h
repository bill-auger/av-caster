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

#ifndef __JUCE_HEADER_8B23E8CA1D72080__
#define __JUCE_HEADER_8B23E8CA1D72080__

//[Headers]     -- You can add your own extra header files here --

#include "ChatList.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Chat is a the chat GUI container for the AvCaster application.
  It hosts the chat history, message entry, and users list components.
                                                                    //[/Comments]
*/
class Chat  : public Component,
              public TextEditor::Listener,
              public ValueTree::Listener
{
public:
    //==============================================================================
    Chat ();
    ~Chat();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void updateVisiblilty() ;
  void refresh         () ;
  void addChatLine     (String prefix , String chat_user , String chat_text) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class MainContent ;

  void textEditorReturnKeyPressed(TextEditor& a_text_editor) override ;
  void valueTreeChildAdded       (ValueTree& servers_store , ValueTree& server_store) override ;
  void valueTreeChildRemoved     (ValueTree& servers_store , ValueTree& server_store) override ;

  void initialize     (ValueTree servers_store) ;
  void createChatList (ValueTree server_store) ;
  void destroyChatList(String server_id) ;
  bool isServersNode  (ValueTree& a_parent_node , ValueTree& a_node) ;

  // unused ValueTree::Listener interface implementations
  void valueTreePropertyChanged(  ValueTree& a_node , const Identifier& a_key) override { UNUSED(a_node) ; UNUSED(a_key) ;  } ;
  void valueTreeChildOrderChanged(ValueTree& a_parent_node)                    override { UNUSED(a_parent_node) ;           } ;
  void valueTreeParentChanged(    ValueTree& a_node)                           override { UNUSED(a_node) ;                  } ;
  void valueTreeRedirected(       ValueTree& a_node)                           override { UNUSED(a_node) ;                  } ;


  ValueTree            serversStore ;
  OwnedArray<ChatList> chatLists ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> chatGroup;
    ScopedPointer<GroupComponent> chatHistoryGroup;
    ScopedPointer<TextEditor> chatHistoryText;
    ScopedPointer<GroupComponent> chatEntryGroup;
    ScopedPointer<TextEditor> chatEntryText;
    ScopedPointer<ChatList> dummyChatList;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8B23E8CA1D72080__
