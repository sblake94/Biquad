/*
	==========================================================================================

	@Author : SBlake
	This class describes a binary state button that can be latched on or off

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/LatchButton.h"

namespace GUI::Controls::Buttons
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A button that can be latched on or off
	/// </summary>
	class EngageButton
		: public BaseTypes::LatchButton
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		EngageButton(
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel,
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			bool _isEngaged = false
		);
		~EngageButton();

		void paint(juce::Graphics& g) override;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EngageButton);
	};
}