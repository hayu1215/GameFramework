#pragma once

#include<string>
#include<memory>
#include<unordered_map>
#include"IResource.h"
#include<Framework/Source/Utility/Template/DynamicSingleton.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/Shader/AShader.h>
//#include<Framework/Source/Graphics/Shader/TextureShader.h>
//#include<Framework/Source/Graphics/2D/Texture.h>

class Texture;
//class AShader;

class ResourceManager:public DynamicSingleton<ResourceManager>
{
private:
	ResourceManager();
	~ResourceManager();

public:
	friend class DynamicSingleton<ResourceManager>;
	template<class T>
	bool loadShader(const std::string &name);
	bool loadTexture(const std::string &name);
	AShader* findShader(const std::string &name);
	Texture* findTexture(const std::string &name);
	void clear();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	std::unordered_map<std::string, std::unique_ptr<AShader>>m_Shaders;
	std::unordered_map<std::string, std::unique_ptr<Texture>>m_Textures;
};

template<class T>
bool ResourceManager::loadShader(const std::string &name)
{
	if (utility::judgeBase<AShader, T>())
	{
		m_Shaders[name] = std::make_unique<T>(name);
		return true;
	}
	utility::debugLog(name + "ì«Ç›çûÇ›é∏îs");
	return false;
}