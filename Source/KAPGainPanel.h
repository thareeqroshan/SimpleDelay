/*
  ==============================================================================

    KAPGainPanel.h
    Created: 1 Dec 2020 9:58:39pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"
#include "KAPVuMeter.h"

class KAPGainPanel
    :public KAPPanelBase
{
public:
    KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPGainPanel();

    void paint(juce::Graphics& g) override;

    void setParameterID(int inParameterID);

private:
    std::unique_ptr<KAPParameterSlider> mSlider;
    std::unique_ptr<KAPVuMeter> mVuMeter;
};