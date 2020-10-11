#pragma once

#include<wrl/client.h>
#include<d3d11.h>
#include<string>

using Microsoft::WRL::ComPtr;

class Shader {
public:
    Shader();
    virtual ~Shader();

    virtual void load(const std::string&) = 0;

    ComPtr<ID3D11VertexShader> getVertexShader();
    ComPtr<ID3D11PixelShader> getPixelShader();
    ComPtr<ID3D11GeometryShader> getGeometryShader();
    ComPtr<ID3D11InputLayout> getInputLayout();

protected:
    ComPtr<ID3D11VertexShader> m_vertexShader;
    ComPtr<ID3D11PixelShader> m_pixelShader;
    ComPtr<ID3D11GeometryShader> m_geometryShader;
    ComPtr<ID3D11InputLayout> m_vertexLayout;
};

