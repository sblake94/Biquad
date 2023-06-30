/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GUI/CustomLookAndFeel.h"
#include "GUI/Controls/CustomControlBase.h"

#include <stdlib.h>
#include <map>

using namespace GUI;

/////////////////////////////////////////////////////////////////////////////////////
BiquadAudioProcessorEditor::BiquadAudioProcessorEditor(BiquadAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , Slider::Listener()
    , Button::Listener()
    , m_controlManager(m_windowWidth, m_windowHeight, new CustomLookAndFeel())
    , m_audioProcessor(p)
    , m_background()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (m_windowWidth, m_windowHeight);
    setResizable(false, false);
    
    // Make all controls visible
    for (juce::Component* dialPtr : m_controlManager.GetAllSliders())
    {
        addAndMakeVisible(dialPtr);
        dynamic_cast<juce::Slider*>(dialPtr)->addListener(this);
    }

    for (juce::Component* buttonPtr : m_controlManager.GetAllButtons())
    {
        addAndMakeVisible(buttonPtr);
        dynamic_cast<juce::Button*>(buttonPtr)->addListener(this);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
BiquadAudioProcessorEditor::~BiquadAudioProcessorEditor()
{
}

/////////////////////////////////////////////////////////////////////////////////////
void BiquadAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    m_background.paint(g, m_windowWidth, m_windowHeight);
    m_controlManager.paint(g);
}

/////////////////////////////////////////////////////////////////////////////////////
void BiquadAudioProcessorEditor::resized()
{
    // Get new window size
    m_windowWidth = getWidth();
    m_windowHeight = getHeight();

    // Resize Controls
    m_controlManager.resized(m_windowWidth, m_windowHeight);
}

/////////////////////////////////////////////////////////////////////////////////////
void BiquadAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // Get the slider's ID
    juce::ParameterID sliderID = dynamic_cast<GUI::Controls::CustomControlBase*>(slider)->m_id;

	// Get the slider's value
	float sliderValue = slider->getValue();

	// Update the processor
    FloatParamDirectory& params = m_audioProcessor.GetParametersRef().GetSliderParams();
    for (std::pair<juce::ParameterID, juce::AudioParameterFloat*> param : params)
    {
        if (param.first.getParamID() == sliderID.getParamID())
		{
            juce::AudioParameterFloat* paramFloat = param.second;
			*paramFloat = (float)sliderValue;
            return;
		}
    }

    throw new std::exception("Slider ID not found in processor");
}

void BiquadAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    // Get the button's ID
	juce::ParameterID buttonID = dynamic_cast<GUI::Controls::CustomControlBase*>(button)->m_id;

	// Get the button's value
	bool buttonValue = button->getToggleState();

	// Update the processor
	BoolParamDirectory& params = m_audioProcessor.GetParametersRef().GetBoolParams();
	for (std::pair<juce::ParameterID, juce::AudioParameterBool*> param : params)
	{
		if (param.first.getParamID() == buttonID.getParamID())
		{
            param.second->setValueNotifyingHost(buttonValue);
			return;
		}
	}

	throw new std::exception("Button ID not found in processor");
}