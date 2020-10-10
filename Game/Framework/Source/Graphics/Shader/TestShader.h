#pragma once

#include"AShader.h"
#include<string>

class TestShader : public AShader {
public:
    TestShader();
    TestShader(const std::string&);
    void load(const std::string&) override;
};