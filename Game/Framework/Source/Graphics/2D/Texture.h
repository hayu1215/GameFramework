#pragma once

#include<d3d11.h>
#include<wrl/client.h>
#include<string>
#include<Framework/Source/Graphics/D3d11.h>
#include<Framework/Source/Utility/Math/XMath.h>

//using namespace Microsoft::WRL;

class Texture
{
public:
	Texture();
	Texture(const std::string&);
	~Texture();

	void load(const std::string &name);
	XMFLOAT2 getSize();
	ComPtr<ID3D11ShaderResourceView> getShaderResourceView();

private:
	ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
	float m_width;
	float m_height;
};