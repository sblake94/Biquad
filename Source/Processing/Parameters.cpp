#include "Parameters.h"

using namespace Processing;


Parameters::Parameters()
	: m_sliderParams()
	, m_lowFreqCutoff(ParameterID(s_lowFreqCutoffParamID), juce::String("Low Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	, m_midFreqCutoff(ParameterID(s_midFreqCutoffParamID), juce::String("Mid Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	, m_highFreqCutoff(ParameterID(s_highFreqCutoffParamID), juce::String("High Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	, m_lowGain(ParameterID(s_lowGainParamID), juce::String("Low Gain"), -24.0f, 24.0f, 0.0f)
	, m_midGain(ParameterID(s_midGainParamID), juce::String("Mid Gain"), -24.0f, 24.0f, 0.0f)
	, m_highGain(ParameterID(s_highGainParamID), juce::String("High Gain"), -24.0f, 24.0f, 0.0f)
	, m_lowResonance(ParameterID(s_lowResonanceParamID), juce::String("Low Resonance"), 0.001f, 1.0f, 0.001f)
	, m_midResonance(ParameterID(s_midResonanceParamID), juce::String("Mid Resonance"), 0.001f, 1.0f, 0.001f)
	, m_highResonance(ParameterID(s_highResonanceParamID), juce::String("High Resonance"), 0.001f, 1.0f, 0.001f)
{
	m_sliderParams = ParamDirectory
	{
		{ s_lowFreqCutoffParamID, &m_lowFreqCutoff },
		{ s_midFreqCutoffParamID, &m_midFreqCutoff },
		{ s_highFreqCutoffParamID, &m_highFreqCutoff },
		{ s_lowGainParamID, &m_lowGain },
		{ s_midGainParamID, &m_midGain },
		{ s_highGainParamID, &m_highGain },
		{ s_lowResonanceParamID, &m_lowResonance },
		{ s_midResonanceParamID, &m_midResonance },
		{ s_highResonanceParamID, &m_highResonance }
	};
}

Parameters::~Parameters()
{
}

ParamDirectory& Parameters::GetSliderParams()
{
	return m_sliderParams;
}

