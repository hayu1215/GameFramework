#pragma once

#include<memory>
#include<vector>
#include<list>
#include<Framework/Source/Utility/Template/DynamicSingleton.h>

class UpdateComponent;

class TaskManager :public DynamicSingleton<TaskManager> 
{
private:
	TaskManager();
	~TaskManager();

public:
	friend class DynamicSingleton<TaskManager>;
	void addTask(const std::weak_ptr<UpdateComponent>&);
	void addRemoveTask(const std::weak_ptr<UpdateComponent>&);
	void update();
	void draw();
	void removeTask();

	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
	TaskManager(TaskManager&&) = delete;
	TaskManager& operator=(TaskManager&&) = delete;

private:
	std::list<std::weak_ptr<UpdateComponent>>m_UpdateComponents;
	std::list<std::weak_ptr<UpdateComponent>>m_RemoveComponents;
 };