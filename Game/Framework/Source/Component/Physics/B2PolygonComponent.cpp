#include "B2PolygonComponent.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include"B2Manager.h"

B2PolygonComponent::B2PolygonComponent()
{
	createBody(false, { XMFLOAT3(0, 10, 0), XMFLOAT3(-10, -10, 0), XMFLOAT3(10, -10, 0) });
}

B2PolygonComponent::B2PolygonComponent(bool isActive, bool isStatic)
	:UpdateComponent(isActive)
{
	if (true)
	{
		auto vertexes = m_entity.lock()->getComponent<MeshComponent>().lock()->model();
		std::vector<XMFLOAT3> vs;
		for (const auto& v : vertexes) {
			vs.emplace_back(v.pos);
		}
		createBody(isStatic, vs);
	}
	else
	{
		createBody(isStatic, { XMFLOAT3(0, 10, 0), XMFLOAT3(-10, -10, 0), XMFLOAT3(10, -10, 0) });
	}
	//auto vertexes = m_entity.lock()->getComponent<MeshComponent>().lock()->model();
	//std::vector<XMFLOAT3> vs;
	//for (const auto& v : vertexes) {
	//	vs.emplace_back(v.pos);
	//}
	//createBody(isStatic, vs);
}

B2PolygonComponent::B2PolygonComponent(bool isActive, bool isStatic, const std::vector<XMFLOAT3>& vertexes)
	:UpdateComponent(isActive)
{
	createBody(isStatic, vertexes);
}

B2PolygonComponent::~B2PolygonComponent()
{
}

void B2PolygonComponent::onCreate()
{
}

void B2PolygonComponent::update()
{
	auto entity = m_entity.lock();
	entity->position(position());
	entity->rotate(XMFLOAT3(0, 0, angle()));
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

float B2PolygonComponent::angle()
{
	return m_body->GetAngle();
}

const XMFLOAT3 & B2PolygonComponent::position()
{
	auto pos = m_body->GetPosition();
	return XMFLOAT3(pos.x, pos.y, 0);
}

const std::vector<XMFLOAT3>& B2PolygonComponent::vertices()
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

void B2PolygonComponent::createBody(bool isStatic, const std::vector<XMFLOAT3>& vertexes)
{
	std::vector<b2Vec2> vs;
	auto scale = m_entity.lock()->scale();
	XMMATRIX scaleM = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f);
	for (unsigned int i = 0; i < vertexes.size(); ++i) {
		auto vertex = vertexes[i];
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertex), scaleM);
		vs.emplace_back(b2Vec2(vertex.x, vertex.y));
	}

	b2BodyDef bodyDef;
	if (isStatic) bodyDef.type = b2_staticBody;
	else bodyDef.type = b2_dynamicBody;

	XMFLOAT3 pos = m_entity.lock()->position();
	bodyDef.position.Set(pos.x, pos.y);
	m_body = B2Manager::World().CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.Set(&vs[0], vs.size());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_body->CreateFixture(&fixtureDef);
}