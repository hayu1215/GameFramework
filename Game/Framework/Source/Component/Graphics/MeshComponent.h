#pragma once

#include<memory>
#include<Framework/Source/Component/DrawComponent.h>
#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>
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

	//std::vector<SimpleVertex> getVertices();
	//std::vector<unsigned short> getIndexes();
	const Mesh& mesh();
	const std::vector<SimpleVertex>& model();

protected:
	void setIndex(unsigned int count, bool isStrip = true);
	std::vector<SimpleVertex> m_model;
	Mesh m_mesh;
	//std::vector<SimpleVertex> m_vertices;
	//std::vector<unsigned short> m_indexes;

private:
	//static std::shared_ptr<PolygonRenderer> m_PolygonRenderer;
	std::weak_ptr<MeshRendererComponent> m_polygonRenderer;
};