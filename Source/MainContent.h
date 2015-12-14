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

#ifndef __JUCE_HEADER_262A4C4094138A40__
#define __JUCE_HEADER_262A4C4094138A40__

//[Headers]     -- You can add your own extra header files here --

#include "Background.h"
#include "Chat.h"
#include "Config.h"
#include "Controls.h"
#include "Preview.h"
#include "Presets.h"
#include "Statusbar.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  MainContent is the main GUI container class for the AvCaster application.
                                                                    //[/Comments]
*/
class MainContent  : public Component
{
public:
    //==============================================================================
    MainContent ();
    ~MainContent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void configureCombobox(ComboBox* a_combobox) ;
  void loadPresetsCombo (ComboBox* a_combobox) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class AvCaster ;


  void           initialize      (ValueTree servers_store) ;
  void           warning         (String message_text) ;
  void           error           (String message_text) ;
  Rectangle<int> getPreviewBounds() ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Background> background;
    ScopedPointer<Controls> controls;
    ScopedPointer<Chat> chat;
    ScopedPointer<Preview> preview;
    ScopedPointer<Presets> presets;
    ScopedPointer<Config> config;
    ScopedPointer<Statusbar> statusbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_262A4C4094138A40__
