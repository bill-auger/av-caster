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

#ifndef _CONFIG_AUDIO_H_
#define _CONFIG_AUDIO_H_

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
                     public ComboBoxListener,
                     public SliderListener
{
public:
    //==============================================================================
    ConfigAudio ();
    ~ConfigAudio();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> audioApiLabel;
    ScopedPointer<ComboBox> audioApiCombo;
    ScopedPointer<Label> audioDevLabel;
    ScopedPointer<ComboBox> audioDevCombo;
    ScopedPointer<Label> audioCodecLabel;
    ScopedPointer<ComboBox> audioCodecCombo;
    ScopedPointer<Label> nChannelsLabel;
    ScopedPointer<Slider> nChannelsSlider;
    ScopedPointer<Label> samplerateLabel;
    ScopedPointer<ComboBox> samplerateCombo;
    ScopedPointer<Label> audioBitrateLabel;
    ScopedPointer<ComboBox> audioBitrateCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigAudio)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIG_AUDIO_H_
