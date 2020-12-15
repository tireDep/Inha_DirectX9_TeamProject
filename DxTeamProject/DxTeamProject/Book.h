#pragma once
#include "IObject.h"

class CSkinnedMesh;

class CBook : public IObject
{
private:
	static int m_nCount;
	float m_fRotationSpeed;
	float m_fRotAngle;
	
	bool pBox, pCylinder, pSphere;
	bool player;
	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot;


public:
	CBook();
	~CBook();
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration);
	bool hasIntersected(CSkinnedMesh * Character);
	void Render();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
};