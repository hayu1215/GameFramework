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

	bool msaa = true;//�A���`�G�C���A�X�̃e�X�gMSAA
	if (!msaa)
	{
		//�X���b�v�`�F�[���̐錾
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		//�X���b�v�`�F�[���̒�`
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

		//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, 0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, m_pSwapChain.GetAddressOf(),
			m_pDevice.GetAddressOf(), pFeatureLevel, m_pDeviceContext.GetAddressOf());
		if (utility::checkError(result, "�f�o�C�X�ƃX���b�v�`�F�[���̍쐬���s"))return false;


		//�����_�[�^�[�Q�b�g�r���[�̍쐬
		//�o�b�N�o�b�t�@�[�̃|�C���^
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//�X���b�v�`�F�[������o�b�N�o�b�t�@�[�̃|�C���^���擾
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//�o�b�N�o�b�t�@�[��n���A����ɑ΂��郌���_�[�^�[�Q�b�g�r���[���쐬
		result = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
		if (utility::checkError(result, "�����_�[�^�[�Q�b�g�r���[�̍쐬���s"))return false;

		//�[�x�X�e���V���r���[�̐錾
		D3D11_TEXTURE2D_DESC descDepth;

		//�[�x�X�e���V���r���[�̒�`
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

		//�[�x�X�e���V���r���[�̍쐬
		result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), NULL, m_pDepthStencilView.GetAddressOf());
		if (utility::checkError(result, "�[�x�X�e���V���r���[�̍쐬���s"))return false;
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

		//�����_�[�^�[�Q�b�g�r���[�̍쐬
		//�o�b�N�o�b�t�@�[�̃|�C���^
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//�X���b�v�`�F�[������o�b�N�o�b�t�@�[�̃|�C���^���擾
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//�o�b�N�o�b�t�@�[��n���A����ɑ΂��郌���_�[�^�[�Q�b�g�r���[���쐬
		result = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_pRenderTargetView.GetAddressOf());
		if (utility::checkError(result, "�����_�[�^�[�Q�b�g�r���[�̍쐬���s"))return false;

		//�[�x�X�e���V���r���[�̐錾
		D3D11_TEXTURE2D_DESC descDepth;

		//�[�x�X�e���V���r���[�̒�`
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

		//�[�x�X�e���V���r���[�̍쐬
		result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &dsvDesc, m_pDepthStencilView.GetAddressOf());
		if (utility::checkError(result, "�[�x�X�e���V���r���[�̍쐬���s"))return false;
	}

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h
    m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	//Z�o�b�t�@�̖�����(��肽���Ȃ�)
	//m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);

	//�[�x�X�e���V���X�e�[�g���쐬
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dc.StencilEnable = false;

	result = m_pDevice->CreateDepthStencilState(&dc, m_pDepthStencilState.GetAddressOf());
	if (utility::checkError(result, "�[�x�X�e���V���X�e�[�g�̍쐬���s"))return false;

	//�[�x�X�e���V���X�e�[�g��K�p
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 0);

	//�r���[�|�[�g�̐錾
	D3D11_VIEWPORT vp;

	//�r���[�|�[�g�̒�`
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);

	//���X�^���C�Y�̐錾
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));

	//���X�^���C�Y�̒�`
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	//rdc.FillMode = D3D11_FILL_WIREFRAME;
	//rdc.FrontCounterClockwise = TRUE;

	//���X�^���C�Y�̍쐬
	result = m_pDevice->CreateRasterizerState(&rdc, m_pRasterizerState.GetAddressOf());
	if (utility::checkError(result, "���X�^���C�Y�̍쐬���s"))return false;

	//���X�^���C�Y�X�e�[�g�̃Z�b�g
	m_pDeviceContext->RSSetState(m_pRasterizerState.Get());

	//�A���t�@�u�����h�p�u�����h�X�e�[�g�쐬
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
	if (utility::checkError(result, "�A���t�@�u�����h�p�u�����h�X�e�[�g�̍쐬���s"))return false;

	UINT mask = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState.Get(), NULL, mask);

	return true;
}

void D3d11::clear()
{
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 1,1,1,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), ClearColor);//��ʃN���A
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);//�[�x�o�b�t�@�N���A
}

void D3d11::present()
{
	m_pSwapChain->Present(0, 0);//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
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