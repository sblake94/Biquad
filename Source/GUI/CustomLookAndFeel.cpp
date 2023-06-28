#include "CustomLookAndFeel.h"


/////////////////////////////////////////////////
GUI::CustomLookAndFeel::CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
GUI::CustomLookAndFeel::~CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
void GUI::CustomLookAndFeel::drawRotarySlider
(
	juce::Graphics& g, 
	int x, 
	int y, 
	int width, 
	int height, 
	float sliderPos, 
	const float rotaryStartAngle, 
	const float rotaryEndAngle, 
	juce::Slider& slider
)
{
	auto bounds = juce::Rectangle<float>(x, y, width, height);

	auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 3.5f;
	auto centreX = bounds.getCentreX();
	auto centreY = bounds.getCentreY();
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	// fill
	g.setColour(m_dialFillColour);
	g.fillEllipse(rx, ry, rw, rw);

	// outline
	g.setColour(m_dialOutlineColour);
	g.drawEllipse(rx, ry, rw, rw, m_dialOutlineThickness);

	juce::Path p;
	auto pointerLength = radius * 0.33f;
	p.addEllipse(-m_dialIndicatorThickness * 0.5f, -radius, m_dialIndicatorThickness, m_dialIndicatorThickness);
	p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

	// pointer
	g.setColour(m_dialIndicatorColour);
	g.fillPath(p);
}
