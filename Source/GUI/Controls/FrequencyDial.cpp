#include "FrequencyDial.h"

using namespace GUI::Controls;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the FrequencyDial class.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
FrequencyDial::FrequencyDial
(
	const char* _labelText,
	const int _xPos,
	const int _yPos,
	juce::ParameterID _parameterID,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Slider(_labelText)
	, CustomSliderBase(_parameterID)
	, m_labelText(_labelText)
	, m_xPos(_xPos)
	, m_yPos(_yPos)
{
	this->setRange(20.0, 20000.0, 0.0);
	this->setValue(20000.0);
	this->setSkewFactorFromMidPoint(2000.0);
	this->setNumDecimalPlacesToDisplay(0);
	this->setTooltip(_labelText);
	
	this->setComponentID(_labelText);
	

	this->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	this->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);

	if(_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the FrequencyDial class.
/// </summary>
FrequencyDial::~FrequencyDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void FrequencyDial::paint(juce::Graphics& g)
{
	const juce::Rectangle<int> textBoxBounds(getLocalBounds().removeFromTop(10));
	juce::LookAndFeel& lookAndFeel = getLookAndFeel();
	
	const int sliderTop = m_textBoxHeight;
	const juce::Rectangle<int> sliderBounds(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));
	juce::Slider::paint(g);

	const juce::String valueText(m_labelText);
	juce::Font font(18);
	g.setColour(lookAndFeel.findColour(juce::Slider::textBoxTextColourId));
	g.setFont(font);
	g.drawFittedText(valueText, textBoxBounds, juce::Justification::centred, 1);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the ID of the parameter that the dial is linked to.
/// </summary>
/// <param name="_parameterID"></param>
void FrequencyDial::SetParameterID(const juce::ParameterID _parameterID)
{
	this->m_parameterID = _parameterID;
}
