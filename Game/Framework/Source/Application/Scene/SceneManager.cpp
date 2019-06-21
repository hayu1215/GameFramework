#include"SceneManager.h"
#include"AScene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>

//SceneManager���K�v�������A�ق���AScene�ɏ����Ă���������
std::string SceneManager::m_CurrentName = "";
std::unordered_map<std::string, std::unique_ptr<AScene>> SceneManager::m_Scenes = {};

void SceneManager::Change(const std::string & next)
{
	if (!m_CurrentName.empty())m_Scenes[m_CurrentName]->end();
	m_CurrentName = next;
	m_Scenes[m_CurrentName]->start();
}

void SceneManager::Add(std::unique_ptr<AScene> scene)
{
	m_Scenes[scene->name()] = std::move(scene);
}

void SceneManager::AddRemoveEntity(const std::weak_ptr<Entity>& entity)
{
	m_Scenes[m_CurrentName]->addRemoveEntity(entity);
}

void SceneManager::RemoveEntity()
{
	m_Scenes[m_CurrentName]->removeEntity();
}
