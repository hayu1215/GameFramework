#include "MeshComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/Mathf.h>

//std::shared_ptr<PolygonRenderer> MeshComponent::m_PolygonRenderer = nullptr;

MeshComponent::MeshComponent()
{
}

MeshComponent::MeshComponent(bool isActive)
	:DrawComponent(isActive)
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::onCreate()
{
	//if(m_PolygonRenderer == nullptr) m_PolygonRenderer = std::make_shared<PolygonRenderer>();
	m_polygonRenderer = m_entity.lock()->getComponent<MeshRendererComponent>();
}

void MeshComponent::draw()
{
	//updateTransform();
	//m_PolygonRenderer->addMeshComponent(std::dynamic_pointer_cast<MeshComponent>(shared_from_this()));
	m_polygonRenderer.lock()->polygonRenderer().addMeshComponent(std::dynamic_pointer_cast<MeshComponent>(shared_from_this()));
}

void MeshComponent::onActive()
{
	//if(TaskManager::GetSystemTask<PolygonRenderer>().expired()) TaskManager::AddTask(m_PolygonRenderer);
}

void MeshComponent::onDeActive()
{
}

void MeshComponent::onDestory()
{
}

//std::vector<SimpleVertex> MeshComponent::getVertices()
//{
//	return m_vertices;
//}

//std::vector<unsigned short> MeshComponent::getIndexes()
//{
//	return m_indexes;
//}

const Mesh& MeshComponent::mesh()
{
	return m_mesh;
}

const std::vector<SimpleVertex>& MeshComponent::model()
{
	return m_model;
}

void MeshComponent::setIndex(unsigned int count, bool isStrip)
{
	m_mesh.indexes.resize((count - 2) * 3);
	unsigned int pos = 0;
	if (isStrip)
	{
		//012,132,234,354,456,576
		for (int i = 0; i < count - 2; i++)
		{
			m_mesh.indexes[pos] = i;
			if (i % 2 == 0)
			{
				m_mesh.indexes[pos + 1] = i + 1;
				m_mesh.indexes[pos + 2] = i + 2;
			}
			else
			{
				m_mesh.indexes[pos + 1] = i + 2;
				m_mesh.indexes[pos + 2] = i + 1;
			}
			pos += 3;
		}
	}
	else
	{
		//012,023,034,045,056,067
		for (int i = 0; i < count - 2; i++)
		{
			m_mesh.indexes[pos] = 0;
			m_mesh.indexes[pos + 1] = i + 1;
			m_mesh.indexes[pos + 2] = i + 2;
			pos += 3;
		}
	}
}