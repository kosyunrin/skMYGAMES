#pragma once

class Player :public GameObject
{
private:
	enum modelID
	{
		modelWalk,
		modelAimToShoot,
		modelCrouchAimIdleLookAround,
		modelCrouchAimIdle,
		modelCrouchToStand,
		modelCrouchToWalk,
		modelCrouchWalkLookAround,
		modelCrouchWalk,
		modelDeath,
		modelGetReady,
		modelIdleLookAround,
		modelIdelNoWeaponLookAround,
		modelIdleNoWeapon,
		modelIdleWithWeapon,
		modelJump,
		modelLowerWeapon,
		modelMelee,
		modelRaiseWeapon,
		modelReadyToShoot,
		modelRecover,
		modelReload,
		modelRunAimLookAround,
		modelRunAim,
		modelRunWeaponDownLookAround2,
		modelRunWeaponDownLookAround,
		modelRunWeaponDown,
		modelShotFastAllAround,
		modelShotFast,
		modelShot,
		modelStrafeBack,
		modelStrafeLeft,
		modelStrafeRight,
		modelStrafeToCrouch,
		modelWalkLookAround,
		modelMax
	};

private:
	enum Event
	{
		Idle,
		WalkFront,
		WalkBack,
		WalkLeft,
		WalkRight,
		CrouchIdle,
		Crouch,
		Run,
		Jump,
		Attack,
		Reload,
	};

	std::unique_ptr<SkinnedModel> model;
	std::unique_ptr<Ellipsoid> ellipsoid;
	EllipsoidPack ep;

	UINT event;

	float speed;
	float counter;
	bool onJump;
	bool onReload;

	float camY;
	bool restrictCam;
	bool updateCollision;

	void Initialize() override;

public:
	Player();

	void Update() override;
	void Render(bool boundingBox) override;

	void SetRestrictCam(bool b) { restrictCam = b; }
	void ImGui();
};