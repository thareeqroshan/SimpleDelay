/*
  ==============================================================================

    KAPLfo.h
    Created: 28 Nov 2020 2:50:31am
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPAudioHelpers.h"

class KAPLfo
{
public:
    KAPLfo();
    ~KAPLfo();

    void setSampleRate(double inSampleRate);

    void reset();
    void process(float inRate, 
                float inDepth,  
                int inNumSamples);

    float* getBuffer();
private:
    double mSampleRate;

    float mPhase;

    float mBuffer[maxBufferDelaySize];
};