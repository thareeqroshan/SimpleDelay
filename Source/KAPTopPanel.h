/*
  ==============================================================================

    KAPTopPanel.h
    Created: 1 Dec 2020 9:59:11pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"

class KAPTopPanel
    :public KAPPanelBase,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();


    void paint(juce::Graphics& g) override;
    void buttonClicked(juce::Button*) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged);


private:
    void displaySaveAsPopup();

    void updatePresetComboBox();

    std::unique_ptr<juce::ComboBox> mPresetDisplay;
    std::unique_ptr<juce::TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
};