#pragma once

#include<memory>
#include<vector>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Graphics/2D/LineRenderer.h>
#include<Framework/Include/Box2D/Box2D.h>

class B2PolygonComponent :public UpdateComponent
{
public:
	B2PolygonComponent();
	B2PolygonComponent(bool isStatic, const std::vector<b2Vec2>& vertexes);
	~B2PolygonComponent();

public:
	void init()override;
	void update()override;

	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

private:
	std::shared_ptr<Camera>a;
	std::unique_ptr<LineRenderer> lineRenderer;
	b2Body* m_pBody;

	const bool m_IsStatic;
	std::vector<b2Vec2>m_Vertexes;
};