#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "Ray.h"
#include "Light.h"
#include "GridMap.h"
#include "Sphere.h"
#include "Cube.h"
#include "ParticleWorld.h"
#include "Xfile.h"

/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"
//#include "ColliderObject.h"
//#include "OBB.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_GridMap(NULL),
	m_pParticleWorld(NULL),
	m_Xfile(NULL)
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
	SafeDelete(m_GridMap);
	SafeDelete(m_pParticleWorld);
	SafeDelete(m_Xfile);

	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
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
	m_pGrid = new CGrid;
	m_pGrid->Setup(100, 1.0f);

	m_pCharacter = new CCharacter;
	m_pCharacter->Setup();

	m_pText = new CText;
	m_pText->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCharacter->GetPosition());

	m_pLight = new CLight;
	m_pLight->Setup();

	m_GridMap = new CGridMap;
	m_GridMap->Setup();
	m_pPrevFrustum.Setup();
	m_pNowFrustum.Setup();

	for (int i = 0; i < 8; i++)
	{
		CSphere* sphere = new CSphere(0.5f, D3DXVECTOR3(5, 0.5f, i * 3));
	}

	for (int i = 0; i < 8; i++)
	{
		CCube* cube = new CCube(D3DXVECTOR3(-5, 0.5f, i * 3));
	}

	g_pEventManager->AddListener(g_gameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}

	m_pParticleWorld = new CParticleWorld;
	m_pParticleWorld->Setup();

	m_Xfile = new CXfile;
	m_Xfile->Setup();

	/// 릴리즈 버전을 위한 주석처리
	//m_pLight->Setup(D3DXVECTOR3(0, -1, 0)); // sun light vector
	//m_pSm = new CSoundManager;
	//m_pSm->init();
	//Setup_OBB();
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	g_pEventManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection());
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
	}

	if (g_gameManager->GetGridMapMode())
	{
		m_pPrevFrustum = m_pNowFrustum;
		m_pNowFrustum.Update();
		if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum))
		{
			m_GridMap->CalcNewMap(&m_pNowFrustum);
		}
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	CRay ray = CRay::RayAtWorldSpace(rc.right / 2, rc.bottom / 2);
	g_pObjectManager->Update(ray, m_pCharacter->GetColor());

	if (m_pParticleWorld && g_gameManager->GetUImode() == false)
		m_pParticleWorld->Update(g_pTimeManager->GetElapsedTime());

	/// 릴리즈 버전을 위한 주석처리
	/// Lim Kyung Tae - Particle World
	//if (COBB::IsCollision(m_pCharacter->GetOBB(), m_pParticleWorld->GetOBB()) == true)
	//{
	//	cout << "in" << endl;
	//	D3DXVECTOR3 direction = m_pCharacter->GetPosition()- m_pParticleWorld->GetPosition();
	//	D3DXVec3Normalize(&direction, &direction);
	//	m_pParticleWorld->SetPusingForce(direction / 100.0f);
	//}

	/// Lee Min Jong - ColliderCube, Plane, Picking
	//for (int i = 0; i < m_vColliderCube.size(); ++i)
	//{
	//	if (COBB::IsCollision(m_pCharacter->GetOBB(), m_vColliderCube[i]->GetOBB()) == true)
	//	{		
	//		m_pCharacter->Collider(true);
	//		m_vColliderCube[i]->Update(m_pCharacter->GetColor());
	//	}
	//	else
	//	{	
	//		m_pCharacter->Collider(false);
	//		m_vColliderCube[i]->Update(m_vColliderCube[i]->GetColor());
	//	}
	//}
	//for (int i = 0; i < m_vecPlaneVertex.size(); i += 3)
	//{
	//	if (ray.IntersectTri(m_vecPlaneVertex[i + 0].p, m_vecPlaneVertex[i + 1].p, m_vecPlaneVertex[i + 2].p) == true)
	//	{
	//		for (int i = 0; i < 36; ++i)
	//		{
	//			m_vecPlaneVertex[i].isPicked = true;
	//		}
	//	}
	//	else
	//	{	
	//		for (int i = 0; i < 36; ++i)
	//		{
	//			m_vecPlaneVertex[i].isPicked = false;
	//		}
	//	}
	//}
	//for (int j = 0; j < 5; ++j)
	//{
	//	for (int i = 0; i < m_vColliderCube[j]->GetVecSize(); i += 3)
	//	{
	//		if (ray.IntersectTri(m_vColliderCube[j]->GetVecPosition(i+0) + m_vColliderCube[j]->GetPosition(),
	//			m_vColliderCube[j]->GetVecPosition(i+1) + m_vColliderCube[j]->GetPosition(),
	//			m_vColliderCube[j]->GetVecPosition(i+2) + m_vColliderCube[j]->GetPosition()) == true)
	//		{
	//			m_vColliderCube[j]->GetVecPick(true);
	//		}
	//		else
	//		{
	//			m_vColliderCube[j]->GetVecPick(false);
	//		}
	//	}
	//}
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150,150,150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	 if (m_pGrid)
	 	m_pGrid->Render();

	if (g_gameManager->GetDevMode())
	{
		if (m_pText)
		{
			m_pText->RenderFPS(g_pTimeManager->GetFPS());
			m_pText->RenderCharacterPosition(m_pCharacter->GetPosition());
			m_pText->RenderBoxPosition(m_pParticleWorld->GetPosition());
		}
	}

	if (m_pCharacter)
		m_pCharacter->Render();

	g_pObjectManager->Render();

	if (g_gameManager->GetGridMapMode())
	{
		m_GridMap->Render();
	}

	if (m_pParticleWorld)
		m_pParticleWorld->Render();

	if (m_Xfile)
		m_Xfile->Render(m_pCamera->GetCameraEye());

	/// 릴리즈 버전을 위한 주석처리

	//OBB_RENDER();

	if (g_gameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/// 릴리즈 버전을 위한 주석처리
//void CMainGame::Setup_OBB()
//{
//	for (int i = 0; i < 5; ++i)
//	{
//		m_vColliderCube.push_back(new CColliderObject);
//		m_vColliderCube[i]->Setup(D3DXVECTOR3(i * 2 + 3, 0.5f, i * 2 + 3));
//	}
//}
//
//void CMainGame::OBB_RENDER()
//{
//	for (vector<CColliderObject>::size_type i = 0; i < m_vColliderCube.size(); ++i)
//	{
//		m_vColliderCube[i]->Render();
//	}
//}