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
	Entity(const XMFLOAT3& position, const XMFLOAT3& rotate, const XMFLOAT3& scale, const std::string& tag, const std::string& name);
	virtual ~Entity();

	template<class T>
	std::weak_ptr<T> getComponent();
	template<class T>
	std::vector<std::weak_ptr<T>> getComponents();
	template<class T, class... Args>
	void addComponent(const Args&... args);

	//Entity* addComponent(const std::shared_ptr<AComponent>&);
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
	std::list<std::shared_ptr<AComponent>>m_components;
	std::list<std::weak_ptr<AComponent>>m_removeComponents;
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotate;
	XMFLOAT3 m_scale;
	const std::string m_tag;
	const std::string m_name;
	bool m_isActive;
};

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
		if (component != nullptr)components.emplace_back(component);
	}
	return components;//moveしたほうがいい？
}

template<class T, class... Args>
void Entity::addComponent(const Args&... args)
{
	//ベースチェック(デバッグ時のみ)
	auto component = std::make_shared<T>(args...);
	m_components.emplace_back(component);
	component->setEntity(shared_from_this());
	component->onCreate();
	component->init();
}