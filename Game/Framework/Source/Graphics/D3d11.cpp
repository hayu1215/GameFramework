#include"D3d11.h"
#include<dxgi1_2.h>
#include<Framework/Source/Utility/Constant.h>
#include<Framework/Source/Utility/Judge.h>

HWND D3d11::m_hWnd = 0;
ComPtr<ID3D11Device> D3d11::m_Device = nullptr;
ComPtr<ID3D11DeviceContext> D3d11::m_DeviceContext = nullptr;
ComPtr<IDXGISwapChain> D3d11::m_SwapChain = nullptr;
ComPtr<ID3D11RenderTargetView> D3d11::m_RenderTargetView = nullptr;
ComPtr<ID3D11DepthStencilView> D3d11::m_DepthStencilView = nullptr;
ComPtr<ID3D11Texture2D> D3d11::m_DepthStencil = nullptr;
ComPtr<ID3D11DepthStencilState> D3d11::m_DepthStencilState = nullptr;
ComPtr<ID3D11BlendState> D3d11::m_BlendState = nullptr;
ComPtr<ID3D11RasterizerState> D3d11::m_RasterizerState = nullptr;

bool D3d11::Init(const HWND &pcd)
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
			NULL, 0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(), pFeatureLevel, m_DeviceContext.GetAddressOf());
		if (utility::CheckError(result, "�f�o�C�X�ƃX���b�v�`�F�[���̍쐬���s"))return false;


		//�����_�[�^�[�Q�b�g�r���[�̍쐬
		//�o�b�N�o�b�t�@�[�̃|�C���^
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//�X���b�v�`�F�[������o�b�N�o�b�t�@�[�̃|�C���^���擾
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//�o�b�N�o�b�t�@�[��n���A����ɑ΂��郌���_�[�^�[�Q�b�g�r���[���쐬
		result = m_Device->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
		if (utility::CheckError(result, "�����_�[�^�[�Q�b�g�r���[�̍쐬���s"))return false;

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

		m_Device->CreateTexture2D(&descDepth, NULL, m_DepthStencil.GetAddressOf());

		//�[�x�X�e���V���r���[�̍쐬
		result = m_Device->CreateDepthStencilView(m_DepthStencil.Get(), NULL, m_DepthStencilView.GetAddressOf());
		if (utility::CheckError(result, "�[�x�X�e���V���r���[�̍쐬���s"))return false;
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
			m_Device.GetAddressOf(), // Returns the Direct3D device created.
			nullptr,
			m_DeviceContext.GetAddressOf() // Returns the device immediate context.
		);

		DXGI_SAMPLE_DESC sampleDesc = {};
		for (int i = 1; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i <<= 1)
		{
			UINT Quality;
			if (SUCCEEDED(m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality)))
			{
				if (0 < Quality)
				{
					sampleDesc.Count = i;
					sampleDesc.Quality = Quality - 1;
				}
			}
		}

		ComPtr<IDXGIDevice1> dxgiDevice;
		m_Device.As(&dxgiDevice);

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
			m_Device.Get(),
			&sd,
			m_SwapChain.GetAddressOf()
		);

		//�����_�[�^�[�Q�b�g�r���[�̍쐬
		//�o�b�N�o�b�t�@�[�̃|�C���^
		ComPtr<ID3D11Texture2D>pBackBuffer;

		//�X���b�v�`�F�[������o�b�N�o�b�t�@�[�̃|�C���^���擾
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

		//�o�b�N�o�b�t�@�[��n���A����ɑ΂��郌���_�[�^�[�Q�b�g�r���[���쐬
		result = m_Device->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
		if (utility::CheckError(result, "�����_�[�^�[�Q�b�g�r���[�̍쐬���s"))return false;

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

		m_Device->CreateTexture2D(&descDepth, NULL, m_DepthStencil.GetAddressOf());

		//�[�x�X�e���V���r���[�̍쐬
		result = m_Device->CreateDepthStencilView(m_DepthStencil.Get(), &dsvDesc, m_DepthStencilView.GetAddressOf());
		if (utility::CheckError(result, "�[�x�X�e���V���r���[�̍쐬���s"))return false;
	}

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h
    m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	//Z�o�b�t�@�̖�����(��肽���Ȃ�)
	//m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL);

	//�[�x�X�e���V���X�e�[�g���쐬
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dc.StencilEnable = false;

	result = m_Device->CreateDepthStencilState(&dc, m_DepthStencilState.GetAddressOf());
	if (utility::CheckError(result, "�[�x�X�e���V���X�e�[�g�̍쐬���s"))return false;

	//�[�x�X�e���V���X�e�[�g��K�p
	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);

	//�r���[�|�[�g�̐錾
	D3D11_VIEWPORT vp;

	//�r���[�|�[�g�̒�`
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &vp);

	//���X�^���C�Y�̐錾
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));

	//���X�^���C�Y�̒�`
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	//rdc.FillMode = D3D11_FILL_WIREFRAME;
	//rdc.FrontCounterClockwise = TRUE;

	//���X�^���C�Y�̍쐬
	result = m_Device->CreateRasterizerState(&rdc, m_RasterizerState.GetAddressOf());
	if (utility::CheckError(result, "���X�^���C�Y�̍쐬���s"))return false;

	//���X�^���C�Y�X�e�[�g�̃Z�b�g
	m_DeviceContext->RSSetState(m_RasterizerState.Get());

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

	result = m_Device->CreateBlendState(&bd, m_BlendState.GetAddressOf());
	if (utility::CheckError(result, "�A���t�@�u�����h�p�u�����h�X�e�[�g�̍쐬���s"))return false;

	UINT mask = 0xffffffff;
	m_DeviceContext->OMSetBlendState(m_BlendState.Get(), NULL, mask);

	return true;
}

void D3d11::Clear()
{
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 1,1,1,1 };// �N���A�F�쐬�@RGBA�̏�
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), ClearColor);//��ʃN���A
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);//�[�x�o�b�t�@�N���A
}

void D3d11::Present()
{
	m_SwapChain->Present(0, 0);//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
}

ID3D11Device* D3d11::Device()
{
	return m_Device.Get();
}

ID3D11DeviceContext* D3d11::DeviceContext()
{
	return m_DeviceContext.Get();
}

ID3D11DepthStencilView* D3d11::DepthStencilView()
{
	return m_DepthStencilView.Get();
}