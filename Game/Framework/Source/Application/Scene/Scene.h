#pragma once

#include<memory>
#include<list>
#include<string>

class Entity;

class Scene {
public:
    Scene(const std::string& name);
    virtual ~Scene();

    virtual void start() = 0;
    virtual void end() = 0;
    const std::string name();

private:
    const std::string m_name;
};