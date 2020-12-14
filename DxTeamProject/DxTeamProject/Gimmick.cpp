#include "stdafx.h"
#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"
#include "MovingCube.h"
#include "Colorchanger.h"

CGimmick::CGimmick() :
	m_onOffCondition(OnOffCondition::eNull)
{
}

CGimmick::~CGimmick()
{
}

void CGimmick::Setup(const ST_MapData & mapData)
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

		case eG_DoorFrame: case eG_Door:
			{
				CDoor* door = new CDoor;
				door->Setup(mapData);
			}
			break;

		case eG_ColorChanger:
		{
			Color_changer* colorChanger = new Color_changer;
			colorChanger->Setup(mapData);
		}
			break;

		case eG_Switch:
		{
			CSwitch* cSwitch = new CSwitch;
			cSwitch->Setup(mapData);
		}
			break;

		case eG_MovingCube:
		{
			CMovingCube* movingCube = new CMovingCube;
			movingCube->Setup(mapData);
		}
			break;
	} // << switch
}

void CGimmick::SetLoadData(const ST_MapData & mapData)
{
	m_strObjName = mapData.strObjName;
	m_strFolder = mapData.strFolderPath;
	m_strXFile = mapData.strXFilePath;
	m_strTxtFile = mapData.strTxtPath;
	m_ObjectType = mapData.objType;

	m_vScale = mapData.vScale;
	m_vRotation = mapData.vRotate;
	m_vTranslation = mapData.vTranslate;

	SetGimmickCondition(mapData);

	ST_XFile* xfile = new ST_XFile;

	g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

	if (m_strTxtFile != "")
		g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

	m_pMesh = xfile->pMesh;
	m_adjBuffer = xfile->adjBuffer;
	m_vecMtrls = xfile->vecMtrl;
	m_vecTextures = xfile->vecTextrure;
	m_numMtrls = xfile->nMtrlNum;

	delete xfile;

	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&m_matR, D3DXToRadian(m_vRotation.y), D3DXToRadian(m_vRotation.x), D3DXToRadian(m_vRotation.z));
	D3DXMatrixTranslation(&m_matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	m_matWorld = m_matS * m_matR * m_matT;

	// OBB TEST
	m_pOBB = new COBB;
	m_pOBB->Setup(*this);
	g_pObjectManager->AddOBBbox(m_pOBB);
	g_pObjectManager->AddGimmick(this);
}

void CGimmick::SetGimmickCondition(const ST_MapData & mapData)
{
	if (mapData.gimmickData.conditionName != "")
	{
		m_strConditionName = mapData.gimmickData.conditionName;

		if (mapData.gimmickData.onOffConditionIndex == 0)		m_onOffCondition = OnOffCondition::eOrb;
		else if (mapData.gimmickData.onOffConditionIndex == 1)	m_onOffCondition = OnOffCondition::eItem;
		else if (mapData.gimmickData.onOffConditionIndex == 2)	m_onOffCondition = OnOffCondition::eSwitch;

		// if (m_onOffCondition != OnOffCondition::eOrb)
		// 	m_conditionOrbindex = -1;
		// else
		// 	m_conditionOrbindex = mapData.gimmickData.conditionOrbIndex;
	}
}
