#pragma once

#include<memory>
#include<string>
#include<Framework/Source/Graphics/2D/SpritebatchOld.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Application/Scene/Scene.h>

class Title : public Scene {
public:
    Title(const std::string name);
    ~Title();

    void start()override;
    void end()override;
};