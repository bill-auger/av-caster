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

#ifndef _CONFIG_CHAT_H_
#define _CONFIG_CHAT_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"


class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ConfigChat is the chat configuration GUI for the AvCaster application.
  It has it controls for setting the per-server chat parameters.
                                                                    //[/Comments]
*/
class ConfigChat  : public Component,
                    public ComboBoxListener
{
public:
    //==============================================================================
    ConfigChat ();
    ~ConfigChat();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> serverButton;
    ScopedPointer<Label> hostLabel;
    ScopedPointer<ComboBox> hostCombo;
    ScopedPointer<Label> portLabel;
    ScopedPointer<TextEditor> portText;
    ScopedPointer<Label> nickLabel;
    ScopedPointer<TextEditor> nickText;
    ScopedPointer<Label> passLabel;
    ScopedPointer<TextEditor> passText;
    ScopedPointer<Label> channelLabel;
    ScopedPointer<TextEditor> channelText;
    ScopedPointer<Label> greetingLabel;
    ScopedPointer<TextEditor> greetingText;
    ScopedPointer<ToggleButton> joinPartToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigChat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIG_CHAT_H_
