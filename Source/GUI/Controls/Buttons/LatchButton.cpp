#include "LatchButton.h"

using namespace GUI::Controls;

LatchButton::LatchButton
(
	const char* _labelText, 
	const int _xPos, 
	const int _yPos, 
	juce::ParameterID _parameterID, 
	juce::LookAndFeel* _lookAndFeel
)
	: juce::ToggleButton(_labelText)
	, CustomControlBase(_parameterID)
	, m_labelText(_labelText)
	, m_xPos(_xPos)
	, m_yPos(_yPos)
{
	this->setClickingTogglesState(true);
	this->setTooltip(_labelText);
	this->setComponentID(_labelText);
	this->setButtonText(_labelText);

	if(_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

LatchButton::~LatchButton()
{
}

void LatchButton::paint(juce::Graphics& g)
{
	const juce::Rectangle<int> textBoxBounds(getLocalBounds().removeFromTop(10));
	juce::LookAndFeel& lookAndFeel = getLookAndFeel();

	const int buttonTop = m_textBoxHeight;
	const juce::Rectangle<int> buttonBounce(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));
	juce::ToggleButton::paint(g);

	const juce::String valueText(m_labelText);
	juce::Font font(18);
	g.setColour(lookAndFeel.findColour(juce::ToggleButton::textColourId));
	g.setFont(font);
	g.drawFittedText(valueText, textBoxBounds, juce::Justification::centred, 1);
}

void GUI::Controls::LatchButton::SetParameterID(const juce::ParameterID _parameterID)
{
	this->m_parameterID = _parameterID;
}
