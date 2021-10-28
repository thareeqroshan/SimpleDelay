/*
  ==============================================================================

    KAPParameters.h
    Created: 2 Dec 2020 7:42:38am
    Author:  thare

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
    kParameter_InputGain = 0,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_DelayWetDry,
    kParameter_DelayType,   //chorus or delay
    kParameter_OutputGain,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_TotalNumParameters
};

static juce::String KAPParameterID[kParameter_TotalNumParameters] =
{
    "InputGain",
    "Time",
    "Feedback",
    "WetDry",
    "Type",
    "OutputGain",
    "ModulationRate",
    "ModulationDepth"
};


static juce::String KAPParameterLabel[kParameter_TotalNumParameters] =
{
    "Input Gain",
    "Delay Time",
    "Delay Feedback",
    "Delay WetDry",
    "Delay Type",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth"
};