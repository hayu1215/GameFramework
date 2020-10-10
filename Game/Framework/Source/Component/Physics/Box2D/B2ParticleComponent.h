#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Include/Box2D/Box2D.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>

class B2ParticleComponent : public UpdateComponent {
public:
    B2ParticleComponent();
    ~B2ParticleComponent();

    void onCreate(const std::weak_ptr<Entity>& world);
    void update()override;

    void destroyParticles();

private:
    b2ParticleSystem* m_particleSystem;
    std::weak_ptr<MeshRendererComponent> m_meshRenderer;
};