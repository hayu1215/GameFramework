#pragma once

#include"MeshComponent.h"

class RegularPolygonComponent :public MeshComponent
{
public:
	RegularPolygonComponent();
	RegularPolygonComponent(bool isActive);
	RegularPolygonComponent(bool isActive, unsigned int vertexCount, const XMFLOAT4& color);
	~RegularPolygonComponent();

	void draw()override;

	void setRegularPolygon(unsigned int vertexCount = 3, const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	std::vector<XMFLOAT3> regularPolygonVertices(float radius, unsigned int count);

private:
	void updateTransform();
};