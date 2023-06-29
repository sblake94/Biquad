#include "BandwidthDial.h"

using namespace GUI::Controls;

/////////////////////////////////////////////////////////////////////////////////////
BandwidthDial::BandwidthDial
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
	this->setRange(0.0001, 4.0, 0.0);
	this->setValue(1.0);
	this->setNumDecimalPlacesToDisplay(1);
	this->setTooltip(_labelText);
	
	this->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	this->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);

	if(_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////
BandwidthDial::~BandwidthDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////
void BandwidthDial::paint(juce::Graphics& g)
{
	/*
	*   TODO: I think there could be a better way to do this,
	*	seems like we're doing all the maths twice.
	*	- Can we just store the variables here as members?
	*/

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
