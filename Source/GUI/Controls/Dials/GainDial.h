/*
	==========================================================================================

	@Author : SBlake
	This class describes a Gain Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once
#include <JuceHeader.h>
<<<<<<< HEAD:Source/GUI/Controls/Dials/GainDial.h
#include "../BaseTypes/RotaryDial.h"
=======
#include "CustomSliderBase.h"
>>>>>>> master:Source/GUI/Controls/GainDial.h

namespace GUI::Controls::Dials
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for Gain-specific parameters.
	/// </summary>
	class GainDial
<<<<<<< HEAD:Source/GUI/Controls/Dials/GainDial.h
		: public BaseTypes::RotaryDial
=======
		: public juce::Slider
		, public CustomSliderBase
>>>>>>> master:Source/GUI/Controls/GainDial.h
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		GainDial(
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel,
			const char* _labelText,
			const int _xPos,
			const int _yPos,
<<<<<<< HEAD:Source/GUI/Controls/Dials/GainDial.h
			const float _defaultValue = 0.0f,
			const float _rangeMin = -12.0f,
			const float _rangeMax = 12.0f,
			const float _rangeInterval = 0.0f);
=======
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr);
>>>>>>> master:Source/GUI/Controls/GainDial.h
		~GainDial();

		void paint(juce::Graphics& g) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainDial)
	};
}