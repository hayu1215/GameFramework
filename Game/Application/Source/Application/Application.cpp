#include"Application.h"
#include"Scene/TestScene.h"
#include"Scene/Title.h"
#include<memory>
#include<Framework/Source/Application/Window/Window.h>
#include<Framework/Source/Graphics/2D/SpritebatchOld.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Graphics/Shader/SpriteShader.h>
#include<Framework/Source/Graphics/Shader/TestShader.h>
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Device/Input/Keyboard.h>
#include<Framework/Source/Graphics/2D/Texture.h>
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Application/Scene/SceneManager.h>
#include<Framework/Source/Component/Physics/B2Manager.h>


Application::Application()
{
}

Application::~Application()
{
}

bool Application::init(HINSTANCE hInstance)
{
	Window window;
	if (!window.initWindow(hInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME))utility::debugLog("ウィンドウ初期化失敗");
	m_hWnd = window.m_hWnd;

	if (!D3d11::Init(m_hWnd)) 
	{ 
		utility::debugLog("D3d11の初期化失敗");
		return false; 
	}

	ResourceManager::LoadShader<SpriteShader>("SpritebatchShader.hlsl");
	ResourceManager::LoadShader<TestShader>("LineShader.hlsl");
	ResourceManager::LoadShader<TestShader>("LineShaderTest.hlsl");
	ResourceManager::LoadTexture("blue.png");
	ResourceManager::LoadTexture("red.png"); 
	ResourceManager::LoadTexture("green_pepper.png");

	SceneManager::Add(std::make_unique<Title>("title"));
	SceneManager::Add(std::make_unique<TestScene>("test"));
	SceneManager::Change("title");

	DeviceLocator::ProvideKeyboard(std::make_unique<Keyboard>(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
	//DeviceLocator::ProvideAudio(std::make_unique<XactAudio>());

	return true;
}

void Application::run(HINSTANCE hInstance)
{
	init(hInstance);
	utility::FPSTimer timer;
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
			timer.update();
			loop();
			timer.wait();
		}
	}
	finalize();
}

void Application::loop()
{
	D3d11::Clear();

	DeviceLocator::Keyboard().update();

	TaskManager::Update();
	TaskManager::Draw();
	TaskManager::RemoveTask();
	B2Manager::Update();

	SceneManager::RemoveEntity();

	D3d11::Present();
}

void Application::finalize()
{
}