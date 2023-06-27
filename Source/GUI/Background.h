/*
	==========================================================================================

	@Author : SBlake
	This class simply draws the background of the GUI
	This allows us to contain future fancy logic for making the background reactive

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>


namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////
	class Background
		: public juce::Component
	{
	public:
		Background();
		~Background();

		void paint(juce::Graphics& g, int width, int height);
	private:
	};
}