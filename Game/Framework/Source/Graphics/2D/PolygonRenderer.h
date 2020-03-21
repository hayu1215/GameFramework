#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include<vector>
#include"Texture.h"
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Graphics/2D/Spritebatch.h>
#include<Framework/Source/Application/Task/UpdateSystem.h>

using Microsoft::WRL::ComPtr;

class MeshComponent;

enum PolygonMesh
{
	None,
	Circle,
	Line,
	Triangle,
	Square,
	Pentagon,
	Hexagon,
};

struct PolygonInfo
{
	PolygonMesh polygonMesh;
	XMFLOAT4 color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT2 scale = XMFLOAT2(1.0f, 1.0f);
	XMFLOAT2 orgin = XMFLOAT2(0, 0);
	float angle = 0;
	unsigned int vertexCount = 0;
};

struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

//struct SimpleConstantBuffer
//{
//	XMFLOAT4X4 matrix;
//};

class PolygonRenderer : public UpdateSystem
{
public:
	PolygonRenderer();
	~PolygonRenderer() override;

	void update();
	void begin();
	void end();
	void draw();
	void addMeshComponent(const std::weak_ptr<MeshComponent>&);
	void drawTriangle(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawSquare(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawPentagon(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawHexagon(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawCircle(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0, unsigned int vertexCount = 25);
	void drawLine(const std::vector<SimpleVertex>& vertices, float width = 1.0f, bool isLoop = false, float cornerVertices = 1.0f, float endCapVertices = 0.0f);
	void drawPolygon(const std::vector<SimpleVertex>& vertices);
	std::vector<XMFLOAT2> regularPolygonVertices(float radius, unsigned int count);

private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createConstantBuffer();
	void sortPolygons();
	void growSortPolygons();
	void setInfo();
	void drawPolygon();
	void setTriangleInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setSquareInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setPentagonInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setHexagonInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setCircleInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setLineInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setPolygonInfo(PolygonInfo* info, SimpleVertex* vertices, unsigned short* indexes);
	void setWorldMatrix(PolygonInfo* info, SimpleVertex* vertices, unsigned int count);
	void setIndex(unsigned short* indexes, int count, bool isStrip = true);

	const unsigned short MAX_SIZE = 2048 * 4;
	const unsigned short QUEUE_SIZE = 64;

	std::vector<std::weak_ptr<MeshComponent>> m_meshComponents;
	std::vector<PolygonInfo> m_drawPolygons;
	std::vector<PolygonInfo*> m_sortPolygons;
	ComPtr<ID3D11Buffer> m_constantBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
	size_t m_vertexBufferPos = 0;
	size_t m_indexBufferPos = 0;
};