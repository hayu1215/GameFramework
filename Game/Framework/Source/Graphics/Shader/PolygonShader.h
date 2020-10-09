#pragma once

#include"AShader.h"
#include<string>

class PolygonShader :public AShader
{
public:
	PolygonShader();
	PolygonShader(const std::string&);
	void load(const std::string&) override;
};