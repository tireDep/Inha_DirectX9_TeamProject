#include "stdafx.h"
#include "Text.h"
#include "FontManager.h"

CText::CText() : 
	m_pFont(NULL)
{
}

CText::~CText()
{
}

void CText::Setup()
{
	m_pFont = g_pFontManager->GetFont(CFontManager::E_CABIN);
}

void CText::Render(int fps)
{
	if (fps > 9999)
		fps = 9999;

	string fpsString = "FPS : ";
	fpsString += to_string(fps);

	DWORD red = 0, green = 0, blue = 0;

	if (fps >= 60)
	{
		red = 0;	green = 255;	blue = 0;
	}
	if (fps < 60)
	{
		red = 255;	green = 255;	blue = 0;
	}
	if (fps < 30)
	{
		red = 255;	green = 0;		blue = 0;
	}

	RECT rc;
	SetRect(&rc, 10, 10, 100, 20);

	m_pFont->DrawTextA(NULL, fpsString.c_str(), fpsString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(red, green, blue));
}