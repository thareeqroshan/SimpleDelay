/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 1 Dec 2020 9:58:02pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include "KAPParameterComboBox.h"

class KAPCenterPanelMenuBar
    :public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanelMenuBar();

    void addFxTypeComboBoxListener(juce::ComboBox::Listener* inListener);

    void removeFxTypeComboBoxListener(juce::ComboBox::Listener* inListener);

private:
    std::unique_ptr<KAPParameterComboBox> mFxTypeComboBox;
};