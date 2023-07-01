#pragma once
#include <JuceHeader.h>
#include "../BaseTypes/RotaryDial.h"

namespace GUI::Controls::Dials
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A dial for controlling the bandwidth of a filter.
	/// </summary>
	class BandwidthDial
		: public BaseTypes::RotaryDial
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		BandwidthDial(
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel,
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const float _defaultValue = 1.0f,
			const float _rangeMin = 0.001f,
			const float _rangeMax = 8.0f,
			const float _rangeInterval = 0.0f);
		~BandwidthDial();

		void paint(juce::Graphics& g) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandwidthDial)
	};
}