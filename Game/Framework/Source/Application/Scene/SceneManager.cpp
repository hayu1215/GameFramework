#include"SceneManager.h"
#include"Scene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Task/TaskManager.h>

//SceneManager‚ª•K—v‚©”÷–­A–Ù‚Á‚ÄScene‚É‘‚¢‚Ä‚à‚¢‚¢‚©‚à
std::string SceneManager::m_CurrentName = "";
std::unordered_map<std::string, std::unique_ptr<Scene>> SceneManager::m_Scenes = {};

void SceneManager::Change(const std::string& next) {
    if (!m_CurrentName.empty()) m_Scenes[m_CurrentName]->end();
    m_CurrentName = next;
    TaskManager::Clear();
    Entity::Clear();
    m_Scenes[m_CurrentName]->start();
}

void SceneManager::Add(std::unique_ptr<Scene> scene) {
    m_Scenes[scene->name()] = std::move(scene);
}