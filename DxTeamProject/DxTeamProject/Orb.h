#pragma once

class COBB;
class COrb 
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
public:

	COBB* m_pOBB;
	COrb();
	~COrb();
	void Setup();
	void Render();
	void Update();
	void SetBillbord();
};

