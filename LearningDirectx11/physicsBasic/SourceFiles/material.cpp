#include "engine.h"
#include "material.h"

#define TEXTUREMAX (sizeof(texturePath) / sizeof(texturePath[0]))
#define MODELMAX (sizeof(modelPath) / sizeof(modelPath[0]))

std::vector<Texture> Material::textures;
std::vector<Model> Material::models;

//Add path here if you want to preload any other texture.
std::string texturePath[] =
{
	{"./Asset/Skymap/Front.png"},
	{"./Asset/Skymap/Back.png"},
	{"./Asset/Skymap/Left.png"},
	{"./Asset/Skymap/Right.png"},
	{"./Asset/Skymap/Sky.png"},
	{"./Asset/Skymap/Floor.png"},
	{"./Asset/Ash.png"},
	{"./Asset/Ash_n.png"},
	{"./Asset/LavaGround.png"},
	{"./Asset/LavaGround_n.png"}
};

//Add path here if you want to preload any other model.
std::string modelPath[] =
{
	{"./Asset/Castle/Castle Pack.obj"},
	{"./Asset/nanosuit/nanosuit.obj"}
};

void Material::Initialize()
{
	//Preload texture
	for (int index = 0; index < TEXTUREMAX; index++)
		textures.push_back(Texture(texturePath[index]));

	textures.push_back(Texture(Color(255, 255, 255))); //White
	textures.push_back(Texture(Color(100, 100, 100))); //Grey
	textures.push_back(Texture(Color(0, 0, 0))); //Black
	textures.push_back(Texture(Color(255, 0, 0))); //Red
	textures.push_back(Texture(Color(0, 255, 0))); //Green
	textures.push_back(Texture(Color(0, 0, 255))); //Blue

	//Preload Model
	for (int index = 0; index < MODELMAX; index++)
		models.push_back(Model(modelPath[index]));
}

void Material::Finalize()
{
	textures.clear();
	models.clear();
}

void Material::SetTexture(UINT ID, UINT map)
{
	textures[ID].SetTexture(map);
}

void Material::SetModel(UINT ID, XMMATRIX worldMatrix)
{
	models[ID].Render(worldMatrix);
}

void Material::SetModel(UINT ID, std::vector<Collision*> collisions, XMMATRIX worldMatrix)
{
	models[ID].Render(collisions, worldMatrix);
}

Texture Material::GetTexture(UINT ID) { return textures[ID]; }
Model Material::GetModel(UINT ID) { return models[ID]; }
