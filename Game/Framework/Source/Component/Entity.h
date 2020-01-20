#pragma once

#include<vector>
#include<list>
#include<memory>
#include<string>
#include<Framework/Source/Utility/Math/XMath.h>

class AComponent;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity();
	Entity(const XMFLOAT3& position, const std::string& tag, const std::string& name);
	virtual ~Entity();

	template<class T>
	std::weak_ptr<T> getComponent();
	template<class T>
	std::vector<std::weak_ptr<T>> getComponents();

	Entity* addComponent(const std::shared_ptr<AComponent>&);
	void addRemoveComponent(const std::weak_ptr<AComponent>&);
	void removeComponent();
	void active();
	void deActive();
	void destroy();

	bool isActive();
	const std::string& getTag();
	const std::string& getName();
	const XMFLOAT3& getPosition();

private:
	std::list<std::shared_ptr<AComponent>>m_Components;
	std::list<std::weak_ptr<AComponent>>m_RemoveComponents;
	XMFLOAT3 m_Position;
	const std::string m_Tag;
	const std::string m_Name;
	bool m_IsActive;
};

template<class T>
std::weak_ptr<T> Entity::getComponent()
{
	std::shared_ptr<T>component;
	for (auto& v : m_Components)
	{
		component = std::dynamic_pointer_cast<T>(v);
		if (component != nullptr)return component;

		//if (typeid(*v.get()).name() == typeid(T).name())
		//{
		//	return dynamic_pointer_cast<T>(v);
		//}
	}
	return std::weak_ptr<T>();
}

template<class T>
std::vector<std::weak_ptr<T>> Entity::getComponents()
{
	std::vector<std::weak_ptr<T>>components;
	for (auto& v : m_Components)
	{
		std::shared_ptr<T>component = std::dynamic_pointer_cast<T>(v);
		if (component != nullptr)components.emplace_back(component);
	}
	return components;//moveÇµÇΩÇŸÇ§Ç™Ç¢Ç¢ÅH
}