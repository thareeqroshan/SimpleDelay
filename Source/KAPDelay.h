/*
  ==============================================================================

    KAPDelay.h
    Created: 28 Nov 2020 2:50:59am
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPAudioHelpers.h"

enum KAPDelayType
{
    kKAPDelayType_Delay=0,
    kKAPDelayType_Chorus
};

class KAPDelay
{
public:
    KAPDelay();
    ~KAPDelay();

    void setSampleRate(double inSampleRate);

    void reset();
    void process(float* inAudio, 
                float inTime, 
                float inFeedback, 
                float inWetDry,
                float inType,
                float* inModulationBuffer,
                float* outAudio, 
                int inNumSamplesToRender);
private:
    //internal
    double getInterpolatedSample(float inDelayTimeInSample);

    double mSampleRate;
    double mBuffer[maxBufferDelaySize];
    double mFeedbackSample;
    float mTimeSmoothed;

    int mDelayIndex;
};