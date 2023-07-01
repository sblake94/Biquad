#include "StaticLabel.h"

#include "../../../GUI/CustomLookAndFeel.h"

GUI::Controls::Labels::StaticLabel::StaticLabel
(
	const char* _labelText, 
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	juce::ParameterID _paramID,
	juce::LookAndFeel* _lookAndFeel
)
	: CustomLabel(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		_paramID,
		_lookAndFeel
	)
{
	
}

GUI::Controls::Labels::StaticLabel::~StaticLabel()
{
}

void GUI::Controls::Labels::StaticLabel::paint(juce::Graphics& g)
{
	GUI::Controls::BaseTypes::CustomLabel::paint(g);
}
