#pragma once

struct AnimationData
{
	UINT action;
	UINT duration;
};

enum TextureID
{
	textureSkyFront,
	textureSkyBack,
	textureSkyLeft,
	textureSkyRight,
	textureSkySky,
	textureSkyFloor,
	textureAsh,
	textureAshN,
	textureLava,
	textureLavaN,

	textureWhite,
	textureGrey,
	textureBlack,
	textureRed,
	textureGreen,
	textureBlue,
	textureMax
};

enum ModelID
{
	modelCastle,
	modelNanosuit,
	modelMax
};

class Material
{
private:
	static std::vector<Texture> textures;
	static std::vector<Model> models;

public:
	static void Initialize();
	static void Finalize();

	//Calling this function can passing in the texture to shader automatically.
	static void SetTexture(UINT ID, UINT map);
	
	//Calling this function can render the model automatically.
	static void SetModel(UINT ID, XMMATRIX worldMatrix);
	static void SetModel(UINT ID, std::vector<Collision*> collisions, XMMATRIX worldMatrix);

	static Texture GetTexture(UINT ID);
	static Model GetModel(UINT ID);
};
