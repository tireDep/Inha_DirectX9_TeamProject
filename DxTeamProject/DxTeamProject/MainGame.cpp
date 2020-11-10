#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "ColliderObject.h"
#include "OBB.h"

/// 릴리즈 버전을 위한 주석처리
//#include "Light.h"
//#include "SoundManager.h"
//#include "GridMap.h"
//#include "RigidBody.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL)
	/// 릴리즈 버전을 위한 주석처리
	//m_pLight(NULL),
	//m_pSm(NULL),
	//m_GridMap(NULL),
	//m_pRigidbody(NULL),
	//m_pRigidbody2(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	g_pDeviceManager->Destroy();
	/// 릴리즈 버전을 위한 주석처리
	//SafeDelete(m_pSm);
	//SafeDelete(m_pLight);
	//SafeDelete(m_GridMap);
	//SafeDelete(m_pRigidbody);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pInputManager->CheckInput(message, wParam, lParam);

}

void CMainGame::Setup()
{
	Setup_OBB();

	m_pGrid = new CGrid;
	m_pGrid->Setup(50, 1.0f);

	m_pCharacter = new CCharacter;
	m_pCharacter->Setup();

	m_pText = new CText;
	m_pText->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCharacter->GetPosition());

	/// 릴리즈 버전을 위한 주석처리
	//m_GridMap = new CGridMap;
	//m_GridMap->Setup();
	//m_pLight = new CLight;
	////m_pLight->Setup();
	//m_pLight->Setup(D3DXVECTOR3(0, -1, 0));		// 태양광 벡터 설정 가능
	//m_pSm = new CSoundManager;
	//m_pSm->init();
	//m_pRigidbody = new CRigidBody;
	//m_pRigidbody->Setup(D3DXVECTOR3(5, 30, 5), D3DXVECTOR3(0, -9.8f / 3, 0));
	//m_pRigidbody2 = new CRigidBody;
	//m_pRigidbody2->Setup(D3DXVECTOR3(-15, 2, -15), D3DXVECTOR3(1, 0, 1));

	g_pInputManager->AddListener(g_gameManager);
	g_pInputManager->AddListener(m_pCamera);
}

void CMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();
	if (m_pCharacter)
		m_pCharacter->Update(m_pCamera->GetCameraDirection());		// 추가. 카메라의 벡터 받아오기

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);

	m_pCharacter->m_pOBB->Update(m_pCharacter->GetTransform());
	for (int i = 0; i < 1; ++i)
	{
		if (COBB::IsCollision(m_pCharacter->GetOBB(), m_vColliderCube[i]->GetOBB()) == true)
		{
			m_vColliderCube[i]->Update(m_pCharacter->GetColor());
		}
		else
		{
			m_vColliderCube[i]->Update(c);
		}
	}

	/// 릴리즈 버전을 위한 주석처리
	//if (m_pRigidbody)
	//	m_pRigidbody->Update();
	//if (m_pRigidbody2)
	//	m_pRigidbody2->Update();
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150,150,150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	 if (m_pGrid)
	 	m_pGrid->Render();

	if (g_gameManager->GetDevMode())
	{
		if (m_pText)
			m_pText->Render(g_pTimeManager->GetFPS());
	}

	if (m_pCharacter)
		m_pCharacter->Render();
	OBB_RENDER();

	/// 릴리즈 버전을 위한 주석처리
	//m_GridMap->Render();
	//if (m_pRigidbody)
	//	m_pRigidbody->Render();
	//if (m_pRigidbody2)
	//	m_pRigidbody2->Render();

	if (g_gameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Setup_OBB()
{
	for (int i = 0; i < 1; ++i)
	{
		m_vColliderCube.push_back(new CColliderObject);
		m_vColliderCube[i]->Setup(D3DXVECTOR3(i * 2 + 3, 0.5f, i * 2 + 3));
	}
}

void CMainGame::OBB_RENDER()
{
	for (vector<CColliderObject>::size_type i = 0; i < m_vColliderCube.size(); ++i)
	{
		m_vColliderCube[i]->Render();
	}
}
