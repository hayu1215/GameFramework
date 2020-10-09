#include "Model.h"
#include<algorithm>
#include<fstream>
#include <sstream>
#include<iostream>
#include <string>
#include<array>
#include<Framework/Source/Utility/Debug/Log.h>
#include<Framework/Source/Utility/Judge.h>

Model::Model()
{
}

Model::Model(const std::string & name)
{
	try
	{
		load(name);
	}
	catch (std::exception& e)
	{
		debug::Log(e.what());
	}
}

Model::~Model()
{
}

void Model::load(const std::string &name)
{
	std::string file = "Application/Resource/Model/" + name;
	std::ifstream ifs(file);
	if (ifs.fail()) throw std::runtime_error("\"" + name + "\"" + " not found");

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
	m_indexCount = fSize * fvCnt;
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
	auto indexes = std::vector<uint16_t>(fSize * fvCnt);
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
				indexes[fCnt] = std::stoi(v) - 1;

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

	auto vertexes = std::vector<ObjVertex>(vSize);
	for (unsigned char i = 0; i < faces.size(); ++i)
	{
		vertexes[faces[i].x].pos = poss[faces[i].x];
		vertexes[faces[i].x].uv = uvs[faces[i].y];
		vertexes[faces[i].x].normal = normals[faces[i].z];
	}

	D3D11_BUFFER_DESC desc1;
	desc1.Usage = D3D11_USAGE_DEFAULT;
	desc1.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc1.ByteWidth = vertexes.size() * sizeof(ObjVertex);
	desc1.CPUAccessFlags = 0;
	desc1.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData1;
	initData1.pSysMem = vertexes.data();
	initData1.SysMemPitch = desc1.ByteWidth;
	auto result1 = D3d11::Device()->CreateBuffer(&desc1, &initData1, m_vertexBuffer.GetAddressOf());
	utility::CheckError(result1, "バーテックスバッファーの作成失敗");

	D3D11_BUFFER_DESC desc2;
	desc2.Usage = D3D11_USAGE_DEFAULT;
	desc2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc2.ByteWidth = indexes.size() * sizeof(uint16_t);
	desc2.CPUAccessFlags = 0;
	desc2.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData2;
	initData2.pSysMem = indexes.data();
	initData2.SysMemPitch = desc2.ByteWidth;
	auto result2 = D3d11::Device()->CreateBuffer(&desc2, &initData2, m_indexBuffer.GetAddressOf());
	utility::CheckError(result2, "インデックスバッファーの作成失敗");
}

ComPtr<ID3D11Buffer> Model::getVertexBuffer()
{
	return m_vertexBuffer;
}

ComPtr<ID3D11Buffer> Model::getIndexBuffer()
{
	return m_indexBuffer;
}

unsigned int Model::getIndexCount()
{
	return m_indexCount;
}
