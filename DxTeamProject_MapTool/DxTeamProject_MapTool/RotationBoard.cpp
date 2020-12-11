#include "stdafx.h"
#include "RotationBoard.h"

CRotationBoard::CRotationBoard() :
	m_fRotationSpeed(0.0f),
	m_rotationAxial(RotationAxial::NONE),
	m_NowState(RotationAxial::NONE),
	m_fRotAngle(0.0f)
{
	m_pMesh = NULL;
	m_pTexture = NULL;
}

CRotationBoard::~CRotationBoard()
{
}

void CRotationBoard::Setup(ST_MapData setData)
{
	CGimmick::Setup(setData);

	m_fRotationSpeed = 0.0f;
	m_rotationAxial = RotationAxial::NONE;
	m_NowState = RotationAxial::NONE;

	m_fRotationSpeed = setData.gimmickData.roationSpeed_rotaitonBoard;
	if (setData.gimmickData.roationAxialIndex_rotaitonBoard == 0)
		m_rotationAxial = RotationAxial::Rotation_X; 
	else if (setData.gimmickData.roationAxialIndex_rotaitonBoard == 1)
		m_rotationAxial = RotationAxial::Rotation_Y;
	else if (setData.gimmickData.roationAxialIndex_rotaitonBoard == 2)
		m_rotationAxial = RotationAxial::Rotation_Z;
	else if (setData.gimmickData.roationAxialIndex_rotaitonBoard == 3)
		m_rotationAxial = RotationAxial::NONE;
}

void CRotationBoard::Render()
{
	CGimmick::Render();
}

void CRotationBoard::SetRotationAxialIndex(int index)
{
	if (index == 0)
		m_rotationAxial = RotationAxial::Rotation_X;
	else if (index == 1)
		m_rotationAxial = RotationAxial::Rotation_Y;
	else if (index == 2)
		m_rotationAxial = RotationAxial::Rotation_Z;
}

int CRotationBoard::GetRotationAxialIndex()
{
	if (m_rotationAxial == RotationAxial::Rotation_X)
		return 0;
	else if (m_rotationAxial == RotationAxial::Rotation_Y)
		return 1;
	else if (m_rotationAxial == RotationAxial::Rotation_Z)
		return 2;
	else if (m_rotationAxial == RotationAxial::NONE)
		return 3;
}
