#include"B_header.h"
#include"mesh.h"
#include"Title.h"
#include"game.h"
#include"end.h"
#include"audio_clip.h"
#include"input.h"
#include"GamePad.h"
CScene* CManager::m_Scene = nullptr;
void CManager::Init()
{
	//CRenderer::Init("vertexShader.cso","pixelShader.cso");
	CRenderer::Init("MainVS.cso", "MainPS.cso");
	CInput::Init();
	CAudioClip::Init();
	Input::GamePad::Initialize();
	/*g_input = new CInput();
	g_input->Init();*/
	
	//g_input = new CInput();
	//g_input->Init();
	SetScene<Title>();
	/*g_sky = new skyBox();
	g_sky->Init();*/
	//g_model = new CModel();
	//g_model->Init();
	//g_Camera = new CCamera;
	//g_Camera->Init();
	//g_Polygon = new CPolygon();
	//g_Polygon->Init();
	//g_field = new CField();
	//g_field->Init();
	//g_gane[0] = new CCamera;
	

}

void CManager::Uninit()
{
	Input::GamePad::Finalize();
	m_Scene->Uninit();
	delete m_Scene;
	CAudioClip::Uninit();

	//g_input->Uninit();
	//delete g_input;

	//g_mesh->UnInit();
	//delete g_mesh;
	
	//m_Scene->Uninit();
	//delete m_Scene;

	/*g_input->Uninit();
	delete g_input;*/
	/*g_sky->UnInit();
	delete g_sky;*/
	//g_model->Uninit();
	//delete g_model;
	//g_Camera->Uninit();
	//delete g_Camera;
	//g_Polygon->UnInit();
	//delete g_Polygon;
	//g_field->UnInit();
	//delete g_field;
	CRenderer::Uninit();

}

void CManager::Update(float dt)
{

	CInput::Update();
	Input::GamePad::Update();
	/*g_input->Update();*/
	m_Scene->Update(dt);


	//CInput::Update();
	//g_sky->UpDate();
	//g_model->Update();
	//g_Camera->Update();
	//g_Polygon->UpDate();
	//g_field->UpDate();

}

void CManager::Draw()
{
	CRenderer::BeiginShadow();
	m_Scene->DrawShadow();
	//3D描画先！
	CRenderer::Begin();

	m_Scene->Draw();
	CRenderer::End();

}

CScene* CManager::GetScene()
{
	return m_Scene;
}





