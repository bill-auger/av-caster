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

#ifndef __JUCE_HEADER_B5AA576BA216A776__
#define __JUCE_HEADER_B5AA576BA216A776__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Instances of ChatListItem are subcomponents of the ChatList container
  They each represent an individual chat user.
                                                                    //[/Comments]
*/
class ChatListItem  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    ChatListItem (ValueTree chatter_store);
    ~ChatListItem();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  ValueTree chatterStore ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> banButton;
    ScopedPointer<Label> nickLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatListItem)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B5AA576BA216A776__
