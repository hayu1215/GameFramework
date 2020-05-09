#pragma once

#include<vector>
#include<list>
#include<memory>
#include<string>
#include<type_traits>
#include<Framework/Source/Utility/Math/XMath.h>
#include<Framework/Source/Component/AComponent.h>

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity();
	Entity(const XMFLOAT3& position, const XMFLOAT3& rotate, const XMFLOAT3& scale, const std::string& tag, const std::string& name);
	virtual ~Entity();

	template<class ...Args>
	static Entity* Add(const Args&... args);
	static void Remove();
	static void Clear();
	static std::list<std::weak_ptr<Entity>> GetEntities();

	template<class T>
	std::weak_ptr<T> getComponent();
	template<class T>
	std::vector<std::weak_ptr<T>> getComponents();
	template<class T, class ...Args>
	void addComponent(bool isActive, const Args&... args);

	void addRemoveComponent(const std::weak_ptr<AComponent>&);
	void removeComponent();
	void active();
	void deActive();
	void destroy();

	bool isActive();
	const std::string& getTag();
	const std::string& getName();
	const XMFLOAT3& position();
	void position(const XMFLOAT3& position);
	const XMFLOAT3& rotate();
	void rotate(const XMFLOAT3& rotate);
	const XMFLOAT3& scale();
	void scale(const XMFLOAT3& scale);

private:
	static std::list<std::shared_ptr<Entity>>m_Entities;
	static std::list<std::weak_ptr<Entity>>m_RemoveEntities;
	std::list<std::shared_ptr<AComponent>>m_components;
	std::list<std::weak_ptr<AComponent>>m_removeComponents;
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotate;
	XMFLOAT3 m_scale;
	const std::string m_tag;
	const std::string m_name;
	bool m_isActive;
};

template<class ...Args>
Entity* Entity::Add(const Args&...args)
{
	auto entitiy = std::make_shared<Entity>(args...);
	m_Entities.push_back(entitiy);
	return entitiy.get();
}

template<class T>
std::weak_ptr<T> Entity::getComponent()
{
	std::shared_ptr<T>component;
	for (auto& v : m_components)
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
	for (auto& v : m_components)
	{
		std::shared_ptr<T>component = std::dynamic_pointer_cast<T>(v);
		if (component != nullptr) components.emplace_back(component);
	}
	return components;//moveしたほうがいい？
}

template<class T, class ...Args>
void Entity::addComponent(bool isActive, const Args&... args)
{
	if (!std::is_base_of<AComponent, T>::value) return;//デバッグ時だけでいいかも
	auto component = std::make_shared<T>();
	m_components.emplace_back(component);
	component->setEntity(shared_from_this());
	component->init(isActive);
	component->onCreate(args...);
}