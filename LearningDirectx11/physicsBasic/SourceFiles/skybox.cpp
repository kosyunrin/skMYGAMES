#include "engine.h"
#include "skybox.h"

Skybox::Skybox()
{
	this->m_Scale = XMFLOAT3(800.0f, 800.0f, 800.0f);
	this->Initialize();
}

void Skybox::Initialize()
{
	Vertex v[] =
	{
		//Front
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f) },
		//Back
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		//Left
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		//Right
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f) },
		//Sky
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
		//Floor
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f) }
	};

	VertexBuffer<Vertex>::CreateVertexBuffer(vertexBuffer, v, ARRAYSIZE(v));
}

void Skybox::Update()
{
	/*--------------------------------------------------------------------------------
	Matrix Transform
	--------------------------------------------------------------------------------*/
	frontMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	backMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	leftMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	rightMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	skyMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	floorMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	/*--------------------------------------------------------------------------------
	Follow Camera
	--------------------------------------------------------------------------------*/
	XMFLOAT3 cameraPos = Camera::GetPosition();
	XMMATRIX cameraPosMatrix = XMMatrixTranslation(cameraPos.x, cameraPos.y, cameraPos.z);

	frontMatrix = frontMatrix * cameraPosMatrix;
	backMatrix = backMatrix * cameraPosMatrix;
	leftMatrix = leftMatrix * cameraPosMatrix;
	rightMatrix = rightMatrix * cameraPosMatrix;
	skyMatrix = skyMatrix * cameraPosMatrix;
	floorMatrix = floorMatrix * cameraPosMatrix;
}

void Skybox::Render(bool boundingBox)
{
	Shader::SetVSShader(VSShaderID::VS_Basic);
	Shader::SetPSShader(PSShaderID::PS_NoLight);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());

	/*--------------------------------------------------------------------------------
	Render
	--------------------------------------------------------------------------------*/
	Material::SetTexture(TextureID::textureSkyFront, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&frontMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 0);

	Material::SetTexture(TextureID::textureSkyBack, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&backMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 4);
	
	Material::SetTexture(TextureID::textureSkyLeft, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&leftMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 8);
	
	Material::SetTexture(TextureID::textureSkyRight, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&rightMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 12);
	
	Material::SetTexture(TextureID::textureSkySky, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&skyMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 16);
	
	Material::SetTexture(TextureID::textureSkyFloor, TextureMapID::DiffuseMap);
	ConstantBuffer::SetWorldMatrix(&floorMatrix);
	VertexBuffer<Vertex>::SetTriangleStrip(4, 20);
}