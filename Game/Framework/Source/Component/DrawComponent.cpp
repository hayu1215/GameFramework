#include"DrawComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Utility/Judge.h>

DrawComponent::DrawComponent() = default;
DrawComponent::~DrawComponent() = default;

void DrawComponent::active()
{
	if (m_isActive) return;
	onActive();
	TaskManager::AddTask(std::dynamic_pointer_cast<DrawComponent>(shared_from_this()));
	m_isActive = true;
}

void DrawComponent::deActive()
{
	if (!m_isActive) return;
	onDeActive();
	TaskManager::AddRemoveTask(std::dynamic_pointer_cast<DrawComponent>(shared_from_this()));
	m_isActive = false;
}