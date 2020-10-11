#include"Component.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Application/Task/TaskManager.h>

Component::Component() = default;

Component::~Component() = default;

void Component::onCreate() {}

void Component::onDestory() {}

void Component::active() {
    if (m_isActive) return;
    m_isActive = true;
    onActive();
}

void Component::deActive() {
    if (!m_isActive) return;
    m_isActive = false;
    onDeActive();
}

void Component::init(bool isActive) {
    m_isActive = isActive ? false : true;
    if (isActive) active();
    else deActive();
}

std::weak_ptr<Entity> Component::getEntity() {
    return m_entity;
}

void Component::setEntity(const std::weak_ptr<Entity>& entity) {
    m_entity = entity;
}

void Component::destroy() {
    onDestory();
    deActive();
    m_entity.lock()->addRemoveComponent(shared_from_this());
}

bool Component::isActive() {
    return m_isActive;
}

void Component::onActive() {}

void Component::onDeActive() {}