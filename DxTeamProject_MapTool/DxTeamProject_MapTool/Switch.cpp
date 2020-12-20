#include "stdafx.h"
#include "Switch.h"

CSwitch::CSwitch() : 
	m_weightType(WeightType::eBlack)
{
}

CSwitch::~CSwitch()
{
}

void CSwitch::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);

	if (setData.gimmickData.weightIndex == 0)
		m_weightType = WeightType::eBlack;
	else if (setData.gimmickData.weightIndex == 1)
		m_weightType = WeightType::eWhite;
	else if (setData.gimmickData.weightIndex == 2)
		m_weightType = WeightType::eYellow;

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

void CSwitch::SetWeightIndex(int index)
{
	if (index == 0)
		m_weightType = WeightType::eBlack;
	else if (index == 1)
		m_weightType = WeightType::eWhite;
	else if (index == 2)
		m_weightType = WeightType::eYellow;
}

int CSwitch::GetWeightIndex()
{
	if (m_weightType == WeightType::eBlack)
		return 0;
	else if (m_weightType == WeightType::eWhite)
		return 1;
	else if (m_weightType == WeightType::eYellow)
		return 2;
}
