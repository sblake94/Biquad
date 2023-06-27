/*
	==========================================================================================

	@Author : SBlake
	This class handles contains all of the dials, knobs, 
	and buttons of the GUI

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Controls/FrequencyDial.h"

using namespace GUI::Controls;

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	class ControlManager
	{
	public:
		ControlManager(
			const int _windowWidth, 
			const int _windowHeight,
			juce::LookAndFeel* _lookAndFeelPtr = nullptr);
		~ControlManager();

		void paint(juce::Graphics& _graphics);
		void resized(const int _newWidth, const int _newHeight);

		const std::vector<juce::Component*> GetAllControls();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlManager);

		FrequencyDial m_highFreqSlider;
		FrequencyDial m_midFreqSlider;
		FrequencyDial m_lowFreqSlider;

		const int m_margin = 20;
		const int m_controlGridSizeX = 6;
		const int m_controlGridSizeY = 6;
		const int m_gridSpacingX = 10;  // Horizontal spacing between grid cells
		const int m_gridSpacingY = 10;  // Vertical spacing between grid cells


		int m_controlAreaWidth;
		int m_controlAreaHeight;
		int m_controlAreaX = m_margin;
		int m_controlAreaY = m_margin;
	};
}