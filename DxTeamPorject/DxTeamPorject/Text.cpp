#include "stdafx.h"
#include "Text.h"
#include "FontManager.h"

CText::CText()
{
}

CText::~CText()
{
}

void CText::Setup()
{
	m_font = g_FontManager->GetFont();
}
