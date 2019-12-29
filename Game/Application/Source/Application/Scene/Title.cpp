#include "Title.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>
#include<Source/Component/LiquidFunComponent.h>

Title::Title(const std::string name)
	:AScene(name)
{
}

Title::~Title()
{
}

void Title::start()
{
	addEntity(std::make_shared<Entity>("test", "test"))
		->addComponent(std::make_shared<TestComponent>())
		->addComponent(std::make_shared<LiquidFunComponent>());
}

void Title::end()
{
}