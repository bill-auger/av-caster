/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
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
  ConfigScreen is the screen capture configuration GUI for the AvCaster application.
  It has it controls for setting the per-preset screen capture parameters.
                                                                    //[/Comments]
*/
class ConfigScreen  : public Component,
                      public Slider::Listener
{
public:
    //==============================================================================
    ConfigScreen ();
    ~ConfigScreen() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> displayLabel;
    std::unique_ptr<Slider> displaySlider;
    std::unique_ptr<Label> screenLabel;
    std::unique_ptr<Slider> screenSlider;
    std::unique_ptr<Label> screenWidthLabel;
    std::unique_ptr<TextEditor> screenWidthText;
    std::unique_ptr<Label> screenHeightLabel;
    std::unique_ptr<TextEditor> screenHeightText;
    std::unique_ptr<Label> xOffsetLabel;
    std::unique_ptr<TextEditor> xOffsetText;
    std::unique_ptr<Label> yOffsetLabel;
    std::unique_ptr<TextEditor> yOffsetText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigScreen)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

