/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 2 Dec 2020 8:06:27am
    Author:  thare

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
    const juce::String& parameterID)
    :juce::ComboBox(parameterID)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, parameterID, *this);
}
KAPParameterComboBox::~KAPParameterComboBox()
{

}