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

public:
	void setPosition(const XMFLOAT3&);
	void setLookatPt(const XMFLOAT3&);
	XMMATRIX getView();

private:
	XMFLOAT4X4 m_View;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_LookatPt;
	XMFLOAT3 m_UpVector = XMFLOAT3(0, 1, 0);
};