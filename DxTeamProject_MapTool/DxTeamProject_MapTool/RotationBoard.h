#pragma once
#include "Gimmick.h"

class CRotationBoard : public CGimmick
{
private:
	enum class RotationAxial { Rotation_X, Rotation_Y, Rotation_Z, NONE = 999 };

	Synthesize(float, m_fRotationSpeed, RotationSpeed);
	Synthesize(RotationAxial, m_rotationAxial, RotationAxial);
	Synthesize(RotationAxial, m_NowState, NowState); // πÃ¡§
	// << : saveData

	float m_fRotAngle;
	// << : UpdateData

public:
	CRotationBoard();
	~CRotationBoard();

	virtual void Setup() { }
	virtual void Setup(ST_MapData setData);
	virtual void Setup_OBB_Box() {}

	virtual void Update();

	// virtual void Update(CRay * ray) { IObject::Update(ray); };
	virtual void Render();
	// virtual void Render_OBB_Box() { IObject::Render_OBB_Box(); }

	// virtual void SetDiffScale(D3DXVECTOR3 set);

	virtual void SetRotationAxialIndex(int index);
	virtual int GetRotationAxialIndex();
};

