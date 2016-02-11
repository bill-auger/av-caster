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
#include "Trace/TraceConfig.h"

//[/Headers]

#include "Config.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Config::Config (MainContent* main_content)
    : mainContent(main_content)
{
    addAndMakeVisible (configGroup = new GroupComponent ("configGroup",
                                                         TRANS("Configuration")));
    configGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    configGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (screenButton = new TextButton ("screenButton"));
    screenButton->setExplicitFocusOrder (1);
    screenButton->setButtonText (TRANS("Screen"));
    screenButton->setConnectedEdges (Button::ConnectedOnBottom);

    addAndMakeVisible (cameraButton = new TextButton ("cameraButton"));
    cameraButton->setExplicitFocusOrder (2);
    cameraButton->setButtonText (TRANS("Camera"));
    cameraButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);

    addAndMakeVisible (audioButton = new TextButton ("audioButton"));
    audioButton->setExplicitFocusOrder (3);
    audioButton->setButtonText (TRANS("Audio"));
    audioButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);

    addAndMakeVisible (textButton = new TextButton ("textButton"));
    textButton->setExplicitFocusOrder (4);
    textButton->setButtonText (TRANS("Text"));
    textButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);

    addAndMakeVisible (imageButton = new TextButton ("imageButton"));
    imageButton->setExplicitFocusOrder (5);
    imageButton->setButtonText (TRANS("Image"));
    imageButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);

    addAndMakeVisible (outputButton = new TextButton ("outputButton"));
    outputButton->setExplicitFocusOrder (6);
    outputButton->setButtonText (TRANS("Output"));
    outputButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);

    addAndMakeVisible (chatButton = new TextButton ("chatButton"));
    chatButton->setExplicitFocusOrder (7);
    chatButton->setButtonText (TRANS("Chat"));
    chatButton->setConnectedEdges (Button::ConnectedOnTop);

    addAndMakeVisible (configPaneGroup = new GroupComponent ("configPaneGroup",
                                                             TRANS("Screen")));
    configPaneGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    configPaneGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (configScreen = new ConfigScreen());
    configScreen->setName ("configScreen");

    addAndMakeVisible (configCamera = new ConfigCamera());
    configCamera->setName ("configCamera");

    addAndMakeVisible (configAudio = new ConfigAudio());
    configAudio->setName ("configAudio");

    addAndMakeVisible (configText = new ConfigText());
    configText->setName ("configText");

    addAndMakeVisible (configImage = new ConfigImage());
    configImage->setName ("configImage");

    addAndMakeVisible (configOutput = new ConfigOutput());
    configOutput->setName ("configOutput");

    addAndMakeVisible (configChat = new ConfigChat());
    configChat->setName ("configChat");

    addAndMakeVisible (configSpacer = new Component());
    configSpacer->setName ("configSpacer");

    addAndMakeVisible (hintsGroup = new GroupComponent ("hintsGroup",
                                                        TRANS("Hints")));
    hintsGroup->setColour (GroupComponent::outlineColourId, Colours::white);
    hintsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (hintsText = new TextEditor ("hintsText"));
    hintsText->setMultiLine (true);
    hintsText->setReturnKeyStartsNewLine (false);
    hintsText->setReadOnly (true);
    hintsText->setScrollbarsShown (true);
    hintsText->setCaretVisible (false);
    hintsText->setPopupMenuEnabled (false);
    hintsText->setColour (TextEditor::textColourId, Colours::white);
    hintsText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    hintsText->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    hintsText->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    hintsText->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    hintsText->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1, 1);


    //[Constructor] You can add your own custom stuff here..

  // establish local handles to child Component widgets
  this->displaySlider     = this->configScreen->displaySlider ;
  this->screenSlider      = this->configScreen->screenSlider ;
  this->screenWidthText   = this->configScreen->screenWidthText ;
  this->screenHeightText  = this->configScreen->screenHeightText ;
  this->xOffsetText       = this->configScreen->xOffsetText ;
  this->yOffsetText       = this->configScreen->yOffsetText ;
  this->cameraDevCombo    = this->configCamera->cameraDevCombo ;
  this->cameraResCombo    = this->configCamera->cameraResCombo ;
  this->audioApiCombo     = this->configAudio ->audioApiCombo ;
  this->audioDevCombo     = this->configAudio ->audioDevCombo ;
  this->audioCodecCombo   = this->configAudio ->audioCodecCombo ;
  this->nChannelsSlider   = this->configAudio ->nChannelsSlider ;
  this->samplerateCombo   = this->configAudio ->samplerateCombo ;
  this->audioBitrateCombo = this->configAudio ->audioBitrateCombo ;
  this->motdText          = this->configText  ->motdText ;
  this->textStyleCombo    = this->configText  ->textStyleCombo ;
  this->textPosCombo      = this->configText  ->textPosCombo ;
  this->interstitialText  = this->configImage ->interstitialText ;
  this->browseButton      = this->configImage ->browseButton ;
  this->outputSinkCombo   = this->configOutput->outputSinkCombo ;
  this->outputWidthText   = this->configOutput->outputWidthText ;
  this->outputHeightText  = this->configOutput->outputHeightText ;
  this->framerateCombo    = this->configOutput->framerateCombo ;
  this->videoBitrateCombo = this->configOutput->videoBitrateCombo ;
  this->outputDestLabel   = this->configOutput->outputDestLabel ;
  this->outputDestText    = this->configOutput->outputDestText ;
  this->serverButton      = this->configChat  ->serverButton ;
  this->hostCombo         = this->configChat  ->hostCombo ;
  this->portText          = this->configChat  ->portText ;
  this->nickText          = this->configChat  ->nickText ;
  this->passText          = this->configChat  ->passText ;
  this->channelText       = this->configChat  ->channelText ;
  this->greetingText      = this->configChat  ->greetingText ;
  this->joinPartToggle    = this->configChat  ->joinPartToggle ;

  // configure
  Button    ::Listener* this_button_listener   = static_cast<Button    ::Listener*>(this) ;
  Slider    ::Listener* this_slider_listener   = static_cast<Slider    ::Listener*>(this) ;
  TextEditor::Listener* this_text_listener     = static_cast<TextEditor::Listener*>(this) ;
  ComboBox  ::Listener* this_combobox_listener = static_cast<ComboBox  ::Listener*>(this) ;
  this->mainContent->configureButton(this->screenButton   , this_button_listener) ;
  this->mainContent->configureButton(this->cameraButton   , this_button_listener) ;
  this->mainContent->configureButton(this->audioButton    , this_button_listener) ;
  this->mainContent->configureButton(this->textButton     , this_button_listener) ;
  this->mainContent->configureButton(this->imageButton    , this_button_listener) ;
  this->mainContent->configureButton(this->outputButton   , this_button_listener) ;
  this->mainContent->configureButton(this->chatButton     , this_button_listener) ;
  this->mainContent->configureButton(this->browseButton   , this_button_listener) ;
  this->mainContent->configureButton(this->serverButton   , this_button_listener) ;
  this->mainContent->configureButton(this->joinPartToggle , this_button_listener) ;
  this->mainContent->configureSlider(this->displaySlider   , this_slider_listener ,
                                     GUI::MIN_DISPLAY_N    , GUI::MAX_DISPLAY_N   , 1.0) ;
  this->mainContent->configureSlider(this->screenSlider    , this_slider_listener ,
                                     GUI::MIN_SCREEN_N     , GUI::MAX_SCREEN_N    , 1.0) ;
  this->mainContent->configureSlider(this->nChannelsSlider , this_slider_listener ,
                                     GUI::MIN_N_CHANNELS   , GUI::MAX_N_CHANNELS  , 1.0) ;
  this->mainContent->configureTextEditor(this->screenWidthText  , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->screenHeightText , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->xOffsetText      , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->yOffsetText      , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->motdText         , this_text_listener   ,
                                         GUI::MAX_MOTD_LEN      , ""                   ) ;
  this->mainContent->configureTextEditor(this->interstitialText , this_text_listener   ,
                                         GUI::MAX_FILENAME_LEN  , APP::VALID_ID_CHARS  ) ;
  this->mainContent->configureTextEditor(this->hintsText        , this_text_listener   ,
                                         0                      , String::empty        ) ;
  this->mainContent->configureTextEditor(this->outputWidthText  , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->outputHeightText , this_text_listener   ,
                                         GUI::MAX_RES_N_CHARS   , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->outputDestText   , this_text_listener   ,
                                         GUI::MAX_FILENAME_LEN  , APP::VALID_URI_CHARS ) ;
  this->mainContent->configureTextEditor(this->portText         , this_text_listener   ,
                                         GUI::MAX_PORT_N_CHARS  , APP::DIGITS          ) ;
  this->mainContent->configureTextEditor(this->nickText         , this_text_listener   ,
                                         GUI::MAX_FILENAME_LEN  , APP::VALID_NICK_CHARS) ;
  this->mainContent->configureTextEditor(this->passText         , this_text_listener   ,
                                         GUI::MAX_MOTD_LEN      , ""                   ) ;
  this->mainContent->configureTextEditor(this->channelText      , this_text_listener   ,
                                         GUI::MAX_FILENAME_LEN  , APP::VALID_NICK_CHARS) ;
  this->mainContent->configureTextEditor(this->greetingText     , this_text_listener   ,
                                         GUI::MAX_MOTD_LEN      , ""                   ) ;
  this->mainContent->configureCombobox(this->cameraDevCombo    , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->cameraResCombo    , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->audioApiCombo     , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->audioDevCombo     , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->audioCodecCombo   , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->samplerateCombo   , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->audioBitrateCombo , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->textStyleCombo    , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->textPosCombo      , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->outputSinkCombo   , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->framerateCombo    , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->videoBitrateCombo , this_combobox_listener) ;
  this->mainContent->configureCombobox(this->hostCombo         , this_combobox_listener) ;

  // NOTE: configSpacer is a non-functional dummy - most siblings bounds are coupled to it
  configSpacer   ->toBack() ;
  configPaneGroup->setText(GUI::SCREEN_GROUP_TEXT) ;

  updateVisibility(static_cast<Component*>(this->configScreen)) ;

    //[/Constructor]
}

Config::~Config()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    configGroup = nullptr;
    screenButton = nullptr;
    cameraButton = nullptr;
    audioButton = nullptr;
    textButton = nullptr;
    imageButton = nullptr;
    outputButton = nullptr;
    chatButton = nullptr;
    configPaneGroup = nullptr;
    configScreen = nullptr;
    configCamera = nullptr;
    configAudio = nullptr;
    configText = nullptr;
    configImage = nullptr;
    configOutput = nullptr;
    configChat = nullptr;
    configSpacer = nullptr;
    hintsGroup = nullptr;
    hintsText = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Config::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff282828));
    g.fillRoundedRectangle (18.0f, 14.0f, static_cast<float> (getWidth() - 36), static_cast<float> (getHeight() - 32), 5.000f);

    g.setColour (Colour (0xff404040));
    g.fillRoundedRectangle (194.0f, 30.0f, static_cast<float> (getWidth() - 226), static_cast<float> (getHeight() - 66), 4.000f);

    g.setColour (Colour (0xff585858));
    g.fillRoundedRectangle (204.0f, 298.0f, static_cast<float> (getWidth() - 246), static_cast<float> (getHeight() - 342), 4.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Config::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    configGroup->setBounds (16, 4, getWidth() - 32, getHeight() - 20);
    screenButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.0000f), 150, roundFloatToInt (252 * 0.1429f));
    cameraButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.1429f), 150, roundFloatToInt (252 * 0.1429f));
    audioButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.2857f), 150, roundFloatToInt (252 * 0.1429f));
    textButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.4286f), 150, roundFloatToInt (252 * 0.1429f));
    imageButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.5714f), 150, roundFloatToInt (252 * 0.1429f));
    outputButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.7143f), 150, roundFloatToInt (252 * 0.1429f));
    chatButton->setBounds (16 + 16, ((4 + 16) + 16) + roundFloatToInt (252 * 0.8571f), 150, roundFloatToInt (252 * 0.1429f));
    configPaneGroup->setBounds (16 + 174, 4 + 16, (getWidth() - 32) - 186, roundFloatToInt ((getHeight() - 20) * 0.9534f));
    configScreen->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configCamera->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configAudio->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configText->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configImage->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configOutput->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configChat->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 0, (((getWidth() - 32) - 186) - 24) - 0, 252 - 0);
    configSpacer->setBounds ((16 + 174) + 12, (4 + 16) + 16, ((getWidth() - 32) - 186) - 24, 252);
    hintsGroup->setBounds (((16 + 174) + 12) + 0, ((4 + 16) + 16) + 252, (((getWidth() - 32) - 186) - 24) - 0, (roundFloatToInt ((getHeight() - 20) * 0.9534f)) - 278);
    hintsText->setBounds ((((16 + 174) + 12) + 0) + 14, (((4 + 16) + 16) + 252) + 20, ((((getWidth() - 32) - 186) - 24) - 0) - 28, ((roundFloatToInt ((getHeight() - 20) * 0.9534f)) - 278) - 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Config::broughtToFront() { loadConfig() ;
/* FIXME: testing
hostCombo->clear               (juce::dontSendNotification) ;
hostCombo->addItemList         (AvCaster::GetPresetsNames() , 1) ;
hostCombo->setSelectedItemIndex(0 , juce::dontSendNotification) ;
*/
}

void Config::sliderValueChanged(Slider* a_slider)
{
  Identifier key ;
  var        value = var((int)a_slider->getValue()) ;

  if      (a_slider == displaySlider  ) key = CONFIG::DISPLAY_N_ID ;
  else if (a_slider == screenSlider   ) key = CONFIG::SCREEN_N_ID ;
  else if (a_slider == nChannelsSlider) key = CONFIG::N_CHANNELS_ID ;

  AvCaster::SetConfig(key , value) ;
}

void Config::comboBoxChanged(ComboBox* a_combobox)
{
  int        option_n    = a_combobox->getSelectedItemIndex() ;
  int        default_idx ;
  Identifier key ;
  var        value ;

  if      (a_combobox == this->cameraDevCombo)
  {
    key         = CONFIG::CAMERA_DEVICE_ID ;
    default_idx = CONFIG::DEFAULT_CAMERA_DEVICE_IDX ;
  }
  else if (a_combobox == this->cameraResCombo)
  {
    key         = CONFIG::CAMERA_RES_ID ;
    default_idx = CONFIG::DEFAULT_CAMERA_RES_IDX ;
  }
  else if (a_combobox == this->audioApiCombo)
  {
    key         = CONFIG::AUDIO_API_ID ;
    default_idx = CONFIG::DEFAULT_AUDIO_API_IDX ;
  }
  else if (a_combobox == this->audioDevCombo)
  {
    key         = CONFIG::AUDIO_DEVICE_ID ;
    default_idx = CONFIG::DEFAULT_AUDIO_DEVICE_IDX ;
  }
  else if (a_combobox == this->audioCodecCombo)
  {
    key         = CONFIG::AUDIO_CODEC_ID ;
    default_idx = CONFIG::DEFAULT_AUDIO_CODEC_IDX ;
  }
  else if (a_combobox == this->samplerateCombo)
  {
    key         = CONFIG::SAMPLERATE_ID ;
    default_idx = CONFIG::DEFAULT_SAMPLERATE_IDX ;
  }
  else if (a_combobox == this->audioBitrateCombo)
  {
    key         = CONFIG::AUDIO_BITRATE_ID ;
    default_idx = CONFIG::DEFAULT_AUDIO_BITRATE_IDX ;
  }
  else if (a_combobox == this->textStyleCombo)
  {
    key         = CONFIG::TEXT_STYLE_ID ;
    default_idx = CONFIG::DEFAULT_TEXT_STYLE_IDX ;
  }
  else if (a_combobox == this->textPosCombo)
  {
    key         = CONFIG::TEXT_POSITION_ID ;
    default_idx = CONFIG::DEFAULT_TEXT_POSITION_IDX ;
  }
  else if (a_combobox == this->outputSinkCombo)
  {
    key         = CONFIG::OUTPUT_SINK_ID ;
    default_idx = CONFIG::DEFAULT_OUTPUT_SINK_IDX ;
  }
  else if (a_combobox == this->framerateCombo)
  {
    key         = CONFIG::FRAMERATE_ID ;
    default_idx = CONFIG::DEFAULT_FRAMERATE_IDX ;
  }
  else if (a_combobox == this->videoBitrateCombo)
  {
    key         = CONFIG::VIDEO_BITRATE_ID ;
    default_idx = CONFIG::DEFAULT_VIDEO_BITRATE_IDX ;
  }
  else if (a_combobox == this->hostCombo)
  {
// TODO: nyi
DBG("Config::comboBoxChanged() hostCombo option_n=" + String(option_n) + " text=" + a_combobox->getText()) ;
if (!(~option_n))
{
DBG("Config::comboBoxChanged() hostCombo text changed=" + a_combobox->getText()) ;
// TODO: validate: GUI::MAX_FILENAME_LEN  , APP::VALID_URI_CHARS ) ;
}
    return ;
//     key         = CONFIG::HOST_ID ;
//     default_idx = CONFIG::DEFAULT_HOST_IDX ;
  }
  else return ;

  value = var((~option_n) ? option_n : default_idx) ;
  a_combobox->setSelectedItemIndex(int(value) , juce::dontSendNotification) ;
  AvCaster::SetConfig(key , value) ;
}

void Config::buttonClicked(Button* a_button)
{
  Component* config_component = nullptr ; // local buttons
  String     config_group_text ;          // local buttons
  Identifier key ;                        // child buttons
  var        value ;                      // child buttons

  // Config buttons
  if      (a_button == screenButton)
  {
    config_component  = static_cast<Component*>(this->configScreen) ;
    config_group_text = GUI::SCREEN_GROUP_TEXT ;
  }
  else if (a_button == cameraButton)
  {
    config_component = static_cast<Component*>(this->configCamera) ;
    config_group_text = GUI::CAMERA_GROUP_TEXT ;
  }
  else if (a_button == audioButton)
  {
    config_component = static_cast<Component*>(this->configAudio) ;
    config_group_text = GUI::AUDIO_GROUP_TEXT ;
  }
  else if (a_button == textButton)
  {
    config_component = static_cast<Component*>(this->configText) ;
    config_group_text = GUI::TEXT_GROUP_TEXT ;
  }
  else if (a_button == imageButton)
  {
    config_component = static_cast<Component*>(this->configImage) ;
    config_group_text = GUI::IMAGE_GROUP_TEXT ;
  }
  else if (a_button == outputButton)
  {
    config_component = static_cast<Component*>(this->configOutput) ;
    config_group_text = GUI::OUTPUT_GROUP_TEXT ;
  }
  else if (a_button == chatButton)
  {
    config_component = static_cast<Component*>(this->configChat) ;
    config_group_text = GUI::CHAT_GROUP_TEXT ;
  }
  // Image buttons
  else if (a_button == browseButton)
  {
    FileChooser           file_chooser(GUI::IMAGE_CHOOSER_TEXT  , APP::PICTURES_DIR ,
                                       GUI::IMG_FILE_EXTENSIONS , false             ) ;
    ImagePreviewComponent image_preview ;
//     image_preview.setSize(GUI::IMG_PREVIEW_W , GUI::IMG_PREVIEW_H) ; // NFG

    if (!file_chooser.browseForFileToOpen(&image_preview)) return ;

    String image_loc = file_chooser.getResult().getFullPathName() ;

    key   = CONFIG::IMAGE_LOC_ID ;
    value = var(image_loc) ;
  }
  // Chat buttons
  else if (a_button == serverButton) { DBG("Config::buttonClicked() serverButton") ; return ; } // TODO: nyi
  else if (a_button == joinPartToggle)
  {
    key   = CONFIG::JOINPART_ID ;
    value = var(a_button->getToggleState()) ;
  }

  if (config_component != nullptr)        // local buttons
  {
    configPaneGroup->setText(config_group_text) ;
    updateVisibility(config_component) ;
  }
  else AvCaster::SetConfig(key , value) ; // child buttons
}

void Config::textEditorTextChanged(TextEditor& a_text_editor)
{
  if (&a_text_editor == this->outputDestText) validateOutputDest() ;
}

void Config::textEditorFocusLost(TextEditor& a_text_editor)
{
  TextEditor* ed      = &a_text_editor ;
  var         str_val = var(ed->getText()) ;
  var         int_val = var(ed->getText().getIntValue()) ;
  Identifier  key ;
  var         value ;

  if      (ed == this->screenWidthText ) { key = CONFIG::SCREENCAP_W_ID ;  value = int_val ; }
  else if (ed == this->screenHeightText) { key = CONFIG::SCREENCAP_H_ID ;  value = int_val ; }
  else if (ed == this->xOffsetText     ) { key = CONFIG::OFFSET_X_ID ;     value = int_val ; }
  else if (ed == this->yOffsetText     ) { key = CONFIG::OFFSET_Y_ID ;     value = int_val ; }
  else if (ed == this->motdText        ) { key = CONFIG::MOTD_TEXT_ID ;    value = str_val ; }
  else if (ed == this->interstitialText) { key = CONFIG::IMAGE_LOC_ID ;    value = str_val ; }
  else if (ed == this->outputWidthText ) { key = CONFIG::OUTPUT_W_ID ;     value = int_val ; }
  else if (ed == this->outputHeightText) { key = CONFIG::OUTPUT_H_ID ;     value = int_val ; }
  else if (ed == this->outputDestText  ) { key = CONFIG::OUTPUT_DEST_ID ;  value = str_val ; }
  else                                   return ;

  AvCaster::SetConfig(key , value) ;
}

void Config::loadConfig()
{
  ValueTree   config_store       = AvCaster::GetConfigStore() ;
  StringArray camera_devices     = AvCaster::GetCameraNames() ;
  StringArray camera_resolutions = AvCaster::GetCameraResolutions() ;
  StringArray audio_devices      = AvCaster::GetAudioNames() ;

DEBUG_TRACE_CONFIG_LOAD_CONFIG

  double display_n         = double(config_store[CONFIG::DISPLAY_N_ID    ]) ;
  double screen_n          = double(config_store[CONFIG::SCREEN_N_ID     ]) ;
  String screencap_w       = STRING(config_store[CONFIG::SCREENCAP_W_ID  ]) ;
  String screencap_h       = STRING(config_store[CONFIG::SCREENCAP_H_ID  ]) ;
  String offset_x          = STRING(config_store[CONFIG::OFFSET_X_ID     ]) ;
  String offset_y          = STRING(config_store[CONFIG::OFFSET_Y_ID     ]) ;
  int    camera_dev_idx    = int   (config_store[CONFIG::CAMERA_DEVICE_ID]) ;
  int    camera_res_idx    = int   (config_store[CONFIG::CAMERA_RES_ID   ]) ;
  int    audio_api_idx     = int   (config_store[CONFIG::AUDIO_API_ID    ]) ;
  int    audio_dev_idx     = int   (config_store[CONFIG::AUDIO_DEVICE_ID ]) ;
  int    audio_codec_idx   = int   (config_store[CONFIG::AUDIO_CODEC_ID  ]) ;
  double n_channels        = double(config_store[CONFIG::N_CHANNELS_ID   ]) ;
  int    samplerate_idx    = int   (config_store[CONFIG::SAMPLERATE_ID   ]) ;
  int    audio_bitrate_idx = int   (config_store[CONFIG::AUDIO_BITRATE_ID]) ;
  int    text_style_idx    = int   (config_store[CONFIG::TEXT_STYLE_ID   ]) ;
  int    text_pos_idx      = int   (config_store[CONFIG::TEXT_POSITION_ID]) ;
  String motd_text         = STRING(config_store[CONFIG::MOTD_TEXT_ID    ]) ;
  String interstitial_text = STRING(config_store[CONFIG::IMAGE_LOC_ID    ]) ;
  int    output_idx        = int   (config_store[CONFIG::OUTPUT_SINK_ID  ]) ;
  String output_w_text     = STRING(config_store[CONFIG::OUTPUT_W_ID     ]) ;
  String output_h_text     = STRING(config_store[CONFIG::OUTPUT_H_ID     ]) ;
  int    framerate_idx     = int   (config_store[CONFIG::FRAMERATE_ID    ]) ;
  int    video_bitrate_idx = int   (config_store[CONFIG::VIDEO_BITRATE_ID]) ;
  String output_dest_text  = STRING(config_store[CONFIG::OUTPUT_DEST_ID  ]) ;
  bool   is_lctv_preset    = AvCaster::GetPresetIdx() == CONFIG::LCTV_PRESET_IDX ;
  String output_label_text = (is_lctv_preset                       ) ? GUI::DEST_LCTV_TEXT :
                             (output_idx == CONFIG::FILE_OUTPUT_IDX) ? GUI::DEST_FILE_TEXT :
                             (output_idx == CONFIG::RTMP_OUTPUT_IDX) ? GUI::DEST_RTMP_TEXT :
                                                                       "ERR"               ;

  this->displaySlider    ->setValue            (display_n ) ;
  this->screenSlider     ->setValue            (screen_n  ) ;
  this->nChannelsSlider  ->setValue            (n_channels) ;
  this->screenWidthText  ->setText             (screencap_w      ) ;
  this->screenHeightText ->setText             (screencap_h      ) ;
  this->xOffsetText      ->setText             (offset_x         ) ;
  this->yOffsetText      ->setText             (offset_y         ) ;
  this->motdText         ->setText             (motd_text        ) ;
  this->interstitialText ->setText             (interstitial_text) ;
  this->outputWidthText  ->setText             (output_w_text    ) ;
  this->outputHeightText ->setText             (output_h_text    ) ;
  this->outputDestText   ->setText             (output_dest_text ) ;
  this->outputDestLabel  ->setText             (output_label_text , juce::dontSendNotification) ;
  this->cameraDevCombo   ->clear               (juce::dontSendNotification) ;
  this->cameraResCombo   ->clear               (juce::dontSendNotification) ;
  this->audioDevCombo    ->clear               (juce::dontSendNotification) ;
  this->audioApiCombo    ->clear               (juce::dontSendNotification) ;
  this->audioCodecCombo  ->clear               (juce::dontSendNotification) ;
  this->samplerateCombo  ->clear               (juce::dontSendNotification) ;
  this->audioBitrateCombo->clear               (juce::dontSendNotification) ;
  this->textStyleCombo   ->clear               (juce::dontSendNotification) ;
  this->textPosCombo     ->clear               (juce::dontSendNotification) ;
  this->outputSinkCombo  ->clear               (juce::dontSendNotification) ;
  this->framerateCombo   ->clear               (juce::dontSendNotification) ;
  this->videoBitrateCombo->clear               (juce::dontSendNotification) ;
  this->cameraDevCombo   ->addItemList         (camera_devices            , 1) ;
  this->cameraResCombo   ->addItemList         (camera_resolutions        , 1) ;
  this->audioApiCombo    ->addItemList         (CONFIG::AUDIO_APIS        , 1) ;
  this->audioDevCombo    ->addItemList         (audio_devices             , 1) ;
  this->audioCodecCombo  ->addItemList         (CONFIG::AUDIO_CODECS      , 1) ;
  this->samplerateCombo  ->addItemList         (CONFIG::AUDIO_SAMPLERATES , 1) ;
  this->audioBitrateCombo->addItemList         (CONFIG::AUDIO_BITRATES    , 1) ;
  this->textStyleCombo   ->addItemList         (CONFIG::TEXT_STYLES       , 1) ;
  this->textPosCombo     ->addItemList         (CONFIG::TEXT_POSITIONS    , 1) ;
  this->outputSinkCombo  ->addItemList         (CONFIG::OUTPUT_SINKS      , 1) ;
  this->framerateCombo   ->addItemList         (CONFIG::FRAMERATES        , 1) ;
  this->videoBitrateCombo->addItemList         (CONFIG::VIDEO_BITRATES    , 1) ;
  this->cameraDevCombo   ->setSelectedItemIndex(camera_dev_idx    , juce::dontSendNotification) ;
  this->cameraResCombo   ->setSelectedItemIndex(camera_res_idx    , juce::dontSendNotification) ;
  this->audioApiCombo    ->setSelectedItemIndex(audio_api_idx     , juce::dontSendNotification) ;
  this->audioDevCombo    ->setSelectedItemIndex(audio_dev_idx     , juce::dontSendNotification) ;
  this->audioCodecCombo  ->setSelectedItemIndex(audio_codec_idx   , juce::dontSendNotification) ;
  this->samplerateCombo  ->setSelectedItemIndex(samplerate_idx    , juce::dontSendNotification) ;
  this->audioBitrateCombo->setSelectedItemIndex(audio_bitrate_idx , juce::dontSendNotification) ;
  this->textStyleCombo   ->setSelectedItemIndex(text_style_idx    , juce::dontSendNotification) ;
  this->textPosCombo     ->setSelectedItemIndex(text_pos_idx      , juce::dontSendNotification) ;
  this->outputSinkCombo  ->setSelectedItemIndex(output_idx        , juce::dontSendNotification) ;
  this->framerateCombo   ->setSelectedItemIndex(framerate_idx     , juce::dontSendNotification) ;
  this->videoBitrateCombo->setSelectedItemIndex(video_bitrate_idx , juce::dontSendNotification) ;

  enableComponents() ;
}

void Config::enableComponents()
{
  bool is_static_preset = AvCaster::IsStaticPreset() ;

  this->audioCodecCombo->setEnabled(!is_static_preset) ; // TODO: videoCodecCombo
  this->outputSinkCombo->setEnabled(!is_static_preset) ; // TODO: outputMuxerCombo

#ifdef DISABLE_GUI_CONFIG_NYI
this->displaySlider   ->setEnabled(false) ;
this->screenSlider    ->setEnabled(false) ;
this->xOffsetText     ->setEnabled(false) ;
this->yOffsetText     ->setEnabled(false) ;
this->cameraResCombo  ->setEnabled(false) ;
this->audioDevCombo   ->setEnabled(false) ;
this->audioCodecCombo ->setEnabled(false) ;
this->motdText        ->setEnabled(false) ;
this->textStyleCombo  ->setEnabled(false) ;
this->textPosCombo    ->setEnabled(false) ;
this->interstitialText->setEnabled(false) ;
this->browseButton    ->setEnabled(false) ;
#endif // DISABLE_GUI_CONFIG_NYI
}

void Config::updateVisibility(Component* config_component)
{
  configAudio     ->setVisible(false) ;
  configCamera    ->setVisible(false) ;
  configChat      ->setVisible(false) ;
  configImage     ->setVisible(false) ;
  configOutput    ->setVisible(false) ;
  configScreen    ->setVisible(false) ;
  configText      ->setVisible(false) ;
  configSpacer    ->setVisible(false) ;
  config_component->setVisible(true ) ;
}

bool Config::validateOutputDest()
{
  String dest_text = this->outputDestText->getText()  ;
  bool   is_valid  = dest_text.containsOnly(APP::VALID_URI_CHARS) ;
  Colour fg_color  = (is_valid) ? GUI::TEXT_NORMAL_COLOR : GUI::TEXT_INVALID_COLOR ;
  Colour bg_color  = (is_valid) ? GUI::TEXT_BG_COLOR     : GUI::TEXT_INVALID_BG_COLOR ;

  this->outputDestText->setText  (dest_text.trim()) ;
  this->outputDestText->setColour(ComboBox::textColourId       , fg_color) ;
  this->outputDestText->setColour(ComboBox::backgroundColourId , bg_color) ;

  return is_valid ;
}

bool Config::validateConfigGui()
{
  bool is_sane = validateOutputDest() ;

  return is_sane ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Config" componentName=""
                 parentClasses="public Component, public Button::Listener, public Slider::Listener, public TextEditor::Listener, public ComboBox::Listener"
                 constructorParams="MainContent* main_content" variableInitialisers="mainContent(main_content)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1" initialHeight="1">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="18 14 36M 32M" cornerSize="5" fill="solid: ff282828" hasStroke="0"/>
    <ROUNDRECT pos="194 30 226M 66M" cornerSize="4" fill="solid: ff404040" hasStroke="0"/>
    <ROUNDRECT pos="204 298 246M 342M" cornerSize="4" fill="solid: ff585858"
               hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="configGroup" id="6607ba656d5c8919" memberName="configGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 4 32M 20M" outlinecol="ffffffff"
                  textcol="ffffffff" title="Configuration"/>
  <TEXTBUTTON name="screenButton" id="100ccdbe8e5db3ab" memberName="screenButton"
              virtualName="" explicitFocusOrder="1" pos="16 0% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Screen" connectedEdges="8" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="cameraButton" id="a4094321ed5d0e5e" memberName="cameraButton"
              virtualName="" explicitFocusOrder="2" pos="16 14.286% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Camera" connectedEdges="12" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="audioButton" id="7b29583a640ebd35" memberName="audioButton"
              virtualName="" explicitFocusOrder="3" pos="16 28.571% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Audio" connectedEdges="12" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="textButton" id="b042999a8c4d0ee5" memberName="textButton"
              virtualName="" explicitFocusOrder="4" pos="16 42.857% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Text" connectedEdges="12" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="imageButton" id="3d8666e0ed316005" memberName="imageButton"
              virtualName="" explicitFocusOrder="5" pos="16 57.143% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Image" connectedEdges="12" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="outputButton" id="3068eaa718dd476b" memberName="outputButton"
              virtualName="" explicitFocusOrder="6" pos="16 71.429% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Output" connectedEdges="12" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="chatButton" id="6e15e064df96f39b" memberName="chatButton"
              virtualName="" explicitFocusOrder="7" pos="16 85.714% 150 14.286%"
              posRelativeX="6607ba656d5c8919" posRelativeY="7ab6ee7eab27ae3e"
              posRelativeW="6607ba656d5c8919" posRelativeH="7ab6ee7eab27ae3e"
              buttonText="Chat" connectedEdges="4" needsCallback="0" radioGroupId="0"/>
  <GROUPCOMPONENT name="configPaneGroup" id="3d078232c622c691" memberName="configPaneGroup"
                  virtualName="" explicitFocusOrder="0" pos="174 16 186M 95.335%"
                  posRelativeX="6607ba656d5c8919" posRelativeY="6607ba656d5c8919"
                  posRelativeW="6607ba656d5c8919" posRelativeH="6607ba656d5c8919"
                  outlinecol="ffffffff" textcol="ffffffff" title="Screen"/>
  <GENERICCOMPONENT name="configScreen" id="e89c0f3c223ab737" memberName="configScreen"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigScreen" params=""/>
  <GENERICCOMPONENT name="configCamera" id="eb987e4a398d67b3" memberName="configCamera"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigCamera" params=""/>
  <GENERICCOMPONENT name="configAudio" id="a97a529009013839" memberName="configAudio"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigAudio" params=""/>
  <GENERICCOMPONENT name="configText" id="46d2ff75060de9b1" memberName="configText"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigText" params=""/>
  <GENERICCOMPONENT name="configImage" id="df20966cb9e5cfa1" memberName="configImage"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigImage" params=""/>
  <GENERICCOMPONENT name="configOutput" id="dbe527be33400926" memberName="configOutput"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigOutput" params=""/>
  <GENERICCOMPONENT name="configChat" id="6363efd2d63fdee4" memberName="configChat"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" posRelativeX="7ab6ee7eab27ae3e"
                    posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                    posRelativeH="7ab6ee7eab27ae3e" class="ConfigChat" params=""/>
  <GENERICCOMPONENT name="configSpacer" id="7ab6ee7eab27ae3e" memberName="configSpacer"
                    virtualName="" explicitFocusOrder="0" pos="12 16 24M 252" posRelativeX="3d078232c622c691"
                    posRelativeY="3d078232c622c691" posRelativeW="3d078232c622c691"
                    posRelativeH="6607ba656d5c8919" class="Component" params=""/>
  <GROUPCOMPONENT name="hintsGroup" id="2ef603e605c1ac5d" memberName="hintsGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 252 0M 278M" posRelativeX="7ab6ee7eab27ae3e"
                  posRelativeY="7ab6ee7eab27ae3e" posRelativeW="7ab6ee7eab27ae3e"
                  posRelativeH="3d078232c622c691" outlinecol="ffffffff" textcol="ffffffff"
                  title="Hints"/>
  <TEXTEDITOR name="hintsText" id="f3411ac6aaf06395" memberName="hintsText"
              virtualName="" explicitFocusOrder="0" pos="14 20 28M 32M" posRelativeX="2ef603e605c1ac5d"
              posRelativeY="2ef603e605c1ac5d" posRelativeW="2ef603e605c1ac5d"
              posRelativeH="2ef603e605c1ac5d" textcol="ffffffff" bkgcol="0"
              hilitecol="0" outlinecol="0" shadowcol="0" initialText="" multiline="1"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
