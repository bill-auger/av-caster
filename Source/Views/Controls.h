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
  Controls is the media selection and preview GUI for the AvCaster application.
  It serves only as a consistent backdrop and/or interstitial.
                                                                    //[/Comments]
*/
class Controls  : public Component,
                  public Button::Listener,
                  public ComboBox::Listener
{
public:
    //==============================================================================
    Controls (MainContent* main_content);
    ~Controls() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

private:

  friend class MainContent ;


  void broughtToFront() override ;

  void initialize        (ValueTree config_store , NamedValueSet& disabled_features) ;
  void loadConfig        () ;
  void handlePresetsCombo() ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  MainContent* mainContent ;
  ValueTree    configStore ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> controlsGroup;
    std::unique_ptr<ToggleButton> screenToggle;
    std::unique_ptr<ToggleButton> cameraToggle;
    std::unique_ptr<ToggleButton> textToggle;
    std::unique_ptr<ToggleButton> imageToggle;
    std::unique_ptr<ToggleButton> previewToggle;
    std::unique_ptr<ToggleButton> audioToggle;
    std::unique_ptr<ToggleButton> outputToggle;
    std::unique_ptr<ComboBox> presetsCombo;
    std::unique_ptr<ImageButton> configButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

