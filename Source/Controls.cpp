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
#include "Trace/TraceControls.h"

//[/Headers]

#include "Controls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Controls::Controls ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (controlsGroup = new GroupComponent ("controlsGroup",
                                                           TRANS("Controls")));
    controlsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    controlsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (screencapToggle = new ToggleButton ("screencapToggle"));
    screencapToggle->setExplicitFocusOrder (1);
    screencapToggle->setButtonText (TRANS("Screen"));
    screencapToggle->addListener (this);
    screencapToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (cameraToggle = new ToggleButton ("cameraToggle"));
    cameraToggle->setExplicitFocusOrder (2);
    cameraToggle->setButtonText (TRANS("Camera"));
    cameraToggle->addListener (this);
    cameraToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (textToggle = new ToggleButton ("textToggle"));
    textToggle->setExplicitFocusOrder (3);
    textToggle->setButtonText (TRANS("Text"));
    textToggle->addListener (this);
    textToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (interstitialToggle = new ToggleButton ("interstitialToggle"));
    interstitialToggle->setExplicitFocusOrder (4);
    interstitialToggle->setButtonText (TRANS("Pause"));
    interstitialToggle->addListener (this);
    interstitialToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (previewToggle = new ToggleButton ("previewToggle"));
    previewToggle->setExplicitFocusOrder (5);
    previewToggle->setButtonText (TRANS("Preview"));
    previewToggle->addListener (this);
    previewToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (outputToggle = new ToggleButton ("outputToggle"));
    outputToggle->setExplicitFocusOrder (6);
    outputToggle->setButtonText (TRANS("Broadcast"));
    outputToggle->addListener (this);
    outputToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (presetCombo = new ComboBox ("presetCombo"));
    presetCombo->setExplicitFocusOrder (7);
    presetCombo->setEditableText (true);
    presetCombo->setJustificationType (Justification::centredLeft);
    presetCombo->setTextWhenNothingSelected (String::empty);
    presetCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetCombo->addListener (this);

    addAndMakeVisible (configButton = new ImageButton ("configButton"));
    configButton->setExplicitFocusOrder (8);
    configButton->addListener (this);

    configButton->setImages (false, true, true,
                             ImageCache::getFromMemory (preferencessystem_png, preferencessystem_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (confighover_png, confighover_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (configpushed_png, configpushed_pngSize), 1.000f, Colour (0x00000000));
    addAndMakeVisible (saveButton = new TextButton ("saveButton"));
    saveButton->setExplicitFocusOrder (9);
    saveButton->setButtonText (TRANS("Save"));
    saveButton->addListener (this);

    addAndMakeVisible (newButton = new TextButton ("newButton"));
    newButton->setExplicitFocusOrder (10);
    newButton->setButtonText (TRANS("New"));
    newButton->addListener (this);

    addAndMakeVisible (deleteButton = new TextButton ("deleteButton"));
    deleteButton->setExplicitFocusOrder (11);
    deleteButton->setButtonText (TRANS("Delete"));
    deleteButton->addListener (this);

    addAndMakeVisible (presetLabel = new Label ("presetLabel",
                                                TRANS("Preset:")));
    presetLabel->setFont (Font (15.00f, Font::plain));
    presetLabel->setJustificationType (Justification::centredLeft);
    presetLabel->setEditable (false, false, false);
    presetLabel->setColour (Label::textColourId, Colours::white);
    presetLabel->setColour (TextEditor::textColourId, Colours::black);
    presetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  configureCombobox(this->presetCombo) ;

    //[/Constructor]
}

Controls::~Controls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    controlsGroup = nullptr;
    screencapToggle = nullptr;
    cameraToggle = nullptr;
    textToggle = nullptr;
    interstitialToggle = nullptr;
    previewToggle = nullptr;
    outputToggle = nullptr;
    presetCombo = nullptr;
    configButton = nullptr;
    saveButton = nullptr;
    newButton = nullptr;
    deleteButton = nullptr;
    presetLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Controls::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff101010));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Controls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    controlsGroup->setBounds (16, 12, getWidth() - 32, 64);
    screencapToggle->setBounds (32, 36, 72, 24);
    cameraToggle->setBounds (108, 36, 76, 24);
    textToggle->setBounds (188, 36, 52, 24);
    interstitialToggle->setBounds (244, 36, 64, 24);
    previewToggle->setBounds (314, 36, 78, 24);
    outputToggle->setBounds (396, 36, 90, 24);
    presetCombo->setBounds (512, 36, 176, 24);
    configButton->setBounds (696, 36, 24, 24);
    saveButton->setBounds (156, 36, 64, 24);
    newButton->setBounds (244, 36, 64, 24);
    deleteButton->setBounds (332, 36, 64, 24);
    presetLabel->setBounds (412, 36, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Controls::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  Identifier key ;
  var        value = var(buttonThatWasClicked->getToggleState()) ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == screencapToggle)
    {
        //[UserButtonCode_screencapToggle] -- add your button handler code here..

      key = CONFIG::IS_SCREENCAP_ON_ID ;

        //[/UserButtonCode_screencapToggle]
    }
    else if (buttonThatWasClicked == cameraToggle)
    {
        //[UserButtonCode_cameraToggle] -- add your button handler code here..

      key = CONFIG::IS_CAMERA_ON_ID ;

        //[/UserButtonCode_cameraToggle]
    }
    else if (buttonThatWasClicked == textToggle)
    {
        //[UserButtonCode_textToggle] -- add your button handler code here..

      key = CONFIG::IS_TEXT_ON_ID ;

        //[/UserButtonCode_textToggle]
    }
    else if (buttonThatWasClicked == interstitialToggle)
    {
        //[UserButtonCode_interstitialToggle] -- add your button handler code here..

      key = CONFIG::IS_INTERSTITIAL_ON_ID ;

        //[/UserButtonCode_interstitialToggle]
    }
    else if (buttonThatWasClicked == previewToggle)
    {
        //[UserButtonCode_previewToggle] -- add your button handler code here..

      key = CONFIG::IS_PREVIEW_ON_ID ;

        //[/UserButtonCode_previewToggle]
    }
    else if (buttonThatWasClicked == outputToggle)
    {
        //[UserButtonCode_outputToggle] -- add your button handler code here..

      key = CONFIG::IS_OUTPUT_ON_ID ;

        //[/UserButtonCode_outputToggle]
    }
    else if (buttonThatWasClicked == configButton)
    {
        //[UserButtonCode_configButton] -- add your button handler code here..

      if (rejectPresetChange()) return ;

      key   = CONFIG::IS_PENDING_ID ;
      value = var(!AvCaster::GetIsConfigPending()) ;

        //[/UserButtonCode_configButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..

      handleSaveButton() ; return ;

        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == newButton)
    {
        //[UserButtonCode_newButton] -- add your button handler code here..

      handleNewButton() ; return ;

        //[/UserButtonCode_newButton]
    }
    else if (buttonThatWasClicked == deleteButton)
    {
        //[UserButtonCode_deleteButton] -- add your button handler code here..

      handleDeleteButton() ; return ;

        //[/UserButtonCode_deleteButton]
    }

    //[UserbuttonClicked_Post]

  AvCaster::GuiChanged(key , value) ;

    //[/UserbuttonClicked_Post]
}

void Controls::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetCombo)
    {
        //[UserComboBoxCode_presetCombo] -- add your combo box handling code here..

      String preset_name = this->presetCombo->getText() ;
      bool   is_saving   = this->saveButton  ->isDown() ; // defer to handleSaveButton()
      bool   is_deleting = this->deleteButton->isDown() ; // defer to handleDeleteButton()

      if (is_deleting) return ;

      if      (isCreatePresetMode()) AvCaster::StorePreset(preset_name) ;
      else if (!is_saving          ) handlePresetCombo() ;

      return ;

        //[/UserComboBoxCode_presetCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Controls::broughtToFront() { toggleControls() ; loadConfig() ; }

void Controls::configureCombobox(ComboBox* a_combobox)
{
  a_combobox->setColour(ComboBox::textColourId       , GUI::TEXT_FG_COLOR) ;
  a_combobox->setColour(ComboBox::backgroundColourId , GUI::TEXT_BG_COLOR) ;
}

void Controls::handleSaveButton()
{
  String preset_name = this->presetCombo->getText() ;

  if (preset_name.isEmpty()) AvCaster::Warning(GUI::PRESET_NAME_ERROR_MSG) ;
  else
  {
    setCreatePresetMode(false) ; AvCaster::StorePreset(preset_name) ;

#ifdef STATIC_PIPELINE
  AvCaster::Warning("Changes will take effect after AvCaster is restarted.") ;
#endif // STATIC_PIPELINE
  }
}

void Controls::handleNewButton()
{
  this->presetCombo ->setText(String::empty , juce::dontSendNotification) ;
  this->presetCombo ->grabKeyboardFocus() ;
  setCreatePresetMode(true) ;
}

void Controls::handleDeleteButton()
{
  if (isCreatePresetMode())
  {
    setCreatePresetMode(false) ;
    this->presetCombo ->setText(AvCaster::GetPresetName() , juce::dontSendNotification) ;
  }
  else if (AvCaster::IsStaticPreset()) AvCaster::ResetPreset() ;
  else                                 AvCaster::DeletePreset() ;
}

void Controls::handlePresetCombo()
{
  Identifier key                  = CONFIG::PRESET_ID ;
  String     preset_name          = this->presetCombo->getText() ;
  int        option_n             = this->presetCombo->getSelectedItemIndex() ;
  int        stored_option_n      = AvCaster::GetPresetIdx() ;
  String     stored_preset_name   = AvCaster::GetPresetName() ;
  bool       is_valid_option      = !!(~option_n) ;
  bool       is_static_preset     = AvCaster::IsStaticPreset() ;
  bool       is_empty             = preset_name.isEmpty() ;
  bool       has_name_changed     = preset_name != stored_preset_name && !is_empty ;
  bool       should_rename_preset = !is_valid_option && has_name_changed && !is_static_preset ;
  bool       should_reset_option  = rejectPresetChange() || should_rename_preset ;
  var        value                = var((is_valid_option) ? option_n : stored_option_n) ;

DEBUG_TRACE_HANDLE_PRESETCOMBO

  // reject empty preset name
  if (!is_valid_option) if (!is_empty) setCreatePresetMode(false) ; else return ;

  // rename preset , restore selection , or commit preset change
  if (should_rename_preset) AvCaster::RenamePreset(preset_name) ;
  if (!should_reset_option) AvCaster::GuiChanged(key , value) ;
  else                      loadConfig() ;
}

void Controls::toggleControls()
{
  bool   is_config_pending = AvCaster::GetIsConfigPending() ;
  String group_text        = (is_config_pending) ? GUI::PRESETS_TEXT : GUI::CONTROLS_TEXT ;

  this->controlsGroup     ->setText(group_text) ;
  this->screencapToggle   ->setVisible(!is_config_pending) ;
  this->cameraToggle      ->setVisible(!is_config_pending) ;
  this->textToggle        ->setVisible(!is_config_pending) ;
  this->interstitialToggle->setVisible(!is_config_pending) ;
  this->previewToggle     ->setVisible(!is_config_pending) ;
  this->outputToggle      ->setVisible(!is_config_pending) ;
  this->saveButton        ->setVisible( is_config_pending) ;
  this->newButton         ->setVisible( is_config_pending) ;
  this->deleteButton      ->setVisible( is_config_pending) ;
  this->presetLabel       ->setVisible( is_config_pending) ;
}

void Controls::loadConfig()
{
  ValueTree   config_store = AvCaster::GetConfigStore() ;
  StringArray preset_names = AvCaster::GetPresetsNames() ;
  int         preset_idx   = AvCaster::GetPresetIdx() ;

  bool is_screencap_on    = bool(config_store[CONFIG::IS_SCREENCAP_ON_ID   ]) ;
  bool is_camera_on       = bool(config_store[CONFIG::IS_CAMERA_ON_ID      ]) ;
  bool is_text_on         = bool(config_store[CONFIG::IS_TEXT_ON_ID        ]) ;
  bool is_interstitial_on = bool(config_store[CONFIG::IS_INTERSTITIAL_ON_ID]) ;
  bool is_preview_on      = bool(config_store[CONFIG::IS_PREVIEW_ON_ID     ]) ;
  bool is_output_on       = bool(config_store[CONFIG::IS_OUTPUT_ON_ID      ]) ;

  this->screencapToggle   ->setToggleState      (is_screencap_on    , juce::dontSendNotification) ;
  this->cameraToggle      ->setToggleState      (is_camera_on       , juce::dontSendNotification) ;
  this->textToggle        ->setToggleState      (is_text_on         , juce::dontSendNotification) ;
  this->interstitialToggle->setToggleState      (is_interstitial_on , juce::dontSendNotification) ;
  this->previewToggle     ->setToggleState      (is_preview_on      , juce::dontSendNotification) ;
  this->outputToggle      ->setToggleState      (is_output_on       , juce::dontSendNotification) ;
  this->presetCombo       ->clear               (juce::dontSendNotification) ;
  this->presetCombo       ->addItemList         (preset_names , 1) ;
  this->presetCombo       ->setSelectedItemIndex(preset_idx , juce::dontSendNotification) ;

  setCreatePresetMode(false) ;

#ifdef DISABLE_CONTROLS_NYI
this->screencapToggle   ->setEnabled(false) ;
this->cameraToggle      ->setEnabled(false) ;
this->textToggle        ->setEnabled(false) ;
this->interstitialToggle->setEnabled(false) ;
#endif // DISABLE_CONTROLS_NYI
}

bool Controls::rejectPresetChange()
{
  bool is_output_active = this->outputToggle->getToggleState() ;

DEBUG_TRACE_REJECT_CONFIG_CHANGE

  if (is_output_active) AvCaster::Warning(GUI::CONFIG_CHANGE_ERROR_MSG) ;

  return is_output_active ;
}

void Controls::setCreatePresetMode(bool is_pending_new_preset_name)
{
  bool   is_static_preset = AvCaster::IsStaticPreset() ;
  String button_text      = (is_pending_new_preset_name) ? GUI::DELETE_BTN_CANCEL_TEXT :
                            (is_static_preset          ) ? GUI::DELETE_BTN_RESET_TEXT  :
                                                           GUI::DELETE_BTN_DELETE_TEXT ;

  this->presetCombo ->setEditableText(is_pending_new_preset_name || !is_static_preset) ;
  this->deleteButton->setButtonText  (button_text) ;
}

bool Controls::isCreatePresetMode()
{
  return this->deleteButton->getButtonText() == GUI::DELETE_BTN_CANCEL_TEXT ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Controls" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="ff101010"/>
  <GROUPCOMPONENT name="controlsGroup" id="5f4ffe47101cb73b" memberName="controlsGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 12 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Controls"/>
  <TOGGLEBUTTON name="screencapToggle" id="ccd6f9830703071b" memberName="screencapToggle"
                virtualName="" explicitFocusOrder="1" pos="32 36 72 24" txtcol="ffffffff"
                buttonText="Screen" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="cameraToggle" id="844fe21cdd50ef0b" memberName="cameraToggle"
                virtualName="" explicitFocusOrder="2" pos="108 36 76 24" txtcol="ffffffff"
                buttonText="Camera" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="textToggle" id="a63786623ec66379" memberName="textToggle"
                virtualName="" explicitFocusOrder="3" pos="188 36 52 24" txtcol="ffffffff"
                buttonText="Text" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="interstitialToggle" id="6a66a5d35080c1cd" memberName="interstitialToggle"
                virtualName="" explicitFocusOrder="4" pos="244 36 64 24" txtcol="ffffffff"
                buttonText="Pause" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="previewToggle" id="692b72b8aa04c022" memberName="previewToggle"
                virtualName="" explicitFocusOrder="5" pos="314 36 78 24" txtcol="ffffffff"
                buttonText="Preview" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="outputToggle" id="22cf1f64bccae1df" memberName="outputToggle"
                virtualName="" explicitFocusOrder="6" pos="396 36 90 24" txtcol="ffffffff"
                buttonText="Broadcast" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="presetCombo" id="94d77976c2b2f37" memberName="presetCombo"
            virtualName="" explicitFocusOrder="7" pos="512 36 176 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <IMAGEBUTTON name="configButton" id="19b48645d13bf310" memberName="configButton"
               virtualName="" explicitFocusOrder="8" pos="696 36 24 24" buttonText="configButton"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="preferencessystem_png" opacityNormal="1" colourNormal="0"
               resourceOver="confighover_png" opacityOver="1" colourOver="0"
               resourceDown="configpushed_png" opacityDown="1" colourDown="0"/>
  <TEXTBUTTON name="saveButton" id="b669a1abab5602e9" memberName="saveButton"
              virtualName="" explicitFocusOrder="9" pos="156 36 64 24" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="newButton" id="693a3f523732acb3" memberName="newButton"
              virtualName="" explicitFocusOrder="10" pos="244 36 64 24" buttonText="New"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="deleteButton" id="846aa62a47585ee2" memberName="deleteButton"
              virtualName="" explicitFocusOrder="11" pos="332 36 64 24" buttonText="Delete"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="presetLabel" id="3a60504146c5134" memberName="presetLabel"
         virtualName="" explicitFocusOrder="0" pos="412 36 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Preset:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: preferencessystem_png, 2129, "../../../home/bill/dl/tango-icon-theme-0.8.90/32x32/categories/preferences-system.png"
static const unsigned char resource_Controls_preferencessystem_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,32,0,0,0,32,8,6,0,0,0,115,122,122,244,0,0,0,4,115,66,73,84,8,8,8,8,124,8,100,
136,0,0,8,8,73,68,65,84,88,133,237,150,107,80,84,231,25,199,255,231,186,247,93,129,101,193,101,65,46,106,21,144,155,58,136,241,66,172,162,226,68,99,106,173,237,76,167,173,218,241,139,83,149,96,65,116,
82,167,41,176,98,117,180,214,100,72,140,153,100,58,109,194,180,90,13,70,136,134,161,157,198,154,78,210,40,226,133,5,21,185,45,236,194,194,46,44,123,238,167,31,194,102,86,5,177,147,15,253,210,103,230,153,
247,125,207,121,159,231,255,123,158,247,157,51,7,248,191,253,143,141,152,110,67,77,77,213,114,154,165,223,7,72,29,8,220,151,5,225,195,96,80,120,235,240,225,195,220,243,138,84,31,127,167,72,3,245,139,146,
146,157,190,255,10,224,200,145,35,38,149,144,2,105,169,179,145,151,187,16,254,64,0,173,183,91,56,239,160,215,205,5,133,130,131,7,15,14,76,39,126,228,196,187,251,21,85,169,161,40,170,91,16,164,229,135,
74,119,62,138,124,79,62,43,184,172,172,108,148,38,169,149,221,61,143,198,253,129,128,226,72,112,96,237,154,245,218,172,204,236,36,131,73,119,254,89,177,117,117,117,212,209,83,239,157,101,117,154,95,45,
46,40,64,98,74,138,157,97,168,127,87,158,120,59,235,185,1,0,160,180,180,252,239,156,40,173,250,228,202,101,82,85,85,94,146,36,100,45,200,166,12,122,195,130,234,163,175,23,78,90,245,145,119,76,15,7,198,
155,76,102,243,214,156,188,69,6,86,163,65,130,195,65,217,29,142,104,82,37,111,214,214,214,50,83,2,84,85,85,197,60,249,172,98,127,197,231,0,252,162,40,246,2,0,207,243,72,77,77,51,176,180,102,203,164,212,
58,234,171,248,248,248,252,172,220,28,3,69,83,0,0,89,145,225,245,122,130,4,65,252,120,215,174,93,226,164,0,78,103,229,90,146,86,7,79,157,58,241,253,200,231,213,199,170,115,1,88,104,154,14,210,52,13,146,
36,97,52,26,9,154,166,83,38,211,39,84,196,204,153,157,162,17,4,1,162,192,67,18,121,180,223,109,227,4,94,108,40,223,187,253,15,145,123,31,3,96,52,204,217,156,236,92,72,138,244,199,218,218,55,94,6,128,154,
154,202,28,66,82,46,205,73,155,251,154,193,96,72,209,104,52,208,106,181,224,56,78,5,224,126,82,220,233,172,181,200,138,60,67,146,68,8,124,8,178,40,96,208,227,81,125,67,222,17,130,147,127,246,228,126,250,
49,0,134,25,74,116,36,217,147,103,165,208,127,189,120,238,188,179,166,18,10,128,204,5,11,78,173,88,86,88,161,170,170,86,146,36,208,52,141,222,222,30,73,20,197,199,10,56,92,91,171,39,56,182,121,254,188,
52,81,149,37,198,239,243,33,20,26,71,95,159,135,32,20,101,83,89,217,206,209,167,186,21,185,56,126,162,166,50,125,126,102,89,110,206,66,138,36,31,191,30,178,44,35,24,12,66,81,20,48,12,3,94,224,209,208,
80,207,9,146,184,109,127,73,249,133,195,181,181,122,109,136,105,202,202,152,147,103,182,152,152,150,86,215,120,32,48,118,23,42,62,133,138,107,229,37,219,47,76,122,92,145,139,202,202,202,56,163,89,239,
218,242,202,86,51,203,178,144,101,25,36,73,130,32,8,72,146,4,138,162,224,243,249,208,218,218,10,155,205,6,91,156,13,13,13,245,28,47,202,27,21,38,246,96,94,230,188,130,168,40,35,123,227,86,251,248,240,
176,255,205,178,189,219,75,39,19,141,52,42,114,209,212,212,20,44,90,183,198,237,114,181,173,115,36,56,104,171,213,10,134,97,192,48,12,100,89,134,63,48,2,69,86,32,138,34,8,226,107,246,244,140,12,218,245,
112,224,71,89,233,223,113,196,217,162,217,214,59,29,33,239,224,200,219,229,251,182,151,76,39,254,84,7,194,118,244,168,115,19,205,210,103,140,6,163,46,198,106,37,131,193,160,226,241,12,208,162,40,106,54,
20,191,164,10,188,72,0,128,170,170,104,117,117,195,26,19,13,251,204,88,180,220,233,224,251,221,222,51,229,251,118,236,126,30,241,41,1,128,175,191,100,15,30,220,75,87,41,34,142,84,136,49,134,209,223,148,
229,208,28,138,97,63,91,91,180,222,32,240,34,113,235,94,39,44,22,11,18,29,241,184,211,246,16,238,158,46,129,87,134,102,31,122,245,80,247,183,6,152,204,146,214,87,165,199,154,177,35,35,129,218,189,98,225,
60,54,198,98,192,172,36,59,218,58,30,129,33,9,36,217,103,40,215,174,127,54,52,62,198,103,84,84,84,120,159,39,231,180,159,226,176,165,110,168,222,174,101,153,127,189,178,110,197,158,144,38,149,250,221,
249,14,24,45,209,232,184,223,13,40,50,210,231,38,33,33,33,145,204,206,202,141,214,25,53,95,58,157,78,203,243,228,165,166,223,2,164,108,168,218,200,178,236,217,31,110,46,212,23,46,76,38,181,122,3,57,60,
202,227,131,198,155,200,77,53,35,63,103,46,104,154,6,207,243,112,56,18,73,89,146,13,254,209,225,205,75,242,11,222,109,110,110,22,159,149,123,90,128,228,226,170,124,154,162,46,110,46,94,166,15,242,42,254,
113,203,141,78,247,48,236,54,11,6,60,126,89,30,119,203,75,114,231,80,0,1,138,162,192,113,28,146,147,83,72,127,192,31,37,138,252,218,252,252,130,247,155,155,155,229,169,242,63,243,8,102,173,175,94,69,145,
212,149,245,171,243,245,10,65,193,235,27,131,251,126,11,186,239,126,142,241,96,16,163,33,62,232,13,138,251,46,55,126,204,41,170,2,69,81,64,146,36,2,129,0,94,40,88,78,199,218,108,57,49,214,25,245,117,117,
117,83,22,58,37,64,90,113,213,46,134,165,62,218,92,188,204,164,213,233,136,62,143,31,195,125,247,16,10,142,32,193,145,136,142,78,175,192,243,194,141,243,167,15,158,86,68,233,229,134,198,75,188,44,75,0,
0,130,32,16,12,6,81,184,98,21,107,54,91,86,14,120,251,254,164,170,234,164,23,254,41,128,185,47,253,214,154,178,193,89,175,51,232,143,253,96,83,161,94,33,41,136,2,143,177,1,23,252,195,62,216,237,9,24,26,
37,133,238,190,129,118,132,212,141,0,80,90,90,222,168,168,202,150,203,141,151,4,94,224,65,16,4,100,89,6,207,243,88,253,221,34,86,171,209,110,60,253,198,201,55,167,5,72,46,174,250,133,4,241,161,221,110,
91,179,109,243,139,6,5,4,28,49,90,244,60,184,13,239,224,32,226,227,227,49,52,70,9,157,61,3,46,112,120,225,193,213,114,127,56,246,213,189,191,172,135,130,109,159,92,185,204,115,28,7,154,166,191,129,88,
245,226,26,13,69,51,63,61,249,251,99,7,158,4,248,166,45,41,197,206,21,172,134,249,40,115,126,154,57,43,35,5,51,244,20,102,70,105,113,238,227,102,116,118,245,32,46,214,10,129,178,72,109,237,189,46,240,
88,26,41,30,105,199,79,30,221,70,168,196,123,171,87,175,101,89,134,69,32,16,192,224,224,32,28,14,7,26,175,92,230,68,94,182,31,56,112,96,248,169,14,168,80,87,197,217,98,76,171,151,206,67,70,146,25,105,
51,77,56,215,120,29,157,143,122,96,54,154,64,234,172,184,215,209,55,42,16,82,209,84,226,0,80,178,103,255,7,36,77,237,188,122,181,81,8,113,33,248,253,126,120,60,30,4,2,1,68,69,69,201,36,169,44,154,226,
8,148,78,45,67,134,76,58,26,93,253,1,156,185,240,5,58,31,118,128,102,52,136,77,72,69,107,91,119,136,31,243,110,237,169,63,228,195,19,255,17,17,221,164,1,104,246,236,222,247,103,158,227,75,154,155,63,21,
162,162,163,144,158,158,14,131,209,128,145,145,97,50,20,18,219,34,131,40,0,44,0,189,42,140,121,57,173,227,231,160,52,218,81,78,66,215,131,54,8,188,128,164,148,185,232,118,251,5,159,183,255,98,79,147,243,
47,0,180,0,52,19,113,228,132,40,11,64,63,225,6,0,134,171,87,155,92,121,121,57,30,119,191,123,249,128,167,95,112,185,238,73,195,195,35,135,94,255,245,111,174,79,232,18,0,20,2,128,101,34,169,214,182,232,
39,43,77,51,231,215,46,93,156,169,229,3,253,0,163,135,66,25,240,229,87,183,199,251,254,249,214,247,120,95,231,32,0,46,194,229,9,151,34,138,97,1,48,225,185,213,106,37,178,179,179,163,219,219,219,123,187,
186,186,2,0,4,0,226,196,200,19,0,76,97,0,0,26,219,226,29,69,6,91,218,81,179,217,32,147,20,67,13,251,252,228,88,207,141,215,6,91,62,252,91,56,104,194,185,136,185,28,33,76,79,192,132,171,84,1,40,17,160,
225,28,66,184,3,68,4,177,14,0,99,76,204,138,54,38,44,89,8,146,212,7,123,91,110,140,62,186,230,137,168,86,136,232,128,56,145,60,242,30,144,19,99,216,213,8,136,240,252,177,128,201,46,83,120,140,124,175,
98,146,4,223,214,254,3,174,151,133,37,87,153,47,161,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* Controls::preferencessystem_png = (const char*) resource_Controls_preferencessystem_png;
const int Controls::preferencessystem_pngSize = 2129;

// JUCER_RESOURCE: confighover_png, 4254, "../../../home/bill/img/config-hover.png"
static const unsigned char resource_Controls_confighover_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,32,0,0,0,32,8,6,0,0,0,115,122,122,244,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,
127,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,223,10,28,2,20,3,203,224,166,93,0,0,16,43,73,68,65,84,88,9,1,32,16,223,239,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,88,
255,255,255,220,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,241,255,255,255,105,
0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,255,255,255,154,0,0,0,41,0,0,0,79,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,23,0,0,0,2,255,255,255,161,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,132,255,255,255,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,49,255,255,255,161,0,0,0,0,4,255,255,255,
49,0,0,0,71,0,0,0,55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,167,167,164,61,3,5,3,162,0,0,2,9,0,1,0,221,254,251,251,169,248,248,252,154,96,96,96,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,165,170,182,70,5,0,255,204,86,86,75,238,0,0,0,0,1,1,1,207,255,255,255,226,255,255,255,83,1,255,255,255,195,0,0,0,139,1,1,1,178,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,167,167,167,13,
255,0,253,242,26,26,27,0,38,37,38,0,244,245,245,0,223,224,222,248,241,241,240,231,250,248,252,57,92,92,92,233,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,167,172,183,117,254,255,255,
138,2,2,2,227,252,252,253,61,93,87,75,225,0,0,0,0,255,255,255,50,0,0,0,161,1,255,255,255,237,0,0,0,23,1,1,1,252,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,169,169,166,62,1,3,1,183,48,47,51,8,21,20,21,2,0,
0,0,0,221,222,220,253,224,224,223,202,84,83,86,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,191,191,191,3,233,239,250,155,3,5,3,86,34,35,36,11,240,240,241,253,234,231,230,241,253,255,253,65,92,84,
76,210,255,255,255,4,0,0,0,237,2,0,0,0,18,1,1,1,252,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,87,90,194,250,252,253,66,204,204,202,2,0,0,0,249,253,253,253,0,35,34,36,3,8,8,9,45,165,168,162,64,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,167,167,182,13,232,239,249,190,10,11,10,86,36,37,39,11,4,5,6,0,20,21,21,3,19,21,21,18,1,255,2,209,179,179,179,5,1,1,1,252,0,0,0,14,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,164,164,164,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,92,88,92,201,0,0,0,241,252,252,252,229,0,0,0,0,250,250,250,0,26,25,26,11,5,3,5,84,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,207,18,18,18,55,34,36,
36,11,2,3,3,0,0,0,0,0,254,255,253,0,240,240,240,245,1,1,0,93,77,77,77,251,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,166,166,164,71,2,3,0,236,174,174,172,85,0,0,0,0,0,0,0,0,0,0,0,0,165,170,165,49,0,0,0,
15,3,3,3,245,3,3,3,0,2,2,2,0,9,9,9,1,3,3,3,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,27,27,25,7,252,252,252,0,253,252,250,0,253,252,250,0,228,225,227,248,252,251,252,184,90,84,74,164,0,0,0,0,
0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,4,5,3,158,36,36,36,0,253,255,253,166,179,179,176,80,0,0,0,0,167,167,164,48,1,253,255,181,28,27,28,126,8,8,8,33,5,5,5,0,6,6,6,0,250,250,250,255,0,0,0,231,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,166,166,179,15,254,254,254,16,253,253,252,0,251,251,249,0,253,252,252,0,241,240,240,255,243,242,240,240,1,250,254,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,
3,4,4,237,22,21,23,26,24,23,25,4,196,197,195,175,166,167,164,0,255,0,0,0,33,33,33,147,46,45,48,122,255,255,255,8,253,253,253,0,3,3,3,0,235,236,235,252,252,252,253,2,0,0,0,0,0,0,0,0,0,0,0,0,160,179,179,
10,1,250,4,192,31,30,26,251,0,254,253,5,245,242,242,0,249,249,249,0,237,237,239,1,1,254,255,79,89,89,75,243,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,255,255,255,255,1,1,1,1,0,0,0,0,170,172,167,133,32,31,33,119,
37,36,39,3,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,254,254,254,0,248,248,248,0,254,254,254,0,4,4,4,0,251,251,251,0,202,202,199,248,251,253,252,88,88,86,90,177,160,179,179,10,6,249,3,190,34,32,28,50,11,11,10,5,
221,223,227,246,246,246,247,215,0,255,0,189,0,255,0,198,90,86,74,177,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,1,255,255,255,255,1,1,1,1,0,0,0,0,164,164,164,23,9,10,7,218,63,62,65,14,4,4,4,0,254,
254,254,0,1,1,1,0,1,1,1,0,253,253,253,0,2,2,2,0,243,243,243,0,223,223,223,0,16,16,16,0,17,18,17,0,202,202,199,248,251,252,254,78,254,4,15,123,38,33,30,57,12,12,9,6,220,223,229,246,244,243,244,151,89,84,
74,116,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,1,255,255,255,255,1,1,1,1,0,0,0,0,0,0,0,0,170,173,169,95,4,3,4,152,54,52,54,8,20,20,21,0,255,255,255,0,0,0,0,0,248,248,248,
0,245,246,244,0,253,252,254,0,236,236,236,0,3,3,3,0,9,9,9,0,9,10,8,0,197,202,210,253,33,31,30,254,18,17,15,5,222,223,228,247,238,239,242,154,90,85,74,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,255,255,255,255,1,255,255,255,255,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,168,168,166,79,3,5,3,156,9,8,9,9,14,15,15,2,248,248,248,254,240,239,238,4,252,252,253,7,56,56,57,255,252,251,253,1,0,
0,0,0,255,255,255,0,223,227,234,0,15,15,14,0,19,18,15,0,222,225,229,249,238,237,241,156,90,85,74,108,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,1,255,255,255,
255,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,191,191,191,3,231,231,226,42,255,2,1,23,2,255,1,244,3,3,7,209,254,254,250,37,2,4,4,197,54,52,55,11,251,251,252,1,222,226,232,0,12,11,11,0,21,21,18,0,225,227,
232,0,237,235,233,250,251,255,242,36,93,86,93,227,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,1,255,255,255,255,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,119,164,42,15,10,0,99,33,21,3,108,46,38,30,6,14,11,8,0,23,22,19,0,227,229,233,0,4,2,1,0,22,19,12,254,213,214,212,237,248,247,250,43,92,92,92,235,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,90,120,165,98,6,4,4,202,62,54,47,111,249,5,25,3,174,195,
229,0,9,11,13,0,229,230,235,0,0,255,254,0,31,28,22,0,21,21,22,2,35,35,36,18,7,9,6,205,166,166,166,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,89,120,164,78,3,5,4,148,66,62,48,11,45,39,26,3,46,41,31,3,24,25,21,0,150,174,207,0,246,248,249,0,37,33,27,0,4,4,4,0,247,247,247,0,31,30,32,3,31,30,31,25,7,
8,4,199,160,160,160,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,88,120,164,55,2,2,3,166,60,54,43,9,244,247,253,
0,180,199,225,0,211,221,235,0,23,21,16,0,7,6,7,253,216,222,227,251,255,0,254,0,255,255,255,0,2,2,2,0,245,245,245,0,37,36,38,4,21,22,23,37,13,14,11,191,160,160,160,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,119,165,66,2,1,3,187,55,51,41,10,254,0,3,0,241,243,247,0,237,230,222,0,235,226,215,0,248,247,248,0,246,249,251,245,240,
247,253,113,201,203,201,248,254,255,254,0,254,254,254,0,2,2,2,0,245,245,245,0,45,43,46,4,16,17,17,48,14,15,12,180,191,191,191,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,90,120,164,103,4,4,2,179,61,55,45,13,6,6,7,1,237,240,244,0,243,237,226,0,250,248,244,0,20,21,21,0,229,233,240,250,251,251,252,208,131,112,92,149,255,252,253,80,202,203,200,249,
254,254,253,0,0,0,0,0,1,1,1,0,247,247,247,0,48,46,49,6,11,10,11,63,239,241,237,167,255,255,255,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,93,122,169,20,89,120,166,180,
7,8,8,141,65,59,48,10,255,2,2,0,252,252,250,0,247,239,228,0,245,243,243,0,19,19,20,0,242,246,2,250,235,236,239,219,0,249,255,78,0,0,0,0,87,87,90,185,255,255,254,84,201,203,200,250,251,251,251,0,1,1,1,
0,254,254,254,0,251,251,251,0,51,51,53,6,6,5,6,78,176,177,173,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,88,120,164,110,253,0,252,223,19,20,16,69,66,60,49,11,255,0,1,0,20,14,
6,0,235,231,224,0,240,241,241,0,18,18,18,0,242,247,2,250,232,235,239,218,0,250,0,59,166,141,90,241,0,0,0,0,0,0,0,0,86,84,89,180,0,254,0,88,203,205,201,249,250,250,250,0,3,3,3,0,254,254,254,0,250,250,250,
0,50,49,52,7,2,3,4,96,173,175,170,121,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,255,255,255,255,1,1,1,1,89,120,166,62,4,5,4,179,33,31,26,14,35,32,25,0,12,7,2,0,18,13,6,0,195,201,208,0,232,233,235,0,17,16,15,0,
252,2,11,252,227,228,236,218,0,251,0,58,166,141,90,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,173,168,88,1,255,1,161,51,51,53,6,5,4,5,0,245,245,245,0,241,241,241,0,21,21,21,0,203,204,201,248,252,
251,254,26,91,91,91,239,0,0,0,0,255,255,255,255,2,0,0,0,0,0,0,0,0,255,0,255,66,18,16,14,13,51,43,30,0,32,22,10,0,26,19,10,0,195,203,214,0,232,232,235,0,11,9,10,0,2,7,15,0,226,229,237,243,251,1,253,70,
166,141,90,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,83,88,168,2,3,2,100,205,205,203,250,249,250,249,0,245,245,245,0,240,240,240,0,246,246,246,0,13,13,13,253,2,2,255,52,0,0,0,0,0,0,0,0,0,
0,0,0,2,0,0,0,0,0,0,0,0,0,0,255,224,6,4,1,247,10,7,3,0,233,238,246,0,181,197,217,0,232,231,229,0,3,4,5,0,15,20,25,0,223,226,234,247,251,247,240,86,235,199,157,238,64,64,64,4,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,64,64,64,1,64,64,64,4,64,64,64,7,147,145,149,172,251,250,251,114,208,208,206,250,13,13,13,0,31,31,31,0,8,9,8,0,244,244,243,2,249,249,252,217,0,0,0,0,0,0,0,0,0,0,0,0,1,250,250,250,239,161,161,161,
42,176,188,206,8,15,35,61,207,48,44,37,15,6,7,6,0,223,221,219,0,249,247,245,0,25,27,30,0,235,238,247,250,235,233,231,176,233,205,163,122,0,0,0,251,0,0,0,250,0,0,0,250,0,0,0,249,0,0,0,254,0,0,0,1,0,0,0,
5,0,0,0,4,0,0,0,5,0,0,0,3,0,0,0,2,92,92,89,88,11,13,13,130,7,7,7,254,250,250,249,1,244,244,245,124,164,162,165,158,0,0,0,251,123,123,123,6,67,67,67,224,1,225,225,225,109,251,251,251,18,100,100,100,160,
17,39,71,63,9,19,31,153,44,39,33,8,251,246,238,0,0,4,7,0,254,2,9,0,218,219,223,246,236,214,180,83,251,242,232,236,0,0,0,248,0,0,0,248,0,0,0,248,0,0,0,253,0,0,0,253,0,0,0,252,0,0,0,3,0,0,0,6,0,0,0,6,0,
0,0,5,0,0,0,6,0,0,0,6,15,15,15,1,35,35,35,18,229,229,229,229,233,233,233,242,0,0,0,250,0,0,0,251,174,174,174,107,8,8,8,233,1,0,0,0,13,228,228,228,155,208,208,208,162,140,140,140,218,17,40,74,70,8,16,26,
139,10,11,9,253,2,2,3,3,243,243,245,2,247,235,220,126,241,221,191,193,0,0,0,250,0,0,0,249,0,0,0,249,0,0,0,248,0,0,0,249,0,0,0,249,0,0,0,253,0,0,0,6,0,0,0,5,0,0,0,4,0,0,0,3,0,0,0,3,0,0,0,1,0,0,0,255,0,
0,0,254,0,0,0,253,0,0,0,252,0,0,0,250,164,164,164,43,24,24,24,103,4,4,4,95,1,0,0,0,1,0,0,0,5,239,239,239,158,242,242,242,228,207,207,207,183,153,166,179,237,9,20,42,51,0,2,1,10,248,235,222,208,246,233,
212,234,0,0,0,253,0,0,0,253,0,0,0,250,0,0,0,248,0,0,0,248,0,0,0,251,192,192,192,254,0,0,0,0,0,0,0,0,64,64,64,1,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,255,0,0,0,255,0,0,0,254,178,178,178,13,13,13,13,101,
0,0,0,44,1,1,1,96,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,87,254,254,254,221,254,254,254,255,253,253,253,255,252,252,252,255,252,252,252,255,252,252,252,255,253,253,253,255,254,254,254,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,239,255,255,255,99,0,0,0,0,0,0,0,0,0,0,0,0,142,119,220,132,34,208,196,92,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* Controls::confighover_png = (const char*) resource_Controls_confighover_png;
const int Controls::confighover_pngSize = 4254;

// JUCER_RESOURCE: configpushed_png, 4254, "../../../home/bill/img/config-pushed.png"
static const unsigned char resource_Controls_configpushed_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,32,0,0,0,32,8,6,0,0,0,115,122,122,244,0,0,0,6,98,75,71,68,0,0,0,0,0,0,249,67,187,
127,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,223,10,28,2,22,54,175,101,0,252,0,0,16,43,73,68,65,84,88,9,1,32,16,223,239,1,0,0,0,0,0,0,0,0,0,0,0,0,181,181,181,88,
203,203,203,132,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,242,
53,53,53,120,75,75,75,151,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,168,168,168,154,216,216,216,231,0,0,0,170,128,128,128,213,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,8,0,0,0,99,40,40,40,54,88,88,88,95,0,0,0,0,0,0,0,0,0,168,168,168,132,128,128,128,120,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,
49,168,168,168,161,0,0,0,0,1,181,181,181,49,203,203,203,154,0,0,0,55,128,128,128,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,103,103,100,61,3,5,3,162,0,0,2,9,0,0,0,221,254,252,251,169,248,248,252,154,160,160,
160,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,101,106,117,70,5,0,0,204,150,150,139,238,0,0,0,0,0,0,0,0,128,128,128,131,53,53,53,208,3,38,38,38,171,0,0,0,135,128,
128,128,216,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,102,102,102,13,0,1,254,218,24,24,25,16,48,47,50,12,19,19,19,29,248,250,249,65,253,255,252,95,47,45,47,168,207,207,207,245,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,102,108,119,117,0,0,255,162,0,3,3,90,48,51,57,174,207,204,198,241,0,0,0,0,64,64,64,241,230,230,230,145,2,0,0,0,42,0,0,0,182,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,154,154,
154,243,3,2,3,63,234,235,233,246,245,246,245,254,21,20,21,0,53,51,54,8,35,33,35,30,9,10,7,175,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,127,127,3,104,110,120,158,5,6,5,127,40,43,43,0,
22,25,24,26,3,3,2,206,99,108,116,46,0,0,0,0,0,0,0,210,0,0,0,30,2,0,0,0,18,128,128,128,252,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,151,151,154,194,250,252,253,66,204,204,201,2,255,255,255,249,253,
253,253,0,34,33,35,3,8,8,8,45,101,104,98,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,102,102,117,13,231,239,249,190,10,10,11,86,36,38,39,11,4,5,5,0,20,21,21,3,20,21,21,18,2,255,1,209,114,114,114,5,128,
128,128,252,0,0,0,14,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100,100,100,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,156,152,156,201,0,0,0,241,253,253,253,229,0,0,0,0,251,251,251,0,25,25,27,11,4,3,5,84,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,207,18,18,18,55,34,37,36,11,2,3,2,0,0,0,0,0,254,254,254,0,240,241,239,245,1,1,1,93,142,142,142,251,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,102,102,99,71,2,3,255,236,110,
110,108,85,0,0,0,0,0,0,0,0,0,0,0,0,101,105,101,49,0,0,0,15,3,3,3,245,3,3,3,0,2,2,2,0,9,9,9,1,3,3,3,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,255,0,19,28,27,24,7,252,252,251,0,252,251,251,0,253,252,
251,0,228,226,227,248,252,250,253,184,154,148,138,164,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,3,5,4,158,36,35,37,0,253,254,253,166,114,114,112,80,0,0,0,0,103,103,99,48,1,253,254,181,27,26,29,
126,8,8,8,33,6,6,6,0,6,6,6,0,250,250,250,255,0,0,0,231,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,102,102,114,15,254,255,253,16,253,253,253,0,251,250,250,0,254,253,252,0,241,240,240,255,243,241,240,240,0,250,253,
97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,237,21,21,23,26,24,24,25,4,196,197,194,175,102,103,99,0,255,0,0,0,33,34,34,147,46,45,48,122,255,255,255,8,253,253,253,0,3,3,3,0,236,236,
235,252,253,252,252,2,0,0,0,0,0,0,0,0,0,0,0,0,96,114,114,10,0,250,5,192,31,30,26,251,255,254,253,5,245,243,242,0,249,249,249,0,237,237,239,1,0,254,255,79,154,154,139,243,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,4,0,0,0,0,0,0,0,0,0,0,0,0,253,253,252,179,235,235,233,42,36,36,38,3,74,73,77,0,0,0,0,0,0,0,0,0,0,0,0,109,249,249,249,0,247,247,247,0,255,255,255,0,4,4,4,0,38,38,39,5,202,202,238,89,104,106,102,177,152,
150,154,177,96,114,114,10,6,250,4,190,34,32,27,43,11,11,10,5,221,223,227,246,246,246,247,215,0,255,0,189,0,255,0,198,154,150,139,202,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,249,
247,252,146,226,228,227,108,33,33,35,14,2,2,2,0,254,254,254,0,1,1,1,0,1,1,1,0,255,255,255,0,10,10,10,0,243,243,243,0,217,217,217,0,16,16,16,0,54,53,57,8,202,202,199,168,102,105,102,78,255,250,4,123,36,
33,30,49,13,13,9,5,220,222,228,246,246,246,247,151,154,148,138,116,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,157,157,157,233,254,254,254,110,195,196,193,
248,244,244,243,0,9,9,9,0,8,8,8,0,7,7,7,0,2,2,2,0,245,246,244,0,255,255,255,0,12,12,12,0,255,255,255,0,247,247,247,0,54,54,56,8,1,3,12,183,35,32,27,58,16,16,12,6,225,226,231,247,243,243,245,155,154,148,
138,116,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,150,148,151,161,104,104,102,240,199,200,198,156,9,9,9,9,14,15,15,2,248,247,247,254,239,
240,239,4,253,252,252,7,56,56,58,255,12,12,12,1,0,0,0,0,0,0,0,0,214,218,226,0,32,30,30,3,18,17,15,3,222,225,229,249,238,239,241,158,154,149,139,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,152,152,154,177,20,19,22,24,242,241,239,57,227,228,225,78,236,235,235,68,1,255,3,17,2,1,0,47,204,205,203,245,6,7,6,255,2,2,2,0,224,
228,234,0,12,12,11,0,19,19,16,0,225,227,231,0,240,237,236,1,253,254,238,137,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,129,129,129,253,0,0,0,211,0,0,0,211,0,0,0,0,0,0,0,0,22,55,100,252,16,10,252,154,220,233,199,108,47,38,30,6,14,12,10,0,22,21,18,0,227,229,233,0,6,4,3,0,47,44,37,4,213,214,211,205,100,100,
100,43,156,156,156,235,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,56,101,98,6,4,4,202,
61,54,47,111,250,6,26,3,173,196,229,0,9,11,13,0,229,230,234,0,0,255,254,0,31,28,22,0,20,20,21,2,35,35,37,18,7,9,5,205,102,102,102,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,56,100,78,4,5,4,148,67,61,48,11,46,39,26,3,46,41,31,3,25,25,21,0,150,174,207,0,246,248,250,0,37,33,27,0,4,4,4,0,247,247,
247,0,31,30,32,3,31,29,32,25,6,8,4,199,96,96,96,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,55,100,55,2,2,2,
166,59,53,43,9,244,248,253,0,180,199,225,0,211,221,235,0,23,20,17,0,6,6,7,253,215,221,227,251,255,0,254,0,254,254,254,0,3,3,3,0,245,245,245,0,36,36,37,4,22,22,23,37,13,14,11,191,96,96,96,6,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,55,101,66,2,2,2,187,55,50,42,10,255,1,2,0,240,243,247,0,237,230,222,0,234,226,214,0,248,248,248,
0,247,249,251,245,241,248,252,113,201,202,201,248,255,0,255,0,254,254,254,0,2,2,2,0,246,246,246,0,44,42,45,4,16,16,16,48,14,15,12,180,127,127,127,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26,55,100,103,4,4,2,179,61,55,45,13,6,7,6,1,236,240,245,0,244,236,226,0,249,248,244,0,21,21,22,0,229,232,240,250,250,251,251,208,195,176,157,149,255,253,253,
80,202,202,200,249,254,254,253,0,0,0,0,0,1,1,1,0,248,248,248,0,48,47,50,6,10,10,11,63,239,240,237,167,191,191,191,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,58,105,
20,25,56,102,180,7,9,8,141,65,59,48,10,254,2,3,0,252,252,251,0,247,239,228,0,244,244,242,0,20,19,20,0,241,246,2,250,234,237,239,219,0,249,0,78,0,0,0,0,151,151,154,185,254,0,254,84,201,203,200,250,250,
251,250,0,0,0,0,0,254,254,254,0,251,251,251,0,51,50,52,6,6,6,6,78,176,176,173,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,24,55,100,110,253,0,252,223,19,20,16,69,66,60,48,11,
255,0,1,0,21,14,6,0,235,230,224,0,241,241,241,0,18,18,18,0,242,247,2,250,232,235,238,218,0,250,0,59,231,205,154,241,0,0,0,0,0,0,0,0,151,148,153,180,0,254,0,88,204,204,202,249,250,250,250,0,3,3,3,0,253,
253,253,0,251,251,251,0,49,48,51,7,2,3,3,96,108,111,105,121,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,25,55,102,62,5,6,5,131,37,33,31,12,52,47,38,6,9,7,3,0,36,26,13,0,216,216,217,0,235,237,239,
0,16,15,15,0,250,255,8,252,232,235,240,220,0,250,0,60,231,205,154,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,150,150,152,175,255,0,255,96,204,205,202,250,247,248,247,0,253,253,253,0,242,242,242,0,228,228,228,
0,45,44,47,7,253,251,254,126,101,101,101,17,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,255,0,255,66,17,16,15,13,51,44,30,0,33,23,11,0,27,19,9,0,195,203,214,0,232,233,235,0,10,9,9,0,2,6,15,0,226,229,236,
243,252,1,253,70,231,205,154,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,150,148,152,168,1,3,2,100,205,205,203,250,250,250,250,0,245,245,245,0,239,239,239,0,245,245,245,0,12,13,13,253,1,1,254,
52,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,254,224,6,4,1,247,10,6,3,0,233,238,245,0,181,197,217,0,232,231,229,0,3,4,5,0,16,20,26,0,223,227,234,247,250,247,241,86,235,199,157,238,0,0,0,4,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,4,0,0,0,7,148,145,149,172,251,250,250,114,208,208,205,250,12,13,12,0,32,32,32,0,9,9,9,0,244,244,243,2,250,250,253,217,0,0,0,0,0,0,0,0,0,0,0,0,3,60,60,60,112,255,255,
255,162,225,221,216,229,250,6,22,101,0,3,5,8,246,249,253,0,233,231,228,0,252,250,251,0,22,25,28,0,234,237,244,250,242,241,239,178,236,207,166,173,0,0,0,8,0,0,0,7,0,0,0,6,0,0,0,2,0,0,0,4,0,0,0,6,0,0,0,
10,0,0,0,10,0,0,0,11,0,0,0,11,205,205,207,218,37,37,36,234,237,239,238,61,239,239,237,250,227,228,226,252,244,244,245,124,162,161,163,200,0,0,0,3,82,82,82,12,22,22,22,105,4,32,32,32,126,236,236,236,102,
195,195,152,160,5,16,31,110,208,212,0,153,44,39,33,8,17,13,9,0,0,17,16,0,255,2,5,0,237,238,239,252,239,218,187,159,0,0,0,17,0,0,0,248,0,0,0,248,0,0,0,248,0,0,0,7,0,0,0,253,0,0,0,252,0,0,0,3,0,0,0,6,0,
0,0,6,0,0,0,5,0,0,0,6,165,165,168,189,15,15,15,190,35,35,35,18,228,228,228,229,234,234,234,242,0,0,0,6,0,0,0,1,34,34,34,107,46,46,46,116,3,178,178,178,215,95,95,95,98,4,4,4,231,210,198,182,208,3,11,23,
221,238,244,252,65,247,252,0,248,244,246,252,253,230,230,235,253,247,235,221,127,246,233,212,216,0,0,0,251,0,0,0,251,0,0,0,252,0,0,0,251,0,0,0,250,0,0,0,248,0,0,0,250,0,0,0,0,0,0,0,255,0,0,0,254,0,0,0,
252,0,0,0,251,0,0,0,247,249,249,249,245,231,231,231,235,245,245,245,246,0,0,0,251,0,0,0,250,110,110,110,42,52,52,52,70,87,87,87,125,1,0,0,0,1,0,0,0,5,155,155,155,158,209,209,209,228,223,223,223,183,190,
203,215,237,9,20,42,51,0,1,2,10,248,236,221,208,246,233,213,234,0,0,0,253,0,0,0,253,0,0,0,250,0,0,0,248,0,0,0,248,0,0,0,251,0,0,0,254,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,255,
0,0,0,255,0,0,0,254,119,119,119,13,9,9,9,101,40,40,40,44,88,88,88,96,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,181,181,181,87,202,202,202,134,0,0,0,34,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,53,53,53,116,75,75,75,157,0,0,0,0,0,0,0,0,22,82,238,110,38,194,229,141,0,0,
0,0,73,69,78,68,174,66,96,130,0,0};

const char* Controls::configpushed_png = (const char*) resource_Controls_configpushed_png;
const int Controls::configpushed_pngSize = 4254;


//[EndFile] You can add extra defines here...
//[/EndFile]
