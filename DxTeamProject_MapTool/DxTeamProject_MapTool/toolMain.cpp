#include "stdafx.h"
#include "ImguiClass.h"
#include "toolMain.h"

CToolMain::CToolMain()
{
	m_pImgui = new CImguiClass;
}

CToolMain::~CToolMain()
{
	m_pImgui->Destroy();
	SafeDelete(m_pImgui);
}

void CToolMain::Setup()
{
	m_pImgui->Setup();
}

void CToolMain::Update()
{
	m_pImgui->Update();
}

void CToolMain::Render()
{
	m_pImgui->SetFrameEnd();

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.5, 0.5, 0.5, 1.0), 1.0f, 0);

	if (g_pD3DDevice->BeginScene() >= 0)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTexture(0, 0);

		// >> Do Render

		// << Do Render

		m_pImgui->Render(); // UI
		g_pD3DDevice->EndScene();
	}

	HRESULT result = g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && g_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		m_pImgui->ResetDevice();
}

void CToolMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	DefWindowProc(hWnd, msg, wParam, lParam);
}

CImguiClass* CToolMain::GetImgui()
{
	return m_pImgui;
}
