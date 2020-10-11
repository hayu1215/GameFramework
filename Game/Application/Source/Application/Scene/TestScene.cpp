#include"TestScene.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>

TestScene::TestScene(const std::string name)
    : Scene(name) {}

TestScene::~TestScene() {}

void TestScene::start() {
    //addEntity(std::make_shared<Entity>("test", "test"))
    //	->addComponent(std::make_shared<TestComponent>());
}

void TestScene::end() {}