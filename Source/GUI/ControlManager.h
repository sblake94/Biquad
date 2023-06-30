/*
	==========================================================================================

	@Author : SBlake
	This class handles contains all of the dials, knobs, 
	and buttons of the GUI

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Controls/Dials/FrequencyDial.h"
#include "Controls/Dials/GainDial.h"
#include "Controls/Dials/BandwidthDial.h"
#include "Controls/Buttons/LatchButton.h"

using namespace GUI::Controls;

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		This class handles contains all of the dials, knobs,
	///		and buttons of the GUI
	/// </summary>
	class ControlManager
	{
	public: /////////////////////////////////////////////////////////////////////////////////////
		ControlManager(
			const int _windowWidth, 
			const int _windowHeight,
			juce::LookAndFeel* _lookAndFeelPtr = nullptr);
		~ControlManager();

		void paint(juce::Graphics& _graphics);
		void resized(const int _newWidth, const int _newHeight);

		const std::vector<juce::Component*> GetAllSliders();
		const std::vector<juce::Component*> GetAllButtons();

	private: /////////////////////////////////////////////////////////////////////////////////////
		FrequencyDial m_highFreqSlider;
		FrequencyDial m_midFreqSlider;
		FrequencyDial m_lowFreqSlider;

		GainDial m_highGainSlider;
		GainDial m_midGainSlider;
		GainDial m_lowGainSlider;

		BandwidthDial m_highBandwidthSlider;
		BandwidthDial m_midBandwidthSlider;
		BandwidthDial m_lowBandwidthSlider;

		LatchButton m_engageHeatButton;

		const int m_margin = 20;
		const int m_controlGridSizeX = 6;
		const int m_controlGridSizeY = 6;
		const int m_gridSpacingX = 10;
		const int m_gridSpacingY = 10;

		int m_controlAreaWidth;
		int m_controlAreaHeight;
		int m_controlAreaX = m_margin;
		int m_controlAreaY = m_margin;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlManager);
	};
}