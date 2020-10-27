/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"


class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  ConfigChat is the chat configuration GUI for the AvCaster application.
  It has it controls for setting the per-network chat parameters.
                                                                    //[/Comments]
*/
class ConfigChat  : public Component
{
public:
    //==============================================================================
    ConfigChat ();
    ~ConfigChat() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ToggleButton> timestampToggle;
    std::unique_ptr<ToggleButton> joinPartToggle;
    std::unique_ptr<Label> networkLabel;
    std::unique_ptr<Label> portLabel;
    std::unique_ptr<TextEditor> portText;
    std::unique_ptr<Label> nickLabel;
    std::unique_ptr<TextEditor> nickText;
    std::unique_ptr<Label> passLabel;
    std::unique_ptr<TextEditor> passText;
    std::unique_ptr<Label> channelLabel;
    std::unique_ptr<TextEditor> channelText;
    std::unique_ptr<Label> greetingLabel;
    std::unique_ptr<TextEditor> greetingText;
    std::unique_ptr<TextEditor> networkText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigChat)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

