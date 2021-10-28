/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "KAPParameters.h"


//==============================================================================
KadenzeAudioPluginAudioProcessor::KadenzeAudioPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                        parameters(*this, nullptr)
#endif
{
    initializeDSP();

    initializeParameters();
    mPresetManager = std::make_unique<KAPPresetManager>(this);

}

KadenzeAudioPluginAudioProcessor::~KadenzeAudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String KadenzeAudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzeAudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KadenzeAudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzeAudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzeAudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzeAudioPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KadenzeAudioPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void KadenzeAudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < 2; i++)
    {
        //mGain[i] = new KAPGain();
        mDelay[i] ->setSampleRate(sampleRate);
        mLfo[i] ->setSampleRate(sampleRate);
    }
}

void KadenzeAudioPluginAudioProcessor::releaseResources()
{
    for (int i = 0; i < 2; i++)
    {
        //mGain[i] = new KAPGain();
        mDelay[i]->reset();
        mLfo[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzeAudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void KadenzeAudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        mInputGain[channel]->process(channelData, 
                                getParameter(kParameter_InputGain), 
                                channelData, 
                                buffer.getNumSamples());
        float rate = channel==0 ? getParameter(kParameter_ModulationRate): 0;

        mLfo[channel]->process(rate, 
                                getParameter(kParameter_ModulationDepth), 
                                buffer.getNumSamples());

        mDelay[channel]->process(channelData, 
                                 getParameter(kParameter_DelayTime), 
                                 getParameter(kParameter_DelayFeedback),
                                 getParameter(kParameter_DelayWetDry),
                                 getParameter(kParameter_DelayType),
                                 mLfo[channel]->getBuffer(),
                                 channelData, 
                                 buffer.getNumSamples());
        mOutputGain[channel]->process(channelData,
                                      getParameter(kParameter_OutputGain),
                                      channelData,
                                      buffer.getNumSamples());


        // ..do something to the data...
    }
}

//==============================================================================
bool KadenzeAudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KadenzeAudioPluginAudioProcessor::createEditor()
{
    return new KadenzeAudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement preset("KAP_StateInfo");
    juce::XmlElement* presetBody = new juce::XmlElement("KAP_Preset");

    mPresetManager->getXmlForPreset(presetBody);

    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

float KadenzeAudioPluginAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
    return normalizeddB;
}

float KadenzeAudioPluginAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
    return normalizeddB;
}

void KadenzeAudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    if (xmlState)
    {
        forEachXmlChildElement(*xmlState, subChild) {
            mPresetManager->loadPresetForXml(subChild);
        }
    }
    else {
        jassertfalse;
    }
}

void KadenzeAudioPluginAudioProcessor::initializeDSP()
{
    for (int i = 0; i < 2; i++)
    {
        //mGain[i] = new KAPGain();
        mInputGain[i] = std::make_unique<KAPGain>();
        mOutputGain[i] = std::make_unique<KAPGain>();
        mDelay[i] = std::make_unique<KAPDelay>();
        mLfo[i] = std::make_unique<KAPLfo>();
    }
}

void KadenzeAudioPluginAudioProcessor::initializeParameters()
{
    for (int i = 0; i < kParameter_TotalNumParameters; i++)
    {
        parameters.createAndAddParameter(KAPParameterID[i],
            KAPParameterID[i],
            KAPParameterLabel[i],
            juce::NormalisableRange<float>(0.0f, 1.0f),
            0.5f,
            nullptr,
            nullptr);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeAudioPluginAudioProcessor();
}
