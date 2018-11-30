/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	parameters(*this, nullptr)
#endif
{
	//NormalisableRange<float> thresholdRange(-56.0f, 0.0f, 0.1f);
	//NormalisableRange<float> ratioRange(1.0f, 7.0f, 1.0f);
	NormalisableRange<float> attackRange(0.1f, 20.0f, 0.1f);
	NormalisableRange<float> releaseRange(10.0f, 1000.0f, 10.0f);
	NormalisableRange<float> makeUpGainRange(0.f, 20.f, .1f);
	NormalisableRange<float> compressionRange(0.f, 1.0f, 0.01f);
	NormalisableRange<float> mugSelectorRange(0.f, 1.0f, 1.f);

	//parameters.createAndAddParameter("threshold", "Threshold", " dB", thresholdRange, 0.0f, nullptr, nullptr);
	//parameters.createAndAddParameter("ratio", "Ratio", ":1", ratioRange, 2.0f, nullptr, nullptr);
	parameters.createAndAddParameter("attack", "Attack", " ms", attackRange, 1.0f, nullptr, nullptr);
	parameters.createAndAddParameter("release", "Release", " ms", releaseRange, 100.0f, nullptr, nullptr);
	parameters.createAndAddParameter("mug", "Make Up Gain", " ms", makeUpGainRange, 0.f, nullptr, nullptr);
	parameters.createAndAddParameter("compression", "Compression", "", compressionRange, 0.f, nullptr, nullptr);
	parameters.createAndAddParameter("mugselector", "MUG Selector", "", mugSelectorRange, 1.f, nullptr, nullptr);

	//threshold = parameters.getRawParameterValue("threshold");
	threshold = *parameters.getRawParameterValue("compression") * -50.f;
	//ratio = parameters.getRawParameterValue("ratio");
	ratio = 2.f + (*parameters.getRawParameterValue("compression") * 5.f);
	attack = parameters.getRawParameterValue("attack");
	release = parameters.getRawParameterValue("release");
	makeUpGain = parameters.getRawParameterValue("mug");
	compression = parameters.getRawParameterValue("compression");
	autoMakeUpGain = fabs(threshold * (1 - 1 / ratio));
	mugSelector = parameters.getRawParameterValue("mugselector");
}

CompressorAudioProcessor::~CompressorAudioProcessor()
{
}

//==============================================================================
const String CompressorAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool CompressorAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool CompressorAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
	return 0;
}

void CompressorAudioProcessor::setCurrentProgram(int index)
{
}

const String CompressorAudioProcessor::getProgramName(int index)
{
	return {};
}

void CompressorAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	thresholdLinear = Decibels::decibelsToGain(threshold);
	//autoMakeUpGain = fabs(threshold / ratio);

	cAT = exp(-1 * 1000 / *attack / sampleRate);
	cRT = exp(-1 * 1000 / *release / sampleRate);

	state = 0;

}

void CompressorAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void CompressorAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.

	auto* leftData = buffer.getWritePointer(0);
	auto* rightData = buffer.getWritePointer(1);
	float slope = 1 - 1 / ratio;

	for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
		auto sideInput = fabs(leftData[sample]);
		auto c = sideInput >= state ? cAT : cRT;
		auto env = sideInput + c * (state - sideInput);
		auto env_db = Decibels::gainToDecibels(env);
		state = env;

		//auto cv = env <= thresholdLinear ? 1 : pow(env / thresholdLinear, 1 / *ratio - 1);
		auto gain = slope * (threshold - env_db);
		gain = fmin(0.f, gain);
		gain = Decibels::decibelsToGain(gain);

		if (*mugSelector < 1.f) {
			leftData[sample] *= gain * (Decibels::decibelsToGain(*makeUpGain));
			rightData[sample] *= gain * (Decibels::decibelsToGain(*makeUpGain));
		}
		else {
			leftData[sample] *= gain * (Decibels::decibelsToGain(autoMakeUpGain));
			rightData[sample] *= gain * (Decibels::decibelsToGain(autoMakeUpGain));
		}

		/*auto input = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
		auto gain = slope * (*threshold - Decibels::gainToDecibels(input));
		gain = fmin(0.f, gain);
		gain = Decibels::decibelsToGain(gain);
		leftData[sample] *= gain;
		rightData[sample] *= gain;*/

		updateParameters();
	}

}

//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
	return new CompressorAudioProcessorEditor(*this);
}

//==============================================================================
void CompressorAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void CompressorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

void CompressorAudioProcessor::updateParameters()
{
	//threshold = parameters.getRawParameterValue("threshold");
	threshold = *parameters.getRawParameterValue("compression") * -50.f;
	//ratio = parameters.getRawParameterValue("ratio");
	ratio = 1.f + (*parameters.getRawParameterValue("compression") * 5.f);
	attack = parameters.getRawParameterValue("attack");
	release = parameters.getRawParameterValue("release");
	makeUpGain = parameters.getRawParameterValue("mug");
	autoMakeUpGain = fabs(threshold * (1 - 1 / ratio));
	mugSelector = parameters.getRawParameterValue("mugselector");

	thresholdLinear = Decibels::decibelsToGain(threshold);
	
	cAT = exp(-1 * 1000 / *attack / getSampleRate());
	cRT = exp(-1 * 1000 / *release / getSampleRate());
}

AudioProcessorValueTreeState& CompressorAudioProcessor::getParametersVTS() {
	return parameters;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new CompressorAudioProcessor();
}
