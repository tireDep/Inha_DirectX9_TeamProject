#pragma once
#include "Gimmick.h"
class COBB;

class CSwitch : public CGimmick
{
private:
	D3DXMATRIXA16 matS, matT, matWorld , collWorld; // �ݸ��� �κ� �����ȴ�!
	D3DXVECTOR3 m_position, m_scale;

	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot; //setdata
	
	//----- �浹
	LPD3DXMESH m_pBox; // CreateBox
	COBB* m_pColl; //�浹�ڽ�
	
	D3DXVECTOR3 m_vMin, m_vMax;


public:

	//���
	bool istrue;

	CSwitch();
	~CSwitch();
	void Setup();
	void Setup(ST_MapData setData);
	void Update();
	void Render();
	void Update(float duration);
	void SetBool(bool set) { istrue = set; }
	
	COBB* GetOBB2() { return m_pColl; } // �ݸ����κ�!
};

