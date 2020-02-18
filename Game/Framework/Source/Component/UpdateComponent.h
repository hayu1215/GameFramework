#pragma once

#include"AComponent.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class UpdateComponent:public AComponent
{
public:
	UpdateComponent();
	UpdateComponent(bool isActive);
	~UpdateComponent();

	virtual void update() = 0;
	void init()override;
	void active()override;
	void deActive()override;
};