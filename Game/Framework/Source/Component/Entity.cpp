#include "Entity.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Component/AComponent.h>
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Application/Scene/SceneManager.h>

std::list<std::shared_ptr<Entity>> Entity::m_Entities = {};
std::list<std::weak_ptr<Entity>> Entity::m_RemoveEntities = {};

Entity::Entity()
	:m_position(XMFLOAT3(0, 0, 0)), m_rotate(XMFLOAT3(0, 0, 0)), m_scale(XMFLOAT3(1, 1, 1)), m_tag(""), m_name(""), m_isActive(false)
{
}

Entity::Entity(const XMFLOAT3& position, const XMFLOAT3& rotate, const XMFLOAT3& scale, const std::string& tag, const std::string& name)
	:m_position(position), m_rotate(rotate), m_scale(scale), m_tag(tag), m_name(name), m_isActive(false)
{
}

Entity::~Entity()
{
}

void Entity::Remove()
{
	for (auto& v : m_Entities)
	{
		v->removeComponent();
	}
	for (auto& v : m_RemoveEntities)
	{
		m_Entities.remove_if([&](const std::weak_ptr<Entity>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveEntities.clear();
}

void Entity::Clear()
{
	m_Entities.clear();
	m_RemoveEntities.clear();
}

std::list<std::weak_ptr<Entity>> Entity::GetEntities()
{
	std::list<std::weak_ptr<Entity>> entities;
	for (const auto& v : m_Entities)
	{
		entities.emplace_back(v);
	}
	return entities;
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
	m_RemoveEntities.emplace_back(shared_from_this());
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

const XMFLOAT3& Entity::position()
{
	return m_position;
}

void Entity::position(const XMFLOAT3 & pos)
{
	m_position = pos;
}

const XMFLOAT3 & Entity::rotate()
{
	return m_rotate;
}

void Entity::rotate(const XMFLOAT3 & rotate)
{
	m_rotate = rotate;
}

const XMFLOAT3 & Entity::scale()
{
	return m_scale;
}

void Entity::scale(const XMFLOAT3 & scale)
{
	m_scale = scale;
}
