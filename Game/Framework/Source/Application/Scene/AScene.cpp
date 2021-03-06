#include"AScene.h"
#include<Framework/Source/Component/Entity.h>
#include<Framework/Source/Utility/Judge.h>

AScene::AScene(const std::string & name)
	:m_Name(name)
{
}

AScene::~AScene()
{
}

Entity * AScene::addEntity(std::shared_ptr<Entity>entitiy)
{
	Entity* pEntity = entitiy.get();
	m_Entities.push_back(std::move(entitiy));
	return pEntity;
}

void AScene::addRemoveEntity(const std::weak_ptr<Entity>& removeEntity)
{
	m_RemoveEntities.emplace_back(removeEntity);
}

void AScene::removeEntity()
{
	//順番逆でもいいかも
	//entityのcomponentの削除依頼を消化
	for (auto& v : m_Entities)
	{
		v->removeComponent();
	}
	//sceneのentityの削除依頼を消化
	for (auto& v : m_RemoveEntities)
	{
		m_Entities.remove_if([&](const std::weak_ptr<Entity>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_RemoveEntities.clear();
}

const std::string AScene::name()
{
	return m_Name;
}
