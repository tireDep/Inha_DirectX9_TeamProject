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

	//충돌
	bool pBox, pCylinder, pSphere, player;
	bool render;
public:

	COrb();
	~COrb();
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration);
	void Render();
	void SetBillbord();

	//충돌
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	//캐릭터와충돌
	void SetBool(bool set) { player = set; }
	bool GetBool() { return render; }
	D3DXVECTOR3 SendPosition() { return D3DXVECTOR3(); }
};

