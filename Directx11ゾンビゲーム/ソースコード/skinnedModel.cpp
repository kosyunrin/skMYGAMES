#include "main.h"
#include "skinnedModel.h"

SkinnedModel::SkinnedModel(std::string modelpath)
{
	bonesCount = 0;
	currentAnimation = 0;//
	nextAnimation = 0;

	animTime1 = 0.0f;
	animTime2 = 0.0f;
	blendTime = 0.0f;

	this->Load(modelpath);
}

SkinnedModel::~SkinnedModel()
{
	meshes.clear();
	importer.FreeScene();
}

void SkinnedModel::Load(std::string path)
{
	//modelpath = path;

	ai_Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if (ai_Scene == nullptr)
	{
		//Engine::ErrorMsg("aiScene Create Failed");
		MessageBox(0, "Modelload  - Failed",
			"Error", MB_OK);
		return;
	}

	//GlobalInverse Matrix
	XMVECTOR determinant;
	XMMATRIX GlobalInversex= XMMATRIX(&ai_Scene->mRootNode->mTransformation.a1);
	GlobalInversex= XMMatrixInverse(&determinant, GlobalInversex);
	XMStoreFloat4x4(&GlobalInversef, GlobalInversex);

	//GlobalInverse = XMMATRIX(&ai_Scene->mRootNode->mTransformation.a1);
	//GlobalInverse = XMMatrixInverse(&determinant, GlobalInverse);

	this->ProcessNode(ai_Scene->mRootNode);
	//setboxV
	MeshPart* meshpart = new MeshPart[meshes.size()];
	for (int index = 0; index < meshes.size(); index++)
	{
		meshes[index]->vertexBuffer = CVertexBuffer<BonesVertex>::CreatVertexBuffer(meshes[index]->vertices.data(), meshes[index]->vertices.size());
		//meshes[index]->vertexBuffer = CVertexBuffer<VERTEX_3D>::CreatVertexBuffer(meshes[index]->vs.data(), meshes[index]->vs.size());
		meshes[index]->indexBuffer = CIndexBuffer<DWORD>::CreatIndexBuffer(NULL,meshes[index]->indices.data(), meshes[index]->indices.size());

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

void SkinnedModel::Update()
{
	animTime1 += 0.02f;
	animTime2 += 0.02f;

	if(blendTime >= 0.0f)
		blendTime -= 0.1f;
}

void SkinnedModel::ResetTimer()
{
	animTime1 = 0.0f;
	animTime2 = 0.0f;
}

std::vector<MeshPart> SkinnedModel::m_GetBoxPinots()
{
	return V_m_meshPart;
}

std::vector<Material> SkinnedModel::MaterialTexture(const aiScene * scene, aiMaterial * material)
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
			modelpath = path.data;
			size_t Pos = modelpath.find_last_of("\\/");
			std::string texName = modelpath.substr(Pos + 1, modelpath.size() - Pos);
			GetMaterial.push_back(Material(texName));
		}
		return GetMaterial;
	}
}

void SkinnedModel::Render(XMMATRIX worldMatrix, UINT animation)
{

	CRenderer::BoneSL();
	//Animation Blend
	if (currentAnimation != animation)
	{
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

void SkinnedModel::ProcessNode(aiNode* node)
{
	for (UINT index = 0; index < node->mNumMeshes; index++)
	{
		aiMesh* mesh = ai_Scene->mMeshes[node->mMeshes[index]];
		meshes.push_back(this->ProcessMesh(mesh));
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		this->ProcessNode(node->mChildren[index]);
	}
}

SkinnedMesh* SkinnedModel::ProcessMesh(aiMesh* mesh)
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
	aiMaterial* material = ai_Scene->mMaterials[mesh->mMaterialIndex];//ﾒｻｸｻﾓﾐﾒｻｸｸﾏﾄﾖﾊｵﾄﾋ｣ｻ/阿瑟东
	skinnedMesh->material = this->MaterialTexture(ai_Scene, material);
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

void SkinnedModel::BoneTransform(std::vector<XMFLOAT4X4>& transform)
{
	XMMATRIX parentMatrix = XMMatrixRotationX(XMConvertToRadians(-90.0f));
	//parentMatrix *= XMMatrixRotationY(XMConvertToRadians(0.0f));
	//XMMATRIX parentMatrix = XMMatrixIdentity();

	//Animation Blend
	if (blendTime > 0.0f)
	{
		int animationtimer;
		if (currentAnimation == 11)
			animationtimer = 140;
		else if (currentAnimation == 21)
			animationtimer = 64;

		float ticksPerSecond = ai_Scene->mAnimations[currentAnimation]->mTicksPerSecond != 0 ?
			ai_Scene->mAnimations[currentAnimation]->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		float animationTime1 = fmod(timeInTicks, animationtimer);//アニメーション時間


		int animationtimers;
		if (nextAnimation == 11)
			animationtimers = 140;
		else if (nextAnimation == 21)
			animationtimers = 64;


		ticksPerSecond = ai_Scene->mAnimations[nextAnimation]->mTicksPerSecond != 0 ?
			ai_Scene->mAnimations[nextAnimation]->mTicksPerSecond : ticksPerSecond = 25.0f;
		timeInTicks = animTime2 * ticksPerSecond;
		float animationTime2 = fmod(timeInTicks, animationtimer);

		ReadNodeHeirarchy(ai_Scene->mRootNode, ai_Scene->mRootNode, parentMatrix, animationTime1, animationTime2, currentAnimation, nextAnimation);
	}
	else
	{
		float ticksPerSecond = ai_Scene->mAnimations[currentAnimation]->mTicksPerSecond != 0 ?
			ai_Scene->mAnimations[currentAnimation]->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		//
		int animationtimer;
		if (currentAnimation == 11)
			animationtimer = 140;
		else if (currentAnimation == 21)
			animationtimer = 64;
		else if (currentAnimation == 0)
			animationtimer = ai_Scene->mAnimations[currentAnimation]->mDuration;
		float animationTime = fmod(timeInTicks, animationtimer);

		ReadNodeHeirarchy(ai_Scene->mRootNode, parentMatrix, animationTime, currentAnimation);
	}

	/*--------------------------------------------------------------------------------
	Send All Bones Data
	--------------------------------------------------------------------------------*/
	transform.resize(bonesCount);

	for (UINT index = 0; index < bonesCount; index++)
		XMStoreFloat4x4(&transform[index], bonesMatrix[index].finalMatrix);
}

void SkinnedModel::ReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action)
{
	std::string nodeName(node->mName.data);
	XMMATRIX nodeTransform = XMMATRIX(&node->mTransformation.a1);

	const aiAnimation* animation = ai_Scene->mAnimations[action];

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
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		ReadNodeHeirarchy(node->mChildren[index], globalTransform, time, action);
	}
}

void SkinnedModel::ReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2)
{
	std::string nodeName1(node1->mName.data);
	std::string nodeName2(node2->mName.data);

	XMMATRIX nodeTransform1 = XMMATRIX(&node1->mTransformation.a1);
	XMMATRIX nodeTransform2 = XMMATRIX(&node2->mTransformation.a1);

	const aiAnimation* animation1 = ai_Scene->mAnimations[action1];
	const aiAnimation* animation2 = ai_Scene->mAnimations[action2];

	const aiNodeAnim* nodeAnimation1 = FindNodeAnim(animation1, nodeName1);
	const aiNodeAnim* nodeAnimation2 = FindNodeAnim(animation2, nodeName2);

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
		ReadNodeHeirarchy(node1->mChildren[index], node2->mChildren[index], globalTransform, time1, time2, action1, action2);
	}

}

const aiNodeAnim* SkinnedModel::FindNodeAnim(const aiAnimation* animation, const std::string nodeName)
{
	for (UINT index = 0; index < animation->mNumChannels; index++)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[index];
		if (std::string(nodeAnim->mNodeName.data) == nodeName)
			return nodeAnim;
	}
	return nullptr;
}

aiVector3D SkinnedModel::interpolatePosition(float time, const aiNodeAnim* anim)
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

aiQuaternion SkinnedModel::interpolateRotation(float time, const aiNodeAnim* anim)
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

aiVector3D SkinnedModel::interpolateScaling(float time, const aiNodeAnim* anim)
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

UINT SkinnedModel::findPosition(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumPositionKeys - 1; index++)
	{
		if (time < (float)anim->mPositionKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT SkinnedModel::findRotation(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumRotationKeys - 1; index++)
	{
		if (time < (float)anim->mRotationKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT SkinnedModel::findScaling(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumScalingKeys - 1; index++)
	{
		if (time < (float)anim->mScalingKeys[index + 1].mTime)
			return index;
	}
	return 0;
}