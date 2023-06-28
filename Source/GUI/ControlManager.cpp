#include "ControlManager.h"

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	ControlManager::ControlManager
	(
		const int _windowWidth,
		const int _windowHeight,
		juce::LookAndFeel* _lookAndFeelPtr
	)
		: m_controlAreaHeight(_windowHeight - 2 * m_margin)
		, m_controlAreaWidth(_windowWidth - 2 * m_margin)
		, m_lowFreqSlider(FrequencyDial("Low Freq", 1, 0, _lookAndFeelPtr))
		, m_midFreqSlider(FrequencyDial("Mid Freq", 2, 0, _lookAndFeelPtr))
		, m_highFreqSlider(FrequencyDial("Hi Freq", 3, 0, _lookAndFeelPtr))
		, m_lowGainSlider(GainDial("Low Gain", 1, 1, _lookAndFeelPtr))
		, m_midGainSlider(GainDial("Mid Gain", 2, 1, _lookAndFeelPtr))
		, m_highGainSlider(GainDial("Hi Gain", 3, 1, _lookAndFeelPtr))
		, m_lowResSlider(ResonanceDial("Low Res", 1, 2, _lookAndFeelPtr))
		, m_midResSlider(ResonanceDial("Mid Res", 2, 2, _lookAndFeelPtr))
		, m_highResSlider(ResonanceDial("Hi Res", 3, 2, _lookAndFeelPtr))
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	ControlManager::~ControlManager()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	void ControlManager::paint(juce::Graphics& _graphics)
	{
		m_highFreqSlider.paint(_graphics);
	}

	/////////////////////////////////////////////////////////////////////////////////////
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
		m_highFreqSlider.setBounds(
			controlXPos(m_highFreqSlider.m_xPos),
			controlYPos(m_highFreqSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_midFreqSlider.setBounds(
			controlXPos(m_midFreqSlider.m_xPos),
			controlYPos(m_midFreqSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_lowFreqSlider.setBounds(
			controlXPos(m_lowFreqSlider.m_xPos),
			controlYPos(m_lowFreqSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_highGainSlider.setBounds(
			controlXPos(m_highGainSlider.m_xPos),
			controlYPos(m_highGainSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_midGainSlider.setBounds(
			controlXPos(m_midGainSlider.m_xPos),
			controlYPos(m_midGainSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_lowGainSlider.setBounds(
			controlXPos(m_lowGainSlider.m_xPos),
			controlYPos(m_lowGainSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_highResSlider.setBounds(
			controlXPos(m_highResSlider.m_xPos),
			controlYPos(m_highResSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_midResSlider.setBounds(
			controlXPos(m_midResSlider.m_xPos),
			controlYPos(m_midResSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_lowResSlider.setBounds(
			controlXPos(m_lowResSlider.m_xPos),
			controlYPos(m_lowResSlider.m_yPos),
			cellWidth,
			cellHeight);

	}

	/////////////////////////////////////////////////////////////////////////////////////
	const std::vector<juce::Component*> ControlManager::GetAllControls()
	{
		std::vector<juce::Component*> result;

		result.push_back(&m_lowFreqSlider);
		result.push_back(&m_midFreqSlider);
		result.push_back(&m_highFreqSlider);

		result.push_back(&m_lowGainSlider);
		result.push_back(&m_midGainSlider);
		result.push_back(&m_highGainSlider);

		result.push_back(&m_lowResSlider);
		result.push_back(&m_midResSlider);
		result.push_back(&m_highResSlider);

		return result;
	}
}