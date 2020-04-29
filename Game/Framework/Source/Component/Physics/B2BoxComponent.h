#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>
#include<Framework/Include/Box2D/Box2D.h>
#include<Framework/Source/Utility/Math/XMath.h>

class B2BoxComponent :public UpdateComponent
{
public:
	B2BoxComponent();
	B2BoxComponent(bool isActive, bool isStatic, const XMFLOAT2& size = XMFLOAT2(1.0f, 1.0f));
	~B2BoxComponent();

	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

	float angle();
	const XMFLOAT3& position();
	const std::vector<XMFLOAT3>& vertices();

private:
	b2Body* m_body;
	const bool m_isStatic;
	const XMFLOAT2 m_size;
};