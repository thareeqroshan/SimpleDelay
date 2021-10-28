/*
  ==============================================================================

    KAPPanelBase.h
    Created: 1 Dec 2020 9:56:57pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "KAPInterfaceDefines.h"

class KAPPanelBase
    : public juce::Component
{
public:
    KAPPanelBase(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPPanelBase();

    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

protected:

    KadenzeAudioPluginAudioProcessor* mProcessor;
};