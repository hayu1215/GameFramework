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
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;

	HRESULT result = device->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (!utility::checkError(result, "DeviceContext��Map�̎��s"))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		//Matrix4Transpose(&wvp, &wvp);
		cb.mWVP = wvp;

		//�J���[��n��
		//Vector4 vColor(0, 0, 0, 1);
		//cb.vColor = vColor;

		//�����x��n��
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
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ComPtr<ID3DBlob> pCompiledShader;

	//result = D3DX11CompileFromFile(lpc, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, pCompiledShader.GetAddressOf(), NULL, NULL);
	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (utility::checkError(result, "hlsl�ǂݍ��ݎ��s"))return false;

	result = device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, m_pVertexShader.GetAddressOf());
	if (utility::checkError(result, "�o�[�e�b�N�X�V�F�[�_�[�쐬���s"))return false;

	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	result = device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	if (utility::checkError(result, "���_�C���v�b�g���C�A�E�g�쐬���s"))return false;

	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (utility::checkError(result, "hlsl�ǂݍ��ݎ��s"))return false;

	result = device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, m_pPixelShader.GetAddressOf());
	if (utility::checkError(result, "�s�N�Z���V�F�[�_�[�쐬���s"))return false;

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	result = device->CreateSamplerState(&SamDesc, m_pSamplerState.GetAddressOf());
	if (utility::checkError(result, "�e�N�X�`���[�p�T���v���[�쐬���s"))return false;

	//�R���X�^���g�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	result = device->CreateBuffer(&cb, NULL, m_pConstantBuffer.GetAddressOf());
	if (utility::checkError(result, "�R���X�^���g�o�b�t�@�[�쐬���s"))return false;

	return true;
}