#include "LineComponent.h"
#include<Framework/Source/Graphics/2D/PolygonRenderer.h>

LineComponent::LineComponent()
{
}

LineComponent::LineComponent(bool isActive)
	:MeshComponent(isActive)
{
}

LineComponent::LineComponent(bool isActive, const std::vector<XMFLOAT3>& positions, const XMFLOAT4 & color, float width, bool isLoop)
	:MeshComponent(isActive)
{
	setLine(positions, color, width, isLoop);
}

LineComponent::~LineComponent()
{
}

void LineComponent::draw()
{
	m_mesh.vertices = m_model;
	MeshComponent::draw();
}

void LineComponent::setLine(const std::vector<XMFLOAT3>& positions, const XMFLOAT4 & color, float width, bool isLoop)
{
	using namespace DirectX;
	m_model.clear();
	//m_model.resize(positions.size() * 2);
	float halfWidth = width / 2;

	if (isLoop) 
	{
		auto loopPos = positions;
		loopPos.emplace_back(positions[0]);
		auto it = loopPos.begin();
		loopPos.insert(it, positions[positions.size() - 1]);

		for (unsigned int i = 1; i < loopPos.size() - 1; i++)
		{
			XMVECTOR p0 = XMLoadFloat3(&loopPos[i - 1]);
			XMVECTOR p1 = XMLoadFloat3(&loopPos[i]);
			XMVECTOR p2 = XMLoadFloat3(&loopPos[i + 1]);
			XMVECTOR line = p1 - p0;
			XMVECTOR normal = XMVector3Normalize(XMVectorSet(-XMVectorGetY(line), XMVectorGetX(line), 0.0f, 0.0f));
			XMVECTOR tangent = XMVector3Normalize(XMVector3Normalize(p2 - p1) + XMVector3Normalize(p1 - p0));
			XMVECTOR miter = XMVectorSet(-XMVectorGetY(tangent), XMVectorGetX(tangent), 0.0f, 0.0f);
			float length = halfWidth / XMVectorGetX(XMVector2Dot(miter, normal));
			SimpleVertex v0;
			SimpleVertex v1;
			v0.color = color;
			v1.color = color;
			XMStoreFloat3(&v0.pos, p1 - miter * length);
			XMStoreFloat3(&v1.pos, p1 + miter * length);
			m_model.emplace_back(v0);
			m_model.emplace_back(v1);
		}

		setIndex(m_model.size(), true);
		m_mesh.indexes.emplace_back(m_model.size() - 2);
		m_mesh.indexes.emplace_back(m_model.size() - 1);
		m_mesh.indexes.emplace_back(0);
		m_mesh.indexes.emplace_back(m_model.size() - 1);
		m_mesh.indexes.emplace_back(1);
		m_mesh.indexes.emplace_back(0);
	}
	else
	{
		XMVECTOR beginP0 = XMLoadFloat3(&positions[0]);
		XMVECTOR beginP1 = XMLoadFloat3(&positions[1]);
		XMVECTOR line0 = beginP1 - beginP0;
		XMVECTOR normal0 = XMVector3Normalize(XMVectorSet(-XMVectorGetY(line0), XMVectorGetX(line0), 0.0f, 0.0f));
		SimpleVertex beginV0;
		SimpleVertex beginV1;
		beginV0.color = color;
		beginV1.color = color;
		XMStoreFloat3(&beginV0.pos, beginP0 - halfWidth * normal0);
		XMStoreFloat3(&beginV1.pos, beginP0 + halfWidth * normal0);
		m_model.emplace_back(beginV0);
		m_model.emplace_back(beginV1);

		for (unsigned int i = 1; i < positions.size() - 1; i++)
		{
			XMVECTOR p0 = XMLoadFloat3(&positions[i - 1]);
			XMVECTOR p1 = XMLoadFloat3(&positions[i]);
			XMVECTOR p2 = XMLoadFloat3(&positions[i + 1]);
			XMVECTOR line = p1 - p0;
			XMVECTOR normal = XMVector3Normalize(XMVectorSet(-XMVectorGetY(line), XMVectorGetX(line), 0.0f, 0.0f));
			XMVECTOR tangent = XMVector3Normalize(XMVector3Normalize(p2 - p1) + XMVector3Normalize(p1 - p0));
			XMVECTOR miter = XMVectorSet(-XMVectorGetY(tangent), XMVectorGetX(tangent), 0.0f, 0.0f);
			float length = halfWidth / XMVectorGetX(XMVector2Dot(miter, normal));
			SimpleVertex v0;
			SimpleVertex v1;
			v0.color = color;
			v1.color = color;
			XMStoreFloat3(&v0.pos, p1 - miter * length);
			XMStoreFloat3(&v1.pos, p1 + miter * length);
			m_model.emplace_back(v0);
			m_model.emplace_back(v1);
		}

		XMVECTOR endP0 = XMLoadFloat3(&positions[positions.size() - 1]);
		XMVECTOR endP1 = XMLoadFloat3(&positions[positions.size() - 2]);
		XMVECTOR line1 = endP0 - endP1;
		XMVECTOR normal1 = XMVector3Normalize(XMVectorSet(-XMVectorGetY(line1), XMVectorGetX(line1), 0.0f, 0.0f));
		SimpleVertex endV0;
		SimpleVertex endV1;
		endV0.color = color;
		endV1.color = color;
		XMStoreFloat3(&endV0.pos, endP0 - halfWidth * normal1);
		XMStoreFloat3(&endV1.pos, endP0 + halfWidth * normal1);
		m_model.emplace_back(endV0);
		m_model.emplace_back(endV1);

		setIndex(m_model.size(), true);
	}
}
