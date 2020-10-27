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
  ConfigAudio is the audio device configuration GUI for the AvCaster application.
  It has it controls for setting the per-preset audio device parameters.
                                                                    //[/Comments]
*/
class ConfigAudio  : public Component,
                     public ComboBox::Listener,
                     public Slider::Listener
{
public:
    //==============================================================================
    ConfigAudio ();
    ~ConfigAudio() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> audioApiLabel;
    std::unique_ptr<ComboBox> audioApiCombo;
    std::unique_ptr<Label> audioDevLabel;
    std::unique_ptr<ComboBox> audioDevCombo;
    std::unique_ptr<Label> audioCodecLabel;
    std::unique_ptr<ComboBox> audioCodecCombo;
    std::unique_ptr<Label> nChannelsLabel;
    std::unique_ptr<Slider> nChannelsSlider;
    std::unique_ptr<Label> samplerateLabel;
    std::unique_ptr<ComboBox> samplerateCombo;
    std::unique_ptr<Label> audioBitrateLabel;
    std::unique_ptr<ComboBox> audioBitrateCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigAudio)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

