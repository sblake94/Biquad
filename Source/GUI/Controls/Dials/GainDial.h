/*
	==========================================================================================

	@Author : SBlake
	This class describes a Gain Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../CustomControlBase.h"

namespace GUI::Controls
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for Gain-specific parameters.
	/// </summary>
	class GainDial
		: public juce::Slider
		, public CustomControlBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		GainDial(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~GainDial();

		void paint(juce::Graphics& g) override;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainDial)
	};
}