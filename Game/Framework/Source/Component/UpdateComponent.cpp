#include "UpdateComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Utility/Judge.h>

UpdateComponent::UpdateComponent()
{
}

UpdateComponent::~UpdateComponent()
{
}

void UpdateComponent::setTask(const std::shared_ptr<AComponent>& task)
{
	TaskManager::Instance().addTask(std::dynamic_pointer_cast<UpdateComponent>(task));
}

void UpdateComponent::prepareDestroy()
{
	deActive();
	TaskManager::Instance().addRemoveTask(std::dynamic_pointer_cast<UpdateComponent>(shared_from_this()));
}