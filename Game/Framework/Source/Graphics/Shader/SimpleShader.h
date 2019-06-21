#pragma once

#include<wrl/client.h>
#include<string>
#include<d3d11.h>
#include<Framework/Source/Utility/Math/Matrix4.h>
#include<Framework/Source/Utility/Math/Vector4.h>

using namespace Microsoft::WRL;

class SimpleShader
{
public:
	SimpleShader();
	SimpleShader(const std::string& name);
	virtual ~SimpleShader();

	virtual void passConstantBuffer(ID3D11DeviceContext*, const Matrix4&, float, const Vector4&);
	virtual bool load(ID3D11Device*, const std::string&);
	ComPtr<ID3D11VertexShader> getVertexShader();
	ComPtr<ID3D11PixelShader> getPixelShader();
	ComPtr<ID3D11SamplerState> getSamplerState();
	ComPtr<ID3D11InputLayout> getInputLayout();
	ComPtr<ID3D11Buffer>getConstantBuffer();

protected:
	ComPtr<ID3D11VertexShader> m_pVertexShader;
	ComPtr<ID3D11PixelShader> m_pPixelShader;
	ComPtr<ID3D11SamplerState> m_pSamplerState;
	ComPtr<ID3D11InputLayout> m_pVertexLayout;
	ComPtr<ID3D11Buffer> m_pConstantBuffer;
};

