/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 1 Dec 2020 9:56:57pm
    Author:  thare

  ==============================================================================
*/

#include "KAPPanelBase.h"
#include "KAPInterfaceDefines.h"

KAPPanelBase::KAPPanelBase(KadenzeAudioPluginAudioProcessor* inProcessor)
    :mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::paint(juce::Graphics& g)
{
    //g.setColour(juce::Colours::white);
    //g.fillAll();

    //g.setColour(juce::Colours::black);
    ////g.drawRect(0, 0, getWidth(), getHeight(), 2);
    
    //g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 4, 2);

    if (isMouseOver())
    {
        g.setColour(KAPColour_4);
        g.fillAll();
    }
}

void KAPPanelBase::mouseEnter(const juce::MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::mouseExit(const juce::MouseEvent& event)
{
    repaint();
}
