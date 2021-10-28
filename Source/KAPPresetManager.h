/*
  ==============================================================================

    KAPPresetManager.h
    Created: 20 Dec 2020 9:29:26pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

#define PRESET_FILE_EXTENSTION  ".kpf"
class KAPPresetManager
{
public:
    KAPPresetManager(juce::AudioProcessor* inProcessor);
    ~KAPPresetManager();

    void getXmlForPreset(juce::XmlElement* inElement);

    void loadPresetForXml(juce::XmlElement* inElement);

    int getNumberOfPresets();

    juce::String getPresetName(int inPresetIndex);

    void createNewPreset();

    void savePreset();

    void saveAsPreset(juce::String inPresetName);

    void loadPreset(int inPresetIndex);

    bool getIsCurrentPresetSaved();

    juce::String getCurrentPresetName();
private:
    void storeLocalPreset();

    bool mCurrentPresetIsSaved;

    juce::File mCurrentlyLoadedPreset;
    juce::Array<juce::File> mLocalPresets;

    juce::String mCurrentPresetName;

    juce::String mPresetDirectory;

    juce::XmlElement* mCurrentPresetXml;
    juce::AudioProcessor* mProcessor;
};