#include "Title.h"
#include<Framework/Source/Device/DeviceLocator.h>
#include<Framework/Source/Component/Entity.h>
#include<Source/Component/TestComponent.h>
#include<Framework/Source/Component/Physics/Box2D/B2WorldComponent.h>
#include<Framework/Source/Component/Physics/Box2D/B2BoxComponent.h>
#include<Framework/Source/Component/Physics/Box2D/B2PolygonComponent.h>
#include<Framework/Source/Component/Physics/Box2D/B2ParticleComponent.h>
#include<Framework/Source/Component/CameraComponent.h>
#include<Framework/Source/Component/Graphics/MeshComponent.h>
#include<Framework/Source/Component/Graphics/ModelComponent.h>
#include<Framework/Source/Component/Graphics/LineComponent.h>
#include<Framework/Source/Component/Graphics/RegularPolygonComponent.h>
#include<Framework/Source/Component/Graphics/MeshRendererComponent.h>
#include<Framework/Source/Graphics/3D/Model.h>
#include<Framework/Source/Graphics/3D/Material.h>
#include<Application/Source/Component/RotationComponent.h>

Title::Title(const std::string name)
    : Scene(name) {}

Title::~Title() {}

void Title::start() {
    auto camera = Entity::Add(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), "camera", "camera1");
    camera->addComponent<CameraComponent>(true);

    auto b2world = Entity::Add(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), "b2world", "b2world1");
    b2world->addComponent<B2WorldComponent>(true, XMFLOAT2(0, -40));

    ////for (int i = 0; i < 11; ++i) 
    ////{
    ////	for (int j = 0; j < 10; ++j)
    ////	{
    ////		//auto obj1 = Entity::Add(XMFLOAT3(-100 + i * 20, 100 + j * 20, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(20, 20, 1), "", "");
    ////		//obj1->addComponent<MeshRendererComponent>(true);
    ////		//obj1->addComponent<RegularPolygonComponent>(true, 5, XMFLOAT4(0.0f, 0.5f, 0.5f, 0.5f));
    ////		//obj1->addComponent<B2PolygonComponent>(true, false);

    ////		auto obj2 = Entity::Add(XMFLOAT3(-100 + i * 20, 100 + j * 20, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(20, 20, 1), "", "");
    ////		obj2->addComponent<MeshRendererComponent>(true);
    ////		obj2->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(0.0f, 1.0f, 1.0f, 0.5f));
    ////		obj2->addComponent<B2BoxComponent>(true, b2world, false);
    ////	}
    ////}

    //auto p = Entity::Add(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), "", "");
    //p->addComponent<MeshRendererComponent>(true);
    //p->addComponent<B2ParticleComponent>(true, b2world);

    ////auto base = Entity::Add(XMFLOAT3(0, -200, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(300, 10, 1), "", "");
    ////base->addComponent<MeshRendererComponent>(true);
    ////base->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
    ////base->addComponent<B2BoxComponent>(true, b2world, true);

    //auto stage = Entity::Add(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), "stage", "stage");
    //	auto right = stage->addCild(XMFLOAT3(-150, 0, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(10, 300, 0), "box", "right");
    //		right->addComponent<MeshRendererComponent>(true);
    //		right->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
    //		right->addComponent<B2BoxComponent>(true, b2world, true);
    //	auto left = stage->addCild(XMFLOAT3(150, 0, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(10, 300, 0), "box", "left");
    //		left->addComponent<MeshRendererComponent>(true);
    //		left->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
    //		left->addComponent<B2BoxComponent>(true, b2world, true);
    //	auto top = stage->addCild(XMFLOAT3(0, 150, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(300, 10, 1), "box", "bottom");
    //		top->addComponent<MeshRendererComponent>(true);
    //		top->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
    //		top->addComponent<B2BoxComponent>(true, b2world, true);
    //	auto bottom = stage->addCild(XMFLOAT3(0, -150, 1), XMFLOAT3(0, 0, 0), XMFLOAT3(300, 10, 1), "box", "bottom");
    //		bottom->addComponent<MeshRendererComponent>(true);
    //		bottom->addComponent<RegularPolygonComponent>(true, 4, XMFLOAT4(1.0f, 0.0f, 1.0f, 0.5f));
    //		bottom->addComponent<B2BoxComponent>(true, b2world, true);

    //for (unsigned int i = 0; i < 100; ++i)
    //{
    //	for (unsigned int j = 0; j < 100; ++j)
    //	{
    //		auto test = Entity::Add(XMFLOAT3(20.0f * i, 20.0f * j, 0), XMFLOAT3(0, 0, i * j), XMFLOAT3(10, 10, 1), "test", "test");
    //		test->addComponent<MeshRendererComponent>(true);
    //		test->addComponent<ModelComponent>(true, "mesh");
    //	}
    //}

    //int pos1 = -400;
    //for (int i = 0; i < 100; i++)
    //{
    //	auto sphere = Entity::Add(XMFLOAT3(pos1, 200, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(20, 20, 1), "test", "test");
    //	sphere->addComponent<MeshRendererComponent>(true);
    //	sphere->addComponent<ModelComponent>(true, "ico_sphere");
    //	sphere->addComponent<RotationComponent>(true);
    //	pos1 += 8;
    //}

    //int pos2 = -400;
    //for (int i = 0; i < 100; i++)
    //{
    //	auto mesh = Entity::Add(XMFLOAT3(pos2, -200, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(14, 14, 1), "test", "test");
    //	mesh->addComponent<MeshRendererComponent>(true);
    //	mesh->addComponent<ModelComponent>(true, "mesh");
    //	mesh->addComponent<RotationComponent>(true);
    //	pos2 += 8;
    //}

    int posx = -400;
    for (int i = 0; i < 25; i++) {
        int posy = -300;
        for (int j = 0; j < 25; j++) {
            auto mesh = Entity::Add(XMFLOAT3(posx, posy, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(25, 25, 1), "test", "test");
            mesh->addComponent<MeshRendererComponent>(true);
            mesh->addComponent<ModelComponent>(true, "mesh");
            mesh->addComponent<RotationComponent>(true);
            posy += 24;
        }
        posx += 32;
    }
}

void Title::end() {}