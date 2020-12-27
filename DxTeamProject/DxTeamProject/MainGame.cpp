#include "stdafx.h"

#include "MainGame.h"
#include "Camera.h"
#include "Grid.h"
#include "UI.h"
#include "Text.h"
#include "Character.h"
#include "Ray.h"
#include "Light.h"
#include "GridMap.h"
#include "Skydome.h"
#include "Dragon.h"
#include "Scene.h"
#include "SoundManager.h"

#include "IObject.h"

CMainGame::CMainGame() :
	m_pCamera(NULL),
	m_pUI(NULL),
	m_pText(NULL),
	m_pCharacter(NULL),
	m_pLight(NULL),
	m_pSkydome(NULL),
	m_pDragon(NULL),
	m_pScene(NULL),
	m_fCheckTime(0.0f)
{
}

CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pUI);
	SafeDelete(m_pText);
	SafeDelete(m_pLight);
	SafeDelete(m_pSkydome);
	SafeDelete(m_pDragon);
	SafeDelete(m_pScene);

	g_pFontManager->Destroy();
	g_pFileLoadManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
	
	/// 릴리즈 버전을 위한 주석처리
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

	m_pScene = new CScene;
	m_pScene->Setup();

	/// Presentation
#ifdef _DEBUG
	m_pGrid = new CGrid;
	m_pGrid->Setup(30, 1.0f);
#endif
	m_pCharacter = new CCharacter;
	m_pCharacter->Setup();
	
	m_pText = new CText;
	m_pText->Setup();

	m_pUI = new CUI;
	m_pUI->Setup_UI();

	m_pCamera = new CCamera;
	m_pCamera->Setup(&m_pCharacter->GetPosition());

	m_pLight = new CLight;
	m_pLight->Setup();

	m_pSkydome = new CSkydome;
	m_pSkydome->Setup("Resource/XFile/Sky", "skydome.X");

	// m_pPrevFrustum.Setup();
	// m_pNowFrustum.Setup();

	m_pDragon = new CDragon;
	m_pDragon->Setup();

	g_pEventManager->AddListener(g_pGameManager);
	g_pEventManager->AddListener(m_pCamera);
	g_pEventManager->AddListener(m_pCharacter);
	g_pEventManager->AddListener(m_pDragon);
	g_pEventManager->AddListener(m_pUI);
	g_pEventManager->AddListener(m_pScene);

	g_pSoundManager->init();
}

void CMainGame::Update()
{
	// >> thread
	// // if (g_pGameManager->GetNowScene() == SceneType::eLoading)
	// {
	// 	if (!g_pFileLoadManager->GetIsThreadRun())
	// 		g_pFileLoadManager->CheckThread();
	// 	//else
	// 	//{
	// 	//	// todo : 초기화 
	// 	//	g_pGameManager->SetNowScene(SceneType::eGameScene);
	// 	//}
	// }

	// >> 임시 로딩창 구현을 위해 로드 위치 이동
	if (g_pGameManager->GetNowScene() == SceneType::eLoading)
	{
		g_pGameManager->SetIsDataLoad(true);

		if (g_pObjectManager->KeepGoing == true)
		{
			m_pCharacter->SaveData(g_pGameManager->SaveData());
			m_pCharacter->SaveSetup();
				
		}

// >> MapData

		/// 1... puzzle side height wall
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map1_puzzle_test.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_puzzle_map1.dat");
		/// 2... puzzle trace orb
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map2_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_puzzle_map2.dat");
		/// 3... bridge
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map3_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map3.dat");
		/// 4... 
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map4_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map4.dat");
		/// 5... 
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map5_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map5.dat");
		/// 6... Tree... Slide...
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map6_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map6.dat");
		/// 7... 
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map7_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_map7.dat");
		/// 8... 
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map8_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map8.dat");
		/// 9... 
		// g_pFileLoadManager->FileLoad_MapData("Resource/MapData/KTMapData", "Autumn_tile_Test_map9_bg.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_bg_map9.dat");
		//g_pFileLoadManager->FileLoad_MapData("Resource/MapData/DesignMapData", "Autumn_tile_map9.dat");

// << MapData
	// todo : set perfect map

		// g_pFileLoadManager->FileLoad_MapData("Resource/MapData", "testMap_orb.dat");

		int size = g_pObjectManager->GetVecObject().size();
		for (int i = 0; i < size; i++)
		{
			g_pEventManager->AddListener(&g_pObjectManager->GetVecObjectIndex(i));
		}

		g_pObjectManager->CalcNowPositionIndex(m_pCharacter->GetPosition());
		g_pGameManager->SetNowScene(SceneType::eGameScene);

	}

	//else if (g_pGameManager->GetNowScene() == SceneType::eGameScene)
	//{
	//	/// Delete Later...
	//	if (GetKeyState('1') & 0x8000)
	//	{
	//		g_pGameManager->SetGetOrb("Blue");
	//		g_pGameManager->SetGetOrb("Green");
	//		g_pGameManager->SetGetOrb("Red");
	//		g_pGameManager->SetGetOrb("White");
	//		g_pGameManager->SetGetOrb("Yellow");
	//		g_pGameManager->SetGetOrb("Black");
	//		// g_pGameManager->CompleteOrb();
	//	}
	//	if (GetKeyState('2') & 0x8000)
	//	{
	//		g_pSoundManager->PlayBGM("f_last");
	//	}
	//	if (GetKeyState('3') & 0x8000)
	//	{
	//		g_pSoundManager->PlayBGM("f_middle");
	//	}
	//}
	if (g_pGameManager->GetNowScene() == SceneType::eGameScene)
	{
		if (g_pGameManager->GetUImode())
			return;

		m_fCheckTime += g_pTimeManager->GetElapsedTime();

		if (m_fCheckTime >= 0.5f)
		{
			m_fCheckTime = 0.0f;
			g_pObjectManager->CalcNowPositionIndex(m_pCharacter->GetPosition());
		}

		g_pTimeManager->Update();
		g_pEventManager->Update(g_pTimeManager->GetElapsedTime());

		RECT rc;
		GetClientRect(g_hWnd, &rc);
		CRay ray = CRay::RayAtWorldSpace(rc.right / 2, rc.bottom / 2);
		g_pObjectManager->Update(ray, m_pCharacter->GetColor());		// Color Change
		g_pObjectManager->UpdateLand(g_pTimeManager->GetElapsedTime());	// PObject Physics
		g_pObjectManager->Update(g_pTimeManager->GetElapsedTime());		// IObject(Gimmick) Physics
		g_pObjectManager->Collide(g_pTimeManager->GetElapsedTime());	// Collide

		if (m_pCamera)
			m_pCamera->Update();

		if (m_pCharacter)
		{
			m_pCharacter->Update(m_pCamera->GetCameraDirection());
			m_pCharacter->Update(g_pTimeManager->GetElapsedTime());
			m_pDragon->DirectionSet(m_pCamera->GetCameraDirection());
			m_pDragon->Update(m_pCharacter->GetPosition(), g_pTimeManager->GetElapsedTime());
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
		}

		//if (g_pGameManager->GetGridMapMode())
		//{
		//	m_pPrevFrustum = m_pNowFrustum;
		//	m_pNowFrustum.Update();
		//	static D3DXVECTOR3 lastPlayerPos = D3DXVECTOR3(0, 0, 0);
		//	D3DXVECTOR3 tempPos = m_pCharacter->GetPosition();
		//	float posCheck = 0.5f;
		//	// >> todo : 판정 변경
		//	if (!m_pNowFrustum.IsUpdateCheck(m_pPrevFrustum)
		//		|| fabs(lastPlayerPos.x - tempPos.x) >= posCheck
		//		|| fabs(lastPlayerPos.y - tempPos.y) >= posCheck
		//		|| fabs(lastPlayerPos.z - tempPos.z) >= posCheck)
		//	{
		//		lastPlayerPos = tempPos;
		//		g_pObjectManager->UpdateNewMap(&m_pNowFrustum);
		//	}
		//}
	}
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

	if (m_pSkydome)
		m_pSkydome->Render(m_pCamera->GetCameraEye());

	if (g_pGameManager->GetNowScene() == SceneType::eMainScene)
	{
		if (m_pScene)
			m_pScene->Render_Main();
	}
	else if (g_pGameManager->GetNowScene() == SceneType::eEndingScene)
	{
		if (m_pScene)
			m_pScene->Render_Ending();
	}
	else if (g_pGameManager->GetNowScene() == SceneType::eLoadStart)
	{		
		if (m_pScene)
			m_pScene->Render_Loading();
		g_pD3DDevice->EndScene();
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
		g_pGameManager->SetNowScene(SceneType::eLoading);
	}
	else
	{
		/// Presentation
#ifdef _DEBUG
		if (m_pGrid)
			m_pGrid->Render();
#endif

		if (m_pCharacter)
			m_pCharacter->Render();

		g_pObjectManager->Render(m_pCamera->GetCameraEye());

		if (g_pGameManager->GetDevMode())
		{
			if (m_pText)
			{
				m_pText->RenderFPS(g_pTimeManager->GetFPS());
				m_pText->RenderCharacterPosition(m_pCharacter->GetPosition());
				g_pObjectManager->RenderOBBBox();
			}
		}

		if (m_pText->GetisGrabstate())
		{
			//m_pText->RenderGrab();
			m_pUI->RenderGrab();
		}

		if (m_pDragon && m_pCamera->GetCameraAngle() >= 0.0f)
			m_pDragon->Render();

		if (g_pGameManager->GetUImode())
		{
			if (m_pUI)
				m_pUI->UI_Render();
		}
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}