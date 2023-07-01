#include "BiquadProcessing.h"
#include "Parameters.h"

using namespace Processing;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
BiquadProcessing::BiquadProcessing()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
BiquadProcessing::~BiquadProcessing()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Process the audio buffer
/// </summary>
void BiquadProcessing::ProcessReplacing
(
	juce::AudioBuffer<float>& _inputBuffer,
	juce::AudioBuffer<float>& _outputBuffer,
	Parameters& _params, 
	const int _sampleRate, 
	const int _sampleFrames
)
{
	// Bypass Logic
	if (_params.GetBoolParams()[s_masterBypassParamID]->get() == true) 
	{	
		_outputBuffer = _inputBuffer;
		return;
	}

	juce::AudioBuffer<float>& tempBuffer = _inputBuffer;

	const bool heatEngaged = _params.GetBoolParams()[s_engageHeatParamID]->get();
	const bool lowShelfEngaged = _params.GetBoolParams()[s_lowBandBypassParamID]->get();
	const bool midPeakEngaged = _params.GetBoolParams()[s_midBandBypassParamID]->get();
	const bool highShelfEngaged = _params.GetBoolParams()[s_highBandBypassParamID]->get();

	// Apply Heat Curve
	if (heatEngaged)
	{
		/*ApplyGain(tempBuffer, _params.GetSliderParams()[s_heatGainParamID]->get(), _sampleFrames);
		ApplyCurve(tempBuffer, _sampleFrames);*/
	}

	// Apply High Shelf
	if (highShelfEngaged)
	{
		m_biquadA.ApplyBiquad(
			tempBuffer, 
			tempBuffer, 
			_params, 
			BiquadUnit::FilterType::HighShelf, 
			_sampleRate, 
			_sampleFrames);
	}

	// Apply Peak
	if (midPeakEngaged)
	{
		m_biquadB.ApplyBiquad(
			tempBuffer,
			tempBuffer,
			_params,
			BiquadUnit::FilterType::PeakShelf,
			_sampleRate,
			_sampleFrames);
	}

	// Apply Low Shelf
	if (lowShelfEngaged)
	{
		m_biquadC.ApplyBiquad(
			tempBuffer,
			tempBuffer,
			_params,
			BiquadUnit::FilterType::LowShelf,
			_sampleRate,
			_sampleFrames);
	}

	// Remove Heat Curve
	if (heatEngaged)
	{ 
		/*RemoveCurve(tempBuffer, _sampleFrames);
		ApplyGain(tempBuffer, 2.0f - (_params.GetSliderParams()[s_heatGainParamID]->get()), _sampleFrames);*/
	}
	
	Clip(tempBuffer, -1.0, 1.0, _sampleFrames);

	// Output Gain
	ApplyGain(tempBuffer, _params.GetSliderParams()[s_masterGainParamID]->get(), _sampleFrames);

	_outputBuffer = tempBuffer;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Applies a sine curve to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_sampleFrames"></param>
void BiquadProcessing::ApplyCurve(juce::AudioSampleBuffer& _buffer, int _sampleFrames)
{
	while (--_sampleFrames > 0)
	{
		// Get the sample
		float sampleL = _buffer.getSample(0, _sampleFrames);
		float sampleR = _buffer.getSample(1, _sampleFrames);
				
		sampleL = sinf(sampleL * 0.5f * MathConstants<float>::pi);
		sampleR = sinf(sampleR * 0.5f * MathConstants<float>::pi);

		_buffer.setSample(0, _sampleFrames, sampleL);
		_buffer.setSample(1, _sampleFrames, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Applies an inverse sine curve to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_sampleFrames"></param>
void BiquadProcessing::RemoveCurve(juce::AudioSampleBuffer& _buffer, int _sampleFrames)
{
	Clip(_buffer, -1.0, 1.0, _sampleFrames);

	while (--_sampleFrames > 0)
	{
		// Get the sample
		float sampleL = _buffer.getSample(0, _sampleFrames);
		float sampleR = _buffer.getSample(1, _sampleFrames);

		sampleL = asinf(sampleL) / (0.5f * MathConstants<float>::pi);
		sampleR = asinf(sampleR) / (0.5f * MathConstants<float>::pi);

		_buffer.setSample(0, _sampleFrames, sampleL);
		_buffer.setSample(1, _sampleFrames, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Clip the output to prevent amplitude spikes
/// </summary>
/// <param name="_sampleFrames"></param>
/// <param name="tempBuffer"></param>
void BiquadProcessing::Clip
(
	juce::AudioSampleBuffer& tempBuffer, 
	float _min,
	float _max,
	int _sampleFrames
)
{
	while (--_sampleFrames > 0)
	{
		if (tempBuffer.getSample(0, _sampleFrames) > 1.0f)
		{
			tempBuffer.setSample(0, _sampleFrames, 1.0f);
		}
		else if (tempBuffer.getSample(0, _sampleFrames) < -1.0f)
		{
			tempBuffer.setSample(0, _sampleFrames, -1.0f);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Apply Gain to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_gain"></param>
/// <param name="_sampleFrames"></param>
void BiquadProcessing::ApplyGain
(
	juce::AudioSampleBuffer& _buffer,
	const float const& _gainDB,
	int _sampleFrames
)
{
	const float gain = Decibels::decibelsToGain(_gainDB);

	while (--_sampleFrames > 0)
	{
		// Get the sample
		float sampleL = _buffer.getSample(0, _sampleFrames);
		float sampleR = _buffer.getSample(1, _sampleFrames);

		sampleL *= gain;
		sampleR *= gain;

		_buffer.setSample(0, _sampleFrames, sampleL);
		_buffer.setSample(1, _sampleFrames, sampleR);
	}
}