#pragma once

#include<Framework/Include/Box2D/Box2D.h>

class B2Manager
{
public:
	B2Manager() = delete;

	static void Update();

public:
	static b2World m_World;
private:
	static constexpr float32 timeStep = 1.0f / 60.0f;
	static constexpr int32 velocityIterations = 6;
	static constexpr int32 positionIterations = 2;
};