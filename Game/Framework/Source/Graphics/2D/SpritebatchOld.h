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


//enum struct SortMode
//{
//	//Draw���Ă񂾏��ŕ`��
//	Deferred = 0,
//
//	//Texture��ID�Ń\�[�g���ĕ`��(�����摜����������`�悷��Ƃ��Ɏg�p)
//	Texture = 1,
//
//	//Z���W�̌�납��O�ɕ��בւ��ĕ`��
//	BackToFront = 2,
//
//	//Z���W�̑O������ɕ��בւ��ĕ`��
//	FrontToBack = 3,
//
//	//�\�[�g���Ȃ��Œ����ɕ`��(Draw���Ă΂ꂽ�u�Ԃɕ`��)
//	//Immediate = 4
//};
//
//struct TextureInfo
//{
//	std::string shaderName = "Texture.hlsl";
//	std::string textureName;
//	//Texture texture;
//	XMFLOAT4 color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	XMFLOAT4 uv = XMFLOAT4(0, 0, 1.0f, 1.0f);
//	XMFLOAT3 position;
//	XMFLOAT2 scale = XMFLOAT2(1.0f, 1.0f);
//	XMFLOAT2 orgin = XMFLOAT2(0, 0);
//	float angle = 0;
//
//	bool operator>(const TextureInfo& info) const {
//		return position.z > info.position.z;
//	}
//	bool operator<(const TextureInfo& info) const {
//		return position.z < info.position.z;
//	}
//};
//
////���_�̍\����
//struct TextureVertex
//{
//	XMFLOAT3 Pos; //�ʒu
//	XMFLOAT2 vTex; //�e�N�X�`���[���W
//};

class SpritebatchOld
{
//public:
//	SpritebatchOld();
//	SpritebatchOld(std::shared_ptr<Camera>);
//	~SpritebatchOld();
//
//	void begin();
//	void begin(const SortMode &sortMode);
//	void begin(const SortMode &sortMode, bool isUI);
//	void end();
//
//	void draw(std::string textureName, XMFLOAT3 position);
//	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT4 color);
//	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT4 uv, XMFLOAT4 color);
//	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT2 scale, XMFLOAT4 color);
//	void draw(std::string textureName, XMFLOAT3 position, float angle, XMFLOAT2 orgin, XMFLOAT4 color);
//	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT2 scale, float angle, XMFLOAT2 orgin, XMFLOAT4 color);
//	void draw(std::string textureName, XMFLOAT3 position, XMFLOAT2 scale, float angle, XMFLOAT2 orgin, XMFLOAT4 uv, XMFLOAT4 color);
//
//	void setCamera(std::shared_ptr<Camera>);
//
//private:
//	void createVertexBuffer();
//	void deferredEnd();
//	void textureEnd();
//	void backToFrontEnd();
//	void frontToBackEnd();
//	void setInfo(const std::string textureName, const std::string shaderName);
//	void draw(const TextureInfo &info);
//	void clearDrawList();
//
//private:
//	SortMode m_CurrentMode;
//	std::weak_ptr<Camera>m_pCamera;
//	std::vector<TextureInfo>m_DrawTextures;
//	ComPtr<ID3D11Buffer> m_pVertexBuffer;
//	bool m_IsUI;
};