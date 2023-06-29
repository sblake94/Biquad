#pragma once

#include <JuceHeader.h>

namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom look and feel for the GUI. 
	/// </summary>
	class CustomLookAndFeel
		: public juce::LookAndFeel_V4
	{
	public: ////////////////////////////////////////////////////////////////////////////////////////////////

		CustomLookAndFeel();
		~CustomLookAndFeel();

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

	private:////////////////////////////////////////////////////////////////////////////////////////////////

		juce::Colour m_dialFillColour = juce::Colour(17u,17u,17u);
		juce::Colour m_dialOutlineColour = juce::Colour(17u, 17u, 17u);
		juce::Colour m_dialTextColour = juce::Colour(255u, 255u, 255u);
		juce::Colour m_dialIndicatorColour = juce::Colour(153u, 51u, 0u);

		juce::Font m_dialFont = juce::Font("Montserrat", 18, 20);

		float m_dialOutlineThickness = 3.0f;
		float m_dialIndicatorThickness = 10.0f;
	};
}
