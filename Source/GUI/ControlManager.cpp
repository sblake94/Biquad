#include "ControlManager.h"

#include "../Processing/Parameters.h"
#include "../GUI/CustomLookAndFeel.h"

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

		, m_lowShelfBypass(EngageButton(Processing::s_lowBandBypassParamID, _lookAndFeelPtr, "Low Shelf", 0, 0, 2, 1))
		, m_midShelfBypass(EngageButton(Processing::s_midBandBypassParamID, _lookAndFeelPtr, "Mid Shelf", 2, 0, 2, 1))
		, m_highShelfBypass(EngageButton(Processing::s_highBandBypassParamID, _lookAndFeelPtr, "High Shelf", 4, 0, 2, 1))
		
		, m_lowFreqSlider(FrequencyDial(Processing::s_lowFreqCutoffParamID, _lookAndFeelPtr, "Freq", 0, 1, 2, 2, 100.0f, 20.0f, 1000.0f))
		, m_midFreqSlider(FrequencyDial(Processing::s_midFreqCutoffParamID, _lookAndFeelPtr, "Freq", 2, 1, 2, 2, 500.0f, 100.0f, 10000.0f))
		, m_highFreqSlider(FrequencyDial(Processing::s_highFreqCutoffParamID, _lookAndFeelPtr, "Freq", 4, 1, 2, 2, 10000.0f, 500.0f, 20000.0f))

		, m_lowGainSlider(GainDial(Processing::s_lowGainParamID, _lookAndFeelPtr, "Gain", 0, 3, 2, 2, 0.0f, -24.0f, 24.0f, 0.0f))
		, m_midGainSlider(GainDial(Processing::s_midGainParamID, _lookAndFeelPtr, "Gain", 2, 3, 2, 2, 0.0f, -24.0f, 24.0f, 0.0f))
		, m_highGainSlider(GainDial(Processing::s_highGainParamID, _lookAndFeelPtr, "Gain", 4, 3, 2, 2, 0.0f, -24.0f, 24.0f, 0.0f))
		
		, m_lowBandwidthSlider(BandwidthDial(Processing::s_lowBandwidthParamID, _lookAndFeelPtr, "BW", 0, 5, 2, 2))
		, m_midBandwidthSlider(BandwidthDial(Processing::s_midBandwidthParamID, _lookAndFeelPtr, "BW", 2, 5, 2, 2))
		, m_highBandwidthSlider(BandwidthDial(Processing::s_highBandwidthParamID, _lookAndFeelPtr, "BW", 4, 5, 2, 2))
		
		, m_engageHeatButton(EngageButton(Processing::s_engageHeatParamID, _lookAndFeelPtr, "Heat",			7, 4, 2, 1))
		, m_heatGainSlider(GainDial(Processing::s_heatGainParamID, _lookAndFeelPtr, "Heat Gain",			7, 5, 2, 2, 0.0f, -12.0f, 12.0f, 0.0f))
		, m_masterBypassButton(EngageButton(Processing::s_masterBypassParamID, _lookAndFeelPtr, "Bypass",	9, 4, 2, 1))
		, m_masterGainSlider(GainDial(Processing::s_masterGainParamID, _lookAndFeelPtr, "Output Gain",		9, 5, 2, 2, 0.0f, -12.0f, 12.0f, 0.0f))
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
		// Draw control groups
		for (std::vector<juce::Component*> ctrlGroup : GetControlGroups())
		{
			// get the bounds of each control in the group
			juce::Rectangle<int> ctrlGroupBounds = juce::Rectangle<int>(0,0,0,0);
			for (juce::Component* component : ctrlGroup)
			{
				const juce::Rectangle<int> componentBounds = component->getBounds();
				ctrlGroupBounds = ctrlGroupBounds.getUnion(componentBounds);
			}

			_graphics.setGradientFill(
				GUI::CustomLookAndFeel::BackgroundGradient(
					ctrlGroupBounds.getTopLeft().toFloat(),
					ctrlGroupBounds.getBottomRight().toFloat()
				));
			_graphics.fillRoundedRectangle(ctrlGroupBounds.toFloat(), GUI::CustomLookAndFeel::s_cornerRadius);

			_graphics.setColour(GUI::CustomLookAndFeel::s_shadowColour);
			_graphics.drawRoundedRectangle(ctrlGroupBounds.toFloat()
				, GUI::CustomLookAndFeel::s_cornerRadius
				, GUI::CustomLookAndFeel::s_outlineThickness);
		}
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

		// get the width of each cell automatically
		const int cellWidth = gridWidth / m_controlGridSizeX;
		const int cellHeight = gridHeight / m_controlGridSizeY;

		auto controlXPos = [this, cellWidth](const int _x) -> int
		{
			return m_margin + _x * (cellWidth + m_gridSpacingX);
		};
		auto controlYPos = [this, cellHeight](const int _y) -> int
		{
			return m_margin + _y * (cellHeight + m_gridSpacingY);
		};

		// Iterate over your controls and set their positions
		for (GUI::Controls::BaseTypes::RotaryDial* rotaryDial : GetAllRotaryDials())
		{
			const int xPos = controlXPos(rotaryDial->m_xPos);
			const int yPos = controlYPos(rotaryDial->m_yPos);
			const int width = (cellWidth * rotaryDial->m_width) + (m_gridSpacingX * jmax(0, rotaryDial->m_width - 1));
			const int height = (cellHeight * rotaryDial->m_height) + (m_gridSpacingY * jmax(0, rotaryDial->m_height - 1));

			rotaryDial->setBounds(xPos, yPos, width, height);
		}

		for (GUI::Controls::BaseTypes::LatchButton* latchButton : GetAllLatchButtons())
		{
			const int xPos = controlXPos(latchButton->m_xPos);
			const int yPos = controlYPos(latchButton->m_yPos);
			const int width = (cellWidth * latchButton->m_width) + (m_gridSpacingX * jmax(0, latchButton->m_width - 1));
			const int height = (cellHeight * latchButton->m_height) + (m_gridSpacingY * jmax(0, latchButton->m_height - 1));

			latchButton->setBounds(xPos, yPos, width, height);
		}

		for (GUI::Controls::BaseTypes::CustomLabel* customLabel : GetAllCustomLabels())
		{
			const int xPos = controlXPos(customLabel->m_xPos);
			const int yPos = controlYPos(customLabel->m_yPos);
			const int width = (cellWidth * customLabel->m_width) + (m_gridSpacingX * jmax(0, customLabel->m_width - 1));
			const int height = (cellHeight * customLabel->m_height) + (m_gridSpacingY * jmax(0, customLabel->m_height - 1));

			customLabel->setBounds(xPos, yPos, width, height);
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

		result.push_back(&m_masterGainSlider);
		result.push_back(&m_heatGainSlider);

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

		result.push_back(&m_lowShelfBypass);
		result.push_back(&m_midShelfBypass);
		result.push_back(&m_highShelfBypass);

		return result;
	}

	const std::vector<BaseTypes::CustomLabel*> ControlManager::GetAllCustomLabels()
	{
		std::vector<BaseTypes::CustomLabel*> result;

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

		for (BaseTypes::CustomLabel* customLabelPtr : GetAllCustomLabels())
		{
			result.push_back(dynamic_cast<juce::Component*>(customLabelPtr));
		}

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of vectors, each containing grouped controls.
	/// </summary>
	/// <returns>Vector of vectors of Component*</returns>
	const std::vector<std::vector<juce::Component*>> ControlManager::GetControlGroups()
	{
		std::vector<std::vector<juce::Component*>> result;

		// Low Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_lowShelfBypass),
			dynamic_cast<juce::Component*>(&m_lowFreqSlider),
			dynamic_cast<juce::Component*>(&m_lowGainSlider),
			dynamic_cast<juce::Component*>(&m_lowBandwidthSlider)
		});

		// Mid Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_midShelfBypass),
			dynamic_cast<juce::Component*>(&m_midFreqSlider),
			dynamic_cast<juce::Component*>(&m_midGainSlider),
			dynamic_cast<juce::Component*>(&m_midBandwidthSlider)
		});

		// High Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_highShelfBypass),
			dynamic_cast<juce::Component*>(&m_highFreqSlider),
			dynamic_cast<juce::Component*>(&m_highGainSlider),
			dynamic_cast<juce::Component*>(&m_highBandwidthSlider)
		});

		// Master
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_masterBypassButton),
			dynamic_cast<juce::Component*>(&m_masterGainSlider),

			dynamic_cast<juce::Component*>(&m_engageHeatButton),
			dynamic_cast<juce::Component*>(&m_heatGainSlider)
		});

		return result;
	}
}