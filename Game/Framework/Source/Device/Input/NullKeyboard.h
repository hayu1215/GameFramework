#pragma once

#include"IKeyboard.h"

class NullKeyboard :public IKeyboard 
{
public:
	~NullKeyboard()override {}
	void update()override {}
	bool getKey(KeyCode)override { return false; }
	bool keyDown(KeyCode)override { return false; }
	bool keyUp(KeyCode)override { return false; }
};