#pragma once

#include<memory>
#include<vector>
#include<Framework/Include/Box2D/Box2D.h>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Component/Entity.h>

class B2PolygonComponent : public UpdateComponent {
public:
    B2PolygonComponent();
    ~B2PolygonComponent();

    void onCreate(const std::weak_ptr<Entity>& world, bool isStatic);
    void onCreate(const std::weak_ptr<Entity>& world, bool isStatic,
                  const std::vector<XMFLOAT3>& vertexes);
    void update()override;

    float angle();
    const XMFLOAT3& position();
    const std::vector<XMFLOAT3>& vertices();

private:
    void createBody(const std::weak_ptr<Entity>& world, bool isStatic,
                    const std::vector<XMFLOAT3>& vertexes);
    b2Body* m_body;
    //const bool m_isStatic;
    //std::vector<b2Vec2> m_vertexes;
};