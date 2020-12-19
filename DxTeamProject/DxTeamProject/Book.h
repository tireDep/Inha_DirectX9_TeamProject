#pragma once
#include "Item.h"

class CSkinnedMesh;

class CBook : public CItem
{
private:
	static int m_nCount;
	float m_fRotationSpeed;
	float m_fRotAngle;
	
	bool pBox, pCylinder, pSphere;
	bool player ,render;
	D3DXMATRIXA16 m_matRot;
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
	bool GetBool() { return render; }
	D3DXVECTOR3 SendPosition() { return D3DXVECTOR3(); }
};