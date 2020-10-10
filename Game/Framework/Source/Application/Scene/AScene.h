#pragma once

#include<memory>
#include<list>
#include<string>

class Entity;

class AScene {
public:
    AScene(const std::string& name);
    virtual ~AScene();

    virtual void start() = 0;
    virtual void end() = 0;
    const std::string name();

private:
    const std::string m_name;
};