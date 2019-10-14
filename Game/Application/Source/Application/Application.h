#pragma once
#include<Windows.h>
#include<Framework/Source/Utility/Timer/FPSTimer.h>
#include<Framework/Source/Application/Scene/SceneManager.h>
#include<memory>

class Window;
//class SpritebatchOld;
class Camera;

class Application
{
public:
	Application();
	~Application();

public:
	bool init();
	void run(HINSTANCE hInstance);
	void loop();
	void finalize();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	std::unique_ptr<Window> m_pWindow;
	utility::FPSTimer m_FPSTimer;
	//std::unique_ptr<SpritebatchOld> m_pSpritebatchOld;
	std::shared_ptr<Camera>m_pCamera;
};