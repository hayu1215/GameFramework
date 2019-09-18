#include"SpriteShader.h"
#include<d3dcompiler.h>
#include<wrl/client.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Device/D3d11.h>

SpriteShader::SpriteShader()
{
}

SpriteShader::SpriteShader(std::string name)
{
	load(D3d11::Instance().getDevice(),name);
}

SpriteShader::~SpriteShader()
{
}

void SpriteShader::passConstantBuffer(ID3D11DeviceContext* device, const Matrix4 &wvp,  float fAlpha, const Vector4 &vUv)
{
}

bool SpriteShader::load(ID3D11Device* device, const std::string &name)
{
	//LPCSTR lpc = name.c_str();
	std::string file = "Framework/Resource/Shader/" + name;
	std::wstring wname(file.begin(), file.end());
	HRESULT result = 0;
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ComPtr<ID3DBlob> pCompiledShader;

	//result = D3DX11CompileFromFile(lpc, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, pCompiledShader.GetAddressOf(), NULL, NULL);
	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (utility::checkError(result, "hlsl読み込み失敗"))return false;

	result = device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());
	if (utility::checkError(result, "バーテックスシェーダー作成失敗"))return false;

	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	result = device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	if (utility::checkError(result, "頂点インプットレイアウト作成失敗"))return false;

	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (utility::checkError(result, "hlsl読み込み失敗"))return false;

	result = device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());
	if (utility::checkError(result, "ピクセルシェーダー作成失敗"))return false;

	return true;
}