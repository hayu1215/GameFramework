#pragma once

#include<Framework/Source/Utility/Math/Vector3.h>
#include<Framework/Source/Utility/Math/Matrix4.h>

class Camera
{
public:
	Camera();
	Camera(const Vector3&, const Vector3&);
	~Camera();

public:
	void setPosition(const Vector3&);
	void setLookatPt(const Vector3&);
	Matrix4 getView();

private:
	Matrix4 m_View;
	Vector3 m_Position;
	Vector3 m_LookatPt;
	Vector3 m_UpVector = Vector3(0, 1, 0);
};