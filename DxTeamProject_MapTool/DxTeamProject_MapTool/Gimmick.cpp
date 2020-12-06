#include "stdafx.h"
#include "RotationBoard.h"
#include "Gimmick.h"

CGimmick::CGimmick()
{
}

CGimmick::~CGimmick()
{
}

void CGimmick::SetDiffScale(D3DXVECTOR3 set)
{
	// >> 같은 비율로 크기 변환
	if (set.x != m_vScale.x)
		m_vScale = D3DXVECTOR3(set.x, set.x, set.x);
	else if (set.y != m_vScale.y)
		m_vScale = D3DXVECTOR3(set.y, set.y, set.y);
	else if (set.z != m_vScale.z)
		m_vScale = D3DXVECTOR3(set.z, set.z, set.z);
}

void CGimmick::CreateGimmick(const ObjectType objType)
{
	switch (objType)
	{
	case eG_RotationBoard:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		mapData.objType = objType;

		mapData.strObjName = string("RoataionBoard") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/RotationBoard";
		mapData.strTxtPath = "board.png";

		mapData.strXFilePath = string("Rotation_board") + string(".X");

		CRotationBoard* rotationBoard = new CRotationBoard;
		rotationBoard->Setup(mapData);
	}
		break;

	case eG_BreakWall:
		break;

	case eG_Door:
		break;

	case eG_ColorChanger:
		break;

	case eG_Switch:
		break;
	} // << switch
}

void CGimmick::CreateGimmick_SaveData(const ST_MapData & mapData)
{
	switch (mapData.objType)
	{
	case eG_RotationBoard:
	{
		CRotationBoard* rotationBoard = new CRotationBoard;
		rotationBoard->Setup(mapData);
	}
	break;

	case eG_BreakWall:
		break;

	case eG_Door:
		break;

	case eG_ColorChanger:
		break;

	case eG_Switch:
		break;
	} // << switch
}
