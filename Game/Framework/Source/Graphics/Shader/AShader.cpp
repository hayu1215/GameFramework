#include "AShader.h"

AShader::AShader()
{
}

AShader::~AShader()
{
}

ComPtr<ID3D11VertexShader> AShader::getVertexShader()
{
	return m_pVertexShader;
}

ComPtr<ID3D11PixelShader> AShader::getPixelShader()
{
	return m_pPixelShader;
}

ComPtr<ID3D11GeometryShader> AShader::getGeometryShader()
{
	return m_pGeometryShader;
}

ComPtr<ID3D11InputLayout> AShader::getInputLayout()
{
	return m_pVertexLayout;
}
