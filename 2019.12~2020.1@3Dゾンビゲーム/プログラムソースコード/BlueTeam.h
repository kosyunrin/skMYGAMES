#pragma once
//Player one control
#define OTSP  8.0f //movespeed
#define ORSP  10.0f //rotaspeedfor p0
#define P0SP 20.0f;
#define P0SPSPEEDDOWN 15.0f;
#define ENEMYSP_RUN 18.0f
#define ENEMYSP_WALK 5.0f
#define ENEMY_SIZE 12.0f
#define ENEMY_ID 7.0f
#define UI_ID  11.0f
#define FONT_ID 13.0f
#define MAP_ID 8.0f
#define ShadowLight_ID 1.0f
//#include<DirectXCollision.h>
class CPolygon;
class CBlueArmy;
class CRedArmy;
class Timer;
struct MoveManager
{
	XMFLOAT3 PointIO;
	XMFLOAT3 FDirection;
	bool ismove;
	XMFLOAT4X4 RXMTRIX;
	float Radians;
	bool isenemy=false;
	int enemyID;
};
enum 
{
	_Camera,
	_skyBox,
	_Cfield,
	_Cplayer,
	_Enemy,
	_redBullet,
	_Cmeshfield,
	_solderHousered,
	_solderHouseblue,
	_blueBullet,
	_Friend,
	_GameUi
};
//tama target
enum 
{
	Tama_p0,
	Tama_p1,
	Tama_BlueXB,
	Tama_RedXB,
	Tama_RedXBfromB,
	Tama_BlueXBfromR,
	Tama_BlueHouse,
	Tama_RedXBfromHouse,
};
//army
enum
{
	XBRun,
	XBDead,
	XBAttack,
};
typedef struct BlueHouse
{
	float Nowlife;
	float Power;
	bool isLife;
};
 struct Enemy
{
	 XMFLOAT3 Pos;
	 XMFLOAT3 rot;
	 XMFLOAT4X4 world;
	 int BoneAnim;
};
typedef struct EnemyBullet
{
	BoundingSphere Collider;
	bool AttackObj;
};
 struct CFBulletDate
{
	std::vector<XMFLOAT3> Pos;
};
typedef struct FriendX
{
	BoundingSphere AttackRange;
	BoundingSphere Collider;
	bool islife;
	float Life;
	float AttackPower;
};
typedef struct DrawUI
{
	bool BuleDraw;
	bool Player1_UI_islife;
};
struct LAimryDate
{
	BoundingBox AABBBOX;
};
struct UserDate
{
	CBlueArmy* pB;
	CRedArmy* pR;
};
//bludearmyDate
struct BARMYDATE
{
	BoundingBox ABox;
	float life = 200.0f;
	CPolygon* pLife;
	int currAnim;
};

struct LPlayerOneDate
{
	BoundingBox AABBBOX;
	XMFLOAT4X4 m_WorldXmmrix;
	CPolygon* pLife;
	float life = 2000.0f;
	int CurrentAnim;
	bool UpAnim;
	bool PlayerOne;
	int target;
};
struct  P0Date
{
	int CurrentAnim;
	BoundingBox box;
	int HP;
	int SpeedControl;
	bool BeHurtAnimControl;
	bool JumpDownControl;
	bool JumpRunControl;
	int targetID;
	float PhysicalBar;
	int TouchNum;
	XMFLOAT3 ZomToPlyerDir;
};
struct SoundCountrol
{
	bool Run;
	bool Jump;
};
struct SNumberDate
{
	CPolygon* p1;
	CPolygon* p2;
	int N1;
	int N2;

};
struct SNumber
{
	int Bulletcount;
	int BulleSize;
	int MoneySize;
	int LifeTimer;
	int StageNum;
	int YaocaoSize;
	int EnemyCountInTheScene;
	int CommingTimer;
	
};
enum
{
	W,
	S,
	A,
	D,
	X,
	Y,
	miaozhun
};
enum COLLIDER
{
	NONE,
	WALLBOX0,
	WALLBOX1,
	WALLBOX2,
	WALLBOX3,
	WALLBOX4,
	WALLBOX5,
	WALLBOX6,
	WALLBOX7,
	WALLBOX8,
	WALLBOX9,
	WALLBOX10,
	WALLBOX11,
	WALLBOX12,
	WALLBOX13,
	WALLBOX14,
	WALLBOX15,
	WALLBOX16,
	WALLBOX17,
	WALLBOX18,
	WALLBOX19,
	WALLBOX20,
	WALLBOX21,
	WALLBOX22,
	WALLBOX23,
	WALLBOX24,
	WALLBOX25,
	WALLBOX26,
	WALLBOX27,
	WALLBOX28,
	WALLBOX29,
	WALLBOX30,
	WALLBOX31,
	MANSBOX,

};
enum COLLIDER2
{
	NONE2,
	FLOOR0,
	FLOOR1,
	FLOOR2,
	FLOOR3,
};
enum ControlXiput
{
	Ww,
	Ss,
	Aa,
	Dd
};
enum TextureType
{
	Tex_TypeAllof,
	Tex_DDS,
	Tex_PJNG
};
enum ZombieState
{
	zombie_active,
	zombie_atRest,
	zombie_atRestMove,
	zombie_AlreadyDead,
	zombie_InitalState
};
enum ZombieRestPos
{
	zombie_posDoor,
	zombie_posLeft,
	zombie_posRight,
	zombie_posTop,
};
struct ZOMBIEDATE
{
	int Currentanim;
	int HP;
	int xHp;
	bool IsDie;
	bool iswall;
	bool isFindPath;
	bool AnimationShow;
	int ID;
	float RotDeg;
	bool StopControl;
	Timer* pStopTimer;
	CPolygon* pBlood;
	ZombieState ZombieState;
	ZombieRestPos RestPos;
	XMFLOAT3 BeginDir;
	bool IsHpShow;
	float HpShowTimer;
	bool StopChangeState;
};
struct SFriendDate
{
	BoundingBox ABOX;
};
struct House
{
	BoundingBox ABOX;
	float HP = 2000.0f;
	CPolygon* pLife;
	int Target;
	int TargetID;
};
struct SBOX
{
	std::vector<BoundingOrientedBox> OBOX;
	std::vector<BoundingBox> ABOX;
	std::vector<BoundingBox> BlockABOX;
};
struct STRINGDRAW
{
	std::string  Text;
	bool StringSwitch;
	XMFLOAT2 Pos;
	XMFLOAT2 RotPoint;
	XMFLOAT2 Scale;
	float RotSpeed;
	XMVECTOR Color;
	int ID;
};
struct GOLDPOOR
{
	std::string  Text;
	XMFLOAT2 Pos;
	XMFLOAT2 RotPoint;
	XMFLOAT2 Scale;
	float RotSpeed;
	XMVECTOR Color;
	Timer* ptimer;
};
enum  SFont
{
	BulletCount,
	BulletSize,
	SurvivalTimer,
	AmountOfMoney,
	StageCount,
	YaochaoCount,
	EnemySize,
	ForEnemyTiming
};
enum class Equipment : int
{
	Gun,
	Knife,
	YaoShui,
	TiliYaoshiu,
};
struct EquipmentUI
{
	CPolygon* pEquipment;
	int textID;
};

