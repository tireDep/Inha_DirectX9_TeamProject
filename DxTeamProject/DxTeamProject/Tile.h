#pragma once
#include "IObject.h"


class COBB;
class CTile : public IObject
{
private:
	vector<COBB*> m_pOBB;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	D3DXMATRIXA16 matWorld;
public:
	CTile();
	~CTile();

	void Setup() { }
	void Setup(ST_MapData setData);
	void Update();
	void Render();
	
	D3DXVECTOR3 GetScale() { return m_vScale; }
};

