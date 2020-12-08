#include "stdafx.h"
#include "Grid.h"
#include "Cube.h"
#include "Camera.h"
#include "Ray.h"
#include "ImguiClass.h"
#include "Tile.h"
#include "Light.h"
#include "toolMain.h"

CToolMain::CToolMain() : 
	m_pRay(NULL),
	m_pLight(NULL)
{
}

CToolMain::~CToolMain()
{
	SafeDelete(m_pGrid);
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);
	SafeDelete(m_pRay);
	SafeDelete(m_pLight);

	m_pImgui->Destroy();
	SafeDelete(m_pImgui);

	g_pFileLoadManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void CToolMain::Setup()
{
	g_pFileLoadManager->Setup();
	g_pDeviceManager->Setup();

	m_pGrid = new CGrid;
	m_pGrid->Setup(15, 1.0f);

	m_pCube = new CCube;
	m_pCube->Setup();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCube->GetPosition());

	m_pImgui = new CImguiClass;
	m_pImgui->Setup();

	m_pRay = new CRay;

	m_pLight = new CLight;
	m_pLight->Setup();
}

void CToolMain::Update()
{
//#ifdef _DEBUG
	// m_pCube->Update();
//#endif
	m_pCamera->Update();

	g_pObjectManager->Update();
	
	m_pImgui->Update();
}

void CToolMain::Render()
{
	m_pImgui->SetFrameEnd();

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.5, 0.5, 0.5, 1.0), 1.0f, 0);

	if (g_pD3DDevice->BeginScene() >= 0)
	{
		if(m_pGrid)
			m_pGrid->Render();

		g_pObjectManager->Render();

//#ifdef _DEBUG
		// if (m_pCube)
		// 	m_pCube->Render();
//#endif

		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		m_pImgui->Render(); // UI

		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);

		g_pD3DDevice->EndScene();
	}

	HRESULT result = g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && g_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		m_pImgui->ResetDevice();
}

void CToolMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		{
			CRay r = CRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			m_pRay->SetOrigin(r.GetOrigin());
			m_pRay->SetDirection(r.GetDirection());

			// ray
			if (m_pRay)
				g_pObjectManager->Update(m_pRay);
		}
	break;

	case WM_RBUTTONDOWN:
		CImguiClass::m_nowSelectindex = -1;
		CImguiClass::m_prevSelectIndex = 0;
		m_pRay->SetOrigin(D3DXVECTOR3(9999, 9999, 9999));
		m_pRay->SetDirection(D3DXVECTOR3(0, 0, 0));
		g_pObjectManager->SetSelectAllFalse();
		break;

	case WM_KEYDOWN:
		if (wParam == VK_DELETE)
		{
			g_pObjectManager->RemoveClickedObj();
			g_pFileLoadManager->SetIndexNumPrev();
			CImguiClass::m_nowSelectindex = -1;
			CImguiClass::m_prevSelectIndex = 0;
		}

		if (wParam == 'F')
		{
			int index = g_pObjectManager->GetSelectIndex();
			if (index != -1)
			{
				// D3DXVECTOR3 center = g_pFileLoadManager->GetSelectCenterPos(g_pObjectManager->GetIObject(index).GetTranslate());
				// m_pCamera->SetCameraPos(center);
				m_pCamera->SetCameraPos(g_pObjectManager->GetIObject(index).GetTranslate());
			}
		}
		break;
	}
}

CImguiClass* CToolMain::GetImgui()
{
	return m_pImgui;
}
