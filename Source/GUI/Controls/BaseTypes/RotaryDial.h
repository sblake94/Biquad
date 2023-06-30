#pragma once

#include <JuceHeader.h>

#include "CustomControlBase.h"

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A base class for all rotary dials
	/// </summary>
	class RotaryDial
		: public juce::Slider
		, public CustomControlBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		RotaryDial(
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _paramID,
			juce::LookAndFeel* _lookAndFeel);
		~RotaryDial();

		virtual void paint(juce::Graphics& _graphics) override;

	private://///////////////////////////////////////////////////////////////////////////////////////
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryDial);
	};
}