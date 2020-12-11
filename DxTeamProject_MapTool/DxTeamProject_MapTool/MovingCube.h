#pragma once
#include "Gimmick.h"
class CMovingCube : public CGimmick
{
private:
	Synthesize(int, m_direction, Direction);
	Synthesize(float, m_speed, Speed);
	Synthesize(float, m_startPos, StartPos);
	Synthesize(float, m_endPos, EndPos);

public:
	CMovingCube();
	~CMovingCube();

	virtual void Setup(ST_MapData setData);

	// int GetDirectionIndex();
};

