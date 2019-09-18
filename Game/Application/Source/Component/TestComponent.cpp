#include "TestComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>

TestComponent::TestComponent()
{
	a = std::make_shared<Camera>();
}

TestComponent::~TestComponent()
{
}

void TestComponent::init()
{
	//m_pEntity.lock()->destroy();
}

void TestComponent::update()
{
	static float angle = 0;
	//angle += 0.01f;
	Spritebatch spritebatch(a);
	spritebatch.begin();
	//spritebatch.draw("blue.png", Vector3(-200, 0, 1.0f), Vector2(1, 1), angle, Vector2(0, 0), Vector4(0, 0, 1, 1), Vector4(0.5f, 0.5f, 1, 1));
	//spritebatch.draw("red.png", Vector3(0, 0, 0.5f), Vector2(1, 1), 0, Vector2(0, 0), Vector4(0, 0, 1, 1), Vector4(1, 1, 1, 0.5f));
	//spritebatch.draw("blue.png", Vector3(200, 0, 0.0f), Vector2(1, 1), 0, Vector2(0, 0), Vector4(0, 0, 1, 1), Vector4(1, 1, 1, 1));
	spritebatch.draw("green_pepper.png", Vector3(0, 0, 0), Vector2(1, 1), 0, Vector2(0, 0), Vector4(0, 0, 1, 1), Vector4(1, 1, 1, 1));
	spritebatch.end("SpritebatchShader.hlsl");
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
