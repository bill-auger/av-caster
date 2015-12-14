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

#ifndef __JUCE_HEADER_27B35F6AAB5C16AC__
#define __JUCE_HEADER_27B35F6AAB5C16AC__

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

class MainContent ;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Presets  : public Component,
                 public ButtonListener,
                 public ComboBoxListener
{
public:
    //==============================================================================
    Presets ();
    ~Presets();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* configpushed_png;
    static const int configpushed_pngSize;
    static const char* confighover_png;
    static const int confighover_pngSize;
    static const char* preferencessystem_png;
    static const int preferencessystem_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void broughtToFront     () override ;

  void handleSaveButton   () ;
  void handleNewButton    () ;
  void handleDeleteButton () ;
  void handlePresetCombo  () ;
  void toggleControls     () ;
  void setCreatePresetMode(bool is_pending_new_preset_name) ;
  bool isCreatePresetMode () ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> presetsGroup;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> newButton;
    ScopedPointer<TextButton> deleteButton;
    ScopedPointer<Label> presetLabel;
    ScopedPointer<ComboBox> presetsCombo;
    ScopedPointer<ImageButton> configButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Presets)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_27B35F6AAB5C16AC__
