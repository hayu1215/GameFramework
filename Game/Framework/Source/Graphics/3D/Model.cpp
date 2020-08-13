#include "Model.h"
#include<algorithm>
#include<fstream>
#include <sstream>
#include<iostream>
#include <string>
#include<Framework/Source/Utility/Debug/Log.h>

Model::Model()
{
}

Model::Model(const std::string & name)
{
	std::string file = "Application/Resource/Model/" + name;
	std::ifstream ifs(file);
	if (ifs.fail()) return;

	std::string str;
	unsigned int vSize = 0;
	unsigned int vtSize = 0;
	unsigned int vnSize = 0;
	unsigned int fSize = 0;
	unsigned int fvCnt = 0;
	while (std::getline(ifs, str))
	{
		std::string header = { str[0], str[1] };
		if (header == "v ")
		{
			++vSize;
		}
		else if (header == "vt")
		{
			++vtSize;
		}
		else if (header == "vn")
		{
			++vnSize;
		}
		else if (header == "f ")
		{
			if (fSize == 0) fvCnt = std::count(str.begin(), str.end(), ' ');
			++fSize;
		}
	}
	m_Vertexes.resize(vSize);
	m_Indexes.resize(fSize * fvCnt);
	ifs.clear();
	ifs.seekg(0, std::ios_base::beg);

	unsigned int vCnt = 0;
	unsigned int vtCnt = 0;
	unsigned int vnCnt = 0;
	unsigned int fCnt = 0;
	auto poss = std::vector<XMFLOAT3>(vSize);
	auto uvs = std::vector<XMFLOAT2>(vtSize);
	auto normals = std::vector<XMFLOAT3>(vnSize);
	auto faces = std::vector<XMFLOAT3>(fSize * fvCnt);
	while (ifs >> str)
	{
		if (str == "v")
		{
			XMFLOAT3 v;
			ifs >> v.x >> v.y >> v.z;
			poss[vCnt] = v;
			++vCnt;
		}
		else if (str == "vt")
		{
			XMFLOAT2 v;
			ifs >> v.x >> v.y;
			uvs[vtCnt] = v;
			++vtCnt;
		}
		else if (str == "vn")
		{
			XMFLOAT3 v;
			ifs >> v.x >> v.y >> v.z;
			normals[vnCnt] = v;
			++vnCnt;
		}
		else if (str == "f")
		{
			for (unsigned char i = 0; i < fvCnt; ++i)
			{
				std::string s;
				ifs >> s;
				std::stringstream ss(s);

				std::string v;
				std::getline(ss, v, '/');
				faces[fCnt].x = std::stoi(v) - 1;
				m_Indexes[fCnt] = std::stoi(v) - 1;

				std::string u;
				std::getline(ss, u, '/');
				faces[fCnt].y = std::stoi(u) - 1;

				std::string n;
				std::getline(ss, n, '/');
				faces[fCnt].z = std::stoi(n) - 1;

				++fCnt;
			}
		}
	}

	//for (unsigned char i = 0; i < vCnt; ++i)
	//{
	//	m_Vertexes[i].pos = poss[i];
	//	m_Vertexes[i].uv = uvs[faces[i].y];
	//	m_Vertexes[i].normal = normals[faces[i].z];
	//}

	for (unsigned char i = 0; i < faces.size(); ++i)
	{
		m_Vertexes[faces[i].x].pos = poss[faces[i].x];
		m_Vertexes[faces[i].x].uv = uvs[faces[i].y];
		m_Vertexes[faces[i].x].normal = normals[faces[i].z];
	}

	for (const auto& x : m_Vertexes)
	{
		debug::Log("pos x : " + std::to_string(x.pos.x) + " y : " + std::to_string(x.pos.y) + " z : " + std::to_string(x.pos.z));
		debug::Log("uv x : " + std::to_string(x.uv.x) + " y : " + std::to_string(x.uv.y));
		debug::Log("normal x : " + std::to_string(x.normal.x) + " y : " + std::to_string(x.normal.y) + " z : " + std::to_string(x.normal.z));
	}
	for (const auto& x : m_Indexes)
	{
		debug::Log("index : " + std::to_string(x));
	}
}

Model::~Model()
{
}

std::vector<ObjVertex> Model::getVertexes()
{
	return m_Vertexes;
}

std::vector<unsigned int> Model::getIndexes()
{
	return m_Indexes;
}
