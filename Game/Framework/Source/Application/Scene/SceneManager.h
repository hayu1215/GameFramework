#pragma once

#include<vector>
#include<unordered_map>
#include<memory>
#include<string>

class AScene;
class Entity;

class SceneManager
{
public:
	static void Change(const std::string&);
	static void Add(std::unique_ptr<AScene>);
	static void AddRemoveEntity(const std::weak_ptr<Entity>&);
	static void RemoveEntity();

private:
	static std::unordered_map<std::string, std::unique_ptr<AScene>> m_Scenes;
	static std::string m_CurrentName;
};