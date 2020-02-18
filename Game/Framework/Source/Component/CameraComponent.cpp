#include "CameraComponent.h"

std::weak_ptr<CameraComponent> CameraComponent::m_MainCamera;

CameraComponent::CameraComponent() :
	m_camera(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 1))
{
}

CameraComponent::CameraComponent(bool isActive) :
	UpdateComponent(isActive),m_camera(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 1))
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::onCreate()
{
	//if (m_MainCamera.lock() == nullptr) m_MainCamera = shared_from_this();
}

void CameraComponent::update()
{
	m_camera.setPosition(m_entity.lock()->getPosition());
}

void CameraComponent::onActive()
{
	if (!m_MainCamera.expired()) m_MainCamera.lock()->deActive();
	m_MainCamera = std::dynamic_pointer_cast<CameraComponent>(shared_from_this());
}

void CameraComponent::onDeActive()
{
}

void CameraComponent::onDestory()
{
}

std::weak_ptr<CameraComponent> CameraComponent::GetMainCamera()
{
	return m_MainCamera;
}

std::vector<std::weak_ptr<CameraComponent>> CameraComponent::GetCameras()
{
	return std::vector<std::weak_ptr<CameraComponent>>();
}

XMMATRIX CameraComponent::getView()
{
	return m_camera.getView();
}
