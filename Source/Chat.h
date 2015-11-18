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

#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

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
              public TextEditor::Listener
{
public:
    //==============================================================================
    Chat ();
    ~Chat();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void updateVisiblilty() ;
  void addChatLine     (String chat_user , String chat_text) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class MainContent ;

  void initialize                (ValueTree chatters_store) ;
  void textEditorReturnKeyPressed(TextEditor& a_text_editor) ;


  ValueTree chattersStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> chatGroup;
    ScopedPointer<GroupComponent> chatHistoryGroup;
    ScopedPointer<TextEditor> chatHistoryText;
    ScopedPointer<GroupComponent> chatEntryGroup;
    ScopedPointer<TextEditor> chatEntryText;
    ScopedPointer<ChatList> chatList;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // CHAT_H_INCLUDED
