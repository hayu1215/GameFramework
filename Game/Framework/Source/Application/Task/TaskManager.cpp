#include"TaskManager.h"
#include<algorithm>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Utility/Judge.h>

TaskManager::TaskManager() = default;
TaskManager::~TaskManager() = default;

void TaskManager::addTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_UpdateComponents.emplace_back(task);
}

void TaskManager::addRemoveTask(const std::weak_ptr<UpdateComponent>& task)
{
	m_RemoveComponents.emplace_back(task);
}

void TaskManager::update()
{
	for (auto& e : m_UpdateComponents)
	{
		e.lock()->update();
	}
}

void TaskManager::draw()
{
}

void TaskManager::removeTask()
{
	for (auto& v : m_RemoveComponents)
	{
		m_UpdateComponents.remove_if([&](const std::weak_ptr<UpdateComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveComponents.clear();
}
