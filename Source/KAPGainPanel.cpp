/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 1 Dec 2020 9:58:39pm
    Author:  thare

  ==============================================================================
*/

#include "KAPGainPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"
KAPGainPanel::KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
    :KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
        GAIN_PANEL_HEIGHT);

    mVuMeter = std::make_unique<KAPVuMeter>(mProcessor);
    const int meter_width = 64;
    mVuMeter->setBounds((getWidth() * 0.5) - (meter_width * 0.5),
        (getHeight() * 0.55) - (meter_width * 0.5),
        meter_width,
        (getHeight() * 0.45));
    addAndMakeVisible(mVuMeter.get());
}
KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::paint(juce::Graphics& g)
{
    KAPPanelBase::paint(g);
    if (mSlider) {
        paintComponentLabel(g, mSlider.get());
    }
}

void KAPGainPanel::setParameterID(int inParameterID)
{
    mSlider = std::make_unique<KAPParameterSlider>(mProcessor->parameters,
                                                   KAPParameterID[inParameterID], KAPParameterLabel[inParameterID] );
    const int slider_size = 54;

    mSlider->setBounds((getWidth() * 0.5) - (slider_size * 0.5),
                       (getHeight() * 0.25) - (slider_size * 0.5) - 10,
                        slider_size, slider_size);
    addAndMakeVisible(mSlider.get());

    mVuMeter->setParameterID(inParameterID);
}