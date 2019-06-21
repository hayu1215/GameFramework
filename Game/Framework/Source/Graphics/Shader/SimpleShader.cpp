#include "SimpleShader.h"


SimpleShader::SimpleShader()
{
}

SimpleShader::SimpleShader(const std::string & name)
{

}

SimpleShader::~SimpleShader()
{
}

void SimpleShader::passConstantBuffer(ID3D11DeviceContext*, const Matrix4 &, float, const Vector4 &)
{
}

bool SimpleShader::load(ID3D11Device*, const std::string &)
{
	return false;
}

ComPtr<ID3D11VertexShader> SimpleShader::getVertexShader()
{
	return m_pVertexShader;
}

ComPtr<ID3D11PixelShader> SimpleShader::getPixelShader()
{
	return m_pPixelShader;
}

ComPtr<ID3D11SamplerState> SimpleShader::getSamplerState()
{
	return m_pSamplerState;
}

ComPtr<ID3D11InputLayout> SimpleShader::getInputLayout()
{
	return m_pVertexLayout;
}

ComPtr<ID3D11Buffer> SimpleShader::getConstantBuffer()
{
	return m_pConstantBuffer;
}
