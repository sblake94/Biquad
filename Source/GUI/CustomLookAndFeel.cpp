#include "CustomLookAndFeel.h"

// There is probably an inbuilt way to do this in JUCE, but I haven't found it yet.
const juce::Colour GUI::CustomLookAndFeel::s_shadowColour		= juce::Colour::fromRGBA(0u,	0u,		0u,		88u);
const juce::Colour GUI::CustomLookAndFeel::s_highlightColour	= juce::Colour::fromRGBA(153u,	51u,	0u,		255u);
const juce::Colour GUI::CustomLookAndFeel::s_fillColorA			= juce::Colour::fromRGBA(51u,	51u,	51u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_fillColorB			= juce::Colour::fromRGBA(34u,	34u,	34u,	255u);

const juce::Colour GUI::CustomLookAndFeel::s_textColourBright	= juce::Colour::fromRGBA(255u,	255u,	255u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourBrightT	= juce::Colour::fromRGBA(255u,	255u,	255u,	125u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourDark		= juce::Colour::fromRGBA(0u,	0u,		0u,		255u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourDarkT	= juce::Colour::fromRGBA(0u,	9u,		9u,		125u);
const juce::Font   GUI::CustomLookAndFeel::s_labelFont			= juce::Font(12, juce::Font::plain);
const juce::Font   GUI::CustomLookAndFeel::s_titleFont			= juce::Font(48, juce::Font::bold);

const float GUI::CustomLookAndFeel::s_cornerRadius = 7.0f;
const float GUI::CustomLookAndFeel::s_dialIndicatorThickness = 10.0f;
const float GUI::CustomLookAndFeel::s_outlineThickness = 2.0f;
const float GUI::CustomLookAndFeel::s_controlBoundsMargin = 5.0f;

const juce::DropShadow GUI::CustomLookAndFeel::s_dialShadow = juce::DropShadow(
	GUI::CustomLookAndFeel::s_shadowColour, 5, juce::Point<int>(5, 5));

const juce::DropShadow GUI::CustomLookAndFeel::s_buttonShadow = juce::DropShadow(
	GUI::CustomLookAndFeel::s_shadowColour, 1, juce::Point<int>(0, 0));

const juce::DropShadow GUI::CustomLookAndFeel::s_panelShadow = juce::DropShadow(
	GUI::CustomLookAndFeel::s_shadowColour, 2, juce::Point<int>(2, 2));

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
	auto bounds = juce::Rectangle<float>(x, y, width, height)
		.reduced(GUI::CustomLookAndFeel::s_controlBoundsMargin);

	auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 3.5f;
	auto centreX = bounds.getCentreX();
	auto centreY = bounds.getCentreY();
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	juce::Path dialPath;
	dialPath.addEllipse(rx, ry, rw, rw);

	// draw a drop shadow for the dial, originating from the top left corner
	s_dialShadow.drawForPath(g, dialPath);

	// fill
	juce::ColourGradient gradFill = BackgroundGradient(juce::Point<float>(rx, ry), bounds.getBottomRight().toFloat());
	g.setGradientFill(gradFill);
	g.fillEllipse(rx, ry, rw, rw);

	// indicator
	juce::Path p;
	auto pointerLength = radius * 0.33f;
	p.addEllipse(-s_dialIndicatorThickness * 0.5f, -radius, s_dialIndicatorThickness, s_dialIndicatorThickness);
	p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

	g.setColour(s_highlightColour);
	g.fillPath(p);

	// outline
	g.setColour(s_shadowColour);
	g.drawEllipse(rx, ry, rw, rw, s_outlineThickness);
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
	// draw the background behind the button text
	const juce::Rectangle<int> buttonArea = button.getLocalBounds().reduced(s_controlBoundsMargin);
	
	// Shadow for the button
	juce::Path buttonPath;
	buttonPath.addRoundedRectangle(buttonArea.toFloat(), s_cornerRadius);
	s_buttonShadow.drawForPath(g, buttonPath);
	
	// Draw the button itself
	const juce::ColourGradient gradFill = BackgroundGradient(buttonArea.getTopLeft().toFloat(), buttonArea.getBottomRight().toFloat());
	g.setGradientFill(gradFill);
	g.fillPath(buttonPath);
	
	// draw the border around the button
	const bool buttonState = button.getToggleState();
	g.setColour(buttonState ? s_highlightColour : s_shadowColour);
	g.drawRoundedRectangle(buttonArea.toFloat().reduced(s_outlineThickness / 3.33f), s_cornerRadius, s_outlineThickness);

	// Draw the text in the button
	const juce::String buttonText = button.getButtonText();
	g.setColour(s_textColourBright);
	g.setFont(s_labelFont);
	g.drawFittedText(buttonText, buttonArea, juce::Justification::centred, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Draws the background of all Components
/// </summary>
/// <param name="_innerPoint">The point where the gradient starts</param>
/// <param name="_outerPoint">The point where the gradient ends</param>
const juce::ColourGradient GUI::CustomLookAndFeel::BackgroundGradient
(
	juce::Point<float> _innerPoint, 
	juce::Point<float> _outerPoint
)
{
	return juce::ColourGradient(
		s_fillColorA,
		_innerPoint,
		s_fillColorB,
		_outerPoint,
		true);
}