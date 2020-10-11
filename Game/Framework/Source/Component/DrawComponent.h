#pragma once

#include"Component.h"
#include<memory>
#include<Framework/Source/Component/Entity.h>

class DrawComponent : public Component {
public:
    DrawComponent();
    ~DrawComponent();

    virtual void draw() = 0;
    void active()override;
    void deActive()override;
};