#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomLabel.h"

namespace GUI::Controls::Labels
{
	// a class that inherits from juce::Label
	class StaticLabel
		: public GUI::Controls::BaseTypes::CustomLabel
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		StaticLabel(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~StaticLabel();

		void paint(juce::Graphics& g) override;

	private ://///////////////////////////////////////////////////////////////////////////////////////
		
		const char* m_labelText;
			
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticLabel);
	};
}