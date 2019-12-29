#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>

class TestComponent :public UpdateComponent
{
public:
	TestComponent();
	~TestComponent();

public:
	void init()override;
	void update()override;

	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

	void drawBezier(const XMFLOAT3 & p0, const XMFLOAT3 & p1, const XMFLOAT3 & p2, const XMFLOAT3 & p3, int s);
	XMFLOAT3 bezier(const XMFLOAT3 & p0, const XMFLOAT3 & p1, const XMFLOAT3 & p2, const XMFLOAT3 & p3, float t);

private:
	std::shared_ptr<Camera>a;
	std::unique_ptr<LineRenderer> lineRenderer;
};