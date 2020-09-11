#pragma once
#include"material.h"
#define XBenemysize  (sizeof(XBenemy) / sizeof(XBenemy[0]))
#define NQsize  (sizeof(NQDate) / sizeof(NQDate[0]))
#define ZOMBIE_SIZE  (sizeof(ZombieDate) / sizeof(ZombieDate[0]))
#define MAN_SIZE  (sizeof(ManDate) / sizeof(ManDate[0]))
#define BLOCK_SIZE  (sizeof(BLockDate) / sizeof(BLockDate[0]))
#define BLOOD_SIZE (sizeof(BloodDate) / sizeof(BloodDate[0]))
struct SFbxanimtype
{
	 std::string  name;
};

 static SFbxanimtype  XBenemy[]
{
	{"asset/Onepiece/xbwark.fbx"},
	{"asset/Onepiece/xbdie.fbx"},
	{"asset/Onepiece/xbattack.fbx"}
};
 static SFbxanimtype NQDate[]
 {
	 //NQDaoState
	 {"asset/Onepiece/NQidiot.fbx"},
	 {"asset/Onepiece/NQDianShe.fbx"},
	 {"asset/Onepiece/NQpaobu.fbx"},
	 {"asset/Onepiece/NQsaoshe.fbx"},
	 {"asset/Onepiece/NQmiaozhun.fbx"},
	 {"asset/Onepiece/NQShouSangSate.fbx"},
	  {"asset/Onepiece/NQHuanzidan10-24run.fbx"},
	   {"asset/Onepiece/NQHuanzidan24.fbx"},
		{"asset/Onepiece/NQHurtDh50.fbx"},
		{"asset/Onepiece/NQDie.fbx"},
		{"asset/Onepiece/NQJump100.fbx"},
		{"asset/Onepiece/NqJumpidiot.fbx"},
		{"asset/Onepiece/NQJumpRun_50.fbx"},
		{"asset/Onepiece/NQDaoState.fbx"},
		{"asset/Onepiece/NQDaoAttack24.fbx"}
 };
 static SFbxanimtype ZombieDate[]
 {
	  {"asset/Onepiece/zombieRun.fbx"},
	  {"asset/Onepiece/Zombie.fbx"},
	  {"asset/Onepiece/zhombieDead.fbx"},
	  {"asset/Onepiece/zombiehurt.fbx"}
 };
 static SFbxanimtype ManDate[]
 {
	  {"asset/Onepiece/Man_run.fbx"},
	  {"asset/Onepiece/Man_wark.fbx"},
	  {"asset/Onepiece/Manwark_Up.fbx"},
	  {"asset/onepiece/Manhurt_duzhi.fbx"},
	 {"asset/onepiece/Manhurt_head.fbx"},
	  {"asset/onepiece/Man_StopAttack39.fbx"},
	   {"asset/onepiece/MAN_DIEEING.fbx"},
	   {"asset/onepiece/MAN_DIE.fbx"},
		{"asset/onepiece/manAttackDH30.fbx"},
		{"asset/onepiece/man_idle.fbx"},
		{"asset/onepiece/Man_StopAttack39.fbx"}
 };
 static SFbxanimtype BLockDate[]
 {
	 {"asset/Onepiece/zhixianganim.fbx"},
	 {"asset/Onepiece/zhixianganimbud.fbx"},
	 {"asset/Onepiece/zhiheanimbud2.fbx"}
 };
 static SFbxanimtype BloodDate[]
 {
	 {"asset/Onepiece/ICEAnim.fbx"}
 };
 enum
 {
	 man_run,
	 man_wark,
	 Manwark_Up,
	 Manhurt_duzhi,
	 Manhurt_head,
	 Man_attack,
	 Man_dead,
	 Man_isDie,
	 Man_attack_DH,
	 Man_idle,
	 Man_StopAttack
 };
 enum
 {
	 Zombie_run,
	 Zombie_attack,
	 Zombie_dead,
	 Zombie_hurt
 };
 enum
 {
	 MoveBack,
	 MoveAttack,
 };
 enum
 {
	 _idie,
	 _NAttack,
	 _Run,
	 _Skill_one,
	 _miaozhun,
	 _SsangSate,
	 _HZD1,
	 _HZD2,
	 _SsangDH,
	 _NQdie,
	 _NQJUMP,
	 _NQJumpStop,
	 _NQJunmpRun,
	 _NQDaomiaozhun,
	 _NQDaoattack
 };
 enum MovieNum
 {
	 LensOne,
	 LensTwo,
 };
struct MODEL_ASSIMP
{

	std::vector<VERTEX_3D> vetexNum;
	std::vector<WORD> indexNum;
	std::vector<Material> material;
	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer*	m_IndexBuffer = NULL;

};
struct SStaticMode
{
	std::vector<VERTEX_3D> vs;
	std::vector<DWORD> indices;
	std::vector<Material> material;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};
//skinned
struct SkinnedMesh
{
	std::vector<BonesVertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Material> material;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

};
struct BoneMatrix
{
	XMMATRIX offsetMatrix;
	XMMATRIX finalMatrix;
	XMMATRIX localWorldMatrix;
};
//
struct BoxPonit
{
	XMFLOAT3 Vmax;
	XMFLOAT3 Vmin;
};
struct MeshPart
{
	BoxPonit m_BoxPoint;
};
//

class CManagerOfModle
{
private:

public:

};
