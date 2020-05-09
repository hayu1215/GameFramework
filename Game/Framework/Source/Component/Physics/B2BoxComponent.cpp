#include "B2BoxComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include"B2Manager.h"

B2BoxComponent::B2BoxComponent() = default;
B2BoxComponent::~B2BoxComponent() = default;

void B2BoxComponent::onCreate(bool isStatic, const XMFLOAT2& size)
{
	m_isStatic = isStatic;
	m_size = size;

	auto entity = m_entity.lock();
	//object
	b2BodyDef bodyDef;

	if (m_isStatic) bodyDef.type = b2_staticBody;
	else bodyDef.type = b2_dynamicBody;

	XMFLOAT3 pos = entity->position();
	bodyDef.position.Set(pos.x, pos.y);
	m_body = B2Manager::World().CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(entity->scale().x / 2, entity->scale().y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_body->CreateFixture(&fixtureDef);
}

void B2BoxComponent::update()
{
	auto entity = m_entity.lock();
	auto pos = position();
	entity->position(pos);
	entity->rotate(XMFLOAT3(0, 0, angle()));
}

float B2BoxComponent::angle()
{
	return m_body->GetAngle();
}

const XMFLOAT3& B2BoxComponent::position()
{
	auto pos = m_body->GetPosition();
	return XMFLOAT3(pos.x, pos.y, 0);
}

const std::vector<XMFLOAT3>& B2BoxComponent::vertices()
{
	b2Fixture* f = m_body->GetFixtureList();
	b2PolygonShape* s = static_cast<b2PolygonShape*>(f->GetShape());
	std::vector<XMFLOAT3> vs;
	for (unsigned int i = 0; i < s->GetVertexCount(); ++i)
	{
		auto v = s->GetVertex(i);
		vs.emplace_back(XMFLOAT3(v.x, v.y, 0));
	}
	return vs;
}