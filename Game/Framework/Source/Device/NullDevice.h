#pragma once

#include"Input/IKeyboard.h"
#include"Sound/IAudio.h"

class NullDevice :public IKeyboard ,public IAudio 
{
public:
	~NullDevice()override {}
	void update()override {}
	bool getKey(KeyCode)override { return false; }
	bool keyDown(KeyCode)override { return false; }
	bool keyUp(KeyCode)override { return false; }

	unsigned short load(std::string waveBankName, std::string soundBankName, const char* cueName)override { return 0; }
	void play(unsigned short index)override {}
};