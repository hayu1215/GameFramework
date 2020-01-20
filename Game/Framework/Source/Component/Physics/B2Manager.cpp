#include"B2Manager.h"

b2World B2Manager::m_World(b2Vec2(0.0f, -10.0f));

void B2Manager::Update()
{
	m_World.Step(timeStep, velocityIterations, positionIterations);
}

b2World& B2Manager::World()
{
	return m_World;
}
