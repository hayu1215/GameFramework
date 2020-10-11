#include"RotationComponent.h"

RotationComponent::RotationComponent() {}

RotationComponent::~RotationComponent() {}

void RotationComponent::onCreate() {}

void RotationComponent::update() {
    if (auto entity = m_entity.lock()) {
        auto def = entity->rotate();
        def.z += 0.01f;
        entity->rotate(def);
    }
}
