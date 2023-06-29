#include "BiquadUnit.h"
#include "Parameters.h"

using namespace Processing;

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

//////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
BiquadUnit::BiquadUnit()
{
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
///	</summary>
BiquadUnit::~BiquadUnit()
{
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Applies the biquad filter to the input buffer and stores the
/// result in the output buffer
/// </summary>
/// <param name="_inputBuffer">The input buffer</param>
/// <param name="_outputBuffer">The output buffer</param>
/// <param name="_params">The parameters</param>
/// <param name="_filterType">The filter type</param>
/// <param name="_sampleRate">The sample rate</param>
/// <param name="_sampleFrames">The number of sample frames</param>
void BiquadUnit::ApplyBiquad
(
	juce::AudioBuffer<float>& _inputBuffer,
	juce::AudioBuffer<float>& _outputBuffer,
	Processing::Parameters& _params,
	FilterType _filterType,
	int _sampleRate,
	int _sampleFrames
)
{
	// Get the pointers to the buffers
	const float* inL = _inputBuffer.getReadPointer(0);
	const float* inR = _inputBuffer.getReadPointer(1);
	float* outL = _outputBuffer.getWritePointer(0);
	float* outR = _outputBuffer.getWritePointer(1);

	// Get the parameters
	ParamDirectory sliderParams = _params.GetSliderParams();

	// Pick filter type
	switch (_filterType) 
	{
		case FilterType::HighShelf:
			SetHighShelfCoeffs(sliderParams, _sampleRate);
			break;

		case FilterType::PeakShelf:
			SetPeakShelfCoeffs(sliderParams, _sampleRate);
			break;

		case FilterType::LowShelf:
			SetLowShelfCoeffs(sliderParams, _sampleRate);
			break;

		// ... other filter types go here ...

		default:
			throw new std::exception("Invalid filter type");
	}

	// Process the samples
	while (--_sampleFrames >= 0)
	{
		double inputSampleL = *inL;
		double inputSampleR = *inR;

		double tempSampleL =
			(m_b0 / m_a0) * inputSampleL +
			(m_b1 / m_a0) * m_in1L +
			(m_b2 / m_a0) * m_in2L -
			(m_a1 / m_a0) * m_out1L -
			(m_a2 / m_a0) * m_out2L;

		double tempSampleR =
			(m_b0 / m_a0) * inputSampleR +
			(m_b1 / m_a0) * m_in1R +
			(m_b2 / m_a0) * m_in2R -
			(m_a1 / m_a0) * m_out1R -
			(m_a2 / m_a0) * m_out2R;

		// Clip both channels
		if (tempSampleL > 1.0) tempSampleL = 1.0;
		if (tempSampleL < -1.0) tempSampleL = -1.0;
		if (tempSampleR > 1.0) tempSampleR = 1.0;
		if (tempSampleR < -1.0) tempSampleR = -1.0;

		m_in2L = m_in1L;
		m_in1L = inputSampleL;
		m_out2L = m_out1L;
		m_out1L = tempSampleL;

		m_in2R = m_in1R;
		m_in1R = inputSampleR;
		m_out2R = m_out1R;
		m_out1R = tempSampleR;

		*outL = (float)tempSampleL;
		*outR = (float)tempSampleR;

		++inL;
		++inR;
		++outL;
		++outR;
	}
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the shared coefficients for a shelf filter
/// </summary>
/// <param name="_gain">The gain</param>
/// <param name="_cutoff">The cutoff frequency</param>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetShelfCoeffs
(
	float _gain, 
	float _cutoff, 
	float _bandwidth, 
	int _sampleRate
)
{
	A = pow(10.0, _gain / 40.0);
	w0 = 2.0 * E_PI * _cutoff / _sampleRate;
	cosw0 = cos(w0);
	sinw0 = sin(w0);
	alpha = sinw0 * sinh((log10(2) / 2) * _bandwidth * (w0 / sinw0));
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a High shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
/// 
void BiquadUnit::SetHighShelfCoeffs
(
	ParamDirectory& _sliderParams, 
	int _sampleRate
)
{
	float hfCutoff = *(_sliderParams[s_highFreqCutoffParamID]);
	float hfGain = *(_sliderParams[s_highGainParamID]);
	float hfBW = *(_sliderParams[s_highBandwidthParamID]);

	SetShelfCoeffs(hfGain, hfCutoff, hfBW, _sampleRate);

	m_b0 = A * ((A + 1) + (A - 1) * cosw0 + 2 * sqrt(A * alpha));
	m_b1 = -2 * A * ((A - 1) + (A + 1) * cosw0);
	m_b2 = A * ((A + 1) + (A - 1) * cosw0 - 2 * sqrt(A * alpha));
	m_a0 = (A + 1) - (A - 1) * cosw0 + 2 * sqrt(A * alpha);
	m_a1 = 2 * ((A - 1) - (A + 1) * cosw0);
	m_a2 = (A + 1) - (A - 1) * cosw0 - 2 * sqrt(A * alpha);
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a Peak shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetPeakShelfCoeffs(ParamDirectory& _sliderParams, int _sampleRate)
{
	float peakCutoff = *(_sliderParams[s_midFreqCutoffParamID]);
	float peakGain = *(_sliderParams[s_midGainParamID]);
	float peakBW = *(_sliderParams[s_midBandwidthParamID]);

	SetShelfCoeffs(peakGain, peakCutoff, peakBW, _sampleRate);

	m_b0 = 1 + alpha * A;
	m_b1 = -2 * cosw0;
	m_b2 = 1 - alpha * A;
	m_a0 = 1 + alpha / A;
	m_a1 = -2 * cosw0;
	m_a2 = 1 - alpha / A;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a Low shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetLowShelfCoeffs(ParamDirectory& _sliderParams, int _sampleRate)
{
	float lfCutoff = *(_sliderParams[s_lowFreqCutoffParamID]);
	float lfGain = *(_sliderParams[s_lowGainParamID]);
	float lfBW = *(_sliderParams[s_lowBandwidthParamID]);

	SetShelfCoeffs(lfGain, lfCutoff, lfBW, _sampleRate);

	m_b0 = A * ((A + 1) - (A - 1) * cosw0 + 2 * sqrt(A * alpha));
	m_b1 = 2 * A * ((A - 1) - (A + 1) * cosw0);
	m_b2 = A * ((A + 1) - (A - 1) * cosw0 - 2 * sqrt(A * alpha));
	m_a0 = (A + 1) + (A - 1) * cosw0 + 2 * sqrt(A * alpha);
	m_a1 = -2 * ((A - 1) + (A + 1) * cosw0);
	m_a2 = (A + 1) + (A - 1) * cosw0 - 2 * sqrt(A * alpha);
}
