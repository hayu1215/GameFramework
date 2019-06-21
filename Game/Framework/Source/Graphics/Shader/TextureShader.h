#pragma once

#include"SimpleShader.h"
#include<string>
#include<d3d11.h>
#include<Framework/Source/Utility/Math/Matrix4.h>
#include<Framework/Source/Utility/Math/Vector4.h>

class TextureShader :public SimpleShader
{
	//�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
	struct SIMPLESHADER_CONSTANT_BUFFER
	{
		Matrix4 mWVP;
		Vector4 vColor;
		Vector4 fAlpha;
		Vector4 vUv;
		//float fAlpha;
	};

public:
	TextureShader();
	TextureShader(std::string name);
	~TextureShader()override;

	void passConstantBuffer(ID3D11DeviceContext*,const Matrix4&, float,const Vector4&)override;
	bool load(ID3D11Device*, const std::string&)override;
};