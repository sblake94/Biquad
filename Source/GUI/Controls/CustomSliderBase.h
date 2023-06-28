#pragma once

#include <JuceHeader.h>

namespace GUI::Controls
{
	class CustomSliderBase
	{
	public:
		CustomSliderBase(juce::ParameterID _paramID) 
			: id(_paramID)
		{
		};

		juce::ParameterID id;
	};
}