#pragma once

#include<memory>
#include<vector>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>

class CameraComponent :public UpdateComponent
{
public:
	CameraComponent();
	CameraComponent(bool isActive);
	~CameraComponent();

	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

	static std::weak_ptr<CameraComponent> GetMainCamera();
	static std::vector<std::weak_ptr<CameraComponent>> GetCameras();
	XMMATRIX getView();

private:
	static std::weak_ptr<CameraComponent> m_MainCamera;
	Camera m_camera;
};