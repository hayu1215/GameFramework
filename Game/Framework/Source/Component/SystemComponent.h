#pragma once

#include"Component.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class SystemComponent : public Component {
public:
    SystemComponent();
    ~SystemComponent();

    virtual void update() = 0;
};