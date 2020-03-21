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

void PolygonRenderer::begin()
{
	//初期化
}

void PolygonRenderer::end()
{
	setInfo();
	drawPolygon();
}

void PolygonRenderer::draw()
{
	if (m_meshComponents.empty()) return;
	//sortの仕方見直したほうが良い
	std::sort(m_meshComponents.begin(), m_meshComponents.end(),
		[](std::weak_ptr<MeshComponent> x, std::weak_ptr<MeshComponent> y) -> bool
	{
		return x.lock()->getVertices()[0].pos.z > y.lock()->getVertices()[0].pos.z;
	});
	setInfo();
	auto deviceContext = D3d11::DeviceContext();
	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
	D3D11_MAPPED_SUBRESOURCE mappedIndexBuffer;

	deviceContext->Map(m_vertexBuffer.Get(), 0, mapType, 0, &mappedVertexBuffer);
	deviceContext->Map(m_indexBuffer.Get(), 0, mapType, 0, &mappedIndexBuffer);
	auto vertices = static_cast<SimpleVertex*>(mappedVertexBuffer.pData);
	auto indexes = static_cast<unsigned short*>(mappedIndexBuffer.pData);

	for(const auto& x : m_meshComponents)
	{
		auto meshVertices = x.lock()->getVertices();
		for (unsigned int i = 0; i < meshVertices.size(); i++)
		{
			vertices[m_vertexBufferPos + i] = meshVertices[i];
		}

		auto meshIndexes = x.lock()->getIndexes();
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

void PolygonRenderer::drawTriangle(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
	PolygonInfo info;
	info.polygonMesh = PolygonMesh::Triangle;
	info.position = position;
	info.scale = scale;
	info.color = color;
	info.orgin = orgin;
	info.angle = angle;
	info.vertexCount = 3;
	m_drawPolygons.emplace_back(info);
}

void PolygonRenderer::drawSquare(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
	PolygonInfo info;
	info.polygonMesh = PolygonMesh::Square;
	info.position = position;
	info.scale = scale;
	info.color = color;
	info.orgin = orgin;
	info.angle = angle;
	info.vertexCount = 4;
	m_drawPolygons.emplace_back(info);
}

void PolygonRenderer::drawPentagon(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
	PolygonInfo info;
	info.polygonMesh = PolygonMesh::Pentagon;
	info.position = position;
	info.scale = scale;
	info.color = color;
	info.orgin = orgin;
	info.angle = angle;
	info.vertexCount = 5;
	m_drawPolygons.emplace_back(info);
}

void PolygonRenderer::drawHexagon(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
	PolygonInfo info;
	info.polygonMesh = PolygonMesh::Hexagon;
	info.position = position;
	info.scale = scale;
	info.color = color;
	info.orgin = orgin;
	info.angle = angle;
	info.vertexCount = 6;
	m_drawPolygons.emplace_back(info);
}

void PolygonRenderer::drawCircle(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle, unsigned int vertexCount)
{
	PolygonInfo info;
	info.polygonMesh = PolygonMesh::Circle;
	info.position = position;
	info.scale = scale;
	info.color = color;
	info.orgin = orgin;
	info.angle = angle;
	info.vertexCount = vertexCount;
	m_drawPolygons.emplace_back(info);
}

void PolygonRenderer::drawLine(const std::vector<SimpleVertex>& vertices, float width, bool isLoop, float cornerVertices, float endCapVertices)
{
	//頂点を複数指定する場合はNoneをうまく使いたい
	//setPolygonInfoで何とかしたい
}

void PolygonRenderer::drawPolygon(const std::vector<SimpleVertex>& vertices)
{
	//頂点を複数指定する場合はNoneをうまく使いたい
}

std::vector<XMFLOAT2> PolygonRenderer::regularPolygonVertices(float radius, unsigned int count)
{
	std::vector<XMFLOAT2> res;
	float angle = 2 * mathf::PI / count;
	for (unsigned int i = 0; i < count; i++)
	{
		auto x = mathf::Sin(i * angle) * radius;
		auto y = mathf::Cos(i * angle) * radius;
		res.emplace_back(XMFLOAT2(x, y));
	}
	return res;
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

void PolygonRenderer::sortPolygons()
{
	growSortPolygons();
	//infoのzソート
	std::sort(m_sortPolygons.begin(), m_sortPolygons.end(),
		[](PolygonInfo const* x, PolygonInfo const* y) -> bool
	{
		return x->position.z > y->position.z;
	});
}

void PolygonRenderer::growSortPolygons()
{
	unsigned int size = m_drawPolygons.size();
	m_sortPolygons.resize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		m_sortPolygons[i] = &m_drawPolygons[i];
	}
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

void PolygonRenderer::drawPolygon()
{
	sortPolygons();

	auto deviceContext = D3d11::DeviceContext();
	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
	D3D11_MAPPED_SUBRESOURCE mappedIndexBuffer;

	deviceContext->Map(m_vertexBuffer.Get(), 0, mapType, 0, &mappedVertexBuffer);
	deviceContext->Map(m_indexBuffer.Get(), 0, mapType, 0, &mappedIndexBuffer);
	auto vertices = static_cast<SimpleVertex*>(mappedVertexBuffer.pData);
	auto indexes = static_cast<unsigned short*>(mappedIndexBuffer.pData);
	for (const auto& x : m_sortPolygons)
	{
		switch (x->polygonMesh)
		{
		case None:
			break;
		case Triangle:
			setTriangleInfo(x, vertices, indexes);
			break;
		case Square:
			setSquareInfo(x, vertices, indexes);
			break;
		case Pentagon:
			setPentagonInfo(x, vertices, indexes);
			break;
		case Hexagon:
			setHexagonInfo(x, vertices, indexes);
			break;
		case Circle:
			setCircleInfo(x, vertices, indexes);
			break;
		default:
			break;
		}
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	utility::DebugLog("x : " + std::to_string(vertices[i].pos.x) + " y : " + std::to_string(vertices[i].pos.y) + " z : " + std::to_string(vertices[i].pos.z));
	//}
	//for (int i = 0; i < 6; i++)
	//{
	//	utility::DebugLog(std::to_string(indexes[i]));
	//}
	deviceContext->Unmap(m_indexBuffer.Get(), 0);
	deviceContext->Unmap(m_vertexBuffer.Get(), 0);

	/*deviceContext->Map(m_vertexBuffer.Get(), 0, mapType, 0, &mappedVertexBuffer);
	auto vertices = static_cast<SimpleVertex*>(mappedVertexBuffer.pData);
	for (const auto& x : m_sortPolygons)
	{
		switch (x->polygonMesh)
		{
		case None:
			break;
		case Triangle:
			setTriangleInfo(x, vertices);
			break;
		case Square:
			break;
		case Pentagon:
			break;
		case Hexagon:
			break;
		case Circle:
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		utility::DebugLog("x : " + std::to_string(vertices[i].pos.x) + " y : " + std::to_string(vertices[i].pos.y) + " z : " + std::to_string(vertices[i].pos.z));
	}
	deviceContext->Unmap(m_vertexBuffer.Get(), 0);

	deviceContext->Map(m_indexBuffer.Get(), 0, mapType, 0, &mappedIndexBuffer);
	auto indexes = static_cast<unsigned short*>(mappedIndexBuffer.pData);
	for (const auto& x : m_sortPolygons)
	{
		switch (x->polygonMesh)
		{
		case None:
			break;
		case Triangle:
			setIndex(indexes, 3);
			m_vertexBufferPos += 3;
			break;
		case Square:
			break;
		case Pentagon:
			break;
		case Hexagon:
			break;
		case Circle:
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		utility::DebugLog(std::to_string(indexes[i]));
	}
	deviceContext->Unmap(m_indexBuffer.Get(), 0);*/

	//auto startIndex = static_cast<UINT>(m_vertexBufferPos);
	auto indexCount = static_cast<UINT>(m_indexBufferPos);

	deviceContext->DrawIndexed(indexCount, 0, 0);

	m_vertexBufferPos = 0;
	m_indexBufferPos = 0;
	m_drawPolygons.clear();
	m_sortPolygons.clear();
}

void PolygonRenderer::setTriangleInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes)
{
	//short count = 3;
	//int l = 1;
	//float h = mathf::Sqrt(l * l - (l / 2.0) * (l / 2.0));

	//vertices[m_vertexBufferPos].pos = XMFLOAT3(l / 2.0, -h * 1.0 / 3.0, 0);
	//vertices[m_vertexBufferPos + 1].pos = XMFLOAT3(0, h * 2.0 / 3.0, 0);
	//vertices[m_vertexBufferPos + 2].pos = XMFLOAT3(- l / 2.0, vertices[m_vertexBufferPos].pos.y, 0);
	short count = info->vertexCount;
	std::vector<XMFLOAT2> polygonVertices = regularPolygonVertices(0.5f, count);
	for (unsigned int i = 0; i < count; i++)
	{
		vertices[m_vertexBufferPos + i].pos = XMFLOAT3(polygonVertices[i].x, polygonVertices[i].y, 0);
	}
	setWorldMatrix(info, vertices, count);
	setIndex(indexes, count, false);
	m_vertexBufferPos += count;
}

void PolygonRenderer::setSquareInfo(PolygonInfo * info, SimpleVertex * vertices, unsigned short * indexes)
{
	short count = info->vertexCount;
	float l = 0.5f;
	vertices[m_vertexBufferPos].pos = XMFLOAT3(-l, -l, 0);
	vertices[m_vertexBufferPos + 1].pos = XMFLOAT3(-l, l, 0);
	vertices[m_vertexBufferPos + 2].pos = XMFLOAT3(l, -l, 0);
	vertices[m_vertexBufferPos + 3].pos = XMFLOAT3(l, l, 0);
	setWorldMatrix(info, vertices, count);
	setIndex(indexes, count);
	m_vertexBufferPos += count;
}

void PolygonRenderer::setPentagonInfo(PolygonInfo * info, SimpleVertex * vertices, unsigned short * indexes)
{
	short count = info->vertexCount;
	std::vector<XMFLOAT2> polygonVertices = regularPolygonVertices(0.5f, count);
	for (unsigned int i = 0; i < count; i++)
	{
		vertices[m_vertexBufferPos + i].pos = XMFLOAT3(polygonVertices[i].x, polygonVertices[i].y, 0);
	}
	setWorldMatrix(info, vertices, count);
	setIndex(indexes, count, false);
	m_vertexBufferPos += count;
}

void PolygonRenderer::setHexagonInfo(PolygonInfo * info, SimpleVertex * vertices, unsigned short * indexes)
{
	short count = info->vertexCount;
	std::vector<XMFLOAT2> polygonVertices = regularPolygonVertices(0.5f, count);
	for (unsigned int i = 0; i < count; i++)
	{
		vertices[m_vertexBufferPos + i].pos = XMFLOAT3(polygonVertices[i].x, polygonVertices[i].y, 0);
	}
	setWorldMatrix(info, vertices, count);
	setIndex(indexes, count, false);
	m_vertexBufferPos += count;
}

void PolygonRenderer::setCircleInfo(PolygonInfo * info, SimpleVertex * vertices, unsigned short * indexes)
{
	short count = info->vertexCount;
	std::vector<XMFLOAT2> polygonVertices = regularPolygonVertices(0.5f, count);
	for (unsigned int i = 0; i < count; i++)
	{
		vertices[m_vertexBufferPos + i].pos = XMFLOAT3(polygonVertices[i].x, polygonVertices[i].y, 0);
	}
	setWorldMatrix(info, vertices, count);
	setIndex(indexes, count, false);
	m_vertexBufferPos += count;
}

void PolygonRenderer::setWorldMatrix(PolygonInfo* info, SimpleVertex* vertices, unsigned int count)
{
	XMMATRIX scale = DirectX::XMMatrixScaling(info->scale.x, info->scale.y, 1.0f);
	XMMATRIX beginTranslation = DirectX::XMMatrixTranslation(-info->orgin.x, -info->orgin.y, 0);
	XMMATRIX rotate = DirectX::XMMatrixRotationZ(info->angle);
	XMMATRIX endTranslation = DirectX::XMMatrixTranslation(info->orgin.x, info->orgin.y, 0);
	XMMATRIX translation = DirectX::XMMatrixTranslation(info->position.x, info->position.y, 0);
	XMMATRIX world = scale * beginTranslation * rotate * endTranslation * translation;

	for (unsigned int i = 0; i < count; i++)
	{
		XMStoreFloat3(&vertices[m_vertexBufferPos + i].pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertices[m_vertexBufferPos + i].pos), world));
		vertices[m_vertexBufferPos + i].color = info->color;
	}
}

void PolygonRenderer::setIndex(unsigned short* indexes, int count, bool isStrip)
{
	if (isStrip)
	{
		//012,123,234
		//for (int i = 0; i < count - 2; i++)
		//{
		//	indexes[m_indexBufferPos] = m_vertexBufferPos + i;
		//	indexes[m_indexBufferPos + 1] = m_vertexBufferPos + i + 1;
		//	indexes[m_indexBufferPos + 2] = m_vertexBufferPos + i + 2;
		//	m_indexBufferPos += 3;
		//}
		//012,132,234,354,456,576
		for (int i = 0; i < count - 2; i++)
		{
			indexes[m_indexBufferPos] = m_vertexBufferPos + i;
			if (i % 2 == 0)
			{
				indexes[m_indexBufferPos + 1] = m_vertexBufferPos + i + 1;
				indexes[m_indexBufferPos + 2] = m_vertexBufferPos + i + 2;
			}
			else
			{
				indexes[m_indexBufferPos + 1] = m_vertexBufferPos + i + 2;
				indexes[m_indexBufferPos + 2] = m_vertexBufferPos + i + 1;
			}
			m_indexBufferPos += 3;
		}
	}
	else
	{
		//012,023,034
		for (int i = 0; i < count - 2; i++)
		{
			indexes[m_indexBufferPos] = m_vertexBufferPos;
			indexes[m_indexBufferPos + 1] = m_vertexBufferPos + i + 1;
			indexes[m_indexBufferPos + 2] = m_vertexBufferPos + i + 2;
			m_indexBufferPos += 3;
		}
	}
}
