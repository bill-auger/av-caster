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


#ifndef STATUSBAR_H_INCLUDED
#define STATUSBAR_H_INCLUDED

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
    ~Statusbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

  void setStatusL(String statusText) ;
  void setStatusC(String statusText) ;
  void setStatusR(String statusText) ;

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> statusLLabel;
    ScopedPointer<Label> statusCLabel;
    ScopedPointer<Label> statusRLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Statusbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // STATUSBAR_H_INCLUDED
