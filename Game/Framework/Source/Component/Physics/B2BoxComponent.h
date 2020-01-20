#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>
#include<Framework/Include/Box2D/Box2D.h>

class B2BoxComponent :public UpdateComponent
{
public:
	B2BoxComponent();
	B2BoxComponent(bool isActive, bool isStatic, const XMFLOAT2& size);
	~B2BoxComponent();

public:
	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

private:
	std::shared_ptr<Camera>a;
	std::unique_ptr<LineRenderer> lineRenderer;
	b2Body* m_pBody;
	const bool m_IsStatic;
	const XMFLOAT2 m_Size;
};