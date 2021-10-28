/*
  ==============================================================================

    KAPFxPanel.cpp
    Created: 1 Dec 2020 9:58:21pm
    Author:  thare

  ==============================================================================
*/

#include "KAPFxPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"
KAPFxPanel::KAPFxPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
    :KAPPanelBase(inProcessor)
{
    setSize(FX_PANEL_WITDH,
            FX_PANEL_HEIGHT);

    const int currentStyle = (int)mProcessor->getParameter(kParameter_DelayType);
    setFxPanelStyle((KAPFxPanelStyle) currentStyle);
}
KAPFxPanel::~KAPFxPanel()
{

}

void KAPFxPanel::paint(juce::Graphics& g) 
{
    KAPPanelBase::paint(g);
    juce::String label;
    switch (mStyle)
    {
        case kKAPFxPanelStyle_Delay: {
            label = "DELAY";
        }break;

        case kKAPFxPanelStyle_Chorus: {
            label = "CHORUS";
        } break;
        default:
        case(kKAPFxPanelStyle_TotalNumStyles):{
            jassertfalse;
        }
    }

    g.setColour(KAPColour_5);
    g.setFont(font_3);

    g.drawText(label, 0, 0, getWidth(), 80, juce::Justification::centred);

    for (int i = 0; i < mSliders.size(); i++)
    {
        paintComponentLabel(g, mSliders[i]);
    }
}


void KAPFxPanel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
    mStyle = inStyle;

    mSliders.clear();
    const int slider_size = 56;
    int x = 130;
    int y = (getHeight() * 0.5) - (slider_size * 0.5);

    switch (mStyle)
    {
    case kKAPFxPanelStyle_Delay: {
        KAPParameterSlider* time = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayTime], KAPParameterLabel[kParameter_DelayTime]);
        time->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(time);
        mSliders.add(time);
        x += slider_size * 2;

        KAPParameterSlider* feedback = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayFeedback], KAPParameterLabel[kParameter_DelayFeedback]);
        feedback->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(feedback);
        mSliders.add(feedback);
        x += slider_size * 2;

        KAPParameterSlider* wetdry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry],KAPParameterLabel[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(wetdry);
        mSliders.add(wetdry);
    }break;

    case kKAPFxPanelStyle_Chorus: {
        KAPParameterSlider* rate = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationRate], KAPParameterLabel[kParameter_ModulationRate]);
        rate->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(rate);
        mSliders.add(rate);
        x += slider_size * 2;

        KAPParameterSlider* depth = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationDepth], KAPParameterLabel[kParameter_ModulationDepth]);
        depth->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(depth);
        mSliders.add(depth);
        x += slider_size * 2;

        KAPParameterSlider* wetdry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry], KAPParameterLabel[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(wetdry);
        mSliders.add(wetdry);
    } break;

    case kKAPFxPanelStyle_TotalNumStyles: {
        jassertfalse;
    }break;
    }
    repaint();
}


void KAPFxPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    KAPFxPanelStyle style =  (KAPFxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();

    setFxPanelStyle(style);
}
