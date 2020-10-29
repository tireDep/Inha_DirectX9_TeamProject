#include "stdafx.h"
#include "MainGame.h"
#include "Camera.h"
#include "Cube.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pCube(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);

	g_pDeviceManager->Destroy();
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void CMainGame::Setup()
{
	m_pCube = new CCube;
	m_pCube->Setup();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCube->GetPosition());
}

void CMainGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCube)
		m_pCube->Update();
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150,150,150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pCube)
		m_pCube->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
