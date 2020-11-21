#include "stdafx.h"
#include "Grid.h"
#include "Cube.h"
#include "Camera.h"
#include "ImguiClass.h"
#include "toolMain.h"

CToolMain::CToolMain()
{
}

CToolMain::~CToolMain()
{
	SafeDelete(m_pGrid);
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);

	m_pImgui->Destroy();
	SafeDelete(m_pImgui);

	g_pDeviceManager->Destroy();
}

void CToolMain::Setup()
{
	g_pDeviceManager->Setup();

	m_pGrid = new CGrid;
	m_pGrid->Setup(25, 1.0f);

	m_pCube = new CCube;
	m_pCube->Setup();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCube->GetPosition());

	m_pImgui = new CImguiClass;
	m_pImgui->Setup();
}

void CToolMain::Update()
{
	m_pCube->Update();
	m_pCamera->Update();
	m_pImgui->Update();
}

void CToolMain::Render()
{
	m_pImgui->SetFrameEnd();
	
	//g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//g_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.5, 0.5, 0.5, 1.0), 1.0f, 0);

	if (g_pD3DDevice->BeginScene() >= 0)
	{
		if(m_pGrid)
			m_pGrid->Render();

		if (m_pCube)
			m_pCube->Render();

		m_pImgui->Render(); // UI

		g_pD3DDevice->EndScene();
	}

	HRESULT result = g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && g_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		m_pImgui->ResetDevice();
}

void CToolMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, msg, wParam, lParam);
}

CImguiClass* CToolMain::GetImgui()
{
	return m_pImgui;
}
