#include "BandwidthDial.h"

using namespace GUI::Controls::Dials;

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the bandwidth dial.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
BandwidthDial::BandwidthDial
(
	juce::ParameterID _parameterID,
	juce::LookAndFeel* _lookAndFeel,
	const char* _labelText,
	const int _xPos,
	const int _yPos,
	const float _defaultValue,
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval
)
	: BaseTypes::RotaryDial(
		_rangeMin,
		_rangeMax,
		_rangeInterval,
		_defaultValue,
		_labelText,
		_xPos,
		_yPos,
		_parameterID,
		_lookAndFeel)
{
	this->setNumDecimalPlacesToDisplay(1);
	this->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the bandwidth dial.
/// </summary>
BandwidthDial::~BandwidthDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void BandwidthDial::paint(juce::Graphics& g)
{
	BaseTypes::RotaryDial::paint(g);

	const int sliderTop = m_textBoxHeight;
	const juce::Rectangle<int> sliderBounds(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));
}