#pragma once

class CAllocateHierarchy;

class COBB
{
public:
	COBB();
	~COBB();
private:
	// get set later
	D3DXVECTOR3			 m_vOriCenterPos;	// center
	D3DXVECTOR3			 m_vOriAxisDir[3];	// axis	
	float				 m_fAxisHalfLen[3];	// distance of center to OBB surface
	D3DXMATRIXA16		 m_matWorld;		// matrix
	vector<ST_PC_VERTEX> m_vOBBLineVertex; // OBB Box Line
	D3DXVECTOR3			 m_vCenterPos;
	D3DXVECTOR3			 m_vAxisDir[3];
	float				 m_fAxisLen[3];
	///
	//D3DXMATRIXA16 m_matWorldTM;

	//float m_fAxisLen[3];		
public:
	void Setup(CObject & object);
	void Setup(CAllocateHierarchy & ah);
	void SetupMesh(D3DXVECTOR3 &vMin, D3DXVECTOR3 &vMax ,float cubesize);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(COBB * pOBB1, COBB* pOBB2);
	bool IsCollision(COBB * otherOBB);
	void Render();
	D3DXVECTOR3 GetCenter() { return m_vCenterPos; }
	float GetOBBWidth()  { return m_fAxisHalfLen[0]; }
	float GetOBBHeight() { return m_fAxisHalfLen[1]; }
	float GetOBBDepth()  { return m_fAxisHalfLen[2]; }
};