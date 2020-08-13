#pragma once

#include<memory>
#include<Framework/Source/Component/SystemComponent.h>

class PolygonRenderer;

class MeshRendererComponent : public SystemComponent
{
public:
	MeshRendererComponent();
	~MeshRendererComponent();

	void update()override;
	void onActive()override;
	void onDeActive()override;
	PolygonRenderer& polygonRenderer();

private:
	static std::shared_ptr<PolygonRenderer> m_PolygonRenderer;
};