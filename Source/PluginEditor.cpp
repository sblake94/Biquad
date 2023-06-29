/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GUI/CustomLookAndFeel.h"
#include "GUI/Controls/CustomSliderBase.h"

#include <stdlib.h>
#include <map>

using namespace GUI;

/////////////////////////////////////////////////////////////////////////////////////
BiquadAudioProcessorEditor::BiquadAudioProcessorEditor(BiquadAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , Slider::Listener()
    , m_controlManager(m_windowWidth, m_windowHeight, new CustomLookAndFeel())
    , m_audioProcessor(p)
    , m_background()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (m_windowWidth, m_windowHeight);
    setResizable(false, false);
    
    // Make all controls visible
    for (juce::Component* controlPtr : m_controlManager.GetAllControls())
    {
        // This is going to be a problem if we have any controls that aren't sliders
        addAndMakeVisible(controlPtr);
        dynamic_cast<juce::Slider*>(controlPtr)->addListener(this);

        // register the control with the processor?
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
    juce::ParameterID sliderID = dynamic_cast<GUI::Controls::CustomSliderBase*>(slider)->m_id;

	// Get the slider's value
	double sliderValue = slider->getValue();

	// Update the processor
    ParamDirectory& params = m_audioProcessor.GetParametersRef().GetSliderParams();
    for (std::pair<juce::ParameterID, juce::AudioParameterFloat*> param : params)
    {
        if (param.first.getParamID() == sliderID.getParamID())
		{
			*(param.second) = (sliderValue);
            return;
		}
    }

    throw new std::exception("Slider ID not found in processor");
}
