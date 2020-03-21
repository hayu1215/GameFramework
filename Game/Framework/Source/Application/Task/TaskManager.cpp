#include"TaskManager.h"
#include<algorithm>
#include"UpdateSystem.h"
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Component/DrawComponent.h>
#include<Framework/Source/Utility/Judge.h>

std::list<std::weak_ptr<UpdateComponent>> TaskManager::m_UpdateComponents = {};
std::list<std::weak_ptr<UpdateComponent>> TaskManager::m_RemoveUpdateComponents = {};
std::list<std::weak_ptr<DrawComponent>> TaskManager::m_DrawComponents = {};
std::list<std::weak_ptr<DrawComponent>> TaskManager::m_RemoveDrawComponents = {};
std::list<std::weak_ptr<UpdateSystem>> TaskManager::m_UpdateSystems = {};
std::list<std::weak_ptr<UpdateSystem>> TaskManager::m_RemoveUpdateSystems = {};

void TaskManager::AddTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_UpdateComponents.emplace_back(task);
}

void TaskManager::AddTask(const std::weak_ptr<DrawComponent>& task)
{
	m_DrawComponents.emplace_back(task);
}

void TaskManager::AddTask(const std::weak_ptr<UpdateSystem>& task)
{
	m_UpdateSystems.emplace_back(task);
}

void TaskManager::AddRemoveTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_RemoveUpdateComponents.emplace_back(task);
}

void TaskManager::AddRemoveTask(const std::weak_ptr<DrawComponent>& task)
{
	m_RemoveDrawComponents.emplace_back(task);
}

void TaskManager::AddRemoveTask(const std::weak_ptr<UpdateSystem>& task)
{
	m_RemoveUpdateSystems.emplace_back(task);
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
	for (auto& e : m_DrawComponents)
	{
		e.lock()->draw();
	}
}

void TaskManager::SystemUpdate()
{
	for (auto& e : m_UpdateSystems)
	{
		e.lock()->update();
	}
}

void TaskManager::RemoveTask()
{
	for (auto& v : m_RemoveUpdateComponents)
	{
		m_UpdateComponents.remove_if([&](const std::weak_ptr<UpdateComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveUpdateComponents.clear();

	for (auto& v : m_RemoveDrawComponents)
	{
		m_DrawComponents.remove_if([&](const std::weak_ptr<DrawComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveDrawComponents.clear();

	for (auto& v : m_RemoveUpdateSystems)
	{
		m_UpdateSystems.remove_if([&](const std::weak_ptr<UpdateSystem>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveUpdateSystems.clear();
}
