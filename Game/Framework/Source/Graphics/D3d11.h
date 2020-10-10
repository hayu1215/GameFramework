#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

#include<d3d11.h>
#include<d3dcompiler.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class D3d11 {
public:
    D3d11() = delete;

    static bool Init(const HWND&);
    static void Clear();
    static void Present();
    static ID3D11Device* Device();
    static ID3D11DeviceContext* DeviceContext();
    static ID3D11DepthStencilView* DepthStencilView();

    //static void CreateVertexBuffer(unsigned int size, ID3D11Buffer** buffer, void* data = nullptr);
    //static void CreateIndexBuffer(unsigned int size, ID3D11Buffer** buffer, void* data = nullptr);

    //static ComPtr<ID3D11Buffer> CreateVertexBuffer(unsigned int size, void* data = nullptr);
    //static ComPtr<ID3D11Buffer> CreateIndexBuffer(unsigned int size, void* data = nullptr);

    static ID3D11Buffer* CreateVertexBuffer(unsigned int size, void* data = nullptr);
    static ID3D11Buffer* CreateIndexBuffer(unsigned int size, void* data = nullptr);

private:
    static HWND m_hWnd;
    static ComPtr<ID3D11Device> m_Device;
    static ComPtr<ID3D11DeviceContext> m_DeviceContext;
    static ComPtr<IDXGISwapChain> m_SwapChain;
    static ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
    static ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
    static ComPtr<ID3D11Texture2D> m_DepthStencil;
    static ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
    static ComPtr<ID3D11BlendState> m_BlendState;
    static ComPtr<ID3D11RasterizerState> m_RasterizerState;
};