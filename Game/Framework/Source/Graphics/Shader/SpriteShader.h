#pragma once

#include"AShader.h"
#include<string>

class SpriteShader :public AShader
{
public:
	SpriteShader();
	SpriteShader(const std::string&);
	void load(const std::string&) override;
};