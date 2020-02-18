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

using Microsoft::WRL::ComPtr;

enum PolygonMesh
{
	None = 0,
	Circle = 1,
	Line = 2,
	Triangle = 3,
	Square = 4,
	Pentagon = 5,
	Hexagon = 6
};

struct PolygonInfo
{
	PolygonMesh polygonMesh;
	XMFLOAT4 color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT2 scale = XMFLOAT2(1.0f, 1.0f);
	XMFLOAT2 orgin = XMFLOAT2(0, 0);
	float angle = 0;
};

struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct SimpleConstantBuffer
{
	XMFLOAT4X4 matrix;
};

class PolygonRenderer
{
public:
	PolygonRenderer();
	~PolygonRenderer();

	void begin();
	void end();
	void drawTriangle(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawSquare(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawPentagon(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawHexagon(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawCircle(const XMFLOAT3& position, const XMFLOAT2& scale = XMFLOAT2(1.0f, 1.0f), const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), const XMFLOAT2& orgin = XMFLOAT2(0, 0), float angle = 0);
	void drawLine(const std::vector<SimpleVertex>& vertices, float width = 1.0f, bool isLoop = false, float cornerVertices = 1.0f, float endCapVertices = 0.0f);
	void drawPolygon(const std::vector<SimpleVertex>& vertices);

private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createConstantBuffer();
	void sortPolygons();
	void setPolygonInfo();
	void setTriangleInfo(PolygonInfo* info, SimpleVertex* vertices, int* indexes);
	void setWorldMatrix(PolygonInfo* info, SimpleVertex* vertices);
	void setIndex(int* indexes, int count);

	const unsigned short MAX_SIZE = 2048 * 4;
	const unsigned short QUEUE_SIZE = 64;

	std::vector<PolygonInfo> m_drawPolygons;
	std::vector<PolygonInfo*> m_sortPolygons;
	ComPtr<ID3D11Buffer> m_constantBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
	size_t m_vertexBufferPos = 0;
};