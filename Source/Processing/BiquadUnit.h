#pragma once

#include "Parameters.h"

namespace Processing
{
	/////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Holds all Logic and State of a Biquad Filter Instance
	/// </summary>
	class BiquadUnit
	{
	public://////////////////////////////////////////////////////////////////

		BiquadUnit();
		~BiquadUnit();

		enum FilterType
		{
			HighShelf,
			PeakShelf,
			LowShelf
		};

		void ApplyBiquad(
			juce::AudioBuffer<float>& _inputBuffer,
			juce::AudioBuffer<float>& _outputBuffer,
			Processing::Parameters& _params,
			FilterType _filterType,
			const int _sampleRate,
			const int _sampleFrames
		);

		void SetHighShelfCoeffs(ParamDirectory& _sliderParams, int _sampleRate);
		void SetPeakShelfCoeffs(ParamDirectory& _sliderParams, int _sampleRate);
		void SetLowShelfCoeffs(ParamDirectory& _sliderParams, int _sampleRate);

	private://////////////////////////////////////////////////////////////////

		void SetShelfCoeffs(float _gain, float _cutoff, float _bandwidth, int _sampleRate);

		// Biquad Coefficients
		double m_b0, m_b1, m_b2, m_a0, m_a1, m_a2;
		double m_in1L, m_in2L, m_out1L, m_out2L;
		double m_in1R, m_in2R, m_out1R, m_out2R;


		// Peak/Shelf Coefficients
		double A, w0, cosw0, sinw0, alpha;
	};
}