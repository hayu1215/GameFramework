#include "Spritebatch.h"
#include<algorithm>
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>
#include<Framework/Source/Utility/Constant.h>

Spritebatch::Spritebatch()
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
}

Spritebatch::Spritebatch(std::shared_ptr<Camera>)
{
	createVertexBuffer();
	createIndexBuffer();
	createConstantBuffer();
}

Spritebatch::~Spritebatch()
{
}

void Spritebatch::begin()
{
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

void Spritebatch::draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 uv, Vector4 color)
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
	//�o�[�e�b�N�X�o�b�t�@�[�̐錾
	D3D11_BUFFER_DESC bd;

	//�o�[�e�b�N�X�o�b�t�@�[�̒�`
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(TextureVertex) * MAX_BATCH_SIZE * VERTICES_SPRITE;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//bd.MiscFlags = 0;

	HRESULT result = D3d11::Instance().getDevice()->CreateBuffer(&bd, nullptr, m_pVertexBuffer.GetAddressOf());
	utility::checkError(result, "�o�[�e�b�N�X�o�b�t�@�[�̍쐬���s");
}

void Spritebatch::createIndexBuffer()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(short) * MAX_BATCH_SIZE * INDICES_SPRITE;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	auto indexValues = createIndexValue();//���ڏ����Ă��悳���������ǂƂ肠��������

	D3D11_SUBRESOURCE_DATA indexDataDesc;
	indexDataDesc.pSysMem = indexValues.data();
	D3d11::Instance().getDevice()->CreateBuffer(&bd, &indexDataDesc, m_pIndexBuffer.GetAddressOf());
}

void Spritebatch::createConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = sizeof(Matrix4);
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	//���������Ă邩�͂킩���A�R���X�^���g�o�b�t�@�̏����l�̐ݒ�
	Matrix4 view = Matrix4::identity;
	Matrix4 proj = {
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	SimpleConstantBuffer cb[] = {{view * proj}};
	D3D11_SUBRESOURCE_DATA dataDesc;
	dataDesc.pSysMem = cb;

	HRESULT result = D3d11::Instance().getDevice()->CreateBuffer(&bd, &dataDesc, m_pConstantBuffer.GetAddressOf());
	if (utility::checkError(result, "�R���X�^���g�o�b�t�@�[�쐬���s"));
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
	auto deviceContext = D3d11::Instance().getDeviceContext();

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	deviceContext->IASetInputLayout(ResourceManager::Instance().findShader(shaderName)->getInputLayout().Get());

	//�g�p����V�F�[�_�[�̓o�^
	deviceContext->VSSetShader(ResourceManager::Instance().findShader(shaderName)->getVertexShader().Get(), nullptr, 0);
	deviceContext->PSSetShader(ResourceManager::Instance().findShader(shaderName)->getPixelShader().Get(), nullptr, 0);

	//�R���X�^���g�o�b�t�@�Ɋւ��Ă͈Ⴄ�������K�v����
	//deviceContext->UpdateSubresource()
	deviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	//deviceContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	deviceContext->PSSetSamplers(0, 1, ResourceManager::Instance().findShader(shaderName)->getSamplerState().GetAddressOf());

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(TextureVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	//�J�X�^���V�F�[�_��ԂȂ炱��
}

void Spritebatch::flushBatch()
{
	if (m_DrawTextures.empty())return;
	sortSprites();
	std::string batchTextureName = "";
	unsigned int batchStart = 0;

	//��T�ڑf�ʂ�@�����������ꂢ�ȃ��[�v�ɂ������A
	for (unsigned int pos = 0; pos < m_DrawTextures.size(); pos++)
	{
		std::string textureName = m_SortTextures[pos]->textureName;

		if (textureName != batchTextureName)
		{
			if (pos > batchStart)
			{
				renderBatch(m_SortTextures[batchStart], pos - batchStart);
			}

			batchTextureName = textureName;
			batchStart = pos;
		}
	}

	renderBatch(m_SortTextures[batchStart], m_DrawTextures.size() - batchStart);

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
	unsigned int size = m_SortTextures.size();
	m_SortTextures.resize(size);

	for (unsigned int i = 0; i < size; i++)
	{
		m_SortTextures[i] = &m_DrawTextures[i];
	}
}

void Spritebatch::renderBatch(TextureInfo* info, size_t count)
{
	ID3D11ShaderResourceView* texture = ResourceManager::Instance().findTexture((*info).textureName)->getShaderResourceView().Get();
	auto deviceContext = D3d11::Instance().getDeviceContext();
	deviceContext->PSSetShaderResources(0, 1, &texture);

	while (count > 0)
	{
		//vertexBufferPosition���ׂ�
		unsigned int batchSize = count;

		unsigned int remainingSpace = MAX_BATCH_SIZE - m_VertexBufferPos;

		Vector2 textureSize = ResourceManager::Instance().findTexture(info->textureName)->getSize();

		if (batchSize > remainingSpace)
		{
			if (remainingSpace < MIN_BATCH_SIZE)
			{
				//�]�T���Ȃ��ꍇ�A�܂��͉ߓx�ɏ������o�b�`�𑗐M���悤�Ƃ��Ă���ꍇ�́A���_�o�b�t�@�̐擪�ɖ߂�܂��B
				m_VertexBufferPos = 0;

				batchSize = std::min<unsigned int>(count, MAX_BATCH_SIZE);
			}
			else
			{
				batchSize = remainingSpace;
			}
		}


		//D3D11_MAP mapType = (m_VertexBufferPos == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;

		D3D11_MAPPED_SUBRESOURCE mappedBuffer;

		deviceContext->Map(m_pVertexBuffer.Get(), 0, mapType, 0, &mappedBuffer);

		auto vertices = static_cast<TextureVertex*>(mappedBuffer.pData) + m_VertexBufferPos * VERTICES_SPRITE;

		for (unsigned int i = 0; i < batchSize; i++)
		{
			renderSprite(info, vertices, textureSize);
			vertices += VERTICES_SPRITE;
		}

		deviceContext->Unmap(m_pVertexBuffer.Get(), 0);

		//�R���X�^���g�o�b�t�@
		//D3D11_MAPPED_SUBRESOURCE pData;
		//SimpleConstantBuffer cb;

		//HRESULT result = deviceContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		//if (!utility::checkError(result, "DeviceContext��Map�̎��s"))
		//{
		//	Matrix4 view = Matrix4::identity;

		//	Matrix4 proj = {
		//		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		//		0.0f, 2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		//		0.0f, 0.0f, 1.0f, 0.0f,
		//		0.0f, 0.0f, 0.0f, 1.0f
		//	};

		//	cb.matrix4 = view * proj;
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

void Spritebatch::renderSprite(TextureInfo const* info, TextureVertex* vertices, const Vector2& textureSize)
{
	//2�����̊g��k���A��]�A���s�ړ����������i����3�����j
	Matrix4 scale;
	scale = Matrix4::Scale(info->scale.x*textureSize.x, info->scale.y*textureSize.y, 1.0f);

	Matrix4 beginTranslation;
	beginTranslation = Matrix4::Translation(-info->orgin.x, -info->orgin.y, 0);

	Matrix4 rotate;
	rotate = Matrix4::RotationFromAxisZ(info->angle);

	Matrix4 endTranslation;
	endTranslation = Matrix4::Translation(info->orgin.x, info->orgin.y, 0);

	Matrix4 translation;
	translation = Matrix4::Translation(info->position.x, info->position.y, info->position.z);

	Matrix4 world = scale * beginTranslation * rotate * endTranslation * translation;

	float halfw = 0.5f;
	float halfh = 0.5f;

	std::pair<Vector3, Vector2>initialData[] =
	{
		{ Vector3(-halfw,halfh,0),Vector2(0,0) },
		{ Vector3(halfw,halfh,0), Vector2(1,0) },
		{ Vector3(-halfw,-halfh,0),Vector2(0,1) },
		{ Vector3(halfw,-halfh,0),Vector2(1,1) }
	};

	for (unsigned int i = 0; i < VERTICES_SPRITE; i++)
	{
		vertices[i].pos = Vector3::Transform(initialData[i].first, world);
		vertices[i].tex = Vector2(initialData[i].second.x * info->uv.z, initialData[i].second.y * info->uv.w) + Vector2(info->uv.x, info->uv.y);
		vertices[i].color = info->color;
	}
}
