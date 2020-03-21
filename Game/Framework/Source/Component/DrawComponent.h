#pragma once

#include"AComponent.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class DrawComponent :public AComponent
{
public:
	DrawComponent();
	DrawComponent(bool isActive);
	~DrawComponent();

	virtual void draw() = 0;
	void init()override;
	void active()override;
	void deActive()override;
};