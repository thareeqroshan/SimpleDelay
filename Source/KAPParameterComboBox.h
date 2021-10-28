/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 2 Dec 2020 8:06:27am
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class KAPParameterComboBox
    : public juce::ComboBox
{
public:
    KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
        const juce::String& parameterID);
    ~KAPParameterComboBox();
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox);
};