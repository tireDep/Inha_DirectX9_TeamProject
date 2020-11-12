#include "stdafx.h"
#include "UI.h"

CUI::CUI()
{
	m_isLButtonDown = false;
	OnButton = false;
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

	GetClientRect(g_hWnd, &rc);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/pngegg.png",
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

	//¹öÆ°2
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/red.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo3, NULL, &m_pTextureUI3);
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

	SetRect(&rc3, 0,0,
		m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureUI2, &rc3,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(150, 255, 255, 255));

	//MAIN UI
	SetRect(&rc,-500,-50,m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pTextureUI, &rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));


	//RED BUTTON
	if (OnButton)
	{
		SetRect(&rc4, -630, -230,
			m_stImageInfo3.Width, m_stImageInfo3.Height);

		m_pSprite->Draw(m_pTextureUI3, &rc4,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	m_pSprite->End();
}

void CUI::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		px.x = LOWORD(lParam);
		px.y = HIWORD(lParam);
		cout << " x : " << px.x << " y: " << px.y;
		if (PtInRect(&imageRC, px) == true)
		{
			m_isLButtonDown = true;

		}
		break;
	case WM_LBUTTONUP:
		px3 = { (LONG)matT._41,(LONG)matT._42 };
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{
		px2.x = LOWORD(lParam);
		px2.y = HIWORD(lParam);
		cout << " x : " << px2.x << " y: " << px2.y;
		if (px2.x > 660 && px2.x < 720 && px2.y > 260 && px2.y < 320)
		{
			OnButton = true;
		}
		else OnButton = false;
	}
	break;
	default:
		break;
	}
}

string CUI::GetName()
{
	return m_strName;
}
