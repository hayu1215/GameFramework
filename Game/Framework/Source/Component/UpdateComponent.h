#pragma once

#include"Component.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class UpdateComponent : public Component {
public:
    UpdateComponent();
    ~UpdateComponent();

    virtual void update() = 0;
    void active()override;
    void deActive()override;
};