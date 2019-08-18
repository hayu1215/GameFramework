#pragma once

#include"SimpleShader.h"
#include<string>
#include<d3d11.h>
#include<Framework/Source/Utility/Math/Matrix4.h>
#include<Framework/Source/Utility/Math/Vector4.h>

class SpriteShader :public SimpleShader
{
	//シェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
	struct SIMPLESHADER_CONSTANT_BUFFER
	{
		Matrix4 mWVP;
		Vector4 vColor;
		Vector4 fAlpha;
		Vector4 vUv;
		//float fAlpha;
	};

public:
	SpriteShader();
	SpriteShader(std::string name);
	~SpriteShader()override;

	void passConstantBuffer(ID3D11DeviceContext*,const Matrix4&, float,const Vector4&)override;
	bool load(ID3D11Device*, const std::string&)override;
};