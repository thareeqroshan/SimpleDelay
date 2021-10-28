/*
  ==============================================================================

    KAPGain.h
    Created: 28 Nov 2020 2:50:52am
    Author:  thare

  ==============================================================================
*/

#pragma once

class KAPGain
{
public:

    KAPGain();
    ~KAPGain();

    void process(float *inAudio,float inGain, float *outAudio, float inNumSamplesToRender);

    float getMeterLevel();
private:
    float mOutputSmoothed;
};