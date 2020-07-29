#pragma once

class Renderer
{
private:
	static ComPtr<ID3D11Device> Device;
	static ComPtr<ID3D11DeviceContext> Context;
	static ComPtr<IDXGISwapChain> SwapChain;
	static ComPtr<ID3D11RenderTargetView> RenderTargetView;
	static ComPtr<ID3D11DepthStencilView> DepthStencilView;
	static ComPtr<ID3D11DepthStencilState> DepthStencilState;

	static D3D11_VIEWPORT Viewport;

	static void CreateSwapChainDevice(UINT width, UINT height);
	static void CreateRasterizerState();
	static void CreateRenderTarget(UINT width, UINT height);
	static void CreateStencilState();
	static void CreateSampleState();
	static void CreateBlendState();

	static void CreateImGui();

public:
	static void Initialize(UINT width, UINT height);
	static void Begin();
	static void End();
	
	static void SetFillMode(D3D11_FILL_MODE mode);
	static void SetCullMode(D3D11_CULL_MODE mode);
	static void SetViewport(UINT width, UINT height);
	static void SetRenderTarget();

	static ID3D11Device* GetDevice() { return Device.Get(); }
	static ID3D11DeviceContext* GetContext() { return Context.Get(); }
	static ID3D11DepthStencilView* GetDepthStencilView() { return DepthStencilView.Get(); }
};