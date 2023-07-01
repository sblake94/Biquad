#include "CustomLookAndFeel.h"


/////////////////////////////////////////////////
/// <summary>
/// Constructor for the custom look and feel
/// </summary>
GUI::CustomLookAndFeel::CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
/// <summary>
/// Destructor for the custom look and feel
/// </summary>
GUI::CustomLookAndFeel::~CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
/// <summary>
/// Defines the behaviour for drawing sliders
/// </summary>
/// <param name="g">The Graphics context</param>
/// <param name="x">The X Position of the Slider</param>
/// <param name="y">The Y Position of the Slider</param>
/// <param name="width">The width of the Slider</param>
/// <param name="height">The width of the Slider</param>
/// <param name="sliderPos">The initial position of the Slider</param>
/// <param name="rotaryStartAngle">The start of the rotational track</param>
/// <param name="rotaryEndAngle">The end of the rotational track</param>
/// <param name="slider">The Slider itself</param>
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

////////////////////////////////////////////////////////////////////////////////////////////////
void GUI::CustomLookAndFeel::drawToggleButton
(
	juce::Graphics& g, 
	juce::ToggleButton& button, 
	bool shouldDrawButtonAsHighlighted, 
	bool shouldDrawButtonAsDown
)
{
	const bool buttonState = button.getToggleState();

	const juce::Colour inactiveColour = juce::Colour::fromRGBA(17u, 17u, 17u, 255u);
	const juce::Colour shadowColour = juce::Colour::fromRGBA(17u, 17u, 17u, 125u);
	const juce::Colour activeColour = juce::Colour::fromRGBA(153u, 51u, 0u, 255u);
	const juce::Colour textColour = juce::Colour::fromRGBA(255u, 255u, 255u, 255u);
	const juce::Colour backgroundColorA = juce::Colour::fromRGBA(51u, 51u, 51u, 255u);
	const juce::Colour backgroundColorB = juce::Colour::fromRGBA(34u, 34u, 34u, 255u);

	const juce::Rectangle<int> buttonArea = button.getLocalBounds();

	const juce::String buttonText = button.getButtonText();
	const float cornerRadius = 5.0f;
	const float inactiveBorderThickness = 2.5f;

	

	// draw the background behind the button text
	auto gradFill = juce::ColourGradient(
		backgroundColorA, 
		buttonArea.getTopLeft().toFloat(), 
		backgroundColorB,
		buttonArea.getBottomRight().toFloat(), 
		true);
	g.setGradientFill(gradFill);
	g.fillRoundedRectangle(buttonArea.toFloat(), cornerRadius);
	
	// draw the border around the button
	g.setColour(buttonState ? activeColour : shadowColour);
	g.drawRoundedRectangle(buttonArea.toFloat().reduced(inactiveBorderThickness / 3.3333f), cornerRadius, inactiveBorderThickness);

	// Draw the text in the button
	g.setColour(textColour);
	g.setFont(15.0f);
	g.drawFittedText(buttonText, buttonArea, juce::Justification::centred, 2);
}
