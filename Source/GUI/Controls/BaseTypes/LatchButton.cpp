#include "LatchButton.h"

using namespace GUI::Controls::BaseTypes;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// A base class for a button that can be latched on or off. Can also be instantiated itself
/// </summary>
/// <param name="_labelText">The text to display on the button</param>
/// <param name="_xPos">The x position of the button</param>
/// <param name="_yPos">The y position of the button</param>
/// <param name="_isLatched">Whether the button is latched on or off</param>
/// <param name="_parameterID">The ID of the parameter that the button controls</param>
/// <param name="_lookAndFeel">The look and feel to use for the button</param>
LatchButton::LatchButton
(
	const char* _labelText,
	const int _xPos,
	const int _yPos,
	const bool _isLatched,
	juce::ParameterID _parameterID,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::ToggleButton()
	, CustomControlBase(_labelText, _xPos, _yPos, _parameterID)
{
	this->setButtonText(_labelText);
	this->setComponentID(_labelText);
	this->setToggleState(_isLatched, juce::sendNotification);

	if (_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
LatchButton::~LatchButton()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the button
/// </summary>
/// <param name="g">The graphics context to paint to</param>
void LatchButton::paint(juce::Graphics& g)
{
	juce::ToggleButton::paint(g);

	const juce::Rectangle<int> textBoxBounds(getLocalBounds().removeFromTop(10));
	juce::LookAndFeel& lookAndFeel = getLookAndFeel();

	const int buttonTop = m_textBoxHeight;
	const juce::Rectangle<int> buttonBounce(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));

	const juce::String valueText(m_labelText);
	juce::Font font(18);
	g.setColour(lookAndFeel.findColour(juce::ToggleButton::textColourId));
	g.setFont(font);
	g.drawFittedText(valueText, textBoxBounds, juce::Justification::centred, 1);
}