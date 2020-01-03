#include"D3d11.h"
#include<dxgi1_2.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Utility/Judge.h>

D3d11::D3d11() = default;
D3d11::~D3d11() = default;

bool D3d11::init(const HWND &pcd)
{
	m_hWnd = pcd;
	HRESULT result = 0;

	bool msaa = true;//アンチエイリアスのテストMSAA
	if (!msaa)
	{
		//スワップチェーンの宣言
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		//スワップチェーンの定義
		sd.BufferCount = 1;
		sd.BufferDesc.Width = WINDOW_WIDTH;
		sd.BufferDesc.Height = WINDOW_HEIGHT;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
		D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

		//デバイスとスワップチェーンの作成
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, 0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, m_pSwapChain.GetAddressOf(),
			m_pDevice.GetAddressOf(), pFeatureLevel, m_pDeviceContext.GetAddressOf());
		if (utility::checkError(result, "デバイスとスワップチェーンの作成失敗"))return false;


		//レンダーターゲットビューの作成
		//バックバッファーのポインタ
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//スワップチェーンからバックバッファーのポインタを取得
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//バックバッファーを渡し、それに対するレンダーターゲットビューを作成
		result = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
		if (utility::checkError(result, "レンダーターゲットビューの作成失敗"))return false;

		//深度ステンシルビューの宣言
		D3D11_TEXTURE2D_DESC descDepth;

		//深度ステンシルビューの定義
		descDepth.Width = WINDOW_WIDTH;
		descDepth.Height = WINDOW_HEIGHT;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		m_pDevice->CreateTexture2D(&descDepth, NULL, m_pDepthStencil.GetAddressOf());

		//深度ステンシルビューの作成
		result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), NULL, m_pDepthStencilView.GetAddressOf());
		if (utility::checkError(result, "深度ステンシルビューの作成失敗"))return false;
	}
	else 
	{
		D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
		D3D11CreateDevice(
			nullptr, // Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			&pFeatureLevels,
			1,
			D3D11_SDK_VERSION, // UWP apps must set this to D3D11_SDK_VERSION.
			m_pDevice.GetAddressOf(), // Returns the Direct3D device created.
			nullptr,
			m_pDeviceContext.GetAddressOf() // Returns the device immediate context.
		);

		DXGI_SAMPLE_DESC sampleDesc = {};
		for (int i = 1; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i <<= 1)
		{
			UINT Quality;
			if (SUCCEEDED(m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality)))
			{
				if (0 < Quality)
				{
					sampleDesc.Count = i;
					sampleDesc.Quality = Quality - 1;
				}
			}
		}

		ComPtr<IDXGIDevice1> dxgiDevice;
		m_pDevice.As(&dxgiDevice);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory> dxgiFactory;
		dxgiAdapter->GetParent(
			__uuidof(IDXGIFactory2),
			&dxgiFactory
		);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = WINDOW_WIDTH;
		sd.BufferDesc.Height = WINDOW_HEIGHT;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_hWnd;
		sd.SampleDesc = sampleDesc;
		sd.Windowed = TRUE;
		dxgiFactory->CreateSwapChain(
			m_pDevice.Get(),
			&sd,
			m_pSwapChain.GetAddressOf()
		);

		//レンダーターゲットビューの作成
		//バックバッファーのポインタ
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//スワップチェーンからバックバッファーのポインタを取得
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//バックバッファーを渡し、それに対するレンダーターゲットビューを作成
		result = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
		if (utility::checkError(result, "レンダーターゲットビューの作成失敗"))return false;

		//深度ステンシルビューの宣言
		D3D11_TEXTURE2D_DESC descDepth;

		//深度ステンシルビューの定義
		descDepth.Width = WINDOW_WIDTH;
		descDepth.Height = WINDOW_HEIGHT;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc = sampleDesc;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = descDepth.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		dsvDesc.Flags = 0;
		dsvDesc.Texture2D.MipSlice = 0;

		m_pDevice->CreateTexture2D(&descDepth, NULL, m_pDepthStencil.GetAddressOf());

		//深度ステンシルビューの作成
		result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &dsvDesc, m_pDepthStencilView.GetAddressOf());
		if (utility::checkError(result, "深度ステンシルビューの作成失敗"))return false;
	}

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
    m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	//Zバッファの無効化(やりたくない)
	//m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);

	//深度ステンシルステートを作成
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dc.StencilEnable = false;

	result = m_pDevice->CreateDepthStencilState(&dc, m_pDepthStencilState.GetAddressOf());
	if (utility::checkError(result, "深度ステンシルステートの作成失敗"))return false;

	//深度ステンシルステートを適用
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 0);

	//ビューポートの宣言
	D3D11_VIEWPORT vp;

	//ビューポートの定義
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);

	//ラスタライズの宣言
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));

	//ラスタライズの定義
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	//rdc.FillMode = D3D11_FILL_WIREFRAME;
	//rdc.FrontCounterClockwise = TRUE;

	//ラスタライズの作成
	result = m_pDevice->CreateRasterizerState(&rdc, m_pRasterizerState.GetAddressOf());
	if (utility::checkError(result, "ラスタライズの作成失敗"))return false;

	//ラスタライズステートのセット
	m_pDeviceContext->RSSetState(m_pRasterizerState.Get());

	//アルファブレンド用ブレンドステート作成
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = m_pDevice->CreateBlendState(&bd, m_pBlendState.GetAddressOf());
	if (utility::checkError(result, "アルファブレンド用ブレンドステートの作成失敗"))return false;

	UINT mask = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState.Get(), NULL, mask);

	return true;
}

void D3d11::clear()
{
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 1,1,1,1 };// クリア色作成　RGBAの順
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), ClearColor);//画面クリア
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア
}

void D3d11::present()
{
	m_pSwapChain->Present(0, 0);//画面更新（バックバッファをフロントバッファに）
}

ID3D11Device* D3d11::getDevice()
{
	return m_pDevice.Get();
}

ID3D11DeviceContext* D3d11::getDeviceContext()
{
	return m_pDeviceContext.Get();
}

ID3D11DepthStencilView* D3d11::getDepthStencilView()
{
	return m_pDepthStencilView.Get();
}