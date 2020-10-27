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
  ConfigOutput is the stream output configuration GUI for the AvCaster application.
  It has it controls for setting the per-preset stream output parameters.
                                                                    //[/Comments]
*/
class ConfigOutput  : public Component,
                      public ComboBox::Listener
{
public:
    //==============================================================================
    ConfigOutput ();
    ~ConfigOutput() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> outputStreamLabel;
    std::unique_ptr<ComboBox> outputSinkCombo;
    std::unique_ptr<Label> outputWidthLabel;
    std::unique_ptr<TextEditor> outputWidthText;
    std::unique_ptr<Label> outputHeightLabel;
    std::unique_ptr<TextEditor> outputHeightText;
    std::unique_ptr<Label> framerateLabel;
    std::unique_ptr<ComboBox> framerateCombo;
    std::unique_ptr<Label> bitrateLabel;
    std::unique_ptr<ComboBox> videoBitrateCombo;
    std::unique_ptr<Label> outputDestLabel;
    std::unique_ptr<TextEditor> outputDestText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigOutput)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

