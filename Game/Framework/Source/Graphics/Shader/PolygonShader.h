#pragma once

#include"Shader.h"
#include<string>

class PolygonShader : public Shader {
public:
    PolygonShader();
    PolygonShader(const std::string&);
    void load(const std::string&) override;
};