#include "TestComponent1.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Debug/Log.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include<Framework/Source/Component/Graphics/LineComponent.h>
#include<Framework/Source/Component/Graphics/RegularPolygonComponent.h>
#include<Framework/Source/Component/Physics/B2BoxComponent.h>
#include<Framework/Source/Utility/Math/XMath.h>

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
	//m_entity.lock()->getComponent<MeshComponent>().lock()->setRegularPolygon(30, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	m_entity.lock()->getComponent<RegularPolygonComponent>().lock()->setRegularPolygon(4, XMFLOAT4(0, 1, 1, 0.5f));
	m_entity.lock()->scale(XMFLOAT3(20, 20, 0));
}

void TestComponent1::update()
{
	//auto entity = m_entity.lock();
	//auto box = entity->getComponent<B2BoxComponent>().lock();

	//XMFLOAT3 pos = box->position();
	//debug::Log("x : " + std::to_string(pos.x) + " y : " + std::to_string(pos.y));
	//entity->position(pos);//box->position()‚ð’¼Úˆø”‚É“n‚·‚Æ‚¤‚Ü‚­‚¢‚©‚È‚¢

	//entity->rotate(XMFLOAT3(0, 0, box->angle()));
	//auto entity = m_entity.lock();
	//auto pos = entity->position();
	//entity->position(XMFLOAT3(pos.x + 0.1f, pos.y, pos.z));
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
