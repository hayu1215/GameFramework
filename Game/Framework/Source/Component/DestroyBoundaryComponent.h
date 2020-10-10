#pragma once

#include<Framework/Source/Component/UpdateComponent.h>

class DestroyBoundaryComponent : public UpdateComponent {
public:
    DestroyBoundaryComponent();
    ~DestroyBoundaryComponent();

    void update()override;
};