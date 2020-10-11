#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include<vector>
#include"Texture.h"
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>

using Microsoft::WRL::ComPtr;

struct LineVertex {
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct LineCBuffer {
    XMFLOAT4X4 wvp;
    XMFLOAT4 width;
};

class LineRenderer {
public:
    LineRenderer();
    ~LineRenderer();

    void drawLine(const XMFLOAT3& position1, const XMFLOAT3& position2, const XMFLOAT4& color1,
                  const XMFLOAT4& color2, float width);
    void drawLine(const std::string& name, const std::vector<XMFLOAT3>& vertexes,
                  const std::vector<XMFLOAT4>& clors, float width);

private:
    void createVertexBuffer();
    void createConstantBuffer();
    void createVertexBuffer2();
    void createConstantBuffer2();

    ComPtr<ID3D11Buffer> m_constantBuffer;
    ComPtr<ID3D11Buffer> m_vertexBuffer;
};