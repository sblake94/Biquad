#include "CustomLabel.h"

#include "CustomControlBase.h"
#include "../../CustomLookAndFeel.h"

GUI::Controls::BaseTypes::CustomLabel::CustomLabel
(
	const char* _labelText, 
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	juce::ParameterID _parameterID, 
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Label(_labelText)
	, BaseTypes::CustomControlBase(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		_parameterID
	)
{
	m_labelText = _labelText;
}

GUI::Controls::BaseTypes::CustomLabel::~CustomLabel()
{
}

void GUI::Controls::BaseTypes::CustomLabel::paint(juce::Graphics& g)
{
	juce::Label::paint(g);

	const juce::Rectangle<int> bounds = getLocalBounds().reduced(5);

	g.setColour(GUI::CustomLookAndFeel::s_shadowColour);
	g.fillRoundedRectangle(bounds.toFloat(), GUI::CustomLookAndFeel::s_cornerRadius);

	g.setColour(GUI::CustomLookAndFeel::s_textColourBright);
	g.setFont(GUI::CustomLookAndFeel::s_font);
	g.drawFittedText(m_labelText, bounds, juce::Justification::centred, 1);
}
