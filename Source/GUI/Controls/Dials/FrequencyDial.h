/*
	==========================================================================================

	@Author : SBlake
	This class describes a Frequency Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
<<<<<<< HEAD:Source/GUI/Controls/Dials/FrequencyDial.h
#include "../BaseTypes/CustomControlBase.h"
#include "../BaseTypes/RotaryDial.h"
=======
#include "CustomSliderBase.h"
>>>>>>> master:Source/GUI/Controls/FrequencyDial.h

namespace GUI::Controls::Dials
{	
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for frequency parameters.
	/// </summary>
	class FrequencyDial
<<<<<<< HEAD:Source/GUI/Controls/Dials/FrequencyDial.h
		: public BaseTypes::RotaryDial
=======
		: public juce::Slider
		, public CustomSliderBase
>>>>>>> master:Source/GUI/Controls/FrequencyDial.h
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		FrequencyDial(
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel,
			const char* _labelText,
			const int _xPos,
			const int _yPos,
<<<<<<< HEAD:Source/GUI/Controls/Dials/FrequencyDial.h
			const float _defaultValue,
			const float _rangeMin = 20.0f,
			const float _rangeMax = 20000.0f);
=======
			juce::ParameterID _parameterID,
			juce::LookAndFeel* _lookAndFeel = nullptr
		);
>>>>>>> master:Source/GUI/Controls/FrequencyDial.h
		~FrequencyDial();
		
		void paint(juce::Graphics& g) override;
		
		const char* m_labelText;
		int m_xPos, m_yPos;

<<<<<<< HEAD:Source/GUI/Controls/Dials/FrequencyDial.h
	private: /////////////////////////////////////////////////////////////////////////////////////////
=======
	private:
>>>>>>> master:Source/GUI/Controls/FrequencyDial.h
		void SetParameterID(const juce::ParameterID _parameterID);
		juce::ParameterID m_parameterID;

		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyDial);
	};
}