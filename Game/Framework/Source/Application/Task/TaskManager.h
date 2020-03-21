#pragma once

#include<memory>
#include<vector>
#include<list>

class UpdateComponent;
class DrawComponent;
class UpdateSystem;

class TaskManager
{
public:
	TaskManager() = delete;

	template<class T>
	static std::weak_ptr<T> GetSystemTask();

	static void AddTask(const std::weak_ptr<UpdateComponent>&);
	static void AddTask(const std::weak_ptr<DrawComponent>&);
	static void AddTask(const std::weak_ptr<UpdateSystem>&);
	static void AddRemoveTask(const std::weak_ptr<UpdateComponent>&);
	static void AddRemoveTask(const std::weak_ptr<DrawComponent>&);
	static void AddRemoveTask(const std::weak_ptr<UpdateSystem>&);
	static void Update();
	static void Draw();
	static void SystemUpdate();
	static void RemoveTask();

private:
	static std::list<std::weak_ptr<UpdateComponent>>m_UpdateComponents;
	static std::list<std::weak_ptr<UpdateComponent>>m_RemoveUpdateComponents;
	static std::list<std::weak_ptr<DrawComponent>>m_DrawComponents;
	static std::list<std::weak_ptr<DrawComponent>>m_RemoveDrawComponents;
	static std::list<std::weak_ptr<UpdateSystem>>m_UpdateSystems;
	static std::list<std::weak_ptr<UpdateSystem>>m_RemoveUpdateSystems;
 };

template<class T>
std::weak_ptr<T> TaskManager::GetSystemTask()
{
	std::shared_ptr<T> task = nullptr;

	for (auto& v : m_UpdateSystems)
	{
		task = std::dynamic_pointer_cast<T>(v.lock());
		if (task != nullptr) return task;
	}
	return std::weak_ptr<T>();
}