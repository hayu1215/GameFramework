#pragma once

#include<memory>
#include<Framework/Source/Component/DrawComponent.h>
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

class MeshComponent :public DrawComponent
{
public:
	MeshComponent();
	MeshComponent(bool isActive);
	~MeshComponent();

	void onCreate()override;
	void draw()override;
	void onActive()override;
	void onDeActive()override;
	void onDestory()override;

	void setRegularPolygon(unsigned int vertexCount = 3, const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	std::vector<XMFLOAT3> regularPolygonVertices(float radius, unsigned int count);
	std::vector<SimpleVertex> getVertices();
	std::vector<unsigned short> getIndexes();

private:
	void setIndex(unsigned int count, bool isStrip = true);
	void updateTransform();

	static std::shared_ptr<PolygonRenderer> m_PolygonRenderer;
	std::vector<SimpleVertex> m_model;
	std::vector<SimpleVertex> m_vertices;
	std::vector<unsigned short> m_indexes;
};