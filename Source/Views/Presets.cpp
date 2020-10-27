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

#include "../Controllers/AvCaster.h"
#include "../Trace/TraceConfig.h"

//[/Headers]

#include "Presets.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Presets::Presets (MainContent* main_content)
    : mainContent(main_content)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    presetsGroup.reset (new GroupComponent ("presetsGroup",
                                            TRANS("Presets")));
    addAndMakeVisible (presetsGroup.get());
    presetsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    presetsGroup->setColour (GroupComponent::textColourId, Colours::white);

    newPresetButton.reset (new TextButton ("newPresetButton"));
    addAndMakeVisible (newPresetButton.get());
    newPresetButton->setExplicitFocusOrder (1);
    newPresetButton->setButtonText (TRANS("New Preset"));
    newPresetButton->addListener (this);

    newPresetButton->setBounds (268, 36, 96, 24);

    deletePresetButton.reset (new TextButton ("deletePresetButton"));
    addAndMakeVisible (deletePresetButton.get());
    deletePresetButton->setExplicitFocusOrder (2);
    deletePresetButton->setButtonText (TRANS("Delete Preset"));
    deletePresetButton->addListener (this);

    deletePresetButton->setBounds (388, 36, 96, 24);

    presetLabel.reset (new Label ("presetLabel",
                                  TRANS("Preset:")));
    addAndMakeVisible (presetLabel.get());
    presetLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    presetLabel->setJustificationType (Justification::centredLeft);
    presetLabel->setEditable (false, false, false);
    presetLabel->setColour (Label::textColourId, Colours::white);
    presetLabel->setColour (TextEditor::textColourId, Colours::black);
    presetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    presetLabel->setBounds (500, 36, 48, 24);

    presetsCombo.reset (new ComboBox ("presetsCombo"));
    addAndMakeVisible (presetsCombo.get());
    presetsCombo->setExplicitFocusOrder (3);
    presetsCombo->setEditableText (true);
    presetsCombo->setJustificationType (Justification::centredLeft);
    presetsCombo->setTextWhenNothingSelected (String());
    presetsCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetsCombo->addListener (this);

    presetsCombo->setBounds (560, 36, 128, 24);

    configButton.reset (new ImageButton ("configButton"));
    addAndMakeVisible (configButton.get());
    configButton->setExplicitFocusOrder (4);
    configButton->addListener (this);

    configButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::config_png, BinaryData::config_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::confighover_png, BinaryData::confighover_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::configpushed_png, BinaryData::configpushed_pngSize), 1.000f, Colour (0x00000000));
    configButton->setBounds (696, 36, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

  this->mainContent->configureCombobox(this->presetsCombo.get()) ;

    //[/Constructor]
}

Presets::~Presets()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    presetsGroup = nullptr;
    newPresetButton = nullptr;
    deletePresetButton = nullptr;
    presetLabel = nullptr;
    presetsCombo = nullptr;
    configButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Presets::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 20.0f, y = 22.0f, width = static_cast<float> (getWidth() - 40), height = 52.0f;
        Colour fillColour = Colour (0xff282828);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 4.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Presets::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    presetsGroup->setBounds (16, 12, getWidth() - 32, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Presets::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  Identifier key ;
  var        value = var(buttonThatWasClicked->getToggleState()) ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == newPresetButton.get())
    {
        //[UserButtonCode_newPresetButton] -- add your button handler code here..

      handleNewButton() ; return ;

        //[/UserButtonCode_newPresetButton]
    }
    else if (buttonThatWasClicked == deletePresetButton.get())
    {
        //[UserButtonCode_deletePresetButton] -- add your button handler code here..

      handleDeleteButton() ; return ;

        //[/UserButtonCode_deletePresetButton]
    }
    else if (buttonThatWasClicked == configButton.get())
    {
        //[UserButtonCode_configButton] -- add your button handler code here..

      if (!createOrUpdatePreset()) return ;

      key   = CONFIG::IS_PENDING_ID ;
      value = var(false) ;

        //[/UserButtonCode_configButton]
    }

    //[UserbuttonClicked_Post]
  AvCaster::SetValue(key , value) ;

    //[/UserbuttonClicked_Post]
}

void Presets::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetsCombo.get())
    {
        //[UserComboBoxCode_presetsCombo] -- add your combo box handling code here..

      handlePresetsCombo() ; return ;

        //[/UserComboBoxCode_presetsCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Presets::broughtToFront()
{
  this->mainContent->loadPresetsCombo(this->presetsCombo.get()) ;
  setCreatePresetMode(false) ;
}

void Presets::handleNewButton()
{
  this->presetsCombo->setText(String() , juce::dontSendNotification) ;
  this->presetsCombo->grabKeyboardFocus() ;
  setCreatePresetMode(true) ;
}

void Presets::handleDeleteButton()
{
  if (isCreatePresetMode())
  {
    setCreatePresetMode(false) ;
    this->presetsCombo->setText(AvCaster::GetPresetName() , juce::dontSendNotification) ;
  }
  else if (AvCaster::IsStaticPreset()) AvCaster::ResetPreset() ;
  else                                 AvCaster::DeletePreset() ;
}

bool Presets::createOrUpdatePreset()
{
  String preset_name           = this->presetsCombo->getText() ;
  int    option_n              = this->presetsCombo->getSelectedItemIndex() ;
  String stored_name           = AvCaster::GetPresetName() ;
  int    stored_idx            = AvCaster::GetPresetIdx() ;
  bool   is_create_preset_mode = isCreatePresetMode() ;
  bool   is_static_preset      = AvCaster::IsStaticPreset() ;
  bool   is_valid_option       = !!(~option_n) ;
  bool   has_selection_changed = option_n != stored_idx ;
  bool   has_name_changed      = !has_selection_changed && preset_name != stored_name ;
  bool   is_empty_preset_name  = preset_name.isEmpty() ;
  bool   should_rename_preset  = !is_static_preset && !is_valid_option     &&
                                  has_name_changed && !is_empty_preset_name ;
  bool   is_name_collision     = false ;

  // reject duplicate preset name if creating or renaming
  for (int preset_n = 0 ; preset_n < this->presetsCombo->getNumItems() ; ++preset_n)
    if (this->presetsCombo->getItemText(preset_n) == preset_name) is_name_collision = true ;

DEBUG_TRACE_CREATE_PRESET

  // validate new preset name existence
  if (is_empty_preset_name) { AvCaster::Warning(GUI::PRESET_NAME_ERROR_MSG) ; return false ; }

  if (is_create_preset_mode || should_rename_preset)
  {
    // validate preset name uniqueness
    if (is_name_collision) { AvCaster::Warning(GUI::PRESET_RENAME_ERROR_MSG) ; return false ; }

    // create preset
    if      (is_create_preset_mode) AvCaster::StorePreset (preset_name) ;
    // rename preset
    else if (should_rename_preset ) AvCaster::RenamePreset(preset_name) ;
  }
  // update preset
  else AvCaster::StorePreset(stored_name) ;

  setCreatePresetMode(false) ;

  return true ;
}

void Presets::handlePresetsCombo()
{
  if (this->deletePresetButton->isDown()) return ; // defer to handleDeleteButton()

  // create, rename or update preset or revert
  String preset_name       = this->presetsCombo->getText() ;
  int    option_n          = this->presetsCombo->getSelectedItemIndex() ;
  int    stored_option_n   = AvCaster::GetPresetIdx() ;
  bool   should_revert_idx = !createOrUpdatePreset() ;
  int    current_option_n  = (should_revert_idx)? stored_option_n : option_n ;

  AvCaster::SetValue(CONFIG::PRESET_ID , current_option_n) ;
}

void Presets::setCreatePresetMode(bool is_pending_new_preset_name)
{
  bool   is_static_preset   = AvCaster::IsStaticPreset() ;
  bool   should_be_editable = is_pending_new_preset_name || !is_static_preset ;
  String button_text        = (is_static_preset          ) ? GUI::DELETE_BTN_RESET_TEXT  :
                              (is_pending_new_preset_name) ? GUI::DELETE_BTN_CANCEL_TEXT :
                                                             GUI::DELETE_BTN_DELETE_TEXT ;

DEBUG_TRACE_SET_CREATE_PRESET_MODE

  this->presetsCombo      ->setEditableText(should_be_editable) ;
  this->deletePresetButton->setButtonText  (button_text) ;

  if (should_be_editable) this->presetsCombo->showEditor() ;
}

bool Presets::isCreatePresetMode()
{
  return this->deletePresetButton->getButtonText() == GUI::DELETE_BTN_CANCEL_TEXT ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Presets" componentName=""
                 parentClasses="public Component" constructorParams="MainContent* main_content"
                 variableInitialisers="mainContent(main_content)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="20 22 40M 52" cornerSize="4.0" fill="solid: ff282828" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="presetsGroup" id="5f4ffe47101cb73b" memberName="presetsGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 12 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Presets"/>
  <TEXTBUTTON name="newPresetButton" id="e71f2f34ab7772e6" memberName="newPresetButton"
              virtualName="" explicitFocusOrder="1" pos="268 36 96 24" buttonText="New Preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="deletePresetButton" id="693a3f523732acb3" memberName="deletePresetButton"
              virtualName="" explicitFocusOrder="2" pos="388 36 96 24" buttonText="Delete Preset"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="presetLabel" id="3a60504146c5134" memberName="presetLabel"
         virtualName="" explicitFocusOrder="0" pos="500 36 48 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Preset:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="presetsCombo" id="94d77976c2b2f37" memberName="presetsCombo"
            virtualName="" explicitFocusOrder="3" pos="560 36 128 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <IMAGEBUTTON name="configButton" id="19b48645d13bf310" memberName="configButton"
               virtualName="" explicitFocusOrder="4" pos="696 36 24 24" buttonText="configButton"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::config_png" opacityNormal="1.0" colourNormal="0"
               resourceOver="BinaryData::confighover_png" opacityOver="1.0"
               colourOver="0" resourceDown="BinaryData::configpushed_png" opacityDown="1.0"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

