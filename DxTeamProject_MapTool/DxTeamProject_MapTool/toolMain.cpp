#include "stdafx.h"
#include "Grid.h"
#include "Cube.h"
#include "Camera.h"
#include "Ray.h"
#include "ImguiClass.h"
#include "Tile.h"
#include "Light.h"
#include "toolMain.h"
#include "Door.h"

CToolMain::CToolMain() : 
	m_pRay(NULL),
	m_pLight(NULL),
	m_isPushCtrl(false),
	m_isPushRBtn(false)
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
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && m_isPushCtrl)
	{
		if (GetKeyState(0x44) & 0x8000)
		{
			m_isPushCtrl = false;
			g_pObjectManager->CopyObject();
		} // << : if_D

	} // << : if

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

static D3DXVECTOR3 preRay(0, 0, 0);
static D3DXVECTOR3 nowRay(0, 0, 0);
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
		if(m_isPushCtrl)
		{
			// >> 오브젝트 설치
			m_isPushRBtn = true;

			CRay r = CRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			m_pRay->SetOrigin(r.GetOrigin());
			m_pRay->SetDirection(r.GetDirection());

			preRay = r.GetDirection();

			CreateObject_RBtn(r);
		}
		else
		{
			// >> 선택 취소
			CImguiClass::m_nowSelectindex = -1;
			CImguiClass::m_prevSelectIndex = 0;
			m_pRay->SetOrigin(D3DXVECTOR3(9999, 9999, 9999));
			m_pRay->SetDirection(D3DXVECTOR3(0, 0, 0));
			g_pObjectManager->SetSelectAllFalse();
		}
	break;

	case WM_RBUTTONUP:
		m_isPushRBtn = false;
		break;

	case WM_MOUSEMOVE:
		if (m_isPushRBtn)
		{
			CRay r = CRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			m_pRay->SetOrigin(r.GetOrigin());
			m_pRay->SetDirection(r.GetDirection());
			nowRay = r.GetDirection();

			if (fabs(nowRay.x - preRay.x) >= 0.03f
			 || fabs(nowRay.y - preRay.y) >= 0.03f
			 || fabs(nowRay.z - preRay.z) >= 0.03f)
			{
				preRay = nowRay;
				CreateObject_RBtn(r);
			}
		}
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBoxA(g_hWnd, "모든 오브젝트가 삭제됩니다.", "삭제", MB_OKCANCEL) == IDOK)
				g_pObjectManager->Destroy();
		}

		if (wParam == VK_CONTROL)
			m_isPushCtrl = true;

		if (wParam == VK_DELETE)
		{
			g_pObjectManager->RemoveClickedObj();
			g_pFileLoadManager->SetIndexNumPrev();
			CImguiClass::m_nowSelectindex = -1;
			CImguiClass::m_prevSelectIndex = 0;
		}

		if (wParam == 'F')
		{
			// >> 선택된 오브젝트에 포커스
			int index = g_pObjectManager->GetSelectIndex();
			if (index != -1)
				m_pCamera->SetCameraPos(g_pObjectManager->GetIObject(index).GetTranslate());
		}

		if (wParam == 'C')
		{
			// >> 선택된 오브젝트의 조건 오브젝트에 포커스
			int index = g_pObjectManager->GetConditionIndex();
			if (index != -1)
			{
				g_pObjectManager->SetSelectAllFalse();
				m_pCamera->SetCameraPos(g_pObjectManager->GetIObject(index).GetTranslate());
				g_pObjectManager->GetIObject(index).SetPick(true);
			}
		}
		break;

	case WM_KEYUP:
		if (wParam == VK_CONTROL)
			m_isPushCtrl = false;

		if (wParam == 0x44)
			m_isPushCtrl = true;

		break;
	}
}

CImguiClass* CToolMain::GetImgui()
{
	return m_pImgui;
}

void CToolMain::CreateObject_RBtn(CRay & r)
{
	// >> 우클릭 & 드래그로 오브젝트 생성
	if (!m_pRay)
		return;

	// >> 오브젝트 판정
	int size = g_pObjectManager->GetVecSize();
	for (int i = 0; i < size; i++)
	{
		if (g_pObjectManager->GetIObject(i).Update(m_pRay))
		{
			CImguiClass::CreateMouseRBtn();

			D3DXVECTOR3 pos = g_pObjectManager->GetHighestY(i);
			pos.y += 1.0f;
			SetCreateObjectPos(pos);

			return;
		}
	}

	// >> 바닥 판정
	vector<D3DXVECTOR3> vCheck = m_pGrid->GetGridVertex();
	D3DXVECTOR3 pos(0, 0, 0);
	for (int i = 0; i < vCheck.size(); i += 3)
	{
		if (r.IntersectTri(vCheck[i + 0], vCheck[i + 1], vCheck[i + 2], pos))
		{
			pos.x = floor(pos.x);		pos.x += 0.5f;
			pos.y = 0;
			pos.z = floor(pos.z);		pos.z += 0.5f;

			if (g_pObjectManager->GetIsAnotherPos(pos))
			{
				CImguiClass::CreateMouseRBtn();
				SetCreateObjectPos(pos);
				break;
			} // << : if_GetIsAnotherPos()

		} // << : if_IntersectTri

	}	// << : for

}

void CToolMain::SetCreateObjectPos(D3DXVECTOR3 pos)
{
	// >> 우클릭 & 드래그로 생성한 오브젝트 위치 값 설정
	if (g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).GetObjType() == eG_DoorFrame
		|| g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).GetObjType() == eG_Door)
	{
		CDoor* temp = static_cast<CDoor*>(&g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1));
		temp->SetAnotherTranslation(pos);
	}
	else
		g_pObjectManager->GetIObject(g_pObjectManager->GetVecSize() - 1).SetTranslate(pos);
}
