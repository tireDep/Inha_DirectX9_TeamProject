#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Cube.h"
#include "Grid.h"
#include "UI.h"
#include "Light.h"
#include "SoundManager.h"
#include "Text.h"
#include "TimeManager.h"
#include "GridMap.h"
#include "ColliderObject.h"
#include "OBB.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pCube(NULL),
	m_pLight(NULL),
	m_pUI(NULL),
	m_pSm(NULL),
	m_pText(NULL),
	m_isDevMode(true),
	m_GridMap(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pSm);
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pLight);
	SafeDelete(m_pText);
	SafeDelete(m_GridMap);
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

	m_pCube = new CCube;
	m_pCube->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCubePC->GetPosition());

	m_GridMap = new CGridMap;
	m_GridMap->Setup();

	m_pGrid = new CGrid;
	m_pGrid->Setup();

	m_pLight = new CLight;
	//m_pLight->Setup();
	m_pLight->Setup(D3DXVECTOR3(0, -1, 0));		// ÅÂ¾ç±¤ º¤ÅÍ ¼³Á¤ °¡´É

	m_pSm = new CSoundManager;
	m_pSm->init();

	m_pText = new CText;
	m_pText->Setup();
}

void CMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCube)
		m_pCube->Update();

	if (m_pCubePC)
		m_pCubePC->Update();

	if (m_pCubePC2)
		m_pCubePC2->Update();

	if (GetKeyState(VK_TAB) & 0x0001)
		m_isDevMode = false;
	else 
		m_isDevMode = true;
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

	//if (m_pCube)
	//	m_pCube->Render();

	OBB_RENDER();

	// if (m_pGrid)
	// 	m_pGrid->Render();

	m_GridMap->Render();

	if (m_isDevMode)
	{
		if (m_pText)
			m_pText->Render(g_pTimeManager->GetFPS());
	}

	if (m_pUI)
		m_pUI->UI_Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Setup_OBB()
{
	m_pCubePC =  new CColliderObject;
	m_pCubePC->Setup();
	m_pCubePC2 = new CColliderObject;
	m_pCubePC2->Setup();

	CCharacter* pCharacter = new CCharacter;
	m_pCubePC->SetCharecterController(pCharacter);
	SafeRelease(pCharacter);

}

void CMainGame::OBB_RENDER()
{
	D3DCOLOR c = D3DCOLOR_XRGB(0, 0, 0);
	if (COBB::IsCollision(m_pCubePC->GetOBB(), m_pCubePC2->GetOBB()) == true)
	{
		c = D3DCOLOR_XRGB(255, 255, 255);
	}


	if (m_pCubePC)
		m_pCubePC->Render(c);

	if (m_pCubePC2)
		m_pCubePC2->Render(c);
}
