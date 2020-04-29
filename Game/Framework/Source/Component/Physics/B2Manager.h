#pragma once

#include<Framework/Include/Box2D/Box2D.h>

class B2Manager
{
public:
	B2Manager() = delete;

	static void Update();
	static b2World& World();

private:
	static b2World m_World;
	static constexpr float32 m_TimeStep = 1.0f / 60.0f;
	static constexpr int32 m_VelocityIterations = 8;//10
	static constexpr int32 m_PositionIterations = 3;//8
};