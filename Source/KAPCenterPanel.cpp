/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 1 Dec 2020 9:57:28pm
    Author:  thare

  ==============================================================================
*/

#include "KAPCenterPanel.h"
KAPCenterPanel::KAPCenterPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
    :KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH,
            CENTER_PANEL_HEIGHT);

    mMenuBar = std::make_unique<KAPCenterPanelMenuBar>(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar.get());

    mFxPanel = std::make_unique<KAPFxPanel>(inProcessor);
    mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mFxPanel.get());

    mMenuBar->addFxTypeComboBoxListener(mFxPanel.get());

}
KAPCenterPanel::~KAPCenterPanel()
{
    mMenuBar->removeFxTypeComboBoxListener(mFxPanel.get());
}
