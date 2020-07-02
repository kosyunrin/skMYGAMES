
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include <io.h>
#include "ImGUI\\imgui.h"
#include "ImGUI\\imgui_impl_win32.h"
#include "ImGUI\\imgui_impl_dx11.h"
#include"Timer.h"

 std::unique_ptr<SpriteBatch>  CRenderer::spritebich;
 std::unique_ptr<SpriteFont>  CRenderer::spritefont;
 //
//state
 
 ID3D11SamplerState*  CRenderer::PSS=NULL;
 ID3D11BlendState* CRenderer::pBs = NULL;
 ID3D11RasterizerState* CRenderer::pRs = NULL;
 //
 //debug
   float  CRenderer::DeBug_show_v3[3];
   float  CRenderer::Debug_show_v2[2];
   float  CRenderer::Debug_show_int[1];
   float  CRenderer::Debug_move_v3[3] = {0.0f,0.0f,0.0f};
   float  CRenderer::Debug_move_v2[2];
   float  CRenderer::Debug_move_Rotation3[3];
   float  CRenderer::Debug_move_Rotation2[2];

   //lightmove
   float CRenderer::LightMove3_0[3] = {-2.0f,0.4f,0.4f};
   float CRenderer::LightMove3_1[3] = { 0.0f, 1.0f, 0.0f };
   float CRenderer::LightMove3_2[3] = { 0.0f, 0.0f, 1.0f };
   float CRenderer::LightMove3_3[3] = { 1.0f, 1.0f, 1.0f };
   float CRenderer::LightMove3_4[3] = { 0.0f, 0.0f, 0.0f };
   float CRenderer::LightMove1_0[1] = {1.0f};
   float CRenderer::LightMove1_1[1]= { 0.09f };
   float CRenderer::LightMove1_2[1]{ 0.032f };
   float CRenderer::LightMove1_3[1]{ 0.1f };
   float CRenderer::LightMove1_4[1]{ 15.0f };


   //
   float  CRenderer::values[12];
   float  CRenderer::values2[12];




   bool   CRenderer::RunSwtichForZombie;
   std::vector<STRINGDRAW> CRenderer::Vstring;


D3D_FEATURE_LEVEL       CRenderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           CRenderer::m_D3DDevice = NULL;
ID3D11DeviceContext*    CRenderer::m_ImmediateContext = NULL;
IDXGISwapChain*         CRenderer::m_SwapChain = NULL;
ID3D11RenderTargetView* CRenderer::m_RenderTargetView = NULL;
ID3D11DepthStencilView* CRenderer::m_DepthStencilView = NULL;



ID3D11VertexShader*     CRenderer::m_VertexShader = NULL;
ID3D11PixelShader*      CRenderer::m_PixelShader = NULL;
ID3D11PixelShader*      CRenderer::m_UIshader = NULL;
ID3D11InputLayout*      CRenderer::m_VertexLayout = NULL;
ID3D11Buffer*			CRenderer::m_WorldBuffer = NULL;
ID3D11Buffer*			CRenderer::m_ViewBuffer = NULL;
ID3D11Buffer*			CRenderer::m_ProjectionBuffer = NULL;
ID3D11Buffer*			CRenderer::m_MaterialBuffer = NULL;
ID3D11Buffer*			CRenderer::m_LightBuffer = NULL;
ID3D11Buffer*			CRenderer::m_SpotBuffer = NULL;
ID3D11Buffer*			CRenderer::m_pointLightBuffer = NULL;
ID3D11Buffer*			CRenderer::m_BonesBuffer = NULL;


ID3D11VertexShader*     CRenderer::m_boneShader = NULL;
ID3D11InputLayout*      CRenderer::m_boneLayout = NULL;
ID3D11Buffer*			CRenderer::m_CBBoneTranform = NULL;

ID3D11VertexShader*     CRenderer::m_WeaponBoneShader = NULL;
ID3D11InputLayout*      CRenderer::m_WeaPonBoneLayout = NULL;
ID3D11Buffer*			CRenderer::m_WeaponBoneBuffer = NULL;


//instance
ID3D11VertexShader*     CRenderer::m_InstanceVSshader = NULL;
ID3D11InputLayout*      CRenderer::m_InstanceLayout = NULL;
ID3D11Buffer*			CRenderer::m_InstanceBuffer = NULL;
//instance anim
ID3D11Buffer*			CRenderer::m_InstanceBuffer_anim = NULL;



ID3D11DepthStencilState* CRenderer::m_DepthStateEnable;
ID3D11DepthStencilState* CRenderer::m_DepthStateDisable;

//shadow
ID3D11DepthStencilView* CRenderer::m_ShadowDepth = NULL;
ID3D11ShaderResourceView* CRenderer::m_ShadowResource = NULL;
ID3D11VertexShader*     CRenderer::m_ShadowVShader = NULL;
ID3D11InputLayout*      CRenderer::m_ShadowLayout = NULL;
ID3D11PixelShader*      CRenderer::m_ShadowPShader = NULL;



void CRenderer::SetShadowShadow(const char * VSname, const char * PSname)
{
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(VSname, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_ShadowVShader);

		//assert(newShader);
		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		m_D3DDevice->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&m_ShadowLayout);

		delete[] buffer;
	}

	{
		FILE* file;
		long int fsize;

		file = fopen(PSname, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreatePixelShader(buffer, fsize, NULL, &m_ShadowPShader);

		delete[] buffer;
	}
}

void CRenderer::Init(const char* mainVs, const char* mianPs)
{
	
	//pSS = std::make_unique<ID3D11SamplerState>();

	
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetWindow();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&sd,
										&m_SwapChain,
										&m_D3DDevice,
										&m_FeatureLevel,
										&m_ImmediateContext );


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	m_D3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_RenderTargetView );
	pBackBuffer->Release();



	//ステンシル用テクスチャー作成
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory( &td, sizeof(td) );
	td.Width			= sd.BufferDesc.Width;
	td.Height			= sd.BufferDesc.Height;
	td.MipLevels		= 1;
	td.ArraySize		= 1;
	td.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc		= sd.SampleDesc;
	td.Usage			= D3D11_USAGE_DEFAULT;
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags	= 0;
	td.MiscFlags		= 0;
	m_D3DDevice->CreateTexture2D( &td, NULL, &depthTexture );

	//ステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory( &dsvd, sizeof(dsvd) );
	dsvd.Format			= td.Format;
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;
	m_D3DDevice->CreateDepthStencilView( depthTexture, &dsvd, &m_DepthStencilView );

	{
		//ShadowRTT
			//ステンシル用テクスチャー作成2
		ID3D11Texture2D* depthTexturex = NULL;
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = sd.BufferDesc.Width;
		td.Height = sd.BufferDesc.Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R32_TYPELESS;
		td.SampleDesc = sd.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		m_D3DDevice->CreateTexture2D(&td, NULL, &depthTexturex);

		//ステンシルターゲット作成2
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Flags = 0;
		m_D3DDevice->CreateDepthStencilView(depthTexturex, &dsvd, &m_ShadowDepth);

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDes = {};
		SRVDes.Format = DXGI_FORMAT_R32_FLOAT;
		SRVDes.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDes.Texture2D.MipLevels = 1;
		m_D3DDevice->CreateShaderResourceView(depthTexturex, &SRVDes, &m_ShadowResource);
	}

	m_ImmediateContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_ImmediateContext->RSSetViewports( 1, &vp );



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd; 
	ZeroMemory( &rd, sizeof( rd ) );
	rd.FillMode = D3D11_FILL_SOLID; 
	rd.CullMode = D3D11_CULL_NONE; 
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = TRUE; 
	rd.MultisampleEnable = FALSE; 

	//ID3D11RasterizerState *rs;
	m_D3DDevice->CreateRasterizerState( &rd, &pRs );

	m_ImmediateContext->RSSetState(pRs);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( blendDesc ) );
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	//ID3D11BlendState* blendState = NULL;
	m_D3DDevice->CreateBlendState( &blendDesc, &pBs );
	m_ImmediateContext->OMSetBlendState( pBs, blendFactor, 0xffffffff );



	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	m_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateEnable );//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	m_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateDisable );//深度無効ステート

	m_ImmediateContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );

	/*spritebich = std::make_unique<SpriteBatch>(CRenderer::GetDeviceContext());
	spritefont = std::make_unique<SpriteFont>(CRenderer::GetDevice(), L"asset/Fonts/comic_sans_ms_16.spritefont");*/
	




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//ID3D11SamplerState* samplerState = NULL;
	m_D3DDevice->CreateSamplerState( &samplerDesc, &PSS );

	m_ImmediateContext->PSSetSamplers( 0, 1, &PSS);



	//SetNewVSshader("BoneWeaponVS.cso", m_WeaponBoneShader, m_WeaPonBoneLayout);
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(mainVs, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_VertexShader);


		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		m_D3DDevice->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&m_VertexLayout);

		delete[] buffer;
	}
	SetNewVSshader("BoneWeaponVS.cso");
	SetShadowShadow("ShadowVS.cso", "ShadowPS.cso");
	// 頂点シェーダ生成
	//{
	//	FILE* file;
	//	long int fsize;

	//	file = fopen("BoneWeaponVS.cso", "rb");
	//	fsize = _filelength(_fileno(file));
	//	unsigned char* buffer = new unsigned char[fsize];
	//	fread(buffer, fsize, 1, file);
	//	fclose(file);

	//	m_D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_WeaponBoneShader);


	//	// 入力レイアウト生成
	//	D3D11_INPUT_ELEMENT_DESC layout[] =
	//	{
	//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	};
	//	UINT numElements = ARRAYSIZE(layout);

	//	m_D3DDevice->CreateInputLayout(layout,
	//		numElements,
	//		buffer,
	//		fsize,
	//		&m_WeaPonBoneLayout);

	//	delete[] buffer;
	//}
	//instance
		// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("InstanceShader.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_InstanceVSshader);


		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEID", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		m_D3DDevice->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&m_InstanceLayout);

		delete[] buffer;
	}
	//bone
	// 頂点シェーダ生成2
	{
		FILE* file;
		long int fsizes;

		file = fopen("BonesVS.cso", "rb");
		fsizes = _filelength(_fileno(file));
		unsigned char* Bonebuffer = new unsigned char[fsizes];
		fread(Bonebuffer, fsizes, 1, file);
		fclose(file);

		m_D3DDevice->CreateVertexShader(Bonebuffer, fsizes, NULL, &m_boneShader);

		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layoutx[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEID", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

		};
		UINT numElementss = ARRAYSIZE(layoutx);

		m_D3DDevice->CreateInputLayout(layoutx,
			numElementss,
			Bonebuffer,
			fsizes,
			&m_boneLayout);

		delete[] Bonebuffer;
	}



	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;
		
		file = fopen(mianPs, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreatePixelShader(buffer, fsize, NULL, &m_PixelShader);

		delete[] buffer;
	}

	// UIピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("UIShader_PS.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreatePixelShader(buffer, fsize, NULL, &m_UIshader);

		delete[] buffer;
	}




	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_WorldBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 0, 1, &m_WorldBuffer);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_ViewBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 1, 1, &m_ViewBuffer );

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_ProjectionBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 2, 1, &m_ProjectionBuffer );


	hBufferDesc.ByteWidth = sizeof(MATERIAL);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_MaterialBuffer);
	m_ImmediateContext->VSSetConstantBuffers( 3, 1, &m_MaterialBuffer);


	hBufferDesc.ByteWidth = sizeof(LIGHT);

	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);
	m_ImmediateContext->VSSetConstantBuffers( 4, 1, &m_LightBuffer );
	m_ImmediateContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);//

	hBufferDesc.ByteWidth = sizeof(XMFLOAT4X4) * BONESMAX;
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_BonesBuffer);
	m_ImmediateContext->VSSetConstantBuffers(5, 1, &m_BonesBuffer);//

	//instance
	hBufferDesc.ByteWidth = sizeof(XMFLOAT4X4) * INSTANCEMAX;
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_InstanceBuffer);
	m_ImmediateContext->VSSetConstantBuffers(6, 1, &m_InstanceBuffer);//

	hBufferDesc.ByteWidth = sizeof(INSTANCEBUFFER)*INSTANCEMAX;
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_InstanceBuffer_anim);
	m_ImmediateContext->VSSetConstantBuffers(7, 1, &m_InstanceBuffer_anim);//

	hBufferDesc.ByteWidth = sizeof(SpotlLight);
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_SpotBuffer);
	m_ImmediateContext->PSSetConstantBuffers(8, 1, &m_SpotBuffer);//

	hBufferDesc.ByteWidth = sizeof(POINTLIGHT);
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_pointLightBuffer);
	m_ImmediateContext->PSSetConstantBuffers(9, 1, &m_pointLightBuffer);//

	hBufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_WeaponBoneBuffer);
	m_ImmediateContext->VSSetConstantBuffers(10, 1, &m_WeaponBoneBuffer);//




	// 入力レイアウト設定
	m_ImmediateContext->IASetInputLayout( m_VertexLayout );

	// シェーダ設定
	m_ImmediateContext->VSSetShader( m_VertexShader, NULL, 0 );
	m_ImmediateContext->PSSetShader( m_PixelShader, NULL, 0 );



	// ライト初期化
	/*LIGHT light;
	light.Direction = XMFLOAT4(1.0f, -1.0f, 0.0f, 0.0f);
	light.Diffuse = COLOR(0.9f, 0.9f, 0.9f, 0.9f);
	light.Ambient = COLOR(0.0f, 0.0f, 0.0f, 0.0f);
	SetLight(light);*/
	


	// マテリアル初期化
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	material.Ambient = COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	SetMaterial( material );
	/*spritebich = std::unique_ptr<SpriteBatch>(new     SpriteBatch(CRenderer::GetDeviceContext()));
	spritefont = std::unique_ptr<SpriteFont>(new	  SpriteFont(CRenderer::GetDevice(), L"asset/Fonts/comic_sans_ms_16.spritefont"));*/

	spritebich = std::make_unique<SpriteBatch>(m_ImmediateContext);
	spritefont = std::make_unique<SpriteFont>(m_D3DDevice, L"asset//Fonts//comic_sans_ms_16.spritefont");

	//Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(m_D3DDevice, m_ImmediateContext);
	ImGui::StyleColorsDark();

}

void CRenderer::SetNewVSshader(const char * Vs)
{
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(Vs, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		m_D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_WeaponBoneShader);

		//assert(newShader);
		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		m_D3DDevice->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&m_WeaPonBoneLayout);

		delete[] buffer;
	}
}




void CRenderer::Uninit()
{
	// オブジェクト解放
	if ( m_WorldBuffer )		m_WorldBuffer->Release();
	if ( m_ViewBuffer )			m_ViewBuffer->Release();
	if ( m_ProjectionBuffer )	m_ProjectionBuffer->Release();

	if( m_MaterialBuffer )		m_MaterialBuffer->Release();
	if( m_VertexLayout )		m_VertexLayout->Release();
	if( m_VertexShader )		m_VertexShader->Release();
	//
	if (m_BonesBuffer)
	{
		m_BonesBuffer->Release();
	}
	if (m_boneLayout)		
		m_boneLayout->Release();
	if (m_boneShader)		
		m_boneShader->Release();

	if( m_PixelShader )			m_PixelShader->Release();
	if (m_UIshader)				m_UIshader->Release();

	if( m_ImmediateContext )	m_ImmediateContext->ClearState();
	if( m_RenderTargetView )	m_RenderTargetView->Release();
	if( m_SwapChain )			m_SwapChain->Release();
	if( m_ImmediateContext )	m_ImmediateContext->Release();
	if( m_D3DDevice )			m_D3DDevice->Release();

	//instance
	if (m_InstanceBuffer)		m_InstanceBuffer->Release();
	if (m_InstanceLayout)			m_InstanceLayout->Release();
	if (m_InstanceVSshader)		m_InstanceVSshader->Release();
	if (m_InstanceBuffer_anim)	m_InstanceBuffer_anim->Release();

	if (m_WeaponBoneBuffer)		m_WeaponBoneBuffer->Release();
	if (m_WeaPonBoneLayout)			m_WeaPonBoneLayout->Release();
	if (m_WeaponBoneShader)		m_WeaponBoneShader->Release();

	if (PSS)   PSS->Release();
	if (pBs)   pBs->Release();
	if (pRs)    pRs->Release();


	Vstring.clear();
	if (m_LightBuffer) m_LightBuffer->Release();
	if (m_SpotBuffer) m_SpotBuffer->Release();
	if (m_pointLightBuffer) m_pointLightBuffer->Release();

	if (m_ShadowDepth) m_ShadowDepth->Release();
	if (m_ShadowResource) m_ShadowResource->Release();
	if (m_ShadowVShader) m_ShadowVShader->Release();
	if (m_ShadowPShader) m_ShadowPShader->Release();
	if (m_ShadowLayout) m_ShadowLayout->Release();

}



void CRenderer::Begin()
{
	
	// バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);//ターゲット　切り替え　,null Color buffer
	m_ImmediateContext->ClearRenderTargetView( m_RenderTargetView, ClearColor );
	m_ImmediateContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	
	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0); 
	m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);
}



void CRenderer::End()
{
	
	/*const wchar_t* sds = L"HAShdi";
	spritebich->Begin();
	spritefont->DrawString(spritebich.get(), sds, XMFLOAT2(0, 0), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));
	spritebich->End();*/
	// start the Imgui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//Creat imgui Test Window
	ImGui::Begin("");
	/*if (ImGui::Button("click me"))
		counter += 1;*/
	static bool is_open = false;

	if (ImGui::Button("DE_BUG"))
	{
		// ボタンがクリックされるとここにきます。
		is_open ^= 1;
	}
	ImGui::SameLine(); // 次に書くUIパーツを現在と同じ行に配置します。
// チェックボックスがクリックされるとis_openが反転し、trueならチェックマークが表示されます。
	ImGui::Checkbox("Open/Close", &is_open);
	if (is_open)
	{
		ImGui::Begin("DE_BUG", &is_open);
		ImGui::Text("Show_me");
		//ImGui::SameLine();
		ImGui::DragFloat3("Show_me_V3", DeBug_show_v3, 0.1f, -1000.0f, 1000.0f);
		ImGui::DragFloat2("Show_me_V2", Debug_show_v2, 100.0f, -1000.0f, 1000.0f);
		ImGui::DragFloat("Show_me_int", Debug_show_int, 0, 0, 500);
		ImGui::Text("Drag_me");
		ImGui::DragFloat3("Drag_me_V3", Debug_move_v3, 0.1f, -1000.0f, 1000.0f);
		ImGui::DragFloat2("Drag_me_V2", Debug_move_v2, 0.1f, -1000.0f, 1000.0f);
		ImGui::DragFloat3("Drag_me_Rotation3", Debug_move_Rotation3, 0.1f, 1.0f, 255.0f);
		ImGui::DragFloat2("Drag_me_Rotation2", Debug_move_Rotation2, 0.1f, 1.0f, 255.0f);
		ImGui::End();
	}

	static bool is_open1 = false;
	ImGui::SameLine();
	if (ImGui::Button("LIGHT"))
	{
		// ボタンがクリックされるとここにきます。
		is_open1 ^= 1;
	}
	ImGui::SameLine(); // 次に書くUIパーツを現在と同じ行に配置します。
// チェックボックスがクリックされるとis_openが反転し、trueならチェックマークが表示されます。
	ImGui::Checkbox("Open/Close", &is_open1);
	if (is_open1)
	{
		ImGui::Begin("Light", &is_open1);
		//lighet
	

		if (ImGui::CollapsingHeader("SunLight"))
		{
			//values[12] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f,0.0f,0.0f,0.0f ,0.0f,0.0f};
			 int BeiginandEndSize[2] = { 0.0f,10.0f };
			static int dir[2];
			static bool button0 = false;
			static int Am[2] = { 0.0f,0.0f };
			static bool button1 = false;
			static int int2[2];
			static bool button2 = false;

			static int int3[2];
			static bool button3 = false;
			if (ImGui::Button("Direction_Range")) button0 ^= 1;
			if (button0)
			{
				ImGui::Begin("SunLight", &button0);
				ImGui::DragInt2("Direction_Range", dir, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Diffuse_Range")) button1 ^= 1;
			if (button1)
			{
				ImGui::Begin("SunLight", &button1);
				ImGui::DragInt2("Diffuse_Range", int2, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Ambient_Range")) button2 ^= 1;
			if (button2)
			{
				ImGui::Begin("SunLight", &button2);
				ImGui::DragInt2("Ambient_Range", Am, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Specular_Range")) button3 ^= 1;
			if (button3)
			{
				ImGui::Begin("SunLight", &button3);
				ImGui::DragInt2("Specular_Range", int3, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			for (int i = 0; i < 12; i++)
			{
				std::string text;
			
				switch (i)
				{
				case 0:
					text = "X";
					ImGui::Text("Direction");
					ImGui::SameLine();
					ImGui::Text("		Diffuse");
					ImGui::SameLine();
					ImGui::Text("		Ambient");
					ImGui::SameLine();
					ImGui::Text("		Specular");
					//ImGui::SameLine();
				
					BeiginandEndSize[0] = dir[0];
					BeiginandEndSize[1] = dir[1];
					break;
				case 1:
					text = "Y";
					BeiginandEndSize[0] = dir[0];
					BeiginandEndSize[1] = dir[1];
					break;
				case 2:
					text = "Z";
					BeiginandEndSize[0] = dir[0];
					BeiginandEndSize[1] = dir[1];
					break;
				case 3:
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					BeiginandEndSize[0] = int2[0];
					BeiginandEndSize[1] = int2[1];
					break;
				case 4:
					text = "Y";
					BeiginandEndSize[0] = int2[0];
					BeiginandEndSize[1] = int2[1];
					break;
				case 5:
					text = "Z";
					BeiginandEndSize[0] = int2[0];
					BeiginandEndSize[1] = int2[1];
					break;
				case 6:
					BeiginandEndSize[0] = Am[0];
					BeiginandEndSize[1] = Am[1];
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					break;
				case 7:
					BeiginandEndSize[0] = Am[0];
					BeiginandEndSize[1] = Am[1];
					text = "Y";
					break;
				case 8:
					BeiginandEndSize[0] = Am[0];
					BeiginandEndSize[1] = Am[1];
					text = "Z";
					break;
				case 9:
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					BeiginandEndSize[0] = int3[0];
					BeiginandEndSize[1] = int3[1];
					break;
				case 10:
					text = "Y";
					BeiginandEndSize[0] = int3[0];
					BeiginandEndSize[1] = int3[1];
					break;
				case 11:
					text = "Z";
					BeiginandEndSize[0] = int3[0];
					BeiginandEndSize[1] = int3[1];
					break;
				}
				if (i > 0) ImGui::SameLine();
				ImGui::PushID(i);
				// 垂直スライダーを幅18,高さ160,最小値0,最大値1で作成します。
				ImGui::VSliderFloat("##v", ImVec2(18, 160), &values[i], BeiginandEndSize[0], BeiginandEndSize[1], text.c_str());

				if (ImGui::IsItemActive() || ImGui::IsItemHovered())
					// スライダー上をマウスオーバーした時に現在の値がポップアップで表示されます。
					ImGui::SetTooltip("%.3f", values[i]);

				ImGui::PopID();
			}
		}

		if (ImGui::CollapsingHeader("pointLight"))
		{
			//static float values2[12] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f,0.0f,0.0f,0.0f ,0.0f,0.0f };
			int BeiginandEndSize[2] = { 0.0f,10.0f };

			static int pint0[2];
			static bool pbutton0 = false;
			static int pint1[2];
			static bool pbutton1 = false;
			static int pint2[2];
			static bool pbutton2 = false;
			static int pint3[2];
			static bool pbutton3 = false;

			if (ImGui::Button("Direction_Range")) pbutton0 ^= 1;
			if (pbutton0)
			{
				ImGui::Begin("pointLight", &pbutton0);
				ImGui::DragInt2("Direction_Range", pint0, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Diffuse_Range")) pbutton1 ^= 1;
			if (pbutton1)
			{
				ImGui::Begin("pointLight", &pbutton1);
				ImGui::DragInt2("Diffuse_Range", pint1, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Ambient_Range")) pbutton2 ^= 1;
			if (pbutton2)
			{
				ImGui::Begin("pointLight", &pbutton2);
				ImGui::DragInt2("Ambient_Range", pint2, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}
			ImGui::SameLine();
			if (ImGui::Button("Specular_Range")) pbutton3 ^= 1;
			if (pbutton3)
			{
				ImGui::Begin("pointLight", &pbutton3);
				ImGui::DragInt2("Specular_Range", pint3, 0.1f, -1000.0f, 1000.0f);
				ImGui::End();
			}

			for (int i = 0; i < 12; i++)
			{
				std::string text;
				switch (i)
				{
				case 0:
					BeiginandEndSize[0] = pint0[0];
					BeiginandEndSize[1] = pint0[1];
					text = "X";
					ImGui::Text("Position");
					ImGui::SameLine();
					ImGui::Text("		Diffuse");
					ImGui::SameLine();
					ImGui::Text("		Ambient");
					ImGui::SameLine();
					ImGui::Text("		Specular");
					break;
				case 1:
					text = "Y";
					break;
				case 2:
					text = "Z";
					break;
				case 3:
					BeiginandEndSize[0] = pint1[0];
					BeiginandEndSize[1] = pint1[1];
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					break;
				case 4:
					text = "Y";
					break;
				case 5:
					text = "Z";
					break;
				case 6:
					BeiginandEndSize[0] = pint2[0];
					BeiginandEndSize[1] = pint2[1];
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					break;
				case 7:
					text = "Y";
					break;
				case 8:
					text = "Z";
					break;
				case 9:
					BeiginandEndSize[0] = pint3[0];
					BeiginandEndSize[1] = pint3[1];
					text = "X";
					ImGui::SameLine();
					ImGui::Text("	");
					break;
				case 10:
					text = "Y";
					break;
				case 11:
					text = "Z";
					break;
				}
				if (i > 0) ImGui::SameLine();
				ImGui::PushID(i);
				// 垂直スライダーを幅18,高さ160,最小値0,最大値1で作成します。
				ImGui::VSliderFloat("##v", ImVec2(18, 160), &values2[i], BeiginandEndSize[0], BeiginandEndSize[1], text.c_str());

				if (ImGui::IsItemActive() || ImGui::IsItemHovered())
					// スライダー上をマウスオーバーした時に現在の値がポップアップで表示されます。
					ImGui::SetTooltip("%.3f", values2[i]);

				ImGui::PopID();
			}
		}


		if (ImGui::CollapsingHeader("SotLight"))
		{
			ImGui::DragFloat3("SpotLight_Pos", LightMove3_0, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat3("SpotLight_Dir", LightMove3_2, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat3("SpotLight_Ambient", LightMove3_4, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat3("SpotLight_Specular", LightMove3_3, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat3("SpotLight_diffuse", LightMove3_1, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat("SpotLight_Constant", LightMove1_0, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat("SpotLight_Linear", LightMove1_1, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat("SpotLight_quadratic", LightMove1_2, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat("SpotLight_cutOff", LightMove1_3, 0.01f, -1000.0f, 1000.0f);
			ImGui::DragFloat("SpotLight_outerCutOff", LightMove1_4, 0.01f, -1000.0f, 1000.0f);
		}

		ImGui::End();
	}





	ImGui::End();
	//Draw date
	ImGui::Render();
	//reder draw date
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	m_SwapChain->Present( 1, 0);
}

void CRenderer::BeiginShadow()
{
	m_ImmediateContext->OMSetRenderTargets(0, NULL, m_ShadowDepth);//ターゲット　切り替え　,null Color buffer
	m_ImmediateContext->ClearDepthStencilView(m_ShadowDepth, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
	m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);
}

void CRenderer::SetShadowTex(int num)
{
	ID3D11ShaderResourceView* srv[1] = { m_ShadowResource };
	m_ImmediateContext->PSSetShaderResources(num, 1, srv);
}




void CRenderer::SetDepthEnable( bool Enable )
{
	if( Enable )
		m_ImmediateContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );
	else
		m_ImmediateContext->OMSetDepthStencilState( m_DepthStateDisable, NULL );

}

void CRenderer::SetWorldViewProjection2D()
{
	XMMATRIX world;
	world = XMMatrixIdentity();
	m_ImmediateContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &XMMatrixTranspose(world), 0, 0);

	XMMATRIX view;
	view = XMMatrixIdentity();
	m_ImmediateContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &XMMatrixTranspose(view), 0, 0);

	XMMATRIX projection;
	projection = XMMatrixOrthographicOffCenterLH( 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f );
	m_ImmediateContext->UpdateSubresource( m_ProjectionBuffer, 0, NULL, &XMMatrixTranspose(projection), 0, 0 );

}


void CRenderer::SetWorldMatrix( XMMATRIX *WorldMatrix )
{
	XMMATRIX world;
	world = *WorldMatrix;
	m_ImmediateContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &XMMatrixTranspose(world), 0, 0);

}

void CRenderer::SetWorldMatrixTranspose(XMMATRIX * WorldMatrix)
{
	XMMATRIX world;
	world = *WorldMatrix;
	m_ImmediateContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &WorldMatrix, 0, 0);
}

void CRenderer::SetViewMatrix( XMMATRIX *ViewMatrix )
{
	XMMATRIX view;
	view = *ViewMatrix;
	m_ImmediateContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &XMMatrixTranspose(view), 0, 0);
}

void CRenderer::SetProjectionMatrix( XMMATRIX *ProjectionMatrix )
{
	XMMATRIX projection;
	projection = *ProjectionMatrix;
	m_ImmediateContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &XMMatrixTranspose(projection), 0, 0);
}


void CRenderer::SetFinalMatrix(FINALMATRIX Finalmatrix)
{
	m_ImmediateContext->UpdateSubresource(m_CBBoneTranform, 0, NULL, &Finalmatrix, 0, 0);
}



void CRenderer::SetMaterial( MATERIAL Material )
{

	m_ImmediateContext->UpdateSubresource( m_MaterialBuffer, 0, NULL, &Material, 0, 0 );

}

void CRenderer::SetLight(LIGHT Light)
{

	m_ImmediateContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);

}

void CRenderer::SetSpotLight(SpotlLight Light)
{
	m_ImmediateContext->UpdateSubresource(m_SpotBuffer, 0, NULL, &Light, 0, 0);
}
void CRenderer::SetPointLight(POINTLIGHT Light)
{
	m_ImmediateContext->UpdateSubresource(m_pointLightBuffer, 0, NULL, &Light, 0, 0);
}


void CRenderer::SetVertexBuffers( ID3D11Buffer* VertexBuffer )
{

	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	ID3D11Buffer* vb[1] = { VertexBuffer };
	m_ImmediateContext->IASetVertexBuffers( 0, 1, vb, &stride, &offset );

}

void CRenderer::SetBoneVertexBuffers(ID3D11Buffer * VertexBuffer)
{
	UINT stride = sizeof(BonesVertex);
	UINT offset = 0;
	ID3D11Buffer* vb[1] = { VertexBuffer };
	m_ImmediateContext->IASetVertexBuffers(0, 1, vb, &stride, &offset);
}



void CRenderer::SetIndexBuffer( ID3D11Buffer* IndexBuffer )
{

	m_ImmediateContext->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R16_UINT, 0 );

}


void CRenderer::SetTexture( CTexture* Texture )
{

	ID3D11ShaderResourceView* srv[1] = { Texture->GetShaderResourceView() };
	m_ImmediateContext->PSSetShaderResources( 0, 1, srv );//将着色器资源数组绑定到像素着色器阶段。

}

void CRenderer::SetTexture2(ID3D11ShaderResourceView * srvs)
{
	ID3D11ShaderResourceView* srv[1] = { srvs };
	m_ImmediateContext->PSSetShaderResources(0, 1, srv);//将着色器资源数组绑定到像素着色器阶段。
}

void CRenderer::SetTextureIndex(CTexture * Texture, int texture)
{
	ID3D11ShaderResourceView* srv[1] = { Texture->GetShaderResourceViewIndex(texture) };
	m_ImmediateContext->PSSetShaderResources(0, 1, srv);
}

void CRenderer::SetTextureJPGPNG(CTexture * Texture, int texture)
{
	ID3D11ShaderResourceView* srv[1] = { Texture->GetShaderResourceViewJpgPng(texture) };
	m_ImmediateContext->PSSetShaderResources(0, 1, srv);
}


void CRenderer::DrawIndexed( unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation )
{

	m_ImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	m_ImmediateContext->DrawIndexed( IndexCount, StartIndexLocation, BaseVertexLocation );

}

void CRenderer::SetBones(std::vector<XMFLOAT4X4>& transforms)
{
	XMFLOAT4X4 bones[BONESMAX];
	ZeroMemory(&bones, sizeof(bones));

	for (int i = 0; i < transforms.size(); i++)
		bones[i] = transforms[i];
	m_ImmediateContext->UpdateSubresource(m_BonesBuffer, 0, NULL, &bones, 0, 0);
}
void CRenderer::SetWeponBone(XMFLOAT4X4 bonematrix)
{
	m_ImmediateContext->UpdateSubresource(m_WeaponBoneBuffer, 0, NULL, &bonematrix, 0, 0);
}
void CRenderer::SetInstanceWorld(XMFLOAT4X4 world[])
{
	XMFLOAT4X4 InstanceW[INSTANCEMAX];
	ZeroMemory(&InstanceW, sizeof(InstanceW));
	for (int i = 0; i < INSTANCEMAX; i++)
	{
		XMMATRIX instancex = XMLoadFloat4x4(&world[i]);
		instancex = XMMatrixTranspose(instancex);
		XMStoreFloat4x4(&InstanceW[i], instancex);
	}
	m_ImmediateContext->UpdateSubresource(m_InstanceBuffer, 0, NULL, &InstanceW, 0, 0);
}

void CRenderer::SetInstanceAimWorld(INSTANCEBUFFER Sinstance[])
{
	/*INSTANCEBUFFER instance[INSTANCEMAX];
	for (UINT i = 0; i < INSTANCEMAX; i++)
	{
		instance[i].Instanceworld = Sinstance[i].Instanceworld;
	}
	for (UINT i = 0; i < BONESMAX; i++)
	{
		instance[0].BoneMarix[i] = Sinstance[0].BoneMarix[i];
	}*/
	m_ImmediateContext->UpdateSubresource(m_InstanceBuffer_anim, 0, NULL, &Sinstance, 0, 0);
}

void CRenderer::BoneSL()
{
	m_ImmediateContext->IASetInputLayout(m_boneLayout);
	m_ImmediateContext->VSSetShader(m_boneShader, NULL, 0);
}

void CRenderer::BoneBack()
{
	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
}
void CRenderer::ShadowDraw()
{
	m_ImmediateContext->IASetInputLayout(m_ShadowLayout);
	m_ImmediateContext->VSSetShader(m_ShadowVShader, NULL, 0);
	m_ImmediateContext->PSSetShader(m_ShadowPShader, NULL, 0);
}
void CRenderer::ShadowEnd()
{
	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
	m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);
}
void CRenderer::WeaponBoneBegin()
{
	m_ImmediateContext->IASetInputLayout(m_WeaPonBoneLayout);
	m_ImmediateContext->VSSetShader(m_WeaponBoneShader, NULL, 0);
}
void CRenderer::WeaponBoneBack()
{
	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
}
void CRenderer::UIBegin()
{

	m_ImmediateContext->PSSetShader(m_UIshader, NULL, 0);
}
void CRenderer::UIBack()
{
	m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);
}
void CRenderer::DrawStringBack()
{


	m_ImmediateContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);
	//m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	//m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
	//m_ImmediateContext->PSSetShader(m_PixelShader, NULL, 0);




	m_ImmediateContext->RSSetState(pRs);


	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_ImmediateContext->OMSetBlendState(pBs, blendFactor, 0xffffffff);

	m_ImmediateContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);

	

	m_ImmediateContext->PSSetSamplers(0, 1, &PSS);
	
}

void CRenderer::InstanceBegin()
{
	m_ImmediateContext->IASetInputLayout(m_InstanceLayout);
	m_ImmediateContext->VSSetShader(m_InstanceVSshader, NULL, 0);
}

void CRenderer::InstanceEnd()
{
	m_ImmediateContext->IASetInputLayout(m_VertexLayout);
	m_ImmediateContext->VSSetShader(m_VertexShader, NULL, 0);
}

void SkinBoneDate::AddBoneData(UINT BoneIDs, float Weights)
{
	/*for (UINT i = 0; i < 4; i++) {
		if (BoneWeight[i] == 0.0) {
			BoneID[i] = BoneIDs;
			BoneWeight[i] = Weights;
			return;
		}
	}*/

	// should never get here - more bones than we have space for
	assert(0);
}
