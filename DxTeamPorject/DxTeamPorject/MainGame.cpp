#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Cube.h"
#include "Grid.h"
#include "UI.h"
#include "Light.h"
#include "Timer.h"
#include "Fps.h"
#include "SoundManager.h"
#include "Text.h"
#include "TimeManager.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pCube(NULL),
	m_pLight(NULL),
	m_pUI(NULL),
	m_pTimer(NULL),
	m_pFps(NULL),
	m_pSm(NULL),
	m_pText(NULL),
	m_isDevMode(true)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pSm);
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pLight);
	SafeDelete(m_pTimer);
	SafeDelete(m_pFps);
	SafeDelete(m_pText);
	g_pDeviceManager->Destroy();
}

void CMainGame::Frame()
{
	m_pTimer->Frame();
	m_pFps->Frame();
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
	m_pCube = new CCube;
	m_pCube->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCube->GetPosition());

	m_pGrid = new CGrid;
	m_pGrid->Setup();

	m_pLight = new CLight;
	//m_pLight->Setup();
	m_pLight->Setup(D3DXVECTOR3(0, -1, 0));		// ÅÂ¾ç±¤ º¤ÅÍ ¼³Á¤ °¡´É

	m_pTimer = new CTimer;
	m_pTimer->Setup();

	m_pFps = new CFps;
	m_pFps->Setup();

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

	if (GetKeyState(VK_TAB) & 0x0001)
		m_isDevMode = false;
	else 
		m_isDevMode = true;
	Frame();
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



	if (m_pCube)
		m_pCube->Render();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_isDevMode)
	{
		if (m_pText)
			m_pText->Render(m_pFps->GetFps());
	}

	if (m_pUI)
		m_pUI->UI_Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
