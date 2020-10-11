#include"ResourceManager.h"
#include<Framework/Source/Graphics/2D/Texture.h>
#include<Framework/Source/Graphics/3D/Model.h>
#include<Framework/Source/Graphics/3D/Material.h>
#include<Framework/Source/Utility/Debug/Log.h>

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::m_Shaders = {};
std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::m_Textures = {};
std::unordered_map<std::string, std::shared_ptr<Model>> ResourceManager::m_Models = {};
std::unordered_map<std::string, std::shared_ptr<Material>> ResourceManager::m_Materials = {};

void ResourceManager::LoadTexture(const std::string & name) {
    if (m_Textures.count(name) > 0) {
        debug::Log("\"" + name + "\"" + " is loaded");
        return;
    }

    auto texture = std::make_unique<Texture>();
    try {
        texture->load(name);
    } catch (std::exception& e) {
        debug::Log(e.what());
        return;
    }

    m_Textures.emplace(name, std::move(texture));
}

void ResourceManager::LoadModel(const std::string & name) {
    if (m_Models.count(name) > 0) {
        debug::Log("\"" + name + "\"" + " is loaded");
        return;
    }

    auto model = std::make_unique<Model>();
    try {
        model->load(name);
    } catch (std::exception& e) {
        debug::Log(e.what());
        return;
    }

    m_Models.emplace(name, std::move(model));
}

void ResourceManager::LoadMaterial(const std::string & name) {
    if (m_Materials.count(name) > 0) {
        debug::Log("\"" + name + "\"" + " is loaded");
        return;
    }

    auto material = std::make_unique<Material>();
    try {
        material->load(name);
    } catch (std::exception& e) {
        debug::Log(e.what());
        return;
    }

    m_Materials.emplace(name, std::move(material));
}

std::weak_ptr<Shader> ResourceManager::GetShader(const std::string & name) {
#ifdef _DEBUG
    if (m_Shaders.count(name) == 0) {
        debug::Log("\"" + name + "\"" + " not found");
        assert(false && "Faild ResourceManager::GetShader");
    }
#endif
    return m_Shaders[name];
}

std::weak_ptr<Texture> ResourceManager::GetTexture(const std::string & name) {
#ifdef _DEBUG
    if (m_Textures.count(name) == 0) {
        debug::Log("\"" + name + "\"" + " not found");
        assert(false && "Faild ResourceManager::GetTexture");
    }
#endif
    return m_Textures[name];
}

std::weak_ptr<Model> ResourceManager::GetModel(const std::string & name) {
#ifdef _DEBUG
    if (m_Models.count(name) == 0) {
        debug::Log("\"" + name + "\"" + " not found");
        assert(false && "Faild ResourceManager::GetModel");
    }
#endif
    return m_Models[name];
}

std::weak_ptr<Material> ResourceManager::GetMaterial(const std::string & name) {
#ifdef _DEBUG
    if (m_Materials.count(name) == 0) {
        debug::Log("\"" + name + "\"" + " not found");
        assert(false && "Faild ResourceManager::GetMaterial");
    }
#endif
    return m_Materials[name];
}

void ResourceManager::Clear() {
    m_Shaders.clear();
    m_Textures.clear();
    m_Models.clear();
    m_Materials.clear();
}