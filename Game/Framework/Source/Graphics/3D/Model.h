#pragma once

#include<string>
#include<vector>
#include<memory>
#include<Framework/Source/Graphics/VertexType.h>

class Model
{
public:
	Model();
	Model(const std::string &name);
	~Model();

	std::vector<ObjVertex> getVertexes();
	std::vector<unsigned int> getIndexes();

private:
	std::vector<ObjVertex> m_Vertexes;
	std::vector<unsigned int> m_Indexes;
};