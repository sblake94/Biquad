#pragma once

#include <JuceHeader.h>

namespace GUI::Controls
{
	/// <summary>
	/// Base class for all custom sliders
	/// </summary>
	class CustomSliderBase
	{
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="_paramID">The ID of the Slider</param>
		CustomSliderBase(juce::ParameterID _paramID) 
			: m_id(_paramID)
		{
		};

		/// <summary>
		/// The ID of the Slider
		/// </summary>
		juce::ParameterID m_id;
	};
}