#include "AShader.h"

AShader::AShader() {}

AShader::~AShader() {}

ComPtr<ID3D11VertexShader> AShader::getVertexShader() {
    return m_vertexShader;
}

ComPtr<ID3D11PixelShader> AShader::getPixelShader() {
    return m_pixelShader;
}

ComPtr<ID3D11GeometryShader> AShader::getGeometryShader() {
    return m_geometryShader;
}

ComPtr<ID3D11InputLayout> AShader::getInputLayout() {
    return m_vertexLayout;
}
