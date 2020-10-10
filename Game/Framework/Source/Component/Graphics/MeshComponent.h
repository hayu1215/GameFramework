#pragma once

#include<memory>
#include<Framework/Source/Component/DrawComponent.h>
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

class MeshRendererComponent;

class MeshComponent : public DrawComponent {
public:
    MeshComponent();
    ~MeshComponent();

    void onCreate()override;
    void draw()override;

    const Mesh& mesh();
    const std::vector<SimpleVertex>& model();

protected:
    void setIndex(unsigned int count, bool isStrip = true);
    std::vector<SimpleVertex> m_model;
    Mesh m_mesh;

private:
    std::weak_ptr<MeshRendererComponent> m_polygonRenderer;
};