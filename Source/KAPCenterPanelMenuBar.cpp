/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 1 Dec 2020 9:58:02pm
    Author:  thare

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"

KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* inProcessor)
    :KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH,
        CENTER_PANEL_MENU_BAR_HEIGHT);
    const int width = 85;

    mFxTypeComboBox = std::make_unique<KAPParameterComboBox>(mProcessor->parameters, KAPParameterID[kParameter_DelayType]);
    
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType), juce::dontSendNotification);
    addAndMakeVisible(mFxTypeComboBox.get());
}
KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

void KAPCenterPanelMenuBar::addFxTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}

void KAPCenterPanelMenuBar::removeFxTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->removeListener(inListener);
}
