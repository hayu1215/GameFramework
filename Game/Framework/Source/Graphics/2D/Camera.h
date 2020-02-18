#pragma once

#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<DirectXMath.h>

class Camera
{
public:
	Camera();
	Camera(const XMFLOAT3&, const XMFLOAT3&);
	~Camera();

	void setPosition(const XMFLOAT3&);
	void setLookatPt(const XMFLOAT3&);
	XMMATRIX getView();

private:
	XMFLOAT4X4 m_view;
	XMFLOAT3 m_position;
	XMFLOAT3 m_lookatPt;
	XMFLOAT3 m_upVector = XMFLOAT3(0, 1, 0);
};