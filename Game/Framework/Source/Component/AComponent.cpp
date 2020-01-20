#include"AComponent.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Application/Task/TaskManager.h>

AComponent::AComponent():
	m_IsActive(false)
{
}

AComponent::AComponent(bool isActive)
	:m_IsActive(isActive)
{
}

AComponent::~AComponent()
{
}

void AComponent::destroy()
{
	onDestory();
	deActive();
	m_pEntity.lock()->addRemoveComponent(shared_from_this());
}

void AComponent::active()
{
	if (m_IsActive)return;
	onActive();
	m_IsActive = true;
}

void AComponent::deActive()
{
	if (!m_IsActive)return;
	onDeActive();
	m_IsActive = false;
}

void AComponent::setEntity(const std::weak_ptr<Entity>& entity)
{
	m_pEntity = entity;
}

bool AComponent::isActive()
{
	return m_IsActive;
}