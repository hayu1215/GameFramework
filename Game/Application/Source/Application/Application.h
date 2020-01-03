#pragma once
#include<Windows.h>
#include<Framework/Source/Utility/Timer/FPSTimer.h>

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
	
	//utility::FPSTimer timer;
};