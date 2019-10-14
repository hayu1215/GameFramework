#include"ResourceManager.h"
#include<Framework/Source/Graphics/2D/Texture.h>
#include<Framework/Source/Graphics/Shader/AShader.h>

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

bool ResourceManager::loadTexture(const std::string & name)
{
	m_Textures[name] = std::make_unique<Texture>(name);
	return true;
}

AShader* ResourceManager::findShader(const std::string & name)
{
	if (m_Shaders.count(name) == 0)return nullptr;
	return m_Shaders[name].get();
}

Texture* ResourceManager::findTexture(const std::string & name)
{
	if (m_Textures.count(name) == 0)return nullptr;
	return m_Textures[name].get();
}

void ResourceManager::clear()
{
	m_Shaders.clear();
	m_Textures.clear();
}