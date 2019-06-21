#pragma once

#include<memory>
#include<list>
#include<string>

class Entity;

class AScene
{
public:
	AScene(const std::string& name);
	virtual ~AScene();

	virtual void start() = 0;
	virtual void end() = 0;
	Entity* addEntity(std::shared_ptr<Entity>);
	void addRemoveEntity(const std::weak_ptr<Entity>&);
	void removeEntity();
	const std::string name();

private:
	const std::string m_Name;
	std::list<std::shared_ptr<Entity>>m_Entities;
	std::list<std::weak_ptr<Entity>>m_RemoveEntities;
};