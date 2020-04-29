#include"B2Manager.h"

b2World B2Manager::m_World(b2Vec2(0.0f, -40.0f));

void B2Manager::Update()
{
	m_World.Step(m_TimeStep, m_VelocityIterations, m_PositionIterations);
}

b2World& B2Manager::World()
{
	return m_World;
}
