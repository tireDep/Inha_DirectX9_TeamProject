#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "Orb.h"
#include "Ray.h"
#include "Light.h"
#include "GridMap.h"
#include "PSphere.h"
#include "PSBox.h"
#include "PSCylinder.h"
#include "SkinnedMesh.h"
/// 이 아래는 지울 수도 있는 선언
#include "Xfile.h"
#include "CHeight.h"
// Ray y check
#include "MeshTile.h"
// Rotation Test
#include "TestForce.h"
#include "TestAngleSet.h"
#include "TestRigidBody.h"
/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_pOrb(NULL),
	// m_GridMap(NULL),
	/// 이 아래는 지울 수도 있는 선언
	m_Xfile(NULL),
	m_pHeightMap(NULL),
	m_pSkinnedMesh(NULL)
	// Ray y check
	, m_pMeshTile(NULL)
	// Rotation Test
	, m_pRigidBody(NULL)
	/// 릴리즈 버전을 위한 주석처리
	//m_pSm(NULL),

{

}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	SafeDelete(m_pLight);
	// SafeDelete(m_GridMap);
	/// 이 아래는 지울 수도 있는 선언
	SafeDelete(m_Xfile);
	SafeDelete(m_pHeightMap);
	SafeDelete(m_pSkinnedMesh);
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	// Ray y check
	SafeDelete(m_pMeshTile);
	// Rotation Test
	SafeDelete(m_pRigidBody);
	/// 릴리즈 버전을 위한 주석처리
	//SafeDelete(m_pSm);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ST_EVENT eventMsg;
	eventMsg.eventType = EventType::eInputEvent;
	eventMsg.message = message;
	eventMsg.wParam = wParam;
	eventMsg.lParam = lParam;

	g_pEventManager->CheckEvent(eventMsg);
	DefWindowProc(hWnd, message, wParam, lParam);
}

void CMainGame::Setup()
{
	g_pFileLoadManager->FileLoad_MapData();

	m_pGrid = new CGrid;
	m_pGrid->Setup(30, 1.0f);

	m_pCharacter = new CCharacter;
	m_pCharacter->Setup();

	m_pText = new CText;
	m_pText->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCharacter->GetPosition());

	m_pOrb = new COrb;
	m_pOrb->Setup();

	m_pLight = new CLight;
	m_pLight->Setup();
	//m_pLight->Setup(D3DXVECTOR3(1, 0, 0)); // sun light vector

	// m_GridMap = new CGridMap;
	// m_GridMap->Setup();
	m_pPrevFrustum.Setup();
	m_pNowFrustum.Setup();

	/// 이 아래는 지울 수도 있는 선언
	for (int i = 0; i < 8; i++)
	{
		CPSphere* Sphere = new CPSphere();
		Sphere->Setup(D3DXVECTOR3(25, 0.5f, 2 * i + 3));
	}
	for (int i = 0; i < 8; i++)
	{
		CPSBox* box = new CPSBox();
		box->Setup(D3DXVECTOR3(-25, 0.5, 2 * i + 3));
	}
	for (int i = 0; i < 8; i++)
	{
		CPSCylinder* cylinder = new CPSCylinder();
		cylinder->Setup(D3DXVECTOR3(2 * i - 7, 0.5, 25));
	}
	//m_pHeightMap = new CHeight;
	//m_pHeightMap->Setup("HeightMapData", "HeightMap.raw");
	m_Xfile = new CXfile;
	m_Xfile->Setup();

	m_pSkinnedMesh = new CSkinnedMesh;
	m_pSkinnedMesh->SetUp("Resource/XFile/Character", "character_test.X");

	g_pEventManager->AddListener(g_gameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}

	// Ray y check
	m_pMeshTile = new MeshTile;
	m_pMeshTile->Setup();

	// Rotation Test
	m_pRigidBody = new CTestRigidBody;
	m_pRigidBody->Setup();
	/// 릴리즈 버전을 위한 주석처리
	//m_pSm = new CSoundManager;
	//m_pSm->init();
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	g_pEventManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection(), m_pHeightMap);	// heightmap... change
		switch (m_pUI->GetPickColor())
		{
		case Pick::Red:
			m_pCharacter->SetColor(RED);
			m_pUI->SetPickColor();
			break;
		case Pick::Yellow:
			m_pCharacter->SetColor(YELLOW);
			m_pUI->SetPickColor();
			break;
		case Pick::Green:
			m_pCharacter->SetColor(GREEN);
			m_pUI->SetPickColor();
			break;
		case Pick::Blue:
			m_pCharacter->SetColor(BLUE);
			m_pUI->SetPickColor();
			break;
		case Pick::Black:
			m_pCharacter->SetColor(BLACK);
			m_pUI->SetPickColor();
			break;
		case Pick::White:
			m_pCharacter->SetColor(WHITE);
			m_pUI->SetPickColor();
			break;
		default:
			break;
		}
		// grab
		if (m_pCharacter->Update(g_pObjectManager->GetVecObject()) != -1)
		{
			m_pText->SetisGrabstate(true);
			D3DXVECTOR3 v;
			v.x = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().x - m_pCharacter->GetPosition().x;
			v.y = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().y - m_pCharacter->GetPosition().y - 0.5f;
			v.z = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().z - m_pCharacter->GetPosition().z;
			D3DXVec3Normalize(&v, &v);
			g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->SetPusingForce(v);
		}
		else
		{
			m_pText->SetisGrabstate(false);
		}
		// Ray y check
		m_pCharacter->UpdateRayYCheck(*m_pMeshTile);
	}

	// if (g_gameManager->GetGridMapMode())
	// {
	// 	m_pPrevFrustum = m_pNowFrustum;
	// 	m_pNowFrustum.Update();
	// 	if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum))
	// 	{
	// 		m_GridMap->CalcNewMap(&m_pNowFrustum);
	// 	}
	// }

	if (g_gameManager->GetGridMapMode())
	{
		m_pPrevFrustum = m_pNowFrustum;
		m_pNowFrustum.Update();

		static D3DXVECTOR3 lastPlayerPos = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 tempPos = m_pCharacter->GetPosition();
		float posCheck = 0.5f;

		// >> todo : 판정 변경
		if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum) 
		 || fabs(lastPlayerPos.x - tempPos.x) >= posCheck 
		 || fabs(lastPlayerPos.y - tempPos.y) >= posCheck 
		 || fabs(lastPlayerPos.z - tempPos.z) >= posCheck)
		{
			lastPlayerPos = tempPos;
			g_pObjectManager->UpdateNewMap(&m_pNowFrustum);
		}
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	CRay ray = CRay::RayAtWorldSpace(rc.right / 2, rc.bottom / 2);
	g_pObjectManager->Update(ray, m_pCharacter->GetColor());					// Color Change
	g_pObjectManager->Update();													// Collision
	g_pObjectManager->Update(g_pTimeManager->GetElapsedTime());					// 2D Physics
	//g_pObjectManager->Update(g_pTimeManager->GetElapsedTime(), m_pHeightMap);	// 3D Physics

	// Rotation Test
	m_pRigidBody->Update(g_pTimeManager->GetElapsedTime());

	/// 릴리즈 버전을 위한 주석처리
	// 민종씨 코드
	//static int count = 0;
	//static float gravity = -0.98;
	//static float plane = 1.5;
	//if (m_pWall[0]->Gravity(*m_pSphere1) == true) //땅에 부딪혔을때
	//{
	//	//cout << m_pWall[4]->Gravity(*m_pSphere1) << endl;
	//	m_pWall[0]->hitBy(*m_pSphere1);
	//	plane -= 0.3f;
	//	//cout << count++ << endl;
	//}
	//else // 떠있을때 중력을 줌
	//{
	//	if (m_pSphere1->getCenter().y > plane)
	//	{
	//		m_pSphere1->setPower(0, gravity, 0);
	//		//cout << m_pSphere1->getCenter().y << endl;
	//	}
	//}
	//	m_pSphere1->Update(g_pTimeManager->GetElapsedTime());
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pCharacter)
		m_pCharacter->Render();

	m_pOrb->SetBillbord();

	if (m_pOrb)
		m_pOrb->Render();
	g_pObjectManager->Render();

	// if (g_gameManager->GetGridMapMode())
	// {
	// 	m_GridMap->Render();
	// }

	 if (m_pSkinnedMesh)
	 	m_pSkinnedMesh->Render(NULL);

	if (m_Xfile)
		m_Xfile->Render(m_pCamera->GetCameraEye());

	//if (m_pHeightMap)
	//	m_pHeightMap->Render();

	if (g_gameManager->GetDevMode())
	{
		if (m_pText)
		{
			m_pText->RenderFPS(g_pTimeManager->GetFPS());
			m_pText->RenderCharacterPosition(m_pCharacter->GetPosition());
			g_pObjectManager->RenderOBBBox();
			//m_pText->RenderBoxPosition(m_pSphere1->getCenter());
			//m_pText->RenderGrab(g_pObjectManager->GetVecObject(), m_pCharacter->GetPosition());
		}
	}

	if (m_pText->GetisGrabstate())
		m_pText->RenderGrab();

	// Ray y check
	if (m_pMeshTile)
		m_pMeshTile->Render();

	// Rotation Test
	if (m_pRigidBody)
		m_pRigidBody->Render();

	/// 릴리즈 버전을 위한 주석처리
	//if (m_pParticleWorld)
	//	m_pParticleWorld->Render();
	/// tmp Physics
	//g_pPhysicsObjectManager->Render();
	//if (m_pSphere1)
	//	m_pSphere1->Render();
	//if (m_pSphere2)
	//	m_pSphere2->Render();
	//if (&m_pWall)
	//	m_pWall[0]->draw();
	//if (&m_pWall)
	//	m_pWall[0]->draw();
	//if (&m_pWall)
	//	m_pWall[2]->draw();
	//if (&m_pWall)
	//	m_pWall[3]->draw();
	if (g_gameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}