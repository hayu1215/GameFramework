#pragma once

#include<vector>
#include<memory>
#include<wrl/client.h>
#include"Texture.h"
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Utility/Math/Vector4.h>
#include<Framework/Source/Utility/Math/Vector3.h>
#include<Framework/Source/Utility/Math/Vector2.h>
#include<Framework/Source/Utility/Math/Matrix4.h>
#include<Framework/Source/Graphics/2D/Camera.h>

using namespace Microsoft::WRL;

struct LineVertex
{
	Vector3 pos;
	Vector4 color;
};

struct LineCBuffer
{
	Matrix4 wvp;
	Vector4 width;
};

class LineRenderer
{
public:
	LineRenderer();
	LineRenderer(std::shared_ptr<Camera>camera);
	~LineRenderer();

	void drawLine(const Vector3& position1, const Vector3& position2, const Vector4& color1, const Vector4& color2, float width);

private:
	void createVertexBuffer();
	void createConstantBuffer();

private:
	ComPtr<ID3D11Buffer> m_pConstantBuffer;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	std::weak_ptr<Camera> m_pCamera;
};