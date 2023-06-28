/*
	==========================================================================================

	@Author : SBlake
	This class describes a slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace GUI::Controls
{	
	/// <summary>
	/// A custom slider class for the frequency dial.
	/// </summary>
	class FrequencyDial
		: public juce::Slider
	{
	public:
		FrequencyDial(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~FrequencyDial();

		void paint(juce::Graphics& g) override;
		
		const char* m_labelText;
		int m_xPos, m_yPos;

	private:
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyDial);
	};
}