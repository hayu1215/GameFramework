#pragma once

#include<memory>
#include<string>
#include<Framework/Source/Application/Scene/Scene.h>
#include<Framework/Source/Graphics/2D/SpritebatchOld.h>
#include<Framework/Source/Graphics/2D/Camera.h>
#include<Framework/Source/Utility/Judge.h>

class TestScene : public Scene {
public:
    TestScene(const std::string name);
    ~TestScene();

    void start()override;
    void end()override;
};