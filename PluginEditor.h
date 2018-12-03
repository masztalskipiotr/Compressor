/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CompressorAudioProcessorEditor : public AudioProcessorEditor,
									   public Button::Listener
{
public:
	CompressorAudioProcessorEditor(CompressorAudioProcessor&);
	~CompressorAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	//void setSliderInvisible();
	void buttonClicked(Button* button) override; 
	
private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	CompressorAudioProcessor& processor;

	Image potOfGoldImage;

	Slider makeUpGainSlider;
	Slider compressionSlider;

	Label makeUpGainSliderLabel;
	Label compressionSliderLabel;

	TextButton makeUpGainSelectorButton;

	ComboBox compressionModeSelectorBox;

	AudioProcessorValueTreeState::SliderAttachment makeUpGainSliderAttachment;
	AudioProcessorValueTreeState::SliderAttachment compressionSliderAttachment;

	AudioProcessorValueTreeState::ButtonAttachment makeUpGainSelectorButtonAttachment;

	AudioProcessorValueTreeState::ComboBoxAttachment compressionModeSelectorBoxAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorAudioProcessorEditor)
};

