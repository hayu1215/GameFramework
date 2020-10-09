#include "PolygonRenderer.h"
#include<algorithm>
#include<array>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Component/CameraComponent.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include<Framework/Source/Component/Graphics/ModelComponent.h>
#include<Framework/Source/Utility/Math/Mathf.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Graphics/3D/Model.h>
#include<Framework/Source/Graphics/3D/Material.h>

PolygonRenderer::PolygonRenderer()
{
	createConstantBuffer();
	createOffsetBuffer();
	setInfo();
}

PolygonRenderer::~PolygonRenderer()
{
}

void PolygonRenderer::update()
{
	viewUpdate();
	draw();
}

void PolygonRenderer::addModelComponent(const std::weak_ptr<ModelComponent>& component)
{
	m_modelComponents[component.lock()->getName()].emplace_back(component);
}

void PolygonRenderer::draw()
{
	for (const auto& x : m_modelComponents)
	{
		ComPtr<ID3D11Buffer> vertexBuffer;
		ComPtr<ID3D11Buffer> indexBuffer;
		unsigned int indexCount;
		if (auto com = x.second[0].lock())
		{
			auto model = com->getModel().lock();
#ifdef _DEBUG
			if (!model)
			{
				debug::Log(com->getName() + "is expired");
				assert(false && "Failed PolygonRenderer::newdraw");
			}
#endif
			vertexBuffer = model->getVertexBuffer();
			indexBuffer = model->getIndexBuffer();
			indexCount = model->getIndexCount();
		}
		else
		{
			continue;
		}

		std::vector<DrawInstance> instances;
		for (const auto& y : x.second)
		{
			DrawInstance di;
			if (auto com = y.lock())
			{
				auto material = com->getMaterial().lock();
#ifdef _DEBUG
				if (!material)
				{
					debug::Log(com->getName() + "is expired");
					assert(false && "Failed PolygonRenderer::newdraw");
				}
#endif
				di.color = material->getColor();
			}
			if (auto entity = y.lock()->getEntity().lock())
			{
				di.position = entity->position();
				di.rotate = entity->rotate();
				di.scale = entity->scale();
			}
			instances.push_back(di);
		}

		//updatesubresource更新
		//D3d11::DeviceContext()->UpdateSubresource(m_offsetBuffer.Get(), 0, 0, instances.data(), 0, 0);
		
		//map unmap更新
		D3D11_MAPPED_SUBRESOURCE mb;
		D3d11::DeviceContext()->Map(m_offsetBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mb);
		memcpy(mb.pData, instances.data(), sizeof(DrawInstance) * instances.size());
		D3d11::DeviceContext()->Unmap(m_offsetBuffer.Get(), 0);

		std::array<ID3D11Buffer*, 2> offsetBuffers = { vertexBuffer.Get(), m_offsetBuffer.Get() };
		std::array<UINT, 2> strides = { sizeof(ObjVertex), sizeof(DrawInstance) };
		std::array<UINT, 2> offsets = { 0, 0 };
		D3d11::DeviceContext()->IASetVertexBuffers(0, static_cast<UINT>(offsetBuffers.size()), offsetBuffers.data(), strides.data(), offsets.data());
		D3d11::DeviceContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		D3d11::DeviceContext()->DrawIndexedInstanced(indexCount, instances.size(), 0, 0, 0);
	}

	m_modelComponents.clear();
}

void PolygonRenderer::viewUpdate()
{
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

void PolygonRenderer::createOffsetBuffer()
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(DrawInstance) * ELEMENTS_NUM;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA initData;
	//initData.pSysMem = m_instances.data();
	//initData.SysMemPitch = desc.ByteWidth;
	HRESULT result = D3d11::Device()->CreateBuffer(&desc, nullptr, m_offsetBuffer.GetAddressOf());
	utility::CheckError(result, "インスタンス描画用のオフセットバッファの作成に失敗");
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
}

void PolygonRenderer::setInfo()
{
	std::string shaderName = "PolygonShader.hlsl";
	auto deviceContext = D3d11::DeviceContext();
	auto shader = ResourceManager::GetShader(shaderName).lock();
#ifdef _DEBUG
	if (!shader)
	{
		debug::Log(shaderName + "is expired");
		assert(false && "Failed PolygonRenderer::newsetInfo");
	}
#endif
	deviceContext->IASetInputLayout(shader->getInputLayout().Get());
	deviceContext->VSSetShader(shader->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(shader->getPixelShader().Get(), nullptr, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	//deviceContext->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
}
