#pragma once

#include"Shader.h"
#include<string>

class SpriteShader : public Shader {
public:
    SpriteShader();
    SpriteShader(const std::string&);
    void load(const std::string&) override;
};