#pragma once

#include"AComponent.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class UpdateComponent:public AComponent
{
public:
	UpdateComponent();
	~UpdateComponent();

public:
	virtual void init() = 0;
	virtual void update() = 0;

protected:
	virtual void onActive() = 0;
	virtual void onDeActive() = 0;
	virtual void onDestory() = 0;

public:
	void setTask(const std::shared_ptr<AComponent>&)override;
	void prepareDestroy()override;
};