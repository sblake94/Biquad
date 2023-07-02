#include "TitleLabel.h"

#include "../../CustomLookAndFeel.h"

GUI::Controls::Labels::TitleLabel::TitleLabel
(
	const char* _labelText, 
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	const int _parameterID,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::CustomLabel(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		GUI::CustomLookAndFeel::s_titleFont,
		2,
		_parameterID,
		_lookAndFeel)
{
}

GUI::Controls::Labels::TitleLabel::~TitleLabel()
{
}

void GUI::Controls::Labels::TitleLabel::paint(juce::Graphics& g)
{
	const juce::Rectangle<int> bounds = getLocalBounds().reduced(CustomLookAndFeel::s_controlBoundsMargin);

	BaseTypes::CustomLabel::paint(g);
}
