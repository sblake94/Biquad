/*
	==========================================================================================

	@Author : SBlake
	This class describes a Frequency Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomSliderBase.h"

namespace GUI::Controls
{	
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for frequency parameters.
	/// </summary>
	class FrequencyDial
		: public juce::Slider
		, public CustomSliderBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		FrequencyDial(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr
		);

		~FrequencyDial();
		
		void paint(juce::Graphics& g) override;
		
		const char* m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		void SetParameterID(const juce::ParameterID _parameterID);
		juce::ParameterID m_parameterID;

		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyDial);
	};
}