#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "cObjLoader.h"
#include "cGroup.h"

#include "cObjMap.h"

#include "cFrame.h"
#include "cAseLoader.h"

#include "Ray.h"

#include "HeigthMap.h"

#include "SkinnedMesh.h"

#include "Frustum.h"

#include "Zealot.h"
#include "OBB.h"

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
	// float to dword
}

void SetBillBoard();

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL) 
	, m_pTexture(NULL)
	, m_directLight(NULL)
	, m_SpotLight(NULL)
	, m_PointLight(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_pMeshTeaPot(NULL)
	, m_pMeshSphere(NULL)
	, m_pObjMesh(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pFrustum(NULL)
	, m_pHoldZealot(NULL)
	, m_pMoveZealot(NULL)
	, m_pFont(NULL)
	, m_p3DText(NULL)
	, m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pShader(NULL)
	, m_heightMap(NULL)
{

}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC); 
	SafeDelete(m_pCamera); 
	SafeDelete(m_pGrid); 
	SafeDelete(m_pCubeMan); 
	SafeRelease(m_pTexture); 

	SafeDelete(m_directLight);
	SafeDelete(m_SpotLight);
	SafeDelete(m_PointLight);

	SafeDelete(m_pMap);

	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();

	m_pRootFrame->Destroy();

	// >> mesh
	SafeRelease(m_pMeshTeaPot);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pObjMesh);
	for each(auto p in m_vecObjMtlTex)
	{
		SafeRelease(p);
	}
	m_vecObjMtlTex.clear();
	// << mesh

	SafeDelete(m_pFrustum);

	SafeDelete(m_pSkinnedMesh);

	// >> OBB
	SafeDelete(m_pHoldZealot);
	SafeDelete(m_pMoveZealot);
	// << OBB

	//>> font
	SafeRelease(m_pFont);
	SafeRelease(m_p3DText);

	g_pFontManager->Destroy();
	//>> font

	// >> UI
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	// << UI

	SafeRelease(m_pShader);

	SafeDelete(m_heightMap);

	g_pObjectManger->Destroy();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePC; 
	m_pCubePC->Setup(); 

	m_pCubeMan = new cCubeMan; 
	m_pCubeMan->Setup(); 

	m_pCamera = new cCamera; 
	m_pCamera->Setup(&m_pCubeMan->GetPosition()); 
	// &m_pCubePC->GetPosition());

	m_pGrid = new cGrid; 
	m_pGrid->Setup(); 

	// >> : for texture  
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"../image/mkLink.png", &m_pTexture); 
		ST_PT_VERTEX v; 
		v.p = D3DXVECTOR3(0, 0, 0); 
		v.t = D3DXVECTOR2(0, 0.5); 
		m_vecVertex.push_back(v); 

		v.p = D3DXVECTOR3(0, 2, 0);
		v.t = D3DXVECTOR2(0, 0.25);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(2, 2, 0);
		v.t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex.push_back(v);
	}

	Set_Light();

	SetUp_Obj();

	cAseLoader aseLoder;
	m_pRootFrame = aseLoder.Load("woman/woman_01_all.ASE");

	// SetUp_MeshObj();
	// 
	// SetUp_PickingObj();
	// 
	SetUp_HeightMap();

	m_pSkinnedMesh = new CSkinnedMesh;
	m_pSkinnedMesh->SetUp("xFile/Zealot", "zealot.x");

	SetUp_Frustum();

	// >> OBB
	SetUp_OBB();
	// << OBB

	Create_Font();

	SetUp_UI();

	SetUp_Particle();

	Setup_MultiTexture();

	LoadAssets();
}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update(); 

	// if (m_pCubeMan)
	// 	m_pCubeMan->Update(m_pMap); 
	
	if (m_pFrustum)
		m_pFrustum->Update();

	if (m_pCamera)
		m_pCamera->Update(); 

	//for (int i = 0; i < m_vecLight.size(); i++)
	//	m_vecLight[i]->Update();

	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);

	// if (GetKeyState('5') & 0x8000)
	// 	m_pSkinnedMesh->SetAnimationIndexBlend(3);
	// 
	g_pTimeManager->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	// >> OBB
	g_pTimeManager->Update();
	if (m_pHoldZealot)
		m_pHoldZealot->Update(m_pMap);

	if (m_pMoveZealot)
		m_pMoveZealot->Update(m_pMap);
	// << OBB

	Update_Particle();

	Update_MultiTexture();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112) , 
		1.0F, 0);

	g_pD3DDevice->BeginScene();

	Render_Txt();
	// PickingObj_Render();

	if (m_pGrid)
		m_pGrid->Render(); 

	//Render_OBB();

	// Render_Frustum();

	// if (m_pCubePC)
	//	m_pCubePC->Render(); 

	if (m_pMap)
		m_pMap->Render();

	// if (m_pCubeMan)
	// 	m_pCubeMan->Render(); 

	Render_SkinnedMesh();

	// for (int i = 0; i < m_vecLight.size(); i++)
	// 	m_vecLight[i]->Render();

	// Render_Obj();

	// Draw_Texture(); 

	// if (m_pRootFrame)
	// 	m_pRootFrame->Render();

	// Render_MeshObj();

	// Render_UI();
	// 맨 마지막에 그릴 것

	Render_Particle();

	//Render_MultiTexture();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam); 

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			CRay r = CRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			for (int i = 0; i < m_vecSphere.size(); i++)
			{
				m_vecSphere[i].isPicked = r.IsPicked(&m_vecSphere[i]);
				// 라인이 있는 모든것이 선택되는 단점이 있음
			}
		}
		break;

	case WM_RBUTTONDOWN:
		{
			// >> frustum
			// for each(ST_SPHERE* sphere in m_vecCullingSphere)
			// {
			// 	if (m_pFrustum->IsIn(sphere))
			// 		sphere->isPicked = true;
			// 	else
			// 		sphere->isPicked = false;
			// }

		// >> Added
		vector<bool> vecIsIn;
		iMap* m_heightMap = m_pMap;
		vector<D3DXVECTOR3> tempVec = m_heightMap->GetVecVertex();
		int maxSize = m_heightMap->GetVecVertex().size();
		for (int i = 0; i < maxSize; i++)
		{
			if (m_pFrustum->IsInFrustum(tempVec[i]))
				vecIsIn.push_back(true);
			else
				vecIsIn.push_back(false);
		}
		m_heightMap->SetFrustumMap(vecIsIn);
			// << frustum

			// << 애니메이션
			//static int n = 0;
			// m_pSkinnedMesh->SetAnimationIndex(++n);
			//m_pSkinnedMesh->SetAnimationIndexBlend(++n);
			// >> 애니메이션

			// CRay r = CRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			// 
			// for (int i = 0; i < m_vecPlanVertex.size(); i+=3)
			// {
			// 	D3DXVECTOR3 v(0, 0, 0);
			// 	if (r.IntersectTri(m_vecPlanVertex[i + 0].p, m_vecPlanVertex[i + 1].p, m_vecPlanVertex[i + 2].p, v))
			// 	{
			// 		m_vPickedPosition = v;
			// 	}
			// }
		}
		break;

	default:
		break;
	}
}

void cMainGame::Set_Light()
{
	m_directLight = new DirectionLight;
	m_vecLight.push_back(m_directLight);

	m_SpotLight = new SpotLight;
	m_vecLight.push_back(m_SpotLight);

	m_PointLight = new PointLight;
	m_vecLight.push_back(m_PointLight);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); 

	D3DXMATRIXA16 matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, m_pTexture); 
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX)); 
	g_pD3DDevice->SetTexture(0, NULL); 
}

void cMainGame::SetUp_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");

	Load_Surface();
}

void cMainGame::Render_Obj()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->LightEnable(1, false);
	g_pD3DDevice->LightEnable(2, false);

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	// m_vecGroup[0]->Render();
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}

	// todo : 과제!
	//		  맵 로드 & 캐릭터 바닥 체크
	// D3DXIntersectTri()
	/*
	D3DXIntersectTri(v1, v2, v3, rayPos, rayDir, u, v, f);
	// v1, v2, v3 : 폴리곤 정점(바닥 surface)
	// rayPos : 광선 시작점
	// rayDir : 광선 진행 방향
	// (캐릭터 위치, 건물 높이 등, 캐릭터 위치)
	// u, v 지금 당장 필요 x
	// f : 충돌이 있을 때 값
	*/
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;

	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::SetUp_MeshObj()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeaPot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlTeaPot,sizeof(D3DMATERIAL9));
	m_stMtlTeaPot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeaPot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeaPot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	// ================================================================

	cObjLoader loader;
	m_pObjMesh = loader.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");

}

void cMainGame::Render_MeshObj()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR); 
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 0, 1, 10);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		g_pD3DDevice->SetMaterial(&m_stMtlTeaPot);
		m_pMeshTeaPot->DrawSubset(0);	// attribute 1개
	}

	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 1, 1, 0);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);	// attribute 1개
	}
	// ================================================================
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());

			m_pObjMesh->DrawSubset(i);
		}
	}
}

void cMainGame::SetUp_PickingObj()
{
	for (int i = 0; i <= 10; i++)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i);
		m_vecSphere.push_back(s);
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient =  D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse =  D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient =  D3DXCOLOR(0.0f, 0.0f, 0.7f, 1.0f);
	m_stMtlPicked.Diffuse =  D3DXCOLOR(0.0f, 0.0f, 0.7f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.0f, 0.0f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient =  D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse =  D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	
	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);	
	v.p = D3DXVECTOR3(-10,  0, -10);	m_vecPlanVertex.push_back(v);
	v.p = D3DXVECTOR3(-10,  0,  10);	m_vecPlanVertex.push_back(v);
	v.p = D3DXVECTOR3( 10,  0,  10);	m_vecPlanVertex.push_back(v);

	v.p = D3DXVECTOR3(-10, 0, -10);	m_vecPlanVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0,  10);	m_vecPlanVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0, -10);	m_vecPlanVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	g_pD3DDevice->LightEnable(1, false);
	g_pD3DDevice->LightEnable(2, false);

	// >> plane
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecPlanVertex[0], sizeof(ST_PN_VERTEX));
	// << plane

	// >> Sphere
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ? &m_stMtlPicked : &m_stMtlNone);

		m_pMeshSphere->DrawSubset(0);
	}
	// << Sphere

	// >> 선택된 위치 표시용
	g_pD3DDevice->SetMaterial(&m_stMtlPicked);	
	D3DXMatrixTranslation(&matWorld, m_vPickedPosition.x, m_vPickedPosition.y, m_vPickedPosition.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pMeshSphere->DrawSubset(0);
	// << 선택된 위치 표시용
}

void cMainGame::SetUp_HeightMap()
{
	CHeigthMap* pMap = new CHeigthMap;
	pMap->SetUp("HeightMapData/", "HeightMap.raw", "terrain.jpg");
	m_pMap = pMap;
}

void cMainGame::Render_SkinnedMesh()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pShader)
	{
		D3DXMATRIXA16 matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		m_pShader->SetMatrix("gWorldMatrix", &matWorld);
		m_pShader->SetMatrix("gViewMatrix", &matView);
		m_pShader->SetMatrix("gProjectionMatrix", &matProj);

		D3DXCOLOR color(0.2f, 0.5f, 0.5f, 0.0f);
		m_pShader->SetValue("gColor", &color, sizeof(D3DXVECTOR4));

		UINT numPasses = 0;
		m_pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				m_pShader->BeginPass(i); // 구체를 그린다

				if (m_pSkinnedMesh)
					m_pSkinnedMesh->Render(NULL);

				m_pShader->EndPass();
			}
		}
		m_pShader->End();
	}
	else
	{
		if (m_pSkinnedMesh)
			m_pSkinnedMesh->Render(NULL);
	}
}

void cMainGame::SetUp_Frustum()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pSphere, NULL);

	for (int i = -20; i <= 20; i++)
	{
		for (int j = -20; j <= 20; j++)
		{
			for (int k = -20; k <= 20; k++)
			{
				ST_SPHERE* s = new ST_SPHERE;
				s->fRadius = 0.5f;
				s->vCenter = D3DXVECTOR3((float)i, (float)j, (float)k);
				s->isPicked = true;

				m_vecCullingSphere.push_back(s);
			} // : for_k

		} // : for_j

	} // : for_i

	ZeroMemory(&m_stCullingMtl, sizeof(D3DMATERIAL9));
	m_stCullingMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
	m_stCullingMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
	m_stCullingMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);

	m_pFrustum = new CFrustum;
	m_pFrustum->SetUp();
}

void cMainGame::Render_Frustum()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	for each(ST_SPHERE* sphere in m_vecCullingSphere)
	{
		if (sphere->isPicked)
		{
			D3DXMatrixIdentity(&matWorld);
			matWorld._41 = sphere->vCenter.x;
			matWorld._42 = sphere->vCenter.y;
			matWorld._43 = sphere->vCenter.z;

			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDevice->SetMaterial(&m_stCullingMtl);
			m_pSphere->DrawSubset(0);
		}
	}
}

void cMainGame::SetUp_OBB()
{
	m_pHoldZealot = new CZealot;
	m_pHoldZealot->SetUp();

	m_pMoveZealot = new CZealot;
	m_pMoveZealot->SetUp();

	cCharacter* pCharacter = new cCharacter;
	m_pMoveZealot->SetCharacterController(pCharacter);	// 캐릭터 이동
	SafeRelease(pCharacter);
}

void cMainGame::Render_OBB()
{
	D3DCOLOR c = COBB::IsCollision(m_pHoldZealot->GetOBB(), m_pMoveZealot->GetOBB())
		? D3DCOLOR_XRGB(255,0,0) : D3DCOLOR_XRGB(255, 255, 255); // 충돌시 색상 변경

	if (m_pHoldZealot)
		m_pHoldZealot->Render(c);

	if (m_pMoveZealot)
		m_pMoveZealot->Render(c);
}

void cMainGame::Create_Font()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;	// 외곽선 관련인듯?
	fd.PitchAndFamily = FF_DONTCARE;

	// wcscpy_s(fd.FaceName, L"굴림체");
	// 시스템 폰트 사용

	// AddFontResource(L"font/umberto.ttf");
	AddFontResourceA("font/umberto.ttf");
	wcscpy_s(fd.FaceName, L"umberto");
	// 텍스트가 깨질 경우 이미지 출력하는 방법으로(글자와 이미지 대치)
	// 외부 폰트 사용

	// >> 3dFont
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWidth = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;

	wcscpy_s(lf.lfFaceName, L"umberto");

	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateTextA(g_pD3DDevice, hdc, "Direct3D", 0.001f, 0.01f, &m_p3DText, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
	// << 3dFont
	// 무거워서 UI는 사용 안하는 것이 좋음(단, 캐릭터 위 아이디 등..? => 부하 생길 수 있음)
	// 오브젝트 처럼 사용 할 수 있음

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cMainGame::Render_Txt()
{
	string sText("ABC 123 !@# 가나다");

	RECT rc;
	SetRect(&rc, 100, 100, 300, 300);

	LPD3DXFONT pFont = g_pFontManager->GetFont(CFontManager::E_DEFAULT);

	// m_pFont->DrawTextA(NULL, sText.c_str(), sText.length(), 
	// 	&rc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));
	// >> 문자 출력

	m_pFont = pFont;
	m_pFont->DrawTextA(NULL, sText.c_str(), sText.length(),
		&rc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));


	// >> 3dFont
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
	D3DXMatrixTranslation(&matT, -2.0f, 1.0f, 0.0f);

	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_p3DText->DrawSubset(0);
	// << 3dFont
}

void cMainGame::SetUp_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	// m_pTextureUI = g_pTextureManager->GetTexture("UI/test2.png");
	// UI는 이런식 로드 X

	D3DXCreateTextureFromFileExA(
		g_pD3DDevice,
		"UI/test2.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImgInfo,
		NULL,
		&m_pTextureUI
	);
}

void cMainGame::Render_UI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0, m_stImgInfo.Width, m_stImgInfo.Height);

	D3DXMATRIXA16 matS, matR, matT, matWorld;
	D3DXMatrixTranslation(&matT, 5, 5, 0);

	static float fAngle = 0.0f;
	fAngle += 0.01f;
	D3DXMatrixRotationZ(&matR, fAngle);

	matWorld = matR * matT;
	m_pSprite->SetTransform(&matWorld);

	m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(150, 255, 255, 255));

	m_pSprite->End();
}

void cMainGame::SetUp_Particle()
{
	m_vecVertexParticle.resize(1000);
	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		float fRadius = rand() % 100 / 10.0f;
		// 0 ~ 10 사이 소수?

		m_vecVertexParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f));

		D3DXMATRIX matRx, matRy, matRz, matWorld;
		D3DXMatrixRotationX(&matRx, vAngle.x);
		D3DXMatrixRotationY(&matRy, vAngle.y);
		D3DXMatrixRotationZ(&matRz, vAngle.z);
		matWorld = matRx * matRy * matRz;

		D3DXVec3TransformCoord(
			&m_vecVertexParticle[i].p,
			&m_vecVertexParticle[i].p,
			&matWorld);

		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(255, 180, 70, 20);
	}
}

void cMainGame::Update_Particle()
{
	static int nAlpha = 0;
	static int nDelta = 4;

	nAlpha += nDelta;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}
	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		if (i % 2)
			continue;

		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(nAlpha, 180, 70, 20);
	}
}

void cMainGame::Render_Particle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true); // 확대 가능 여부
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(5.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));
	// c만 1.0 ~ 10.0 사이로 변경해 보기

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true); // 포인터에 텍스쳐 적용
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(100.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // MODULATE : 조절하다
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);	// 1번 위치 색상
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// >> draw
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("shader/alpha_tex.tga"));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, m_vecVertexParticle.size(), 
		&m_vecVertexParticle[0], sizeof(ST_PC_VERTEX));
	// << draw

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

void cMainGame::Setup_MultiTexture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"multiTexture/stones.png", &m_pTex0);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"multiTexture/env0.png", &m_pTex1);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"multiTexture/env1.png", &m_pTex2);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"multiTexture/Albedo00.jpg", &m_pTex3);

	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0); v.t = D3DXVECTOR2(0, 1); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0); v.t = D3DXVECTOR2(1, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
}

void cMainGame::Update_MultiTexture()
{
	if (::GetAsyncKeyState('1') & 0x8000) m_nType = 1;
	if (::GetAsyncKeyState('2') & 0x8000) m_nType = 2;
	if (::GetAsyncKeyState('3') & 0x8000) m_nType = 3;
	if (::GetAsyncKeyState('4') & 0x8000) m_nType = 4;
	if (::GetAsyncKeyState('5') & 0x8000) m_nType = 5;
	if (::GetAsyncKeyState('6') & 0x8000) m_nType = 6;
	if (::GetAsyncKeyState('7') & 0x8000) m_nType = 7;
	if (::GetAsyncKeyState('8') & 0x8000) m_nType = 8;
	if (::GetAsyncKeyState('9') & 0x8000) m_nType = 9;
	if (::GetAsyncKeyState('0') & 0x8000) m_nType = 0;
	if (::GetAsyncKeyState('R') & 0x8000) m_nType = -1;
}

void cMainGame::Render_MultiTexture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int i = 0; i <4; i++)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);

	switch (m_nType)
	{
	case 1:	Render_MultiTexture1(); break;
	case 2:	Render_MultiTexture2(); break;
	case 3:	Render_MultiTexture3(); break;
	case 4:	Render_MultiTexture4(); break;
	case 5:	Render_MultiTexture5(); break;
	case 6:	Render_MultiTexture6(); break;
	case 7:	Render_MultiTexture7(); break;
	case 8:	Render_MultiTexture8(); break;
	case 9:	Render_MultiTexture9(); break;
	case 0:	Render_MultiTexture0(); break;
	default: Render_MultiTexture_default(); break;
	}

	SetBillBoard();

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multi.size() / 3,
		&m_vecVertex_Multi[0],
		sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTexture(1, NULL);
	g_pD3DDevice->SetTexture(2, NULL);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);

	for (int i = 0; i < 4; ++i)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
}

void cMainGame::Render_MultiTexture1()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture2()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture3()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE4X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture4()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture5()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture6()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture7()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED2X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture8()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSMOOTH);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture9()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex2);
	g_pD3DDevice->SetTexture(2, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);

	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture0()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex2);
	g_pD3DDevice->SetTexture(2, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_LERP);

	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Render_MultiTexture_default()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

bool cMainGame::LoadAssets()
{
	// 셰이더 로딩
	m_pShader = LoadShader("shader/textureMapping.fx");
	if (!m_pShader)
		return false;

	return true;
}

LPD3DXEFFECT cMainGame::LoadShader(const char * filename)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_pD3DDevice, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		// if (ack)
		// {
		// 	char* str = new char[size];
		// 	sprintf(str, (const char*)ack, size);
		// 	OutputDebugString(str);
		// 	delete[] str;
		// }
	}

	return ret;
}

void SetBillBoard()
{
	D3DXMATRIXA16 matBillBoard, matView;
	D3DXMatrixIdentity(&matBillBoard);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	// view 매트릭스를 구해서 y축 회전
	matBillBoard._11 = matView._11;
	matBillBoard._13 = matView._13;
	matBillBoard._31 = matView._31;
	matBillBoard._33 = matView._33;

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 1, 0, 0);
	matBillBoard *= matT;

	D3DXMatrixInverse(&matBillBoard, NULL, &matBillBoard);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matBillBoard);
}