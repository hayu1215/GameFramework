#include "TestShader.h"
#include<d3dcompiler.h>
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Utility/Debug/Log.h>

TestShader::TestShader()
{
}

TestShader::TestShader(const std::string& name)
{
	try
	{
		load(name);
	}
	catch (std::exception& e)
	{
		debug::Log(e.what());
	}
}

void TestShader::load(const std::string& name)
{
	auto device = D3d11::Device();

	std::string file = "Framework/Resource/Shader/" + name;
	std::wstring wname(file.begin(), file.end());
	ComPtr<ID3DBlob> pCompiledShader;

	auto result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (result < 0) throw std::runtime_error("Faild D3DCompileFromFile \"" + name + "\"");
	device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf());

	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "GS", "gs_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (result < 0) throw std::runtime_error("Faild D3DCompileFromFile \"" + name + "\"");
	device->CreateGeometryShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, m_geometryShader.GetAddressOf());

	result = D3DCompileFromFile(wname.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, pCompiledShader.GetAddressOf(), nullptr);
	if (result < 0) throw std::runtime_error("Faild D3DCompileFromFile \"" + name + "\"");
	device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), m_vertexLayout.GetAddressOf());
}
