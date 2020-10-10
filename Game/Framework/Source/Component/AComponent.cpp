#include"AComponent.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Application/Task/TaskManager.h>

AComponent::AComponent() = default;

AComponent::~AComponent() = default;

void AComponent::onCreate() {}

void AComponent::onDestory() {}

void AComponent::active() {
    if (m_isActive) return;
    m_isActive = true;
    onActive();
}

void AComponent::deActive() {
    if (!m_isActive) return;
    m_isActive = false;
    onDeActive();
}

void AComponent::init(bool isActive) {
    m_isActive = isActive ? false : true;
    if (isActive) active();
    else deActive();
}

std::weak_ptr<Entity> AComponent::getEntity() {
    return m_entity;
}

void AComponent::setEntity(const std::weak_ptr<Entity>& entity) {
    m_entity = entity;
}

void AComponent::destroy() {
    onDestory();
    deActive();
    m_entity.lock()->addRemoveComponent(shared_from_this());
}

bool AComponent::isActive() {
    return m_isActive;
}

void AComponent::onActive() {}

void AComponent::onDeActive() {}