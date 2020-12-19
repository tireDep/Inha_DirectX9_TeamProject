#pragma once
#include "Gimmick.h"

class CDoor : public CGimmick
{
private:
	// Need Map tool(Two Class? Need to Modify)
	// Size : Use m_vScale;
	// Opening_angle : m_fOpeningAngle;
	// Required_object : IsOpen(true, false)
		// Update(float, bool)
		// bool : switch ON/OFF
	D3DXMATRIXA16 m_matRotGimmick;
	float m_fOpeningAngle;
	bool IsOpen;
	bool pBox, pCylinder, pSphere;
	bool player ,render;
	float m_fRotationSpeed;
	float m_fRotAngle;
public:
	CDoor();
	~CDoor();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	void Setup(const ST_MapData & mapData);
	void Update(float duration);
	void Update(float duration, bool isSwitchOn);
	void Render();
	bool GetBool() { return render; }
	string GetName() { return m_strName; }
	D3DXVECTOR3 SendPosition() { return D3DXVECTOR3(); }
};
//void Setup(string folder, string file);