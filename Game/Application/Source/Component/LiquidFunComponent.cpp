#include "LiquidFunComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Utility/Math/XMath.h>

LiquidFunComponent::LiquidFunComponent()
	:m_World(b2Vec2(0.0f,-10.0f))
{
	a = std::make_shared<Camera>();
	lineRenderer = std::make_unique<LineRenderer>(a);
}

LiquidFunComponent::~LiquidFunComponent()
{
}

void LiquidFunComponent::init()
{
	//ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	m_GroundBody = m_World.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	m_GroundBody->CreateFixture(&groundBox, 0.0f);

	//object
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 100.0f);
	bodyDef.angle = 90;
	bodyDef.angularVelocity = 5;
	m_Body = m_World.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(10.0f, 10.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_Body->CreateFixture(&fixtureDef);
}

void LiquidFunComponent::update()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_World.Step(timeStep, velocityIterations, positionIterations);

	b2Fixture* f = m_Body->GetFixtureList();
	b2PolygonShape* s = (b2PolygonShape*)f->GetShape();

	int size = s->GetVertexCount();
	std::vector<XMFLOAT3>pos1;
	pos1.resize(4);
	for (int i = 0; i < s->GetVertexCount(); i++) {
		b2Vec2 v = s->GetVertex(i);
		XMVECTORF32 xv = XMVECTORF32{ v.x, v.y, 0 };
		XMMATRIX scale;
		scale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
		XMMATRIX rotate;
		rotate = DirectX::XMMatrixRotationZ(m_Body->GetAngle());
		XMMATRIX translation;
		translation = DirectX::XMMatrixTranslation(m_Body->GetPosition().x, m_Body->GetPosition().y, 0);
		XMMATRIX world = scale *  rotate * translation;
		XMStoreFloat3(&pos1[i], DirectX::XMVector3Transform(xv, world));
	}
	pos1.push_back(pos1.front());
	std::vector<XMFLOAT4> col = { XMFLOAT4(1, 0, 0, 1) };
	lineRenderer->drawLine("LineShader.hlsl", pos1, col, 1.0f);
	//	XMFLOAT4X4 mRotate;
//	mRotate = XMFLOAT4X4::RotationFromAxisZ(info.angle);
}

void LiquidFunComponent::onActive()
{
}

void LiquidFunComponent::onDeActive()
{
}

void LiquidFunComponent::onDestory()
{
}