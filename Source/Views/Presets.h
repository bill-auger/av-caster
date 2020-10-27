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
  Presets is the preset management GUI for the AvCaster application.
  It has controls for adding, removing, and selecting preset stream configurations.
                                                                    //[/Comments]
*/
class Presets  : public Component,
                 public Button::Listener,
                 public ComboBox::Listener
{
public:
    //==============================================================================
    Presets (MainContent* main_content);
    ~Presets() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void broughtToFront() override ;

  void handleNewButton     () ;
  void handleDeleteButton  () ;
  bool handleConfigButton  () ;
  void handlePresetsCombo  () ;
  void toggleControls      () ;
  void setCreatePresetMode (bool is_pending_new_preset_name) ;
  bool isCreatePresetMode  () ;
  bool createOrUpdatePreset() ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> presetsGroup;
    std::unique_ptr<TextButton> newPresetButton;
    std::unique_ptr<TextButton> deletePresetButton;
    std::unique_ptr<Label> presetLabel;
    std::unique_ptr<ComboBox> presetsCombo;
    std::unique_ptr<ImageButton> configButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Presets)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

