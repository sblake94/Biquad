#pragma once
#include <JuceHeader.h>
#include "CustomSliderBase.h"

namespace GUI::Controls
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A dial for controlling the bandwidth of a filter.
	/// </summary>
	class BandwidthDial
		: public juce::Slider
		, public CustomSliderBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		BandwidthDial(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~BandwidthDial();

		void paint(juce::Graphics& g) override;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandwidthDial)
	};
}