#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Base class for all custom sliders
	/// </summary>
	class CustomControlBase
	{
	public://///////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="_paramID">The ID of the Slider</param>
		inline CustomControlBase(
			const char* _labelText,
			const int _xPos,
			const int _yPos,
			juce::ParameterID _paramID)
			: m_id(_paramID)
			, m_labelText(_labelText)
			, m_xPos(_xPos)
			, m_yPos(_yPos)
		{
		};

		/////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// The ID of the Slider
		/// </summary>
		juce::ParameterID m_id;

		const char* m_labelText;
		int m_xPos, m_yPos;

	private://///////////////////////////////////////////////////////////////////////////////////////
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomControlBase);
	};
}