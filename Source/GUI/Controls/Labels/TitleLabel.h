#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomLabel.h"

namespace GUI::Controls::Labels
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A label for displaying large text
	/// </summary>
	class TitleLabel
		: public GUI::Controls::BaseTypes::CustomLabel
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		TitleLabel(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~TitleLabel();

		void paint(juce::Graphics& g) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////
	};
}