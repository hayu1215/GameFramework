#include"AScene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>

AScene::AScene(const std::string & name)
	:m_name(name)
{
}

AScene::~AScene()
{
}

const std::string AScene::name()
{
	return m_name;
}
