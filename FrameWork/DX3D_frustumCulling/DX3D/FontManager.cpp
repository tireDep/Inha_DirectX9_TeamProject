#include "stdafx.h"
#include "FontManager.h"

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
}

LPD3DXFONT CFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];
	}

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (e == E_DEFAULT)
	{
		fd.Height = 25;
		fd.Width = 12;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;	// 외곽선 관련인듯?
		fd.PitchAndFamily = FF_DONTCARE;

		wcscpy_s(fd.FaceName, L"굴림체");
	}
	else
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;	// 외곽선 관련인듯?
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResourceA("font/umberto.ttf");
		wcscpy_s(fd.FaceName, L"umberto");
	}

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);

	return m_mapFont[e];
}

void CFontManager::Destroy()
{
	// for each(auto it in m_mapFont)
	// {
	// 	SafeRelease(it.second);
	// }
}
