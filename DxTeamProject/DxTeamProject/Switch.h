#pragma once
#include "Gimmick.h"
class COBB;

class CSwitch : public CGimmick
{
private:
	D3DXMATRIXA16 matS, matT, matWorld , collWorld;
	D3DXVECTOR3 m_position, m_scale;


	
	//----- 충돌
	LPD3DXMESH m_pBox; // CreateBox
	COBB* m_pColl; //충돌박스
	
	D3DXVECTOR3 m_vMin, m_vMax;


public:

	//잠깐
	bool istrue;

	CSwitch();
	~CSwitch();
	void Setup(string folder, string file);
	void Update();
	void Render();
	void Update(float duration) { };
	void SetBool(bool set) { istrue = set; }
	
	COBB* GetOBB2() { return m_pColl; }
};

