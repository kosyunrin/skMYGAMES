#include "engine.h"
#include "cube.h"

Cube::Cube(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID)
{
	this->m_Position = position;
	this->m_Rotation = rotation;
	this->m_Scale = scaling;
	this->seamx = scaling.x;
	this->seamy = scaling.y;
	this->seamz = scaling.z;
	this->ID = ID;
	this->Initialize();
}

void Cube::Initialize()
{
	if (seamx < 1.0f)
		seamx = 1.0f;
	if (seamy < 1.0f)
		seamy = 1.0f;
	if (seamz < 1.0f)
		seamz = 1.0f;

	Vertex v[] =
	{
		//Front
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f),	XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(0.5f, 0.5f, -0.5f),	XMFLOAT2(seamx, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT2(0.0f, seamy), XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT2(seamx, seamy),XMFLOAT3(0.0f, 0.0f, -1.0f)},
		//Back																							 
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),	XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT2(seamx, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(0.5f, -0.5f, 0.5f),	XMFLOAT2(0.0f, seamy), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f),	XMFLOAT2(seamx, seamy),XMFLOAT3(0.0f, 0.0f, 1.0f)},
		//Left																								
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f),	XMFLOAT2(seamz, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f),	XMFLOAT2(0.0f, seamy), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT2(seamz, seamy),XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		//Right																							
		{ XMFLOAT3(0.5f, 0.5f, -0.5f),	XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),	XMFLOAT2(seamz, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT2(0.0f, seamy), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(0.5f, -0.5f, 0.5f),	XMFLOAT2(seamz, seamy),XMFLOAT3(1.0f, 0.0f, 0.0f)},
		//Sky																								
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),	XMFLOAT2(seamx, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f),	XMFLOAT2(0.0f, seamz), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, 0.5f, -0.5f),	XMFLOAT2(seamx, seamz),XMFLOAT3(0.0f, 1.0f, 0.0f)},
		//Bottom																						
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT2(0.0f, 0.0f),  XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),	XMFLOAT2(seamx, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f),	XMFLOAT2(0.0f, seamz), XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{ XMFLOAT3(0.5f, -0.5f, 0.5f),	XMFLOAT2(seamx, seamz),XMFLOAT3(0.0f, -1.0f, 0.0f)}
	};

	DWORD i[] =
	{
		0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20, 21, 22, 22, 21, 23
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

void Cube::Update()
{
	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	GameObject::Update();
}

void Cube::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	if (Camera::GetVisibility(myCollisions[0]->GetBoundingBox()->GetMinWorld(), myCollisions[0]->GetBoundingBox()->GetMaxWorld()));
	{
		Shader::SetVSShader(VSShaderID::VS_Basic);
		Shader::SetPSShader(PSShaderID::PS_Normal);

		Material::SetTexture(ID, TextureMapID::DiffuseMap);

		VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
		IndexBuffer::SetIndexBuffer(indexBuffer.Get());
		ConstantBuffer::SetWorldMatrix(&worldMatrix);
		IndexBuffer::SetTriangleList(indices.size(), 0, 0);
	}
}