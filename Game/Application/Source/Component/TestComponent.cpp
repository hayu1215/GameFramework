#include "TestComponent.h"
#include<Framework/Source/Utility/Judge.h>

TestComponent::TestComponent()
{
	utility::debugLog("TestComponent:TestComponent");
}

TestComponent::~TestComponent()
{
	utility::debugLog("TestComponent:~TestComponent");
}

void TestComponent::init()
{
	utility::debugLog("TestComponent:init");
	m_pEntity.lock()->destroy();
}

void TestComponent::update()
{
	utility::debugLog("TestComponent:update");
}

void TestComponent::onActive()
{
	utility::debugLog("TestComponent:onActive");
}

void TestComponent::onDeActive()
{
	utility::debugLog("TestComponent:onDeActive");
}

void TestComponent::onDestory()
{
	utility::debugLog("TestComponent:onDestroy");
}
