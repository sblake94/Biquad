#pragma once

#include "Parameters.h"
#include "BiquadUnit.h"

namespace Processing
{
	///////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Dedicated class for holding all DSP logic
	/// </summary>
	class BiquadProcessing
	{
	public: //////////////////////////////////////////////////////////////////
		BiquadProcessing();
		~BiquadProcessing();

		void ProcessReplacing
		(
			juce::AudioBuffer<float>& _inputs,
			juce::AudioBuffer<float>& _outputs,
			Processing::Parameters& _params,
			int _sampleRate,
			int _sampleFrames
		);

		void ApplyCurve(juce::AudioSampleBuffer& _buffer, int _sampleFrames);
		void RemoveCurve(juce::AudioSampleBuffer& _buffer, int _sampleFrames);

		void Clip
		(
			juce::AudioSampleBuffer& tempBuffer,
			float _min,
			float _max,
			int _sampleFrames
		);

	private://////////////////////////////////////////////////////////////////
		BiquadUnit m_biquadA;
		BiquadUnit m_biquadB;
		BiquadUnit m_biquadC;
	};
}