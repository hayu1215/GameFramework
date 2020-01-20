#include "B2BoxComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include"B2Manager.h"

B2BoxComponent::B2BoxComponent()
	:m_IsStatic(false), m_Size(10, 10)
{
}

B2BoxComponent::B2BoxComponent(bool isActive, bool isStatic, const XMFLOAT2 & size)
	:UpdateComponent(isActive), m_IsStatic(isStatic),m_Size(size)
{
}

B2BoxComponent::~B2BoxComponent()
{
}

void B2BoxComponent::onCreate()
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
	shape.SetAsBox(m_Size.x, m_Size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_pBody->CreateFixture(&fixtureDef);
}

void B2BoxComponent::update()
{
	b2Fixture* f = m_pBody->GetFixtureList();
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
		rotate = DirectX::XMMatrixRotationZ(m_pBody->GetAngle());
		XMMATRIX translation;
		translation = DirectX::XMMatrixTranslation(m_pBody->GetPosition().x, m_pBody->GetPosition().y, 0);
		XMMATRIX world = scale * rotate * translation;
		XMStoreFloat3(&pos1[i], DirectX::XMVector3Transform(xv, world));
	}
	pos1.push_back(pos1.front());
	std::vector<XMFLOAT4> col = { XMFLOAT4(0, 1, 1, 1.0f) };
	lineRenderer->drawLine("LineShader.hlsl", pos1, col, 1.0f);
}

void B2BoxComponent::onActive()
{
}

void B2BoxComponent::onDeActive()
{
}

void B2BoxComponent::onDestory()
{
}