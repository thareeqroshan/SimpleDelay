/*
  ==============================================================================

    KAPLfo.cpp
    Created: 28 Nov 2020 2:50:31am
    Author:  thare

  ==============================================================================
*/

#include "KAPLfo.h"
#include "JuceHeader.h"


KAPLfo::KAPLfo()
{
    reset();
}

KAPLfo::~KAPLfo()
{

}

void KAPLfo::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPLfo::reset()
{
    mPhase = 0.0f;
    juce::zeromem(mBuffer, sizeof(float) * maxBufferDelaySize);
}

void KAPLfo::process(float inRate,
    float inDepth,
    int inNumSamples) 
{
    const float rate = juce::jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);

    for (int i = 0; i < inNumSamples; i++)
    {
        mPhase += rate / mSampleRate;


        if (mPhase > 1.0f)
        {
            mPhase -= 1.0f;
        }

        const float lfoPosition = sinf(mPhase * k2PI) * inDepth;
        mBuffer[i] = lfoPosition;
    }
}

float* KAPLfo::getBuffer()
{
    return mBuffer;
}