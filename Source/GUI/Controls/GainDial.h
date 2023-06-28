#pragma once
#include <JuceHeader.h>

namespace GUI::Controls
{
	class GainDial
		: public juce::Slider
	{
	public:
		GainDial(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~GainDial();

		void paint(juce::Graphics& g) override;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private:
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainDial)
	};
}