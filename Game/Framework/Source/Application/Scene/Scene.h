#pragma once

#include<memory>
#include<list>
#include<string>
#include<unordered_map>

class Scene {
public:
    Scene(const std::string& name);
    virtual ~Scene();

    static void Change(const std::string&);
    static void Add(std::unique_ptr<Scene>);

    virtual void start() = 0;
    virtual void end() = 0;
    const std::string name();

private:
    static std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
    static std::string m_CurrentName;

    const std::string m_name;
};