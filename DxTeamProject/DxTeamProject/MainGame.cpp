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
#include "PhysicsSphere.h"
#include "Wall.h"
/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_GridMap(NULL),
	m_pParticleWorld(NULL),
	m_Xfile(NULL),
	m_pSphere1(NULL),
	m_pSphere2(NULL),
	m_pWall(NULL)
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
	//SafeDelete(m_pSphere1);
	//SafeDelete(m_pSphere2);
	
	for(int i = 0; i < 4; ++i)
	SafeDelete(m_pWall[i]);
	
	g_pObjectManager->Destroy();
	g_pPhysicsObjectManager->Destroy();
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
		CSphere* sphere = new CSphere(0.5f, D3DXVECTOR3(5, 0.5f, i + 3));
	}

	for (int i = 0; i < 8; i++)
	{
		CCube* cube = new CCube(D3DXVECTOR3(-10, 0.5f, i + 3));
	}

	for (int i = 0; i < 4; i++)
	{
		CPhysicsSphere* pSphere = new CPhysicsSphere;
		pSphere->setCenter(i, 0.21f, 0.0f);
		pSphere->setPower(-i, i);
	}

	//// tmp Physics
	m_pSphere1 = new CPhysicsSphere;
	//m_pSphere1->Setup();
	m_pSphere1->setCenter(-2.7f, 0.21f, 0.0f);
	m_pSphere1->setPower(5.0f, 10.0f);

	m_pSphere2 = new CPhysicsSphere;
	//m_pSphere2->Setup();
	m_pSphere2->setCenter(+2.4f, 0.21f, 0.0f);
	m_pSphere2->setPower(0, 0);

	g_pEventManager->AddListener(g_gameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}
	// 내일 예슬씨에게 질문 이름이 다른데 에러 호출
	for (int i = 0; i < g_pPhysicsObjectManager->getVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pPhysicsObjectManager->getVecObject()[i]);
	}

	m_pParticleWorld = new CParticleWorld;
	m_pParticleWorld->Setup();

	m_Xfile = new CXfile;
	m_Xfile->Setup();

	for (int i = 0; i < 4; ++i)
	{
		m_pWall.push_back(new CWall);
	}
	m_pWall[0]->Setup(0.12f, 0.3f, 6.24f); 
	m_pWall[0]->setPosition(5, 0, 0);

	m_pWall[1]->Setup(0.12f, 0.3f, 6.24f);
	m_pWall[1]->setPosition(-5, 0, 0);

	m_pWall[2]->Setup(10, 0.3f, 0.12f);
	m_pWall[2]->setPosition(0, 0, 3.0);

	m_pWall[3]->Setup(10, 0.3f, 0.12f);
	m_pWall[3]->setPosition(0, 0, -3.0);

	/// 릴리즈 버전을 위한 주석처리
	//m_pLight->Setup(D3DXVECTOR3(0, -1, 0)); // sun light vector
	//m_pSm = new CSoundManager;
	//m_pSm->init();
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

	// tmp
	g_pPhysicsObjectManager->Update(g_pTimeManager->GetElapsedTime());
	//for (int hittee = 0; hittee < 4; hittee++)
	//{
	//	for (int hitter = 0; hitter < 4; hitter++)
	//	{
	//		if (hittee >= hitter)
	//		{
	//			continue;
	//		}
	//		m_pPhysicsSphere[hittee]->Hitball(&m_pPhysicsSphere[hitter]);
	//		//m_pPhysicsSphere[hittee].hitBall(m_pPhysicsSphere[hitter]);
	//	}
	//}

	m_pSphere1->Update(g_pTimeManager->GetElapsedTime());
	m_pSphere2->Update(g_pTimeManager->GetElapsedTime());

	m_pSphere1->Hitball(*m_pSphere2);
	m_pWall[0]->hitBy(*m_pSphere1);
	m_pWall[0]->hitBy(*m_pSphere2);
	/// 릴리즈 버전을 위한 주석처리
	/// Lim Kyung Tae - Particle World
	//if (COBB::IsCollision(m_pCharacter->GetOBB(), m_pParticleWorld->GetOBB()) == true)
	//{
	//	cout << "in" << endl;
	//	D3DXVECTOR3 direction = m_pCharacter->GetPosition()- m_pParticleWorld->GetPosition();
	//	D3DXVec3Normalize(&direction, &direction);
	//	m_pParticleWorld->SetPusingForce(direction / 100.0f);
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
			//m_pText->RenderBoxPosition(m_pParticleWorld->GetPosition());
			//m_pText->RenderBoxPosition(m_pSphere1->getCenter());
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

	g_pPhysicsObjectManager->Render();
	if (m_pSphere1)
		m_pSphere1->Render();

	if (m_pSphere2)
		m_pSphere2->Render();

	if (&m_pWall)
		m_pWall[0]->draw();

	if (&m_pWall)
		m_pWall[1]->draw();

	if (&m_pWall)
		m_pWall[2]->draw();

	if (&m_pWall)
		m_pWall[3]->draw();
	/// 릴리즈 버전을 위한 주석처리

	if (g_gameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}