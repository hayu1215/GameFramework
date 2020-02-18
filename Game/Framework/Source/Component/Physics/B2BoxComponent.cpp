#include "B2BoxComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include"B2Manager.h"

B2BoxComponent::B2BoxComponent()
	:m_isStatic(false), m_size(10, 10)
{
}

B2BoxComponent::B2BoxComponent(bool isActive, bool isStatic, const XMFLOAT2 & size)
	:UpdateComponent(isActive), m_isStatic(isStatic),m_size(size)
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

	if (m_isStatic)bodyDef.type = b2_staticBody;
	else bodyDef.type = b2_dynamicBody;

	XMFLOAT3 pos = m_entity.lock()->getPosition();
	bodyDef.position.Set(pos.x, pos.y);
	m_body = B2Manager::World().CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(m_size.x, m_size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_body->CreateFixture(&fixtureDef);
}

void B2BoxComponent::update()
{
	b2Fixture* f = m_body->GetFixtureList();
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
		rotate = DirectX::XMMatrixRotationZ(m_body->GetAngle());
		XMMATRIX translation;
		translation = DirectX::XMMatrixTranslation(m_body->GetPosition().x, m_body->GetPosition().y, 0);
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