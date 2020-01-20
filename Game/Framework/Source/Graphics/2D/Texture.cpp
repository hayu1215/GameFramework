#include"Texture.h"
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Utility/Judge.h>
#include<Framework/Include/Loader/TextureLoader/WICTextureLoader.h>

Texture::Texture() :
	m_ShaderResourceView(nullptr), m_Width(0), m_Height(0)
{}

Texture::Texture(const std::string &name)
{
	std::string file = "Application/Resource/Texture/" + name;
	std::wstring wname(file.begin(), file.end());
	ComPtr<ID3D11Resource> resource;
	HRESULT result = 0;

	result = DirectX::CreateWICTextureFromFile(D3d11::Device(), wname.c_str(), resource.GetAddressOf(), m_ShaderResourceView.GetAddressOf());
	utility::checkError(result, "TextureÇÃì«Ç›çûÇ›é∏îs");

	ComPtr<ID3D11Texture2D> texture2D;
	texture2D = static_cast<ID3D11Texture2D*>(resource.Get());

	D3D11_TEXTURE2D_DESC texDesc;
	texture2D->GetDesc(&texDesc);

	m_Width = texDesc.Width;
	m_Height = texDesc.Height;
}

Texture::~Texture()
{}

//std::pair<float, float> Texture::getSize()
//{
//	return std::make_pair(m_Width, m_Height);
//}

XMFLOAT2 Texture::getSize()
{
	return XMFLOAT2(m_Width, m_Height);
}

ComPtr<ID3D11ShaderResourceView> Texture::getShaderResourceView()
{
	return m_ShaderResourceView;
}