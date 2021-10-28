/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 1 Dec 2020 9:57:28pm
    Author:  thare

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include "KAPCenterPanelMenuBar.h"
#include "KAPFxPanel.h"


class KAPCenterPanel
    :public KAPPanelBase
{
public:
    KAPCenterPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanel();

private:
    std::unique_ptr<KAPCenterPanelMenuBar> mMenuBar;
    std::unique_ptr<KAPFxPanel> mFxPanel;
};