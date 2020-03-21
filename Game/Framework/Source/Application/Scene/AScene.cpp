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

//Entity * AScene::addEntity(std::shared_ptr<Entity>entitiy)
//{
//	Entity* pEntity = entitiy.get();
//	m_entities.push_back(std::move(entitiy));
//	return pEntity;
//}

void AScene::addRemoveEntity(const std::weak_ptr<Entity>& removeEntity)
{
	m_removeEntities.emplace_back(removeEntity);
}

void AScene::removeEntity()
{
	//‡”Ô‹t‚Å‚à‚¢‚¢‚©‚à
	//entity‚Ìcomponent‚ÌíœˆË—Š‚ğÁ‰»
	for (auto& v : m_entities)
	{
		v->removeComponent();
	}
	//scene‚Ìentity‚ÌíœˆË—Š‚ğÁ‰»
	for (auto& v : m_removeEntities)
	{
		m_entities.remove_if([&](const std::weak_ptr<Entity>& x) {return x.lock().get() == v.lock().get(); });
	}
	m_removeEntities.clear();
}

const std::string AScene::name()
{
	return m_name;
}
