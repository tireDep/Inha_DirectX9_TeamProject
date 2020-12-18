#pragma once
#include "Gimmick.h"
class COBB;

class Color_changer : public CGimmick
{
public:
	Color_changer();
	~Color_changer();
private:
	LPD3DXMESH m_pMeshBeam; //빔 메쉬.

	D3DXMATRIXA16  BeamWorld; //장치월드 , 빔월드
	D3DXMATRIXA16 matS, matT , matR;  // 빔
	D3DXVECTOR3  m_scale; //빔포지션 , 빔 크기 

	float angle; //장치 , 빔 앵글 조절.

	float length; // 빔 길이 조절.

	D3DXCOLOR c; 
	D3DXVECTOR3 m_vMin, m_vMax;
	bool pBox, pCylinder, pSphere, player, render;
	// KT
	float m_fHitLength;
	// D3DXMATRIXA16 m_matS, m_matR, m_matT;  //맵 데이터
public:
	D3DMATERIAL9 m_stMtl;
	D3DXVECTOR3 m_position;
	COBB *m_BeamOBB;
	
	void Setup(); // x파일
	void Setup(ST_MapData setData);

	void Update();
	void Render();

	void Update(float duration);

	void SetColor(D3DXCOLOR color);
	
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	bool GetBool() { return render; }
	// KT
	void SetHitLength(float HitLength); // 빔이 맞았을때 거리 구해줌.


	//인터섹트
	
};

