#include "ModelComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/Mathf.h>
#include<Framework/Source/Graphics/3D/Model.h>
#include<Framework/Source/Graphics/3D/Material.h>
#include<Framework/Source/Application/Resource/ResourceManager.h>

ModelComponent::ModelComponent()
{
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::onCreate(const std::string & name)
{
	m_name = name;
	m_model = ResourceManager::GetModel(name + ".obj");
	m_material = ResourceManager::GetMaterial(name + ".mtl");
	m_polygonRenderer = m_entity.lock()->getComponent<MeshRendererComponent>();
}

void ModelComponent::draw()
{
	m_polygonRenderer.lock()->polygonRenderer().addModelComponent(std::dynamic_pointer_cast<ModelComponent>(shared_from_this()));
}

std::weak_ptr<Model> ModelComponent::getModel()
{
	return m_model;
}

std::weak_ptr<Material> ModelComponent::getMaterial()
{
	return m_material;
}

const std::string& ModelComponent::getName()
{
	return m_name;
}
