#include "B2WorldComponent.h"

B2WorldComponent::B2WorldComponent() = default;

B2WorldComponent::~B2WorldComponent() = default;

void B2WorldComponent::onCreate(const XMFLOAT2& f2) {
    m_world.SetGravity(b2Vec2(f2.x, f2.y));
}

void B2WorldComponent::update() {
    m_world.Step(m_timeStep, m_velocityIterations, m_positionIterations);
}

b2World& B2WorldComponent::world() {
    return m_world;
}