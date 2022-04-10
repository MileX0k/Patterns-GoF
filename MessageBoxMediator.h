#pragma once
#include "LevelGUI.h"

class MessageBoxMediator
{
public:
	MessageBoxMediator( LevelGUI *gui) : gui{ gui } {};

	void AddMessage(std::string_view text, uint16_t x, uint16_t y) {
		gui->DisplayMessage(x, y, 1.0, text); 
	}


private:
	LevelGUI* gui;
};

