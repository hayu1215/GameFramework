#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include"Texture.h"
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Graphics/2D/Camera.h>

//using namespace Microsoft::WRL;
using Microsoft::WRL::ComPtr;

struct LineVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct LineCBuffer
{
	XMFLOAT4X4 wvp;
	XMFLOAT4 width;
};

class LineRenderer
{
public:
	LineRenderer();
	LineRenderer(std::shared_ptr<Camera>camera);
	~LineRenderer();

	void drawLine(const XMFLOAT3& position1, const XMFLOAT3& position2, const XMFLOAT4& color1, const XMFLOAT4& color2, float width);

private:
	void createVertexBuffer();
	void createConstantBuffer();

private:
	ComPtr<ID3D11Buffer> m_pConstantBuffer;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	std::weak_ptr<Camera> m_pCamera;
};