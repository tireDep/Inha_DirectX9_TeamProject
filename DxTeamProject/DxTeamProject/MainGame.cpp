#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "Orb.h"
#include "Ray.h"
#include "Light.h"
#include "GridMap.h"
#include "PSphere.h"
#include "PSBox.h"
#include "PSCylinder.h"
#include "TestAngleSet.h"
#include "SkinnedMesh.h"
#include "Skydome.h"
/// �� �Ʒ��� ���� ���� �ִ� ����
#include "CHeight.h"
// Ray y check
#include "MeshTile.h"
#include "OBB.h"
#include "Tile.h"
//Gimmick
#include "Colorchanger.h"
#include "Door.h"
#include "BreakableWall.h"
#include "RotationBoard.h"
#include "Switch.h"

#include "PObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "PSOBB.h"

#include "Book.h"
#include "Dragon.h"

#include "MovingCube.h"
/// ������ ������ ���� �ּ�ó��
//#include "SoundManager.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_pOrb(NULL),
	// m_GridMap(NULL),
	/// �� �Ʒ��� ���� ���� �ִ� ����
	m_pSkydome(NULL),
	m_pHeightMap(NULL),
	// Ray y check
	m_pMeshTile(NULL),
	// Gimmick
	m_pGimmick_RotationBoard(NULL),
	m_pGimmick_Switch(NULL),
	//
	m_pBook(NULL),
	m_pDragon(NULL)
	/// ������ ������ ���� �ּ�ó��
	//m_pSm(NULL),
{
	m_pGimmick_Door[0] = NULL;
	m_pGimmick_Door[1] = NULL;
	m_pGimmick_BreakableWall[0] = NULL;
	m_pGimmick_BreakableWall[1] = NULL;
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	SafeDelete(m_pLight);
	SafeDelete(m_pSkydome);
	// Gimmick
	SafeDelete(m_pGimmick_Door[0]);
	SafeDelete(m_pGimmick_Door[1]);
	SafeDelete(m_pGimmick_RotationBoard);
	SafeDelete(m_pGimmick_Switch);
	SafeDelete(m_pGimmick_BreakableWall[0]);
	SafeDelete(m_pGimmick_BreakableWall[1]);
	//
	SafeDelete(m_pBook);
	SafeDelete(m_pDragon);

	g_pFileLoadManager->Destroy();
	
	/// �� �Ʒ��� ���� ���� �ִ� ����
	SafeDelete(m_pHeightMap);

	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	// Ray y check
	
	/// ������ ������ ���� �ּ�ó��
	//SafeDelete(m_pSm);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ST_EVENT eventMsg;
	eventMsg.eventType = EventType::eInputEvent;
	eventMsg.message = message;
	eventMsg.wParam = wParam;
	eventMsg.lParam = lParam;

	g_pEventManager->CheckEvent(eventMsg);
	DefWindowProc(hWnd, message, wParam, lParam);
}

void CMainGame::Setup()
{

	 //g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "123456.dat");

#ifdef _DEBUG
	 g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "Gtest.dat");
	// >> mapData
#else
	g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "mapData.dat");
#endif // DEBUG
	
	m_pGrid = new CGrid;
	m_pGrid->Setup(30, 1.0f);

	m_pCharacter = new CCharacter;
	m_pCharacter->Setup();
	
	m_pText = new CText;
	m_pText->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCharacter->GetPosition());

	m_pMovingCube = new MovingCube;
	m_pMovingCube->Setup("Resource/XFile/Gimmick/MovingCube", "moving_cube.X");
	//m_pOrb = new COrb;
	//m_pOrb->Setup();

	m_pLight = new CLight;
	m_pLight->Setup();
	//m_pLight->Setup(D3DXVECTOR3(1, 0, 0)); // sun light vector

	// m_pPrevFrustum.Setup();
	// m_pNowFrustum.Setup();

	//m_pSkydome = new CSkydome;
	//m_pSkydome->Setup("Resource/XFile/Sky", "skydome.X");

	////--Gimmick
	m_pChanger = new Color_changer;
	m_pChanger->Setup("Resource/XFile/Gimmick/ColorChanger", "Color_changer.X"); //Resource/XFile/Gimmick/ColorChanger", "Color_changer.X

	
	m_pGimmick_Door[0] = new CDoor;
	m_pGimmick_Door[0]->Setup("Resource/XFile/Gimmick/Door", "door_frame.X");
	m_pGimmick_Door[1] = new CDoor;
	m_pGimmick_Door[1]->Setup("Resource/XFile/Gimmick/Door", "door_right.X");

	// m_pGimmick_RotationBoard = new RotationBoard;
	// m_pGimmick_RotationBoard->Setup("Resource/XFile/Gimmick/RotationBoard", "Rotation_board.X");

	m_pGimmick_Switch = new CSwitch;
	m_pGimmick_Switch->Setup("Resource/XFile/Gimmick/Switch", "Force_switch.X");

	m_pGimmick_BreakableWall[0] = new CBreakableWall;
	m_pGimmick_BreakableWall[0]->Setup("Resource/XFile/Gimmick/BreakableWall", "standard_wall.X");
	m_pGimmick_BreakableWall[1] = new CBreakableWall;
	m_pGimmick_BreakableWall[1]->Setup("Resource/XFile/Gimmick/BreakableWall", "brick.X");


	m_pBook = new CBook;
	m_pBook->Setup();

	m_pDragon = new CDragon;
	m_pDragon->Setup();

	/// �� �Ʒ��� ���� ���� �ִ� ����
	//m_pSphere = new CSphere();
	//m_pSphere->Setup();
	//m_pBox = new CBox();
	//m_pBox->Setup();

	g_pEventManager->AddListener(g_gameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}

	// Ray y check

	for (int i = 0; i < 8; ++i)
	{
		m_pMeshTile.push_back(new MeshTile);
	
	}
	m_pMeshTile[0]->Setup(0, 1.5, 10);
	m_pMeshTile[1]->Setup(0, 1.5, -10);
	m_pMeshTile[2]->Setup(10, 1.5, 0);
	m_pMeshTile[3]->Setup(-10, 1.5, 0);
	m_pMeshTile[4]->Setup(10, 1.5, -10);
	m_pMeshTile[5]->Setup(-10, 1.5, 10);
	m_pMeshTile[6]->Setup(10, 1.5, 10);
	m_pMeshTile[7]->Setup(-10, 1.5, -10);
	//m_pMeshTile = new MeshTile;
	//m_pMeshTile->Setup();


	/// ������ ������ ���� �ּ�ó��
	//m_pSm = new CSoundManager;
	//m_pSm->init();
}

void CMainGame::Update()
{
	g_pTimeManager->Update();
	g_pEventManager->Update();

	if (m_pCamera)
		m_pCamera->Update();


	//if(m_pOrb)
	//	m_pOrb->Update();

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection());
		//m_pCharacter->Update(m_pCamera->GetCameraDirection(), m_pHeightMap);	// heightmap... change
		switch (m_pUI->GetPickColor())
		{
		case Pick::Red:
			m_pCharacter->SetColor(RED);
			m_pDragon->Update(RED);
			m_pUI->SetPickColor();
			break;
		case Pick::Yellow:
			m_pCharacter->SetColor(YELLOW);
			m_pDragon->Update(YELLOW);
			m_pUI->SetPickColor();
			break;
		case Pick::Green:
			m_pCharacter->SetColor(GREEN);
			m_pDragon->Update(GREEN);
			m_pUI->SetPickColor();
			break;
		case Pick::Blue:
			m_pCharacter->SetColor(BLUE);
			m_pDragon->Update(BLUE);
			m_pUI->SetPickColor();
			break;
		case Pick::Black:
			m_pCharacter->SetColor(BLACK);
			m_pDragon->Update(BLACK);
			m_pUI->SetPickColor();
			break;
		case Pick::White:
			m_pCharacter->SetColor(WHITE);
			m_pDragon->Update(WHITE);
			m_pUI->SetPickColor();
			break;
		default:
			break;
		}
		// grab
		if (m_pCharacter->Update(g_pObjectManager->GetVecPObejct()) != -1)
		{
			m_pText->SetisGrabstate(true);
			D3DXVECTOR3 v;
			v = g_pObjectManager->GetVecPObejct()[m_pCharacter->Update(g_pObjectManager->GetVecPObejct())]->GetPosition() - m_pCharacter->GetPosition();
			v.y -= 0.5f;
			//v.x = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().x - m_pCharacter->GetPosition().x;
			//v.y = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().y - m_pCharacter->GetPosition().y - 0.5f;
			//v.z = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().z - m_pCharacter->GetPosition().z;
			D3DXVec3Normalize(&v, &v);
			g_pObjectManager->GetVecPObejct()[m_pCharacter->Update(g_pObjectManager->GetVecPObejct())]->SetPusingForce(v);
		}
		else
		{
			m_pText->SetisGrabstate(false);
		}
		// Ray y check
		/*m_pCharacter->UpdateRayYCheck(*m_pMeshTile);*/
	}

	 //if (g_gameManager->GetGridMapMode())
	 //{
	 //	m_pPrevFrustum = m_pNowFrustum;
	 //	m_pNowFrustum.Update();
	 //	if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum))
	 //	{
	 //		m_GridMap->CalcNewMap(&m_pNowFrustum);
	 //	}
	 //}

	if (g_gameManager->GetGridMapMode())
	{
		m_pPrevFrustum = m_pNowFrustum;
		m_pNowFrustum.Update();

		static D3DXVECTOR3 lastPlayerPos = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 tempPos = m_pCharacter->GetPosition();
		float posCheck = 0.5f;

		// >> todo : ���� ����
		if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum) 
		 || fabs(lastPlayerPos.x - tempPos.x) >= posCheck 
		 || fabs(lastPlayerPos.y - tempPos.y) >= posCheck 
		 || fabs(lastPlayerPos.z - tempPos.z) >= posCheck)
		{
			lastPlayerPos = tempPos;
			g_pObjectManager->UpdateNewMap(&m_pNowFrustum);
		}
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	CRay ray = CRay::RayAtWorldSpace(rc.right / 2, rc.bottom / 2);
	g_pObjectManager->Update(ray, m_pCharacter->GetColor());					// Color Change
	g_pObjectManager->UpdateLand(g_pTimeManager->GetElapsedTime());
	g_pObjectManager->Update(g_pTimeManager->GetElapsedTime());
	g_pObjectManager->Update();
	///
	//m_pBox->Update(g_pTimeManager->GetElapsedTime());
	//g_pObjectManager->UpdateLand(g_pTimeManager->GetElapsedTime());					// 2D Physics
	//g_pObjectManager->UpdateCollide(g_pTimeManager->GetElapsedTime());			// new Collision
	//g_pObjectManager->Update();													// Collision
	//g_pObjectManager->Update(g_pTimeManager->GetElapsedTime(), m_pHeightMap);	// 3D Physics

	// Gimmick
	if (m_pGimmick_Door[0])
		m_pGimmick_Door[0]->Update(g_pTimeManager->GetElapsedTime());
	if (m_pGimmick_Door[1])
		m_pGimmick_Door[1]->Update(g_pTimeManager->GetElapsedTime());

	//if (m_pGimmick_RotationBoard)
	//	m_pGimmick_RotationBoard->Update(g_pTimeManager->GetElapsedTime());
	
	if (m_pChanger)
		m_pChanger->Update();

	if (m_pMovingCube)
		m_pMovingCube->Update();

	for(int i =0 ; i < m_pMeshTile.size(); ++i)
	if (m_pMeshTile[i])
		m_pMeshTile[i]->Update();

	for (int i = 0; i < m_pMeshTile.size(); ++i)
	{
		if (COBB::IsCollision(m_pChanger->GetOBB(), m_pMeshTile[i]->GetOBB()) == true)
		{
			
			D3DXVECTOR3 tmp = m_pChanger->GetPos() - m_pMeshTile[i]->GetPos();
			m_pChanger->SetHitLength(D3DXVec3Length(&tmp));
			m_pMeshTile[i]->SetColor(m_pChanger->m_stMtl);

			break;
		}
		else 
		{
	
			m_pChanger->SetHitLength(50);
		
		}
	}
	if (m_pGimmick_BreakableWall[0])
		m_pGimmick_BreakableWall[0]->Update();
	if (m_pGimmick_BreakableWall[1])
		m_pGimmick_BreakableWall[1]->Update();

	if (m_pBook)
		m_pBook->Update(g_pTimeManager->GetElapsedTime());
}

void CMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	//if (m_pSkydome)
	//	m_pSkydome->Render(m_pCamera->GetCameraEye());

	if (m_pGrid)
		m_pGrid->Render();
	

	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);

	if (m_pCharacter)
		m_pCharacter->Render(c);

	//if (m_pOrb)
	//{
	//	m_pOrb->SetBillbord();
	//	m_pOrb->Render();
	//}

	g_pObjectManager->Render();

	//if (m_pHeightMap)
	//	m_pHeightMap->Render();

	if (g_gameManager->GetDevMode())
	{
		if (m_pText)
		{
			m_pText->RenderFPS(g_pTimeManager->GetFPS());
			m_pText->RenderCharacterPosition(m_pCharacter->GetPosition());
			g_pObjectManager->RenderOBBBox();
			//m_pText->RenderBoxPosition(m_pSphere1->getCenter());
			//m_pText->RenderGrab(g_pObjectManager->GetVecObject(), m_pCharacter->GetPosition());
		}
	}

	if (m_pText->GetisGrabstate())
		m_pText->RenderGrab();

	// Ray y check

	if(m_pMovingCube)
		m_pMovingCube->Render();

	for(int i =0; i < m_pMeshTile.size(); ++i)
		m_pMeshTile[i]->Render();

	//if (m_pMeshTile)
	//	m_pMeshTile->Render();

	// Gimmick
	if (m_pGimmick_Door[0])
		m_pGimmick_Door[0]->Render();
	if (m_pGimmick_Door[1])
		m_pGimmick_Door[1]->Render();
	//if (m_pGimmick_RotationBoard)
	//	m_pGimmick_RotationBoard->Render();
	if (m_pGimmick_Switch)
		m_pGimmick_Switch->Render();
	if (m_pChanger)
		m_pChanger->Render();
	if (m_pGimmick_BreakableWall[0])
		m_pGimmick_BreakableWall[0]->Render();
	if (m_pGimmick_BreakableWall[1]) 
		m_pGimmick_BreakableWall[1]->Render();
//

	if (m_pBook)
		m_pBook->Render();

	if (m_pDragon)
		m_pDragon->Render();

	if (g_gameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}