#include "stdafx.h"
#include "MovingCube.h"

CMovingCube::CMovingCube()
{
}

CMovingCube::~CMovingCube()
{
}

void CMovingCube::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);
	
	m_startPos = 0.0f;
	m_endPos = 0.0f;
	m_speed = 0.0f;
	m_direction = 0;

	m_startPos = setData.gimmickData.startPos_movingCube;
	m_endPos = setData.gimmickData.endPos_movingCube;
	m_speed = setData.gimmickData.speed_movingCube;
	m_direction = setData.gimmickData.directionIndex_movingCube;
}
