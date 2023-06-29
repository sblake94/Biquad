#pragma once

#include "Parameters.h"
#include "BiquadUnit.h"

namespace Processing
{
	class BiquadProcessor
	{
	public:
		BiquadProcessor();
		~BiquadProcessor();

		void ProcessReplacing
		(
			juce::AudioBuffer<float>& _inputs,
			juce::AudioBuffer<float>& _outputs,
			Processing::Parameters& _params,
			int _sampleRate,
			int _sampleFrames
		);

	private:
		BiquadUnit m_biquadA;
		BiquadUnit m_biquadB;
		BiquadUnit m_biquadC;
	};
}