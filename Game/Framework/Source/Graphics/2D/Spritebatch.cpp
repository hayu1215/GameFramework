#include "Spritebatch.h"
#include<algorithm>
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Utility/Constant.h>

Spritebatch::Spritebatch()
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
	createSamplerState();
}

Spritebatch::Spritebatch(std::shared_ptr<Camera>camera)
	:m_pCamera(camera)
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
	createSamplerState();
}

Spritebatch::~Spritebatch()
{
}

void Spritebatch::begin()
{
	m_SortMode = SortMode::BackToFront;
}

void Spritebatch::begin(const SortMode & sortMode)
{
	m_SortMode = sortMode;
}

void Spritebatch::end(const std::string& shaderName)
{
	setInfo(shaderName);
	flushBatch();
}

void Spritebatch::draw(std::string textureName, XMFLOAT3 position, XMFLOAT2 scale, float angle, XMFLOAT2 orgin, XMFLOAT4 uv, XMFLOAT4 color)
{
	TextureInfo info;
	info.textureName = textureName;
	info.position = position;
	info.scale = scale;
	info.angle = angle;
	info.orgin = orgin;
	info.uv = uv;
	info.color = color;
	m_DrawTextures.push_back(info);
}

void Spritebatch::createVertexBuffer()
{
	//バーテックスバッファーの宣言
	D3D11_BUFFER_DESC bd;

	//バーテックスバッファーの定義
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(TextureVertex) * MAX_BATCH_SIZE * VERTICES_SPRITE;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_pVertexBuffer.GetAddressOf());
	utility::checkError(result, "バーテックスバッファーの作成失敗");
}

void Spritebatch::createIndexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(short) * MAX_BATCH_SIZE * INDICES_SPRITE;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	//bd.StructureByteStride = 0;

	auto indexValues = createIndexValue();//直接書いてもよさそうだけどとりあえずこれ

	D3D11_SUBRESOURCE_DATA indexDataDesc;
	indexDataDesc.pSysMem = indexValues.data();
	//indexDataDesc.SysMemPitch = 0;
	//indexDataDesc.SysMemSlicePitch = 0;
	HRESULT result = D3d11::Device()->CreateBuffer(&bd, &indexDataDesc, m_pIndexBuffer.GetAddressOf());
	utility::checkError(result, "インデックスバッファーの作成失敗");

	//D3d11::Device()->CreateBuffer(&bd, nullptr, m_pIndexBuffer.GetAddressOf());
	//D3d11::DeviceContext()->UpdateSubresource(m_pIndexBuffer.Get(), 0, nullptr, indexValues.data(), 0, 0);
}

void Spritebatch::createConstantBuffer()
{
	//コンスタントバッファー作成
	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = sizeof(SimpleConstantBuffer);
	bd.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT result = D3d11::Device()->CreateBuffer(&bd, nullptr, m_pConstantBuffer.GetAddressOf());
	if (utility::checkError(result, "コンスタントバッファー作成失敗"));

	//やり方あってるかはわからん、コンスタントバッファの初期値の設定
	XMMATRIX view = m_pCamera.lock()->getView();
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

void Spritebatch::createSamplerState()
{
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	D3d11::Device()->CreateSamplerState(&SamDesc, m_pSamplerState.GetAddressOf());
}

std::vector<short> Spritebatch::createIndexValue()
{
	std::vector<short> indices;

	indices.reserve(MAX_BATCH_SIZE * INDICES_SPRITE);

	for (size_t j = 0; j < MAX_BATCH_SIZE * VERTICES_SPRITE; j += VERTICES_SPRITE)
	{
		short i = static_cast<short>(j);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}

	return indices;
}

void Spritebatch::setInfo(const std::string& shaderName)
{
	auto deviceContext = D3d11::DeviceContext();

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点インプットレイアウトをセット
	deviceContext->IASetInputLayout(ResourceManager::FindShader(shaderName)->getInputLayout().Get());

	//使用するシェーダーの登録
	deviceContext->VSSetShader(ResourceManager::FindShader(shaderName)->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(ResourceManager::FindShader(shaderName)->getPixelShader().Get(), nullptr, 0);

	//コンスタントバッファに関しては違う処理が必要かも
	deviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	//deviceContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

	deviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

	//バーテックスバッファーをセット
	UINT stride = sizeof(TextureVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	//インデックスバッファをセット
	deviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	//理由まだ調べてない
	if (deviceContext->GetType() == D3D11_DEVICE_CONTEXT_DEFERRED)
	{
		m_VertexBufferPos = 0;
	}

	//カスタムシェーダよぶならここ
}

void Spritebatch::flushBatch()
{
	if (m_DrawTextures.empty())return;
	sortSprites();
	std::string batchTextureName = "";
	unsigned int batchStart = 0;
	auto a = m_DrawTextures.size();

	//一週目素通り　もう少しきれいなループにしたい、
	for (unsigned int i = 0; i < m_DrawTextures.size(); i++)
	{
		std::string textureName = m_SortTextures[i]->textureName;

		if (textureName != batchTextureName)
		{
			if (i > batchStart)
			{
				renderBatch(&m_SortTextures[batchStart], i - batchStart);
			}

			batchTextureName = textureName;
			batchStart = i;
		}
	}

	renderBatch(&m_SortTextures[batchStart], m_DrawTextures.size() - batchStart);

	m_DrawTextures.clear();
	m_SortTextures.clear();
}

void Spritebatch::sortSprites()
{
	growSortSprites();

	switch (m_SortMode)
	{
	case SortMode::Texture:
		std::sort(m_SortTextures.begin(), m_SortTextures.end(),
			[](TextureInfo const* x, TextureInfo const* y) -> bool
			{
				return x->textureName < y->textureName;
			});
		break;

	case SortMode::BackToFront:
		std::sort(m_SortTextures.begin(), m_SortTextures.end(),
			[](TextureInfo const* x, TextureInfo const* y) -> bool
		{
			return x->position.z > y->position.z;
		});
		break;

	case SortMode::FrontToBack:
		std::sort(m_SortTextures.begin(), m_SortTextures.end(),
			[](TextureInfo const* x, TextureInfo const* y) -> bool
		{
			return x->position.z < y->position.z;
		});
		break;

	default:
		break;
	}
}

void Spritebatch::growSortSprites()
{
	unsigned int size = m_DrawTextures.size();
	m_SortTextures.resize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		m_SortTextures[i] = &m_DrawTextures[i];
	}
}

void Spritebatch::renderBatch(TextureInfo** info, size_t count)
{
	ID3D11ShaderResourceView* texture = ResourceManager::FindTexture((*info)->textureName)->getShaderResourceView().Get();
	auto deviceContext = D3d11::DeviceContext();
	deviceContext->PSSetShaderResources(0, 1, &texture);

	while (count > 0)
	{
		//vertexBufferPosition調べる
		unsigned int batchSize = count;

		unsigned int remainingSpace = MAX_BATCH_SIZE - m_VertexBufferPos;

		XMFLOAT2 textureSize = ResourceManager::FindTexture((*info)->textureName)->getSize();

		if (batchSize > remainingSpace)
		{
			if (remainingSpace < MIN_BATCH_SIZE)
			{
				//余裕がない場合、または過度に小さいバッチを送信しようとしている場合は、頂点バッファの先頭に戻ります。
				m_VertexBufferPos = 0;

				batchSize = std::min<unsigned int>(count, MAX_BATCH_SIZE);
			}
			else
			{
				batchSize = remainingSpace;
			}
		}


		D3D11_MAP mapType = (m_VertexBufferPos == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		//D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;

		D3D11_MAPPED_SUBRESOURCE mappedBuffer;

		deviceContext->Map(m_pVertexBuffer.Get(), 0, mapType, 0, &mappedBuffer);

		auto vertices = static_cast<TextureVertex*>(mappedBuffer.pData) + m_VertexBufferPos * VERTICES_SPRITE;

		for (unsigned int i = 0; i < batchSize; i++)
		{
			renderSprite(info[i], vertices, textureSize);
			vertices += VERTICES_SPRITE;
		}

		deviceContext->Unmap(m_pVertexBuffer.Get(), 0);

		//コンスタントバッファ
		//D3D11_MAPPED_SUBRESOURCE pData;
		//SimpleConstantBuffer cb;

		//HRESULT result = deviceContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		//if (!utility::checkError(result, "DeviceContextのMapの失敗"))
		//{
		//	XMFLOAT4X4 view = XMFLOAT4X4::identity;

		//	XMFLOAT4X4 proj = {
		//		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		//		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		//		0.0f, 0.0f, 1.0f, 0.0f,
		//		0.0f, 0.0f, 0.0f, 1.0f
		//	};

		//	cb.XMFLOAT4X4 = view * proj;
		//	memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		//	deviceContext->Unmap(m_pConstantBuffer.Get(), 0);
		//}

		auto startIndex = static_cast<UINT>(m_VertexBufferPos * INDICES_SPRITE);
		auto indexCount = static_cast<UINT>(batchSize * INDICES_SPRITE);

		deviceContext->DrawIndexed(indexCount, startIndex, 0);

		m_VertexBufferPos += batchSize;
		info += batchSize;
		count -= batchSize;
	}
}

void Spritebatch::renderSprite(TextureInfo * info, TextureVertex* vertices, const XMFLOAT2& textureSize)
{
	//2次元の拡大縮小、回転、平行移動をしたい（今は3次元）
	XMMATRIX scale;
	//scale = XMFLOAT4X4::Scale(info->scale.x*textureSize.x, info->scale.y*textureSize.y, 1.0f);
	scale = DirectX::XMMatrixScaling(info->scale.x*textureSize.x, info->scale.y*textureSize.y, 1.0f);

	XMMATRIX beginTranslation;
	//beginTranslation = XMFLOAT4X4::Translation(-info->orgin.x, -info->orgin.y, 0);
	beginTranslation = DirectX::XMMatrixTranslation(-info->orgin.x, -info->orgin.y, 0);

	XMMATRIX rotate;
	//rotate = XMFLOAT4X4::RotationFromAxisZ(info->angle);
	rotate = DirectX::XMMatrixRotationZ(info->angle);

	XMMATRIX endTranslation;
	//endTranslation = XMFLOAT4X4::Translation(info->orgin.x, info->orgin.y, 0);
	endTranslation = DirectX::XMMatrixTranslation(info->orgin.x, info->orgin.y, 0);

	XMMATRIX translation;
	//translation = XMFLOAT4X4::Translation(info->position.x, info->position.y, 0);
	translation = DirectX::XMMatrixTranslation(info->position.x, info->position.y, 0);

	XMMATRIX world = scale * beginTranslation * rotate * endTranslation * translation;

	float halfw = 0.5f;
	float halfh = 0.5f;

	std::pair<XMVECTORF32, XMVECTORF32>initialData[] =
	{
		{ XMVECTORF32{-halfw,halfh,0},XMVECTORF32{0,0} },
		{ XMVECTORF32{halfw,halfh,0}, XMVECTORF32{1,0} },
		{ XMVECTORF32{-halfw,-halfh,0},XMVECTORF32{0,1} },
		{ XMVECTORF32{halfw,-halfh,0},XMVECTORF32{1,1} }
	};

	for (unsigned int i = 0; i < VERTICES_SPRITE; i++)
	{
		//vertices[i].pos = XMFLOAT3::Transform(initialData[i].first, world);
		XMStoreFloat3(&vertices[i].pos, DirectX::XMVector3Transform(initialData[i].first, world));
		XMStoreFloat2(&vertices[i].tex, XMVECTORF32{ initialData[i].second[0] * info->uv.z, initialData[i].second[1] * info->uv.w } + XMVECTORF32{ info->uv.x, info->uv.y });
		vertices[i].color = info->color;
	}
}
