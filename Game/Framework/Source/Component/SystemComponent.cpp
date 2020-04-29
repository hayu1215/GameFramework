#include "SystemComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>

SystemComponent::SystemComponent()
{
}

SystemComponent::SystemComponent(bool isActive)
	:AComponent(isActive)
{
}

SystemComponent::~SystemComponent()
{
}

void SystemComponent::init()
{
}

void SystemComponent::onCreate()
{
}

void SystemComponent::onDestory()
{
}

void SystemComponent::onActive()
{
}

void SystemComponent::onDeActive()
{
}