#pragma once

#include<Framework/Include/Box2D/Box2D.h>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Utility/Math/XMath.h>

class B2WorldComponent : public UpdateComponent {
public:
    B2WorldComponent();
    ~B2WorldComponent();

    void onCreate(const XMFLOAT2&);
    void update()override;
    b2World& world();

private:
    b2World m_world{ b2Vec2(0.0f, -60.0f) };
    const float32& m_timeStep = 1.0f / 10.0f;
    const int32& m_velocityIterations = 8;//10
    const int32& m_positionIterations = 3;//8
};