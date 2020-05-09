#pragma once

#include<vector>
#include "MeshComponent.h"
#include<Framework/Source/Utility/Math/XMath.h>

class LineComponent :public MeshComponent
{
public:
	LineComponent();
	~LineComponent();

	void onCreate(const std::vector<XMFLOAT3>& positions, const XMFLOAT4& color, float width, bool isLoop);
	void draw()override;

	void setLine(const std::vector<XMFLOAT3>& positions, const XMFLOAT4& color, float width, bool isLoop);
};