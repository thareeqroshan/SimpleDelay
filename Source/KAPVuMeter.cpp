/*
  ==============================================================================

    KAPVuMeter.cpp
    Created: 21 Dec 2020 11:26:29pm
    Author:  thare

  ==============================================================================
*/

#include "KAPVuMeter.h"
#include "KAPInterfaceDefines.h"
#include "KAPParameters.h"

KAPVuMeter::KAPVuMeter(KadenzeAudioPluginAudioProcessor* inProcessor)
   :mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    mProcessor(inProcessor)
{
}

KAPVuMeter::~KAPVuMeter()
{
}

void KAPVuMeter::paint(Graphics& g)
{
    const int meter_width = getWidth() / 3;

    g.setColour(KAPColour_6);
    //left VU
    g.fillRect(0, 0, meter_width, getHeight());
    //right VU
    g.fillRect(meter_width * 2, 0, meter_width, getHeight());

    int ch0fill = getHeight() - (getHeight() * mCh0Level);
    int ch1fill = getHeight() - (getHeight() * mCh1Level);

    if (ch0fill < 0)ch0fill = 0;
    if (ch1fill < 0)ch1fill = 0; 
    g.setColour(KAPColour_7);
    g.fillRect(0, ch0fill, meter_width, getHeight());
    g.fillRect(meter_width * 2, ch1fill, meter_width, getHeight());
}

void KAPVuMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    startTimerHz(25);
}

void KAPVuMeter::timerCallback()
{
    float updateCh0Level = 0.0f;
    float updateCh1Level = 0.0f;

    switch (mParameterID)
    {
        case(kParameter_InputGain): {
            updateCh0Level = mProcessor->getInputGainMeterLevel(0);
            updateCh1Level = mProcessor->getInputGainMeterLevel(1);
            }break;

        case(kParameter_OutputGain): {
            updateCh0Level = mProcessor->getOutputGainMeterLevel(0);
            updateCh1Level = mProcessor->getOutputGainMeterLevel(1);
        }break;
    }

    if (updateCh0Level > mCh0Level) {
        mCh0Level = updateCh0Level;
    }
    else {
        mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updateCh0Level) + updateCh0Level;
    }
    if (updateCh1Level > mCh1Level) {
        mCh1Level = updateCh1Level;
    }
    else {
        mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updateCh1Level) + updateCh0Level;
    }

    mCh0Level = kap_denormalize(mCh0Level);
    mCh1Level = kap_denormalize(mCh1Level);

    if (mCh0Level && mCh1Level) {
        repaint();
    }

}
