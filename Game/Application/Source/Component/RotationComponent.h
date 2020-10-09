#pragma once

#include<memory>
#include<Framework/Source/Component/UpdateComponent.h>

class RotationComponent :public UpdateComponent
{
public:
	RotationComponent();
	~RotationComponent();

	void onCreate()override;
	void update()override;

private:
};