#include "engine.h"
#include "multiSkinnedModel.h"

MultiSkinnedModel::MultiSkinnedModel(std::string* modelpath, UINT count)
{
	this->bonesCount = 0;
	this->currentAnimation = 1;
	this->lastAnimation = 1;

	this->animTime1 = 0.0f;
	this->animTime2 = 0.0f;
	this->blendTime = 0.0f;

	this->Load(modelpath, count);
}

MultiSkinnedModel::~MultiSkinnedModel()
{
	meshes.clear();
	myCollisions.clear();

	for(int index = 0; index < ANIMATIONMAX; index++)
		importer[index].FreeScene();
}

void MultiSkinnedModel::Load(std::string* path, UINT animCount)
{
	modelpath = path[0];

	for(int index = 0; index < animCount; index++)
	{ 
		scene[index] = importer[index].ReadFile(path[index], aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder);

		if (scene[index] == nullptr)
		{
			Engine::ErrorMsg("aiScene Create Failed" + path[index]);
			return;
		}
	}

	//GlobalInverse Matrix
	XMVECTOR determinant;
	GlobalInverse = XMMATRIX(&scene[0]->mRootNode->mTransformation.a1);
	GlobalInverse = XMMatrixInverse(&determinant, GlobalInverse);

	this->ProcessNode(scene[0]->mRootNode, XMMatrixIdentity());

	/*--------------------------------------------------------------------------------
	Create buffer
	--------------------------------------------------------------------------------*/
	for (int index = 0; index < meshes.size(); index++)
	{
		VertexBuffer<BonesVertex>::CreateVertexBuffer(meshes[index].vertexBuffer, meshes[index].vertices.data(), (UINT)meshes[index].vertices.size());
		IndexBuffer::CreateIndexBuffer(meshes[index].indexBuffer, meshes[index].indices.data(), (UINT)meshes[index].indices.size());
	}

	/*--------------------------------------------------------------------------------
	Create collision
	--------------------------------------------------------------------------------*/
	BoneTransform(scene[currentAnimation], scene[lastAnimation], bonesTransform);

	for (int index = 0; index < meshes.size(); index++)
	{
		SkinnedMesh m = meshes[index];

		std::vector<XMFLOAT3> collisionVertices;
		for (int v = 0; v < m.vertices.size(); v++)
		{
			BonesVertex vertex = m.vertices[v];

			XMMATRIX transform0 = XMMatrixTranspose(XMLoadFloat4x4(&bonesTransform[vertex.boneID[0]]));
			XMMATRIX transform1 = XMMatrixTranspose(XMLoadFloat4x4(&bonesTransform[vertex.boneID[1]]));

			XMVECTOR posVec = XMLoadFloat3(&vertex.Position);
			XMVECTOR temp = vertex.boneWeights[0] * XMVector3TransformCoord(posVec, transform0);
			temp += vertex.boneWeights[1] * XMVector3TransformCoord(posVec, transform1);

			XMFLOAT3 pos;
			XMStoreFloat3(&pos, temp);
			collisionVertices.push_back(pos);
		}

		Collision* c = new Collision;
		c->Initialize(collisionVertices, m.indices);
		myCollisions.push_back(c);
	}
}

void MultiSkinnedModel::Update(bool updateCollision)
{
	animTime1 += 0.02f;
	animTime2 += 0.02f;

	if (blendTime >= 0.0f)
		blendTime -= 0.1f;

	/*--------------------------------------------------------------------------------
	Update collision
	--------------------------------------------------------------------------------*/
	this->updateCollision = updateCollision;

	if (updateCollision)
	{
		BoneTransform(scene[currentAnimation], scene[lastAnimation], bonesTransform);

		for (int index = 0; index < meshes.size(); index++)
		{
			SkinnedMesh m = meshes[index];

			std::vector<XMFLOAT3> collisionVertices;
			for (int v = 0; v < m.vertices.size(); v++)
			{
				BonesVertex vertex = m.vertices[v];

				XMMATRIX transform0 = XMMatrixTranspose(XMLoadFloat4x4(&bonesTransform[vertex.boneID[0]]));
				XMMATRIX transform1 = XMMatrixTranspose(XMLoadFloat4x4(&bonesTransform[vertex.boneID[1]]));

				XMVECTOR posVec = XMLoadFloat3(&vertex.Position);
				XMVECTOR temp = vertex.boneWeights[0] * XMVector3TransformCoord(posVec, transform0);
				temp += vertex.boneWeights[1] * XMVector3TransformCoord(posVec, transform1);

				XMFLOAT3 pos;
				XMStoreFloat3(&pos, temp);
				collisionVertices.push_back(pos);
			}

			myCollisions[index]->Update(collisionVertices, m.indices);
		}
	}
}

void MultiSkinnedModel::RestrictTextures(std::string* texPath, UINT texCount, UINT meshID)
{
	std::vector<Texture> tex;

	for (int index = 0; index < texCount; index++)
	{
		//Get the texture file location
		size_t pos = modelpath.find_last_of("\\/");
		std::string basePath = modelpath.substr(0, pos + 1);

		std::string texturepath = texPath[index];
		size_t texPos = texturepath.find_last_of("\\/");
		texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
		std::string fileloc = basePath + texturepath + "png";

		tex.push_back(Texture(fileloc));
	}
	meshes[meshID].textures = tex;
}

void MultiSkinnedModel::ResetTimer()
{
	animTime1 = 0.0f;
	animTime2 = 0.0f;
}

void MultiSkinnedModel::ReduceTimer(float v)
{
	animTime1 -= v;

	if (animTime1 <= 0.0f)
		animTime1 = 100.0f;

	animTime2 -= v;
		
	if (animTime2 <= 0.0f)
		animTime2 = 100.0f;
}

void MultiSkinnedModel::Render(XMMATRIX worldMatrix, UINT ID)
{
	Shader::SetVSShader(VSShaderID::VS_Bones);

	//Animation Blend
	if (currentAnimation != ID)
	{
		lastAnimation = currentAnimation;
		currentAnimation = ID;

		blendTime = 1.0f;
	}
	
	if (!updateCollision)
		BoneTransform(scene[currentAnimation], scene[lastAnimation], bonesTransform);

	ConstantBuffer::SetBones(bonesTransform);

	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index].textures.size(); tex++)
		{
			switch (meshes[index].textures.size())
			{
			case 1:
				Shader::SetPSShader(PSShaderID::PS_Basic);
				meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
				break;
			case 2:
				Shader::SetPSShader(PSShaderID::PS_Normal);
				meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
				meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
				break;
			case 3:
				Shader::SetPSShader(PSShaderID::PS_NormalSpecular);
				meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
				meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
				meshes[index].textures[2].SetTexture(TextureMapID::SpecularMap);
				break;
			}
		}

		VertexBuffer<BonesVertex>::SetVertexBuffers(meshes[index].vertexBuffer.Get());
		IndexBuffer::SetIndexBuffer(meshes[index].indexBuffer.Get());
		ConstantBuffer::SetWorldMatrix(&worldMatrix);
		IndexBuffer::SetTriangleList((UINT)meshes[index].indices.size(), 0, 0);
	}
}

void MultiSkinnedModel::Render(std::vector<Collision*> collisions, XMMATRIX worldMatrix, UINT ID)
{
	Shader::SetVSShader(VSShaderID::VS_Bones);

	//Animation Blend
	if (currentAnimation != ID)
	{
		lastAnimation = currentAnimation;
		currentAnimation = ID;

		blendTime = 1.0f;
	}

	if (!updateCollision)
		BoneTransform(scene[currentAnimation], scene[lastAnimation], bonesTransform);

	ConstantBuffer::SetBones(bonesTransform);

	for (int index = 0; index < meshes.size(); index++)
	{
		if (Camera::GetVisibility(collisions[index]->GetBoundingBox()->GetMinWorld(), collisions[index]->GetBoundingBox()->GetMaxWorld()));
		{
			for (int tex = 0; tex < meshes[index].textures.size(); tex++)
			{
				switch (meshes[index].textures.size())
				{
				case 1:
					Shader::SetPSShader(PSShaderID::PS_Basic);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					break;
				case 2:
					Shader::SetPSShader(PSShaderID::PS_Normal);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					break;
				case 3:
					Shader::SetPSShader(PSShaderID::PS_NormalSpecular);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					meshes[index].textures[2].SetTexture(TextureMapID::SpecularMap);
					break;
				}
			}

			VertexBuffer<BonesVertex>::SetVertexBuffers(meshes[index].vertexBuffer.Get());
			IndexBuffer::SetIndexBuffer(meshes[index].indexBuffer.Get());
			ConstantBuffer::SetWorldMatrix(&worldMatrix);
			IndexBuffer::SetTriangleList((UINT)meshes[index].indices.size(), 0, 0);
		}
	}
}

void MultiSkinnedModel::ProcessNode(aiNode* node, const XMMATRIX parentMatrix)
{
	XMMATRIX nodeMatrix = XMMatrixTranspose(XMMATRIX(&node->mTransformation.a1)) * parentMatrix;

	for (UINT index = 0; index < node->mNumMeshes; index++)
	{
		aiMesh* mesh = scene[0]->mMeshes[node->mMeshes[index]];
		meshes.push_back(this->ProcessMesh(mesh, nodeMatrix));
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		this->ProcessNode(node->mChildren[index], nodeMatrix);
	}
}

SkinnedMesh MultiSkinnedModel::ProcessMesh(aiMesh* mesh, XMMATRIX transformMatrix)
{
	SkinnedMesh m;

	/*--------------------------------------------------------------------------------
	Getting vertex
	--------------------------------------------------------------------------------*/
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
		//Tangent
		if (mesh->mTangents != nullptr)
			v.Tangent = XMFLOAT3(mesh->mTangents[index].x, mesh->mTangents[index].y, mesh->mTangents[index].z);
		//BiTangent
		if (mesh->mBitangents != nullptr)
			v.Bitangent = XMFLOAT3(mesh->mBitangents[index].x, mesh->mBitangents[index].y, mesh->mBitangents[index].z);

		m.vertices.push_back(v);
	}

	/*--------------------------------------------------------------------------------
	Getting index
	--------------------------------------------------------------------------------*/
	for (UINT index = 0; index < mesh->mNumFaces; index++)
	{
		aiFace ai_Face = mesh->mFaces[index];

		for (UINT count = 0; count < ai_Face.mNumIndices; count++)
			m.indices.push_back(ai_Face.mIndices[count]);
	}

	/*--------------------------------------------------------------------------------
	Getting material
	--------------------------------------------------------------------------------*/
	aiMaterial* ai_Material = scene[0]->mMaterials[mesh->mMaterialIndex];
	m.textures = this->ProcessMaterialTextures(ai_Material);

	/*--------------------------------------------------------------------------------
	Getting bones data
	--------------------------------------------------------------------------------*/
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
			m.vertices[ID].insert(bone, weight);
		}
	}
	return m;
}

std::vector<Texture> MultiSkinnedModel::ProcessMaterialTextures(aiMaterial* material)
{
	std::vector<Texture> textures;

	UINT diffuseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	UINT normalCount = material->GetTextureCount(aiTextureType_HEIGHT);
	UINT specularCount = material->GetTextureCount(aiTextureType_SPECULAR);

	/*--------------------------------------------------------------------------------
	Load Diffuse
	--------------------------------------------------------------------------------*/
	if (diffuseCount == 0)
	{
		aiColor3D aiColor;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
		if (aiColor.IsBlack())
			textures.push_back(Texture(Color(50, 50, 50, 255)));
		else
			textures.push_back(Texture(Color((BYTE)aiColor.r * 255, (BYTE)aiColor.g * 255, (BYTE)aiColor.b * 255, 255)));
	}
	else
	{
		for (UINT index = 0; index < diffuseCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_DIFFUSE, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}

	/*--------------------------------------------------------------------------------
	Load Normal
	--------------------------------------------------------------------------------*/
	if (normalCount)
	{
		for (UINT index = 0; index < normalCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_HEIGHT, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}

	/*--------------------------------------------------------------------------------
	Load Specular
	--------------------------------------------------------------------------------*/
	if (specularCount)
	{
		for (UINT index = 0; index < specularCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_SPECULAR, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}
	return textures;
}

void MultiSkinnedModel::BoneTransform(const aiScene* scene1, const aiScene* scene2, std::vector<XMFLOAT4X4>& transform)
{
	XMMATRIX parentMatrix = XMMatrixIdentity();

	//Animation Blend
	if (blendTime > 0.0f)
	{
		float ticksPerSecond = scene1->mAnimations[0]->mTicksPerSecond != 0 ?
			scene1->mAnimations[0]->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		float animationTime1 = fmod(timeInTicks, scene1->mAnimations[0]->mDuration);

		ticksPerSecond = scene2->mAnimations[0]->mTicksPerSecond != 0 ?
			scene2->mAnimations[0]->mTicksPerSecond : ticksPerSecond = 25.0f;
		timeInTicks = animTime2 * ticksPerSecond;
		float animationTime2 = fmod(timeInTicks, scene2->mAnimations[0]->mDuration);
		
		ReadNodeHeirarchy(scene1, scene2, scene1->mRootNode, scene2->mRootNode, parentMatrix, animationTime1, animationTime2);
	}
	else
	{
		float ticksPerSecond = scene1->mAnimations[0]->mTicksPerSecond != 0 ?
			scene1->mAnimations[0]->mTicksPerSecond : ticksPerSecond = 25.0f;
		float timeInTicks = animTime1 * ticksPerSecond;
		float animationTime = fmod(timeInTicks, scene1->mAnimations[0]->mDuration);

		ReadNodeHeirarchy(scene1, scene1->mRootNode, parentMatrix, animationTime);
	}

	/*--------------------------------------------------------------------------------
	Send All Bones Data
	--------------------------------------------------------------------------------*/
	transform.resize(bonesCount);

	for (UINT index = 0; index < bonesCount; index++)
		XMStoreFloat4x4(&transform[index], bonesMatrix[index].finalMatrix);
}

void MultiSkinnedModel::ReadNodeHeirarchy(const aiScene* scene, const aiNode* node, const XMMATRIX parentTransform, float time)
{
	std::string nodeName(node->mName.data);
	XMMATRIX nodeTransform = XMMATRIX(&node->mTransformation.a1);

	const aiAnimation* animation = scene->mAnimations[0];

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
		bonesMatrix[bone].finalMatrix = GlobalInverse * globalTransform * bonesMatrix[bone].offsetMatrix;
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		ReadNodeHeirarchy(scene, node->mChildren[index], globalTransform, time);
	}
}

void MultiSkinnedModel::ReadNodeHeirarchy(const aiScene* scene1, const aiScene* scene2, const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2)
{
	std::string nodeName1(node1->mName.data);
	std::string nodeName2(node2->mName.data);

	XMMATRIX nodeTransform1 = XMMATRIX(&node1->mTransformation.a1);
	XMMATRIX nodeTransform2 = XMMATRIX(&node2->mTransformation.a1);

	const aiAnimation* animation1 = scene1->mAnimations[0];
	const aiAnimation* animation2 = scene2->mAnimations[0];

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
		bonesMatrix[bone].finalMatrix = GlobalInverse * globalTransform * bonesMatrix[bone].offsetMatrix;
	}


	UINT c;
	if (node1->mNumChildren < node2->mNumChildren)
		c = node1->mNumChildren;
	else
		c = node2->mNumChildren;

	for (UINT index = 0; index < c; index++)
	{
		ReadNodeHeirarchy(scene1, scene2, node1->mChildren[index], node2->mChildren[index], globalTransform, time1, time2);
	}

}

const aiNodeAnim* MultiSkinnedModel::FindNodeAnim(const aiAnimation* animation, const std::string nodeName)
{
	for (UINT index = 0; index < animation->mNumChannels; index++)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[index];
		if (std::string(nodeAnim->mNodeName.data) == nodeName)
			return nodeAnim;
	}
	return nullptr;
}

aiVector3D MultiSkinnedModel::interpolatePosition(float time, const aiNodeAnim* anim)
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

aiQuaternion MultiSkinnedModel::interpolateRotation(float time, const aiNodeAnim* anim)
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

aiVector3D MultiSkinnedModel::interpolateScaling(float time, const aiNodeAnim* anim)
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

UINT MultiSkinnedModel::findPosition(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumPositionKeys - 1; index++)
	{
		if (time < (float)anim->mPositionKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT MultiSkinnedModel::findRotation(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumRotationKeys - 1; index++)
	{
		if (time < (float)anim->mRotationKeys[index + 1].mTime)
			return index;
	}
	return 0;
}

UINT MultiSkinnedModel::findScaling(float time, const aiNodeAnim* anim)
{
	for (UINT index = 0; index < anim->mNumScalingKeys - 1; index++)
	{
		if (time < (float)anim->mScalingKeys[index + 1].mTime)
			return index;
	}
	return 0;
}
