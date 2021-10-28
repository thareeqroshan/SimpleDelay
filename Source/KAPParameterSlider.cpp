/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 2 Dec 2020 8:06:14am
    Author:  thare

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
    const juce::String& parameterID,
    const juce::String& parameterLabel)
    :juce::Slider(parameterLabel)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);

    setRange(0.0f, 1.0f, 0.001f);

    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);

}
KAPParameterSlider::~KAPParameterSlider()
{

}