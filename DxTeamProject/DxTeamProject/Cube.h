#pragma once
#include "Object.h"

class CCube : public CObject
{
private:
	vector<D3DXVECTOR3>	m_vecPos;
	LPD3DXMESH			m_pMeshCube;
	D3DMATERIAL9			m_stMtlCube;

	vector<ST_PC_VERTEX>	m_vecSideLineVertex;
	D3DXVECTOR3				m_vCenter;
	
public:
	CCube();
	CCube(D3DXVECTOR3 center);
	~CCube();
	
	void Setup();
	void Update(CRay ray, D3DXCOLOR& playerColor, vector<bool>& vecIsPick, vector<D3DXVECTOR3>& vecVPos);
	void Render();
	void SetPickState(bool set);

	string GetName();
	void ReceiveEvent(ST_EVENT eventMsg);
};