#include"Scene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Task/TaskManager.h>

std::string Scene::m_CurrentName = "";
std::unordered_map<std::string, std::unique_ptr<Scene>> Scene::m_Scenes = {};

Scene::Scene(const std::string& name)
    : m_name(name) {}

Scene::~Scene() {}

void Scene::Change(const std::string& next) {
    if (!m_CurrentName.empty()) m_Scenes[m_CurrentName]->end();
    m_CurrentName = next;
    TaskManager::Clear();
    Entity::Clear();
    m_Scenes[m_CurrentName]->start();
}

void Scene::Add(std::unique_ptr<Scene> scene) {
    m_Scenes[scene->name()] = std::move(scene);
}

const std::string Scene::name() {
    return m_name;
}
