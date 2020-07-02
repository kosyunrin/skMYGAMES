#include "engine.h"
#include "boundingBox.h"

void BoundingBox::Initialize(std::vector<XMFLOAT3> vertices)
{
	worldMatrix = XMMatrixIdentity();

	min = vertices[0];
	max = vertices[0];

	for (int index = 0; index < vertices.size(); index++)
	{
		min.x = Engine::min(min.x, vertices[index].x);
		min.y = Engine::min(min.y, vertices[index].y);
		min.z = Engine::min(min.z, vertices[index].z);

		max.x = Engine::max(max.x, vertices[index].x);
		max.y = Engine::max(max.y, vertices[index].y);
		max.z = Engine::max(max.z, vertices[index].z);
	}

	/*--------------------------------------------------------------------------------
	Create Vertex
	--------------------------------------------------------------------------------*/
	//Top vertex
	v[0] = XMFLOAT3(min.x, max.y, min.z);
	v[1] = XMFLOAT3(max.x, max.y, min.z);
	v[2] = XMFLOAT3(min.x, max.y, max.z);
	v[3] = XMFLOAT3(max.x, max.y, max.z);
	//Bottom vertex
	v[4] = XMFLOAT3(min.x, min.y, min.z);
	v[5] = XMFLOAT3(max.x, min.y, min.z);
	v[6] = XMFLOAT3(min.x, min.y, max.z);
	v[7] = XMFLOAT3(max.x, min.y, max.z);

	DWORD i[] =
	{
		0, 1, 4, 4, 1, 5, //Front
		3, 2, 7, 7, 2, 6, //Back
		2, 3, 0, 0, 3, 1, //Top
		4, 5, 6, 6, 5, 7, //Bottom
		2, 0, 6, 6, 0, 4, //Left
		1, 3, 5, 5, 3, 7  //Right
	};

	for (int index = 0; index < ARRAYSIZE(i); index++)
		boundingVertices.push_back(v[i[index]]);

	boundingVerticesWorld.resize(boundingVertices.size());

	/*--------------------------------------------------------------------------------
	Transform vertex into world space
	--------------------------------------------------------------------------------*/
	minWorld = Engine::VertexToWorld(v[0], worldMatrix);
	maxWorld = Engine::VertexToWorld(v[0], worldMatrix);

	for (int index = 0; index < ARRAYSIZE(v); index++)
	{
		XMFLOAT3 temp = Engine::VertexToWorld(v[index], worldMatrix);

		minWorld.x = Engine::min(minWorld.x, temp.x);
		minWorld.y = Engine::min(minWorld.y, temp.y);
		minWorld.z = Engine::min(minWorld.z, temp.z);

		maxWorld.x = Engine::max(maxWorld.x, temp.x);
		maxWorld.y = Engine::max(maxWorld.y, temp.y);
		maxWorld.z = Engine::max(maxWorld.z, temp.z);
	}

	/*--------------------------------------------------------------------------------
	Create Border Line
	--------------------------------------------------------------------------------*/
	Vertex borderVertex[] =
	{
		//Top
		{XMFLOAT3(min.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		//Bottom
		{XMFLOAT3(min.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		//Leg
		{XMFLOAT3(min.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, min.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(max.x, max.y, min.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, min.y, max.z), XMFLOAT2(0.0f, 0.0f) },
		{XMFLOAT3(min.x, max.y, max.z), XMFLOAT2(0.0f, 0.0f) },
	};

	VertexBuffer<Vertex>::CreateVertexBuffer(vertexBuffer, borderVertex, ARRAYSIZE(borderVertex));
}

void BoundingBox::Update(XMMATRIX worldMatrix)
{
	this->worldMatrix = worldMatrix;

	/*--------------------------------------------------------------------------------
	Transform vertex into world space
	--------------------------------------------------------------------------------*/
	minWorld = Engine::VertexToWorld(v[0], worldMatrix);
	maxWorld = Engine::VertexToWorld(v[0], worldMatrix);

	for (int index = 0; index < ARRAYSIZE(v); index++)
	{
		XMFLOAT3 temp = Engine::VertexToWorld(v[index], worldMatrix);

		minWorld.x = Engine::min(minWorld.x, temp.x);
		minWorld.y = Engine::min(minWorld.y, temp.y);
		minWorld.z = Engine::min(minWorld.z, temp.z);

		maxWorld.x = Engine::max(maxWorld.x, temp.x);
		maxWorld.y = Engine::max(maxWorld.y, temp.y);
		maxWorld.z = Engine::max(maxWorld.z, temp.z);
	}

	/*--------------------------------------------------------------------------------
	Transform bounding vertex into world space
	--------------------------------------------------------------------------------*/
	for (int index = 0; index < boundingVertices.size(); index++)
		boundingVerticesWorld[index] = Engine::VertexToWorld(boundingVertices[index], worldMatrix);
}

void BoundingBox::Update(std::vector<XMFLOAT3> vertices)
{
	this->vertexBuffer = nullptr;
	this->Initialize(vertices);
}

void BoundingBox::Render()
{
	Shader::SetVSShader(VSShaderID::VS_Basic);
	Shader::SetPSShader(PSShaderID::PS_NoLight);

	Material::SetTexture(TextureID::textureWhite, TextureMapID::DiffuseMap);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
	ConstantBuffer::SetWorldMatrix(&worldMatrix);
	VertexBuffer<Vertex>::SetLineList(24, 0);

	Shader::SetLastShader();
}