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
	if (m_isActive)
	{
		onActive();
		TaskManager::AddTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	}
	else onDeActive();
}

void UpdateComponent::active()
{
	if (m_isActive)return;
	onActive();
	TaskManager::AddTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	m_isActive = true;
}

void UpdateComponent::deActive()
{
	if (!m_isActive)return;
	onDeActive();
	TaskManager::AddRemoveTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
	m_isActive = false;
}