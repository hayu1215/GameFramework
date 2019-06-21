#include "Camera.h"

Camera::Camera() :
	m_Position(0, 0, 0), m_LookatPt(0, 0, 1)
{
	m_View = Matrix4::identity;
}

Camera::Camera(const Vector3 &position, const Vector3 &lookat):
     m_Position(position), m_LookatPt(lookat)
{
	m_View = Matrix4::identity;
}

Camera::~Camera()
{
}

void Camera::setPosition(const Vector3 &position)
{
	m_Position = position;
}

void Camera::setLookatPt(const Vector3 &lookatPt)
{
	m_LookatPt = lookatPt;
}

Matrix4 Camera::getView()
{
	m_LookatPt = m_Position;
	m_LookatPt.z += 1.0f;
	m_View = Matrix4::LookAt(m_Position, m_LookatPt, m_UpVector);
	return m_View;
}