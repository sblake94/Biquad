/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GUI/CustomLookAndFeel.h"

/////////////////////////////////////////////////////////////////////////////////////
BiquadAudioProcessorEditor::BiquadAudioProcessorEditor(BiquadAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , m_background()
    , m_controlManager(m_windowWidth, m_windowHeight, new GUI::CustomLookAndFeel())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (m_windowWidth, m_windowHeight);
    setResizable(false, false);
    
    // Make all controls visible
    for (juce::Component* control : m_controlManager.GetAllControls())
    {
        addAndMakeVisible(control);
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