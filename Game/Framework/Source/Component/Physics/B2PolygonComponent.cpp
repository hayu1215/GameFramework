#include "B2PolygonComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include"B2Manager.h"

B2PolygonComponent::B2PolygonComponent()
	:m_IsStatic(false), m_Vertexes({ b2Vec2(0,10), b2Vec2(-10,-10), b2Vec2(10,-10) })
{
}

B2PolygonComponent::B2PolygonComponent(bool isActive, bool isStatic, const std::vector<b2Vec2>& vertexes)
	:UpdateComponent(isActive), m_IsStatic(isStatic), m_Vertexes(vertexes)
{
}

B2PolygonComponent::~B2PolygonComponent()
{
}

void B2PolygonComponent::onCreate()
{
	lineRenderer = std::make_unique<LineRenderer>();

	//object
	b2BodyDef bodyDef;

	if (m_IsStatic)bodyDef.type = b2_staticBody;
	else bodyDef.type = b2_dynamicBody;

	XMFLOAT3 pos = m_pEntity.lock()->getPosition();
	bodyDef.position.Set(pos.x, pos.y);
	m_pBody = B2Manager::World().CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.Set(&m_Vertexes[0], m_Vertexes.size());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_pBody->CreateFixture(&fixtureDef);
}

void B2PolygonComponent::update()
{
	std::vector<XMFLOAT3>pos;
	pos.resize(m_Vertexes.size());
	for (int i = 0; i < m_Vertexes.size(); i++) {
		XMVECTORF32 xv = XMVECTORF32{ m_Vertexes[i].x, m_Vertexes[i].y, 0 };
		XMMATRIX rotate;
		rotate = DirectX::XMMatrixRotationZ(m_pBody->GetAngle());
		XMMATRIX translation;
		translation = DirectX::XMMatrixTranslation(m_pBody->GetPosition().x, m_pBody->GetPosition().y, 0);
		XMMATRIX world = rotate * translation;
		XMStoreFloat3(&pos[i], DirectX::XMVector3Transform(xv, world));
	}
	pos.push_back(pos.front());
	std::vector<XMFLOAT4> col = { XMFLOAT4(0, 1, 1, 1.0f) };
	lineRenderer->drawLine("LineShader.hlsl", pos, col, 1.0f);
}

void B2PolygonComponent::onActive()
{
}

void B2PolygonComponent::onDeActive()
{
}

void B2PolygonComponent::onDestory()
{
}