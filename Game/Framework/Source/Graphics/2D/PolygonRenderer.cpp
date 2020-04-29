#include "PolygonRenderer.h"
#include<algorithm>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Component/CameraComponent.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include<Framework/Source/Utility/Math/Mathf.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>

PolygonRenderer::PolygonRenderer()
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
}

PolygonRenderer::~PolygonRenderer()
{
}

void PolygonRenderer::update()
{
	draw();
}

void PolygonRenderer::draw()
{
	std::vector<Mesh> meshes = m_meshes;
	for (const auto& x : m_meshComponents)
	{
		meshes.emplace_back(x.lock()->mesh());
	}

	if (meshes.empty()) return;
	std::sort(meshes.begin(), meshes.end(), [](Mesh x, Mesh y) -> bool
	{
		return x.vertices[0].pos.z > y.vertices[0].pos.z;
	});

	//if (m_meshComponents.empty()) return;
	////sortの仕方見直したほうが良い
	//std::sort(m_meshComponents.begin(), m_meshComponents.end(),
	//	[](std::weak_ptr<MeshComponent> x, std::weak_ptr<MeshComponent> y) -> bool
	//{
	//	return x.lock()->getVertices()[0].pos.z > y.lock()->getVertices()[0].pos.z;
	//});
	setInfo();
	auto deviceContext = D3d11::DeviceContext();
	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
	D3D11_MAPPED_SUBRESOURCE mappedIndexBuffer;

	deviceContext->Map(m_vertexBuffer.Get(), 0, mapType, 0, &mappedVertexBuffer);
	deviceContext->Map(m_indexBuffer.Get(), 0, mapType, 0, &mappedIndexBuffer);
	auto vertices = static_cast<SimpleVertex*>(mappedVertexBuffer.pData);
	auto indexes = static_cast<unsigned short*>(mappedIndexBuffer.pData);

	for(const auto& x : meshes)
	{
		auto meshVertices = x.vertices;
		for (unsigned int i = 0; i < meshVertices.size(); i++)
		{
			vertices[m_vertexBufferPos + i] = meshVertices[i];
		}

		auto meshIndexes = x.indexes;
		for (unsigned int i = 0; i < meshIndexes.size(); i++)
		{
			indexes[m_indexBufferPos + i] = meshIndexes[i] + m_vertexBufferPos;
		}
		m_vertexBufferPos += meshVertices.size();
		m_indexBufferPos += meshIndexes.size();
	}

	deviceContext->Unmap(m_indexBuffer.Get(), 0);
	deviceContext->Unmap(m_vertexBuffer.Get(), 0);
	auto indexCount = static_cast<UINT>(m_indexBufferPos);
	deviceContext->DrawIndexed(indexCount, 0, 0);
	m_vertexBufferPos = 0;
	m_indexBufferPos = 0;
	m_meshComponents.clear();
}

void PolygonRenderer::addMeshComponent(const std::weak_ptr<MeshComponent>& component)
{
	m_meshComponents.emplace_back(component);
}

void PolygonRenderer::addMesh(const Mesh& mesh)
{
	m_meshes.emplace_back(mesh);
}

void PolygonRenderer::createVertexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(SimpleVertex) * MAX_SIZE;//とりあえずテキトー
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_vertexBuffer.GetAddressOf());
	utility::CheckError(result, "バーテックスバッファーの作成失敗");
}

void PolygonRenderer::createIndexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * MAX_SIZE;//とりあえずテキトー
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_indexBuffer.GetAddressOf());
	utility::CheckError(result, "インデックスバッファーの作成失敗");
}

void PolygonRenderer::createConstantBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = sizeof(SimpleConstantBuffer);
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_constantBuffer.GetAddressOf());
	if (utility::CheckError(result, "コンスタントバッファー作成失敗"));

	XMMATRIX view = CameraComponent::GetMainCamera().lock()->getView();
	XMMATRIX proj = DirectX::XMMatrixSet(
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	SimpleConstantBuffer cb;
	XMStoreFloat4x4(&cb.matrix, DirectX::XMMatrixMultiplyTranspose(view, proj));
	D3d11::DeviceContext()->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

void PolygonRenderer::setInfo()
{
	std::string shaderName = "PolygonShader.hlsl";
	auto deviceContext = D3d11::DeviceContext();
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetInputLayout(ResourceManager::FindShader(shaderName)->getInputLayout().Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->VSSetShader(ResourceManager::FindShader(shaderName)->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(ResourceManager::FindShader(shaderName)->getPixelShader().Get(), nullptr, 0);
	deviceContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	deviceContext->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
}