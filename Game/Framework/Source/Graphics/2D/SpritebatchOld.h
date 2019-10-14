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
	//Drawを呼んだ順で描画
	Deferred = 0,

	//TextureのIDでソートして描画(同じ画像をたくさん描画するときに使用)
	Texture = 1,

	//Z座標の後ろから前に並べ替えて描画
	BackToFront = 2,

	//Z座標の前から後ろに並べ替えて描画
	FrontToBack = 3,

	//ソートしないで直ちに描画(Drawが呼ばれた瞬間に描画)
	//Immediate = 4
};

struct TextureInfo
{
	std::string shaderName = "Texture.hlsl";
	std::string textureName;
	//Texture texture;
	Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 uv = Vector4(0, 0, 1.0f, 1.0f);
	Vector3 position;
	Vector2 scale = Vector2(1.0f, 1.0f);
	Vector2 orgin = Vector2(0, 0);
	float angle = 0;

	bool operator>(const TextureInfo& info) const {
		return position.z > info.position.z;
	}
	bool operator<(const TextureInfo& info) const {
		return position.z < info.position.z;
	}
};

//頂点の構造体
struct TextureVertex
{
	Vector3 Pos; //位置
	Vector2 vTex; //テクスチャー座標
};

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
//	void draw(std::string textureName, Vector3 position);
//	void draw(std::string textureName, Vector3 position, Vector4 color);
//	void draw(std::string textureName, Vector3 position, Vector4 uv, Vector4 color);
//	void draw(std::string textureName, Vector3 position, Vector2 scale, Vector4 color);
//	void draw(std::string textureName, Vector3 position, float angle, Vector2 orgin, Vector4 color);
//	void draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 color);
//	void draw(std::string textureName, Vector3 position, Vector2 scale, float angle, Vector2 orgin, Vector4 uv, Vector4 color);
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