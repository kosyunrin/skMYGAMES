#include "engine.h"
#include "collision.h"

void Collision::Initialize(std::vector<XMFLOAT3> vertices, std::vector<DWORD> indices)
{
	this->vertices = vertices;
	this->indices = indices;

	boundingBox = new BoundingBox;
	this->boundingBox->Initialize(this->vertices);
}

void Collision::Update(XMMATRIX worldMatrix)
{
	this->worldMatrix = worldMatrix;
	this->boundingBox->Update(this->worldMatrix);
}

void Collision::Update(std::vector<XMFLOAT3> vertices, std::vector<DWORD> indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->boundingBox->Update(this->vertices);
}

void Collision::Render()
{
	this->boundingBox->Render();
}