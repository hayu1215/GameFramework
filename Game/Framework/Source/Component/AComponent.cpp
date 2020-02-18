#include"AComponent.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Application/Task/TaskManager.h>

AComponent::AComponent():
	m_isActive(false)
{
}

AComponent::AComponent(bool isActive)
	:m_isActive(isActive)
{
}

AComponent::~AComponent()
{
}

void AComponent::destroy()
{
	onDestory();
	deActive();
	m_entity.lock()->addRemoveComponent(shared_from_this());
}

void AComponent::active()
{
	if (m_isActive)return;
	onActive();
	m_isActive = true;
}

void AComponent::deActive()
{
	if (!m_isActive)return;
	onDeActive();
	m_isActive = false;
}

void AComponent::setEntity(const std::weak_ptr<Entity>& entity)
{
	m_entity = entity;
}

bool AComponent::isActive()
{
	return m_isActive;
}