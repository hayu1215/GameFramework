#include"Application.h"
#include<Framework/Source/Application/Window/Window.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Graphics/Shader/TextureShader.h>
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Device/Input/Keyboard.h>
//#include<Framework/Source/Device/Sound/XactAudio.h>
#include<Framework/Source/Graphics/2D/Texture.h>
#include<Framework/Source/Application/Task/TaskManager.h>
#include"Scene/TestScene.h"
#include"Scene/Title.h"


Application::Application():
	m_FPSTimer(100,60)
{
	init();
	m_pCamera = std::make_shared<Camera>();
	m_pSpritebatch = std::make_unique<Spritebatch>(m_pCamera);
}

Application::~Application()
{
}

bool Application::init()
{
	//Window
	m_pWindow = std::make_unique<Window>();
	if (utility::checkNull(m_pWindow.get(), "Windowのインスタンス取得失敗"))return false;
	if (!m_pWindow->initWindow(m_hInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME))utility::debugLog("ウィンドウ初期化失敗");
	m_hWnd = m_pWindow->m_hWnd;

	//Direct3D11
	D3d11::Create();
	if (!D3d11::Instance().init(m_hWnd)) 
	{ 
		utility::debugLog("D3d11の初期化失敗");
		return false; 
	}

	//Input
	DeviceLocator::ProvideKeyboard(std::make_unique<Keyboard>(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
	//DeviceLocator::ProvideAudio(std::make_unique<XactAudio>());

	ResourceManager::Create();

	ResourceManager::Instance().loadShader<TextureShader>("Texture.hlsl");
	//ResourceManager::Instance().loadTexture("blue.png");
	//ResourceManager::Instance().loadTexture("red.png");

	TaskManager::Create();

	SceneManager::Add(std::make_unique<Title>("title"));
	SceneManager::Add(std::make_unique<TestScene>("test"));
	SceneManager::Change("title");

	return true;
}

void Application::run(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// メッセージループ
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_FPSTimer.update();
			loop();
			m_FPSTimer.wait();
		}
	}
	finalize();
}

void Application::loop()
{
	D3d11::Instance().clear();

	DeviceLocator::Keyboard().update();

	TaskManager::Instance().update();
	TaskManager::Instance().draw();

	if (DeviceLocator::Keyboard().keyUp(KeyCode::A)) {
		SceneManager::Change("title");
	}

	if (DeviceLocator::Keyboard().keyUp(KeyCode::S)) {
		SceneManager::Change("test");
	}

	/*m_SceneManager.update();*/

	//static float angle = 0;
	//angle += 0.02;

	//static float angle2 = 0;
	//angle2 += 0.04;

	//m_pSpritebatch->begin(SortMode::BackToFront);
	//m_pSpritebatch->draw("blue.png", Vector3(0, 0, 0), angle, Vector2(0, 0), Vector4(1, 1, 1, 0.5f));
	//m_pSpritebatch->draw("red.png", Vector3(0, 0, 0.5f), Vector2(0.5f, 0.5f), angle2, Vector2(0, 0), Vector4(1, 1, 1, 0.5f));
	//m_pSpritebatch->end();

	TaskManager::Instance().removeTask();
	SceneManager::RemoveEntity();
	D3d11::Instance().present();
}

void Application::finalize()
{
	D3d11::Destroy();
	ResourceManager::Destroy();
}