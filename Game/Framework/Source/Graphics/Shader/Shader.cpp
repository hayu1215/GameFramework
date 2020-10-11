#include "Shader.h"

Shader::Shader() {}

Shader::~Shader() {}

ComPtr<ID3D11VertexShader> Shader::getVertexShader() {
    return m_vertexShader;
}

ComPtr<ID3D11PixelShader> Shader::getPixelShader() {
    return m_pixelShader;
}

ComPtr<ID3D11GeometryShader> Shader::getGeometryShader() {
    return m_geometryShader;
}

ComPtr<ID3D11InputLayout> Shader::getInputLayout() {
    return m_vertexLayout;
}
