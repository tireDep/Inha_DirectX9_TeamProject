#pragma once

class CPSOBB
{
public:
	CPSOBB();
	~CPSOBB();
private:
	// get set later
	D3DXVECTOR3 m_OriCenterPos;		// center
	D3DXVECTOR3 m_vOriAxisDir[3];	// axis
	D3DXVECTOR3 m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	float m_fAxisLen[3];			
	float m_fAxisHalfLen[3];		// distance of center to OBB surface
	D3DXMATRIXA16 m_matWorldTM;
public:
	void Setup(D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(CPSOBB * pOBB1, CPSOBB* pOBB2);
	void OBBBOX_RENDER();
};