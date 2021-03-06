#include "stdafx.h"
#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"
#include "MovingCube.h"
#include "ColorChanger.h"

CGimmick::CGimmick() : 
	m_openCondition(OnOffCondition::eOrb)
{
	m_strConditionName = "Black";
}

CGimmick::~CGimmick()
{
}

void CGimmick::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

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

	IObject::Setup_OBB_Box();

	// =================

	if (m_ObjectType != ObjectType::eG_Door
		&& m_ObjectType != ObjectType::eG_DoorFrame
		&& m_ObjectType != ObjectType::eG_ColorChanger
		&& m_ObjectType != ObjectType::eG_Switch)
	{
		m_strConditionName = "";
		return;
	}

	if (setData.gimmickData.conditionName != "")
	{
		m_strConditionName = setData.gimmickData.conditionName;

		if (setData.gimmickData.onOffConditionIndex == 0)		m_openCondition = OnOffCondition::eOrb;
		else if (setData.gimmickData.onOffConditionIndex == 1)	m_openCondition = OnOffCondition::eItem;
		else if (setData.gimmickData.onOffConditionIndex == 2)	m_openCondition = OnOffCondition::eSwitch;

		if (m_openCondition != OnOffCondition::eOrb)
			m_conditionOrbindex = 0;
		else
			m_conditionOrbindex = setData.gimmickData.conditionOrbIndex;
	}
}

void CGimmick::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (g_pObjectManager->GetPickObjName() == m_strConditionName && m_strConditionName != "" && m_pShader)
	{
		// >> 조건 오브젝트가 선택되었을 경우
		SetShader(GetmatWorld());
		SetShaderColor(D3DXVECTOR4(0, 0, 0, 1), D3DXVECTOR4(0, 0.5, 0.5, 1));
		IObject::Render();
	}
	else if (!m_isPick && !m_isClick || !m_pShader)
	{
		// >> 오브젝트가 선택되지 않거나 셰이더가 없을 경우
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (m_vecTextures[i] != 0)
				g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			else if (m_pTexture != NULL)
				g_pD3DDevice->SetTexture(0, m_pTexture);
			// >> 텍스처 매치 안되있을 때

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		// >> 오브젝트가 선택되었을 경우
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
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

void CGimmick::SetTexture(int index)
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

	case 4:
		m_strTxtFile = "tower_defense_texture.tga";
		break;
	}

	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
	// m_vecTextures.clear(); // 텍스쳐가 없어서 지우면 터짐(0 삭제됨)
	m_vecTextures.push_back(m_pTexture);
}

int CGimmick::GetTextureIndex()
{
	if (m_strTxtFile == "cubeworld_glow.tga")
		return 0;
	if (m_strTxtFile == "cubeworld_metal.tga")
		return 1;
	if (m_strTxtFile == "cubeworld_rough.tga")
		return 2;
	if (m_strTxtFile == "cubeworld_texture.tga")
		return 3;
	if (m_strTxtFile == "tower_defense_texture.tga")
		return 4;
}

void CGimmick::SetOpenCondition(int index)
{
	if (index == 0)			m_openCondition = OnOffCondition::eOrb;
	else if (index == 1)	m_openCondition = OnOffCondition::eItem;
	else if (index == 2)	m_openCondition = OnOffCondition::eSwitch;
}

void CGimmick::SetConditionName(string strName)
{
	m_strConditionName = strName;
}

int CGimmick::GetOpenConditionIndex()
{
	if (m_openCondition == OnOffCondition::eOrb)			return 0;
	else if (m_openCondition == OnOffCondition::eItem)		return 1;
	else if (m_openCondition == OnOffCondition::eSwitch)	return 2;
	else
		return -1;
}

string CGimmick::GetOpenConditionType()
{
	if (m_openCondition == OnOffCondition::eOrb)			return "Orb";
	else if (m_openCondition == OnOffCondition::eItem)		return "Item";
	else if (m_openCondition == OnOffCondition::eSwitch);	return "Switch";
}

string CGimmick::GetConditionName()
{
	return m_strConditionName;
}

void CGimmick::CreateGimmick(const ObjectType& objType)
{
	ST_MapData mapData;
	mapData.vScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mapData.vTranslate = D3DXVECTOR3(0.5f, 0.0f, 0.5f);

	mapData.objType = objType;

	switch (objType)
	{
	case eG_RotationBoard:
	{
		mapData.strObjName = string("RoataionBoard") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/RotationBoard";
		mapData.strTxtPath = "board.png";

		mapData.strXFilePath = string("Rotation_board") + string(".X");

		mapData.gimmickData.roationSpeed_rotaitonBoard = 0.0f;
		mapData.gimmickData.roationAxialIndex_rotaitonBoard = 0;

		CRotationBoard* rotationBoard = new CRotationBoard;
		rotationBoard->Setup(mapData);
	}
		break;

	case eG_BreakWall:
		break;

	case eG_DoorFrame:
	{
		mapData.strObjName = string("Door") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/Door";
		mapData.strTxtPath = "cubeworld_texture.tga";

		mapData.strXFilePath = string("door_frame") + string(".X");

		CDoor* doorFrame = new CDoor;
		doorFrame->Setup(mapData);

		// 문은 프레임, 문짝으로 이루어짐

		mapData.objType = eG_Door;
		mapData.strObjName = string("Door") + to_string(m_nRefCnt + 1);
		mapData.strXFilePath = string("door_right") + string(".X");

		CDoor* doorRight = new CDoor;
		doorRight->Setup(mapData);
	}
	break;

	case eG_ColorChanger:
	{
		mapData.strObjName = string("ColorChanger") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/ColorChanger";
		mapData.strTxtPath = "cubeworld_texture.tga";

		mapData.strXFilePath = string("Color_changer.X");

		CColorChanger* colorChanger = new CColorChanger;
		colorChanger->Setup(mapData);
	}
		break;

	case eG_Switch:
	{
		mapData.strObjName = string("Switch") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/Switch";
		mapData.strTxtPath = "cubeworld_texture.tga";

		mapData.strXFilePath = string("Force_switch") + string(".X");

		CSwitch* cSwitch = new CSwitch;
		cSwitch->Setup(mapData);
	}
		break;

	case eG_MovingCube:
	{
		mapData.strObjName = string("MovingCube") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Gimmick/MovingCube";
		mapData.strTxtPath = "moving_cube_1.png";

		mapData.strXFilePath = string("moving_cube") + string(".X");

		mapData.gimmickData.startPos_movingCube= 0.0f;
		mapData.gimmickData.endPos_movingCube = 0.0f;
		mapData.gimmickData.speed_movingCube = 0.0f;
		mapData.gimmickData.directionIndex_movingCube = 0;

		CMovingCube* movingCube = new CMovingCube;
		movingCube->Setup(mapData);
	}
		break;
	} // << switch
}

void CGimmick::CreateGimmick_SaveData(ST_MapData & mapData)
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
		CDoor* doorFrame = new CDoor;
		doorFrame->Setup(mapData);
	}
	break;

	case eG_ColorChanger:
	{
		CColorChanger* colorChanger = new CColorChanger;
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
		CMovingCube* rotationBoard = new CMovingCube;
		rotationBoard->Setup(mapData);
	}
		break;
	} // << switch
}
