#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include"Texture.h"
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Graphics/2D/Camera.h>


enum struct SortMode
{
	//Draw���Ă񂾏��ŕ`��
	Deferred = 0,

	//Texture��ID�Ń\�[�g���ĕ`��(�����摜����������`�悷��Ƃ��Ɏg�p)
	Texture = 1,

	//Z���W�̌�납��O�ɕ��בւ��ĕ`��
	BackToFront = 2,

	//Z���W�̑O������ɕ��בւ��ĕ`��
	FrontToBack = 3,

	//�\�[�g���Ȃ��Œ����ɕ`��(Draw���Ă΂ꂽ�u�Ԃɕ`��)
	Immediate = 4
};

struct TextureInfo
{
	std::string textureName;
	XMFLOAT4 color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 uv = XMFLOAT4(0, 0, 1.0f, 1.0f);
	XMFLOAT3 position;
	XMFLOAT2 scale = XMFLOAT2(1.0f, 1.0f);
	XMFLOAT2 orgin = XMFLOAT2(0, 0);
	float angle = 0;

	//bool operator>(const TextureInfo& info) const {
	//	return position.z > info.position.z;
	//}
	//bool operator<(const TextureInfo& info) const {
	//	return position.z < info.position.z;
	//}
};

//���_�̍\����
struct TextureVertex
{
	XMFLOAT3 pos;
	XMFLOAT2 tex;
	XMFLOAT4 color;
};

struct SimpleConstantBuffer
{
	XMFLOAT4X4 matrix;
};

class Spritebatch
{
public:
	Spritebatch();
	Spritebatch(std::shared_ptr<Camera>);
	~Spritebatch();

	void begin();
	void begin(const SortMode &sortMode);
	void end(const std::string& shaderName);
	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT2 scale, float angle, XMFLOAT2 orgin, XMFLOAT4 uv, XMFLOAT4 color);

private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createConstantBuffer();
	void createSamplerState();
	std::vector<short> createIndexValue();
	void setInfo(const std::string& shaderName);
	void flushBatch();
	void sortSprites();
	void growSortSprites();
	void renderBatch(TextureInfo**info, size_t count);
	void renderSprite(TextureInfo* info, TextureVertex* vertices, const XMFLOAT2& textureSize);

	const unsigned short MAX_BATCH_SIZE = 2048;
	const unsigned short MIN_BATCH_SIZE = 128;
	const unsigned short QUEUE_SIZE = 64;
	const unsigned short VERTICES_SPRITE = 4;
	const unsigned short INDICES_SPRITE = 6;

	SortMode m_sortMode;
	std::weak_ptr<Camera> m_camera;
	std::vector<TextureInfo> m_drawTextures;
	std::vector<TextureInfo*> m_sortTextures;
	ComPtr<ID3D11Buffer> m_constantBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
	ComPtr<ID3D11SamplerState> m_samplerState;
	size_t m_vertexBufferPos; //���̖��O���@veretx��pos�Ȃ̂ɃX�v���C�g1���ɑ΂��ĂP���������Ȃ�
};