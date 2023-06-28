#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

using ParamDirectory = std::map<int, juce::AudioParameterFloat*>;

namespace Processing
{
static const int s_lowFreqCutoffParamID(0);
static const int s_midFreqCutoffParamID(1);
static const int s_highFreqCutoffParamID(2);
static const int s_lowGainParamID(3);
static const int s_midGainParamID(4);
static const int s_highGainParamID(5);
static const int s_lowResonanceParamID(6);
static const int s_midResonanceParamID(7);
static const int s_highResonanceParamID(8);

	class Parameters
	{
	public:
		Parameters();
		~Parameters();

		ParamDirectory& GetSliderParams();

	private:
		ParamDirectory m_sliderParams;

		AudioParameterFloat m_lowFreqCutoff;
		AudioParameterFloat m_midFreqCutoff;
		AudioParameterFloat m_highFreqCutoff;

		AudioParameterFloat m_lowGain;
		AudioParameterFloat m_midGain;
		AudioParameterFloat m_highGain;

		AudioParameterFloat m_lowResonance;
		AudioParameterFloat m_midResonance;
		AudioParameterFloat m_highResonance;
	};
}