#pragma once

//ヘッダーファイルのインクルード
#include<d3d11.h>
#include<d3dcompiler.h>
#include<wrl/client.h>
#include<Framework/Source/Utility/Template/DynamicSingleton.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

using namespace Microsoft::WRL;

//とりあえず、動的にインスタンス生成するシングルトンを使う
class D3d11:public DynamicSingleton<D3d11>
{
private:
	D3d11();
	~D3d11();

public:
	friend class DynamicSingleton<D3d11>;
	bool init(const HWND&);
	void clear();
	void present();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	ID3D11DepthStencilView* getDepthStencilView();

	D3d11(const D3d11&) = delete;
	D3d11& operator=(const D3d11&) = delete;
	D3d11(D3d11&&) = delete;
	D3d11& operator=(D3d11&&) = delete;

private:
	HWND m_hWnd;
	ComPtr<ID3D11Device>m_pDevice;
	ComPtr<ID3D11DeviceContext>m_pDeviceContext;
	ComPtr<IDXGISwapChain>m_pSwapChain;
	ComPtr<ID3D11RenderTargetView>m_pRenderTargetView;
	ComPtr<ID3D11DepthStencilView>m_pDepthStencilView;
	ComPtr<ID3D11Texture2D>m_pDepthStencil;
	ComPtr<ID3D11DepthStencilState>m_pDepthStencilState;
	ComPtr<ID3D11BlendState>m_pBlendState;
	ComPtr<ID3D11RasterizerState>m_pRasterizerState;
};