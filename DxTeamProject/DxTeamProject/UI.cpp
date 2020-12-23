#include "stdafx.h"
#include "UI.h"
#include "Character.h"



CUI::CUI()
{
	m_isLButtonDown = false;
	OnButton = Color::NONE;
	PickColor = Pick::NONE;
	movep = 0;
	movepy = 0;
	px3 = { 0,0 };
	m_strName = "UI";
}

CUI::~CUI()
{
}

void CUI::Setup_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	GetClientRect(g_hWnd, &UIrc);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/palette.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo, NULL, &m_pTextureUI);

	////BackG
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/back.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo2, NULL, &m_pTextureUI2);

	//Red 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/Bigred.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo3, NULL, &m_pTextureUI3);

	//yellow 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/Bigyellow.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo4, NULL, &m_pTextureUI4);

	//Green 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/Biggreen.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo5, NULL, &m_pTextureUI5);

	//Blue 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/Bigblue.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo6, NULL, &m_pTextureUI6);

	//Black 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/Bigblack.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo7, NULL, &m_pTextureUI7);

	//White 버튼
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/BigWhite.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo8, NULL, &m_pTextureUI8);

	////////////////////////
	///red
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/red.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo, NULL, &m_SmallUI);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/yellow.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo2, NULL, &m_SmallUI2);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/green.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo3, NULL, &m_SmallUI3);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/blue.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo4, NULL, &m_SmallUI4);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/black.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo5, NULL, &m_SmallUI5);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/white.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_smallInfo6, NULL, &m_SmallUI6);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/message.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_textInfo, NULL, &m_textUI);
	//////////////////////////////////

	//겨울
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Mapname/winter.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_textInfo2, NULL, &m_textUI2);

	//가을
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Mapname/fall.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_textInfo3, NULL, &m_textUI3);
}

void CUI::UI_Render()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND); // | D3DXSPRITE_SORT_TEXTURE

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//BackG

	SetRect(&Backrc, 0,0,
		m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureUI2, &Backrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(150, 255, 255, 255));


	///red
	if (g_pGameManager->GetIsHasOrb("Red"))
	{
		SetRect(&s_Redrc, -638, -239,
			m_smallInfo.Width, m_smallInfo.Height);

		m_pSprite->Draw(m_SmallUI, &s_Redrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
	///yellow
	if (g_pGameManager->GetIsHasOrb("Yellow"))
	{
		SetRect(&s_Yellowrc, -558, -209,
			m_smallInfo2.Width, m_smallInfo2.Height);

		m_pSprite->Draw(m_SmallUI2, &s_Yellowrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	///green
	if (g_pGameManager->GetIsHasOrb("Green"))
	{
		SetRect(&s_Greenrc, -585, -154,
			m_smallInfo3.Width, m_smallInfo3.Height);

		m_pSprite->Draw(m_SmallUI3, &s_Greenrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	///blue
	if (g_pGameManager->GetIsHasOrb("Blue"))
	{
		SetRect(&s_Bluerc, -647, -129,
			m_smallInfo4.Width, m_smallInfo4.Height);

		m_pSprite->Draw(m_SmallUI4, &s_Bluerc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	///black
	if (g_pGameManager->GetIsHasOrb("Black"))
	{
		SetRect(&s_Blackrc, -710, -140,
			m_smallInfo5.Width, m_smallInfo5.Height);

		m_pSprite->Draw(m_SmallUI5, &s_Blackrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	///White
	if (g_pGameManager->GetIsHasOrb("White"))
	{
		SetRect(&s_Whiterc, -740, -205,
			m_smallInfo6.Width, m_smallInfo6.Height);

		m_pSprite->Draw(m_SmallUI6, &s_Whiterc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//MAIN UI
	SetRect(&UIrc,-500,-50,m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pTextureUI, &UIrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	///big///
	//RED BUTTON
	if (OnButton == Color::Red && g_pGameManager->GetIsHasOrb("Red"))
	{
		SetRect(&Redrc, -630, -230,
			m_stImageInfo3.Width, m_stImageInfo3.Height);

		m_pSprite->Draw(m_pTextureUI3, &Redrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//Yellow BUTTON
	if (OnButton == Color::Yellow && g_pGameManager->GetIsHasOrb("Yellow"))
	{
		SetRect(&Yellowrc, -550, -200,
			m_stImageInfo4.Width, m_stImageInfo4.Height);

		m_pSprite->Draw(m_pTextureUI4, &Yellowrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//Green BUTTON
	if (OnButton == Color::Green && g_pGameManager->GetIsHasOrb("Green"))
	{
		SetRect(&Greenrc, -575, -145,
			m_stImageInfo5.Width, m_stImageInfo5.Height);

		m_pSprite->Draw(m_pTextureUI5, &Greenrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//Blue BUTTON
	if (OnButton == Color::Blue && g_pGameManager->GetIsHasOrb("Blue"))
	{
		SetRect(&Bluerc, -635, -120,
			m_stImageInfo6.Width, m_stImageInfo6.Height);

		m_pSprite->Draw(m_pTextureUI6, &Bluerc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//Black BUTTON
	if (OnButton == Color::Black && g_pGameManager->GetIsHasOrb("Black"))
	{
		SetRect(&Blackrc, -700, -130,
			m_stImageInfo7.Width, m_stImageInfo7.Height);

		m_pSprite->Draw(m_pTextureUI7, &Blackrc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//White BUTTON
	if (OnButton == Color::White && g_pGameManager->GetIsHasOrb("White"))
	{
		SetRect(&Whiterc, -730, -195,
			m_stImageInfo8.Width, m_stImageInfo8.Height);

		m_pSprite->Draw(m_pTextureUI8, &Whiterc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pSprite->End();
}

void CUI::RenderGrab()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	SetRect(&s_textrc, -732, -360, m_textInfo.Width, m_textInfo.Height);
	m_pSprite->Draw(m_textUI, &s_textrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));


	m_pSprite->End();
}

void CUI::Render_Mapname()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//겨울
	SetRect(&s_textrc2, -25, -295, m_textInfo2.Width, m_textInfo2.Height);
	m_pSprite->Draw(m_textUI2, &s_textrc2,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//가을
	SetRect(&s_textrc3, -25, -295, m_textInfo3.Width, m_textInfo3.Height);
	m_pSprite->Draw(m_textUI3, &s_textrc3,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}


void CUI::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eInputEvent && g_pGameManager->GetUImode())
	{
		switch (eventMsg.message)
		{
		case WM_LBUTTONDOWN:
			px.x = LOWORD(eventMsg.lParam);
			px.y = HIWORD(eventMsg.lParam);

			if (PtInRect(&imageRC, px) == true)
			{
				m_isLButtonDown = true;
			}

			switch (OnButton)
			{
			case Color::Red: PickColor = Pick::Red;
				break;
			case Color::Yellow:PickColor = Pick::Yellow;
				break;
			case Color::Green: PickColor = Pick::Green;
				break;
			case Color::Blue: PickColor = Pick::Blue;
				break;
			case Color::Black: PickColor = Pick::Black;
				break;
			case Color::White: PickColor = Pick::White;
				break;
			default:
				break;
			}
			break;

		case WM_LBUTTONUP:
			px3 = { (LONG)matT._41,(LONG)matT._42 };
			m_isLButtonDown = false;
			break;

		case WM_MOUSEMOVE:
		{
			px2.x = LOWORD(eventMsg.lParam);
			px2.y = HIWORD(eventMsg.lParam);

			if (px2.x > 660 && px2.x < 720 && px2.y > 260 && px2.y < 320)
			{
				OnButton = Color::Red;
			}
			else if (px2.x > 580 && px2.x < 640 && px2.y > 230 && px2.y < 280)
			{
				OnButton = Color::Yellow;
			}
			else if (px2.x > 610 && px2.x < 670 && px2.y > 180 && px2.y < 230)
			{
				OnButton = Color::Green;
			}
			else if (px2.x > 670 && px2.x < 730 && px2.y > 150 && px2.y < 200)
			{
				OnButton = Color::Blue;
			}
			else if (px2.x > 735 && px2.x < 795 && px2.y > 165 && px2.y < 215)
			{
				OnButton = Color::Black;
			}
			else if (px2.x > 765 && px2.x < 825 && px2.y > 230 && px2.y < 280)
			{
				OnButton = Color::White;
			}
			else OnButton = Color::NONE;
		}
		break;
		}
	}
}

string CUI::GetName()
{
	return m_strName;
}

Color CUI::GetOnButton()
{
	return OnButton;
}

Pick CUI::GetPickColor()
{
	return PickColor;
}

void CUI::SetPickColor()
{
	//PickRed = false;
}
