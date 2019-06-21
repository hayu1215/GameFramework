#pragma once

#include<memory>
#include<string>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Scene/AScene.h>

class Title :public AScene
{
public:
	Title(const std::string name);
	~Title();

	void start()override;
	void end()override;
};