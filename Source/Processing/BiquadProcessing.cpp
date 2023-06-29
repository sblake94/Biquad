#include "BiquadProcessing.h"
#include "Parameters.h"

using namespace Processing;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
BiquadProcessor::BiquadProcessor()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
BiquadProcessor::~BiquadProcessor()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Process the audio buffer
/// </summary>
void BiquadProcessor::ProcessReplacing
(
	juce::AudioBuffer<float>& _inputBuffer,
	juce::AudioBuffer<float>& _outputBuffer,
	Processing::Parameters& _params, 
	int _sampleRate, 
	int _sampleFrames
)
{
	juce::AudioBuffer<float>& tempBuffer = _inputBuffer;

	// Apply processing to tempBuffer
	m_biquadA.ApplyBiquad(
		tempBuffer, 
		tempBuffer, 
		_params, 
		BiquadUnit::FilterType::HighShelf, 
		_sampleRate, 
		_sampleFrames);

	m_biquadB.ApplyBiquad(
		tempBuffer,
		tempBuffer,
		_params,
		BiquadUnit::FilterType::PeakShelf,
		_sampleRate,
		_sampleFrames);

	m_biquadC.ApplyBiquad(
		tempBuffer,
		tempBuffer,
		_params,
		BiquadUnit::FilterType::LowShelf,
		_sampleRate,
		_sampleFrames);

	_outputBuffer = tempBuffer;
}