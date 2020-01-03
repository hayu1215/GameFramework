#pragma once

#include<memory>
#include<vector>
#include<list>

class UpdateComponent;

class TaskManager
{
public:
	TaskManager() = delete;

	static void AddTask(const std::weak_ptr<UpdateComponent>&);
	static void AddRemoveTask(const std::weak_ptr<UpdateComponent>&);
	static void Update();
	static void Draw();
	static void RemoveTask();

private:
	static std::list<std::weak_ptr<UpdateComponent>>m_UpdateComponents;
	static std::list<std::weak_ptr<UpdateComponent>>m_RemoveComponents;
 };