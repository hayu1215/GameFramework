#include "UpdateComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Utility/Judge.h>

UpdateComponent::UpdateComponent()
{
}

UpdateComponent::UpdateComponent(bool isActive)
	:AComponent(isActive)
{
}

UpdateComponent::~UpdateComponent()
{
}

void UpdateComponent::init()
{
	if (m_IsActive)
	{
		onActive();
		TaskManager::AddTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	}
	else onDeActive();
}

void UpdateComponent::active()
{
	if (m_IsActive)return;
	onActive();
	TaskManager::AddTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	m_IsActive = true;
}

void UpdateComponent::deActive()
{
	if (!m_IsActive)return;
	onDeActive();
	TaskManager::AddRemoveTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	m_IsActive = false;
}