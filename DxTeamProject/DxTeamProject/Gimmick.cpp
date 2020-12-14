#include "stdafx.h"
#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"
#include "MovingCube.h"

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
