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
class CompressorAudioProcessorEditor : public AudioProcessorEditor
{
public:
	CompressorAudioProcessorEditor(CompressorAudioProcessor&);
	~CompressorAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	CompressorAudioProcessor& processor;

	//Slider thresholdSlider;
	//Slider ratioSlider;
	Slider attackSlider;
	Slider releaseSlider;
	Slider makeUpGainSlider;
	Slider compressionSlider;

	//Label thresholdSliderLabel;
	//Label ratioSliderLabel;
	Label attackSliderLabel;
	Label releaseSliderLabel;
	Label makeUpGainSliderLabel;
	Label compressionSliderLabel;

	TextButton makeUpGainSelectorButton;

	//AudioProcessorValueTreeState::SliderAttachment thresholdSliderAttachment;
	//AudioProcessorValueTreeState::SliderAttachment ratioSliderAttachment;
	AudioProcessorValueTreeState::SliderAttachment attackSliderAttachment;
	AudioProcessorValueTreeState::SliderAttachment releaseSliderAttachment;
	AudioProcessorValueTreeState::SliderAttachment makeUpGainSliderAttachment;
	AudioProcessorValueTreeState::SliderAttachment compressionSliderAttachment;

	AudioProcessorValueTreeState::ButtonAttachment makeUpGainSelectorButtonAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorAudioProcessorEditor)
};

