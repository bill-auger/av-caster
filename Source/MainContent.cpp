/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

#include "AvCaster.h"
#include "Trace/Trace.h"

//[/Headers]

#include "MainContent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContent::MainContent ()
{
    addAndMakeVisible (background = new Background());
    background->setName ("background");

    addAndMakeVisible (controls = new Controls (this));
    controls->setName ("controls");

    addAndMakeVisible (chat = new Chat());
    chat->setName ("chat");

    addAndMakeVisible (preview = new Preview());
    preview->setName ("preview");

    addAndMakeVisible (presets = new Presets (this));
    presets->setName ("presets");

    addAndMakeVisible (config = new Config (this));
    config->setName ("config");

    addAndMakeVisible (statusbar = new Statusbar());
    statusbar->setName ("statusbar");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (758, 762);


    //[Constructor] You can add your own custom stuff here..

  setSize(GUI::WINDOW_W , GUI::WINDOW_H) ;

  this->statusbar->setAlwaysOnTop(true) ;
  this->statusbar->setStatusL(GUI::INIT_STATUS_TEXT) ;

    //[/Constructor]
}

MainContent::~MainContent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    background = nullptr;
    controls = nullptr;
    chat = nullptr;
    preview = nullptr;
    presets = nullptr;
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
    chat->setBounds (0, 76, getWidth() - 0, getHeight() - 100);
    preview->setBounds (0, 76, getWidth() - 0, getHeight() - 100);
    presets->setBounds (0, 0, getWidth() - 0, 76);
    config->setBounds (0, 76, getWidth() - 0, getHeight() - 100);
    statusbar->setBounds (0, getHeight() - 24, getWidth() - 0, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainContent::configureButton(Button* a_button , Button::Listener* a_button_listener)
{
  a_button->addListener(a_button_listener) ;
}

void MainContent::configureSlider(Slider* a_slider , Slider::Listener* a_slider_listener ,
                                  double  min_val  , double            max_val           ,
                                  double  step                                           )
{
  a_slider->setColour(Slider::textBoxBackgroundColourId   , GUI::TEXT_BG_COLOR      ) ;
  a_slider->setColour(Slider::textBoxTextColourId         , GUI::TEXT_NORMAL_COLOR  ) ;
  a_slider->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  a_slider->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  a_slider->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  a_slider->setRange(min_val , max_val , step) ;
  a_slider->addListener(a_slider_listener) ;
}

void MainContent::configureTextEditor(TextEditor*           a_text_editor   ,
                                      TextEditor::Listener* a_text_listener ,
                                      int                   max_n_chars     ,
                                      const String          allowed_chars   )
{
  a_text_editor->setSelectAllWhenFocused(true) ;
  a_text_editor->setInputRestrictions(max_n_chars , allowed_chars) ;
  a_text_editor->setColour(TextEditor::backgroundColourId      , GUI::TEXT_BG_COLOR      ) ;
  a_text_editor->setColour(TextEditor::textColourId            , GUI::TEXT_NORMAL_COLOR  ) ;
  a_text_editor->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  a_text_editor->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  a_text_editor->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  a_text_editor->addListener(a_text_listener) ;
}

void MainContent::configureCombobox(ComboBox* a_combobox , ComboBox::Listener* a_combobox_listener)
{
  a_combobox->setColour(ComboBox::textColourId       , GUI::TEXT_NORMAL_COLOR) ;
  a_combobox->setColour(ComboBox::backgroundColourId , GUI::TEXT_BG_COLOR    ) ;
  a_combobox->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  a_combobox->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  a_combobox->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  if (a_combobox_listener == nullptr) return ;

  a_combobox->addListener(a_combobox_listener) ;
}

void MainContent::loadPresetsCombo(ComboBox* a_combobox)
{
  StringArray preset_names = AvCaster::GetPresetsNames() ;
  int         preset_idx   = AvCaster::GetPresetIdx() ;

  a_combobox->clear               (juce::dontSendNotification) ;
  a_combobox->addItemList         (preset_names , 1) ;
  a_combobox->setSelectedItemIndex(preset_idx , juce::dontSendNotification) ;
}

void MainContent::initialize(ValueTree servers_store)
{
  this->chat->initialize(servers_store) ;
}

void MainContent::disableControls(bool is_media_enabled  , bool is_screen_enabled  ,
                                  bool is_camera_enabled , bool is_text_enabled    ,
                                  bool is_image_enabled  , bool is_preview_enabled ,
                                  bool is_audio_enabled                            )
{
  this->controls->disableControls(is_media_enabled  , is_screen_enabled  ,
                                  is_camera_enabled , is_text_enabled    ,
                                  is_image_enabled  , is_preview_enabled ,
                                  is_audio_enabled                       ) ;
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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="758" initialHeight="762">
  <BACKGROUND backgroundColour="ff101010"/>
  <GENERICCOMPONENT name="background" id="4d43eef09b00fdf4" memberName="background"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="Background"
                    params=""/>
  <GENERICCOMPONENT name="controls" id="7a0ffc87dbd1f2a3" memberName="controls" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 76" class="Controls" params="this"/>
  <GENERICCOMPONENT name="chat" id="ac9a4042c98734e2" memberName="chat" virtualName=""
                    explicitFocusOrder="0" pos="0 76 0M 100M" class="Chat" params=""/>
  <GENERICCOMPONENT name="preview" id="75e8b11c95e2efaf" memberName="preview" virtualName=""
                    explicitFocusOrder="0" pos="0 76 0M 100M" class="Preview" params=""/>
  <GENERICCOMPONENT name="presets" id="c3256eaa517d34eb" memberName="presets" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 76" class="Presets" params="this"/>
  <GENERICCOMPONENT name="config" id="4f3cab5613666ef6" memberName="config" virtualName=""
                    explicitFocusOrder="0" pos="0 76 0M 100M" class="Config" params="this"/>
  <GENERICCOMPONENT name="statusbar" id="2dc0514b582b96cb" memberName="statusbar"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 0M 24" class="Statusbar"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
