#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

class TestComponent1 :public UpdateComponent
{
public:
	TestComponent1();
	TestComponent1(bool isActive);
	~TestComponent1();

	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;
};