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


#ifndef _CHAT_H_
#define _CHAT_H_

//[Headers]     -- You can add your own extra header files here --

#include "ChatList.h"


class MainContent ;

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
    Chat (MainContent* main_content);
    ~Chat();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  friend class MainContent ;


  void updateVisiblilty(bool is_visible) ;
#ifndef DISABLE_CHAT
  void addChatLine     (String prefix , String nick , String message) ;
#endif // DISABLE_CHAT


private:

  void textEditorReturnKeyPressed(TextEditor& a_text_editor) override ;

  void setFontSize() ;
  int  getFontSize() ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
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

#endif   // _CHAT_H_
