
#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
	m_isLButtonDown = false;
	movep = 0;
	movepy = 0;
	px3 = { 0,0 };
}


CUI::~CUI()
{

}

void CUI::Setup_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/panel-info.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo, NULL, &m_pTextureUI);


	//버튼1
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/btn-med-up.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE
		, D3DX_DEFAULT, 0, &m_stImageInfo2, NULL, &m_pTextureUI2);


	//버튼2
	D3DXCreateTextureFromFileExA(g_pD3DDevice,
		"UI/btn-med-up.png",
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

	//MAIN UI
	SetRect(&rc, 0, 0,
		m_stImageInfo.Width, m_stImageInfo.Height);

	m_pSprite->Draw(m_pTextureUI, &rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//BUTTON 1

	SetRect(&rc3, rc.left - 145, rc.top - 300,
		m_stImageInfo2.Width, m_stImageInfo2.Height);

	m_pSprite->Draw(m_pTextureUI2, &rc3,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//BUTTON2

	SetRect(&rc4, rc.left - 145, rc.top - 365,
		m_stImageInfo3.Width, m_stImageInfo3.Height);

	m_pSprite->Draw(m_pTextureUI3, &rc4,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));


	m_pSprite->End();

}




void CUI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		px.x = LOWORD(lParam);
		px.y = HIWORD(lParam);
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

		if (m_isLButtonDown == true)
		{
			px2.x = LOWORD(lParam);
			px2.y = HIWORD(lParam);

			movep = px3.x + px2.x - px.x;
			movepy = px3.y + px2.y - px.y;
		}
		break;
	default:
		break;
	}
}


