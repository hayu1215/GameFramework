#include "B2ParticleComponent.h"
#include"B2Manager.h"
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

B2ParticleComponent::B2ParticleComponent()
{
}

B2ParticleComponent::B2ParticleComponent(bool isActive)
{
}

B2ParticleComponent::~B2ParticleComponent()
{
}

void B2ParticleComponent::onCreate()
{
	const b2ParticleSystemDef particleSystemDef;
	m_particleSystem = B2Manager::World().CreateParticleSystem(&particleSystemDef);
	m_particleSystem->SetDestructionByAge(true);
	//m_particleSystem->SetMaxParticleCount(30);
	//m_particleSystem->SetGravityScale(g);
	m_particleSystem->SetRadius(1.0f);

	b2ParticleGroupDef pd;
	b2PolygonShape shape;
	shape.SetAsBox(10, 5);
	pd.shape = &shape;
	pd.flags = b2_elasticParticle;
	pd.angle = -0.5f;
	pd.angularVelocity = 2.0f;
	pd.position.Set(0, 0);
	pd.color.Set(0,1,1,1);
	m_particleSystem->CreateParticleGroup(pd);

	//for (unsigned int i = 0; i < 10; ++i)
	//{
	//	b2ParticleDef pd;
	//	pd.flags = b2_elasticParticle;
	//	pd.color.Set(0, 0, 255, 255);
	//	pd.position.Set(i, 0);
	//	auto index = m_particleSystem->CreateParticle(pd);
	//	m_particleSystem->SetParticleLifetime(index, 10.0f);
	//}
}

void B2ParticleComponent::update()
{
	auto positions = m_particleSystem->GetPositionBuffer();
	auto colors = m_particleSystem->GetColorBuffer();
	auto size = m_particleSystem->GetParticleCount();
	auto radius = m_particleSystem->GetRadius();

	for (unsigned int i = 0; i < size; ++i)
	{
		b2Vec2 b2Pos = positions[i];
		XMFLOAT3 pos = XMFLOAT3(b2Pos.x, b2Pos.y, 0);
		b2ParticleColor b2Color = colors[i];
		XMFLOAT4 color = XMFLOAT4(b2Color.r, b2Color.g, b2Color.b, b2Color.a);
	}
}

void B2ParticleComponent::onActive()
{
}

void B2ParticleComponent::onDeActive()
{
}

void B2ParticleComponent::onDestory()
{
}

void B2ParticleComponent::destroyParticles()
{
	b2ParticleGroup* group = m_particleSystem->GetParticleGroupList();
	while (group)
	{
		//m_particleSystem->SetGroupFlags(m_particleSystem->GetGroupFlags() & ~b2_particleGroupCanBeEmpty);
		group->DestroyParticles(false);
		group = group->GetNext();
	}
}
