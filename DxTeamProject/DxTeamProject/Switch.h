#pragma once
#include "Gimmick.h"
class COBB;

class CSwitch : public CGimmick
{
private:
	D3DXMATRIXA16 matS, matT, matWorld , collWorld; // �ݸ��� �κ� �����ȴ�!
	D3DXVECTOR3 m_position, m_scale;

	//----- �浹
	LPD3DXMESH m_pBox; // CreateBox
	
	D3DXVECTOR3 m_vMin, m_vMax;
	bool pBox, pCylinder,pSphere ,player ,render;

	// D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot; //setdata

public:

	COBB* m_pColl; //�浹����
	CSwitch();
	~CSwitch();
	bool GetBool() { return render; }
	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();
	void Update(float duration);
	void pBoxBool(bool set);
	void pCylinderBool(bool set);
	void pSphereBool(bool set);
	void SetBool(bool set);
	COBB* GetOBB2() { return m_pColl; } // �ݸ����κ�!

	void ChangeConditionMsg(bool set);
};

