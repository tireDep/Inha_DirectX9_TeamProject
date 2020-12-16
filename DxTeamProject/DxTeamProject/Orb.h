#pragma once
#include "Gimmick.h"
class COBB;
class COrb : public CGimmick
{
private:
	D3DXIMAGE_INFO m_stImageInfo;
	LPDIRECT3DTEXTURE9 m_pTex0;
	vector<ST_PT_VERTEX> m_vecVertex_Multi;
	ST_PT_VERTEX v;
	D3DXMATRIXA16 m_matWorld;
	float m_Uv_x;
	float m_Uv_y;
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vMin, m_vMax;
	D3DXMATRIXA16 mView, mInvView;
	//충돌
	bool pBox, pCylinder, pSphere, player;
public:

	COBB* m_pOBB;
	COrb();
	~COrb();
	void Setup();
	void Setup(ST_MapData setData);
	void Update(float duration) {};
	void Render();
	void Update();
	void SetBillbord();

	//충돌
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	//캐릭터와충돌
	void SetBool(bool set) { player = set; }


};

