#pragma once
#include "Gimmick.h"

enum class RotationAxial
{
	Rotation_X, Rotation_Y, Rotation_Z, NONE = 999
};
class CRotationBoard : public CGimmick
{
private:
	D3DXMATRIXA16 m_matRotGimmick;
	RotationAxial rotationAxial;
	float m_fRotationSpeed;
	float m_fRotAngle;
	bool pBox, pCylinder, pSphere;
	bool player ,render;
	/// Need Map tool
	// Size : Use m_vScale
	// Rotation_axial : enum class RotationAxial
	// Rotation_Speed : m_fRotationSpeed
	// State - Stop : RotationAxial::None
public:
	CRotationBoard();
	~CRotationBoard();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	void Setup(const ST_MapData & mapData);
	void Update(float duration);
	void Render();
	bool GetBool() { return render; }
	string GetName() { return m_strName; }
	D3DXVECTOR3 SendPosition() { return D3DXVECTOR3(); }
};
/// Delete Later...
//void Setup(string folder, string file);
//D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRotGimmick;