/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 2 Dec 2020 8:06:14am
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class KAPParameterSlider
    : public juce::Slider
{
public:
    KAPParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
                        const juce::String& parameterID,
                        const juce::String& parameterLabel);
    ~KAPParameterSlider();
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterSlider);
};