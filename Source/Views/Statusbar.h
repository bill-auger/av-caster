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

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Statusbar is the bottom statusbar GUI for the AvCaster application.
  It does nothing useful yet.
                                                                    //[/Comments]
*/
class Statusbar  : public Component
{
public:
    //==============================================================================
    Statusbar ();
    ~Statusbar() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setStatusL(String statusText) ;
  void setStatusC(String statusText) ;
  void setStatusR(String statusText) ;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> statusLLabel;
    std::unique_ptr<Label> statusCLabel;
    std::unique_ptr<Label> statusRLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Statusbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

