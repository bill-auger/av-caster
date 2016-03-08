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


#ifndef _CONFIGOUTPUT_H_
#define _CONFIGOUTPUT_H_

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
                      public ComboBoxListener
{
public:
    //==============================================================================
    ConfigOutput ();
    ~ConfigOutput();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  friend class Config ;


  MainContent* mainContent ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> outputStreamLabel;
    ScopedPointer<ComboBox> outputSinkCombo;
    ScopedPointer<Label> outputWidthLabel;
    ScopedPointer<TextEditor> outputWidthText;
    ScopedPointer<Label> outputHeightLabel;
    ScopedPointer<TextEditor> outputHeightText;
    ScopedPointer<Label> framerateLabel;
    ScopedPointer<ComboBox> framerateCombo;
    ScopedPointer<Label> bitrateLabel;
    ScopedPointer<ComboBox> videoBitrateCombo;
    ScopedPointer<Label> outputDestLabel;
    ScopedPointer<TextEditor> outputDestText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigOutput)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIGOUTPUT_H_
