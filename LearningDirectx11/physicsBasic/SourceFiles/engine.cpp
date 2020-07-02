#include "engine.h"

void Engine::Initialize()
{
	Renderer::Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	Input::Initialize();
	Shader::Initialize();
	ConstantBuffer::Initialize();
	Sound::Initialize();
	Material::Initialize();
	Sprite::Initialize();
}

void Engine::Update()
{
	Input::Update();
}

void Engine::Finalize()
{
	Material::Finalize();
	Sound::Finalize();
}

std::wstring Engine::StringToWString(std::string str)
{
	std::wstring wc(str.begin(), str.end());
	return wc;
}

void Engine::ErrorMsg(std::string str)
{
	std::wstring wc = StringToWString(str);
	MessageBoxW(NULL, wc.c_str(), (L"Error"), MB_ICONERROR);
}

XMMATRIX Engine::WorldTransform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling)
{
	XMMATRIX world = XMMatrixIdentity();

	rotation = XMFLOAT3(XMConvertToRadians(rotation.x), XMConvertToRadians(rotation.y), XMConvertToRadians(rotation.z));

	world = XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
	XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
	XMMatrixTranslation(position.x, position.y, position.z);

	return world;
}

XMMATRIX Engine::WorldTransformRotAfter(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling)
{
	XMMATRIX world = XMMatrixIdentity();

	rotation = XMFLOAT3(XMConvertToRadians(rotation.x), XMConvertToRadians(rotation.y), XMConvertToRadians(rotation.z));

	world = XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
	XMMatrixTranslation(position.x, position.y, position.z) *
	XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	return world;
}

XMMATRIX Engine::WorldTransform(XMFLOAT3 position, XMVECTOR rotation, XMFLOAT3 scaling)
{
	XMMATRIX world = XMMatrixIdentity();

	world = XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
	XMMatrixRotationQuaternion(rotation) *
	XMMatrixTranslation(position.x, position.y, position.z);

	return world;
}

XMMATRIX Engine::WorldTransformRotAfter(XMFLOAT3 position, XMVECTOR rotation, XMFLOAT3 scaling)
{
	XMMATRIX world = XMMatrixIdentity();

	world = XMMatrixScaling(scaling.x, scaling.y, scaling.z) *
	XMMatrixTranslation(position.x, position.y, position.z) *
	XMMatrixRotationQuaternion(rotation);

	return world;
}

void Engine::Clamp(float& value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
}

int Engine::min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

int Engine::max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

float Engine::min(float x, float y)
{
	if (x < y)
		return x;
	else
		return y;
}

float Engine::max(float x, float y)
{
	if (x > y)
		return x;
	else
		return y;
}

void Engine::Interpolate(float& current, float target, float speed)
{
	if (current < target)
		current += speed;
	if (current > target)
		current -= speed;
}

void Engine::Interpolate(XMFLOAT3& current, XMFLOAT3 target, float speed)
{
	if (current.x < target.x)
		current.x += speed;
	if (current.x > target.x)
		current.x -= speed;
	if (current.y < target.y)
		current.y += speed;
	if (current.y > target.y)
		current.y -= speed;
	if (current.z < target.z)
		current.z += speed;
	if (current.z > target.z)
		current.z -= speed;
}

XMFLOAT3 Engine::VertexToWorld(XMFLOAT3 v, XMMATRIX worldMatrix)
{
	XMVECTOR vec = XMLoadFloat3(&v);
	vec = XMVector3TransformCoord(vec, worldMatrix);
	XMFLOAT3 out;
	XMStoreFloat3(&out, vec);

	return out;
}

void Engine::CalculateTangent(Vertex v[], UINT indicesCount)
{
	for (int index = 0; index < indicesCount / 6; index++)
	{
		Engine::CalculateTangent(v[index * 4], v[index * 4 + 1], v[index * 4 + 2], v[index * 4].Tangent, v[index * 4].Bitangent);
		Engine::CalculateTangent(v[index * 4 + 1], v[index * 4], v[index * 4 + 2], v[index * 4 + 1].Tangent, v[index * 4 + 1].Bitangent);
		Engine::CalculateTangent(v[index * 4 + 2], v[index * 4], v[index * 4 + 1], v[index * 4 + 2].Tangent, v[index * 4 + 2].Bitangent);
		Engine::CalculateTangent(v[index * 4 + 3], v[index * 4 + 1], v[index * 4 + 2], v[index * 4 + 3].Tangent, v[index * 4 + 3].Bitangent);
	}
}

void Engine::CalculateTangent(Vertex v1, Vertex v2, Vertex v3, XMFLOAT3& tangent, XMFLOAT3& bitangent)
{
	XMFLOAT3 edge1, edge2;
	XMFLOAT2 texEdge1, texEdge2;

	//Edge1
	edge1.x = v2.Position.x - v1.Position.x;
	edge1.y = v2.Position.y - v1.Position.y;
	edge1.z = v2.Position.z - v1.Position.z;

	//Edge2
	edge2.x = v3.Position.x - v1.Position.x;
	edge2.y = v3.Position.y - v1.Position.y;
	edge2.z = v3.Position.z - v1.Position.z;

	//TexEdge1
	texEdge1.x = v2.TexCoord.x - v1.TexCoord.x;
	texEdge1.y = v2.TexCoord.y - v1.TexCoord.y;

	//TexEdge2
	texEdge2.x = v3.TexCoord.x - v1.TexCoord.x;
	texEdge2.y = v3.TexCoord.y - v1.TexCoord.y;

	float den = 1.0f / (texEdge1.x * texEdge2.y - texEdge1.y * texEdge2.x);

	//Tangent
	tangent.x = den * (texEdge2.y * edge1.x - texEdge1.y * edge2.x);
	tangent.y = den * (texEdge2.y * edge1.y - texEdge1.y * edge2.y);
	tangent.z = den * (texEdge2.y * edge1.z - texEdge1.y * edge2.z);

	//Bitangent
	bitangent.x = den * (-texEdge2.x * edge1.x + texEdge1.x * edge2.x);
	bitangent.y = den * (-texEdge2.x * edge1.y + texEdge1.x * edge2.y);
	bitangent.z = den * (-texEdge2.x * edge1.z + texEdge1.x * edge2.z);
}
