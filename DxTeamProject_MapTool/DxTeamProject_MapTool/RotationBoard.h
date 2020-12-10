#pragma once
#include "Gimmick.h"

class CRotationBoard : public CGimmick
{
private:
	enum class RotationAxial { Rotation_X, Rotation_Y, Rotation_Z, NONE = 999 };

	Synthesize(float, m_fRotationSpeed, RotationSpeed);
	Synthesize(RotationAxial, m_rotationAxial, Rotation_Axial);
	Synthesize(RotationAxial, m_NowState, NowState); // πÃ¡§
	// << : saveData

	float m_fRotAngle;
	// << : UpdateData

public:
	CRotationBoard();
	~CRotationBoard();

	virtual void Setup(ST_MapData setData);

	virtual void Render();

	virtual void SetRotationAxialIndex(int index);
	virtual int GetRotationAxialIndex();
};

