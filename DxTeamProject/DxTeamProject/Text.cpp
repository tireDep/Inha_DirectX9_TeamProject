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

void CText::RenderFPS(int fps)
{
	if (fps > 9999)
		fps = 9999;

	string fpsString = "FPS : ";
	fpsString += to_string(fps);

	RECT rc;
	SetRect(&rc, 10, 10, 100, 20);

	if (fps >= 60)
		m_pFont->DrawTextA(NULL, fpsString.c_str(), fpsString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, GREEN);
	if (fps < 60)
		m_pFont->DrawTextA(NULL, fpsString.c_str(), fpsString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, YELLOW);
	if (fps < 30)
		m_pFont->DrawTextA(NULL, fpsString.c_str(), fpsString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);
}

void CText::RenderCharacterPosition(D3DXVECTOR3 CharacterPosition)
{
	stringstream stream;
	float _x = CharacterPosition.x;
	float _y = CharacterPosition.y;
	float _z = CharacterPosition.z;

	string positionString = "Character";

	RECT rc;
	SetRect(&rc, 10, 40, 100, 60);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "x : ";
	stream << fixed << setprecision(2) << _x;
	positionString += stream.str();	stream.str("");
	SetRect(&rc, 120, 40, 200, 60);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "y : ";
	stream << fixed << setprecision(2) << _y;
	positionString += stream.str(); stream.str("");
	SetRect(&rc, 220, 40, 300, 60);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "z : ";
	stream << fixed << setprecision(2) << _z;
	positionString += stream.str(); stream.str("");
	SetRect(&rc, 320, 40, 400, 60);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);
}

void CText::RenderBoxPosition(D3DXVECTOR3 BoxPosition)
{
	stringstream stream;
	float _x = BoxPosition.x;
	float _y = BoxPosition.y;
	float _z = BoxPosition.z;

	string positionString = "Box";

	RECT rc;
	SetRect(&rc, 10, 70, 100, 80);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "x : ";
	stream << fixed << setprecision(2) << _x;
	positionString += stream.str();	stream.str("");
	SetRect(&rc, 120, 70, 200, 80);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "y : ";
	stream << fixed << setprecision(2) << _y;
	positionString += stream.str(); stream.str("");
	SetRect(&rc, 220, 70, 300, 80);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);

	positionString = "z : ";
	stream << fixed << setprecision(2) << _z;
	positionString += stream.str(); stream.str("");
	SetRect(&rc, 320, 70, 400, 80);
	m_pFont->DrawTextA(NULL, positionString.c_str(), positionString.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, RED);
}

void CText::RenderGrab(vector<CObject*> ObjectPosition , D3DXVECTOR3 PlayerPosition)
{
	for (int i = 0; i < ObjectPosition.size(); ++i)
	{
		if (ObjectPosition[i]->GetPosition().x - PlayerPosition.x < 1.5f
			&& ObjectPosition[i]->GetPosition().z - PlayerPosition.z < 1.5f
			&&    ObjectPosition[i]->GetPosition().x - PlayerPosition.x> -1.5f
			&& ObjectPosition[i]->GetPosition().z - PlayerPosition.z > -1.5f)
		{
			RECT rc;
			// later client rect
			SetRect(&rc, 732, 360, 100, 60);
			string GrabString = "Àâ±â(F)";
			m_pFont->DrawTextA(NULL, GrabString.c_str(), GrabString.length(),
				&rc, DT_LEFT | DT_TOP | DT_NOCLIP, BLUE);
			return;
		}
	}
}