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


#ifndef _CONFIG_H_
#define _CONFIG_H_

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "Constants.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  Config is the presets configuration GUI for the AvCaster application.
  It has it controls for setting the stream parameters.
                                                                    //[/Comments]
*/
class Config  : public Component,
                public TextEditor::Listener,
                public SliderListener,
                public ComboBoxListener,
                public ButtonListener
{
public:
    //==============================================================================
    Config ();
    ~Config();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  void broughtToFront() override ;
  void textEditorFocusLost(TextEditor& a_text_editor) override ;

  void configureSlider    (Slider* a_slider) ;
  void configureTextEditor(TextEditor*  a_text_editor , int max_n_chars ,
                           const String allowed_chars                   ) ;
  void configureCombobox  (ComboBox* a_combobox) ;
  void loadConfig         () ;
  void enableComponents   () ;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> screenGroup;
    ScopedPointer<Label> displayLabel;
    ScopedPointer<Slider> displaySlider;
    ScopedPointer<Label> screenLabel;
    ScopedPointer<Slider> screenSlider;
    ScopedPointer<Label> screenWidthLabel;
    ScopedPointer<TextEditor> screenWidthText;
    ScopedPointer<Label> screenHeightLabel;
    ScopedPointer<TextEditor> screenHeightText;
    ScopedPointer<Label> xOffsetLabel;
    ScopedPointer<TextEditor> xOffsetText;
    ScopedPointer<Label> yOffsetLabel;
    ScopedPointer<TextEditor> yOffsetText;
    ScopedPointer<GroupComponent> cameraGroup;
    ScopedPointer<Label> cameraDevLabel;
    ScopedPointer<ComboBox> cameraDevCombo;
    ScopedPointer<Label> cameraResLabel;
    ScopedPointer<ComboBox> cameraResCombo;
    ScopedPointer<GroupComponent> audioGroup;
    ScopedPointer<Label> audioApiLabel;
    ScopedPointer<ComboBox> audioApiCombo;
    ScopedPointer<Label> audioDevLabel;
    ScopedPointer<ComboBox> audioDevCombo;
    ScopedPointer<Label> audioCodecLabel;
    ScopedPointer<ComboBox> audioCodecCombo;
    ScopedPointer<Label> nChannelsLabel;
    ScopedPointer<Slider> nChannelsSlider;
    ScopedPointer<Label> samplerateLabel;
    ScopedPointer<ComboBox> samplerateCombo;
    ScopedPointer<Label> audioBitrateLabel;
    ScopedPointer<ComboBox> audioBitrateCombo;
    ScopedPointer<GroupComponent> textGroup;
    ScopedPointer<Label> motdLabel;
    ScopedPointer<TextEditor> motdText;
    ScopedPointer<Label> textStyleLabel;
    ScopedPointer<ComboBox> textStyleCombo;
    ScopedPointer<Label> textPosLabel;
    ScopedPointer<ComboBox> textPosCombo;
    ScopedPointer<GroupComponent> interstitialGroup;
    ScopedPointer<Label> locationLabel;
    ScopedPointer<TextEditor> interstitialText;
    ScopedPointer<TextButton> browseButton;
    ScopedPointer<GroupComponent> outputGroup;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // _CONFIG_H_
