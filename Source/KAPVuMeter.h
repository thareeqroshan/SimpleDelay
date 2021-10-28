/*
  ==============================================================================

    KAPVuMeter.h
    Created: 21 Dec 2020 11:26:29pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
using namespace juce;

class KAPVuMeter :public Component,
                  public Timer
{
public:
    KAPVuMeter(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPVuMeter();

    void paint(Graphics& g)override;
    void setParameterID(int inParameterID);

    void timerCallback() override;
private:
    int mParameterID;

    float mCh0Level;
    float mCh1Level;

    KadenzeAudioPluginAudioProcessor* mProcessor;
};