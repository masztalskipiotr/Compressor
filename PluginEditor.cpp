/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor(CompressorAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p),
	thresholdSliderAttachment(processor.getParametersVTS(), "threshold", thresholdSlider),
	ratioSliderAttachment(processor.getParametersVTS(), "ratio", ratioSlider),
	attackSliderAttachment(processor.getParametersVTS(), "attack", attackSlider),
	releaseSliderAttachment(processor.getParametersVTS(), "release", releaseSlider),
	makeUpGainSliderAttachment(processor.getParametersVTS(), "mug", makeUpGainSlider)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(500, 300);

	thresholdSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	thresholdSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 65, 20);
	thresholdSlider.setTextValueSuffix(" dB");
	thresholdSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	thresholdSliderLabel.setText("THRESHOLD", dontSendNotification);
	thresholdSliderLabel.attachToComponent(&thresholdSlider, false);
	thresholdSliderLabel.setJustificationType(Justification::centredTop);
	thresholdSliderLabel.setFont(Font("Bahnschrift", "Light", 16));



	ratioSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	ratioSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 65, 20);
	ratioSlider.setTextValueSuffix(":1");
	ratioSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	ratioSliderLabel.setText("RATIO", dontSendNotification);
	ratioSliderLabel.attachToComponent(&ratioSlider, false);
	ratioSliderLabel.setJustificationType(Justification::centredTop);
	ratioSliderLabel.setFont(Font("Bahnschrift", "Light", 16));



	attackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	attackSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 65, 20);
	attackSlider.setTextValueSuffix(" ms");
	attackSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	attackSliderLabel.setText("ATTACK", dontSendNotification);
	attackSliderLabel.attachToComponent(&attackSlider, false);
	attackSliderLabel.setJustificationType(Justification::centredTop);
	attackSliderLabel.setFont(Font("Bahnschrift", "Light", 16));



	releaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	releaseSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 65, 20);
	releaseSlider.setTextValueSuffix(" ms");
	releaseSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	releaseSliderLabel.setText("RELEASE", dontSendNotification);
	releaseSliderLabel.attachToComponent(&releaseSlider, false);
	releaseSliderLabel.setJustificationType(Justification::centredTop);
	releaseSliderLabel.setFont(Font("Bahnschrift", "Light", 16));



	makeUpGainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	makeUpGainSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 40, 10);
	makeUpGainSlider.setTextValueSuffix(" dB");
	makeUpGainSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	makeUpGainSliderLabel.setText("MAKE UP GAIN", dontSendNotification);
	makeUpGainSliderLabel.attachToComponent(&makeUpGainSlider, false);
	makeUpGainSliderLabel.setJustificationType(Justification::centredTop);
	makeUpGainSliderLabel.setFont(Font("Bahnschrift", "Light", 10));



	addAndMakeVisible(thresholdSlider);
	addAndMakeVisible(ratioSlider);
	addAndMakeVisible(attackSlider);
	addAndMakeVisible(releaseSlider);
	addAndMakeVisible(makeUpGainSlider);

	addAndMakeVisible(thresholdSliderLabel);
	addAndMakeVisible(ratioSliderLabel);
	addAndMakeVisible(attackSliderLabel);
	addAndMakeVisible(releaseSliderLabel);
	addAndMakeVisible(makeUpGainSliderLabel);


}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void CompressorAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	thresholdSlider.setBounds(0, 30, 200, 120);
	ratioSlider.setBounds(200, 30, 200, 120);
	attackSlider.setBounds(0, 180, 200, 120);
	releaseSlider.setBounds(200, 180, 200, 120);
	makeUpGainSlider.setBounds(400, 100, 70, 70);
}
