#include "engine.h"
#include "plane.h"

Plane::Plane(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID)
{
	this->m_Position = position;
	this->m_Rotation = rotation;
	this->m_Scale = scaling;
	this->seamx = scaling.x;
	this->seamz = scaling.z;
	this->ID = ID;
	this->enableReflection = true;
	this->Initialize();
}

void Plane::Initialize()
{
	if (seamx < 1.0f)
		seamx = 1.0f;
	if (seamz < 1.0f)
		seamz = 1.0f;

	Vertex v[] =
	{
		{ XMFLOAT3(-0.5f, 0.0f, 0.5f),	XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, 0.0f, 0.5f),	XMFLOAT2(seamx, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, 0.0f, -0.5f),	XMFLOAT2(0.0f, seamz), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, 0.0f, -0.5f),	XMFLOAT2(seamx, seamz), XMFLOAT3(0.0f, 1.0f, 0.0f)}
	};

	DWORD i[] =
	{
		0, 1, 2, 2, 1, 3
	};

	//Tangent
	Engine::CalculateTangent(v, ARRAYSIZE(i));

	VertexBuffer<Vertex>::CreateVertexBuffer(vertexBuffer, v, ARRAYSIZE(v));
	IndexBuffer::CreateIndexBuffer(indexBuffer, i, ARRAYSIZE(i));

	for (int index = 0; index < ARRAYSIZE(v); index++)
		vertices.push_back(v[index].Position);
	for (int index = 0; index < ARRAYSIZE(i); index++)
		indices.push_back(i[index]);

	/*--------------------------------------------------------------------------------
	Collision Data
	--------------------------------------------------------------------------------*/
	Collision* c = new Collision;

	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	c->Initialize(vertices, indices);

	myCollisions.push_back(c);
}

void Plane::Update()
{
	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	GameObject::Update();
}

void Plane::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	Shader::SetVSShader(VSShaderID::VS_Basic);

	if (enableReflection)
		Shader::SetPSShader(PSShaderID::PS_Reflection);
	else
		Shader::SetPSShader(PSShaderID::PS_Normal);

	Material::SetTexture(ID, TextureMapID::DiffuseMap);
	Material::SetTexture((ID + 1), TextureMapID::NormalMap);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
	IndexBuffer::SetIndexBuffer(indexBuffer.Get());
	ConstantBuffer::SetWorldMatrix(&worldMatrix);
	IndexBuffer::SetTriangleList(indices.size(), 0, 0);
}