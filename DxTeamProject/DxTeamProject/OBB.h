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
	D3DXMATRIXA16		 m_matWorld;		// OBB matrix
	D3DXVECTOR3			 m_vCenterPos;		// center from translate to OBB matrix
	D3DXVECTOR3			 m_vAxisDir[3];		// axis from translate to OBB matrix

	vector<ST_PC_VERTEX> m_vOBBLineVertex;  // OBB Box Line
	float				 m_fAxisLen[3];
public:
	void Setup(CObject & object);
	void Setup(CAllocateHierarchy & ah);
	void SetupMesh(D3DXVECTOR3 &vMin, D3DXVECTOR3 &vMax, float cubesize);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(COBB * pOBB1, COBB* pOBB2);
	bool IsCollision(COBB * otherOBB);
	bool IsCollision(COBB * otherOBB, D3DXVECTOR3* contactNormal, float* penetration);
	void Render();
	D3DXVECTOR3 GetCenter() { return m_vCenterPos; }
	float GetOBBWidth() { return m_fAxisHalfLen[0]; }	// distance of center to x axis
	float GetOBBHeight() { return m_fAxisHalfLen[1]; }	// distance of center to y axis
	float GetOBBDepth() { return m_fAxisHalfLen[2]; }  // distance of center to z axis
};