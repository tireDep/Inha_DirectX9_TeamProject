#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
	movep = 0;
	movepy = 0;
	m_strName = "Scene";
}


CScene::~CScene()
{
}

void CScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	GetClientRect(g_hWnd, &imageRC);

	//start
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/start.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo, NULL, &m_pTextureScene);

	//BigStart
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/black_script_1.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo4, NULL, &m_pTextureScene4);

	//backG2
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Scene/back.png",
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
}

void CScene::Render_Main()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND); // | D3DXSPRITE_SORT_TEXTURE

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//BackG
	SetRect(&Backrc, 0, 0, m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureScene2, &Backrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//start
	SetRect(&Startrc, -250, -100, m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pTextureScene, &Startrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//BigStart

	//SetRect(&BigStartrc, -250, -100, m_stImageInfo4.Width, m_stImageInfo4.Height);

	//m_pSprite->Draw(m_pTextureScene4, &BigStartrc,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));
	

	m_pSprite->End();
}

void CScene::Render_Ending()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND); // | D3DXSPRITE_SORT_TEXTURE

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

void CScene::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eInputEvent)
	{
		switch(eventMsg.message)
		{
		case WM_LBUTTONDOWN:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);
			if (px.x > 411 && px.x < 1076 && px.y >330 && px.y < 574 && g_pGameManager->GetNowScene() == SceneType::eMainScene)
			{
				g_pGameManager->SetNowScene(SceneType::eLoadStart);
				ShowCursor(false);
			}
			break;
		case WM_MOUSEMOVE:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);
			//cout << "x : "<<px.x << endl;
			//cout << "y : "<<px.y << endl;

		break;
		}
	}
}

string CScene::GetName()
{
	return m_strName;
}
