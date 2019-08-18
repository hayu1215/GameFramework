#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include"Texture.h"
#include<Framework/Source/Utility/Math/Vector4.h>
#include<Framework/Source/Utility/Math/Vector3.h>
#include<Framework/Source/Utility/Math/Vector2.h>
#include<Framework/Source/Utility/Math/Matrix4.h>
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
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 uv = Vector4(0, 0, 1.0f, 1.0f);
	Vector3 position;
	Vector2 scale = Vector2(1.0f, 1.0f);
	Vector2 orgin = Vector2(0, 0);
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
	Vector3 pos;
	Vector2 tex;
	Vector4 color;
};

struct SimpleConstantBuffer
{
	Matrix4 matrix4;
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
	void draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 uv, Vector4 color);

private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createConstantBuffer();
	std::vector<short> createIndexValue();
	void setInfo(const std::string& shaderName);
	void flushBatch();
	void sortSprites();
	void growSortSprites();
	void renderBatch(TextureInfo*info, size_t count);
	void renderSprite(TextureInfo const* info, TextureVertex* vertices, const Vector2& textureSize);

private:
	const unsigned short MAX_BATCH_SIZE = 2048;
	const unsigned short MIN_BATCH_SIZE = 128;
	const unsigned short QUEUE_SIZE = 64;
	const unsigned short VERTICES_SPRITE = 4;
	const unsigned short INDICES_SPRITE = 6;

	SortMode m_SortMode;
	std::weak_ptr<Camera> m_pCamera;
	std::vector<TextureInfo> m_DrawTextures;
	std::vector<TextureInfo*> m_SortTextures;
	ComPtr<ID3D11Buffer> m_pConstantBuffer;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11Buffer> m_pIndexBuffer;
	size_t m_VertexBufferPos; //���̖��O���@veretx��pos�Ȃ̂ɃX�v���C�g1���ɑ΂��ĂP���������Ȃ�

};