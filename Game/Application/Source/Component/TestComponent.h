#pragma once

#include<Framework/Source/Component/UpdateComponent.h>

class TestComponent :public UpdateComponent
{
public:
	TestComponent();
	~TestComponent();

public:
	void init()override;
	void update()override;

	void onActive()override;
	void onDeActive()override;
	void onDestory()override;
};