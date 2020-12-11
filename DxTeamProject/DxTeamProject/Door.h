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
	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRotGimmick;
	float m_fOpeningAngle;
	bool IsOpen;

	float m_fRotationSpeed;
	float m_fRotAngle;
public:
	CDoor();
	~CDoor();
	void SetBool(bool set) {};
	void Setup(const ST_MapData & mapData);
	void Update(float duration);
	void Update(float duration, bool isSwitchOn);
	void Render();
	string GetName() { return m_strName; }
};
//void Setup(string folder, string file);