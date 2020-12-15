#pragma once
#include "IObject.h"

class CTile : public IObject
{
private:
	bool  pBox, pCylinder, pSphere;
	bool player;
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
	virtual string GetName() { return m_strName; }
};
/// Delete Later...
//vector<COBB*> m_pOBB;
//D3DXVECTOR3 m_vMin;
//D3DXVECTOR3 m_vMax;
//D3DXMATRIXA16 matWorld;
//D3DXVECTOR3 GetScale() { return m_vScale; }