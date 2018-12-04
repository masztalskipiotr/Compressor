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
	
	makeUpGainSliderAttachment(processor.getParametersVTS(), "mug", makeUpGainSlider),
	compressionSliderAttachment(processor.getParametersVTS(), "compression", compressionSlider),
	makeUpGainSelectorButtonAttachment(processor.getParametersVTS(), "mugselector", makeUpGainSelectorButton),
	compressionModeSelectorBoxAttachment(processor.getParametersVTS(), "compmode", compressionModeSelectorBox)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(570, 370);

	potOfGoldImage = ImageCache::getFromMemory(BinaryData::rsz_80potofgold_png, BinaryData::rsz_80potofgold_pngSize);

	makeUpGainSelectorButton.setButtonText("AUTO");
	makeUpGainSelectorButton.setClickingTogglesState(true);
	makeUpGainSelectorButton.setColour(TextButton::buttonOnColourId, compressionSlider.findColour(Slider::thumbColourId));
	//makeUpGainSelectorButton.onClick = [this] { setSliderInvisible(); };
	makeUpGainSelectorButton.addListener(this);


	compressionModeSelectorBox.addSectionHeading("VOCALS");
	compressionModeSelectorBox.addItem("Natural", 1);
	compressionModeSelectorBox.addItem("Aggresive", 2);
	compressionModeSelectorBox.addSeparator();

	compressionModeSelectorBox.addSectionHeading("DRUMS");
	compressionModeSelectorBox.addItem("Punch", 3);
	compressionModeSelectorBox.addItem("Meat", 4);
	compressionModeSelectorBox.setJustificationType(Justification::centred);
	compressionModeSelectorBox.addSeparator();

	compressionModeSelectorBox.addSectionHeading("MASTER");
	compressionModeSelectorBox.addItem("Glue", 5);
	compressionModeSelectorBox.addItem("Limiter", 6);

	compressionModeSelectorBox.setSelectedId(*processor.getParametersVTS().getRawParameterValue("compmode") + 1);

	makeUpGainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	makeUpGainSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 60, 15);
	makeUpGainSlider.setTextValueSuffix(" dB");
	makeUpGainSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	

	makeUpGainSliderLabel.setText("MAKE UP GAIN", dontSendNotification);
	makeUpGainSliderLabel.attachToComponent(&makeUpGainSlider, false);
	makeUpGainSliderLabel.setJustificationType(Justification::centredTop);
	makeUpGainSliderLabel.setFont(Font("Bahnschrift", "Light", 12));
	if (makeUpGainSelectorButton.getToggleState() == true)
		makeUpGainSlider.setEnabled(false);
	else
		makeUpGainSlider.setEnabled(true);



	compressionSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	compressionSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	compressionSlider.setTextValueSuffix("");
	compressionSlider.getLookAndFeel().setColour(Slider::textBoxOutlineColourId,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	compressionSlider.setRotaryParameters(-2.f, 1.7f, false);
	

	compressionSliderLabel.setText("COMPRESSION", dontSendNotification);
	compressionSliderLabel.attachToComponent(&compressionSlider, false);
	compressionSliderLabel.setJustificationType(Justification::centredTop);
	compressionSliderLabel.setFont(Font("Bahnschrift", "Light", 16));



	addAndMakeVisible(makeUpGainSlider);
	addAndMakeVisible(compressionSlider);
	addAndMakeVisible(makeUpGainSelectorButton);
	addAndMakeVisible(compressionModeSelectorBox);

	addAndMakeVisible(makeUpGainSliderLabel);
	addAndMakeVisible(compressionSliderLabel);


}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
	makeUpGainSelectorButton.removeListener(this);
}

//==============================================================================
void CompressorAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.drawImageAt(potOfGoldImage, 355, 240);
}

//void CompressorAudioProcessorEditor::setSliderInvisible() {
//	if (makeUpGainSelectorButton.isDown()) {
//		makeUpGainSlider.setEnabled(false);
//	}
//}

void CompressorAudioProcessorEditor::resized()
{
	makeUpGainSlider.setBounds(485, 230, 70, 70);
	compressionSlider.setBounds(90, 80, 380, 300);
	makeUpGainSelectorButton.setBounds(495, 315, 50, 30);
	compressionModeSelectorBox.setBounds(20, 20, 100, 30);

}

void CompressorAudioProcessorEditor::buttonClicked(Button *button) {
	if (button == &makeUpGainSelectorButton) {
		if (button->getToggleState() == true)
			makeUpGainSlider.setEnabled(false);
		else
			makeUpGainSlider.setEnabled(true);
	}
}