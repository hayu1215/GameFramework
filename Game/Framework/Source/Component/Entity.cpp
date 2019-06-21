#include "Entity.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Component/AComponent.h>
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Application/Scene/SceneManager.h>

Entity::Entity()
{
}

Entity::Entity(const std::string & tag, const std::string & name)
	:m_Tag(tag), m_Name(name)
{
}

Entity::~Entity()
{
	utility::debugLog("Entity::~Entity");
}

Entity* Entity::addComponent(const std::shared_ptr<AComponent>& component)
{
	utility::debugLog("addComponent");
	m_Components.emplace_back(component);
	component->setEntity(shared_from_this());
	component->setTask(component);
	component->init();
	return this;
}

void Entity::addRemoveComponent(const std::weak_ptr<AComponent>& component)
{
	m_RemoveComponents.emplace_back(component);
}

void Entity::removeComponent()
{
	for (auto& v : m_RemoveComponents)
	{
		m_Components.remove_if([&](const std::weak_ptr<AComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveComponents.clear();
}

void Entity::active()
{
	for (auto& v : m_Components)
	{
		v->active();
	}
}

void Entity::deActive()
{
	for (auto& v : m_Components)
	{
		v->deActive();
	}
}

void Entity::destroy()
{
	for (auto& v : m_Components)
	{
		v->prepareDestroy();
	}
	SceneManager::AddRemoveEntity(shared_from_this());
}

bool Entity::isActive()
{
	return m_IsActive;
}

const std::string& Entity::getTg()
{
	return m_Tag;
}

const std::string& Entity::getName()
{
	return m_Name;
}