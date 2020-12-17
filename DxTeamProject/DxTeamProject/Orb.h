#pragma once
#include "Item.h"

class COBB;
class COrb : public CItem
{
private:
	float m_preAni;
	float m_nowAni;
	float m_UvX;
	float m_UvY;

	//�浹
	bool pBox, pCylinder, pSphere, player;

public:
	COBB* m_pOBB;
	COrb();
	~COrb();
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration);
	void Render();
	void SetBillbord();

	//�浹
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	//ĳ���Ϳ��浹
	void SetBool(bool set) { player = set; }
};

