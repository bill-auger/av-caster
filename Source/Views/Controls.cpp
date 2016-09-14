/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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
#include "../Trace/TraceControls.h"

//[/Headers]

#include "Controls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Controls::Controls (MainContent* main_content)
    : mainContent(main_content)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (controlsGroup = new GroupComponent ("controlsGroup",
                                                           TRANS("Controls")));
    controlsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    controlsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (screenToggle = new ToggleButton ("screenToggle"));
    screenToggle->setExplicitFocusOrder (1);
    screenToggle->setButtonText (TRANS("Screen"));
    screenToggle->addListener (this);
    screenToggle->setColour (ToggleButton::textColourId, Colours::white);

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

    addAndMakeVisible (imageToggle = new ToggleButton ("imageToggle"));
    imageToggle->setExplicitFocusOrder (4);
    imageToggle->setButtonText (TRANS("Pause"));
    imageToggle->addListener (this);
    imageToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (previewToggle = new ToggleButton ("previewToggle"));
    previewToggle->setExplicitFocusOrder (5);
    previewToggle->setButtonText (TRANS("Preview"));
    previewToggle->addListener (this);
    previewToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (audioToggle = new ToggleButton ("audioToggle"));
    audioToggle->setExplicitFocusOrder (6);
    audioToggle->setButtonText (TRANS("Audio"));
    audioToggle->addListener (this);
    audioToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (outputToggle = new ToggleButton ("outputToggle"));
    outputToggle->setExplicitFocusOrder (7);
    outputToggle->setButtonText (TRANS("Transmit"));
    outputToggle->addListener (this);
    outputToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (presetsCombo = new ComboBox ("presetsCombo"));
    presetsCombo->setExplicitFocusOrder (8);
    presetsCombo->setEditableText (true);
    presetsCombo->setJustificationType (Justification::centredLeft);
    presetsCombo->setTextWhenNothingSelected (String());
    presetsCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetsCombo->addListener (this);

    addAndMakeVisible (configButton = new ImageButton ("configButton"));
    configButton->setExplicitFocusOrder (9);
    configButton->addListener (this);

    configButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::config_png, BinaryData::config_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::confighover_png, BinaryData::confighover_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::configpushed_png, BinaryData::configpushed_pngSize), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  this->mainContent->configureCombobox(this->presetsCombo) ;

    //[/Constructor]
}

Controls::~Controls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    controlsGroup = nullptr;
    screenToggle = nullptr;
    cameraToggle = nullptr;
    textToggle = nullptr;
    imageToggle = nullptr;
    previewToggle = nullptr;
    audioToggle = nullptr;
    outputToggle = nullptr;
    presetsCombo = nullptr;
    configButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Controls::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff282828));
    g.fillRoundedRectangle (20.0f, 22.0f, static_cast<float> (getWidth() - 40), 52.0f, 4.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Controls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    controlsGroup->setBounds (16, 12, getWidth() - 32, 64);
    screenToggle->setBounds (32, 36, 72, 24);
    cameraToggle->setBounds (108, 36, 76, 24);
    textToggle->setBounds (188, 36, 52, 24);
    imageToggle->setBounds (244, 36, 64, 24);
    previewToggle->setBounds (314, 36, 78, 24);
    audioToggle->setBounds (396, 36, 64, 24);
    outputToggle->setBounds (464, 36, 90, 24);
    presetsCombo->setBounds (560, 36, 128, 24);
    configButton->setBounds (696, 36, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Controls::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

  Identifier key ;
  var        value = var(buttonThatWasClicked->getToggleState()) ;

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == screenToggle)
    {
        //[UserButtonCode_screenToggle] -- add your button handler code here..

      key = CONFIG::SCREEN_ID ;

        //[/UserButtonCode_screenToggle]
    }
    else if (buttonThatWasClicked == cameraToggle)
    {
        //[UserButtonCode_cameraToggle] -- add your button handler code here..

      key = CONFIG::CAMERA_ID ;

        //[/UserButtonCode_cameraToggle]
    }
    else if (buttonThatWasClicked == textToggle)
    {
        //[UserButtonCode_textToggle] -- add your button handler code here..

      key = CONFIG::TEXT_ID ;

        //[/UserButtonCode_textToggle]
    }
    else if (buttonThatWasClicked == imageToggle)
    {
        //[UserButtonCode_imageToggle] -- add your button handler code here..

      key = CONFIG::IMAGE_ID ;

        //[/UserButtonCode_imageToggle]
    }
    else if (buttonThatWasClicked == previewToggle)
    {
        //[UserButtonCode_previewToggle] -- add your button handler code here..

      key = CONFIG::PREVIEW_ID ;

        //[/UserButtonCode_previewToggle]
    }
    else if (buttonThatWasClicked == audioToggle)
    {
        //[UserButtonCode_audioToggle] -- add your button handler code here..

      key = CONFIG::AUDIO_ID ;

        //[/UserButtonCode_audioToggle]
    }
    else if (buttonThatWasClicked == outputToggle)
    {
        //[UserButtonCode_outputToggle] -- add your button handler code here..

      key = CONFIG::OUTPUT_ID ;

        //[/UserButtonCode_outputToggle]
    }
    else if (buttonThatWasClicked == configButton)
    {
        //[UserButtonCode_configButton] -- add your button handler code here..

      key   = CONFIG::IS_PENDING_ID ;
      value = var(true) ;

        //[/UserButtonCode_configButton]
    }

    //[UserbuttonClicked_Post]

  AvCaster::SetValue(key , value) ;

    //[/UserbuttonClicked_Post]
}

void Controls::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetsCombo)
    {
        //[UserComboBoxCode_presetsCombo] -- add your combo box handling code here..

      handlePresetsCombo() ; return ;

        //[/UserComboBoxCode_presetsCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Controls::broughtToFront() { loadConfig() ; }

void Controls::initialize(ValueTree config_store , NamedValueSet& disabled_features)
{
  this->configStore = config_store ;

  // disable controls per cli args
  this->screenToggle ->setEnabled(!disabled_features.contains(CONFIG::SCREEN_ID )) ;
  this->cameraToggle ->setEnabled(!disabled_features.contains(CONFIG::CAMERA_ID )) ;
  this->textToggle   ->setEnabled(!disabled_features.contains(CONFIG::TEXT_ID   )) ;
  this->imageToggle  ->setEnabled(!disabled_features.contains(CONFIG::IMAGE_ID  )) ;
  this->previewToggle->setEnabled(!disabled_features.contains(CONFIG::PREVIEW_ID)) ;
  this->audioToggle  ->setEnabled(!disabled_features.contains(CONFIG::AUDIO_ID  )) ;
  this->outputToggle ->setEnabled(!disabled_features.contains(CONFIG::OUTPUT_ID )) ;
}

void Controls::loadConfig()
{
  bool   is_screen_active   = bool(this->configStore[CONFIG::SCREEN_ID     ]) ;
  bool   is_camera_active   = bool(this->configStore[CONFIG::CAMERA_ID     ]) ;
  bool   is_text_active     = bool(this->configStore[CONFIG::TEXT_ID       ]) ;
  bool   is_image_active    = bool(this->configStore[CONFIG::IMAGE_ID      ]) ;
  bool   is_preview_active  = bool(this->configStore[CONFIG::PREVIEW_ID    ]) ;
  bool   is_audio_active    = bool(this->configStore[CONFIG::AUDIO_ID      ]) ;
  bool   is_output_active   = bool(this->configStore[CONFIG::OUTPUT_ID     ]) ;
  int    sink_idx           = int (this->configStore[CONFIG::OUTPUT_SINK_ID]) ;
  Colour screen_text_color  = this->mainContent->btnTextColor(is_screen_active ) ;
  Colour screen_tick_color  = this->mainContent->btnTickColor(is_screen_active ) ;
  Colour camera_text_color  = this->mainContent->btnTextColor(is_camera_active ) ;
  Colour camera_tick_color  = this->mainContent->btnTickColor(is_camera_active ) ;
  Colour text_text_color    = this->mainContent->btnTextColor(is_text_active   ) ;
  Colour text_tick_color    = this->mainContent->btnTickColor(is_text_active   ) ;
  Colour image_text_color   = this->mainContent->btnTextColor(is_image_active  ) ;
  Colour image_tick_color   = this->mainContent->btnTickColor(is_image_active  ) ;
  Colour preview_text_color = this->mainContent->btnTextColor(is_preview_active) ;
  Colour preview_tick_color = this->mainContent->btnTickColor(is_preview_active) ;
  Colour audio_text_color   = this->mainContent->btnTextColor(is_audio_active  ) ;
  Colour audio_tick_color   = this->mainContent->btnTickColor(is_audio_active  ) ;
  Colour output_text_color  = this->mainContent->btnTextColor(is_output_active ) ;
  Colour output_tick_color  = this->mainContent->btnTickColor(is_output_active ) ;
  String xmit_btn_text      = (sink_idx == CONFIG::FILE_OUTPUT_IDX) ? GUI::FILE_XMIT_TEXT :
                              (sink_idx == CONFIG::RTMP_OUTPUT_IDX) ? GUI::RTMP_XMIT_TEXT :
                                                                      String::empty       ;

DEBUG_TRACE_CONTROLS_LOAD_CONFIG

  this->screenToggle ->setToggleState  (is_screen_active  , juce::dontSendNotification) ;
  this->cameraToggle ->setToggleState  (is_camera_active  , juce::dontSendNotification) ;
  this->textToggle   ->setToggleState  (is_text_active    , juce::dontSendNotification) ;
  this->imageToggle  ->setToggleState  (is_image_active   , juce::dontSendNotification) ;
  this->previewToggle->setToggleState  (is_preview_active , juce::dontSendNotification) ;
  this->audioToggle  ->setToggleState  (is_audio_active   , juce::dontSendNotification) ;
  this->outputToggle ->setToggleState  (is_output_active  , juce::dontSendNotification) ;
  this->screenToggle ->setColour       (ToggleButton::textColourId , screen_text_color ) ;
  this->screenToggle ->setColour       (ToggleButton::tickColourId , screen_tick_color ) ;
  this->cameraToggle ->setColour       (ToggleButton::textColourId , camera_text_color ) ;
  this->cameraToggle ->setColour       (ToggleButton::tickColourId , camera_tick_color ) ;
  this->textToggle   ->setColour       (ToggleButton::textColourId , text_text_color   ) ;
  this->textToggle   ->setColour       (ToggleButton::tickColourId , text_tick_color   ) ;
  this->imageToggle  ->setColour       (ToggleButton::textColourId , image_text_color  ) ;
  this->imageToggle  ->setColour       (ToggleButton::tickColourId , image_tick_color  ) ;
  this->previewToggle->setColour       (ToggleButton::textColourId , preview_text_color) ;
  this->previewToggle->setColour       (ToggleButton::tickColourId , preview_tick_color) ;
  this->outputToggle ->setColour       (ToggleButton::textColourId , output_text_color ) ;
  this->outputToggle ->setColour       (ToggleButton::tickColourId , output_tick_color ) ;
  this->outputToggle ->setButtonText   (xmit_btn_text) ;
  this->mainContent  ->loadPresetsCombo(this->presetsCombo) ;
  this->presetsCombo ->setEditableText (false) ;
}

void Controls::handlePresetsCombo()
{
  int option_n = this->presetsCombo->getSelectedItemIndex() ;

  // should loadConfig() asynchronously
  AvCaster::SetValue(CONFIG::PRESET_ID , option_n) ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Controls" componentName=""
                 parentClasses="public Component" constructorParams="MainContent* main_content"
                 variableInitialisers="mainContent(main_content)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="20 22 40M 52" cornerSize="4" fill="solid: ff282828" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="controlsGroup" id="5f4ffe47101cb73b" memberName="controlsGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 12 32M 64" outlinecol="ffffffff"
                  textcol="ffffffff" title="Controls"/>
  <TOGGLEBUTTON name="screenToggle" id="ccd6f9830703071b" memberName="screenToggle"
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
  <TOGGLEBUTTON name="imageToggle" id="6a66a5d35080c1cd" memberName="imageToggle"
                virtualName="" explicitFocusOrder="4" pos="244 36 64 24" txtcol="ffffffff"
                buttonText="Pause" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="previewToggle" id="692b72b8aa04c022" memberName="previewToggle"
                virtualName="" explicitFocusOrder="5" pos="314 36 78 24" txtcol="ffffffff"
                buttonText="Preview" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="audioToggle" id="36486443d32175e6" memberName="audioToggle"
                virtualName="" explicitFocusOrder="6" pos="396 36 64 24" txtcol="ffffffff"
                buttonText="Audio" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="outputToggle" id="22cf1f64bccae1df" memberName="outputToggle"
                virtualName="" explicitFocusOrder="7" pos="464 36 90 24" txtcol="ffffffff"
                buttonText="Transmit" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="presetsCombo" id="94d77976c2b2f37" memberName="presetsCombo"
            virtualName="" explicitFocusOrder="8" pos="560 36 128 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <IMAGEBUTTON name="configButton" id="19b48645d13bf310" memberName="configButton"
               virtualName="" explicitFocusOrder="9" pos="696 36 24 24" buttonText="configButton"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::config_png" opacityNormal="1" colourNormal="0"
               resourceOver="BinaryData::confighover_png" opacityOver="1" colourOver="0"
               resourceDown="BinaryData::configpushed_png" opacityDown="1" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
