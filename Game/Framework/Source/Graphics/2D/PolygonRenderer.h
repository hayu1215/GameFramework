#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include<vector>
#include"Texture.h"
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Graphics/VertexType.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Application/Task/UpdateSystem.h>

using Microsoft::WRL::ComPtr;

class MeshComponent;

struct Mesh
{
	std::vector<SimpleVertex> vertices;
	std::vector<unsigned short> indexes;
};

class PolygonRenderer : public UpdateSystem
{
public:
	PolygonRenderer();
	~PolygonRenderer() override;

	void update();
	void addMeshComponent(const std::weak_ptr<MeshComponent>&);
	void addMesh(const Mesh&);

private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createConstantBuffer();
	void setInfo();
	void draw();

	const unsigned short MAX_SIZE = 2048 * 4;
	std::vector<std::weak_ptr<MeshComponent>> m_meshComponents;
	std::vector<Mesh> m_meshes;
	ComPtr<ID3D11Buffer> m_constantBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
	size_t m_vertexBufferPos = 0;
	size_t m_indexBufferPos = 0;
};