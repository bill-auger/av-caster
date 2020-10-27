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


//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Preview.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Preview::Preview ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    previewGroup.reset (new GroupComponent ("previewGroup",
                                            TRANS("Preview")));
    addAndMakeVisible (previewGroup.get());
    previewGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    previewGroup->setColour (GroupComponent::textColourId, Colours::white);

    drawable1 = Drawable::createFromImageData (BinaryData::avcasterlogo128_png, BinaryData::avcasterlogo128_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Preview::~Preview()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    previewGroup = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Preview::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 18.0f, y = 18.0f, width = static_cast<float> (getWidth() - 36), height = static_cast<float> (getHeight() - 36);
        Colour fillColour = Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
    }

    {
        int x = proportionOfWidth (0.5000f) - (100 / 2), y = proportionOfHeight (0.5000f) - (100 / 2), width = 100, height = 100;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black);
        jassert (drawable1 != nullptr);
        if (drawable1 != nullptr)
            drawable1->drawWithin (g, Rectangle<int> (x, y, width, height).toFloat(),
                                   RectanglePlacement::stretchToFit, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Preview::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    previewGroup->setBounds (16, 8, getWidth() - 32, getHeight() - 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Preview" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="18 18 36M 36M" cornerSize="5.0" fill="solid: ff000000" hasStroke="0"/>
    <IMAGE pos="50%c 50%c 100 100" resource="BinaryData::avcasterlogo128_png"
           opacity="1.0" mode="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="previewGroup" id="6607ba656d5c8919" memberName="previewGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 8 32M 24M" outlinecol="ffffffff"
                  textcol="ffffffff" title="Preview"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

