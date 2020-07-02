#include <d3dcompiler.h>
#include "engine.h"
#include "shader.h"

ComPtr<ID3D10Blob> Shader::buffer = nullptr;

//VS
ComPtr<ID3D11VertexShader> Shader::Vertex = nullptr;
ComPtr<ID3D11VertexShader> Shader::BonesVertex = nullptr;

ComPtr<ID3D11InputLayout> Shader::VertexIL = nullptr;
ComPtr<ID3D11InputLayout> Shader::BonesVertexIL = nullptr;

//PS
ComPtr<ID3D11PixelShader> Shader::PS_Basic = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_NoLight = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_Normal = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_NormalSpecular = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_Shadow = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_Reflection = nullptr;
ComPtr<ID3D11PixelShader> Shader::PS_Blur = nullptr;

UINT Shader::currentVSShaderID = 0;
UINT Shader::lastVSShaderID = 0;
UINT Shader::currentPSShaderID = 0;
UINT Shader::lastPSShaderID = 0;

bool Shader::restrictShader = false;

void Shader::Initialize()
{
	/*--------------------------------------------------------------------------------
	Vertex Shader
	--------------------------------------------------------------------------------*/
	//Basic Vertex
	{
		CreateVertexShader(Vertex, L"./SourceFiles/Shader/VS.cso");
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		CreateInputLayout(VertexIL, layout, ARRAYSIZE(layout));
	}

	//Bones Vertex
	{
		CreateVertexShader(BonesVertex, L"./SourceFiles/Shader/VS_Bones.cso");
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEID", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		CreateInputLayout(BonesVertexIL, layout, ARRAYSIZE(layout));
	}

	/*--------------------------------------------------------------------------------
	Pixel Shader
	--------------------------------------------------------------------------------*/
	CreatePixelShader(PS_Basic, L"./SourceFiles/Shader/PS.cso");
	CreatePixelShader(PS_NoLight, L"./SourceFiles/Shader/PS_NoLight.cso");
	CreatePixelShader(PS_Normal, L"./SourceFiles/Shader/PS_Normal.cso");
	CreatePixelShader(PS_NormalSpecular, L"./SourceFiles/Shader/PS_NormalSpecular.cso");

	//RTT Shader
	CreatePixelShader(PS_Shadow, L"./SourceFiles/Shader/PS_Shadow.cso");
	CreatePixelShader(PS_Reflection, L"./SourceFiles/Shader/PS_Reflection.cso");
	CreatePixelShader(PS_Blur, L"./SourceFiles/Shader/PS_Blur.cso");
}

void Shader::SetVSShader(UINT id)
{
	if (id != currentVSShaderID)
		lastVSShaderID = currentVSShaderID;

	currentVSShaderID = id;

	switch (currentVSShaderID)
	{
	case VSShaderID::VS_Basic:
		Renderer::GetContext()->VSSetShader(Vertex.Get(), NULL, 0);
		Renderer::GetContext()->IASetInputLayout(VertexIL.Get());
		break;
	case VSShaderID::VS_Bones:
		Renderer::GetContext()->VSSetShader(BonesVertex.Get(), NULL, 0);
		Renderer::GetContext()->IASetInputLayout(BonesVertexIL.Get());
		break;
	}
}

void Shader::SetPSShader(UINT id)
{
	if (!restrictShader)
	{
		if (id != currentPSShaderID)
			lastPSShaderID = currentPSShaderID;

		currentPSShaderID = id;

		switch (currentPSShaderID)
		{
		case PSShaderID::PS_Basic:
			Renderer::GetContext()->PSSetShader(PS_Basic.Get(), NULL, 0);
			break;
		case PSShaderID::PS_NoLight:
			Renderer::GetContext()->PSSetShader(PS_NoLight.Get(), NULL, 0);
			break;
		case PSShaderID::PS_Normal:
			Renderer::GetContext()->PSSetShader(PS_Normal.Get(), NULL, 0);
			break;
		case PSShaderID::PS_NormalSpecular:
			Renderer::GetContext()->PSSetShader(PS_NormalSpecular.Get(), NULL, 0);
			break;
		case PSShaderID::PS_Shadow:
			Renderer::GetContext()->PSSetShader(PS_Shadow.Get(), NULL, 0);
			break;
		case PSShaderID::PS_Reflection:
			Renderer::GetContext()->PSSetShader(PS_Reflection.Get(), NULL, 0);
			break;
		case PSShaderID::PS_Blur:
			Renderer::GetContext()->PSSetShader(PS_Blur.Get(), NULL, 0);
			break;
		}
	}
}

void Shader::SetLastShader()
{
	SetVSShader(lastVSShaderID);
	SetPSShader(lastPSShaderID);
}

void Shader::CreateVertexShader(ComPtr<ID3D11VertexShader>& shader, LPCWSTR path)
{
	HRESULT hr;

	hr = D3DReadFileToBlob(path, buffer.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create vertex shader buffer");

	hr = Renderer::GetDevice()->CreateVertexShader(buffer.Get()->GetBufferPointer(), buffer.Get()->GetBufferSize(), NULL, shader.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create vertex shader");
}

void Shader::CreateInputLayout(ComPtr<ID3D11InputLayout>& inputLayout, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements)
{
	HRESULT hr;

	hr = Renderer::GetDevice()->CreateInputLayout(layout, numElements, buffer.Get()->GetBufferPointer(), buffer.Get()->GetBufferSize(), inputLayout.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create vertex input layout");
}

void Shader::CreatePixelShader(ComPtr<ID3D11PixelShader>& shader, LPCWSTR path)
{
	HRESULT hr;

	hr = D3DReadFileToBlob(path, buffer.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create pixel shader buffer");

	hr = Renderer::GetDevice()->CreatePixelShader(buffer.Get()->GetBufferPointer(), buffer.Get()->GetBufferSize(), NULL, shader.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create pixel shader");
}
