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
//#include "Sphere.h"
//#include "Cube.h"
#include "Xfile.h"
/// tmp Physics
#include "PhysicsSphere.h"
#include "Wall.h"
#include "PSphere.h"
#include "PSBox.h"
#include "PSCylinder.h"
#include "CHeight.h"

/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"
//#include "ParticleWorld.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_GridMap(NULL),
	m_Xfile(NULL),
	m_pHeightMap(NULL)
	/// tmp Physics
	//m_pSphere1(NULL),
	//m_pSphere2(NULL),
	//m_pWall(NULL)
	/// 릴리즈 버전을 위한 주석처리
	//m_pSm(NULL),
	//m_pParticleWorld(NULL),
{

}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	SafeDelete(m_pLight);
	SafeDelete(m_GridMap);
	SafeDelete(m_Xfile);
	SafeDelete(m_pHeightMap);
	/// tmp Physics
	//for(int i = 0; i < 4; ++i)
	//SafeDelete(m_pWall[i]);
	//g_pPhysicsObjectManager->Destroy();

	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	/// 릴리즈 버전을 위한 주석처리
	//SafeDelete(m_pSm);
	//SafeDelete(m_pParticleWorld);
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

	m_pLight = new CLight;
	m_pLight->Setup();

	m_GridMap = new CGridMap;
	m_GridMap->Setup();
	m_pPrevFrustum.Setup();
	m_pNowFrustum.Setup();

	//m_pHeightMap = new CHeight;
	//m_pHeightMap->Setup("HeightMapData", "HeightMap.raw");

	for (int i = 0; i < 8; i++)
	{
		CPSphere* Sphere = new CPSphere();
		Sphere->Setup(D3DXVECTOR3(5, 0.5f, 2 * i + 3));
	}

	for (int i = 0; i < 8; i++)
	{
		CPSBox* box = new CPSBox();
		box->Setup(D3DXVECTOR3(-5, 0.5, 2 * i + 3));
	}

	for (int i = 0; i < 8; i++)
	{
		CPSCylinder* cylinder = new CPSCylinder();
		cylinder->Setup(D3DXVECTOR3(2 * i - 7, 0.5, 20));
	}

	g_pEventManager->AddListener(g_gameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}

	m_Xfile = new CXfile;
	m_Xfile->Setup();

	/// 릴리즈 버전을 위한 주석처리
	//m_pLight->Setup(D3DXVECTOR3(0, -1, 0)); // sun light vector
	//m_pSm = new CSoundManager;
	//m_pSm->init();
	//m_pParticleWorld = new CParticleWorld;
	//m_pParticleWorld->Setup();
	/// tmp Physics
	//for (int i = 0; i < 4; i++)
	//{
	//	CPhysicsSphere* pSphere = new CPhysicsSphere;
	//	pSphere->setCenter(i, 0.21f, 0.0f);
	//	pSphere->setPower(-i, i);
	//}
	//m_pSphere1 = new CPhysicsSphere;
	//m_pSphere1->Setup();
	//m_pSphere1->setCenter(-2.7f, 5.0f, 0.0f);
	//m_pSphere2 = new CPhysicsSphere;
	////m_pSphere2->Setup();
	//m_pSphere2->setCenter(+2.4f, 0.21f, 0.0f);
	//m_pSphere2->setPower(0, 0);
	//for (int i = 0; i < g_pPhysicsObjectManager->getVecObject().size(); i++)
	//{
	//	g_pEventManager->AddListener(g_pPhysicsObjectManager->getVecObject()[i]);
	//}
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_pWall.push_back(new CWall);
	//}
	//m_pWall[0]->Setup(8.0f, 0.0f, 8.0f); 
	//m_pWall[0]->setPosition(0, 0, 0);
	//m_pWall[1]->Setup(0.12f, 0.3f, 6.24f);
	//m_pWall[1]->setPosition(-5, 0, 0);
	//m_pWall[2]->Setup(10, 0.3f, 0.12f);
	//m_pWall[2]->setPosition(0, 0, 3.0);
	//m_pWall[3]->Setup(10, 0.3f, 0.12f);
	//m_pWall[3]->setPosition(0, 0, -3.0);
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	g_pEventManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection(), m_pHeightMap);
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
	g_pObjectManager->Update();
	g_pObjectManager->Update(g_pTimeManager->GetElapsedTime());
	//g_pObjectManager->Update(g_pTimeManager->GetElapsedTime(), m_pHeightMap);

	/// 릴리즈 버전을 위한 주석처리
	/// Lim Kyung Tae - Particle World
	//if (m_pParticleWorld && g_gameManager->GetUImode() == false)
	//	m_pParticleWorld->Update(g_pTimeManager->GetElapsedTime());
	//if (COBB::IsCollision(m_pCharacter->GetOBB(), m_pParticleWorld->GetOBB()) == true)
	//{
	//	cout << "in" << endl;
	//	D3DXVECTOR3 direction = m_pCharacter->GetPosition()- m_pParticleWorld->GetPosition();
	//	D3DXVec3Normalize(&direction, &direction);
	//	m_pParticleWorld->SetPusingForce(direction / 100.0f);
	//}
	/// tmp Physics
	//g_pPhysicsObjectManager->Update(g_pTimeManager->GetElapsedTime());
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
	//m_pSphere2->Update(g_pTimeManager->GetElapsedTime());
	//m_pSphere1->Hitball(*m_pSphere2);
	//m_pWall[0]->hitBy(*m_pSphere1);
	//m_pWall[0]->hitBy(*m_pSphere2);
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

	g_pObjectManager->Render();

	if (g_gameManager->GetGridMapMode())
	{
		m_GridMap->Render();
	}

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
			//m_pText->RenderBoxPosition(m_pSphere1->getCenter());
			//m_pText->RenderGrab(g_pObjectManager->GetVecObject(), m_pCharacter->GetPosition());
		}
	}

	if (m_pText->GetisGrabstate())
		m_pText->RenderGrab();

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