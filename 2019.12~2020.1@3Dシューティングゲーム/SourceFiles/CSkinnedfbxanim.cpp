#include "main.h"
#include "CSkinnedfbxanim.h"
CSkinnedfbxanim::CSkinnedfbxanim( SFbxanimtype t[], int animCount)
{
	bonesCount = 0;
	currentAnimation = 0;//
	nextAnimation = 0;

	animTime1 = 0.0f;
	animTime2 = 0.0f;
	blendTime = 0.0f;
	animShow = false;
	this->Load(t,animCount);
}

CSkinnedfbxanim::~CSkinnedfbxanim()
{
	meshes.clear();
	for (int i = 0; i < 5; i++)
	{
		importers[i].FreeScene();
	}
}
void CSkinnedfbxanim::Load( SFbxanimtype t[], int animCount)
{
	this->ai_Scenesload(t, animCount);
	//modelpath = path;
	//ai_Scenes[0] = importer.ReadFile(t[0].name, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if (ai_Scenes[0] == nullptr)
	{
		//Engine::ErrorMsg("aiScene Create Failed");
		MessageBox(0, "Modelload  - Failed",
			"Error", MB_OK);
		return;
	}
	//this->ai_Scenesload(t,animCount);

	//GlobalInverse Matrix
	XMVECTOR determinant;
	XMMATRIX GlobalInversex = XMMATRIX(&ai_Scenes[0]->mRootNode->mTransformation.a1);
	GlobalInversex = XMMatrixInverse(&determinant, GlobalInversex);
	XMStoreFloat4x4(&GlobalInversef, GlobalInversex);

	//GlobalInverse = XMMATRIX(&ai_Scene->mRootNode->mTransformation.a1);
	//GlobalInverse = XMMatrixInverse(&determinant, GlobalInverse);

	this->ProcessNode(ai_Scenes[0]->mRootNode);
	//setboxV
	MeshPart* meshpart = new MeshPart[meshes.size()];
	for (int index = 0; index < meshes.size(); index++)
	{
		meshes[index]->vertexBuffer = CVertexBuffer<BonesVertex>::CreatVertexBuffer(meshes[index]->vertices.data(), meshes[index]->vertices.size());
		//meshes[index]->vertexBuffer = CVertexBuffer<VERTEX_3D>::CreatVertexBuffer(meshes[index]->vs.data(), meshes[index]->vs.size());
		meshes[index]->indexBuffer = CIndexBuffer<DWORD>::CreatIndexBuffer(NULL, meshes[index]->indices.data(), meshes[index]->indices.size());

		//getboxVertex
		meshpart[index].m_BoxPoint.Vmax = meshes[index]->vertices[0].Position;
		meshpart[index].m_BoxPoint.Vmin = meshes[index]->vertices[0].Position;
		for (UINT g = 0; g < meshes[index]->vertices.size(); g++)
		{
			XMFLOAT3 meshPos = meshes[index]->vertices[g].Position;
			meshpart[index].m_BoxPoint.Vmax = Tool::GET_MAX_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmax);
			meshpart[index].m_BoxPoint.Vmin = Tool::GET_MIN_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmin);
		}
		V_m_meshPart.push_back(meshpart[index]);
	}
}

void CSkinnedfbxanim::Update(float dt, float speed)
{
	animTime1 += (speed *dt);
	animTime2 += (speed *dt);

	if (blendTime >= 0.0f)
		blendTime -= 5.0f*speed*dt;
}

void CSkinnedfbxanim::InstanceUpdate(float dt, float speed)
{
	animTime1 += (speed *dt);
	animTime2 += (speed *dt);
	for (int i = 0; i < INSTANCEMAX; i++)
	{
		/*InsanimTime[i] += speed * dt;
		InsanimaTime2[i] += speed * dt;*/

		if (Insblend[i] >= 0.0f)
			Insblend[i] -= 5.0f*speed*dt;
	}
}

void CSkinnedfbxanim::ResetTimer()
{
	animTime1 = 0.0f;
	animTime2 = 0.0f;
}

void CSkinnedfbxanim::Insanimation( int animtionx)
{
	for (UINT i = 0; i < INSTANCEMAX; i++)
	{
		InscurrentAnimation[i] = animtionx;
	}
}

std::vector<MeshPart> CSkinnedfbxanim::m_GetBoxPinots()
{
	return V_m_meshPart;
}

std::vector<Material> CSkinnedfbxanim::MaterialTexture(const aiScene * scene, aiMaterial * material)
{
	std::vector<Material> GetMaterial;
	UINT TextureGrainCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	if (TextureGrainCount == 0)
	{
		aiColor3D aicolor;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, aicolor);
		if (aicolor.IsBlack())
		{
			GetMaterial.push_back(Material(&MaterialColor(100, 100, 100, 255), 1, 1));
			return GetMaterial;
		}
		GetMaterial.push_back(Material(&MaterialColor(aicolor.r * 255, aicolor.b * 255, aicolor.g * 255, 255), 1, 1));
		return GetMaterial;
	}
	else
	{
		for (UINT index = 0; index < TextureGrainCount; index++)
		{
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, index, &path);//ｴﾓｲﾄﾖﾊｻ｡ﾌﾘｶｨｵﾄｲﾎﾊ
			std::string 
			modelpath = path.data;
			size_t Pos = modelpath.find_last_of("\\/");
			std::string texName = modelpath.substr(Pos + 1, modelpath.size() - Pos);
			GetMaterial.push_back(Material(texName));
		}
		return GetMaterial;
	}
}
void CSkinnedfbxanim::ai_Scenesload( SFbxanimtype t[], int animCount)
{
	//m_Scene[1] = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_CalcTangentSpace |//ﾗﾔｶｯｼﾆﾋ翩ﾐﾏﾟｺﾍｷｨﾏﾟ
	//	aiProcess_Triangulate |//ﾗﾔｶｯﾋﾄｱﾟﾐﾎﾗｪｻｻﾎｪﾈｽﾇﾐﾎ
	//	aiProcess_JoinIdenticalVertices | //ｺﾏｲ｢ﾏ猩ｬｵﾄｶ･ｵ・
	//	aiProcess_ConvertToLeftHanded);
		for (int i = 0; i < animCount; i++)
		{
			ai_Scenes[i]= importers[i].ReadFile(t[i].name, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs| aiProcess_ConvertToLeftHanded);//aiProcess_Triangulate  bian3 jiao//aiProcess_FlipUVs//tu pian zuoyou huan
		}
}

void CSkinnedfbxanim::SetInstanceBoneMatrix(std::vector<XMFLOAT4X4>& transform)
{
	//Insanim.BoneSwitch[0][0] = true;
	//Insanim.BoneSwitch[0][1] = 0;
	for (UINT i = 0; i < transform.size(); i++)
	{
		//bool asd = false;
		Insanim[0].BoneMarix[i] =  transform[i];
		//Insanim.BoneSwitch[i] = false;
	}
}

void CSkinnedfbxanim::SetInsWorldBuffer(XMFLOAT4X4 world[])
{
	for (UINT i = 0; i < INSTANCEMAX; i++)
	{
		XMMATRIX tes=
		 XMMatrixTranspose(XMLoadFloat4x4(&world[i]));
		XMStoreFloat4x4(&Insanim[i].Instanceworld, tes);
	}
}

bool CSkinnedfbxanim::AiamFramManager(float FramCount, int currentanim)
{
	//float CurrentAimFram = (int)(NextAimCurrentFrama + 0.5f);
	if (blendTime <= 0)
    if(currentAnimation == currentanim)
	{
		if (NextAimCurrentFrama >= FramCount)
			return true;
	}
	return false;
}

bool CSkinnedfbxanim::AiamFramManager2(float FramCount, int currentanim)
{
	//float CurrentAimFram = (int)(NextAimCurrentFrama + 0.5f);
		if (currentAnimation == currentanim)
		{
			if (NextAimCurrentFrama >= FramCount)
				return true;
		}
	return false;
}

bool CSkinnedfbxanim::PlayShot()
{
	if (blendTime <= 0)
		return true;
	return false;
}

bool CSkinnedfbxanim::PlyaerOne(float FramCount, int currentanim, bool& isboolx)
{
	if (isboolx == false)
	{
		if(blendTime<=0)
		if (currentAnimation == currentanim)
		{
			if (NextAimCurrentFrama >= FramCount)
			{
				isboolx = true;
				return true;
			}
		}
	}
	return false;
}

bool CSkinnedfbxanim::PlayerOnce(float FramCount, int currentanim, bool & isboolx)
{
	if (isboolx == false)
	{
		if (blendTime <= 0)
			if (currentAnimation == currentanim)
			{
				if (NextAimCurrentFrama2 >= FramCount)
				{
					isboolx = true;
					return true;
				}
			}
	}
	if (NextAimCurrentFrama2 < FramCount) isboolx = false;
	return false;
}

bool CSkinnedfbxanim::AnimShow(float framcount, int currentanim)
{
	if (NextAimCurrentFrama <= framcount - 3.0f)
		animShow = false;
	if (blendTime <= 0.0f)
	{
		if (!animShow)
		{
			if (currentAnimation == currentanim)
			{
				if (NextAimCurrentFrama >= framcount) { animShow = true; return true; }
			}
		}
	}
	return false;
}

INSTANCEBUFFER * CSkinnedfbxanim::GetInsBuffer()
{
	return Insanim;
}

void CSkinnedfbxanim::CpuPosUpdate()
{
	/*for (int index = 0; index < meshes.size(); index++)
	{
		for (UINT g = 0; g < meshes[index]->vertices.size(); g++)
		{
			XMFLOAT3 meshPos = meshes[index]->vertices[g].Position;
			meshpart[index].m_BoxPoint.Vmax = Tool::GET_MAX_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmax);
			meshpart[index].m_BoxPoint.Vmin = Tool::GET_MIN_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmin);
		}
		V_m_meshPart.push_back(meshpart[index]);*/
}

void CSkinnedfbxanim::AddPartMeshes(std::vector<SStaticMode*> partmesh)
{
	for (UINT i = 0; i < partmesh.size(); i++)
	{
		SkinnedMesh* skinmesh = new SkinnedMesh;

		skinmesh->vertexBuffer = partmesh[i]->vertexBuffer;
		skinmesh->indexBuffer = partmesh[i]->indexBuffer;
		for (UINT j = 0; j < partmesh[i]->vs.size(); j++)
		{
			BonesVertex bonevs;
			bonevs.Position = partmesh[i]->vs[j].Position;
			bonevs.Normal = partmesh[i]->vs[j].Normal;
			bonevs.TexCoord = partmesh[i]->vs[j].TexCoord;
			//bonevs.AddBoneDatas(48, 1.0f);
			bonevs.boneID[0] = 48;
			bonevs.boneweights[0] = 1.0f;

			skinmesh->vertices.push_back(bonevs);
		}
		for (UINT k = 0; k < partmesh[i]->indices.size(); k++)
		{
			DWORD ind = partmesh[i]->indices[k];
			skinmesh->indices.push_back(ind);
		}
		for (UINT y = 0; y < partmesh[i]->material.size(); y++)
		{
			Material m = partmesh[i]->material[y];
			skinmesh->material.push_back(m);
		}
		meshes.push_back(skinmesh);
	}

}

void CSkinnedfbxanim::WeaponBoneTransform(std::vector<XMFLOAT4X4>& transform)
{
	//XMMATRIX parentMatrix = XMMatrixRotationX(XMConvertToRadians(-90));
	//parentMatrix *= XMMatrixRotationY(XMConvertToRadians(135));
	XMMATRIX parentMatrix = XMMatrixIdentity();

	//Animation Blend
	const aiAnimation* Aanimation = NULL;
	const aiAnimation* Aanimation1 = NULL;
	if (blendTime > 0.0f)
	{

		int animationtimer;
		Aanimation = ai_Scenes[currentAnimation]->mAnimations[0];
		animationtimer = Aanimation->mDuration;

		float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
			Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		float animationTime1 = fmod(timeInTicks, animationtimer);//アニメーション時間


		int animationtimers;
		Aanimation1 = ai_Scenes[nextAnimation]->mAnimations[0];
		animationtimers = Aanimation1->mDuration;

		ticksPerSecond = Aanimation1->mTicksPerSecond != 0 ?
			Aanimation1->mTicksPerSecond : ticksPerSecond = 25.0f;
		timeInTicks = animTime2 * ticksPerSecond;
		float animationTime2 = fmod(timeInTicks, animationtimers);

		WeaponReadNodeHeirarchy(ai_Scenes[0]->mRootNode, ai_Scenes[0]->mRootNode, parentMatrix, animationTime1, animationTime2, currentAnimation, nextAnimation, Aanimation, Aanimation1);
	}
	else
	{

		//
		int animationtimer;
		Aanimation = ai_Scenes[currentAnimation]->mAnimations[0];
		animationtimer = Aanimation->mDuration;

		float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
			Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;

		float animationTime = fmod(timeInTicks, animationtimer);
		float animFramManagertimer = fmod(timeInTicks, animationtimer + 10.0f);
		NextAimCurrentFrama = animFramManagertimer;
		NextAimCurrentFrama2 = animationTime;
		WeaponReadNodeHeirarchy(ai_Scenes[0]->mRootNode, parentMatrix, animationTime, currentAnimation, Aanimation);
		//if(animationTime)
	}

	/*--------------------------------------------------------------------------------
	Send All Bones Data
	--------------------------------------------------------------------------------*/
	transform.resize(bonesCount);
	Framlocalworldmatrix.resize(bonesCount);

	for (UINT index = 0; index < bonesCount; index++)
	{
		XMStoreFloat4x4(&transform[index], bonesMatrix[index].finalMatrix);
		if (index == 38 || index == 12)
			XMStoreFloat4x4(&Framlocalworldmatrix[index], bonesMatrix[index].localWorldMatrix);
	}
}

void CSkinnedfbxanim::Render(XMMATRIX worldMatrix, UINT animation)
{

	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
		this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	BoneTransform(currentBonesTransform);
	CRenderer::SetBones(currentBonesTransform);
	CRenderer::SetWorldMatrix(&worldMatrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		//CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
	CRenderer::BoneBack();
}

void CSkinnedfbxanim::Render(XMMATRIX worldMatrix, XMMATRIX & outworldMatrix, int num,UINT animation)
{
	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
		this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	BoneTransform(currentBonesTransform);
   XMMATRIX asd;
   XMFLOAT4X4 sss = currentBonesTransform[num];
   outworldMatrix = XMLoadFloat4x4(&sss);
	CRenderer::SetBones(currentBonesTransform);
	CRenderer::SetWorldMatrix(&worldMatrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		//CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
	CRenderer::BoneBack();
}

void CSkinnedfbxanim::Render(XMMATRIX worldMatrix, XMMATRIX worldMatrix2, UINT animation)
{
	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
		this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	BoneTransform(currentBonesTransform);
	CRenderer::SetBones(currentBonesTransform);
	//CRenderer::SetWorldMatrix(&worldMatrix);
	//CRenderer::SetWorldMatrix(&worldMatrix2);
	for (int index = 0; index < meshes.size(); index++)
	{
		if(index<meshes.size()-2) CRenderer::SetWorldMatrix(&worldMatrix);
		else CRenderer::SetWorldMatrix(&worldMatrix2);
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		//CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
	CRenderer::BoneBack();
}

void CSkinnedfbxanim::RenderGotimer(XMMATRIX worldMatrix, UINT animation)
{
	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
		//this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	BoneTransform(currentBonesTransform);
	CRenderer::SetBones(currentBonesTransform);
	CRenderer::SetWorldMatrix(&worldMatrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		//CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
	CRenderer::BoneBack();
}

void CSkinnedfbxanim::RenderInstance(XMFLOAT4X4 world[], UINT animation)
{
	CRenderer::SetInstanceWorld(world);
	CRenderer::InstanceBegin();
	//Animation Blend
	if (currentAnimation != animation)
	{
		this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	BoneTransform(currentBonesTransform);//dange
	CRenderer::SetBones(currentBonesTransform);
	CRenderer::GetDeviceContext()->UpdateSubresource(CRenderer::GetBufferofInstance(), 0, NULL, &Insanim, 0, 0);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST_INSTANCE(meshes[index]->indices.size(), INSTANCEMAX);
	}
	CRenderer::InstanceEnd();
}

void CSkinnedfbxanim::ProcessNode(aiNode* node)
{
	for (UINT index = 0; index < node->mNumMeshes; index++)
	{
		aiMesh* mesh = ai_Scenes[0]->mMeshes[node->mMeshes[index]];
		meshes.push_back(this->ProcessMesh(mesh));
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		this->ProcessNode(node->mChildren[index]);
	}
}

SkinnedMesh* CSkinnedfbxanim::ProcessMesh(aiMesh* mesh)
{
	SkinnedMesh* skinnedMesh = new SkinnedMesh;

	//Getting Vertex
	for (UINT index = 0; index < mesh->mNumVertices; index++)
	{
		BonesVertex v;
		//Position
		v.Position = XMFLOAT3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
		//Normal
		if (mesh->mNormals != nullptr)
			v.Normal = XMFLOAT3(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
		//Texture Coord
		if (mesh->mTextureCoords[0])
			v.TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][index].x, (float)mesh->mTextureCoords[0][index].y);

		skinnedMesh->vertices.push_back(v);
		//jingzhi
	/*	VERTEX_3D Vertex;
		Vertex.Position = XMFLOAT3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
		if (mesh->mNormals != nullptr)
			Vertex.Normal = XMFLOAT3(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
		Vertex.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		if (mesh->mTextureCoords[0])
			Vertex.TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][index].x, (float)mesh->mTextureCoords[0][index].y);
		skinnedMesh->vs.push_back(Vertex);*/
	}

	//Getting Index
	for (UINT index = 0; index < mesh->mNumFaces; index++)
	{
		aiFace ai_Face = mesh->mFaces[index];

		for (UINT count = 0; count < ai_Face.mNumIndices; count++)
		{
			skinnedMesh->indices.push_back(ai_Face.mIndices[count]);
		}
	}


	//aimaterial
	aiMaterial* material = ai_Scenes[0]->mMaterials[mesh->mMaterialIndex];//ﾒｻｸｻﾓﾐﾒｻｸｸﾏﾄﾖﾊｵﾄﾋ｣ｻ/阿瑟东
	skinnedMesh->material = this->MaterialTexture(ai_Scenes[0], material);
	//Getting Material
	//aiMaterial* ai_Material = ai_Scene->mMaterials[mesh->mMaterialIndex];
	//skinnedMesh->textures = this->ProcessMaterialTextures(ai_Material);

	//Getting Bones Data
	for (UINT index = 0; index < mesh->mNumBones; index++)
	{
		UINT bone = 0;
		std::string boneName(mesh->mBones[index]->mName.data);

		if (bonesMap.find(boneName) == bonesMap.end())
		{
			bone = bonesCount;
			bonesCount++;
			BoneMatrix temp;
			bonesMatrix.push_back(temp);

			bonesMatrix[bone].offsetMatrix = XMMATRIX(&mesh->mBones[index]->mOffsetMatrix.a1);

			bonesMap[boneName] = bone;
		}
		else
		{
			bone = bonesMap[boneName];
		}

		for (UINT w = 0; w < mesh->mBones[index]->mNumWeights; w++)
		{
			UINT ID = mesh->mBones[index]->mWeights[w].mVertexId;
			float weight = mesh->mBones[index]->mWeights[w].mWeight;
			skinnedMesh->vertices[ID].AddBoneDatas(bone, weight);
		}
	}
	return skinnedMesh;
}

//std::vector<CTexture> SkinnedModel::ProcessMaterialTextures(aiMaterial* material)
//{
//	std::vector<CTexture> textures;
//
//	UINT diffuseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
//	UINT normalCount = material->GetTextureCount(aiTextureType_HEIGHT);
//	UINT specularCount = material->GetTextureCount(aiTextureType_SPECULAR);
//
//	/*--------------------------------------------------------------------------------
//	Load Diffuse
//	--------------------------------------------------------------------------------*/
//	if (diffuseCount > 0)
//	{
//			aiString path;
//
//			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
//
//			//Get the texture file location
//			size_t pos = modelpath.find_last_of("\\/");
//			std::string basePath = modelpath.substr(0, pos + 1);
//			std::string fileloc = basePath + path.data;
//
//			textures.push_back(CTexture(fileloc));
//	}
//
//	/*--------------------------------------------------------------------------------
//	Load Normal
//	--------------------------------------------------------------------------------*/
//	//Restrict
//	normalCount = 1;
//	if (normalCount)
//	{
//		for (UINT index = 0; index < normalCount; index++)
//		{
//			aiString path;
//
//			material->GetTexture(aiTextureType_HEIGHT, index, &path);
//
//			//Get the texture file location
//			size_t pos = modelpath.find_last_of("\\/");
//			std::string basePath = modelpath.substr(0, pos + 1);
//			std::string fileloc = basePath + path.data;
//
//			if(meshes.size() == 0)
//				textures.push_back(Texture("./Asset/Soldier/soldier_soldier2_mat_nmap.png"));
//			if (meshes.size() == 1)
//				textures.push_back(Texture("./Asset/Soldier/soldier_weapon_mat_nmap.png"));
//		}
//	}
//
//	/*
//	if (normalCount)
//	{
//		for (UINT index = 0; index < normalCount; index++)
//		{
//			aiString path;
//
//			material->GetTexture(aiTextureType_HEIGHT, index, &path);
//
//			//Get the texture file location
//			size_t pos = modelpath.find_last_of("\\/");
//			std::string basePath = modelpath.substr(0, pos + 1);
//			std::string fileloc = basePath + path.data;
//
//			textures.push_back(Texture(fileloc));
//		}
//	}
//	*/
//	/*--------------------------------------------------------------------------------
//	Load Specular
//	--------------------------------------------------------------------------------*/
//	if (specularCount)
//	{
//		for (UINT index = 0; index < specularCount; index++)
//		{
//			aiString path;
//
//			material->GetTexture(aiTextureType_SPECULAR, index, &path);
//
//			//Get the texture file location
//			size_t pos = modelpath.find_last_of("\\/");
//			std::string basePath = modelpath.substr(0, pos + 1);
//			std::string fileloc = basePath + path.data;
//
//			textures.push_back(Texture(fileloc));
//		}
//	}
//	return textures;
//}

void CSkinnedfbxanim::BoneTransform(std::vector<XMFLOAT4X4>& transform)
{
	//XMMATRIX parentMatrix = XMMatrixRotationX(XMConvertToRadians(-90));
	//parentMatrix *= XMMatrixRotationY(XMConvertToRadians(135));
	XMMATRIX parentMatrix = XMMatrixIdentity();

	//Animation Blend
	const aiAnimation* Aanimation=NULL;
	const aiAnimation* Aanimation1= NULL;
	if (blendTime > 0.0f)
	{
		
		int animationtimer;
			Aanimation = ai_Scenes[currentAnimation]->mAnimations[0];
			animationtimer = Aanimation->mDuration;

		float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
			Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		float animationTime1 = fmod(timeInTicks, animationtimer);//アニメーション時間


		int animationtimers;
			Aanimation1 = ai_Scenes[nextAnimation]->mAnimations[0];
			animationtimers = Aanimation1->mDuration;

		ticksPerSecond = Aanimation1->mTicksPerSecond != 0 ?
			Aanimation1->mTicksPerSecond : ticksPerSecond = 25.0f;
		timeInTicks = animTime2 * ticksPerSecond;
		float animationTime2 = fmod(timeInTicks, animationtimers);

		ReadNodeHeirarchy(ai_Scenes[0]->mRootNode, ai_Scenes[0]->mRootNode, parentMatrix, animationTime1, animationTime2, currentAnimation, nextAnimation, Aanimation, Aanimation1);
	}
	else
	{
	
		//
		int animationtimer;
			Aanimation = ai_Scenes[currentAnimation]->mAnimations[0];
			animationtimer = Aanimation->mDuration;
		
		float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
			Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;

		float animationTime = fmod(timeInTicks, animationtimer);
		float animFramManagertimer = fmod(timeInTicks, animationtimer+10.0f);
		NextAimCurrentFrama = animFramManagertimer;
		NextAimCurrentFrama2 = animationTime;
		ReadNodeHeirarchy(ai_Scenes[0]->mRootNode, parentMatrix, animationTime, currentAnimation,Aanimation);
		//if(animationTime)
	}

	/*--------------------------------------------------------------------------------
	Send All Bones Data
	--------------------------------------------------------------------------------*/
	transform.resize(bonesCount);

	for (UINT index = 0; index < bonesCount; index++)
	{
		XMStoreFloat4x4(&transform[index], bonesMatrix[index].finalMatrix);
	}
}

void CSkinnedfbxanim::InstanceBoneUpdate()
{
	XMMATRIX parentMatrix = XMMatrixIdentity();
	for (UINT i = 0; i < INSTANCEMAX; i++)
	{

		//Animation Blend
		const aiAnimation* Aanimation = NULL;
		const aiAnimation* Aanimation1 = NULL;
		if (Insblend[i] > 0.0f)
		{

			int animationtimer;
			Aanimation = ai_Scenes[InscurrentAnimation[i]]->mAnimations[0];
			animationtimer = Aanimation->mDuration;

			float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
				Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
			float timeInTicks = animTime1 * ticksPerSecond;
			float animationTime1 = fmod(timeInTicks, animationtimer);//アニメーション時間


			int animationtimers;
			Aanimation1 = ai_Scenes[InsnextAnimation[i]]->mAnimations[0];
			animationtimers = Aanimation1->mDuration;

			ticksPerSecond = Aanimation1->mTicksPerSecond != 0 ?
				Aanimation1->mTicksPerSecond : ticksPerSecond = 25.0f;
			timeInTicks = animTime2 * ticksPerSecond;
			float animationTime2 = fmod(timeInTicks, animationtimers);

			ReadNodeHeirarchy(ai_Scenes[0]->mRootNode, ai_Scenes[0]->mRootNode, parentMatrix, animationTime1, animationTime2, currentAnimation, nextAnimation, Aanimation, Aanimation1);
		}
		else
		{

			//
			int animationtimer;
			Aanimation = ai_Scenes[InscurrentAnimation[i]]->mAnimations[0];
			animationtimer = Aanimation->mDuration;

			float ticksPerSecond = Aanimation->mTicksPerSecond != 0 ?
				Aanimation->mTicksPerSecond : ticksPerSecond = 25.0f;
			float timeInTicks = animTime1 * ticksPerSecond;

			float animationTime = fmod(timeInTicks, animationtimer);
			float animFramManagertimer = fmod(timeInTicks, animationtimer + 10.0f);
			NextAimCurrentFrama = animationTime;

			ReadNodeHeirarchy(ai_Scenes[0]->mRootNode, parentMatrix, animationTime, currentAnimation, Aanimation);
			//if(animationTime)
		}

		/*--------------------------------------------------------------------------------
		Send All Bones Data
		--------------------------------------------------------------------------------*/
		//transform.resize(bonesCount);

		for (UINT index = 0; index < bonesCount; index++)
			XMStoreFloat4x4(&Insanim[i].BoneMarix[index], bonesMatrix[index].finalMatrix);
	}
}

void CSkinnedfbxanim::ReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action, const aiAnimation* animation)
{
	std::string nodeName(node->mName.data);
	XMMATRIX nodeTransform = XMMATRIX(&node->mTransformation.a1);

	//const aiAnimation* animation = ai_Scene->mAnimations[action];

	const aiNodeAnim* nodeAnimation = FindNodeAnim(animation, nodeName);

	//Calculate interpolate value
	if (nodeAnimation)
	{
		aiVector3D t = interpolatePosition(time, nodeAnimation);
		XMMATRIX TranslationM = XMMatrixTranslation(t.x, t.y, t.z);

		aiQuaternion q = interpolateRotation(time, nodeAnimation);
		XMMATRIX RotationM = XMMatrixRotationQuaternion(XMVectorSet(q.x, q.y, q.z, q.w));

		aiVector3D s = interpolateScaling(time, nodeAnimation);
		XMMATRIX ScalingM = XMMatrixScaling(s.x, s.y, s.z);

		nodeTransform = ScalingM * RotationM * TranslationM;
		nodeTransform = XMMatrixTranspose(nodeTransform);
	}

	XMMATRIX globalTransform = XMMatrixMultiply(parentTransform, nodeTransform);

	if (bonesMap.find(nodeName) != bonesMap.end())
	{
		UINT bone = bonesMap[nodeName];
		bonesMatrix[bone].finalMatrix = XMLoadFloat4x4(&GlobalInversef) * globalTransform * bonesMatrix[bone].offsetMatrix;
		//bonesMatrix[bone].localWorldMatrix = globalTransform;
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		ReadNodeHeirarchy(node->mChildren[index], globalTransform, time, action, animation);
	}
}

void CSkinnedfbxanim::ReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2, const aiAnimation* animation, const aiAnimation* animation1s)
{
	std::string nodeName1(node1->mName.data);
	std::string nodeName2(node2->mName.data);

	XMMATRIX nodeTransform1 = XMMATRIX(&node1->mTransformation.a1);
	XMMATRIX nodeTransform2 = XMMATRIX(&node2->mTransformation.a1);

	//const aiAnimation* animation1 = animation;
	//const aiAnimation* animation2 = animation1s;

	const aiNodeAnim* nodeAnimation1 = FindNodeAnim(animation, nodeName1);
	const aiNodeAnim* nodeAnimation2 = FindNodeAnim(animation1s, nodeName2);

	//Calculate interpolate value
	if (nodeAnimation1 && nodeAnimation2)
	{
		aiVector3D t1 = interpolatePosition(time1, nodeAnimation1);
		aiVector3D t2 = interpolatePosition(time2, nodeAnimation2);
		aiVector3D deltaT = t2 - t1;
		aiVector3D t = t1 + blendTime * deltaT;
		XMMATRIX TranslationM = XMMatrixTranslation(t.x, t.y, t.z);

		aiQuaternion q1 = interpolateRotation(time1, nodeAnimation1);
		aiQuaternion q2 = interpolateRotation(time2, nodeAnimation2);
		aiQuaternion r;
		aiQuaternion::Interpolate(r, q1, q2, blendTime);
		r = r.Normalize();
		XMMATRIX RotationM = XMMatrixRotationQuaternion(XMVectorSet(r.x, r.y, r.z, r.w));

		aiVector3D s1 = interpolateScaling(time1, nodeAnimation1);
		aiVector3D s2 = interpolateScaling(time2, nodeAnimation2);
		aiVector3D deltaS = s2 - s1;
		aiVector3D s = s1 + blendTime * deltaS;
		XMMATRIX ScalingM = XMMatrixScaling(s.x, s.y, s.z);

		nodeTransform1 = ScalingM * RotationM * TranslationM;
		nodeTransform1 = XMMatrixTranspose(nodeTransform1);
	}

	XMMATRIX globalTransform = XMMatrixMultiply(parentTransform, nodeTransform1);

	if (bonesMap.find(nodeName1) != bonesMap.end())
	{
		UINT bone = bonesMap[nodeName1];
		bonesMatrix[bone].finalMatrix = XMLoadFloat4x4(&GlobalInversef) * globalTransform * bonesMatrix[bone].offsetMatrix;
	}


	UINT c;
	if (node1->mNumChildren < node2->mNumChildren)
		c = node1->mNumChildren;
	else
		c = node2->mNumChildren;

	for (UINT index = 0; index < c; index++)
	{
		ReadNodeHeirarchy(node1->mChildren[index], node2->mChildren[index], globalTransform, time1, time2, action1, action2, animation, animation1s);
	}

}

const aiNodeAnim* CSkinnedfbxanim::FindNodeAnim(const aiAnimation* animation, const std::string nodeName)
{
	for (UINT index = 0; index < animation->mNumChannels; index++)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[index];
		if (std::string(nodeAnim->mNodeName.data) == nodeName)
			return nodeAnim;
	}
	return nullptr;
}

aiVector3D CSkinnedfbxanim::interpolatePosition(float time, const aiNodeAnim* anim)
{
	if (anim->mNumPositionKeys == 1)
	{
		return anim->mPositionKeys[0].mValue;
	}

	//Find Current Position
	UINT currentPosition = findPosition(time, anim);
	UINT nextPosition = currentPosition + 1;

	float deltaTime = (float)(anim->mPositionKeys[nextPosition].mTime - anim->mPositionKeys[currentPosition].mTime);
	float factor = (time - (float)anim->mPositionKeys[currentPosition].mTime) / deltaTime;

	aiVector3D start = anim->mPositionKeys[currentPosition].mValue;
	aiVector3D end = anim->mPositionKeys[nextPosition].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion CSkinnedfbxanim::interpolateRotation(float time, const aiNodeAnim* anim)
{
	if (anim->mNumRotationKeys == 1)
	{
		return anim->mRotationKeys[0].mValue;
	}

	//Find Current Rotation
	UINT currentRotation = findRotation(time, anim);
	UINT nextRotation = currentRotation + 1;

	float deltaTime = (float)(anim->mRotationKeys[nextRotation].mTime - anim->mRotationKeys[currentRotation].mTime);
	float factor = (time - (float)anim->mRotationKeys[currentRotation].mTime) / deltaTime;

	aiQuaternion start = anim->mRotationKeys[currentRotation].mValue;
	aiQuaternion end = anim->mRotationKeys[nextRotation].mValue;

	aiQuaternion out;
	aiQuaternion::Interpolate(out, start, end, factor);
	out = out.Normalize();

	return out;
}

aiVector3D CSkinnedfbxanim::interpolateScaling(float time, const aiNodeAnim* anim)
{
	if (anim->mNumScalingKeys == 1)
	{
		return anim->mScalingKeys[0].mValue;
	}

	//Find Current Scaling
	UINT currentScale = findScaling(time, anim);
	UINT nextScale = currentScale + 1;

	float deltaTime = (float)(anim->mScalingKeys[nextScale].mTime - anim->mScalingKeys[currentScale].mTime);
	float factor = (time - (float)anim->mScalingKeys[currentScale].mTime) / deltaTime;

	aiVector3D start = anim->mScalingKeys[currentScale].mValue;
	aiVector3D end = anim->mScalingKeys[nextScale].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

UINT CSkinnedfbxanim::findPosition(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumPositionKeys - 1; index++)
	{
		if (time < (float)anim->mPositionKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT CSkinnedfbxanim::findRotation(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumRotationKeys - 1; index++)
	{
		if (time < (float)anim->mRotationKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT CSkinnedfbxanim::findScaling(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumScalingKeys - 1; index++)
	{
		if (time < (float)anim->mScalingKeys[index + 1].mTime)
			return index;
	}
	return 0;
}
void CSkinnedfbxanim::WeaponRender(XMMATRIX worldMatrix, UINT animation)
{
	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
		this->ResetTimer();
		nextAnimation = currentAnimation;
		currentAnimation = animation;

		blendTime = 1.0f;
	}

	WeaponBoneTransform(currentBonesTransform);
	CRenderer::SetBones(currentBonesTransform);
	CRenderer::SetWorldMatrix(&worldMatrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<BonesVertex>::SetVertexBuffer(meshes[index]->vertexBuffer);
		//CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
	CRenderer::BoneBack();
}
void CSkinnedfbxanim::WeaponReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action, const aiAnimation* animation)
{
	std::string nodeName(node->mName.data);
	XMMATRIX nodeTransform = XMMATRIX(&node->mTransformation.a1);

	//const aiAnimation* animation = ai_Scene->mAnimations[action];

	const aiNodeAnim* nodeAnimation = FindNodeAnim(animation, nodeName);

	//Calculate interpolate value
	if (nodeAnimation)
	{
		aiVector3D t = interpolatePosition(time, nodeAnimation);
		XMMATRIX TranslationM = XMMatrixTranslation(t.x, t.y, t.z);

		aiQuaternion q = interpolateRotation(time, nodeAnimation);
		XMMATRIX RotationM = XMMatrixRotationQuaternion(XMVectorSet(q.x, q.y, q.z, q.w));

		aiVector3D s = interpolateScaling(time, nodeAnimation);
		XMMATRIX ScalingM = XMMatrixScaling(s.x, s.y, s.z);

		nodeTransform = ScalingM * RotationM * TranslationM;
		nodeTransform = XMMatrixTranspose(nodeTransform);
	}

	XMMATRIX globalTransform = XMMatrixMultiply(parentTransform, nodeTransform);

	if (bonesMap.find(nodeName) != bonesMap.end())
	{
		UINT bone = bonesMap[nodeName];
		bonesMatrix[bone].finalMatrix = XMLoadFloat4x4(&GlobalInversef) * globalTransform * bonesMatrix[bone].offsetMatrix;
		//bonesMatrix[bone].localWorldMatrix = globalTransform;
		switch (bone)
		{
		case 38:
		{
			XMMATRIX weaPonBoneMatrix = XMLoadFloat4x4(&WeaPonMatrix);
			XMMATRIX globalTransformx = XMMatrixMultiply(parentTransform, weaPonBoneMatrix);
			bonesMatrix[bone].localWorldMatrix = globalTransformx;
		}
		break;
		case 12:
		{
			XMMATRIX weaPonBoneMatrix = XMLoadFloat4x4(&WeaPonMatrix);
			XMMATRIX globalTransformx = XMMatrixMultiply(parentTransform, weaPonBoneMatrix);
			bonesMatrix[bone].localWorldMatrix = globalTransformx;
		}
		break;
		}
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		WeaponReadNodeHeirarchy(node->mChildren[index], globalTransform, time, action, animation);
	}
}
void CSkinnedfbxanim::WeaponReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2, const aiAnimation* animation, const aiAnimation* animation1s)
{
	std::string nodeName1(node1->mName.data);
	std::string nodeName2(node2->mName.data);

	XMMATRIX nodeTransform1 = XMMATRIX(&node1->mTransformation.a1);
	XMMATRIX nodeTransform2 = XMMATRIX(&node2->mTransformation.a1);

	//const aiAnimation* animation1 = animation;
	//const aiAnimation* animation2 = animation1s;

	const aiNodeAnim* nodeAnimation1 = FindNodeAnim(animation, nodeName1);
	const aiNodeAnim* nodeAnimation2 = FindNodeAnim(animation1s, nodeName2);

	//Calculate interpolate value
	if (nodeAnimation1 && nodeAnimation2)
	{
		aiVector3D t1 = interpolatePosition(time1, nodeAnimation1);
		aiVector3D t2 = interpolatePosition(time2, nodeAnimation2);
		aiVector3D deltaT = t2 - t1;
		aiVector3D t = t1 + blendTime * deltaT;
		XMMATRIX TranslationM = XMMatrixTranslation(t.x, t.y, t.z);

		aiQuaternion q1 = interpolateRotation(time1, nodeAnimation1);
		aiQuaternion q2 = interpolateRotation(time2, nodeAnimation2);
		aiQuaternion r;
		aiQuaternion::Interpolate(r, q1, q2, blendTime);
		r = r.Normalize();
		XMMATRIX RotationM = XMMatrixRotationQuaternion(XMVectorSet(r.x, r.y, r.z, r.w));

		aiVector3D s1 = interpolateScaling(time1, nodeAnimation1);
		aiVector3D s2 = interpolateScaling(time2, nodeAnimation2);
		aiVector3D deltaS = s2 - s1;
		aiVector3D s = s1 + blendTime * deltaS;
		XMMATRIX ScalingM = XMMatrixScaling(s.x, s.y, s.z);

		nodeTransform1 = ScalingM * RotationM * TranslationM;
		nodeTransform1 = XMMatrixTranspose(nodeTransform1);
	}

	XMMATRIX globalTransform = XMMatrixMultiply(parentTransform, nodeTransform1);

	if (bonesMap.find(nodeName1) != bonesMap.end())
	{
		UINT bone = bonesMap[nodeName1];
		bonesMatrix[bone].finalMatrix = XMLoadFloat4x4(&GlobalInversef) * globalTransform * bonesMatrix[bone].offsetMatrix;
		switch (bone)
		{
		case 38:
		{
			XMMATRIX weaPonBoneMatrix = XMLoadFloat4x4(&WeaPonMatrix);
			XMMATRIX globalTransformx = XMMatrixMultiply(parentTransform, weaPonBoneMatrix);
			bonesMatrix[bone].localWorldMatrix = globalTransformx;
		}
		break;
		case 12:
		{
			XMMATRIX weaPonBoneMatrix = XMLoadFloat4x4(&WeaPonMatrix);
			XMMATRIX globalTransformx = XMMatrixMultiply(parentTransform, weaPonBoneMatrix);
			bonesMatrix[bone].localWorldMatrix = globalTransformx;
		}
		break;
		}
	}


	UINT c;
	if (node1->mNumChildren < node2->mNumChildren)
		c = node1->mNumChildren;
	else
		c = node2->mNumChildren;

	for (UINT index = 0; index < c; index++)
	{
		WeaponReadNodeHeirarchy(node1->mChildren[index], node2->mChildren[index], globalTransform, time1, time2, action1, action2, animation, animation1s);
	}
}
