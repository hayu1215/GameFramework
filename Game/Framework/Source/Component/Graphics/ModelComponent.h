#pragma once

#include<memory>
#include<Framework/Source/Component/DrawComponent.h>
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

class MeshRendererComponent;
class Model;
class Material;

class ModelComponent :public DrawComponent
{
public:
	ModelComponent();
	~ModelComponent();

	void onCreate(const std::string &name);
	void draw()override;

	std::weak_ptr<Model> getModel();
	std::weak_ptr<Material> getMaterial();
	const std::string& getName();

private:
	std::weak_ptr<MeshRendererComponent> m_polygonRenderer;
	std::weak_ptr<Model> m_model;
	std::weak_ptr<Material> m_material;
	std::string m_name = "";
};