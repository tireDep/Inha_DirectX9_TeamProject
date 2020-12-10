#pragma once

#include "Gimmick.h"

class COBB;

class MovingCube : public CGimmick
{
public:
	MovingCube();
	~MovingCube();

private:
	

	int IndexNum; // 번호.
	bool istrue; //범위 조절 장치
	float speed; //속도
	float startpos , endpos; // 거리 ?
	D3DXVECTOR3 m_vPosition;

	//D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 m_matS, m_matR, m_matT, m_matRot; //setdata
	D3DXMATRIXA16 matS, matT, matR; // 대용
	D3DXVECTOR3 m_vMin, m_vMax;
public:
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration) { };
	void Update();

	void Render();

	
};

