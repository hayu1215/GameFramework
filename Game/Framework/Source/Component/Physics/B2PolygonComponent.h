#pragma once

#include<memory>
#include<vector>
#include<Framework/Source/Component/UpdateComponent.h>
#include<Framework/Include/Box2D/Box2D.h>

class B2PolygonComponent :public UpdateComponent
{
public:
	B2PolygonComponent();
	B2PolygonComponent(bool isActive, bool isStatic);
	B2PolygonComponent(bool isActive, bool isStatic, const std::vector<XMFLOAT3>& vertexes);
	~B2PolygonComponent();

	void onCreate()override;
	void update()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

	float angle();
	const XMFLOAT3& position();
	const std::vector<XMFLOAT3>& vertices();

private:
	void createBody(bool isStatic, const std::vector<XMFLOAT3>& vertexes);
	b2Body* m_body;
	//const bool m_isStatic;
	//std::vector<b2Vec2> m_vertexes;
};