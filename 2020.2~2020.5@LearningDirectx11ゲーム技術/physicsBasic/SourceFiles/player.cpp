#include "engine.h"
#include "map.h"
#include "plane.h"
#include "staticObject.h"
#include "player.h"

AnimationData animationData[] =
{
	{0, 31},
	{1, 14},
	{2, 114},
	{3, 45},
	{4, 33},
	{5, 10},
	{6, 124},
	{7, 31},
	{8, 27},
	{9, 11},
	{10, 176},
	{11, 141},
	{12, 47},
	{13, 44},
	{14, 21},
	{15, 18},
	{16, 17},
	{17, 18},
	{18, 8},
	{19, 41},
	{20, 45},
	{21, 64},
	{22, 16},
	{23, 68},
	{24, 68},
	{25, 17},
	{26, 99},
	{27, 33},
	{28, 11},
	{29, 33},
	{30, 29},
	{31, 30},
	{32, 18},
	{33, 94}
};

Player::Player()
{
	this->m_Position = XMFLOAT3(0.0f, 3.0f, -8.0f);
	this->m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	this->event = 0;
	this->speed = 0.1f;
	this->counter = 0.0f;
	this->onJump = false;
	this->onReload = false;

	this->camY = 0.0f;
	this->restrictCam = true;
	this->updateCollision = true;

	//Ellipsoid
	ep.ellipsoidSpace = XMVectorSet(0.3f, 0.1f, 0.3f, 0.0f);
	ep.w_Position = m_PositionVec;

	m_PositionVec = XMLoadFloat3(&m_Position);
	m_At = m_PositionVec + (m_Front * 5.0f);

	this->Initialize();
}

void Player::Initialize()
{
	model = std::make_unique<SkinnedModel>("./Asset/Soldier/soldier1.x");

	//Add Collision Target
	ellipsoid = std::make_unique<Ellipsoid>(1.0f);
	ellipsoid->AddTargetObjects<Plane>();
	ellipsoid->AddTargetObjects<Map>();

	std::string mesh1[] =
	{
		{"soldier_weapon_mat_color.png"},
		{"soldier_weapon_mat_nmap.png"},
		{"soldier_weapon_mat_metalness.png"}
	};

	std::string mesh2[] =
	{
		{"soldier_soldier2_mat_color.png"},
		{"soldier_soldier2_mat_nmap.png"},
		{"soldier_soldier2_mat_metalness.png"}
	};

	model->RestrictTextures(mesh1, 3, 0);
	model->RestrictTextures(mesh2, 3, 0);

	this->myCollisions = model->GetMyCollisions();
}

void Player::Update()
{
	//Initialize
	ep.rightVelocity = 0.0f;
	ep.frontVelocity = 0.0f;
	ep.upVelocity -= 0.005f;	//Gravity

	model->Update(updateCollision);
	myCollisions = model->GetMyCollisions();

	m_PositionVec = XMLoadFloat3(&m_Position);

	/*--------------------------------------------------------------------------------
	Movement
	--------------------------------------------------------------------------------*/
	//Idle
	if (!Input::KeyPress('W') && !Input::KeyPress('A') && !Input::KeyPress('S') && !Input::KeyPress('D') && !Input::MouseLeftDown())
	{
		event = Event::Idle;
	}

	//Crouch Idle
	if (!Input::KeyPress('W') && !Input::KeyPress('A') && !Input::KeyPress('S') && !Input::KeyPress('D') && Input::KeyPress(VK_LCONTROL))
	{
		event = Event::CrouchIdle;
	}

	//Walk Forward
	if (Input::KeyPress('W') && !Input::KeyPress(VK_LSHIFT) && !Input::KeyPress(VK_LCONTROL) && !Input::KeyPress('A') && !Input::KeyPress('D'))
	{
		event = Event::WalkFront;
		ep.frontVelocity = speed;
	}

	//Walk Backward
	if (Input::KeyPress('S') && !Input::KeyPress('A') && !Input::KeyPress('D'))
	{
		event = Event::WalkBack;
		ep.frontVelocity = -speed;
	}

	//Walk Leftward
	if (Input::KeyPress('A') && !Input::KeyPress('W') && !Input::KeyPress('S'))
	{
		event = Event::WalkLeft;
		ep.rightVelocity = -speed / 2.0f;
	}

	//Walk Rightward
	if (Input::KeyPress('D') && !Input::KeyPress('W') && !Input::KeyPress('S'))
	{
		event = Event::WalkRight;
		ep.rightVelocity = speed / 2.0f;
	}

	//Walk Forward & Leftward
	if (Input::KeyPress('W') && Input::KeyPress('A'))
	{
		event = Event::WalkLeft;
		ep.rightVelocity = -speed / 2.0f / 2.0f;
		ep.frontVelocity = speed / 2.0f;
	}

	//Walk Forward & Rightward
	if (Input::KeyPress('W') && Input::KeyPress('D'))
	{
		event = Event::WalkRight;
		ep.rightVelocity = speed / 2.0f / 2.0f;
		ep.frontVelocity = speed / 2.0f;
	}

	//Walk Backward & Leftward
	if (Input::KeyPress('S') && Input::KeyPress('A'))
	{
		event = Event::WalkLeft;
		ep.rightVelocity = -speed / 2.0f / 2.0f;
		ep.frontVelocity = -speed / 2.0f;
	}

	//Walk Backward & Rightward
	if (Input::KeyPress('S') && Input::KeyPress('D'))
	{
		event = Event::WalkRight;
		ep.rightVelocity = speed / 2.0f / 2.0f;
		ep.frontVelocity = -speed / 2.0f;
	}

	//Run
	if (Input::KeyPress('W') && Input::KeyPress(VK_LSHIFT))
	{
		event = Event::Run;
		ep.frontVelocity = speed * 2.0f;
	}

	//Crouch
	if (Input::KeyPress(VK_LCONTROL) && Input::KeyPress('W'))
	{
		event = Event::Crouch;
		ep.frontVelocity = speed / 2.0f;
	}

	//Attack
	if (Input::MouseLeftDown() && !Input::KeyPress('W') && !Input::KeyPress('S') && !Input::KeyPress('A') && !Input::KeyPress('D'))
	{
		event = Event::Attack;
	}

	//Reload
	if (Input::KeyTrigger('R'))
	{
		event = Event::Reload;
		onReload = true;
	}

	//Jump
	if (Input::KeyTrigger(VK_SPACE))
	{
		event = Event::Jump;
		if(!restrictCam)
			ep.upVelocity = 0.11f;

		onJump = true;
		model->ResetTimer();
	}

	/*--------------------------------------------------------------------------------
	Animation Restriction
	--------------------------------------------------------------------------------*/
	if (onJump)
	{
		if (counter < 16.0f)
		{
			counter += 0.48f;
			event = Event::Jump;
		}
		else
		{
			counter = 0.0f;
			onJump = false;
		}
	}

	if (onReload)
	{
		if (counter < 45.0f)
		{
			counter += 0.48f;
			event = Event::Reload;
		}
		else
		{
			counter = 0.0f;
			onReload = false;
		}
	}

	/*--------------------------------------------------------------------------------
	Rotation
	--------------------------------------------------------------------------------*/
	XMMATRIX tempMatrix;

	float tempX = 0.0f;
	tempX = camY;

	camY += Input::MousePosY() * MouseSensitivity;

	//Restriction X axis rotation
	if (!restrictCam)
	{
		if (camY > 0.8f)
			camY = 0.8f;
	}
	else
	{
		if (camY > 0.0f)
			camY = 0.0f;
	}

	if (camY < -0.8f)
		camY = -0.8f;

	//Turning by Y axis	[Leftward or Rightward]
	tempMatrix = XMMatrixRotationY(Input::MousePosX() * MouseSensitivity);
	m_Front = XMVector3TransformNormal(m_Front, tempMatrix);
	m_Right = XMVector3TransformNormal(m_Right, tempMatrix);
	m_Up = XMVector3TransformNormal(m_Up, tempMatrix);

	//Turning by X axis	[Upward or Downward]
	tempMatrix = XMMatrixRotationAxis(m_Right, camY - tempX);
	m_Front = XMVector3TransformNormal(m_Front, tempMatrix);
	m_Right = XMVector3TransformNormal(m_Right, tempMatrix);
	m_Up = XMVector3TransformNormal(m_Up, tempMatrix);
	
	m_Rotation.x = XMConvertToDegrees(camY);
	m_Rotation.y += XMConvertToDegrees(Input::MousePosX() * MouseSensitivity);

	/*--------------------------------------------------------------------------------
	Update variable
	--------------------------------------------------------------------------------*/
	m_PositionVec = ellipsoid->Update(m_PositionVec, m_Right, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), m_Front, ep);

	XMStoreFloat3(&m_Position, m_PositionVec);
	m_At = m_PositionVec + (m_Front * 5.0f);

	worldMatrix = Engine::WorldTransform(m_Position, XMFLOAT3(0.0f, m_Rotation.y, 0.0f), m_Scale);

	GameObject::Update();
}

void Player::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	switch (event)
	{
	case Event::Idle:
		model->Render(worldMatrix, animationData[modelID::modelIdleNoWeapon].action, animationData[modelID::modelIdleNoWeapon].duration);
		break;
	case Event::WalkFront:
		model->Render(worldMatrix, animationData[modelID::modelWalk].action, animationData[modelID::modelWalk].duration);
		break;
	case Event::WalkBack:
		model->Render(worldMatrix, animationData[modelID::modelStrafeBack].action, animationData[modelID::modelStrafeBack].duration);
		break;
	case Event::WalkLeft:
		model->Render(worldMatrix, animationData[modelID::modelStrafeLeft].action, animationData[modelID::modelStrafeLeft].duration);
		break;
	case Event::WalkRight:
		model->Render(worldMatrix, animationData[modelID::modelStrafeRight].action, animationData[modelID::modelStrafeRight].duration);
		break;
	case Event::CrouchIdle:
		model->Render(worldMatrix, animationData[modelID::modelCrouchAimIdle].action, animationData[modelID::modelCrouchAimIdle].duration);
		break;
	case Event::Crouch:
		model->Render(worldMatrix, animationData[modelID::modelCrouchWalk].action, animationData[modelID::modelCrouchWalk].duration);
		break;
	case Event::Run:
		model->Render(worldMatrix, animationData[modelID::modelRunAim].action, animationData[modelID::modelRunAim].duration);
		break;
	case Event::Jump:
		model->Render(worldMatrix, animationData[modelID::modelJump].action, animationData[modelID::modelJump].duration);
		break;
	case Event::Attack:
		model->Render(worldMatrix, animationData[modelID::modelShotFast].action, animationData[modelID::modelShotFast].duration);
		break;
	case Event::Reload:
		model->Render(worldMatrix, animationData[modelID::modelReload].action, animationData[modelID::modelReload].duration);
		break;
	}
}

void Player::ImGui()
{
	ImGui::Begin("Player");
	ImGui::Checkbox("Update Collision", &updateCollision);
	ImGui::End();
}
