#pragma once

#include<string>
#include<vector>
#include<memory>
#include<Framework/Source/Graphics/VertexType.h>

class Material
{
public:
	Material();
	Material(const std::string &name);
	~Material();

	void load(const std::string &name);
	XMFLOAT4 getColor();

private:
	float m_ns = 0;
	float m_ni = 0;
	float m_d = 0;
	unsigned int m_illum = 0;
	XMFLOAT3 m_ka = XMFLOAT3(1, 1, 1);
	XMFLOAT3 m_kd = XMFLOAT3(1, 1, 1);
	XMFLOAT3 m_ks = XMFLOAT3(0, 0, 0);
	std::string m_mapKa = "";
	std::string m_mapKd = "";
	std::string m_mapKs = "";
	std::string m_mapNs = "";
	std::string m_mapD = "";
	std::string m_mapBump = "";
};