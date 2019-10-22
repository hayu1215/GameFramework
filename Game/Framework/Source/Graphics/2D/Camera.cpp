#include "Camera.h"

Camera::Camera() :
	m_Position(0, 0, 0), m_LookatPt(0, 0, 1)
{
	XMStoreFloat4x4(&m_View, DirectX::XMMatrixIdentity());
}

Camera::Camera(const XMFLOAT3 &position, const XMFLOAT3 &lookat):
     m_Position(position), m_LookatPt(lookat)
{
	XMStoreFloat4x4(&m_View, DirectX::XMMatrixIdentity());
}

Camera::~Camera()
{
}

void Camera::setPosition(const XMFLOAT3 &position)
{
	m_Position = position;
}

void Camera::setLookatPt(const XMFLOAT3 &lookatPt)
{
	m_LookatPt = lookatPt;
}

XMMATRIX Camera::getView()
{
	m_LookatPt = m_Position;
	m_LookatPt.z += 1.0f;
	XMStoreFloat4x4(&m_View, DirectX::XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_LookatPt), XMLoadFloat3(&m_UpVector)));
	return XMLoadFloat4x4(&m_View);
}