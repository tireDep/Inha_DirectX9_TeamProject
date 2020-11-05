#include "stdafx.h"
#include "MainGame.h"
#include "Grid.h"
#include "Camera.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pGrid);
	g_pDeviceManager->Destroy();
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void CMainGame::Setup()
{
	m_pGrid = new CGrid;
	m_pGrid->Setup();

	m_pCamera = new CCamera;
	m_pCamera->Setup();
}

void CMainGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}