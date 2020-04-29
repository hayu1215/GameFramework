#include "MeshRendererComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>

std::shared_ptr<PolygonRenderer> MeshRendererComponent::m_PolygonRenderer = nullptr;

MeshRendererComponent::MeshRendererComponent()
{
}

MeshRendererComponent::MeshRendererComponent(bool isActive)
	:SystemComponent(isActive)
{
}

MeshRendererComponent::~MeshRendererComponent()
{
}

void MeshRendererComponent::update()
{
	m_PolygonRenderer->update();
}

void MeshRendererComponent::init()
{
	if (m_isActive)
	{
		onActive();
		if (TaskManager::GetSystemTask<SystemComponent>().expired()) TaskManager::AddTask(std::dynamic_pointer_cast<SystemComponent>(shared_from_this()));
	}
	else onDeActive();
}

void MeshRendererComponent::onCreate()
{
	if (m_PolygonRenderer == nullptr) m_PolygonRenderer = std::make_shared<PolygonRenderer>();
}

void MeshRendererComponent::onActive()
{
	if (TaskManager::GetSystemTask<SystemComponent>().expired()) TaskManager::AddTask(std::dynamic_pointer_cast<SystemComponent>(shared_from_this()));
}

void MeshRendererComponent::onDeActive()
{
	std::list<std::weak_ptr<Entity>> entities = Entity::GetEntities();
	for (const auto& v : entities)
	{
		std::vector<std::weak_ptr<MeshRendererComponent>> components = v.lock()->getComponents<MeshRendererComponent>();
		for (const auto& w : components)
		{
			if (w.lock()->isActive()) return;
		}
	}
	TaskManager::AddRemoveTask(std::dynamic_pointer_cast<SystemComponent>(shared_from_this()));
}

PolygonRenderer& MeshRendererComponent::polygonRenderer()
{
	return *m_PolygonRenderer;
}