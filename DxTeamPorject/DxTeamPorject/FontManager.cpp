#include "stdafx.h"
#include "FontManager.h"


CFontManager::CFontManager()
{
}


CFontManager::~CFontManager()
{
}

LPD3DXFONT CFontManager::GetFont()
{
	D3DXFONT_DESC fd;
	fd.Height = 50;
	fd.Width = 50;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	wcscpy_s(fd.FaceName, L"±¼¸²Ã¼");
	
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, fd);
}

void CFontManager::Destroy()
{
}
