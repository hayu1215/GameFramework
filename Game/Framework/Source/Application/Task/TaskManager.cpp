#include"TaskManager.h"
#include<algorithm>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Utility/Judge.h>

std::list<std::weak_ptr<UpdateComponent>> TaskManager::m_UpdateComponents = {};
std::list<std::weak_ptr<UpdateComponent>> TaskManager::m_RemoveComponents = {};

void TaskManager::AddTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_UpdateComponents.emplace_back(task);
}

void TaskManager::AddRemoveTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_RemoveComponents.emplace_back(task);
}

void TaskManager::Update()
{
	for (auto& e : m_UpdateComponents)
	{
		e.lock()->update();
	}
}

void TaskManager::Draw()
{
}

void TaskManager::RemoveTask()
{
	for (auto& v : m_RemoveComponents)
	{
		m_UpdateComponents.remove_if([&](const std::weak_ptr<UpdateComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveComponents.clear();
}
