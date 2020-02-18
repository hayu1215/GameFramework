#include "Entity.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Component/AComponent.h>
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Application/Scene/SceneManager.h>

Entity::Entity()
	:m_position(XMFLOAT3(0, 0, 0)), m_tag(""), m_name(""), m_isActive(false)
{
}

Entity::Entity(const XMFLOAT3& position, const std::string& tag, const std::string& name)
	:m_position(position), m_tag(tag), m_name(name), m_isActive(false)
{
}

Entity::~Entity()
{
}

Entity* Entity::addComponent(const std::shared_ptr<AComponent>& component)
{
	m_components.emplace_back(component);
	component->setEntity(shared_from_this());
	component->init();
	component->onCreate();
	return this;
}

void Entity::addRemoveComponent(const std::weak_ptr<AComponent>& component)
{
	m_removeComponents.emplace_back(component);
}

void Entity::removeComponent()
{
	for (auto& v : m_removeComponents)
	{
		m_components.remove_if([&](const std::weak_ptr<AComponent>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_removeComponents.clear();
}

void Entity::active()
{
	for (auto& v : m_components)
	{
		v->active();
	}
}

void Entity::deActive()
{
	for (auto& v : m_components)
	{
		v->deActive();
	}
}

void Entity::destroy()
{
	for (auto& v : m_components)
	{
		v->onDestory();
		v->deActive();
	}
	SceneManager::AddRemoveEntity(shared_from_this());
}

bool Entity::isActive()
{
	return m_isActive;
}

const std::string& Entity::getTag()
{
	return m_tag;
}

const std::string& Entity::getName()
{
	return m_name;
}

const XMFLOAT3& Entity::getPosition()
{
	return m_position;
}