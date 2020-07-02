#pragma once

enum VSShaderID
{
	VS_Basic,
	VS_Bones
};

enum PSShaderID
{
	PS_Basic,
	PS_NoLight,
	PS_Normal,
	PS_NormalSpecular,
	PS_Shadow,
	PS_Reflection,
	PS_Blur
};

class Shader
{
private:
	static ComPtr<ID3D10Blob> buffer;

	//VS
	static ComPtr<ID3D11VertexShader> Vertex;
	static ComPtr<ID3D11VertexShader> BonesVertex;

	static ComPtr<ID3D11InputLayout> VertexIL;
	static ComPtr<ID3D11InputLayout> BonesVertexIL;

	//PS
	static ComPtr<ID3D11PixelShader> PS_Basic;
	static ComPtr<ID3D11PixelShader> PS_NoLight;
	static ComPtr<ID3D11PixelShader> PS_Normal;
	static ComPtr<ID3D11PixelShader> PS_NormalSpecular;
	static ComPtr<ID3D11PixelShader> PS_Shadow;
	static ComPtr<ID3D11PixelShader> PS_Reflection;
	static ComPtr<ID3D11PixelShader> PS_Blur;

	static void CreateVertexShader(ComPtr<ID3D11VertexShader>& shader, LPCWSTR path);
	static void CreateInputLayout(ComPtr<ID3D11InputLayout>& inputLayout, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);
	static void CreatePixelShader(ComPtr<ID3D11PixelShader>& shader, LPCWSTR path);

	static UINT currentVSShaderID;
	static UINT lastVSShaderID;
	static UINT currentPSShaderID;
	static UINT lastPSShaderID;

	static bool restrictShader;

public:
	static void Initialize();

	static void SetVSShader(UINT id);
	static void SetPSShader(UINT id);

	static void SetLastShader();

	static void SetRestrictShader() { restrictShader = !restrictShader; }
};
