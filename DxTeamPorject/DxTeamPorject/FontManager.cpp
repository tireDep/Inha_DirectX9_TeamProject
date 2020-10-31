#include "stdafx.h"
#include "FontManager.h"

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
}

LPD3DXFONT CFontManager::GetFont(eFuntType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
		return m_mapFont[e];
	
	D3DXFONT_DESC	FontDesc;
	ZeroMemory(&FontDesc, sizeof(D3DXFONT_DESC));

	if (e == E_DEFAULT)
	{
		FontDesc.Height = 25;
		FontDesc.Width = 12;
		FontDesc.Weight = FW_BOLD;
		FontDesc.Italic = false;
		FontDesc.CharSet = DEFAULT_CHARSET;
		FontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		FontDesc.PitchAndFamily = FF_DONTCARE;
		wcscpy_s(FontDesc.FaceName, L"±¼¸²Ã¼");
	}
	else if(e==E_CABIN)
	{
		FontDesc.Height = 25;
		FontDesc.Width = 12;
		FontDesc.Weight = FW_BOLD;
		FontDesc.Italic = false;
		FontDesc.CharSet = DEFAULT_CHARSET;
		FontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		FontDesc.PitchAndFamily = FF_DONTCARE;
		AddFontResourceEx(L"font/Cabin.otf", FR_PRIVATE, 0);
		wcscpy_s(FontDesc.FaceName, L"Cabin");
	}
	D3DXCreateFontIndirect(g_pD3DDevice, &FontDesc, &m_mapFont[e]);
	return m_mapFont[e];
}

void CFontManager::Destroy()
{
	for each(auto it in m_mapFont)
		SafeRealse(it.second);
	m_mapFont.clear();
}