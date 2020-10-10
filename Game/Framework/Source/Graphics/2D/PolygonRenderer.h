#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include<vector>
#include<unordered_map>
#include"Texture.h"
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Graphics/VertexType.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Application/Task/UpdateSystem.h>

using Microsoft::WRL::ComPtr;

class MeshComponent;
class ModelComponent;

struct Mesh {
    std::vector<SimpleVertex> vertices;
    std::vector<unsigned short> indexes;
};

struct DrawInstance {
    XMFLOAT3 position;
    XMFLOAT3 rotate;
    XMFLOAT3 scale;
    XMFLOAT4 color;
};

class PolygonRenderer : public UpdateSystem {
public:
    PolygonRenderer();
    ~PolygonRenderer() override;

    void update();
    void addModelComponent(const std::weak_ptr<ModelComponent>&);

private:
    void createOffsetBuffer();
    void createConstantBuffer();
    void setInfo();
    void draw();
    void viewUpdate();

    const unsigned int BITONIC_BLOCK_SIZE = 1024;
    const unsigned int BITONIC_BLOCK_NUM = 32; //min 16 max 1024
    const unsigned int ELEMENTS_NUM = 10000;//BITONIC_BLOCK_SIZE * BITONIC_BLOCK_NUM;
    std::unordered_map<std::string, std::vector<std::weak_ptr<ModelComponent>>> m_modelComponents;
    ComPtr<ID3D11Buffer> m_offsetBuffer;
    ComPtr<ID3D11Buffer> m_constantBuffer;
};