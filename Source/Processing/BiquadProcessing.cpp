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
	int _sampleRate, 
	int _sampleFrames
)
{
	juce::AudioBuffer<float>& tempBuffer = _inputBuffer;
	bool heatEngaged = _params.GetBoolParams()[s_engageHeatParamID]->get();

	if (heatEngaged)
	{
		ApplyCurve(tempBuffer, _sampleFrames);
	}

	// Apply High Shelf
	m_biquadA.ApplyBiquad(
		tempBuffer, 
		tempBuffer, 
		_params, 
		BiquadUnit::FilterType::HighShelf, 
		_sampleRate, 
		_sampleFrames);

	// Apply Peak
	m_biquadB.ApplyBiquad(
		tempBuffer,
		tempBuffer,
		_params,
		BiquadUnit::FilterType::PeakShelf,
		_sampleRate,
		_sampleFrames);

	// Apply Low Shelf
	m_biquadC.ApplyBiquad(
		tempBuffer,
		tempBuffer,
		_params,
		BiquadUnit::FilterType::LowShelf,
		_sampleRate,
		_sampleFrames);

	// Remove Curve
	if (heatEngaged)
	{ 
		RemoveCurve(tempBuffer, _sampleFrames);
	}
	
	Clip(tempBuffer, -1.0, 1.0, _sampleFrames);

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