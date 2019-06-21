#include "Title.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>

Title::Title(const std::string name)
	:AScene(name)
{
}

Title::~Title()
{
}

void Title::start()
{
	utility::debugLog("Tittle: start");
	addEntity(std::make_shared<Entity>("test", "test"))
		->addComponent(std::make_shared<TestComponent>());
}

void Title::end()
{
	utility::debugLog("Tittle: end");
}