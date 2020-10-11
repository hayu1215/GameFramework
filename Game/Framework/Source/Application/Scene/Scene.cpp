#include"Scene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>

Scene::Scene(const std::string& name)
    : m_name(name) {}

Scene::~Scene() {}

const std::string Scene::name() {
    return m_name;
}
