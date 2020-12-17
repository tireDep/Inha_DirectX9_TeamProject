#pragma once
#include "Gimmick.h"
class COBB;

class CSwitch : public CGimmick
{
private:
	D3DXMATRIXA16 matS, matT, matWorld , collWorld; // 콜리더 부분 지우면안댐!
	D3DXVECTOR3 m_position, m_scale;

	//----- 충돌
	LPD3DXMESH m_pBox; // CreateBox
	
	D3DXVECTOR3 m_vMin, m_vMax;
	bool pBox, pCylinder,pSphere ,player ,render;

	// D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot; //setdata

public:

	COBB* m_pColl; //충돌박스
	CSwitch();
	~CSwitch();
	bool GetBool() { return render; }
	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();
	void Update(float duration);
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	COBB* GetOBB2() { return m_pColl; } // 콜리더부분!
};

