#pragma once
#include "IObject.h"

class CBackground : public IObject
{
private:
	bool pBox, pCylinder, pSphere;
	bool player, render;
	LPD3DXEFFECT m_pShader;
	LPDIRECT3DTEXTURE9 m_pShaderTxt;
	FLOAT m_fShaderTime;
	void SetShader();
public:
	CBackground();
	virtual ~CBackground();
	void pBoxBool(bool set) { pBox = set; }
	void pCylinderBool(bool set) { pCylinder = set; }
	void pSphereBool(bool set) { pSphere = set; }
	void SetBool(bool set) { player = set; }
	bool GetBool() { return render; }
	virtual void Setup() { };
	virtual void Setup(const ST_MapData & mapData);
	virtual void Update(float duration) { m_pOBB->Update(&m_matWorld);	};
	virtual void Render();
	virtual string GetName() { return m_strName; }
	D3DXVECTOR3 SendPosition(){ return D3DXVECTOR3(); }
};