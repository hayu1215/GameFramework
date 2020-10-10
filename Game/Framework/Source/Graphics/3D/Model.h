#pragma once

#include<string>
#include<vector>
#include<memory>
#include<wrl/client.h>
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Graphics/VertexType.h>

using Microsoft::WRL::ComPtr;

class Model {
public:
    Model();
    Model(const std::string &name);
    ~Model();

    void load(const std::string &name);
    ComPtr<ID3D11Buffer> getVertexBuffer();
    ComPtr<ID3D11Buffer> getIndexBuffer();
    unsigned int getIndexCount();

private:
    //std::vector<ObjVertex> m_Vertexes;
    //std::vector<unsigned int> m_Indexes;

    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11Buffer> m_indexBuffer;
    unsigned int m_indexCount = 0;
};