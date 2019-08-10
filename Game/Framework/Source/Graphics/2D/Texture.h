#pragma once

#include<d3d11.h>
#include<wrl/client.h>
#include<string>
#include<Framework/Source/Device/D3d11.h>
#include<Framework/Source/Utility/Math/Vector2.h>

using namespace Microsoft::WRL;

class Texture
{
public:
	Texture();
	Texture(const std::string&);
	~Texture();

	//std::pair<float, float> getSize();
	Vector2 getSize();
	ComPtr<ID3D11ShaderResourceView> getShaderResourceView();

private:
	ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
	float m_Width;
	float m_Height;
};