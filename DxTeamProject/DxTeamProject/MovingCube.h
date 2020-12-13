#pragma once

#include "Gimmick.h"

class COBB;

class CMovingCube : public CGimmick
{
public:
	CMovingCube();
	~CMovingCube();

private:
	int m_indexNum; // 번호.
	bool m_istrue; //범위 조절 장치
	float m_fSpeed; //속도
	float m_fStartPos , m_fEndPos; // 거리 ?
	D3DXVECTOR3 m_vPosition;

	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot; //setdata
	//D3DXMATRIXA16 matWorld;
	// D3DXMATRIXA16 matS, matT, matR; // 대용
	// D3DXVECTOR3 m_vMin, m_vMax;
public:
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration);
	void Update();

	void Render();

	virtual void SetBool(bool set) { }
};

