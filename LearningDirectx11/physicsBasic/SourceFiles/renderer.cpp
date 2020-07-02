#include "engine.h"
#include "renderer.h"

ComPtr<ID3D11Device> Renderer::Device = nullptr;
ComPtr<ID3D11DeviceContext> Renderer::Context = nullptr;
ComPtr<IDXGISwapChain> Renderer::SwapChain = nullptr;
ComPtr<ID3D11RenderTargetView> Renderer::RenderTargetView = nullptr;
ComPtr<ID3D11DepthStencilView> Renderer::DepthStencilView = nullptr;
ComPtr<ID3D11DepthStencilState> Renderer::DepthStencilState = nullptr;

D3D11_VIEWPORT Renderer::Viewport;

void Renderer::Initialize(UINT width, UINT height)
{
	CreateSwapChainDevice(width, height);

	SetViewport(width, height);

	CreateRasterizerState();

	CreateRenderTarget(width, height);

	CreateStencilState();

	CreateSampleState();

	CreateBlendState();

	CreateImGui();
}

void Renderer::Begin()
{
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //Background color of the frame
	Context->ClearRenderTargetView( RenderTargetView.Get(), ClearColor ); //Clear the back buffer
	Context->ClearDepthStencilView( DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); //Clear the depth buffer

	//ImGui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Renderer::End()
{
	//ImGui
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	SwapChain->Present(1, 0);
}

void Renderer::CreateSwapChainDevice(UINT width, UINT height)
{
	HRESULT hr;

	D3D_FEATURE_LEVEL v;
	v= D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	/*--------------------------------------------------------------------------------
	Swap Chain
	--------------------------------------------------------------------------------*/
	DXGI_SWAP_CHAIN_DESC sd; //Swap chain struct
	ZeroMemory(&sd, sizeof(sd)); //Clean out the struct for use

	//Fill the swap chain description struct
	sd.BufferCount = 1; //One back buffer
	sd.BufferDesc.Width = width; //Screen width
	sd.BufferDesc.Height = height; //Screen height
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Use 32-bit color
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Draw graphics into the back buffer
	sd.OutputWindow = GetWindow();
	sd.SampleDesc.Count = 1; //How many multi-samples (MSAA) render
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE; //Window screen mode or Full screen mode
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	/*--------------------------------------------------------------------------------
	Create Direct3D Device
	--------------------------------------------------------------------------------*/
	hr = D3D11CreateDeviceAndSwapChain(
		NULL, //Decide which GPU to use, let DXGI choose automatically
		D3D_DRIVER_TYPE_HARDWARE, //Use GPU hardware for rendering
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION, //SDK version
		&sd, //Pointer to swap chain settings
		SwapChain.GetAddressOf(), //Pointer to swap chain device
		Device.GetAddressOf(), //Pointer to Direct3D device 
		&v, //Pointer to feature level
		Context.GetAddressOf()); //Pointer to the device context object

	if (FAILED(hr))
		Engine::ErrorMsg("Create Direct Device & Swap Chain Failed");

	//Create Render Target View
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backBuffer.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("SwapChain Get Buffer Failed");

	hr = Device->CreateRenderTargetView(backBuffer.Get(), NULL, RenderTargetView.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Render Target View Failed");
}

void Renderer::CreateRasterizerState()
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;

	hr = Device->CreateRasterizerState(&rd, rasterizerState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Rasterizer State Failed");

	Context->RSSetState(rasterizerState.Get());
}

void Renderer::CreateRenderTarget(UINT width, UINT height)
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> depthTexture = nullptr;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	hr = Device->CreateTexture2D(&td, NULL, depthTexture.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Depth Stencil Texture Failed");

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;

	hr = Device->CreateDepthStencilView(depthTexture.Get(), &dsvd, DepthStencilView.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Stencil Target Failed");

	SetRenderTarget();
}

void Renderer::CreateStencilState()
{
	HRESULT hr;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	hr = Device->CreateDepthStencilState(&depthStencilDesc, DepthStencilState.GetAddressOf()); //Enable Depth State
	if (FAILED(hr))
		Engine::ErrorMsg("Create Depth Stencil State Failed");

	Context->OMSetDepthStencilState(DepthStencilState.Get(), NULL);
}

void Renderer::CreateSampleState()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ComPtr<ID3D11SamplerState> wrapSamplerState = nullptr;

	hr = Device->CreateSamplerState(&samplerDesc, wrapSamplerState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Wrap Sampler State Failed");

	Context->PSSetSamplers(0, 1, wrapSamplerState.GetAddressOf());

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	ComPtr<ID3D11SamplerState> clampSamplerState = nullptr;
	hr = Device->CreateSamplerState(&samplerDesc, clampSamplerState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Clamp Sampler State Failed");

	Context->PSSetSamplers(1, 1, clampSamplerState.GetAddressOf());

}

void Renderer::CreateBlendState()
{
	HRESULT hr;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //Blend All RGBA

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	ComPtr<ID3D11BlendState> blendState = nullptr;

	hr = Device->CreateBlendState(&blendDesc, blendState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Blend State Failed");

//	Context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	Context->OMSetBlendState(NULL, NULL, 0xffffffff);
}

void Renderer::SetFillMode(D3D11_FILL_MODE mode)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = mode;
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;

	hr = Device->CreateRasterizerState(&rd, rasterizerState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Rasterizer State Failed");

	Context->RSSetState(rasterizerState.Get());
}

void Renderer::SetCullMode(D3D11_CULL_MODE mode)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rd.CullMode = mode;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;

	hr = Device->CreateRasterizerState(&rd, rasterizerState.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create Rasterizer State Failed");

	Context->RSSetState(rasterizerState.Get());
}

void Renderer::SetViewport(UINT width, UINT height)
{
	Viewport.Width = (float)width;
	Viewport.Height = (float)height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;

	Context->RSSetViewports(1, &Viewport); //Activate the viewport struct
}

void Renderer::SetRenderTarget()
{
	Context->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());
}

void Renderer::CreateImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("./Asset/Fonts./NotoSans.otf", 25.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(Device.Get(), Context.Get());
	ImGui::StyleColorsDark();
}