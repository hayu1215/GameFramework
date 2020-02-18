#pragma once

#include<memory>

class Entity;

class AComponent : public std::enable_shared_from_this<AComponent>
{
public:
	AComponent();
	AComponent(bool isActive);
	virtual ~AComponent();

	virtual void init() = 0;
	virtual void onCreate() = 0;
	virtual void onDestory() = 0;
	virtual void active();
	virtual void deActive();

	void destroy();
	void setEntity(const std::weak_ptr<Entity>&);
	bool isActive();

protected:
	virtual void onActive() = 0;
	virtual void onDeActive() = 0;

	std::weak_ptr<Entity>m_entity;
	bool m_isActive;
};