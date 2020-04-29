#include"SceneManager.h"
#include"AScene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Task/TaskManager.h>

//SceneManager‚ª•K—v‚©”÷–­A–Ù‚Á‚ÄAScene‚É‘‚¢‚Ä‚à‚¢‚¢‚©‚à
std::string SceneManager::m_CurrentName = "";
std::unordered_map<std::string, std::unique_ptr<AScene>> SceneManager::m_Scenes = {};

void SceneManager::Change(const std::string & next)
{
	if (!m_CurrentName.empty()) m_Scenes[m_CurrentName]->end();
	m_CurrentName = next;
	TaskManager::Clear();
	Entity::Clear();
	m_Scenes[m_CurrentName]->start();
}

void SceneManager::Add(std::unique_ptr<AScene> scene)
{
	m_Scenes[scene->name()] = std::move(scene);
}