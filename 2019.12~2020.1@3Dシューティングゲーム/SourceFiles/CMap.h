#pragma once
#define R  (99)
#define C  (99)
class Ray;


class CMap:public CGameObject
{

public:
	CMap();
	~CMap();
	
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	SBOX GetBlock() { return sBOXBlock; }
	bool AreYouKnockingOnTheABox(CGameObject* pOBj,Ray ray);
	bool AreYouKnockingOnTheOBox(CGameObject* pOBj, Ray ray);
	void SetObjectHeight(CGameObject* pOBj,XMFLOAT3& outPosH, float ErrorValue);
	void SetObjectHeight(XMFLOAT3 RayPos, XMFLOAT3& outPosH, float ErrorValue);
	void AIAction(int ZombieType,float dt);
private:
	void SetUpMap(SBOX sbox);
	AStarPathFinding* pA;
	pathNode	Map[R][C];
	std::vector<MyPoint> BodyWallMapPos;
	COLLIDER2 State_floor;
	SBOX sBOX;
	SBOX sBOXBlock;
	Line* pWorldCollider;
	BoundingBox box0;
	BoundingBox Box1;
	BoundingBox Box2;
	BoundingBox Box3;
	BoundingBox Box4;
	BoundingBox Box5;
	BoundingBox Box6;
	BoundingBox Box7;
	BoundingBox Box8;
	BoundingBox Box9;
	BoundingBox Box10;
	BoundingBox Box11;
	BoundingBox Box12;
	BoundingBox Box13;
	BoundingBox Box14;
	BoundingBox Box15;
	BoundingBox Box16;
	BoundingBox Box17;
	BoundingBox Box18;
	BoundingBox Box19obb;
	BoundingBox Box20obb;
	BoundingBox Box21obb;
	BoundingBox Box22obb;
	BoundingBox Box23obb;
	BoundingBox Box24obb;
	BoundingBox Box25obb;
	BoundingBox Box26obb;
	BoundingBox Box27obb;



	BoundingBox floorBox0;
	BoundingBox floorBox1;
	BoundingBox floorBox2;
	BoundingBox floorBox3;
public:
	BoundingBox GetFloorBox(int num)
	{
		BoundingBox box;
		switch (num)
		{
		case 0:
			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(XMConvertToRadians(35.0f), 0.0f, 0.0f);
			worlds *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
			worlds *= XMMatrixTranslation(0.0f, -40.0f, -20.0f);
			floorBox0.Transform(box, worlds);
			break;
		case 1:
			XMMATRIX world;
			world = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
			world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
			world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

			floorBox1.Transform(box, world);
			break;
		case 2:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);
			floorBox2.Transform(box, worlds);
			break;
		}
		case 3:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);
			floorBox3.Transform(box, worlds);
			break;
		}
		}

		return box;
	}
	BoundingBox GetWallBox(int num)
	{
		XMMATRIX world;
		world = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		BoundingBox box;
		switch (num)
		{
		case 0:
			box0.Transform(box, world);
			break;
		case 1:
			Box1.Transform(box, world);
			break;
		case 2:
			Box2.Transform(box, world);
			break;
		case 3:
			Box3.Transform(box, world);
			break;
		case 4:
			Box4.Transform(box, world);
			break;
		case 5:
			Box5.Transform(box, world);
			break;
		case 6:
			Box6.Transform(box, world);
			break;
		case 7:
			Box7.Transform(box, world);
			break;
		case 8:
			Box8.Transform(box, world);
			break;
		case 9:
			Box9.Transform(box, world);
			break;
		case 10:
			Box10.Transform(box, world);
			break;
		case 11:
			Box11.Transform(box, world);
			break;
		case 12:
			Box12.Transform(box, world);
			break;
		case 13:
			Box13.Transform(box, world);
			break;
		case 14:
			Box14.Transform(box, world);
			break;
		case 15:
			Box15.Transform(box, world);
			break;
		case 16:
			Box16.Transform(box, world);
			break;
		case 17:

			
			Box17.Transform(box, world);
			break;
		case 18:
			Box18.Transform(box, world);
			break;
		case 25:
			Box25obb.Transform(box, world);
			break;
		case 26:
			Box26obb.Transform(box, world);
			break;
		}

		
		return box;
	}
	BoundingOrientedBox Get_OBBOX(int numobb)
	{

		BoundingOrientedBox _obb;
		BoundingOrientedBox __obb;

		switch (numobb)
		{
		case 0:
		{
			XMFLOAT3 pos = { -140.0f, 0.0f, 96.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(45.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box19obb);
			_obb.Transform(__obb, worlds);
		}
			break;
		case 1:
		{
			XMFLOAT3 pos = { -150.0f, 0.0f, 73.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(19.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box20obb);
			_obb.Transform(__obb, worlds);
		}
		break;

		case 2:
		{
			XMFLOAT3 pos = { 20.0f,0.0f,-50.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-15.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box21obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 3:
		{
			XMFLOAT3 pos = { 14.0f,0.0f,-41.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-70.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box22obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 4:
		{
			XMFLOAT3 pos = { -9.0f,0.0f,-30.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-45.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box23obb);
			_obb.Transform(__obb, worlds);
		}
		break;

		case 5:
		{
			XMFLOAT3 pos = { -152.0f, 0.0f, 61.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(63.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box24obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 6:
		{
			XMFLOAT3 pos = { -117.0f, 0.0f, 59.0f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-60.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box24obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 7:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, floorBox2);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 8:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, floorBox3);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 9:
		{
			XMFLOAT3 pos = { -19.0f + 15.8f,0.0f,344.0f - 18.3f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-27.0f) + 6.4f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box24obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 10:
		{
			
			XMFLOAT3 pos = { -19.0f + 7.3,0.0f,344.0f - 9.4 };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-71.0f) + 6.2f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box24obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 11:
		{
			XMFLOAT3 pos = { -19.0f - 15.9f,0.0f,344.0f - 0.2f };
			XMFLOAT3 rot = { 0.0f,XMConvertToRadians(-45.0f),0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box24obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 12:
		{
			XMFLOAT3 pos = { 0.0f,0.0f,-3.0f };
			XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box27obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 13:
		{
			XMFLOAT3 pos = { 0.0f,0.0f,52.0f };
			XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, Box27obb);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 14:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, floorBox2);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 15:
		{
			XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
			XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, floorBox3);
			_obb.Transform(__obb, worlds);
		}
		break;
		case 16:
		{
			XMFLOAT3 pos = { 0.0f, -40.0f, -20.0f };
			XMFLOAT3 rot = { XMConvertToRadians(35.0f), 0.0f, 0.0f};
			XMFLOAT3 sca = { 1.0f,1.0f,1.0f };


			XMMATRIX worlds;
			worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
			worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

			BoundingOrientedBox::CreateFromBoundingBox(_obb, floorBox0);
			_obb.Transform(__obb, worlds);
		}
		break;
		}


		return __obb;
	}

};

