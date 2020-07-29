#pragma once
#define INSTANCEMAX 20
#define BONEMAX 100

struct ShadowSettings
{
	ShadowSettings() {}
	ShadowSettings(float bias, float color)
	{
		Bias = bias;
		ShadowColor = color;
		Empty = XMFLOAT2(0, 0);
	}

	float Bias;
	float ShadowColor;
	XMFLOAT2 Empty;
};

struct BlurSettings
{
	BlurSettings() {}
	BlurSettings(float width, float height, float factor)
	{
		Width = width;
		Height = height;
		Factor = factor;
		Empty = 0;
	}

	float Width;
	float Height;
	float Factor;
	float Empty;
};

class ConstantBuffer
{
private:
	//VS
	static ComPtr<ID3D11Buffer> worldBuffer;
	static ComPtr<ID3D11Buffer> viewBuffer;
	static ComPtr<ID3D11Buffer> projectionBuffer;
	static ComPtr<ID3D11Buffer> cameraBuffer;
	static ComPtr<ID3D11Buffer> bonesBuffer;
	static ComPtr<ID3D11Buffer> reflectionBuffer;

	//PS
	static ComPtr<ID3D11Buffer> shadowBuffer;
	static ComPtr<ID3D11Buffer> blurBuffer;

	static void VS();
	static void PS();

public:
	static void Initialize();

	/*--------------------------------------------------------------------------------
	Vertex Shader
	--------------------------------------------------------------------------------*/
	//Set the world matrix for 2D sprite use.
	static void SetWorldMatrix2D();

	//Set the world matrix for 3D object use.
	static void SetWorldMatrix(XMMATRIX* matrix);

	//Set the view matrix for camera view point.
	static void SetViewMatrix(XMMATRIX* matrix);

	//Set the projection matrix for camera projection.
	static void SetProjectionMatrix(XMMATRIX* matrix);

	//Set the camera position for passing it into shader.
	static void SetCamera(XMFLOAT3 position);

	//Set the bones matrix for skinned mesh animation.
	static void SetBones(std::vector<XMFLOAT4X4>& transforms);

	//Set the reflection matrix for reflection RTT use.
	static void SetReflectionMatrix(XMMATRIX* matrix);

	/*--------------------------------------------------------------------------------
	Pixel Shader
	--------------------------------------------------------------------------------*/
	//Set the shadow map settings for calculating the shadow use.
	static void SetShadowSettings(ShadowSettings settings);

	//Set the blur factor for calculating the blur texture use.
	static void SetBlurSettings(BlurSettings settings);
};