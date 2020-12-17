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
#include "SkinnedMesh.h"
#include "Skydome.h"
#include "PObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "OBB.h"
// Ray y check
#include "MeshTile.h"
#include "Tile.h"
//Gimmick
#include "Colorchanger.h"
#include "Door.h"
#include "BreakableWall.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "MovingCube.h"
#include "Book.h"
#include "Dragon.h"
//
#include "Scene.h"
//
/// 이 아래는 지울 수도 있는 선언
//#include "CHeight.h"
//#include "PSphere.h"
//#include "PSBox.h"
//#include "PSCylinder.h"
//#include "TestAngleSet.h"
//#include "PSOBB.h"
/// 릴리즈 버전을 위한 주석처리
//#include "SoundManager.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_pOrb(NULL),
	// m_GridMap(NULL),
	/// 이 아래는 지울 수도 있는 선언
	m_pSkydome(NULL),
	m_pHeightMap(NULL),
	// Ray y check
	m_pMeshTile(NULL),
	// Gimmick
	//m_pGimmick_RotationBoard(NULL),
	// m_pGimmick_Switch(NULL),
	//
	m_pBook(NULL),
	m_pDragon(NULL),
	m_pScene(NULL)
	/// 릴리즈 버전을 위한 주석처리
	//m_pSm(NULL),
{
	//m_pGimmick_Door[0] = NULL;
	//m_pGimmick_Door[1] = NULL;
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
	//SafeDelete(m_pGimmick_Door[0]);
	//SafeDelete(m_pGimmick_Door[1]);
	//SafeDelete(m_pGimmick_RotationBoard);
	//SafeDelete(m_pGimmick_Switch); // >> 삭제가 오브젝트 매니저 통해서 되므로 메모리 이중삭제 됨
	SafeDelete(m_pGimmick_BreakableWall[0]);
	SafeDelete(m_pGimmick_BreakableWall[1]);
	//
	SafeDelete(m_pBook);
	SafeDelete(m_pDragon);

	g_pFileLoadManager->Destroy();
	
	/// 이 아래는 지울 수도 있는 선언
	SafeDelete(m_pHeightMap);

	SafeDelete(m_pScene);

	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	// Ray y check
	
	/// 릴리즈 버전을 위한 주석처리
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
	g_pGameManager->SetLoadData();

#ifdef _DEBUG
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "conditionTest.dat");
	 g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "CharacterToTile.dat");
	//g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "colorTagTest.dat");

	//g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "conditionTest.dat");
	//g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "BoxToTile.dat");
	//g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "CharacterCollisionTest.dat");
	//g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "colorTagTest.dat");

	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "conditionTest.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "Book.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "PObjectToGimmick.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "mapData.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "Book.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "testBook.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "AllTest_6.0.dat");
	// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "doorTest2.dat");
#else
	g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "mapData.dat");
#endif // DEBUG
	m_pScene = new CScene;
	m_pScene->Setup();

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

	//m_pMovingCube = new MovingCube;
	//m_pMovingCube->Setup();

	m_pLight = new CLight;
	m_pLight->Setup();
	//m_pLight->Setup(D3DXVECTOR3(1, 0, 0)); // sun light vector

	// m_pPrevFrustum.Setup();
	// m_pNowFrustum.Setup();

	//m_pSkydome = new CSkydome;
	//m_pSkydome->Setup("Resource/XFile/Sky", "skydome.X");

	////--Gimmick
	//m_pChanger = new Color_changer;
	//m_pChanger->Setup(); //Resource/XFile/Gimmick/ColorChanger", "Color_changer.X

	//m_pGimmick_Door[0] = new CDoor;
	//m_pGimmick_Door[0]->Setup("Resource/XFile/Gimmick/Door", "door_frame.X");
	//m_pGimmick_Door[1] = new CDoor;
	//m_pGimmick_Door[1]->Setup("Resource/XFile/Gimmick/Door", "door_right.X");

	// m_pGimmick_RotationBoard = new RotationBoard;
	// m_pGimmick_RotationBoard->Setup("Resource/XFile/Gimmick/RotationBoard", "Rotation_board.X");

	/* m_pGimmick_Switch = new CSwitch;
	 m_pGimmick_Switch->Setup();*/

	//m_pGimmick_BreakableWall[0] = new CBreakableWall;
	//m_pGimmick_BreakableWall[0]->Setup("Resource/XFile/Gimmick/BreakableWall", "Pillar.X");
	//m_pGimmick_BreakableWall[1] = new CBreakableWall;
	//m_pGimmick_BreakableWall[1]->Setup("Resource/XFile/Gimmick/BreakableWall", "brick.X");

	//m_pBook = new CBook;
	//m_pBook->Setup();

	m_pDragon = new CDragon;
	m_pDragon->Setup();

	g_pEventManager->AddListener(g_pGameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pDragon);
	g_pEventManager->AddListener(m_pUI);

	for (int i = 0; i < g_pObjectManager->GetVecObject().size(); i++)
	{
		g_pEventManager->AddListener(g_pObjectManager->GetVecObject()[i]);
	}

	// Ray y check

	//for (int i = 0; i < 8; ++i)
	//{
	//	m_pMeshTile.push_back(new MeshTile);
	//
	//}
	//m_pMeshTile[0]->Setup(0, 1.5, 10);
	//m_pMeshTile[1]->Setup(0, 1.5, -10);
	//m_pMeshTile[2]->Setup(10, 1.5, 0);
	//m_pMeshTile[3]->Setup(-10, 1.5, 0);
	//m_pMeshTile[4]->Setup(10, 1.5, -10);
	//m_pMeshTile[5]->Setup(-10, 1.5, 10);
	//m_pMeshTile[6]->Setup(10, 1.5, 10);
	//m_pMeshTile[7]->Setup(-10, 1.5, -10);
	//m_pMeshTile = new MeshTile;
	//m_pMeshTile->Setup();


	/// 릴리즈 버전을 위한 주석처리
	//m_pSm = new CSoundManager;
	//m_pSm->init();
}

void CMainGame::Update()
{
	if (GetKeyState('1') & 0x8000)
	{
		g_pGameManager->SetGetOrb("Blue");
		g_pGameManager->SetGetOrb("Green");
		g_pGameManager->SetGetOrb("Red");
		g_pGameManager->SetGetOrb("White");
		g_pGameManager->SetGetOrb("Yellow");
		g_pGameManager->SetGetOrb("Black");
	}

	g_pGameManager->CompleteOrb();
	// >> 조건 확인 테스트
	// >> on/off 상태 조건 // 텍스쳐 태깅

	g_pTimeManager->Update();

	g_pEventManager->Update(g_pTimeManager->GetElapsedTime());

	if (m_pCamera)
		m_pCamera->Update();

	

	if (m_pCharacter)
	{
		m_pCharacter->Update(m_pCamera->GetCameraDirection());
		m_pCharacter->Update(g_pTimeManager->GetElapsedTime());
		m_pDragon->DirectionSet(m_pCamera->GetCameraDirection());
		m_pDragon->Update(m_pCharacter->GetPosition(), g_pTimeManager->GetElapsedTime());
		//m_pCharacter->Update(m_pCamera->GetCameraDirection(), m_pHeightMap);	// heightmap... change
		//m_pCharacter->ColliderOtherObject(g_pObjectManager->GetVecIObject()[0]);
		//for(int i =0; i < g_pObjectManager->GetVecIObject().size() ;++i)
		//	m_pCharacter->ColliderOtherObject(g_pObjectManager->GetVecIObject()[i]);
		switch (m_pUI->GetPickColor())
		{
		case Pick::Red:
			m_pCharacter->SetColor(RED);
			m_pDragon->ChangeColor(RED);
			m_pUI->SetPickColor();
			break;
		case Pick::Yellow:
			m_pCharacter->SetColor(YELLOW);
			m_pDragon->ChangeColor(YELLOW);
			m_pUI->SetPickColor();
			break;
		case Pick::Green:
			m_pCharacter->SetColor(GREEN);
			m_pDragon->ChangeColor(GREEN);
			m_pUI->SetPickColor();
			break;
		case Pick::Blue:
			m_pCharacter->SetColor(BLUE);
			m_pDragon->ChangeColor(BLUE);
			m_pUI->SetPickColor();
			break;
		case Pick::Black:
			m_pCharacter->SetColor(BLACK);
			m_pDragon->ChangeColor(BLACK);
			m_pUI->SetPickColor();
			break;
		case Pick::White:
			m_pCharacter->SetColor(WHITE);
			m_pDragon->ChangeColor(WHITE);
			m_pUI->SetPickColor();
			break;
		default:
			break;
		}
		// grab
		if (m_pCharacter->GetGrab())
			m_pText->SetisGrabstate(true);
		else
			m_pText->SetisGrabstate(false);
		//if (m_pCharacter->Update(g_pObjectManager->GetVecPObejct(), g_pTimeManager->GetElapsedTime()) != -1)
		//{
		//	m_pText->SetisGrabstate(true);
		//	//D3DXVECTOR3 v;
		//	//v = g_pObjectManager->GetVecPObejct()[m_pCharacter->Update(g_pObjectManager->GetVecPObejct(), g_pTimeManager->GetElapsedTime())]->GetPosition() - m_pCharacter->GetPosition();
		//	//v.y -= 0.5f;
		//	////v.x = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().x - m_pCharacter->GetPosition().x;
		//	////v.y = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().y - m_pCharacter->GetPosition().y - 0.5f;
		//	////v.z = g_pObjectManager->GetVecObject()[m_pCharacter->Update(g_pObjectManager->GetVecObject())]->GetPosition().z - m_pCharacter->GetPosition().z;
		//	//D3DXVec3Normalize(&v, &v);
		//	//g_pObjectManager->GetVecPObejct()[m_pCharacter->Update(g_pObjectManager->GetVecPObejct(), g_pTimeManager->GetElapsedTime())]->SetPusingForce(v);
		//}
		//else
		//{
		//	m_pText->SetisGrabstate(false);
		//}
		// Ray y check
		/*m_pCharacter->UpdateRayYCheck(*m_pMeshTile);*/
	}

	 //if (g_pGameManager->GetGridMapMode())
	 //{
	 //	m_pPrevFrustum = m_pNowFrustum;
	 //	m_pNowFrustum.Update();
	 //	if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum))
	 //	{
	 //		m_GridMap->CalcNewMap(&m_pNowFrustum);
	 //	}
	 //}

	if (g_pGameManager->GetGridMapMode())
	{
		m_pPrevFrustum = m_pNowFrustum;
		m_pNowFrustum.Update();

		static D3DXVECTOR3 lastPlayerPos = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 tempPos = m_pCharacter->GetPosition();
		float posCheck = 0.5f;

		// >> todo : 판정 변경
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
	g_pObjectManager->Update(ray, m_pCharacter->GetColor());		// Color Change
	g_pObjectManager->UpdateLand(g_pTimeManager->GetElapsedTime());	// PObject Physics
	g_pObjectManager->Update(g_pTimeManager->GetElapsedTime());		// IObject(Gimmick) Physics
	g_pObjectManager->Collide(g_pTimeManager->GetElapsedTime());	// Collide
	///
	//m_pBox->Update(g_pTimeManager->GetElapsedTime());
	//g_pObjectManager->UpdateLand(g_pTimeManager->GetElapsedTime());					// 2D Physics
	//g_pObjectManager->UpdateCollide(g_pTimeManager->GetElapsedTime());			// new Collision
	//g_pObjectManager->Update();													// Collision
	//g_pObjectManager->Update(g_pTimeManager->GetElapsedTime(), m_pHeightMap);	// 3D Physics

	// Gimmick
	//if (m_pGimmick_Door[0])
	//	m_pGimmick_Door[0]->Update(g_pTimeManager->GetElapsedTime());
	//if (m_pGimmick_Door[1])
	//	m_pGimmick_Door[1]->Update(g_pTimeManager->GetElapsedTime());

	//if (m_pGimmick_RotationBoard)
	//	m_pGimmick_RotationBoard->Update(g_pTimeManager->GetElapsedTime());
	
	//if (m_pChanger)
	//	m_pChanger->Update();

	/*if (m_pMovingCube)
		m_pMovingCube->Update();*/

	//for(int i =0 ; i < m_pMeshTile.size(); ++i)
	//if (m_pMeshTile[i])
	//	m_pMeshTile[i]->Update();

	//for (int i = 0; i < m_pMeshTile.size(); ++i)
	//{
	//	if (COBB::IsCollision(m_pChanger->m_BeamOBB, m_pMeshTile[i]->GetOBB()) == true)
	//	{
	//		D3DXVECTOR3 tmp = m_pChanger->m_position - m_pMeshTile[i]->GetPos();
	//		m_pChanger->SetHitLength(D3DXVec3Length(&tmp));
	//		m_pMeshTile[i]->SetColor(m_pChanger->m_stMtl);
	//		break;
	//	}
	//	else 
	//	{
	//		m_pChanger->SetHitLength(50);
	//	
	//	}
	//}
	// if (m_pGimmick_Switch)
	// 	m_pGimmick_Switch->Update();
	//// 
	//// 
	// if (COBB::IsCollision(m_pMovingCube->GetOBB(), m_pGimmick_Switch->GetOBB()) == true)
	// {
	//	 cout << 1 << endl;
	// }
	// else
	// {
	//	 cout << 2 << endl;
	// }

	//if (m_pGimmick_BreakableWall[0])
	//	m_pGimmick_BreakableWall[0]->Update();
	//if (m_pGimmick_BreakableWall[1])
	//	m_pGimmick_BreakableWall[1]->Update();

	//if (m_pBook)
	//	m_pBook->Update(g_pTimeManager->GetElapsedTime());
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

	if (g_pGameManager->GetNowScene() == SceneType::eMainScene)
	{
		if (m_pScene)
			m_pScene->Render_Main();
	}

	if (g_pGameManager->GetNowScene() == SceneType::eEndingScene)
	{
		if (m_pScene)
			m_pScene->Render_Ending();
		g_pGameManager->SetClipCursor(-15);
		ShowCursor(true);
	}

	if (m_pGrid)
		m_pGrid->Render();
	
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);

	if (m_pCharacter)
		m_pCharacter->Render(c);

	g_pObjectManager->Render();

	//if (m_pHeightMap)
	//	m_pHeightMap->Render();

	if (g_pGameManager->GetDevMode())
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

	/*if(m_pMovingCube)
		m_pMovingCube->Render();*/

	//for(int i =0; i < m_pMeshTile.size(); ++i)
	//	m_pMeshTile[i]->Render();

	//if (m_pMeshTile)
	//	m_pMeshTile->Render();

	// Gimmick
	//if (m_pGimmick_Door[0])
	//	m_pGimmick_Door[0]->Render();
	//if (m_pGimmick_Door[1])
	//	m_pGimmick_Door[1]->Render();
	//if (m_pGimmick_RotationBoard)
	//	m_pGimmick_RotationBoard->Render();
	/* if (m_pGimmick_Switch)
	 	m_pGimmick_Switch->Render();*/
	//if (m_pChanger)
	//	m_pChanger->Render();

	/*if (m_pChanger)
		m_pChanger->Render();*/
	//if (m_pGimmick_BreakableWall[0])
	//	m_pGimmick_BreakableWall[0]->Render();
	//if (m_pGimmick_BreakableWall[1]) 
	//	m_pGimmick_BreakableWall[1]->Render();
//

	//if (m_pBook)
	//	m_pBook->Render();

	if (m_pDragon)
		m_pDragon->Render();

	if (g_pGameManager->GetUImode())
	{
		if (m_pUI)
			m_pUI->UI_Render();
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}