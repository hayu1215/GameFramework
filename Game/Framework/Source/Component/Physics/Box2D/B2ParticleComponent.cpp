#include "B2ParticleComponent.h"
#include<Framework/Source/Component/Physics/Box2D/B2WorldComponent.h>
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>
#include<Framework/Source/Component/Graphics/RegularPolygonComponent.h>
//#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>
#include<Framework/Source/Component/DestroyBoundaryComponent.h>
#include<Framework/Source/Utility/Debug/Log.h>

B2ParticleComponent::B2ParticleComponent() = default;

B2ParticleComponent::~B2ParticleComponent() = default;

void B2ParticleComponent::onCreate(const std::weak_ptr<Entity>& world) {
    m_meshRenderer = m_entity.lock()->getComponent<MeshRendererComponent>();

    const b2ParticleSystemDef particleSystemDef;
    m_particleSystem = world.lock()->getComponent<B2WorldComponent>().lock()->world().CreateParticleSystem(&particleSystemDef);
    m_particleSystem->SetDestructionByAge(true);
    m_particleSystem->SetMaxParticleCount(3000);
    //m_particleSystem->SetGravityScale(g);
    m_particleSystem->SetRadius(4.0f);

    b2ParticleGroupDef pd;
    b2PolygonShape shape;
    shape.SetAsBox(100, 100);
    pd.shape = &shape;
    //pd.flags = b2_elasticParticle;
    pd.angle = -0.5f;
    pd.angularVelocity = 2.0f;
    pd.position.Set(0, 0);
    pd.color.Set(0, 1, 1, 1);
    m_particleSystem->CreateParticleGroup(pd);

    auto colors = m_particleSystem->GetColorBuffer();
    auto radius = m_particleSystem->GetRadius();
    //for (unsigned int i = 0; i < m_particleSystem->GetParticleCount(); ++i)
    //{
    //	b2ParticleColor b2Color = colors[i];
    //	XMFLOAT4 color = XMFLOAT4(b2Color.r, b2Color.g, b2Color.b, b2Color.a);

    //	auto p = m_entity.lock()->addCild(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(radius*2, radius * 2, 0), "p", "p1");
    //	p->addComponent<MeshRendererComponent>(true);
    //	p->addComponent<RegularPolygonComponent>(true, 10, color);
    //	p->addComponent<DestroyBoundaryComponent>(true);
    //}

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

void B2ParticleComponent::update() {
    //auto polygonRenderer = m_entity.lock()->getComponent<MeshRendererComponent>().lock()->polygonRenderer();
    auto positions = m_particleSystem->GetPositionBuffer();
    auto size = m_particleSystem->GetParticleCount();

    Mesh mesh;
    mesh.indexes = { 0, 1, 2 };
    for (unsigned short i = 0; i < 3; ++i) {
        SimpleVertex vertex;
        vertex.color = XMFLOAT4(0, 0, 1, 0.3f);
        mesh.vertices.emplace_back(vertex);
    }
    for (unsigned int i = 0; i < size; ++i) {
        b2Vec2 b2Pos = positions[i];
        //XMFLOAT3 pos = XMFLOAT3(b2Pos.x, b2Pos.y, 0);
        mesh.vertices[0].pos = XMFLOAT3(b2Pos.x, b2Pos.y + 3, 0);
        mesh.vertices[1].pos = XMFLOAT3(b2Pos.x + 3, b2Pos.y - 3, 0);
        mesh.vertices[2].pos = XMFLOAT3(b2Pos.x - 3, b2Pos.y - 3, 0);
        //m_meshRenderer.lock()->polygonRenderer().addMesh(mesh);
        //auto p = m_entity.lock()->getChild(i);
        //p->position(pos);
    }
}

void B2ParticleComponent::destroyParticles() {
    b2ParticleGroup* group = m_particleSystem->GetParticleGroupList();
    while (group) {
        //m_particleSystem->SetGroupFlags(m_particleSystem->GetGroupFlags() & ~b2_particleGroupCanBeEmpty);
        group->DestroyParticles(false);
        group = group->GetNext();
    }
}
