#include "MeshComponent.h"
#include<Framework/Source/Application/Task/TaskManager.h>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Utility/Math/Mathf.h>

std::shared_ptr<PolygonRenderer> MeshComponent::m_PolygonRenderer = nullptr;

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
	if(m_PolygonRenderer == nullptr) m_PolygonRenderer = std::make_shared<PolygonRenderer>();
}

void MeshComponent::draw()
{
	updateTransform();
	m_PolygonRenderer->addMeshComponent(std::dynamic_pointer_cast<MeshComponent>(shared_from_this()));
}

void MeshComponent::onActive()
{
	if(TaskManager::GetSystemTask<PolygonRenderer>().expired())TaskManager::AddTask(m_PolygonRenderer);
}

void MeshComponent::onDeActive()
{
}

void MeshComponent::onDestory()
{
}

void MeshComponent::setRegularPolygon(unsigned int vertexCount, const XMFLOAT4 & color)
{
	std::vector<XMFLOAT3> vertices;
	if (vertexCount == 4) vertices = { XMFLOAT3(-0.5f, 0.5f, 0), XMFLOAT3(0.5f, 0.5f, 0),  XMFLOAT3(0.5f, -0.5f, 0),  XMFLOAT3(-0.5f, -0.5f, 0) };
	else vertices = regularPolygonVertices(0.5f, vertexCount);

	std::vector<SimpleVertex> model;
	for (int i = 0; i < vertexCount; i++)
	{
		SimpleVertex sv;
		sv.pos = vertices[i];
		sv.color = color;
		model.emplace_back(sv);
	}
	m_model = model;
	setIndex(vertexCount, false);
}

std::vector<XMFLOAT3> MeshComponent::regularPolygonVertices(float radius, unsigned int count)
{
	std::vector<XMFLOAT3> res;
	float angle = 2 * mathf::PI / count;
	for (unsigned int i = 0; i < count; i++)
	{
		auto x = mathf::Sin(i * angle) * radius;
		auto y = mathf::Cos(i * angle) * radius;
		res.emplace_back(XMFLOAT3(x, y, 0));
	}
	return res;
}

std::vector<SimpleVertex> MeshComponent::getVertices()
{
	return m_vertices;
}

std::vector<unsigned short> MeshComponent::getIndexes()
{
	return m_indexes;
}

void MeshComponent::setIndex(unsigned int count, bool isStrip)
{
	m_indexes.resize((count - 2) * 3);
	unsigned int pos = 0;
	if (isStrip)
	{
		//012,132,234,354,456,576
		for (int i = 0; i < count - 2; i++)
		{
			m_indexes[pos] = i;
			if (i % 2 == 0)
			{
				m_indexes[pos + 1] = i + 1;
				m_indexes[pos + 2] = i + 2;
			}
			else
			{
				m_indexes[pos + 1] = i + 2;
				m_indexes[pos + 2] = i + 1;
			}
			pos += 3;
		}
	}
	else
	{
		//012,023,034,045,056,067
		for (int i = 0; i < count - 2; i++)
		{
			m_indexes[pos] = 0;
			m_indexes[pos + 1] = i + 1;
			m_indexes[pos + 2] = i + 2;
			pos += 3;
		}
	}
}

void MeshComponent::updateTransform()
{
	auto entity = m_entity.lock();
	auto position = entity->position();
	auto rotate = entity->rotate();
	auto scale = entity->scale();
	
	XMMATRIX scaleM = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f);
	XMMATRIX rotateM = DirectX::XMMatrixRotationZ(rotate.z);
	XMMATRIX translationM = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX worldM = scaleM * rotateM * translationM;

	m_vertices = m_model;
	for (auto& x : m_vertices)
	{
		XMStoreFloat3(&x.pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&x.pos), worldM));
	}
}
