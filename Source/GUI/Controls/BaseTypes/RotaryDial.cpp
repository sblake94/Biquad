#include "RotaryDial.h"

using namespace GUI::Controls::BaseTypes;
/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
/// <param name="_rangeMin">The minimum value of the slider</param>
/// <param name="_rangeMax">The maximum value of the slider</param>
/// <param name="_rangeInterval">The interval between values of the slider</param>
/// <param name="_defaultValue">The default value of the slider</param>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_paramID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
RotaryDial::RotaryDial
(
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	const float _defaultValue,
	const char* _labelText,
	const int _xPos,
	const int _yPos,
	juce::ParameterID _paramID,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Slider()
	, CustomControlBase(_labelText, _xPos, _yPos, _paramID)
{
	this->setRange(_rangeMin, _rangeMax, _rangeInterval);
	this->setValue(_defaultValue);

	this->setTooltip(_labelText);
	this->setComponentID(_labelText);

	this->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

	if(_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
RotaryDial::~RotaryDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
///	</summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void RotaryDial::paint(juce::Graphics& g)
{
	juce::Slider::paint(g);

	const juce::Rectangle<int> textBoxBounds(getLocalBounds().removeFromTop(10));
	juce::LookAndFeel& lookAndFeel = getLookAndFeel();
		
	const juce::String valueText(m_labelText);
	juce::Font font(18);
	g.setColour(lookAndFeel.findColour(juce::Slider::textBoxTextColourId));
	g.setFont(font);
	g.drawFittedText(valueText, textBoxBounds, juce::Justification::centred, 1);
}
