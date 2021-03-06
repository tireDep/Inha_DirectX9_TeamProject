#pragma once
#include "IObject.h"

class CTile : public IObject
{
private:
	bool  pBox, pCylinder, pSphere;
	bool player, render;

	vector<ST_PNT_VERTEX> m_vecVertex;

	LPD3DXEFFECT m_pShader_Ocean;
	float m_shaderTime;
	float m_shaderTimeAngle;

	LPD3DXEFFECT m_pShader_Tile;
	LPDIRECT3DTEXTURE9 m_pShaderTxt;
	FLOAT m_fShaderTime;
	DWORD m_dwOldTime;

	void SetShader_Ocean();
	void SetShader_Tile();
public:
	CTile();
	~CTile();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	void Setup() { };
	void Setup(const ST_MapData & mapData);
	void Update(float duration) { m_pOBB->Update(&m_matWorld); };
	void Render();
	bool GetBool() { return render; }
	virtual string GetName() { return m_strName; }
	D3DXVECTOR3 SendPosition() { return D3DXVECTOR3(); }
};
/// Delete Later...
//vector<COBB*> m_pOBB;
//D3DXVECTOR3 m_vMin;
//D3DXVECTOR3 m_vMax;
//D3DXMATRIXA16 matWorld;
//D3DXVECTOR3 GetScale() { return m_vScale; }