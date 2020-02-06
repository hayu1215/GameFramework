#include "PolygonRenderer.h"
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Component/CameraComponent.h>
#include<Framework/Source/Utility/Math/Mathf.h>

PolygonRenderer::PolygonRenderer()
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
}

PolygonRenderer::~PolygonRenderer()
{
}

void PolygonRenderer::begin()
{
	//初期化
}

void PolygonRenderer::end()
{
	//描画
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
	m_DrawPolygons.emplace_back(info);
}

void PolygonRenderer::drawSquare(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
}

void PolygonRenderer::drawPentagon(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
}

void PolygonRenderer::drawHexagon(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
}

void PolygonRenderer::drawCircle(const XMFLOAT3 & position, const XMFLOAT2 & scale, const XMFLOAT4 & color, const XMFLOAT2 & orgin, float angle)
{
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

void PolygonRenderer::createVertexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(SimpleVertex) * MAX_SIZE;//とりあえずテキトー
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_pVertexBuffer.GetAddressOf());
	utility::checkError(result, "バーテックスバッファーの作成失敗");
}

void PolygonRenderer::createIndexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(short) * MAX_SIZE;//とりあえずテキトー
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_pIndexBuffer.GetAddressOf());
	utility::checkError(result, "インデックスバッファーの作成失敗");
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

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_pConstantBuffer.GetAddressOf());
	if (utility::checkError(result, "コンスタントバッファー作成失敗"));

	XMMATRIX view = CameraComponent::GetMainCamera().lock()->getView();
	XMMATRIX proj = DirectX::XMMatrixSet(
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	SimpleConstantBuffer cb;
	XMStoreFloat4x4(&cb.matrix, DirectX::XMMatrixMultiplyTranspose(view, proj));
	D3d11::DeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

void PolygonRenderer::sortPolygons()
{
	//infoのzソート
}

void PolygonRenderer::setPolygonInfo()
{
	auto deviceContext = D3d11::DeviceContext();
	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
	D3D11_MAPPED_SUBRESOURCE mappedVertexBuffer;
	D3D11_MAPPED_SUBRESOURCE mappedIndexBuffer;

	deviceContext->Map(m_pVertexBuffer.Get(), 0, mapType, 0, &mappedVertexBuffer);
	deviceContext->Map(m_pIndexBuffer.Get(), 0, mapType, 0, &mappedIndexBuffer);
	auto vertices = static_cast<SimpleVertex*>(mappedVertexBuffer.pData);
	auto indexes = static_cast<int*>(mappedIndexBuffer.pData);

	for (const auto& x : m_SortPolygons)
	{
		switch (x->polygonMesh)
		{
		case None:
			break;
		case Triangle:
			setTriangleInfo(x, vertices, indexes);
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
	deviceContext->Unmap(m_pIndexBuffer.Get(), 0);
	deviceContext->Unmap(m_pVertexBuffer.Get(), 0);
}

void PolygonRenderer::setTriangleInfo(PolygonInfo* info, SimpleVertex* vertices, int* indexes)
{
	short count = 3;
	int l = 1;
	float h = mathf::sqrt(l * l - (l / 2.0) * (l / 2.0));
	vertices[m_VertexBufferPos].pos = XMFLOAT3(info->position.x, info->position.y - h * 2.0 / 3.0, 0);
	vertices[m_VertexBufferPos + 1].pos = XMFLOAT3(info->position.x + l / 2.0, info->position.y + h * 1.0 / 3.0, 0);
	vertices[m_VertexBufferPos + 2].pos = XMFLOAT3(info->position.x - l / 2.0, vertices[1].pos.y, 0);
	setWorldMatrix(info, vertices);
	setIndex(indexes, count);
	m_VertexBufferPos += count;
}

void PolygonRenderer::setWorldMatrix(PolygonInfo* info, SimpleVertex* vertices)
{
	XMMATRIX scale = DirectX::XMMatrixScaling(info->scale.x, info->scale.y, 1.0f);
	XMMATRIX beginTranslation = DirectX::XMMatrixTranslation(-info->orgin.x, -info->orgin.y, 0);
	XMMATRIX rotate = DirectX::XMMatrixRotationZ(info->angle);
	XMMATRIX endTranslation = DirectX::XMMatrixTranslation(info->orgin.x, info->orgin.y, 0);
	XMMATRIX translation = DirectX::XMMatrixTranslation(info->position.x, info->position.y, 0);
	XMMATRIX world = scale * beginTranslation * rotate * endTranslation * translation;

	for (unsigned int i = 0; i < info->polygonMesh; i++)
	{
		XMStoreFloat3(&vertices[i].pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertices[i].pos), world));
		vertices[i].color = info->color;
	}
}

void PolygonRenderer::setIndex(int* indexes, int count)
{
	for (int i = 0; i < count - 2; i++) 
	{
		indexes[m_VertexBufferPos + i] = m_VertexBufferPos;
		indexes[m_VertexBufferPos + i + 1] = m_VertexBufferPos + i + 1;
		indexes[m_VertexBufferPos + i + 2] = m_VertexBufferPos + i + 2;
	}
	//頂点バッファの書きかえってmap使わないとできないのかな、
	//d3dにセットする前だったら書き換えられるのか？
	//頂点バッファの扱いがいまいちわからなくなった、
	//頂点バッファって複数登録できたりするのかな、
}
