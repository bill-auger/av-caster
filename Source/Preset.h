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

#ifndef __JUCE_HEADER_E38720C00B5B6F26__
#define __JUCE_HEADER_E38720C00B5B6F26__

//[Headers]     -- You can add your own extra header files here --

#include "MainContent.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Preset  : public Component,
                public ButtonListener
{
public:
    //==============================================================================
    Preset (MainContent* main_content);
    ~Preset();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

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


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> presetsGroup;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> newButton;
    ScopedPointer<TextButton> deleteButton;
    ScopedPointer<Label> presetLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Preset)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_E38720C00B5B6F26__
