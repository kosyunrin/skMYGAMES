#pragma once
class ArmyKnife;
namespace WEAPON
{
	enum  class Pattern;
	enum  class Type;
}
class CP0 : public CGameObject
{
public:
	CP0();
	~CP0();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	void DrawShadow();
private:
	WEAPON::Pattern m_WeaponPattern;
	WEAPON::Type m_WeaponType;
	MovieNum movieNum;
	std::unique_ptr<CAudioClip> chuanxi;
	std::unique_ptr<CAudioClip> jiaobu;
	
	SoundCountrol Sound;
	std::unique_ptr<Timer> pTimer;
	CSkinnedfbxanim* pModle;
	std::unique_ptr<ArmyKnife> m_Weapon_Knife;
	CPolygon* pZhunxin;
	CPolygon* pUI;
	P0Date SDate;
	COLLIDER State_Collider;
	int StateCollider;
	COLLIDER2 State_Floor;
	int FaceNumber;//
	ControlXiput xiputnum;
	float AnimationSpeed;
	//ä«óùÅ@ëOå„ÇÎ
	float rotBlend;
	float Left_Right;
	//ä«óùÅ@ç∂âE
	float rotBlend1;
	float rotBlend2;
	//DHÉJÉÅÉâä«óùblend
	float CameraRotBlend;
	float CameraRotBlendZ;
	float CameraRotBlendZ2;
	float CameraRotaBlendZ3;
	float CameraViewShootControl;
	//
	bool sheji;
	bool Huanzidancontrol; //huanzidan kongzhi 
	bool moveStop;//animation Ç‡é~ÇﬂÇƒÇÈ
	//bool WDirStop;//animation Ç‡é~ÇﬂÇƒÇ»Ç¢
	//bool SDirStop;//animation Ç‡é~ÇﬂÇƒÇ»Ç¢
	bool ZhunXSwitch;
	float ZHunxWH;
	float ZhunxColor;
	XMFLOAT2 ZhunxPos;
	Line* line;
	XMFLOAT4X4 boxMartix;
	XMFLOAT4X4 WorldMartix;
private:
	void MoveRevise(XMVECTOR& PlayerPos, XMVECTOR& ForwardMovement, float dt, XMVECTOR nowFaceDir);
	void AnimInit()
	{
		CameraRotBlend = 0.0f;
		CameraRotBlendZ = 0.0f;
		CameraRotBlendZ2 = 0.0f;
		SDate.TouchNum = 0.0f;
		CameraRotaBlendZ3 = 0.0f;
	}
public:
	void SetMyWeaponStatePattern(WEAPON::Pattern statepattren)
	{
		m_WeaponPattern = statepattren;
	}
	void SetMyWeapon_Type(WEAPON::Type type)
	{
		m_WeaponType = type;
	}
	void SetShejiBool(bool _bool)
	{
		sheji = false;
	}
	CPolygon* GetZhunxin() { return pZhunxin; }
	bool GetZhunXS() { return ZhunXSwitch; }
	XMFLOAT2 Get_ZXpos() { return ZhunxPos; }
	float Get_ZXWH() { return ZHunxWH; }
	BoundingBox Get_Box();
	BoundingSphere Get_Sphere();
	float Get_color() { return ZhunxColor; }
	XMMATRIX XMGet_WorldMatrix() { return XMLoadFloat4x4(&WorldMartix); }
	XMVECTOR XMGet_pos() { return XMLoadFloat3(&m_Position); }
	P0Date* GetP0Dataptr() { return &SDate; }
	void SetMovie(MovieNum num) { movieNum = num; }
	MovieNum GetMovieSate() { return movieNum; }
	void SetMiaozhunPos(XMFLOAT2 pos)
	{
		ZhunxPos = pos;
	}
};