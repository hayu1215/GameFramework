#pragma once

#include<string>
#include<memory>
#include<unordered_map>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Source/Graphics/Shader/Shader.h>
#include<Framework/Source/Graphics/VertexType.h>
#include<Framework/Source/Utility/Debug/Log.h>

class Texture;
class Model;
class Material;

class ResourceManager {
public:
    ResourceManager() = delete;

    template<class T>
    static void LoadShader(const std::string& name);
    static void LoadTexture(const std::string& name);
    static void LoadModel(const std::string& name);
    static void LoadMaterial(const std::string& name);
    static std::weak_ptr<Shader> GetShader(const std::string& name);
    static std::weak_ptr<Texture> GetTexture(const std::string& name);
    static std::weak_ptr<Model> GetModel(const std::string& name);
    static std::weak_ptr<Material> GetMaterial(const std::string& name);
    static void Clear();

private:
    static std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    static std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
    static std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
};

template<class T>
void ResourceManager::LoadShader(const std::string &name) {
#ifdef _DEBUG
    if (!utility::JudgeBase<Shader, T>()) {
        std::string type = typeid(T).name();
        debug::Log("\"" + type + "\"" + "is not Shader");
        return;
    }
#endif

    if (m_Shaders.count(name) > 0) {
        debug::Log("\"" + name + "\"" + " is loaded");
        return;
    }

    auto shader = std::make_unique<T>();
    try {
        shader->load(name);
    } catch (std::exception& e) {
        debug::Log(e.what());
        return;
    }

    m_Shaders.emplace(name, std::move(shader));
}