#pragma once

#include<Windows.h>

class Application
{
public:
	Application();
	~Application();

public:
	void run(HINSTANCE hInstance);

private:
	bool init(HINSTANCE hInstance);
	void loop();
	void finalize();

private:
	HWND m_hWnd;
};