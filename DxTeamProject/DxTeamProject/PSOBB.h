#pragma once

class CPSOBB
{
public:
	CPSOBB();
	~CPSOBB();
private:
	// get set later
	D3DXVECTOR3			 m_vOriCenterPos;		// center
	D3DXVECTOR3			 m_vOriAxisDir[3];	// axis	
	float				 m_fAxisHalfLen[3];	// distance of center to OBB surface
	D3DXMATRIXA16		 m_matWorld;			// matrix
	vector<ST_PC_VERTEX> m_vOBBLineVertex; // OBB Box Line
	D3DXVECTOR3			 m_vCenterPos;
	D3DXVECTOR3			 m_vAxisDir[3];
	///
	//D3DXMATRIXA16 m_matWorldTM;

	//float m_fAxisLen[3];		
public:
	void Setup(CObject & object);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(CPSOBB * pOBB1, CPSOBB* pOBB2);
	bool IsCollision(CPSOBB * otherOBB);
	void Render();

	D3DXVECTOR3 GetCenter() { return m_vCenterPos; }
};