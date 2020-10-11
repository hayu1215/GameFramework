#pragma once

#include"Shader.h"
#include<string>

class TestShader : public Shader {
public:
    TestShader();
    TestShader(const std::string&);
    void load(const std::string&) override;
};