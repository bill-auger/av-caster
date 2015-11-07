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

//[Headers] You can add your own extra header files here...

#include "AvCaster.h"
#include "Trace/Trace.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent (DocumentWindow* main_window)
    : mainWindow(main_window)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (background = new Background());
    background->setName ("background");

    addAndMakeVisible (controls = new Controls());
    controls->setName ("controls");

    addAndMakeVisible (preview = new Preview());
    preview->setName ("preview");

    addAndMakeVisible (config = new Config());
    config->setName ("config");

    addAndMakeVisible (statusbar = new Statusbar());
    statusbar->setName ("statusbar");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (758, 694);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainContent::~MainContent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    background = nullptr;
    controls = nullptr;
    preview = nullptr;
    config = nullptr;
    statusbar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainContent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    background->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    controls->setBounds (0, 0, getWidth() - 0, 76);
    preview->setBounds (0, 76, getWidth() - 0, getHeight() - 100);
    config->setBounds (0, 76, getWidth() - 0, getHeight() - 100);
    statusbar->setBounds (0, getHeight() - 24, getWidth() - 0, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainContent::instantiate()
{
  // Background
  this->background = new Background() ;
  this->addChildAndSetID(this->background , GUI::BACKGROUND_GUI_ID) ;

  // Controls
  this->controls = new Controls() ;
  this->addChildAndSetID(this->controls , GUI::CONTROLS_GUI_ID) ;

  // Preview
  this->preview = new Preview() ;
  this->addChildAndSetID(this->preview , GUI::PREVIEW_GUI_ID) ;

  // Config
  this->config = new Config() ;
  this->addChildAndSetID(this->config , GUI::CONFIG_GUI_ID) ;

  // Statusbar
  this->statusbar = new Statusbar() ;
  this->addChildAndSetID(this->statusbar , GUI::STATUSBAR_GUI_ID) ;
  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::INIT_STATUS_TEXT) ;

  resized() ;
}

void MainContent::setTitle(String title_text)
{
  this->mainWindow->setName(APP::APP_NAME + " - " + title_text) ;
}

void MainContent::warning(String message_text)
{
  if (JUCEApplicationBase::getInstance()->isInitialising()) return ;

  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon , GUI::MODAL_WARNING_TITLE ,
                                   message_text          , String::empty            ,
                                   nullptr               , AvCaster::GetModalCb()   ) ;
}

void MainContent::error(String message_text)
{
  if (JUCEApplicationBase::getInstance()->isInitialising()) return ;

  AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon , GUI::MODAL_ERROR_TITLE ,
                                   message_text             , String::empty          ,
                                   nullptr                  , AvCaster::GetModalCb() ) ;
}

Rectangle<int> MainContent::getPreviewBounds()
{
  Rectangle<int> preview_bounds = this->preview->getBounds() ;
  Rectangle<int> group_bounds   = this->preview->getChildComponent(0)->getBounds() ;

  preview_bounds.setX     (group_bounds  .getX()      + GUI::PAD4) ;
  preview_bounds.setY     (preview_bounds.getY()      + GUI::PAD4 + GUI::PAD8) ;
  preview_bounds.setWidth (group_bounds  .getWidth()  - GUI::PAD8) ;
  preview_bounds.setHeight(group_bounds  .getHeight() - GUI::PAD8) ;

  return preview_bounds ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContent" componentName=""
                 parentClasses="public Component" constructorParams="DocumentWindow* main_window"
                 variableInitialisers="mainWindow(main_window)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="758" initialHeight="694">
  <BACKGROUND backgroundColour="ff101010"/>
  <GENERICCOMPONENT name="background" id="4d43eef09b00fdf4" memberName="background"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="Background"
                    params=""/>
  <GENERICCOMPONENT name="controls" id="7a0ffc87dbd1f2a3" memberName="controls" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 76" class="Controls" params=""/>
  <GENERICCOMPONENT name="preview" id="ac9a4042c98734e2" memberName="preview" virtualName=""
                    explicitFocusOrder="0" pos="0 76 0M 100M" class="Preview" params=""/>
  <GENERICCOMPONENT name="config" id="75e8b11c95e2efaf" memberName="config" virtualName=""
                    explicitFocusOrder="0" pos="0 76 0M 100M" class="Config" params=""/>
  <GENERICCOMPONENT name="statusbar" id="2dc0514b582b96cb" memberName="statusbar"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 0M 24" class="Statusbar"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
