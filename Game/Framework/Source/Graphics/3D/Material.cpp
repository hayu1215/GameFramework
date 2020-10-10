#include"Material.h"
#include<algorithm>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<Framework/Source/Utility/Debug/Log.h>

Material::Material() {}

Material::Material(const std::string & name) {
    try {
        load(name);
    } catch (std::exception& e) {
        debug::Log(e.what());
    }
}

Material::~Material() {}

void Material::load(const std::string & name) {
    std::string file = "Application/Resource/Model/" + name;
    std::ifstream ifs(file);
    if (ifs.fail()) throw std::runtime_error("\"" + name + "\"" + " not found");

    std::string str;
    while (ifs >> str) {
        if (str == "Ka") {
            ifs >> m_ka.x >> m_ka.y >> m_ka.z;
        } else if (str == "Kd") {
            ifs >> m_kd.x >> m_kd.y >> m_kd.z;
        } else if (str == "Ks") {
            ifs >> m_ks.x >> m_ks.y >> m_ks.z;
        } else if (str == "Ns") {
            ifs >> m_ns;
        } else if (str == "Ni") {
            ifs >> m_ni;
        } else if (str == "d") {
            ifs >> m_d;
        } else if (str == "illum") {
            ifs >> m_illum;
        } else if (str == "map_Ka") {
            ifs >> m_mapKa;
        } else if (str == "map_Kd") {
            ifs >> m_mapKd;
        } else if (str == "map_Ks") {
            ifs >> m_mapKs;
        } else if (str == "map_Ns") {
            ifs >> m_mapNs;
        } else if (str == "map_d") {
            ifs >> m_mapD;
        } else if (str == "map_Bump") {
            ifs >> m_mapBump;
        }
    }
}

XMFLOAT4 Material::getColor() {
    return XMFLOAT4(m_kd.x, m_kd.y, m_kd.z, m_d);
}
