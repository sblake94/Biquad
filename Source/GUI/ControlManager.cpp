#include "ControlManager.h"

#include "../Processing/Parameters.h"

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Constructor for the ControlManager class.
	/// </summary>
	/// <param name="_windowWidth">The width of the editor window</param>
	/// <param name="_windowHeight">The height of the editor window</param>
	/// <param name="_lookAndFeelPtr">The custom LookAndFeel to be used when drawing the controls</param>
	ControlManager::ControlManager
	(
		const int _windowWidth,
		const int _windowHeight,
		juce::LookAndFeel* _lookAndFeelPtr
	)
		: m_controlAreaHeight(_windowHeight - 2 * m_margin)
		, m_controlAreaWidth(_windowWidth - 2 * m_margin)
		, m_lowFreqSlider(FrequencyDial(Processing::s_lowFreqCutoffParamID, _lookAndFeelPtr, "LowFreq", 0, 0, 100.0f, 20.0f, 1000.0f))
		, m_midFreqSlider(FrequencyDial(Processing::s_midFreqCutoffParamID, _lookAndFeelPtr, "MidFreq", 1, 0, 500.0f, 100.0f, 10000.0f))
		, m_highFreqSlider(FrequencyDial(Processing::s_highFreqCutoffParamID, _lookAndFeelPtr, "HighFreq", 2, 0, 10000.0f, 500.0f, 20000.0f))
		, m_lowGainSlider(GainDial(Processing::s_lowGainParamID, _lookAndFeelPtr, "LowGain", 0, 1, 0.0f, -24.0f, 24.0f, 0.0f))
		, m_midGainSlider(GainDial(Processing::s_midGainParamID, _lookAndFeelPtr, "MidGain", 1, 1, 0.0f, -24.0f, 24.0f, 0.0f))
		, m_highGainSlider(GainDial(Processing::s_highGainParamID, _lookAndFeelPtr, "HighGain", 2, 1, 0.0f, -24.0f, 24.0f, 0.0f))
		, m_lowBandwidthSlider(BandwidthDial(Processing::s_lowBandwidthParamID, _lookAndFeelPtr, "LowBandWidth", 0, 2))
		, m_midBandwidthSlider(BandwidthDial(Processing::s_midBandwidthParamID, _lookAndFeelPtr, "MidBandWidth", 1, 2))
		, m_highBandwidthSlider(BandwidthDial(Processing::s_highBandwidthParamID, _lookAndFeelPtr, "HighBandWidth", 2, 2))
		, m_engageHeatButton(EngageButton(Processing::s_engageHeatParamID, _lookAndFeelPtr, "Heat", 5, 1))
		, m_masterBypassButton(EngageButton(Processing::s_masterBypassParamID, _lookAndFeelPtr, "Bypass", 5, 0))
	{
		
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Destructor for the ControlManager class.
	/// </summary>
	ControlManager::~ControlManager()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Paint the ControlManager.
	/// </summary>
	void ControlManager::paint(juce::Graphics& _graphics)
	{
		
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Resizes and Repositions all components.
	/// </summary>
	/// <param name="_newWidth"></param>
	/// <param name="_newHeight"></param>
	void ControlManager::resized
	(
		const int _newWidth, 
		const int _newHeight
	)
	{
		const int gridWidth = _newWidth - (m_controlGridSizeX - 1) * m_gridSpacingX;
		const int gridHeight = _newHeight - (m_controlGridSizeY - 1) * m_gridSpacingY;

		const int cellWidth = 100;
		const int cellHeight = 100;

		auto controlXPos = [this, cellWidth](const int _x) -> int
		{
			return m_margin + _x * (cellWidth + m_gridSpacingX);
		};
		auto controlYPos = [this, cellHeight](const int _y) -> int
		{
			return m_margin + _y * (cellHeight + m_gridSpacingY);
		};

		// Iterate over your controls and set their positions
		for (auto* rotaryDial : GetAllRotaryDials())
		{
			rotaryDial->setBounds(
				controlXPos(rotaryDial->m_xPos),
				controlYPos(rotaryDial->m_yPos),
				cellWidth,
				cellHeight);
		}

		for (auto* latchButton : GetAllLatchButtons())
		{
			latchButton->setBounds(
				controlXPos(latchButton->m_xPos),
				controlYPos(latchButton->m_yPos),
				cellWidth,
				cellHeight);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::RotaryDial*> ControlManager::GetAllRotaryDials()
	{
		std::vector<BaseTypes::RotaryDial*> result;

		result.push_back(&m_lowFreqSlider);
		result.push_back(&m_midFreqSlider);
		result.push_back(&m_highFreqSlider);

		result.push_back(&m_lowGainSlider);
		result.push_back(&m_midGainSlider);
		result.push_back(&m_highGainSlider);

		result.push_back(&m_lowBandwidthSlider);
		result.push_back(&m_midBandwidthSlider);
		result.push_back(&m_highBandwidthSlider);

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all buttons.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::LatchButton*> ControlManager::GetAllLatchButtons()
	{
		std::vector<BaseTypes::LatchButton*> result;

		result.push_back(&m_engageHeatButton);
		result.push_back(&m_masterBypassButton);

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<juce::Component*> ControlManager::GetAllCustomControls()
	{
		std::vector<juce::Component*> result;

		for (BaseTypes::RotaryDial* rotaryDialPtr : GetAllRotaryDials())
		{
			result.push_back(dynamic_cast<juce::Component*>(rotaryDialPtr));
		}

		for (BaseTypes::LatchButton* latchButtonPtr : GetAllLatchButtons())
		{
			result.push_back(dynamic_cast<juce::Component*>(latchButtonPtr));
		}

		return result;
	}
}