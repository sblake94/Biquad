#include "FrequencyDial.h"

using namespace GUI::Controls::Dials;

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
	juce::ParameterID _parameterID,
	juce::LookAndFeel* _lookAndFeel,
	const char* _labelText,
	const int _xPos,
	const int _yPos,
	const float _defaultValue,
	const float _rangeMin,
	const float _rangeMax
)
	: BaseTypes::RotaryDial(
		_rangeMin,
		_rangeMax,
		0.0f,
		_defaultValue,
		_labelText,
		_xPos,
		_yPos,
		_parameterID,
		_lookAndFeel)
{
	this->setSkewFactor(0.29f);
	this->setNumDecimalPlacesToDisplay(0);
	
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
	BaseTypes::RotaryDial::paint(g);

	const int sliderTop = m_textBoxHeight;
	const juce::Rectangle<int> sliderBounds(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));
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
