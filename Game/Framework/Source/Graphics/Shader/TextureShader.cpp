#include"TextureShader.h"
#include<d3dcompiler.h>
#include<wrl/client.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Device/D3d11.h>

TextureShader::TextureShader()
{
}

TextureShader::TextureShader(std::string name)
{
	load(D3d11::Instance().getDevice(),name);
}

TextureShader::~TextureShader()
{
}

void TextureShader::passConstantBuffer(ID3D11DeviceContext* device, const Matrix4 &wvp,  float fAlpha, const Vector4 &vUv)
{
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;

	HRESULT result = device->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (!utility::checkError(result, "DeviceContextのMapの失敗"))
	{
		//ワールド、カメラ、射影行列を渡す
		//Matrix4Transpose(&wvp, &wvp);
		cb.mWVP = wvp;

		//カラーを渡す
		//Vector4 vColor(0, 0, 0, 1);
		//cb.vColor = vColor;

		//透明度を渡す
		/*float fAlpha = 0.7f;*/
		cb.fAlpha.x = fAlpha;
		//cb.fAlpha = fAlpha;
		cb.vUv = vUv;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		device->Unmap(m_pConstantBuffer.Get(), 0);
	}
}

bool TextureShader::load(ID3D11Device* device, const std::string &name)
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

	result = device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, m_pVertexShader.GetAddressOf());
	if (utility::checkError(result, "バーテックスシェーダー作成失敗"))return false;

	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	result = device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	if (utility::checkError(result, "頂点インプットレイアウト作成失敗"))return false;

	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (utility::checkError(result, "hlsl読み込み失敗"))return false;

	result = device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, m_pPixelShader.GetAddressOf());
	if (utility::checkError(result, "ピクセルシェーダー作成失敗"))return false;

	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	result = device->CreateSamplerState(&SamDesc, m_pSamplerState.GetAddressOf());
	if (utility::checkError(result, "テクスチャー用サンプラー作成失敗"))return false;

	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	result = device->CreateBuffer(&cb, NULL, m_pConstantBuffer.GetAddressOf());
	if (utility::checkError(result, "コンスタントバッファー作成失敗"))return false;

	return true;
}