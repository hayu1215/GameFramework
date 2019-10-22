#include "TestComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>

TestComponent::TestComponent()
{
	a = std::make_shared<Camera>();
	lineRenderer = std::make_unique<LineRenderer>(a);
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
	//spritebatch.draw("blue.png", XMFLOAT3(-200, 0, 1.0f), XMFLOAT2(1, 1), angle, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(0.5f, 0.5f, 1, 1));
	//spritebatch.draw("red.png", XMFLOAT3(0, 0, 0.5f), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 0.5f));
	//spritebatch.draw("blue.png", XMFLOAT3(200, 0, 0.0f), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 1));
	spritebatch.draw("green_pepper.png", XMFLOAT3(0, 0, 0), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 1));
	spritebatch.end("SpritebatchShader.hlsl");

	//LineRenderer lineRenderer(a);
	//lineRenderer->drawLine(XMFLOAT3(-200, 100, 0), XMFLOAT3(200, -100, 0), XMFLOAT4(1, 1, 0, 1), XMFLOAT4(0, 0, 1, 1), 40.0f);
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
