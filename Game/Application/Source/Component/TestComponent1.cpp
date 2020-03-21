#include "TestComponent1.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>

TestComponent1::TestComponent1()
{
}

TestComponent1::TestComponent1(bool isActive)
	:UpdateComponent(isActive)
{
}

TestComponent1::~TestComponent1()
{
}

void TestComponent1::onCreate()
{
	m_entity.lock()->getComponent<MeshComponent>().lock()->setRegularPolygon(30, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
}

void TestComponent1::update()
{
	auto entity = m_entity.lock();
	auto pos = entity->position();
	entity->position(XMFLOAT3(pos.x + 0.1f, pos.y, pos.z));
}

void TestComponent1::onActive()
{
}

void TestComponent1::onDeActive()
{
}

void TestComponent1::onDestory()
{
}
