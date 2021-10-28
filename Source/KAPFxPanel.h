/*
  ==============================================================================

    KAPFxPanel.h
    Created: 1 Dec 2020 9:58:21pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"
enum KAPFxPanelStyle
{
    kKAPFxPanelStyle_Delay,
    kKAPFxPanelStyle_Chorus,
    kKAPFxPanelStyle_TotalNumStyles
};


class KAPFxPanel
    :public KAPPanelBase,
    public juce::ComboBox::Listener
{
public:
    KAPFxPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPFxPanel();

    void paint(juce::Graphics& g) override;

    void setFxPanelStyle(KAPFxPanelStyle inStyle);

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    KAPFxPanelStyle mStyle;

    juce::OwnedArray<KAPParameterSlider> mSliders;
};