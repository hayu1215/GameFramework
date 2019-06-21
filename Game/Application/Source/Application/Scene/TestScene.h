#pragma once

#include<memory>
#include<string>
#include<Framework/Source/Application/Scene/AScene.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>

class TestScene :public AScene
{
public:
	TestScene(const std::string name);
	~TestScene();

	void start()override;
	void end()override;
};