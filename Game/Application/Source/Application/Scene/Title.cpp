#include "Title.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>
#include<Source/Component/TestComponent1.h>
#include<Source/Component/LiquidFunComponent.h>
#include<Framework/Source/Component/Physics/B2BoxComponent.h>
#include<Framework/Source/Component/Physics/B2PolygonComponent.h>
#include<Framework/Source/Component/CameraComponent.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include<Framework/Source/Component/Graphics/LineComponent.h>
#include<Framework/Source/Component/Graphics/RegularPolygonComponent.h>
#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>

Title::Title(const std::string name)
	:AScene(name)
{
}

Title::~Title()
{
}

void Title::start()
{
	auto camera = Entity::Add(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), "camera", "camera1");
	camera->addComponent<CameraComponent>(true);

	//for (int i = 0; i < 11; ++i) 
	//{
	//	for (int j = 0; j < 10; ++j)
	//	{
	//		auto c = Entity::Add(XMFLOAT3(-100 + i * 20, 100 + j * 20, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(20, 20, 1), "", "");
	//		c->addComponent<MeshRendererComponent>(true);
	//		c->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.5f));
	//		c->addComponent<B2BoxComponent>(true, false);
	//		//c->addComponent<TestComponent1>(true);
	//	}
	//}

	auto a = Entity::Add(XMFLOAT3(0, 200, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(10, 10, 1), "", "");
	a->addComponent<MeshRendererComponent>(true);
	a->addComponent<RegularPolygonComponent>(true, 5, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
	a->addComponent<B2PolygonComponent>(true, true);

	auto b = Entity::Add(XMFLOAT3(0, -200, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(100, 10, 1), "", "");
	b->addComponent<MeshRendererComponent>(true);
	b->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
	b->addComponent<B2BoxComponent>(true, true);
	//b->addComponent<TestComponent>(true);
}

void Title::end()
{
}