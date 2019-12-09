#include "LineRenderer.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Utility/Constant.h>

LineRenderer::LineRenderer()
{
	createVertexBuffer2();
	createConstantBuffer2();
}

LineRenderer::LineRenderer(std::shared_ptr<Camera>camera)
	:m_pCamera(camera)
{
	createVertexBuffer2();
	createConstantBuffer2();
}

LineRenderer::~LineRenderer()
{
}

void LineRenderer::drawLine(const XMFLOAT3 & position1, const XMFLOAT3 & position2, const XMFLOAT4& color1, const XMFLOAT4& color2, float width)
{
	std::string shaderName = "LineShader.hlsl";
	auto deviceContext = D3d11::Instance().getDeviceContext();
	UINT stride = sizeof(LineVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(ResourceManager::Instance().findShader(shaderName)->getInputLayout().Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);
	deviceContext->GSSetShader(ResourceManager::Instance().findShader(shaderName)->getGeometryShader().Get(), nullptr, 0);
	deviceContext->VSSetShader(ResourceManager::Instance().findShader(shaderName)->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(ResourceManager::Instance().findShader(shaderName)->getPixelShader().Get(), nullptr, 0);
	deviceContext->GSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	deviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	deviceContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedBuffer;
	deviceContext->Map(m_pVertexBuffer.Get(), 0, mapType, 0, &mappedBuffer);
	auto vertices = static_cast<LineVertex*>(mappedBuffer.pData);

	vertices[0].pos = position1;
	vertices[0].color = color1;
	vertices[1].pos = position2;
	vertices[1].color = color2;

	deviceContext->Unmap(m_pVertexBuffer.Get(), 0);

	XMMATRIX mView = m_pCamera.lock()->getView();
	XMMATRIX mProj = {
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	D3D11_MAPPED_SUBRESOURCE pData;
	LineCBuffer cb;
	HRESULT result = deviceContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (!utility::checkError(result, "DeviceContext‚ÌMap‚ÌŽ¸”s"))
	{
		XMMATRIX m = XMMatrixMultiplyTranspose(mView, mProj);
		XMStoreFloat4x4(&cb.wvp,m);
		cb.width.x = width;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		deviceContext->Unmap(m_pConstantBuffer.Get(), 0);
	}

	D3d11::Instance().getDeviceContext()->Draw(2, 0);
}

void LineRenderer::drawLine(const std::string& name,const std::vector<XMFLOAT3>& vertexes, const std::vector<XMFLOAT4>& clors, float width)
{
	std::string shaderName = name;
	auto deviceContext = D3d11::Instance().getDeviceContext();
	UINT stride = sizeof(LineVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(ResourceManager::Instance().findShader(shaderName)->getInputLayout().Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	deviceContext->GSSetShader(ResourceManager::Instance().findShader(shaderName)->getGeometryShader().Get(), nullptr, 0);
	deviceContext->VSSetShader(ResourceManager::Instance().findShader(shaderName)->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(ResourceManager::Instance().findShader(shaderName)->getPixelShader().Get(), nullptr, 0);
	deviceContext->GSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	deviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	deviceContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedBuffer;
	deviceContext->Map(m_pVertexBuffer.Get(), 0, mapType, 0, &mappedBuffer);
	auto vertices = static_cast<LineVertex*>(mappedBuffer.pData);

	for (int i = 0; i < vertexes.size(); i++) {
		vertices[i].pos = vertexes[i];
		vertices[i].color = clors[i];
	}

	deviceContext->Unmap(m_pVertexBuffer.Get(), 0);

	XMMATRIX mView = m_pCamera.lock()->getView();
	XMMATRIX mProj = {
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	D3D11_MAPPED_SUBRESOURCE pData;
	LineCBuffer cb;
	HRESULT result = deviceContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (!utility::checkError(result, "DeviceContext‚ÌMap‚ÌŽ¸”s"))
	{
		XMMATRIX m = XMMatrixMultiplyTranspose(mView, mProj);
		XMStoreFloat4x4(&cb.wvp, m);
		cb.width.x = width;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		deviceContext->Unmap(m_pConstantBuffer.Get(), 0);
	}

	D3d11::Instance().getDeviceContext()->Draw(vertexes.size(), 0);
}

void LineRenderer::createVertexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(LineVertex) * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	D3d11::Instance().getDevice()->CreateBuffer(&bd, nullptr, m_pVertexBuffer.GetAddressOf());
}

void LineRenderer::createConstantBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(LineCBuffer);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3d11::Instance().getDevice()->CreateBuffer(&bd, nullptr, m_pConstantBuffer.GetAddressOf());
}

void LineRenderer::createVertexBuffer2()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(LineVertex) * 100;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	D3d11::Instance().getDevice()->CreateBuffer(&bd, nullptr, m_pVertexBuffer.GetAddressOf());
}

void LineRenderer::createConstantBuffer2()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(LineCBuffer);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3d11::Instance().getDevice()->CreateBuffer(&bd, nullptr, m_pConstantBuffer.GetAddressOf());
}
