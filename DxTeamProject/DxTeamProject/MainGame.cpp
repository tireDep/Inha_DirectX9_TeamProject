#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "ColliderObject.h"
#include "OBB.h"
#include "Ray.h"
#include "Light.h"

#include "ParticleWorld.h"

/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"
//#include "GridMap.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_pParticleWorld(NULL)
	/// 릴리즈 버전을 위한 주석처리
	//m_pSm(NULL),
	//m_GridMap(NULL)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	SafeDelete(m_pLight);
	SafeDelete(m_pParticleWorld);
	g_pDeviceManager->Destroy();
	/// 릴리즈 버전을 위한 주석처리
	//SafeDelete(m_pSm);
	//SafeDelete(m_GridMap);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pInputManager->CheckInput(message, wParam, lParam);
	//m_pUI->WndProc(hWnd,message,wParam,lParam);
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

	Setup_PickingObj();

	m_pLight = new CLight;
	m_pLight->Setup();

	//m_pParticleWorld = new CParticleWorld;
	//m_pParticleWorld->Setup();

	/// 릴리즈 버전을 위한 주석처리
	//m_pLight->Setup(D3DXVECTOR3(0, -1, 0));		// 태양광 벡터 설정 가능
	//m_GridMap = new CGridMap;
	//m_GridMap->Setup();
	//m_pSm = new CSoundManager;
	//m_pSm->init();
	
	g_pInputManager->Setup();
	g_pInputManager->AddListener(g_gameManager);
	g_pInputManager->AddListener(m_pCamera);
	g_pInputManager->AddListener(m_pCharacter);
	g_pInputManager->AddListener(m_pUI);
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	g_pInputManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection());
		if (m_pUI->GetPickColor())
			m_pCharacter->SetColor(D3DCOLOR_XRGB(255, 0, 0));
	}
		
	for (int i = 0; i < 1; ++i)
	{
		if (COBB::IsCollision(m_pCharacter->GetOBB(), m_vColliderCube[i]->GetOBB()) == true)
		{		
			m_pCharacter->Collider(true);
			m_vColliderCube[i]->Update(m_pCharacter->GetColor());
		}
		else
		{	
			m_pCharacter->Collider(false);
			m_vColliderCube[i]->Update(m_vColliderCube[i]->GetColor());
		}
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	CRay r = CRay::RayAtWorldSpace(rc.right / 2, rc.bottom / 2);

	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		if (r.IsPicked(&m_vecSphere[i]) == true)
		{
			m_vecSphere[i].isPicked = true;
		}
		else
		{
			m_vecSphere[i].isPicked = false;
		}

	}
	//if(m_pParticleWorld)
	//	m_pParticleWorld->Update(g_pTimeManager->GetElapsedTime());
	/// 릴리즈 버전을 위한 주석처리
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

	PickingObj_Render();

	//if (m_pParticleWorld)
	//	m_pParticleWorld->Render();
	/// 릴리즈 버전을 위한 주석처리
	//m_GridMap->Render();

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

void CMainGame::Setup_PickingObj()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	for (int i = 0; i <= 10; i++)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i);
		m_vecSphere.push_back(s);
		m_vecSphere[i].isPicked = false;
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
}

void CMainGame::PickingObj_Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ?
			&m_stMtlPicked : &m_stMtlNone);
		m_pMeshSphere->DrawSubset(0);
	}
	g_pD3DDevice->SetMaterial(&m_stMtlNone);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMeshSphere->DrawSubset(0);
}