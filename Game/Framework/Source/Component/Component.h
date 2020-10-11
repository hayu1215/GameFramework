#pragma once

#include<memory>

class Entity;

class Component : public std::enable_shared_from_this<Component> {
public:
    Component();
    virtual ~Component();

    virtual void onCreate();
    virtual void onDestory();
    virtual void active();
    virtual void deActive();
    void init(bool isActive);
    std::weak_ptr<Entity> getEntity();
    void setEntity(const std::weak_ptr<Entity>&);
    void destroy();
    bool isActive();

protected:
    virtual void onActive();
    virtual void onDeActive();

    std::weak_ptr<Entity> m_entity;
    bool m_isActive = false;
};