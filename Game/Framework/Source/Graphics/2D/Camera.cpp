#include "Camera.h"

Camera::Camera() :
	m_position(0, 0, 0), m_lookatPt(0, 0, 1)
{
	XMStoreFloat4x4(&m_view, DirectX::XMMatrixIdentity());
}

Camera::Camera(const XMFLOAT3 &position, const XMFLOAT3 &lookat):
     m_position(position), m_lookatPt(lookat)
{
	XMStoreFloat4x4(&m_view, DirectX::XMMatrixIdentity());
}

Camera::~Camera()
{
}

void Camera::setPosition(const XMFLOAT3 &position)
{
	m_position = position;
}

void Camera::setLookatPt(const XMFLOAT3 &lookatPt)
{
	m_lookatPt = lookatPt;
}

XMMATRIX Camera::getView()
{
	m_lookatPt = m_position;
	m_lookatPt.z += 1.0f;
	XMStoreFloat4x4(&m_view, DirectX::XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_lookatPt), XMLoadFloat3(&m_upVector)));
	return XMLoadFloat4x4(&m_view);
}