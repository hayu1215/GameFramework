#include "DestroyBoundaryComponent.h"

DestroyBoundaryComponent::DestroyBoundaryComponent() = default;

DestroyBoundaryComponent::~DestroyBoundaryComponent() = default;

void DestroyBoundaryComponent::update() {
    if (auto e = m_entity.lock()) {
        if (e->position().y < -300) e->destroy();
    }
}