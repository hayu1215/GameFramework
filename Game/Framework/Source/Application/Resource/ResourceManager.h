#pragma once

#include<string>
#include<memory>
#include<unordered_map>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/Shader/AShader.h>

class Texture;

class ResourceManager
{
public:
	ResourceManager() = delete;

	template<class T>
	static bool LoadShader(const std::string &name);
	static bool LoadTexture(const std::string &name);
	static AShader* FindShader(const std::string &name);
	static Texture* FindTexture(const std::string &name);
	static void Clear();

private:
	static std::unordered_map<std::string, std::unique_ptr<AShader>>m_Shaders;
	static std::unordered_map<std::string, std::unique_ptr<Texture>>m_Textures;
};

template<class T>
bool ResourceManager::LoadShader(const std::string &name)
{
	if (utility::judgeBase<AShader, T>())
	{
		m_Shaders[name] = std::make_unique<T>(name);
		return true;
	}
	utility::debugLog(name + "読み込み失敗");
	return false;
}