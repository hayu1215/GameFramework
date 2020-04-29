#pragma once

#include"AComponent.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class SystemComponent : public AComponent
{
public:
	SystemComponent();
	SystemComponent(bool isActive);
	~SystemComponent();

	virtual void update() = 0;
	void init()override;
	void onCreate()override;
	void onDestory()override;
	void onActive()override;
	void onDeActive()override;
};