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
	puls = 0.f;
	colorpuls = false;
	BookCol = false;

	BlackAlp = 0;
	BlackAlp2 = 0;
	BlackAlp3 = 0;
	Blacksw = false;
	Blacksw2 = false;
	Blacksw3 = false;
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

void CUI::Setup_Script()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	GetClientRect(g_hWnd, &UIrc);
	////////////// black
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/black_script_1.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo, NULL, &m_scriUI);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/black_script_2.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo2, NULL, &m_scriUI2);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/black_script_3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo3, NULL, &m_scriUI3);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/black_script_3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo3, NULL, &m_scriUI3);
	/////////////////////white
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/white_script_1.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo4, NULL, &m_scriUI4);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/white_script_2.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo5, NULL, &m_scriUI5);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/white_script_3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo6, NULL, &m_scriUI6);
	//////////////yellow
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/yellow_script_1.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo7, NULL, &m_scriUI7);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/yellow_script_2.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo8, NULL, &m_scriUI8);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Script/yellow_script_3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_scriInfo9, NULL, &m_scriUI9);

}

void CUI::Rneder_Script()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	//black
	if (g_pGameManager->GetIsHasOrb("Black"))
	{
		SetRect(&s_scrirc, -270, -590,
			m_scriInfo.Width, m_scriInfo.Height);

		m_pSprite->Draw(m_scriUI, &s_scrirc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(BlackAlp, 255, 255, 255));

		HasOrb = true;
	}

	//SetRect(&s_scrirc2, -380, -590,
	//	m_scriInfo2.Width, m_scriInfo2.Height);

	//m_pSprite->Draw(m_scriUI2, &s_scrirc2,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(BlackAlp2, 255, 255, 255));

	//SetRect(&s_scrirc3, -190,-590,
	//	m_scriInfo3.Width, m_scriInfo3.Height);

	//m_pSprite->Draw(m_scriUI3, &s_scrirc3,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(BlackAlp2, 255, 255, 255));

	//white
	//SetRect(&s_scrirc4, -425, -590,
	//	m_scriInfo4.Width, m_scriInfo4.Height);

	//m_pSprite->Draw(m_scriUI4, &s_scrirc4,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	//SetRect(&s_scrirc5, -255, -590,
	//	m_scriInfo5.Width, m_scriInfo5.Height);

	//m_pSprite->Draw(m_scriUI5, &s_scrirc5,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	//SetRect(&s_scrirc6, -310, -590,
	//	m_scriInfo6.Width, m_scriInfo6.Height);

	//m_pSprite->Draw(m_scriUI6, &s_scrirc6,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	////yellow
	//SetRect(&s_scrirc7, -345, -590,
	//	m_scriInfo7.Width, m_scriInfo7.Height);

	//m_pSprite->Draw(m_scriUI7, &s_scrirc7,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	//SetRect(&s_scrirc8, -215, -590,
	//	m_scriInfo8.Width, m_scriInfo8.Height);

	//m_pSprite->Draw(m_scriUI8, &s_scrirc8,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	//SetRect(&s_scrirc8, -140, -590,
	//	m_scriInfo9.Width, m_scriInfo9.Height);

	//m_pSprite->Draw(m_scriUI9, &s_scrirc9,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void CUI::Setup_Attain()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	GetClientRect(g_hWnd, &UIrc);

	//////////////back
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/back.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo, NULL, &m_attUI);

	//////////////winter
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/winter_01.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo2, NULL, &m_attUI2);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/winter_02.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo3, NULL, &m_attUI3);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/winter_03.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo4, NULL, &m_attUI4);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/winter_04.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo5, NULL, &m_attUI5);

	//////////fall
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/fall_01.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo7, NULL, &m_attUI7);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/fall_02.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo8, NULL, &m_attUI8);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/fall_03.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo9, NULL, &m_attUI9);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"Attain/fall_04.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_attInfo10, NULL, &m_attUI10);

}

void CUI::Render_Attain()
{
	SetRect(&imageRC, matT._41, matT._42,
		matT._41 + m_stImageInfo.Width, matT._42 + m_stImageInfo.Height);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTranslation(&matT, movep, movepy, 0);
	matWorld = matT;

	m_pSprite->SetTransform(&matWorld);

	////back
	SetRect(&s_attrc, 0, 0,
		m_attInfo.Width, m_attInfo.Height);
	m_pSprite->Draw(m_attUI, &s_attrc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	////winter
	SetRect(&s_attrc2, -10, -160,
		m_attInfo2.Width, m_attInfo2.Height);
	m_pSprite->Draw(m_attUI2, &s_attrc2,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));
	
	if (g_pGameManager->GetIsHasOrb("Black"))
	{
		SetRect(&s_attrc3, -10, -160,
			m_attInfo3.Width, m_attInfo3.Height);
		m_pSprite->Draw(m_attUI3, &s_attrc3,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (g_pGameManager->GetIsHasOrb("White"))
	{
		SetRect(&s_attrc4, -10, -160,
			m_attInfo4.Width, m_attInfo4.Height);
		m_pSprite->Draw(m_attUI4, &s_attrc4,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SetRect(&s_attrc5, -10, -160,
		m_attInfo5.Width, m_attInfo5.Height);
	m_pSprite->Draw(m_attUI5, &s_attrc5,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

/////////////fall

	SetRect(&s_attrc7, -710, -160,
		m_attInfo7.Width, m_attInfo7.Height);
	m_pSprite->Draw(m_attUI7, &s_attrc7,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	if (g_pGameManager->GetIsHasOrb("Yellow"))
	{
		SetRect(&s_attrc8, -710, -160,
			m_attInfo8.Width, m_attInfo8.Height);
		m_pSprite->Draw(m_attUI8, &s_attrc8,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (BookCol)
	{
		SetRect(&s_attrc9, -710, -160,
			m_attInfo9.Width, m_attInfo9.Height);
		m_pSprite->Draw(m_attUI9, &s_attrc9,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SetRect(&s_attrc10, -710, -160,
		m_attInfo10.Width, m_attInfo10.Height);
	m_pSprite->Draw(m_attUI10, &s_attrc10,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
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
		D3DCOLOR_ARGB(puls, 255, 255, 255));

	//가을
	//SetRect(&s_textrc3, -25, -295, m_textInfo3.Width, m_textInfo3.Height);
	//m_pSprite->Draw(m_textUI3, &s_textrc3,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void CUI::Update()
{
	if (colorpuls == false)
	{
		puls++;
		if (puls == 255)
			colorpuls = true;
	}
	else if (colorpuls == true)
	{
		puls--;
		if (puls == 0)
			colorpuls = false;
	}
}

void CUI::Script_Update()
{
	if (HasOrb)
	{
		BlackAlp++;
		if (BlackAlp == 255)
			Blacksw = false;
	}
	else if (!Blacksw)
	{
		BlackAlp--;
		if (BlackAlp == 0)
		{
			Blacksw2 = true;
			HasOrb = false;
		}
	}

	if (Blacksw2)
	{
		BlackAlp2++;
		if (BlackAlp2 == 255)
			Blacksw2 = false;
	}
	else if (!Blacksw2)
	{
		BlackAlp2--;
		if (BlackAlp2 == 0)
		{
			Blacksw3 = true;
		}
	}
}


void CUI::ReceiveEvent(ST_EVENT eventMsg)
{
	if (eventMsg.eventType == EventType::eConditionChange)
	{
		if (strstr(eventMsg.conditionName.c_str(), "Book"))
			BookCol = true;
		else if (strstr(eventMsg.conditionName.c_str(), "Trigger"))
			cout << "hit" << endl;
	}


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
