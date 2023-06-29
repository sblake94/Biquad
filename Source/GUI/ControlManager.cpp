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
		, m_lowFreqSlider(FrequencyDial("LowFreq", 1, 0, Processing::s_lowFreqCutoffParamID, _lookAndFeelPtr))
		, m_midFreqSlider(FrequencyDial("MidFreq", 2, 0, Processing::s_midFreqCutoffParamID, _lookAndFeelPtr))
		, m_highFreqSlider(FrequencyDial("HiFreq", 3, 0, Processing::s_highFreqCutoffParamID, _lookAndFeelPtr))
		, m_lowGainSlider(GainDial("LowGain", 1, 1, Processing::s_lowGainParamID, _lookAndFeelPtr))
		, m_midGainSlider(GainDial("MidGain", 2, 1, Processing::s_midGainParamID, _lookAndFeelPtr))
		, m_highGainSlider(GainDial("HiGain", 3, 1, Processing::s_highGainParamID, _lookAndFeelPtr))
		, m_lowBandwidthSlider(BandwidthDial("LowBW", 1, 2, Processing::s_lowBandwidthParamID, _lookAndFeelPtr))
		, m_midBandwidthSlider(BandwidthDial("MidBW", 2, 2, Processing::s_midBandwidthParamID, _lookAndFeelPtr))
		, m_highBandwidthSlider(BandwidthDial("HighBW", 3, 2, Processing::s_highBandwidthParamID, _lookAndFeelPtr))
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
	/// Distributes the paint call to all components.
	/// </summary>
	void ControlManager::paint(juce::Graphics& _graphics)
	{
		m_highFreqSlider.paint(_graphics);
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

		m_highBandwidthSlider.setBounds(
			controlXPos(m_highBandwidthSlider.m_xPos),
			controlYPos(m_highBandwidthSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_midBandwidthSlider.setBounds(
			controlXPos(m_midBandwidthSlider.m_xPos),
			controlYPos(m_midBandwidthSlider.m_yPos),
			cellWidth,
			cellHeight);

		m_lowBandwidthSlider.setBounds(
			controlXPos(m_lowBandwidthSlider.m_xPos),
			controlYPos(m_lowBandwidthSlider.m_yPos),
			cellWidth,
			cellHeight);

	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<juce::Component*> ControlManager::GetAllControls()
	{
		std::vector<juce::Component*> result;

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
}