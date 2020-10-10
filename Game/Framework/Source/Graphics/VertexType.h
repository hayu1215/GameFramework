#pragma once

#include<Framework/Source/Utility/Math/XMath.h>

struct Vertex {
    XMFLOAT3 pos;
};

struct SimpleVertex {
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct ObjVertex {
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT3 normal;
};

//namespace vertex
//{
//	struct P
//	{
//		XMFLOAT3 pos;
//	};
//
//	struct Pc
//	{
//		XMFLOAT3 pos;
//		XMFLOAT4 color;
//	};
//
//	struct Pun
//	{
//		XMFLOAT3 pos;
//		XMFLOAT2 uv;
//		XMFLOAT3 normal;
//	};
//}