#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>
#include<Framework/Include/Box2D/Box2D.h>
#include<Framework/Source/Utility/Judge.h>

class LiquidFunComponent :public UpdateComponent
{
public:
	LiquidFunComponent();
	~LiquidFunComponent();

	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

private:
	b2World m_world;
	b2Body* m_groundBody;
	b2Body* m_body;
	std::shared_ptr<Camera>a;
	std::unique_ptr<LineRenderer> lineRenderer;
};