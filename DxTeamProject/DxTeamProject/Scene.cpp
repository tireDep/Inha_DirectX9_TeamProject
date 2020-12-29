#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
	movep = 0;
	movepy = 0;
	m_strName = "Scene";
	OnButton = false;
	PickButton = false;
}


CScene::~CScene()
{
}

void CScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	GetClientRect(g_hWnd, &imageRC);
	//main
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/Main.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo5, NULL, &m_pTextureScene5);

	//start
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/New.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo, NULL, &m_pTextureScene);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/OnNew.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_onImageInfo, NULL, &m_pOnTexture);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/PickNew.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_onImageInfo2, NULL, &m_pOnTexture2);

	//continue
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/continue.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo4, NULL, &m_pTextureScene4);

	//backG
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/Back.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo2, NULL, &m_pTextureScene2);

	//end
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/end.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo3, NULL, &m_pTextureScene3);

	//exit
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/EXIT.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo6, NULL, &m_pTextureScene6);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/loading.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stLoading, NULL, &m_pLoading);
}

void CScene::Render_Main()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//BackG
	SetRect(&Backrc, 0, 0, m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureScene2, &Backrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//Main
	SetRect(&Mainrc, -405, -140, m_stImageInfo5.Width, m_stImageInfo5.Height);

	m_pSprite->Draw(m_pTextureScene5, &Mainrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//start

	if (OnButton)
	{
		SetRect(&OnNewrc, -575, -485, m_onImageInfo.Width, m_onImageInfo.Height);

		m_pSprite->Draw(m_pOnTexture, &OnNewrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(g_pGameManager->GetNowScene() == SceneType::eMainScene)
	{
		SetRect(&Startrc, -575, -485, m_stImageInfo.Width, m_stImageInfo.Height);

		m_pSprite->Draw(m_pTextureScene, &Startrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (PickButton)
	{
		SetRect(&PickNewrc, -575, -485, m_onImageInfo2.Width, m_onImageInfo2.Height);

		m_pSprite->Draw(m_pOnTexture2, &PickNewrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//continue

	SetRect(&BigStartrc, -575, -565, m_stImageInfo4.Width, m_stImageInfo4.Height);

	m_pSprite->Draw(m_pTextureScene4, &BigStartrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//exit

	SetRect(&Exitrc, -570, -655, m_stImageInfo6.Width, m_stImageInfo6.Height);

	m_pSprite->Draw(m_pTextureScene6, &Exitrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	

	m_pSprite->End();
}

void CScene::Render_Ending()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//BackG
	SetRect(&Backrc, 0, 0, m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureScene2, &Backrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));


	//End
	SetRect(&Endrc, -50, -50, m_stImageInfo3.Width, m_stImageInfo3.Height);

	m_pSprite->Draw(m_pTextureScene3, &Endrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void CScene::Render_Loading()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	SetRect(&loadrc, 0, 0, m_stLoading.Width, m_stLoading.Height);
	m_pSprite->Draw(m_pLoading, &loadrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();

}

void CScene::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eInputEvent)
	{
		switch(eventMsg.message)
		{
		case WM_LBUTTONDOWN:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);

			if (px.x > 610 && px.x < 870 && px.y >505 && px.y < 540 
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				//새로하기
				PickButton = true;
				g_pSoundManager->PlaySFX("button");
			}

			if (px.x > 610 && px.x < 860 && px.y >570 && px.y < 605 
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				//이어하기
				PickButton = true;
				g_pSoundManager->PlaySFX("button");
			}

			if (px.x > 585 && px.x < 850 && px.y > 665 && px.y < 700
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				//끝내기
				PickButton = true;
				g_pSoundManager->PlaySFX("button");
				exit(0);

			}
			break;

		case WM_LBUTTONUP:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);

			if (px.x > 610 && px.x < 870 && px.y >505 && px.y < 540
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				//새로하기
				g_pGameManager->SetNowScene(SceneType::eLoadStart);
				g_pObjectManager->KeepGoing = false;
			}

			if (px.x > 610 && px.x < 860 && px.y >570 && px.y < 605
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				//이어하기
				g_pGameManager->SetNowScene(SceneType::eLoadStart);

				g_pObjectManager->KeepGoing = true; 
			}
			break;

		case WM_MOUSEMOVE:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);

			if (px.x > 610 && px.x < 870 && px.y >505 && px.y < 540
				&& g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				OnButton = true;
			}
			else OnButton = false;

			break;
		}
	}
}

string CScene::GetName()
{
	return m_strName;
}
