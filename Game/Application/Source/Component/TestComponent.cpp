#include "TestComponent.h"
#include<Framework/Source/Utility/Judge.h>

TestComponent::TestComponent()
{
}

TestComponent::~TestComponent()
{
}

void TestComponent::init()
{
	m_pEntity.lock()->destroy();
}

void TestComponent::update()
{
}

void TestComponent::onActive()
{
}

void TestComponent::onDeActive()
{
}

void TestComponent::onDestory()
{
}
