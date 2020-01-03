#pragma once

//ヘッダーファイルのインクルード
#include<d3d11.h>
#include<d3dcompiler.h>
#include<wrl/client.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

using Microsoft::WRL::ComPtr;

class D3d11
{
public:
	D3d11() = delete;

	static bool Init(const HWND&);
	static void Clear();
	static void Present();
	static ID3D11Device* Device();
	static ID3D11DeviceContext* DeviceContext();
	static ID3D11DepthStencilView* DepthStencilView();

private:
	static HWND m_hWnd;
	static ComPtr<ID3D11Device>m_pDevice;
	static ComPtr<ID3D11DeviceContext>m_pDeviceContext;
	static ComPtr<IDXGISwapChain>m_pSwapChain;
	static ComPtr<ID3D11RenderTargetView>m_pRenderTargetView;
	static ComPtr<ID3D11DepthStencilView>m_pDepthStencilView;
	static ComPtr<ID3D11Texture2D>m_pDepthStencil;
	static ComPtr<ID3D11DepthStencilState>m_pDepthStencilState;
	static ComPtr<ID3D11BlendState>m_pBlendState;
	static ComPtr<ID3D11RasterizerState>m_pRasterizerState;
};