#pragma once

#include<vector>
#include<unordered_map>
#include<memory>
#include<string>

class Scene;
class Entity;

class SceneManager {
public:
    SceneManager() = delete;

    static void Change(const std::string&);
    static void Add(std::unique_ptr<Scene>);

private:
    static std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
    static std::string m_CurrentName;
};