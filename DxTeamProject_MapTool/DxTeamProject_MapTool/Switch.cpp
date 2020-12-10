#include "stdafx.h"
#include "Switch.h"

CSwitch::CSwitch()
{
}

CSwitch::~CSwitch()
{
}

void CSwitch::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);

	// todo condition variable
}

void CSwitch::Render()
{
	CGimmick::Render();
}

void CSwitch::SetTexture(int index)
{
	switch (index)
	{
	case 0:
		m_strTxtFile = "cubeworld_glow.tga";
		break;

	case 1:
		m_strTxtFile = "cubeworld_metal.tga";
		break;

	case 2:
		m_strTxtFile = "cubeworld_rough.tga";
		break;

	case 3:
		m_strTxtFile = "cubeworld_texture.tga";
		break;
	}

	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
	// m_vecTextures.clear(); // 텍스쳐가 없어서 지우면 터짐(0 삭제됨)
	m_vecTextures.push_back(m_pTexture);
}


int CSwitch::GetTextureIndex()
{
	if (m_strTxtFile == "cubeworld_glow.tga")
		return 0;
	if (m_strTxtFile == "cubeworld_metal.tga")
		return 1;
	if (m_strTxtFile == "cubeworld_rough.tga")
		return 2;
	if (m_strTxtFile == "cubeworld_texture.tga")
		return 3;
}

void CSwitch::SetConditionType()
{
}

void CSwitch::SetCondition()
{
}
