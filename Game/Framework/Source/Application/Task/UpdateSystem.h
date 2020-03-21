#pragma once

class UpdateSystem
{
public:
	virtual ~UpdateSystem() {};
	virtual void update() = 0;
};