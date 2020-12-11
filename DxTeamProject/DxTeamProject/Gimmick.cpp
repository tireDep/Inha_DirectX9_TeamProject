#include "stdafx.h"
#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"
#include "Door.h"

CGimmick::CGimmick()
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
	} // << switch
}