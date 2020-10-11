#include"RegularPolygonComponent.h"
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/Mathf.h>

RegularPolygonComponent::RegularPolygonComponent() = default;

RegularPolygonComponent::~RegularPolygonComponent() = default;

void RegularPolygonComponent::onCreate(unsigned int vertexCount, const XMFLOAT4& color) {
    setRegularPolygon(vertexCount, color);
}

void RegularPolygonComponent::draw() {
    updateTransform();
    MeshComponent::draw();
}

void RegularPolygonComponent::setRegularPolygon(unsigned int vertexCount, const XMFLOAT4& color) {
    std::vector<XMFLOAT3> vertices;
    if (vertexCount == 4) vertices = { XMFLOAT3(-0.5f, 0.5f, 0), XMFLOAT3(0.5f, 0.5f, 0),  XMFLOAT3(0.5f, -0.5f, 0),  XMFLOAT3(-0.5f, -0.5f, 0) };
    else vertices = regularPolygonVertices(0.5f, vertexCount);

    std::vector<SimpleVertex> model;
    for (int i = 0; i < vertexCount; i++) {
        SimpleVertex sv;
        sv.pos = vertices[i];
        sv.color = color;
        model.emplace_back(sv);
    }
    m_model = model;
    setIndex(vertexCount, false);
}

std::vector<XMFLOAT3> RegularPolygonComponent::regularPolygonVertices(float radius, unsigned int count) {
    std::vector<XMFLOAT3> res;
    float angle = 2 * mathf::PI / count;
    for (unsigned int i = 0; i < count; i++) {
        auto x = mathf::Sin(i * angle) * radius;
        auto y = mathf::Cos(i * angle) * radius;
        res.emplace_back(XMFLOAT3(x, y, 0));
    }
    return res;
}

void RegularPolygonComponent::updateTransform() {
    auto entity = m_entity.lock();
    auto position = entity->position();
    auto rotate = entity->rotate();
    auto scale = entity->scale();

    XMMATRIX scaleM = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f);
    XMMATRIX rotateM = DirectX::XMMatrixRotationZ(rotate.z);
    XMMATRIX translationM = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    XMMATRIX worldM = scaleM * rotateM * translationM;

    m_mesh.vertices = m_model;
    for (auto& x : m_mesh.vertices) {
        XMStoreFloat3(&x.pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&x.pos), worldM));
    }
}
