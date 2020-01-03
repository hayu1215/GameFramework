#include "Title.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>
#include<Source/Component/LiquidFunComponent.h>
#include<Framework/Source/Component/Physics/B2BoxComponent.h>
#include<Framework/Source/Component/Physics/B2PolygonComponent.h>

Title::Title(const std::string name)
	:AScene(name)
{
}

Title::~Title()
{
}

void Title::start()
{
	auto a = addEntity(std::make_shared<Entity>(XMFLOAT3(0, -100, 0), "entity", "entity1"));
	a->addComponent(std::make_shared<B2BoxComponent>(true, XMFLOAT2(100, 10)));

	for (int i = 0; i < 10; i++) 
	{
		auto b = addEntity(std::make_shared<Entity>(XMFLOAT3(0, 100 + i * 20, 0), "entity", "entity2"));
		b->addComponent(std::make_shared<TestComponent>());
		b->addComponent(std::make_shared<B2PolygonComponent>(false, std::vector<b2Vec2>{ b2Vec2(0,10), b2Vec2(-5,5), b2Vec2(-5,-5), b2Vec2(0,-10), b2Vec2(5,-5), b2Vec2(5,5) }));
		//b->addComponent(std::make_shared<B2PolygonComponent>());
		//b->addComponent(std::make_shared<B2BoxComponent>(false, XMFLOAT2(10 + i * 5, 10)));
	}
}

void Title::end()
{
}