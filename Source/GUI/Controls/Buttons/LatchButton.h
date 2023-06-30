/*
	==========================================================================================

	@Author : SBlake
	This class describes a binary state button that can be latched on or off

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../CustomControlBase.h"

namespace GUI::Controls 
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A button that can be latched on or off
	/// </summary>
	class LatchButton
		: public juce::ToggleButton
		, public CustomControlBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		LatchButton(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr
		);
		~LatchButton();

		void paint(juce::Graphics& g) override;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		void SetParameterID(const juce::ParameterID _parameterID);
		juce::ParameterID m_parameterID;

		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LatchButton);
	};
}