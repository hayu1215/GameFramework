#pragma once

#include<memory>

class Entity;

class AComponent : public std::enable_shared_from_this<AComponent>
{
public:
	AComponent();
	virtual ~AComponent();

public:
	virtual void init() = 0;
	virtual void setTask(const std::shared_ptr<AComponent>&) = 0;

protected:
	virtual void onActive() = 0;
	virtual void onDeActive() = 0;
	virtual void onDestory() = 0;

public:
	virtual void prepareDestroy();
	void destroy();
	void active();
	void deActive();
	void setEntity(const std::weak_ptr<Entity>&);

	bool isActive();

private:
	bool m_IsActive;

protected:
	std::weak_ptr<Entity>m_pEntity;
};