#include"ResourceManager.h"
#include<Framework/Source/Graphics/2D/Texture.h>
#include<Framework/Source/Graphics/3D/Model.h>

std::unordered_map<std::string, std::unique_ptr<AShader>> ResourceManager::m_Shaders = {};
std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::m_Textures = {};
std::unordered_map<std::string, std::unique_ptr<Model>> ResourceManager::m_Models = {};

bool ResourceManager::LoadTexture(const std::string & name)
{
	m_Textures[name] = std::make_unique<Texture>(name);
	return true;
}

bool ResourceManager::LoadModel(const std::string & name)
{
	m_Models[name] = std::make_unique<Model>(name);
	return true;
}

AShader* ResourceManager::FindShader(const std::string & name)
{
	if (m_Shaders.count(name) == 0) return nullptr;
	return m_Shaders[name].get();
}

Texture* ResourceManager::FindTexture(const std::string & name)
{
	if (m_Textures.count(name) == 0) return nullptr;
	return m_Textures[name].get();
}

Model * ResourceManager::FindModel(const std::string & name)
{
	if (m_Models.count(name) == 0) return nullptr;
	return m_Models[name].get();
}

void ResourceManager::Clear()
{
	m_Shaders.clear();
	m_Textures.clear();
	m_Models.clear();
}