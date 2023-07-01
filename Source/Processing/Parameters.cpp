#include "Parameters.h"

using namespace Processing;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
Parameters::Parameters()
	: m_floatParams()
	, m_boolParams()

	, m_lowBandBypass(ParameterID(s_lowBandBypassParamID), juce::String("Low Band Bypass"), false)
	, m_midBandBypass(ParameterID(s_midBandBypassParamID), juce::String("Mid Band Bypass"), false)
	, m_highBandBypass(ParameterID(s_highBandBypassParamID), juce::String("High Band Bypass"), false)
	
	, m_lowFreqCutoff(ParameterID(s_lowFreqCutoffParamID), juce::String("Low Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	, m_midFreqCutoff(ParameterID(s_midFreqCutoffParamID), juce::String("Mid Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	, m_highFreqCutoff(ParameterID(s_highFreqCutoffParamID), juce::String("High Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f)
	
	, m_lowGain(ParameterID(s_lowGainParamID), juce::String("Low Gain"), -24.0f, 24.0f, 0.0f)
	, m_midGain(ParameterID(s_midGainParamID), juce::String("Mid Gain"), -24.0f, 24.0f, 0.0f)
	, m_highGain(ParameterID(s_highGainParamID), juce::String("High Gain"), -24.0f, 24.0f, 0.0f)
	
	, m_lowBandwidth(ParameterID(s_lowBandwidthParamID), juce::String("Low Bandwidth"), 0.001f, 8.0f, 0.001f)
	, m_midBandwidth(ParameterID(s_midBandwidthParamID), juce::String("Mid Bandwidth"), 0.001f, 8.0f, 0.001f)
	, m_highBandwidth(ParameterID(s_highBandwidthParamID), juce::String("High Bandwidth"), 0.001f, 8.0f, 0.001f)
	
	, m_masterBypass(ParameterID(s_masterBypassParamID), juce::String("Master Bypass"), false)
	, m_masterGain(ParameterID(s_masterGainParamID), juce::String("Master Gain"), -24.0f, 24.0f, 0.0f)

	, m_engageHeat(ParameterID(s_engageHeatParamID), juce::String("Engage Heat"), false)
	, m_heatGain(ParameterID(s_heatGainParamID), juce::String("Heat Gain"), -6.0f, 6.0f, 0.0f)
{
	m_floatParams = FloatParamDirectory
	{
		{ s_lowFreqCutoffParamID, &m_lowFreqCutoff },
		{ s_midFreqCutoffParamID, &m_midFreqCutoff },
		{ s_highFreqCutoffParamID, &m_highFreqCutoff },

		{ s_lowGainParamID, &m_lowGain },
		{ s_midGainParamID, &m_midGain },
		{ s_highGainParamID, &m_highGain },

		{ s_lowBandwidthParamID, &m_lowBandwidth },
		{ s_midBandwidthParamID, &m_midBandwidth },
		{ s_highBandwidthParamID, &m_highBandwidth },

		{ s_masterGainParamID, &m_masterGain },
		{ s_heatGainParamID, &m_heatGain }
	};

	m_boolParams = BoolParamDirectory
	{
		{ s_engageHeatParamID, &m_engageHeat },
		{ s_masterBypassParamID, &m_masterBypass },

		{ s_lowBandBypassParamID, &m_lowBandBypass },
		{ s_midBandBypassParamID, &m_midBandBypass },
		{ s_highBandBypassParamID, &m_highBandBypass}
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
Parameters::~Parameters()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the slider parameters as a Reference to a ParamDirectory
/// </summary>
FloatParamDirectory& Parameters::GetSliderParams()
{
	return m_floatParams;
}

BoolParamDirectory& Processing::Parameters::GetBoolParams()
{
	return m_boolParams;
}
