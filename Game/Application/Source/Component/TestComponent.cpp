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
	//Spritebatch spritebatch(a);
	//spritebatch.begin();
	//spritebatch.draw("blue.png", XMFLOAT3(-200, 0, 1.0f), XMFLOAT2(1, 1), angle, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(0.5f, 0.5f, 1, 1));
	//spritebatch.draw("red.png", XMFLOAT3(0, 0, 0.5f), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 0.5f));
	//spritebatch.draw("blue.png", XMFLOAT3(200, 0, 0.0f), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 1));
	//spritebatch.draw("green_pepper.png", XMFLOAT3(0, 0, 0), XMFLOAT2(1, 1), 0, XMFLOAT2(0, 0), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 1, 1, 1));
	//spritebatch.end("SpritebatchShader.hlsl");

	//LineRenderer lineRenderer(a);
	//lineRenderer->drawLine(XMFLOAT3(-200, 100, 0), XMFLOAT3(200, -100, 0), XMFLOAT4(1, 1, 0, 1), XMFLOAT4(1, 0, 0, 1), 40.0f);
	//std::vector<XMFLOAT3> pos = { XMFLOAT3(-200, 0, 0), XMFLOAT3(-100, 100, 0), XMFLOAT3(100, 100, 0), XMFLOAT3(200, 0, 0) };
	//std::vector<XMFLOAT4> col = { XMFLOAT4(1, 1, 0, 1), XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 1, 0, 1) };
	std::vector<XMFLOAT3> pos1 = { XMFLOAT3(-200, 0, 0), XMFLOAT3(-100, 100, 0), XMFLOAT3(100, 100, 0), XMFLOAT3(200, 0, 0) };
	std::vector<XMFLOAT4> col1 = { XMFLOAT4(1, 1, 0, 1), XMFLOAT4(1, 0, 0, 1), XMFLOAT4(1, 1, 0, 1), XMFLOAT4(1, 1, 0, 1) };
	std::vector<XMFLOAT3> pos2 = { XMFLOAT3(-200, -1, 0), XMFLOAT3(-100, 99, 0), XMFLOAT3(100, 99, 0), XMFLOAT3(200, -1, 0), XMFLOAT3(100, -99, 0) };
	std::vector<XMFLOAT4> col2 = { XMFLOAT4(1, 0, 0, 1), XMFLOAT4(0, 1, 0, 1), XMFLOAT4(0, 0, 1, 1), XMFLOAT4(1, 0, 0, 1) , XMFLOAT4(0, 1, 0, 1) };
	//lineRenderer->drawLine("LineShaderTest.hlsl",pos1, col1, 40.0f);
	//lineRenderer->drawLine("LineShader.hlsl", pos1, col1, 3.0f);

	//drawBezier(XMFLOAT3(-200, 0, 0), XMFLOAT3(-100, 200, 0), XMFLOAT3(100, -200, 0), XMFLOAT3(200, 0, 0), 30);
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

void TestComponent::drawBezier(const XMFLOAT3 & p0, const XMFLOAT3 & p1, const XMFLOAT3 & p2, const XMFLOAT3 & p3, int s)
{
	double t = 1.0f / s;
	std::vector<XMFLOAT3>pos;

	for (int i = 0; i < s + 1; i++)
	{
		XMFLOAT3 v = bezier(p0, p1, p2, p3, i * t);
		pos.emplace_back(v);
	}
	std::vector<XMFLOAT4> col = { XMFLOAT4(1, 0, 0, 1) };
	lineRenderer->drawLine("LineShader.hlsl", pos, col, 20.0f);
}

XMFLOAT3 TestComponent::bezier(const XMFLOAT3 & p0, const XMFLOAT3 & p1, const XMFLOAT3 & p2, const XMFLOAT3 & p3, float t)
{
	auto a = DirectX::XMVectorLerp(DirectX::XMLoadFloat3(&p0), DirectX::XMLoadFloat3(&p1), t);
	auto b = DirectX::XMVectorLerp(DirectX::XMLoadFloat3(&p1), DirectX::XMLoadFloat3(&p2), t);
	auto c = DirectX::XMVectorLerp(DirectX::XMLoadFloat3(&p2), DirectX::XMLoadFloat3(&p3), t);

	auto d = DirectX::XMVectorLerp(a, b, t);
	auto e = DirectX::XMVectorLerp(b, c, t);

	XMFLOAT3 res;
	DirectX::XMStoreFloat3(&res,DirectX::XMVectorLerp(d, e, t));

	return res;
}