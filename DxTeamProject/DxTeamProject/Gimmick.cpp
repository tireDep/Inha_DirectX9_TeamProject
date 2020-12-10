#include "stdafx.h"
#include "Gimmick.h"
#include "RotationBoard.h"
#include "Switch.h"

CGimmick::CGimmick()
	//: m_pOBB(NULL)
{
}

CGimmick::~CGimmick()
{
	//SafeDelete(m_pOBB)
}

void CGimmick::Setup(ST_MapData setData)
{
	switch (setData.objType)
	{
		case eG_RotationBoard:
			{
				CRotationBoard* rotationBoard = new CRotationBoard;
				rotationBoard->Setup(setData);
			}
			break;

		case eG_BreakWall:
			break;

		case eG_Door:
			break;

		case eG_ColorChanger:
			break;

		case eG_Switch:
		{
			CSwitch* cSwitch = new CSwitch;
			cSwitch->Setup(setData);
		}
			break;
	} // << switch
}
