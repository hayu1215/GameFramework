#pragma once

#include<memory>

class Entity;

class AComponent : public std::enable_shared_from_this<AComponent>
{
public:
	AComponent();
	AComponent(bool isActive);
	virtual ~AComponent();

public:
	virtual void init() = 0;
	virtual void onCreate() = 0;
	virtual void onDestory() = 0;

protected:
	virtual void onActive() = 0;
	virtual void onDeActive() = 0;

public:
	virtual void active();
	virtual void deActive();
	void destroy();
	void setEntity(const std::weak_ptr<Entity>&);

	bool isActive();

protected:
	std::weak_ptr<Entity>m_pEntity;
	bool m_IsActive;
};