#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Light.h"
#include "SoundManager.h"
#include "Text.h"
#include "TimeManager.h"
#include "GridMap.h"
#include "ColliderObject.h"
#include "OBB.h"
#include "RigidBody.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pLight(NULL),
	m_pUI(NULL),
	m_pSm(NULL),
	m_pText(NULL),
	m_isDevMode(false),
	m_Uimode(false),
	m_GridMap(NULL), 
	m_pRigidbody(NULL),
	m_pRigidbody2(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pSm);
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pLight);
	SafeDelete(m_pText);
	SafeDelete(m_GridMap);
	SafeDelete(m_pRigidbody);
	g_pDeviceManager->Destroy();
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	if (m_pUI)
		m_pUI->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			m_pSm->PlaySFX("BombPut");
			break;
		}
		break;

		case WM_KEYDOWN:
		{
			if (GetKeyState(VK_CONTROL) & 0x8000 || GetKeyState(VK_CONTROL) & 0x0000)
				m_Uimode = !m_Uimode;
		

			if (GetKeyState(VK_TAB) & 0x8000 || GetKeyState(VK_TAB) & 0x0000)
				m_isDevMode = !m_isDevMode;
		}
			break;
		default:
			break;
	}
}

void CMainGame::Setup()
{
	//OBB
	Setup_OBB();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_vColliderCube[0]->GetPosition());

	m_GridMap = new CGridMap;
	m_GridMap->Setup();

	m_pGrid = new CGrid;
	m_pGrid->Setup();

	m_pLight = new CLight;
	//m_pLight->Setup();
	m_pLight->Setup(D3DXVECTOR3(0, -1, 0));		// 태양광 벡터 설정 가능

	m_pSm = new CSoundManager;
	m_pSm->init();

	m_pText = new CText;
	m_pText->Setup();

	m_pRigidbody = new CRigidBody;
	m_pRigidbody->Setup(D3DXVECTOR3(5, 30, 5), D3DXVECTOR3(0, -9.8f / 3, 0));

	m_pRigidbody2 = new CRigidBody;
	m_pRigidbody2->Setup(D3DXVECTOR3(-15, 2, -15), D3DXVECTOR3(1, 0, 1));
}

void CMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
	m_vColliderCube[0]->Update(c);

	for (int i = 0; i < 5; ++i)
	{
		if (COBB::IsCollision(m_vColliderCube[0]->GetOBB(), m_vColliderCube[i]->GetOBB()) == true)
		{
			c = D3DCOLOR_XRGB(255, 255, 0); // 충돌하였을때
			m_vColliderCube[i]->Update(c);		
		}
		else
		{
			c = D3DCOLOR_XRGB(255, 0, 0); // 충돌하지 않았을때
			m_vColliderCube[i]->Update(c);
		}
	}

	if (m_pRigidbody)
		m_pRigidbody->Update();

	if (m_pRigidbody2)
		m_pRigidbody2->Update();
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150,150,150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	OBB_RENDER();

	 //if (m_pGrid)
	 //	m_pGrid->Render();

	m_GridMap->Render();

	if (m_isDevMode)
	{
		if (m_pText)
			m_pText->Render(g_pTimeManager->GetFPS());
	}

	if (m_pRigidbody)
		m_pRigidbody->Render();

	if (m_pRigidbody2)
		m_pRigidbody2->Render();

	if (m_Uimode)
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Setup_OBB()
{
	for (int i = 0; i < 5; ++i)
	{
		m_vColliderCube.push_back(new CColliderObject);
		m_vColliderCube[i]->Setup(D3DXVECTOR3(i, 0, i));
	}

	CCharacter* pCharacter = new CCharacter;
	m_vColliderCube[0]->SetCharecterController(pCharacter);
	SafeRelease(pCharacter);
}

void CMainGame::OBB_RENDER()
{
	D3DCOLOR c = D3DCOLOR_XRGB(0, 0, 0);
	for (vector<CColliderObject>::size_type i = 0; i < m_vColliderCube.size(); ++i)
	{
		m_vColliderCube[i]->Render();
	}
}
