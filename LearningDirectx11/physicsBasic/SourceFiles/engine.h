#pragma once

#define MouseSensitivity 0.003

#include "main.h"
#include "renderer.h"
#include "shader.h"
#include "constantBuffer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "color.h"
#include "texture.h"
#include "model.h"
#include "skinnedModel.h"
#include "multiSkinnedModel.h"
#include "material.h"
#include "sprite.h"
#include "RTT.h"
#include "blur.h"
#include "shadow.h"
#include "input.h"
#include "sound.h"

/*Scene*/
#include "gameObject.h"
#include "scene.h"
#include "manager.h"

/*System*/
#include "camera.h"
#include "directionLight.h"
#include "pointLight.h"
#include "spotlight.h"

/*Physics*/
#include "boundingBox.h"
#include "collision.h"
#include "collisionSystem.h"
#include "ellipsoid.h"
#include "ray.h"



class Engine
{
public:
	static void Initialize();
	static void Update();
	static void Finalize();

	static std::wstring StringToWString(std::string str);

	static void ErrorMsg(std::string str);

	static XMMATRIX WorldTransform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling);
	static XMMATRIX WorldTransformRotAfter(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling);
	static XMMATRIX WorldTransform(XMFLOAT3 position, XMVECTOR rotation, XMFLOAT3 scaling);
	static XMMATRIX WorldTransformRotAfter(XMFLOAT3 position, XMVECTOR rotation, XMFLOAT3 scaling);

	static void Clamp(float& value, float min, float max);

	static int min(int x, int y);
	static int max(int x, int y);
	static float min(float x, float y);
	static float max(float x, float y);

	static void Interpolate(float& current, float target, float speed);
	static void Interpolate(XMFLOAT3& current, XMFLOAT3 target, float speed);

	static XMFLOAT3 VertexToWorld(XMFLOAT3 v, XMMATRIX worldMatrix);

	static void CalculateTangent(Vertex v[], UINT indicesSize);
	static void CalculateTangent(Vertex v1, Vertex v2, Vertex v3, XMFLOAT3& tangent, XMFLOAT3& bitangent);
};
