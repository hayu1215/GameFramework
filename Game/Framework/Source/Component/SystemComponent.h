#pragma once

#include"AComponent.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class SystemComponent : public AComponent {
public:
    SystemComponent();
    ~SystemComponent();

    virtual void update() = 0;
};